/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file compressionEncode.c
 * @brief Encoding of EXI bodies in channels: compression and pre-compression
 *
 * EXI 1.0 section 9, following EXIficient 1.0.7 (EXIBodyEncoderReordered):
 * - the events of a block are written as they come: the structure channel;
 * - each AT and CH value (a list with its items) is recorded in the value channel of its
 *   QName (the attribute, or the element of the characters); channels are ordered by first
 *   occurrence; xsi:type and, under a schema-informed grammar, xsi:nil are structure values,
 *   written in place;
 * - the block closes right after the value that brings it to blockSize values, and at the
 *   end of the document (an empty last block writes nothing);
 * - at the close, the values are written channel by channel, so that they enter the string
 *   tables in that order: if the block has at most 100 values, after the structure in one
 *   stream; otherwise the structure is one stream, then the channels of at most 100 values
 *   together, then each larger channel as a stream of its own;
 * - streams are written as they are with pre-compression alignment; with compression each is
 *   a raw DEFLATE stream (RFC 1951), as java.util.zip.Deflater(level, nowrap) writes them:
 *   zlib, window bits -15, memory level 8, default strategy, finished per stream and reset
 *   between streams. Same zlib, same bytes as EXIficient.
 */

#include "compressionEncode.h"
#include "compressionDecode.h"
#include "memManagement.h"
#include "dynamicArray.h"
#include "errorHandle.h"
#include <string.h>

#if defined(EXIP_USE_ZLIB)
#include <zlib.h>
#endif

/** A channel with at most this many values in a block shares a stream (spec 9.3) */
#define SMALL_CHANNEL_VALUES 100
#define ENCODER_ARRAY_CHUNK 32
/** The buffer the serializer writes into during the body; full, it goes to a segment */
#define WORK_BUFFER_SIZE 512

/* Encoded bytes kept in memory: the structure of a block, a group of value channels */
typedef struct
{
	char* data;
	size_t len;
	size_t cap;
} Segment;

/* A value of a channel: the records [firstRecord, firstRecord + recordCount), a list head
 * followed by its items */
typedef struct
{
	Index firstRecord;
	Index recordCount;
	Index nextInChannel;
} ChannelValue;

typedef struct
{
	QNameID qnameID;
	Index first;
	Index last;
	Index count;
} EncChannel;

typedef struct { DynArray dynArray; ValueContent* rec; Index count; } RecordArray;
typedef struct { DynArray dynArray; ChannelValue* val; Index count; } ChannelValueArray;
typedef struct { DynArray dynArray; EncChannel* ch; Index count; } EncChannelArray;

struct CompressionEncoder
{
	BinaryBuffer app;        // the application's buffer and stream: the encoded stream
	Index appIndx;           // bytes of the encoded stream in app.buf
	char work[WORK_BUFFER_SIZE];
	Segment structure;
	Segment values;
	Segment* target;         // where full work buffers go
	RecordArray records;
	ChannelValueArray values_;
	EncChannelArray channels;
	AllocList blockMem;
	Index blockValues;
	Index listValue;         // the list value receiving items
	unsigned int listItemsLeft;
	exip_bool recording;
	exip_bool redirected;
#if defined(EXIP_USE_ZLIB)
	exip_bool deflating;
	z_stream zstrm;
#endif
};

typedef struct CompressionEncoder CompressionEncoder;

static errorCode closeBlock(EXIStream* strm, CompressionEncoder* enc);

/******* Output *******/

static errorCode segmentAppend(Segment* seg, const char* data, size_t len)
{
	if(seg->len + len > seg->cap)
	{
		size_t cap = seg->cap == 0 ? 1024 : seg->cap;
		char* grown;

		while(cap < seg->len + len)
			cap *= 2;
		grown = EXIP_REALLOC(seg->data, cap);
		if(grown == NULL)
			return EXIP_MEMORY_ALLOCATION_ERROR;
		seg->data = grown;
		seg->cap = cap;
	}
	memcpy(seg->data + seg->len, data, len);
	seg->len += len;
	return EXIP_OK;
}

/* readWriteToStream of the work buffer: full buffers go to the current segment */
static size_t writeToSegment(void* buf, size_t size, void* stream)
{
	CompressionEncoder* enc = (CompressionEncoder*) stream;
	if(segmentAppend(enc->target, (const char*) buf, size) != EXIP_OK)
		return 0;
	return size;
}

