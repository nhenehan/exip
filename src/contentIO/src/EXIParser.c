/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file EXIParser.c
 * @brief Implementation of a parser of EXI streams
 *
 * @date Sep 30, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: EXIParser.c 357 2014-12-05 09:54:22Z kjussakov $
 */

#include "EXIParser.h"
#include "procTypes.h"
#include "headerDecode.h"
#include "memManagement.h"
#include "bodyDecode.h"
#include "sTables.h"
#include "grammars.h"
#include "initSchemaInstance.h"

#if defined(EXIP_USE_ZLIB)
#include <string.h>
#include <zlib.h>

typedef struct CompressionInputAdapter
{
	IOStream rawIO;
	unsigned char* rawBuf;
	Index rawBufLen;
	boolean initialized;
	z_stream zstrm;
} CompressionInputAdapter;

static size_t readCompressedEXIChunk(void* buf, size_t size, void* stream)
{
	CompressionInputAdapter* adapter = (CompressionInputAdapter*) stream;
	unsigned char* outBuf = (unsigned char*) buf;
	Index bytesProduced = 0;
	int zret = Z_OK;

	if(adapter == NULL || outBuf == NULL || size == 0)
		return 0;

	adapter->zstrm.next_out = outBuf;
	adapter->zstrm.avail_out = (uInt) size;

	while(adapter->zstrm.avail_out > 0)
	{
		if(adapter->zstrm.avail_in == 0)
		{
			/* Preserve any remaining compressed bytes before reading new input.
			 * This ensures we don't lose unprocessed data when the buffer is refilled.
			 * After previous inflate() calls, next_in may point mid-buffer, and avail_in
			 * (now 0) means all bytes from next_in onward have been consumed. We're safe
			 * to refill the entire buffer. However, between inflate() calls that return
			 * early (e.g., output buffer full), next_in may point to unprocessed data.
			 * Since avail_in==0 here, there's nothing to preserve. We can safely refill. */
			Index bytesRead = adapter->rawIO.readWriteToStream(adapter->rawBuf, adapter->rawBufLen, adapter->rawIO.stream);
			if(bytesRead == 0)
				break;

			adapter->zstrm.next_in = adapter->rawBuf;
			adapter->zstrm.avail_in = (uInt) bytesRead;
		}

		zret = inflate(&adapter->zstrm, Z_NO_FLUSH);
		bytesProduced = (Index) (size - adapter->zstrm.avail_out);

		if(zret == Z_STREAM_END)
		{
			/* EXI compression may concatenate multiple raw DEFLATE blocks.
			 * Preserve any unused input, restart the inflater for the next block. */
			Bytef* pendingNextIn = adapter->zstrm.next_in;
			uInt pendingAvailIn = adapter->zstrm.avail_in;

			if(inflateEnd(&adapter->zstrm) != Z_OK)
			{
				DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> EXI compression stream inflate reset failed"));
				break;
			}

			adapter->zstrm.zalloc = Z_NULL;
			adapter->zstrm.zfree = Z_NULL;
			adapter->zstrm.opaque = Z_NULL;
			/* Use raw DEFLATE format (matching the initial inflateInit2 call above). */
			if(inflateInit2(&adapter->zstrm, -MAX_WBITS) != Z_OK)
			{
				DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> EXI compression stream inflate re-init failed"));
				break;
			}

			adapter->zstrm.next_in = pendingNextIn;
			adapter->zstrm.avail_in = pendingAvailIn;
			continue;
		}

		if(zret == Z_BUF_ERROR)
		{
			if(adapter->zstrm.avail_in == 0)
				continue;
			break;
		}

		if(zret != Z_OK)
		{
			DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> EXI compression stream inflate failed"));
			break;
		}

		if(adapter->zstrm.avail_out == 0)
			break;
	}

	return (size_t) bytesProduced;
}

