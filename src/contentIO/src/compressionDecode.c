/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file compressionDecode.c
 * @brief Decoding of EXI streams with channels: compression and pre-compression
 *
 * EXI 1.0 section 9, following EXIficient 1.0.7 (EXIBodyDecoderReordered), which Nagasena
 * agrees with on every rexi-interop case:
 * - a block holds the events up to the one that brings its channel values to blockSize, or
 *   to the end of the document;
 * - the structure channel has the event codes and their content, and the values of xsi:type
 *   and (under a schema-informed grammar) xsi:nil;
 * - every other AT and CH value is in the value channel of its QName (the attribute, or the
 *   element containing the characters); channels are ordered by first occurrence;
 * - the channels with at most 100 values come first, then each larger channel (in a block
 *   of at most 100 values that is simply the channel order); with compression these are
 *   consecutive DEFLATE streams, whose inflated bytes are read as one byte-aligned stream;
 * - values enter the string tables in the order they are decoded, and the tables persist
 *   across blocks.
 */

#include "compressionDecode.h"
#include "bodyDecode.h"
#include "grammars.h"
#include "memManagement.h"
#include "dynamicArray.h"
#include "errorHandle.h"
#include <string.h>

#if defined(EXIP_USE_ZLIB)
#include <zlib.h>
#endif

/** A channel with at most this many values in a block shares a stream (spec 9.3) */
#define SMALL_CHANNEL_VALUES 100
#define CHANNEL_ARRAY_CHUNK 32

/* Recorded events of the current block */
enum ChEventKind
{
	CEV_SE,
	CEV_EE,
	CEV_AT,
	CEV_ED,
	CEV_NS,
	CEV_SC,
	CEV_PI,
	CEV_VALUE
};

typedef struct
{
	unsigned char kind;
	unsigned char hasPrefix;
	exip_bool isLocal;
	String a; // SE, AT: uri; NS: namespace
	String b; // SE, AT: local name; NS: prefix
	String c; // SE, AT: prefix
	Index valueId; // CEV_VALUE
} ChEvent;

/* The handler calls one value produces (a list: listData and its items) */
enum ChRecordKind
{
	CR_INT,
	CR_BOOL,
	CR_STRING,
	CR_FLOAT,
	CR_BINARY,
	CR_DATETIME,
	CR_DECIMAL,
	CR_LIST,
	CR_QNAME
};

typedef struct
{
	unsigned char kind;
	unsigned char hasPrefix;
	EXIType exiType;
	union
	{
		Integer intVal;
		exip_bool boolVal;
		String strVal;
		Float floatVal;
		struct { char* data; Index nbytes; } binVal;
		EXIPDateTime dtVal;
		Decimal decVal;
		struct { EXITypeClass type; unsigned int count; } listVal;
		struct { String uri; String ln; String pfx; } qnameVal;
	} u;
} ChRecord;

typedef struct
{
	QNameID qnameID;
	Index typeId;
	Index firstRecord;
	Index recordCount;
	Index nextInChannel;
} ChValue;

typedef struct
{
	QNameID qnameID;
	Index first;
	Index last;
	Index count;
} Channel;

typedef struct { DynArray dynArray; ChEvent* ev; Index count; } ChEventArray;
typedef struct { DynArray dynArray; ChRecord* rec; Index count; } ChRecordArray;
typedef struct { DynArray dynArray; ChValue* val; Index count; } ChValueArray;
typedef struct { DynArray dynArray; Channel* ch; Index count; } ChannelArray;

enum ChPhase
{
	PHASE_STRUCTURE,
	PHASE_CHANNELS,
	PHASE_REPLAY
};

struct CompressionDecoder
{
	EXIStream* strm;
	ContentHandler recorder;
	ContentHandler* user;
	void* app_data;
	ChEventArray events;
	ChRecordArray records;
	ChValueArray values;
	ChannelArray channels;
	AllocList blockMem;
	unsigned char phase;
	Index currentValue;  // the value receiving handler calls, INDEX_MAX if none
	Index blockValues;   // channel values of the block
	Index replayPos;
	exip_bool documentEnded;
#if EXIP_COMPRESSION_TRACE == ON
	unsigned int blockNumber;
#endif
#if defined(EXIP_USE_ZLIB)
	exip_bool inflating;
	BinaryBuffer raw;       // the application's buffer and stream: the compressed input
	unsigned char* rawBuf;  // compressed input read from the application's stream
	z_stream zstrm;
#endif
};

