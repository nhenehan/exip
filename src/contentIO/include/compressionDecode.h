/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file compressionDecode.h
 * @brief Decoding of EXI streams with channels: compression and pre-compression
 *
 * With compression or pre-compression alignment, an EXI body is a sequence of blocks; each
 * block holds a structure channel (the events) followed by value channels, one per QName,
 * with the attribute and character values (EXI 1.0, section 9). The parser decodes a block
 * in three passes: the structure, recording the events and deferring the values; the value
 * channels, in stream order; and the replay of the events, with their values, to the
 * application's handler.
 */

#ifndef COMPRESSIONDECODE_H_
#define COMPRESSIONDECODE_H_

#include "procTypes.h"
#include "contentHandler.h"

/** TRUE when the EXI body is organised in channels (compression or pre-compression) */
#define WITH_CHANNELS(enumOpt) (WITH_COMPRESSION(enumOpt) || GET_ALIGNMENT(enumOpt) == PRE_COMPRESSION)

/**
 * @brief Prepares channel decoding after the header has been decoded
 * With compression the body input is inflated from here on.
 * @param[in, out] strm EXI stream positioned after the header
 * @param[in] handler the application's handler (read when events are replayed)
 * @param[in] app_data the application's data
 * @return Error handling code
 */
errorCode initCompressionDecoder(EXIStream* strm, ContentHandler* handler, void* app_data);

/**
 * @brief Decodes the next block of the body and delivers its events to the application
 * @param[in, out] strm EXI stream with a channel decoder
 * @return EXIP_OK, EXIP_PARSING_COMPLETE after the last block, or an error code
 */
errorCode compressionParseNext(EXIStream* strm);

/**
 * @brief Called by decodeValueItem() before it decodes a value
 * During the structure pass, the value of an AT or CH event is not in the structure
 * channel: it is recorded for its value channel instead (except xsi:type, and xsi:nil
 * under a schema-informed grammar, which are part of the structure).
 * @param[in, out] strm EXI stream
 * @param[in] typeId the type of the value
 * @param[in] qnameID the channel: the attribute, or the element of a CH value
 * @param[out] deferred TRUE when the value was recorded and must not be decoded now
 * @return Error handling code
 */
errorCode compressionDeferValue(EXIStream* strm, Index typeId, QNameID qnameID, exip_bool* deferred);

/**
 * @brief Releases the channel decoder of a stream, if any
 * @param[in, out] strm EXI stream
 */
void destroyCompressionDecoder(EXIStream* strm);

#endif /* COMPRESSIONDECODE_H_ */
