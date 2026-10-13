/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file compressionEncode.h
 * @brief Encoding of EXI bodies in channels: compression and pre-compression
 *
 * The encoder side of compressionDecode.h. The events of a block are written as they come
 * (the structure channel, kept in memory); the AT and CH values are recorded in their value
 * channels and written when the block closes, after the value that brings it to blockSize
 * and at the end of the document (EXI 1.0, section 9; EXIficient 1.0.7
 * EXIBodyEncoderReordered).
 */

#ifndef COMPRESSIONENCODE_H_
#define COMPRESSIONENCODE_H_

#include "procTypes.h"
#include "bodyEncode.h"

/**
 * @brief Starts channel encoding of the body, after the header has been written
 * The header stays in the application's buffer; the body follows it block by block.
 * @param[in, out] strm EXI stream positioned after the header (byte boundary)
 * @return Error handling code
 */
errorCode initCompressionEncoder(EXIStream* strm);

/**
 * @brief Called by encodeValueContent() before it writes a value
 * Records an AT or CH value in its value channel, except the structure values (xsi:nil
 * under a schema-informed grammar; xsi:type does not come here). Checks the value first,
 * so that an invalid value is reported to the call that gave it.
 * @param[in, out] strm EXI stream
 * @param[in] vc the value
 * @param[out] recorded TRUE when the value was recorded and must not be written now
 * @return Error handling code
 */
errorCode compressionRecordValue(EXIStream* strm, const ValueContent* vc, exip_bool* recorded);

/**
 * @brief Closes the last block after the ED event and gives the stream its application
 * buffer back, with the encoded body in it (or written to its stream)
 * @param[in, out] strm EXI stream
 * @return Error handling code
 */
errorCode compressionEndDocument(EXIStream* strm);

/**
 * @brief Releases the channel encoder of a stream, if any, and gives the stream its
 * application buffer back
 * @param[in, out] strm EXI stream
 */
void destroyCompressionEncoder(EXIStream* strm);

#endif /* COMPRESSIONENCODE_H_ */