typedef struct CompressionDecoder CompressionDecoder;

/******* Inflating the body (compression) *******/

#if defined(EXIP_USE_ZLIB)
/* readWriteToStream of the stream buffer: inflates the body. The body is a sequence of raw
 * DEFLATE streams (RFC 1951); a stream end restarts the inflater on the following bytes. */
static size_t readInflatedChunk(void* buf, size_t size, void* stream)
{
	CompressionDecoder* dec = (CompressionDecoder*) stream;

	dec->zstrm.next_out = (Bytef*) buf;
	dec->zstrm.avail_out = (uInt) size;

	while(dec->zstrm.avail_out > 0)
	{
		int zret;

		if(dec->zstrm.avail_in == 0)
		{
			size_t bytesRead = 0;

			// After the rest of the application's buffer: its stream, if any
			if(dec->raw.ioStrm.readWriteToStream != NULL)
			{
				if(dec->rawBuf == NULL)
				{
					dec->rawBuf = memManagedAllocate(&dec->strm->memList, dec->raw.bufLen);
					if(dec->rawBuf == NULL)
						break;
				}
				bytesRead = dec->raw.ioStrm.readWriteToStream(dec->rawBuf, dec->raw.bufLen, dec->raw.ioStrm.stream);
			}
			if(bytesRead == 0)
				break;
			dec->zstrm.next_in = dec->rawBuf;
			dec->zstrm.avail_in = (uInt) bytesRead;
		}

		zret = inflate(&dec->zstrm, Z_NO_FLUSH);
		if(zret == Z_STREAM_END)
		{
			if(inflateReset(&dec->zstrm) != Z_OK)
				break;
		}
		else if(zret != Z_OK)
		{
			// Z_BUF_ERROR: no progress possible; otherwise a corrupt stream. Either way the
			// reader sees the end of the input
			DEBUG_MSG(EXIP_LOG_ERROR, DEBUG_CONTENT_IO, ("\n> Inflating the EXI body failed (zlib %d)", zret));
			break;
		}
	}

	return size - dec->zstrm.avail_out;
}

static errorCode initInflater(CompressionDecoder* dec, EXIStream* strm)
{
	char* inflated;

	// The header is padded to a byte boundary when compression is used
	if(strm->context.bitPointer != 0)
		return EXIP_INCONSISTENT_PROC_STATE;

	// The stream buffer is given inflated bytes from here on; the application's buffer
	// stays as it is: its rest is the first compressed input
	inflated = memManagedAllocate(&strm->memList, strm->buffer.bufLen);
	if(inflated == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;

	dec->raw = strm->buffer;
	dec->zstrm.zalloc = Z_NULL;
	dec->zstrm.zfree = Z_NULL;
	dec->zstrm.opaque = Z_NULL;
	dec->zstrm.next_in = (Bytef*) (strm->buffer.buf + strm->context.bufferIndx);
	dec->zstrm.avail_in = (uInt) (strm->buffer.bufContent - strm->context.bufferIndx);
	if(inflateInit2(&dec->zstrm, -MAX_WBITS) != Z_OK)
		return EXIP_UNEXPECTED_ERROR;
	dec->inflating = TRUE;

	strm->buffer.buf = inflated;
	strm->buffer.bufContent = 0;
	strm->buffer.ioStrm.readWriteToStream = readInflatedChunk;
	strm->buffer.ioStrm.stream = dec;
	strm->context.bufferIndx = 0;
	strm->context.bitPointer = 0;

	return EXIP_OK;
}
#endif

/******* Recording *******/

static errorCode newEvent(CompressionDecoder* dec, unsigned char kind, ChEvent** ev)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Index id;

	TRY(addEmptyDynEntry(&dec->events.dynArray, (void**) ev, &id));
	memset(*ev, 0, sizeof(ChEvent));
	(*ev)->kind = kind;
	// An event ends the value the handler calls belonged to
	dec->currentValue = INDEX_MAX;

	return EXIP_OK;
}