static errorCode initCompressionInputAdapter(EXIStream* strm)
{
	CompressionInputAdapter* adapter = memManagedAllocate(&strm->memList, sizeof(CompressionInputAdapter));
	Index rawBytes = strm->buffer.bufContent - strm->context.bufferIndx;

	if(adapter == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;

	memset(adapter, 0, sizeof(CompressionInputAdapter));
	adapter->rawBufLen = strm->buffer.bufLen;
	adapter->rawBuf = memManagedAllocate(&strm->memList, adapter->rawBufLen);
	if(adapter->rawBuf == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;

	adapter->rawIO = strm->buffer.ioStrm;
	if(rawBytes > 0)
	{
		memcpy(adapter->rawBuf, strm->buffer.buf + strm->context.bufferIndx, rawBytes);
	}

	adapter->zstrm.zalloc = Z_NULL;
	adapter->zstrm.zfree = Z_NULL;
	adapter->zstrm.opaque = Z_NULL;
	/* EXI compression uses raw DEFLATE format (not zlib-wrapped).
	 * The -MAX_WBITS parameter tells zlib to expect raw DEFLATE without headers.
	 * EXI concatenates multiple DEFLATE blocks, which are restarted in readCompressedEXIChunk. */
	if(inflateInit2(&adapter->zstrm, -MAX_WBITS) != Z_OK)
		return EXIP_UNEXPECTED_ERROR;
	adapter->initialized = TRUE;

	if(rawBytes > 0)
	{
		adapter->zstrm.next_in = adapter->rawBuf;
		adapter->zstrm.avail_in = (uInt) rawBytes;
	}

	strm->buffer.ioStrm.readWriteToStream = readCompressedEXIChunk;
	strm->buffer.ioStrm.stream = adapter;
	strm->context.bufferIndx = 0;
	strm->context.bitPointer = 0;
	strm->buffer.bufContent = 0;

	return EXIP_OK;
}

static void destroyCompressionInputAdapter(EXIStream* strm)
{
	CompressionInputAdapter* adapter;

	if(strm == NULL || strm->buffer.ioStrm.readWriteToStream != readCompressedEXIChunk)
		return;

	adapter = (CompressionInputAdapter*) strm->buffer.ioStrm.stream;
	if(adapter != NULL && adapter->initialized)
		inflateEnd(&adapter->zstrm);

	strm->buffer.ioStrm.readWriteToStream = NULL;
	strm->buffer.ioStrm.stream = NULL;
}
#endif

/**
 * The handler to be used by the applications to parse EXI streams
 */
const EXIParser parse ={initParser,
						parseHeader,
						setSchema,
						parseNext,
						pushEXIData,
						destroyParser,
						getValueExiType};

errorCode initParser(Parser* parser, BinaryBuffer buffer, void* app_data)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	TRY(initAllocList(&parser->strm.memList));

	parser->strm.buffer = buffer;
	parser->strm.context.bitPointer = 0;
	parser->strm.context.bufferIndx = 0;
	parser->strm.context.currAttr.lnId = 0;
	parser->strm.context.currAttr.uriId = 0;
	parser->strm.context.expectATData = FALSE;
	parser->strm.context.isNilType = FALSE;
	parser->strm.context.attrTypeId = INDEX_MAX;
	parser->strm.context.valueExiType = VALUE_TYPE_NONE;
	parser->strm.context.compressionValueHandoffReady = FALSE;
	parser->strm.context.compressionValueHandoffCount = 0;
	parser->strm.gStack = NULL;
	parser->strm.valueTable.value = NULL;
	parser->strm.valueTable.count = 0;
	parser->app_data = app_data;
	parser->strm.schema = NULL;
    makeDefaultOpts(&parser->strm.header.opts);

	initContentHandler(&parser->handler);

#if HASH_TABLE_USE
	parser->strm.valueTable.hashTbl = NULL;
#endif

	return EXIP_OK;
}

errorCode parseHeader(Parser* parser, boolean outOfBandOpts)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;

	TRY(decodeHeader(&parser->strm, outOfBandOpts));

	if(WITH_COMPRESSION(parser->strm.header.opts.enumOpt))
	{
		parser->strm.context.compressionValueHandoffReady = FALSE;
		parser->strm.context.compressionValueHandoffCount = 0;
	#if defined(EXIP_USE_ZLIB)
		TRY(initCompressionInputAdapter(&parser->strm));
	#else
		DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> EXI compression mode decode is not implemented"));
		return EXIP_NOT_IMPLEMENTED_YET;
	#endif

		/* [SLICE 2] Initialize compression block tracking for per-block value partition resets. */
		parser->strm.context.compressionBlockValueCount = 0;
		parser->strm.context.compressionBlockBoundaryDetected = FALSE;
	}

	if(parser->strm.header.opts.valuePartitionCapacity > 0)
	{
		TRY(createValueTable(&parser->strm.valueTable));
	}

	// The parsing of the header is successful
	// TODO: Consider removing the startDocument all together instead of invoking it always here?
	if(parser->handler.startDocument != NULL)
	{
		TRY(parser->handler.startDocument(parser->app_data));
	}

	return EXIP_OK;
}