/* The serializer writes into the work buffer, whose content goes to target */
static void writeInto(EXIStream* strm, CompressionEncoder* enc, Segment* target)
{
	enc->target = target;
	strm->buffer.buf = enc->work;
	strm->buffer.bufLen = WORK_BUFFER_SIZE;
	strm->buffer.bufContent = 0;
	strm->buffer.ioStrm.readWriteToStream = writeToSegment;
	strm->buffer.ioStrm.stream = enc;
	strm->context.bufferIndx = 0;
	strm->context.bitPointer = 0;
}

/* The rest of the work buffer to the current segment; channels are byte-aligned */
static errorCode flushWork(EXIStream* strm, CompressionEncoder* enc)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;

	if(strm->context.bitPointer != 0)
		return EXIP_INCONSISTENT_PROC_STATE;
	TRY(segmentAppend(enc->target, enc->work, strm->context.bufferIndx));
	strm->context.bufferIndx = 0;
	return EXIP_OK;
}

/* Encoded bytes to the application's buffer, which goes to its stream when full */
static errorCode writeOut(CompressionEncoder* enc, const char* data, size_t len)
{
	while(len > 0)
	{
		size_t room = enc->app.bufLen - enc->appIndx;
		size_t n = len < room ? len : room;

		memcpy(enc->app.buf + enc->appIndx, data, n);
		enc->appIndx += n;
		data += n;
		len -= n;
		if(enc->appIndx == enc->app.bufLen && len > 0)
		{
			if(enc->app.ioStrm.readWriteToStream == NULL)
				return EXIP_BUFFER_END_REACHED;
			if(enc->app.ioStrm.readWriteToStream(enc->app.buf, enc->app.bufLen, enc->app.ioStrm.stream) < enc->app.bufLen)
				return EXIP_UNEXPECTED_ERROR;
			enc->appIndx = 0;
		}
	}
	return EXIP_OK;
}

/* One stream of the block: as it is (pre-compression), or deflated (compression) */
static errorCode writeStream(CompressionEncoder* enc, Segment* seg)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
#if defined(EXIP_USE_ZLIB)
	if(enc->deflating)
	{
		unsigned char chunk[512];
		int zret;

		enc->zstrm.next_in = (Bytef*) seg->data;
		enc->zstrm.avail_in = (uInt) seg->len;
		do
		{
			enc->zstrm.next_out = chunk;
			enc->zstrm.avail_out = sizeof chunk;
			zret = deflate(&enc->zstrm, Z_FINISH);
			if(zret != Z_OK && zret != Z_STREAM_END)
				return EXIP_UNEXPECTED_ERROR;
			TRY(writeOut(enc, (const char*) chunk, sizeof chunk - enc->zstrm.avail_out));
		}
		while(zret != Z_STREAM_END);
		if(deflateReset(&enc->zstrm) != Z_OK)
			return EXIP_UNEXPECTED_ERROR;
		return EXIP_OK;
	}
#endif
	TRY(writeOut(enc, seg->data, seg->len));
	return EXIP_OK;
}

/******* Recording *******/