static errorCode newValue(CompressionDecoder* dec, QNameID qnameID, Index typeId, Index* valueId)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChValue* val;
	ChEvent* ev;

	TRY(newEvent(dec, CEV_VALUE, &ev));
	TRY(addEmptyDynEntry(&dec->values.dynArray, (void**) &val, valueId));
	val->qnameID = qnameID;
	val->typeId = typeId;
	val->firstRecord = 0;
	val->recordCount = 0;
	val->nextInChannel = INDEX_MAX;
	ev->valueId = *valueId;

	return EXIP_OK;
}

/* A handler call of a value: during the structure pass these are the structure values
 * (xsi:type, xsi:nil), which start a value of their own; during the channel pass they belong
 * to the deferred value being decoded */
static errorCode newRecord(CompressionDecoder* dec, unsigned char kind, ChRecord** rec)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Index id;
	ChValue* val;

	if(dec->currentValue == INDEX_MAX)
	{
		QNameID noQName = {URI_MAX, LN_MAX};

		if(dec->phase != PHASE_STRUCTURE)
			return EXIP_INCONSISTENT_PROC_STATE;
		TRY(newValue(dec, noQName, INDEX_MAX, &dec->currentValue));
	}

	TRY(addEmptyDynEntry(&dec->records.dynArray, (void**) rec, &id));
	memset(*rec, 0, sizeof(ChRecord));
	(*rec)->kind = kind;
	(*rec)->exiType = dec->strm->context.valueExiType;

	val = &dec->values.val[dec->currentValue];
	if(val->recordCount == 0)
		val->firstRecord = id;
	val->recordCount++;

	return EXIP_OK;
}

/* Strings the handler gets for a value may be freed after the call: copy them */
static errorCode copyString(CompressionDecoder* dec, const String* src, String* dst)
{
	dst->length = src->length;
	dst->str = NULL;
	if(src->length > 0 && src->str != NULL)
	{
		dst->str = memManagedAllocate(&dec->blockMem, sizeof(CharType) * src->length);
		if(dst->str == NULL)
			return EXIP_MEMORY_ALLOCATION_ERROR;
		memcpy(dst->str, src->str, sizeof(CharType) * src->length);
	}
	return EXIP_OK;
}

/* QNames point into the string tables, whose arrays can move as they grow: keep the Strings
 * (their characters do not move) */
static void keepQName(QName qname, ChEvent* ev)
{
	ev->a = *qname.uri;
	ev->b = *qname.localName;
	ev->hasPrefix = qname.prefix != NULL;
	if(qname.prefix != NULL)
		ev->c = *qname.prefix;
}

static errorCode recStartElement(QName qname, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChEvent* ev;
	TRY(newEvent((CompressionDecoder*) app_data, CEV_SE, &ev));
	keepQName(qname, ev);
	return EXIP_OK;
}

static errorCode recAttribute(QName qname, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChEvent* ev;
	TRY(newEvent((CompressionDecoder*) app_data, CEV_AT, &ev));
	keepQName(qname, ev);
	return EXIP_OK;
}

static errorCode recEndElement(void* app_data)
{
	ChEvent* ev;
	return newEvent((CompressionDecoder*) app_data, CEV_EE, &ev);
}

static errorCode recEndDocument(void* app_data)
{
	ChEvent* ev;
	return newEvent((CompressionDecoder*) app_data, CEV_ED, &ev);
}

static errorCode recSelfContained(void* app_data)
{
	ChEvent* ev;
	return newEvent((CompressionDecoder*) app_data, CEV_SC, &ev);
}

static errorCode recProcessingInstruction(void* app_data)
{
	ChEvent* ev;
	return newEvent((CompressionDecoder*) app_data, CEV_PI, &ev);
}

static errorCode recNamespaceDeclaration(const String ns, const String prefix, exip_bool isLocalElementNS, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChEvent* ev;
	TRY(newEvent((CompressionDecoder*) app_data, CEV_NS, &ev));
	ev->a = ns;
	ev->b = prefix;
	ev->isLocal = isLocalElementNS;
	return EXIP_OK;
}