errorCode setSchema(Parser* parser, EXIPSchema* schema)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;

	if(parser->strm.header.opts.schemaIDMode == SCHEMA_ID_NIL)
	{
		// When the "schemaId" element in the EXI options document contains the xsi:nil attribute
		// with its value set to true, no schema information is used for processing the EXI body
		// (i.e. a schema-less EXI stream)
		parser->strm.schema = NULL;
#if EXI_PROFILE_DEFAULT
		DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> EXI Profile mode require schema mode processing"));
		return EXIP_INVALID_EXI_INPUT;
#endif
#if DEBUG_CONTENT_IO == ON && EXIP_DEBUG_LEVEL <= WARNING
		if(schema != NULL)
			DEBUG_MSG(WARNING, DEBUG_CONTENT_IO, ("\n> Ignored out-of-band schema information. Schema-less mode required"));
#endif
	}
	else if(parser->strm.header.opts.schemaIDMode == SCHEMA_ID_EMPTY)
	{
		// When the value of the "schemaId" element is empty, no user defined schema information
		// is used for processing the EXI body; however, the built-in XML schema types are available for use in the EXI body
#if DEBUG_CONTENT_IO == ON && EXIP_DEBUG_LEVEL <= WARNING
		if(schema != NULL)
			DEBUG_MSG(WARNING, DEBUG_CONTENT_IO, ("\n> Ignored out-of-band schema information. Schema mode built-in types required"));
#endif
		parser->strm.schema = memManagedAllocate(&parser->strm.memList, sizeof(EXIPSchema));
		if(parser->strm.schema == NULL)
			return EXIP_MEMORY_ALLOCATION_ERROR;

		TRY(initSchema(parser->strm.schema, INIT_SCHEMA_BUILD_IN_TYPES));

		if(WITH_FRAGMENT(parser->strm.header.opts.enumOpt))
		{
			TRY(createFragmentGrammar(parser->strm.schema, NULL, 0));
		}
		else
		{
			TRY(createDocGrammar(parser->strm.schema, NULL, 0));
		}
	}
	else if(schema != NULL)
	{
		/* Schema enabled mode*/
		if(WITH_FRAGMENT(parser->strm.header.opts.enumOpt))
		{
			/* Fragment document grammar */
			// TODO: create a Schema-informed Fragment Grammar from the EXIP schema object
			return EXIP_NOT_IMPLEMENTED_YET;
		}
		else
		{
			parser->strm.schema = schema;
		}
	}

	if(parser->strm.schema == NULL)
	{
		// Schema-less mode
		if(parser->strm.header.opts.schemaIDMode == SCHEMA_ID_SET)
		{
			DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> Schema mode required, but NULL schema set"));
			return EXIP_INVALID_EXIP_CONFIGURATION;
		}

#if EXI_PROFILE_DEFAULT
		DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> EXI Profile mode require schema mode processing"));
		return EXIP_INVALID_EXI_INPUT;
#endif

		parser->strm.schema = memManagedAllocate(&parser->strm.memList, sizeof(EXIPSchema));
		if(parser->strm.schema == NULL)
			return EXIP_MEMORY_ALLOCATION_ERROR;

		TRY(initSchema(parser->strm.schema, INIT_SCHEMA_SCHEMA_LESS_MODE));

		if(WITH_FRAGMENT(parser->strm.header.opts.enumOpt))
		{
			TRY(createFragmentGrammar(parser->strm.schema, NULL, 0));
		}
		else
		{
			TRY(createDocGrammar(parser->strm.schema, NULL, 0));
		}
	}

	{
		QNameID emptyQNameID = {URI_MAX, LN_MAX};
		TRY(pushGrammar(&parser->strm.gStack, emptyQNameID, &parser->strm.schema->docGrammar));
	}

	return EXIP_OK;
}