errorCode compressionRecordValue(EXIStream* strm, const ValueContent* vc, exip_bool* recorded)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionEncoder* enc = strm->channelEncoder;
	ValueContent* rec;
	Index recId;
	exip_bool complete = FALSE;

	*recorded = FALSE;
	if(enc == NULL || !enc->recording)
		return EXIP_OK;

	// xsi:nil under a schema-informed grammar is a structure value (xsi:type does not come
	// here: qnameData writes it in place)
	if(vc->qnameID.uriId == XML_SCHEMA_INSTANCE_ID && vc->qnameID.lnId == XML_SCHEMA_INSTANCE_NIL_ID &&
			strm->gStack != NULL && IS_SCHEMA(strm->gStack->grammar->props))
		return EXIP_OK;

	// The checks the content would make when it is written at the close
	TRY(checkValueContent(strm, vc));

	TRY(addEmptyDynEntry(&enc->records.dynArray, (void**) &rec, &recId));
	*rec = *vc;
	// The application may free or reuse its data after the call
	if(vc->kind == VALUE_CONTENT_STRING && vc->u.strVal.length > 0)
	{
		rec->u.strVal.str = memManagedAllocate(&enc->blockMem, sizeof(CharType) * vc->u.strVal.length);
		if(rec->u.strVal.str == NULL)
			return EXIP_MEMORY_ALLOCATION_ERROR;
		memcpy(rec->u.strVal.str, vc->u.strVal.str, sizeof(CharType) * vc->u.strVal.length);
	}
	else if(vc->kind == VALUE_CONTENT_BINARY && vc->u.binVal.nbytes > 0)
	{
		char* copy = memManagedAllocate(&enc->blockMem, vc->u.binVal.nbytes);
		if(copy == NULL)
			return EXIP_MEMORY_ALLOCATION_ERROR;
		memcpy(copy, vc->u.binVal.data, vc->u.binVal.nbytes);
		rec->u.binVal.data = copy;
	}

	if(enc->listItemsLeft > 0)
	{
		// An item of the list being written: part of the list's value
		enc->values_.val[enc->listValue].recordCount++;
		enc->listItemsLeft--;
		complete = enc->listItemsLeft == 0;
	}
	else
	{
		ChannelValue* val;
		EncChannel* channel;
		Index valueId;
		Index ch;

		TRY(addEmptyDynEntry(&enc->values_.dynArray, (void**) &val, &valueId));
		val->firstRecord = recId;
		val->recordCount = 1;
		val->nextInChannel = INDEX_MAX;

		// Its channel, searched from the most recent one
		for(ch = enc->channels.count; ch > 0; ch--)
		{
			if(enc->channels.ch[ch - 1].qnameID.uriId == vc->qnameID.uriId && enc->channels.ch[ch - 1].qnameID.lnId == vc->qnameID.lnId)
				break;
		}
		if(ch == 0)
		{
			TRY(addEmptyDynEntry(&enc->channels.dynArray, (void**) &channel, &ch));
			channel->qnameID = vc->qnameID;
			channel->first = valueId;
			channel->count = 0;
		}
		else
		{
			channel = &enc->channels.ch[ch - 1];
			enc->values_.val[channel->last].nextInChannel = valueId;
		}
		channel->last = valueId;
		channel->count++;

		if(vc->kind == VALUE_CONTENT_LIST && vc->u.itemCount > 0)
		{
			enc->listValue = valueId;
			enc->listItemsLeft = vc->u.itemCount;
		}
		else
			complete = TRUE;
	}

	*recorded = TRUE;
	if(complete)
	{
		enc->blockValues++;
		if(enc->blockValues == strm->header.opts.blockSize)
			TRY(closeBlock(strm, enc));
	}

	return EXIP_OK;
}

/******* Block close *******/

static errorCode writeChannel(EXIStream* strm, CompressionEncoder* enc, Index ch)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Index valueId = enc->channels.ch[ch].first;

	while(valueId != INDEX_MAX)
	{
		ChannelValue* val = &enc->values_.val[valueId];
		Index r;

		for(r = val->firstRecord; r < val->firstRecord + val->recordCount; r++)
			TRY(encodeValueContent(strm, &enc->records.rec[r]));
		valueId = val->nextInChannel;
	}
	return EXIP_OK;
}

static errorCode resetBlock(CompressionEncoder* enc)
{
	enc->records.count = 0;
	enc->values_.count = 0;
	enc->channels.count = 0;
	enc->blockValues = 0;
	enc->listItemsLeft = 0;
	enc->structure.len = 0;
	enc->values.len = 0;
	freeAllocList(&enc->blockMem);
	return initAllocList(&enc->blockMem);
}

static errorCode closeBlock(EXIStream* strm, CompressionEncoder* enc)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Index ch;

	TRY(flushWork(strm, enc));

	// Nothing in the block (implicit events after the last block): no stream
	if(enc->structure.len > 0 || enc->blockValues > 0)
	{
		enc->recording = FALSE;
		if(enc->blockValues <= SMALL_CHANNEL_VALUES)
		{
			// One stream: the structure, then every channel
			writeInto(strm, enc, &enc->structure);
			for(ch = 0; ch < enc->channels.count; ch++)
				TRY(writeChannel(strm, enc, ch));
			TRY(flushWork(strm, enc));
			TRY(writeStream(enc, &enc->structure));
		}
		else
		{
			exip_bool anySmall = FALSE;

			TRY(writeStream(enc, &enc->structure));

			// The channels of at most 100 values, together
			writeInto(strm, enc, &enc->values);
			for(ch = 0; ch < enc->channels.count; ch++)
			{
				if(enc->channels.ch[ch].count <= SMALL_CHANNEL_VALUES)
				{
					TRY(writeChannel(strm, enc, ch));
					anySmall = TRUE;
				}
			}
			TRY(flushWork(strm, enc));
			if(anySmall)
				TRY(writeStream(enc, &enc->values));

			// Each larger channel
			for(ch = 0; ch < enc->channels.count; ch++)
			{
				if(enc->channels.ch[ch].count > SMALL_CHANNEL_VALUES)
				{
					enc->values.len = 0;
					TRY(writeChannel(strm, enc, ch));
					TRY(flushWork(strm, enc));
					TRY(writeStream(enc, &enc->values));
				}
			}
		}
		enc->recording = TRUE;
	}

	TRY(resetBlock(enc));
	writeInto(strm, enc, &enc->structure);

	return EXIP_OK;
}