static errorCode recIntData(Integer int_val, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChRecord* rec;
	TRY(newRecord((CompressionDecoder*) app_data, CR_INT, &rec));
	rec->u.intVal = int_val;
	return EXIP_OK;
}

static errorCode recBooleanData(exip_bool bool_val, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChRecord* rec;
	TRY(newRecord((CompressionDecoder*) app_data, CR_BOOL, &rec));
	rec->u.boolVal = bool_val;
	return EXIP_OK;
}

static errorCode recStringData(const String str_val, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionDecoder* dec = (CompressionDecoder*) app_data;
	ChRecord* rec;
	TRY(newRecord(dec, CR_STRING, &rec));
	return copyString(dec, &str_val, &rec->u.strVal);
}

static errorCode recFloatData(Float float_val, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChRecord* rec;
	TRY(newRecord((CompressionDecoder*) app_data, CR_FLOAT, &rec));
	rec->u.floatVal = float_val;
	return EXIP_OK;
}

static errorCode recBinaryData(const char* binary_val, Index nbytes, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionDecoder* dec = (CompressionDecoder*) app_data;
	ChRecord* rec;
	TRY(newRecord(dec, CR_BINARY, &rec));
	rec->u.binVal.nbytes = nbytes;
	rec->u.binVal.data = NULL;
	if(nbytes > 0)
	{
		rec->u.binVal.data = memManagedAllocate(&dec->blockMem, nbytes);
		if(rec->u.binVal.data == NULL)
			return EXIP_MEMORY_ALLOCATION_ERROR;
		memcpy(rec->u.binVal.data, binary_val, nbytes);
	}
	return EXIP_OK;
}

static errorCode recDateTimeData(EXIPDateTime dt_val, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChRecord* rec;
	TRY(newRecord((CompressionDecoder*) app_data, CR_DATETIME, &rec));
	rec->u.dtVal = dt_val;
	return EXIP_OK;
}

static errorCode recDecimalData(Decimal dec_val, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChRecord* rec;
	TRY(newRecord((CompressionDecoder*) app_data, CR_DECIMAL, &rec));
	rec->u.decVal = dec_val;
	return EXIP_OK;
}

static errorCode recListData(EXITypeClass exiType, unsigned int itemCount, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChRecord* rec;
	TRY(newRecord((CompressionDecoder*) app_data, CR_LIST, &rec));
	rec->u.listVal.type = exiType;
	rec->u.listVal.count = itemCount;
	return EXIP_OK;
}

static errorCode recQnameData(const QName qname, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ChRecord* rec;
	TRY(newRecord((CompressionDecoder*) app_data, CR_QNAME, &rec));
	rec->u.qnameVal.uri = *qname.uri;
	rec->u.qnameVal.ln = *qname.localName;
	rec->hasPrefix = qname.prefix != NULL;
	if(qname.prefix != NULL)
		rec->u.qnameVal.pfx = *qname.prefix;
	return EXIP_OK;
}

/* Errors and warnings go to the application at once */
static errorCode recWarning(const errorCode code, const char* msg, void* app_data)
{
	CompressionDecoder* dec = (CompressionDecoder*) app_data;
	if(dec->user->warning != NULL)
		return dec->user->warning(code, msg, dec->app_data);
	return EXIP_OK;
}

static errorCode recError(const errorCode code, const char* msg, void* app_data)
{
	CompressionDecoder* dec = (CompressionDecoder*) app_data;
	if(dec->user->error != NULL)
		return dec->user->error(code, msg, dec->app_data);
	return EXIP_OK;
}

static errorCode recFatalError(const errorCode code, const char* msg, void* app_data)
{
	CompressionDecoder* dec = (CompressionDecoder*) app_data;
	if(dec->user->fatalError != NULL)
		return dec->user->fatalError(code, msg, dec->app_data);
	return EXIP_OK;
}