errorCode parseNext(Parser* parser)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	SmallIndex tmpNonTermID = GR_VOID_NON_TERMINAL;
	StreamContext savedContext = parser->strm.context;

	tmp_err_code = processNextProduction(&parser->strm, &tmpNonTermID, &parser->handler, parser->app_data);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
		parser->strm.context = savedContext;

	if(tmp_err_code != EXIP_OK)
	{
		DEBUG_MSG(ERROR, EXIP_DEBUG, ("\n>Error %s:%d at %s, line %d", GET_ERR_STRING(tmp_err_code), tmp_err_code, __FILE__, __LINE__));
		return tmp_err_code;
	}

	if(tmpNonTermID == GR_VOID_NON_TERMINAL)
	{
		popGrammar(&(parser->strm.gStack));
		if(parser->strm.gStack == NULL) // There is no more grammars in the stack
		{
			return EXIP_PARSING_COMPLETE; // The stream is parsed
		}
	}
	else
	{
		parser->strm.gStack->currNonTermID = tmpNonTermID;
	}

	return EXIP_OK;
}

errorCode pushEXIData(char* inBuf, unsigned int bufSize, unsigned int* bytesRead, Parser* parser)
{
	Index bytesCopied = parser->strm.buffer.bufContent - parser->strm.context.bufferIndx;

	*bytesRead = parser->strm.buffer.bufLen - bytesCopied;
	if(*bytesRead > bufSize)
		*bytesRead = bufSize;

	/* Checks for possible overlaps when copying the left Over Bits,
	 * normally should not happen when the size of strm->buffer is set
	 * reasonably and not too small */
	if(2*bytesCopied > parser->strm.buffer.bufLen)
	{
		DEBUG_MSG(ERROR, DEBUG_CONTENT_IO, ("\n> The size of strm->buffer is too small! Set to at least: %d", 2*((int) bytesCopied)));
		return EXIP_INCONSISTENT_PROC_STATE;
	}

	memcpy(parser->strm.buffer.buf, parser->strm.buffer.buf + parser->strm.context.bufferIndx, bytesCopied);
	memcpy(parser->strm.buffer.buf + bytesCopied, inBuf, *bytesRead);

	parser->strm.context.bufferIndx = 0;
	parser->strm.buffer.bufContent = bytesCopied + *bytesRead;

	return EXIP_OK;
}

void destroyParser(Parser* parser)
{
	#if defined(EXIP_USE_ZLIB)
	destroyCompressionInputAdapter(&parser->strm);
	#endif

	while(parser->strm.gStack != NULL)
	{
		popGrammar(&parser->strm.gStack);
	}

	freeAllMem(&parser->strm);
}

errorCode getValueExiType(Parser* parser, EXIType* exiType)
{
	if(parser == NULL || exiType == NULL)
		return EXIP_NULL_POINTER_REF;
	*exiType = parser->strm.context.valueExiType;
	return EXIP_OK;
}