/******* Life cycle *******/

errorCode initCompressionEncoder(EXIStream* strm)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionEncoder* enc;

#if !defined(EXIP_USE_ZLIB)
	if(WITH_COMPRESSION(strm->header.opts.enumOpt))
	{
		DEBUG_MSG(EXIP_LOG_ERROR, DEBUG_CONTENT_IO, ("\n> EXI compression needs exip built with zlib"));
		return EXIP_NOT_IMPLEMENTED_YET;
	}
#endif
	// The header ends on a byte boundary (it is padded when it has options)
	if(strm->context.bitPointer != 0)
		return EXIP_INCONSISTENT_PROC_STATE;

	enc = memManagedAllocate(&strm->memList, sizeof(CompressionEncoder));
	if(enc == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;
	memset(enc, 0, sizeof(CompressionEncoder));
	enc->app = strm->buffer;
	enc->appIndx = strm->context.bufferIndx;

	TRY(initAllocList(&enc->blockMem));
	strm->channelEncoder = enc;
	TRY(createDynArray(&enc->records.dynArray, sizeof(ValueContent), ENCODER_ARRAY_CHUNK));
	TRY(createDynArray(&enc->values_.dynArray, sizeof(ChannelValue), ENCODER_ARRAY_CHUNK));
	TRY(createDynArray(&enc->channels.dynArray, sizeof(EncChannel), ENCODER_ARRAY_CHUNK));

#if defined(EXIP_USE_ZLIB)
	if(WITH_COMPRESSION(strm->header.opts.enumOpt))
	{
		enc->zstrm.zalloc = Z_NULL;
		enc->zstrm.zfree = Z_NULL;
		enc->zstrm.opaque = Z_NULL;
		if(deflateInit2(&enc->zstrm, EXIP_DEFLATE_LEVEL, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK)
			return EXIP_UNEXPECTED_ERROR;
		enc->deflating = TRUE;
	}
#endif

	writeInto(strm, enc, &enc->structure);
	enc->redirected = TRUE;
	enc->recording = TRUE;

	return EXIP_OK;
}

/* The application's buffer again, holding the encoded bytes not yet written to its stream */
static void restoreApplicationBuffer(EXIStream* strm, CompressionEncoder* enc)
{
	if(!enc->redirected)
		return;
	strm->buffer = enc->app;
	strm->buffer.bufContent = enc->appIndx;
	strm->context.bufferIndx = enc->appIndx;
	strm->context.bitPointer = 0;
	enc->redirected = FALSE;
}

errorCode compressionEndDocument(EXIStream* strm)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionEncoder* enc = strm->channelEncoder;

	TRY(closeBlock(strm, enc));
	enc->recording = FALSE;
	restoreApplicationBuffer(strm, enc);

	return EXIP_OK;
}

void destroyCompressionEncoder(EXIStream* strm)
{
	CompressionEncoder* enc = strm->channelEncoder;

	if(enc == NULL)
		return;

	restoreApplicationBuffer(strm, enc);
#if defined(EXIP_USE_ZLIB)
	if(enc->deflating)
		deflateEnd(&enc->zstrm);
	enc->deflating = FALSE;
#endif
	if(enc->records.rec != NULL)
		destroyDynArray(&enc->records.dynArray);
	if(enc->values_.val != NULL)
		destroyDynArray(&enc->values_.dynArray);
	if(enc->channels.ch != NULL)
		destroyDynArray(&enc->channels.dynArray);
	EXIP_MFREE(enc->structure.data);
	EXIP_MFREE(enc->values.data);
	freeAllocList(&enc->blockMem);
	strm->channelEncoder = NULL;
}