errorCode compressionDeferValue(EXIStream* strm, Index typeId, QNameID qnameID, exip_bool* deferred)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionDecoder* dec = strm->compression;
	Index valueId;
	Index ch;
	Channel* channel;

	*deferred = FALSE;
	if(dec == NULL || dec->phase != PHASE_STRUCTURE)
		return EXIP_OK;

	// The structure values: decoded in place (EXIficient handleSpecialAttributeCases)
	if(qnameID.uriId == XML_SCHEMA_INSTANCE_ID &&
			(qnameID.lnId == XML_SCHEMA_INSTANCE_TYPE_ID ||
			 (qnameID.lnId == XML_SCHEMA_INSTANCE_NIL_ID && strm->gStack != NULL && IS_SCHEMA(strm->gStack->grammar->props))))
	{
		dec->currentValue = INDEX_MAX;
		return EXIP_OK;
	}

	TRY(newValue(dec, qnameID, typeId, &valueId));
	dec->currentValue = INDEX_MAX;

	// Its channel (channels are numbered by first occurrence in the block); searched from
	// the most recent one
	for(ch = dec->channels.count; ch > 0; ch--)
	{
		if(dec->channels.ch[ch - 1].qnameID.uriId == qnameID.uriId && dec->channels.ch[ch - 1].qnameID.lnId == qnameID.lnId)
			break;
	}
	if(ch == 0)
	{
		TRY(addEmptyDynEntry(&dec->channels.dynArray, (void**) &channel, &ch));
		channel->qnameID = qnameID;
		channel->first = valueId;
		channel->count = 0;
	}
	else
	{
		channel = &dec->channels.ch[ch - 1];
		dec->values.val[channel->last].nextInChannel = valueId;
	}
	channel->last = valueId;
	channel->count++;

	dec->blockValues++;
	*deferred = TRUE;
	return EXIP_OK;
}

/******* The block passes *******/

static errorCode resetBlock(CompressionDecoder* dec)
{
	dec->events.count = 0;
	dec->records.count = 0;
	dec->values.count = 0;
	dec->channels.count = 0;
	dec->blockValues = 0;
	dec->replayPos = 0;
	dec->currentValue = INDEX_MAX;
	freeAllocList(&dec->blockMem);
	return initAllocList(&dec->blockMem);
}

static errorCode decodeStructure(EXIStream* strm, CompressionDecoder* dec)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;

	dec->phase = PHASE_STRUCTURE;
	do
	{
		SmallIndex nonTermID = GR_VOID_NON_TERMINAL;

		TRY(processNextProduction(strm, &nonTermID, &dec->recorder, dec));
		if(nonTermID == GR_VOID_NON_TERMINAL)
		{
			popGrammar(&strm->gStack);
			if(strm->gStack == NULL)
			{
				dec->documentEnded = TRUE;
				break;
			}
		}
		else
			strm->gStack->currNonTermID = nonTermID;
	}
	while(dec->blockValues < strm->header.opts.blockSize);

	return EXIP_OK;
}

static errorCode decodeChannel(EXIStream* strm, CompressionDecoder* dec, Index ch)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Index valueId = dec->channels.ch[ch].first;

	while(valueId != INDEX_MAX)
	{
		SmallIndex nonTermID = GR_VOID_NON_TERMINAL;
		ChValue val = dec->values.val[valueId];

		dec->currentValue = valueId;
		TRY(decodeValueItem(strm, val.typeId, &dec->recorder, &nonTermID, val.qnameID, dec));
		valueId = val.nextInChannel;
	}
	dec->currentValue = INDEX_MAX;

	return EXIP_OK;
}

static errorCode decodeChannels(EXIStream* strm, CompressionDecoder* dec)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Index ch;

	dec->phase = PHASE_CHANNELS;
	// The channels of at most 100 values, then the larger ones
	for(ch = 0; ch < dec->channels.count; ch++)
	{
		if(dec->channels.ch[ch].count <= SMALL_CHANNEL_VALUES)
			TRY(decodeChannel(strm, dec, ch));
	}
	for(ch = 0; ch < dec->channels.count; ch++)
	{
		if(dec->channels.ch[ch].count > SMALL_CHANNEL_VALUES)
			TRY(decodeChannel(strm, dec, ch));
	}

#if EXIP_COMPRESSION_TRACE == ON
	fprintf(stderr, "\n> Channels block %u: %u events, %u values, %u channels%s", dec->blockNumber,
			(unsigned int) dec->events.count, (unsigned int) dec->blockValues, (unsigned int) dec->channels.count,
			dec->documentEnded ? " (last)" : "");
	fflush(stderr);
#endif

	return EXIP_OK;
}

static errorCode replayValue(CompressionDecoder* dec, ChValue* val)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ContentHandler* h = dec->user;
	Index r;

	for(r = val->firstRecord; r < val->firstRecord + val->recordCount; r++)
	{
		ChRecord* rec = &dec->records.rec[r];

		// What parse.valueExiType reports inside the handler call
		dec->strm->context.valueExiType = rec->exiType;
		switch(rec->kind)
		{
			case CR_INT:
				if(h->intData != NULL)
					TRY(h->intData(rec->u.intVal, dec->app_data));
			break;
			case CR_BOOL:
				if(h->booleanData != NULL)
					TRY(h->booleanData(rec->u.boolVal, dec->app_data));
			break;
			case CR_STRING:
				if(h->stringData != NULL)
					TRY(h->stringData(rec->u.strVal, dec->app_data));
			break;
			case CR_FLOAT:
				if(h->floatData != NULL)
					TRY(h->floatData(rec->u.floatVal, dec->app_data));
			break;
			case CR_BINARY:
				if(h->binaryData != NULL)
					TRY(h->binaryData(rec->u.binVal.data, rec->u.binVal.nbytes, dec->app_data));
			break;
			case CR_DATETIME:
				if(h->dateTimeData != NULL)
					TRY(h->dateTimeData(rec->u.dtVal, dec->app_data));
			break;
			case CR_DECIMAL:
				if(h->decimalData != NULL)
					TRY(h->decimalData(rec->u.decVal, dec->app_data));
			break;
			case CR_LIST:
				if(h->listData != NULL)
					TRY(h->listData(rec->u.listVal.type, rec->u.listVal.count, dec->app_data));
			break;
			case CR_QNAME:
				if(h->qnameData != NULL)
				{
					QName qname;
					qname.uri = &rec->u.qnameVal.uri;
					qname.localName = &rec->u.qnameVal.ln;
					qname.prefix = rec->hasPrefix ? &rec->u.qnameVal.pfx : NULL;
					TRY(h->qnameData(qname, dec->app_data));
				}
			break;
			default:
				return EXIP_INCONSISTENT_PROC_STATE;
		}
	}

	return EXIP_OK;
}

/* Delivers the recorded events of the block; a handler error stops the replay after that
 * event, so the next parseNext() continues with the following one */
static errorCode replayBlock(CompressionDecoder* dec)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ContentHandler* h = dec->user;

	dec->phase = PHASE_REPLAY;
	while(dec->replayPos < dec->events.count)
	{
		ChEvent* ev = &dec->events.ev[dec->replayPos++];
		QName qname;

		switch(ev->kind)
		{
			case CEV_SE:
			case CEV_AT:
				qname.uri = &ev->a;
				qname.localName = &ev->b;
				qname.prefix = ev->hasPrefix ? &ev->c : NULL;
				if(ev->kind == CEV_SE && h->startElement != NULL)
					TRY(h->startElement(qname, dec->app_data));
				else if(ev->kind == CEV_AT && h->attribute != NULL)
					TRY(h->attribute(qname, dec->app_data));
			break;
			case CEV_EE:
				if(h->endElement != NULL)
					TRY(h->endElement(dec->app_data));
			break;
			case CEV_ED:
				if(h->endDocument != NULL)
					TRY(h->endDocument(dec->app_data));
			break;
			case CEV_NS:
				if(h->namespaceDeclaration != NULL)
					TRY(h->namespaceDeclaration(ev->a, ev->b, ev->isLocal, dec->app_data));
			break;
			case CEV_SC:
				if(h->selfContained != NULL)
					TRY(h->selfContained(dec->app_data));
			break;
			case CEV_PI:
				if(h->processingInstruction != NULL)
					TRY(h->processingInstruction(dec->app_data));
			break;
			case CEV_VALUE:
				TRY(replayValue(dec, &dec->values.val[ev->valueId]));
			break;
			default:
				return EXIP_INCONSISTENT_PROC_STATE;
		}
	}

	return EXIP_OK;
}

errorCode compressionParseNext(EXIStream* strm)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionDecoder* dec = strm->compression;

	if(dec->replayPos >= dec->events.count)
	{
		if(dec->documentEnded)
			return EXIP_PARSING_COMPLETE;

		TRY(resetBlock(dec));
		TRY(decodeStructure(strm, dec));
		TRY(decodeChannels(strm, dec));
#if EXIP_COMPRESSION_TRACE == ON
		dec->blockNumber++;
#endif
	}

	TRY(replayBlock(dec));

	return dec->documentEnded ? EXIP_PARSING_COMPLETE : EXIP_OK;
}

/******* Life cycle *******/

errorCode initCompressionDecoder(EXIStream* strm, ContentHandler* handler, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	CompressionDecoder* dec;

	dec = memManagedAllocate(&strm->memList, sizeof(CompressionDecoder));
	if(dec == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;
	memset(dec, 0, sizeof(CompressionDecoder));
	dec->strm = strm;
	dec->user = handler;
	dec->app_data = app_data;
	dec->currentValue = INDEX_MAX;

	initContentHandler(&dec->recorder);
	dec->recorder.startElement = recStartElement;
	dec->recorder.endElement = recEndElement;
	dec->recorder.attribute = recAttribute;
	dec->recorder.endDocument = recEndDocument;
	dec->recorder.selfContained = recSelfContained;
	dec->recorder.processingInstruction = recProcessingInstruction;
	dec->recorder.namespaceDeclaration = recNamespaceDeclaration;
	dec->recorder.intData = recIntData;
	dec->recorder.booleanData = recBooleanData;
	dec->recorder.stringData = recStringData;
	dec->recorder.floatData = recFloatData;
	dec->recorder.binaryData = recBinaryData;
	dec->recorder.dateTimeData = recDateTimeData;
	dec->recorder.decimalData = recDecimalData;
	dec->recorder.listData = recListData;
	dec->recorder.qnameData = recQnameData;
	dec->recorder.warning = recWarning;
	dec->recorder.error = recError;
	dec->recorder.fatalError = recFatalError;

	TRY(initAllocList(&dec->blockMem));
	// Registered before the arrays, so that a failure below is cleaned up by destroyParser
	strm->compression = dec;
	TRY(createDynArray(&dec->events.dynArray, sizeof(ChEvent), CHANNEL_ARRAY_CHUNK));
	TRY(createDynArray(&dec->records.dynArray, sizeof(ChRecord), CHANNEL_ARRAY_CHUNK));
	TRY(createDynArray(&dec->values.dynArray, sizeof(ChValue), CHANNEL_ARRAY_CHUNK));
	TRY(createDynArray(&dec->channels.dynArray, sizeof(Channel), CHANNEL_ARRAY_CHUNK));

	if(WITH_COMPRESSION(strm->header.opts.enumOpt))
	{
#if defined(EXIP_USE_ZLIB)
		TRY(initInflater(dec, strm));
#else
		DEBUG_MSG(EXIP_LOG_ERROR, DEBUG_CONTENT_IO, ("\n> EXI compression needs exip built with zlib"));
		return EXIP_NOT_IMPLEMENTED_YET;
#endif
	}

	return EXIP_OK;
}

void destroyCompressionDecoder(EXIStream* strm)
{
	CompressionDecoder* dec = strm->compression;

	if(dec == NULL)
		return;

#if defined(EXIP_USE_ZLIB)
	if(dec->inflating)
	{
		inflateEnd(&dec->zstrm);
		// The application's buffer and stream again
		strm->buffer = dec->raw;
	}
#endif
	if(dec->events.ev != NULL)
		destroyDynArray(&dec->events.dynArray);
	if(dec->records.rec != NULL)
		destroyDynArray(&dec->records.dynArray);
	if(dec->values.val != NULL)
		destroyDynArray(&dec->values.dynArray);
	if(dec->channels.ch != NULL)
		destroyDynArray(&dec->channels.dynArray);
	freeAllocList(&dec->blockMem);
	strm->compression = NULL;
}
