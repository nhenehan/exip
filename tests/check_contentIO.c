/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file check_contentIO.c
 * @brief Tests the Content IO module
 *
 * @date Sep 28, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: check_contentIO.c 360 2015-04-19 19:44:06Z kjussakov $
 */

#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "headerDecode.h"
#include "bodyDecode.h"
#include "memManagement.h"
#include "EXISerializer.h"

/* BEGIN: header tests */

START_TEST (test_decodeHeader)
{
	EXIStream testStream;  // Default options, no EXI cookie
	char buf[3];
	errorCode err = EXIP_UNEXPECTED_ERROR;
	EXIStream testStream2;  // Default options, with EXI cookie
	char buf2[7];

	testStream.context.bitPointer = 0;
	buf[0] = (char) 0x80;
	buf[1] = (char) 0x60;
	buf[2] = (char) 0x7C;
	testStream.buffer.buf = buf;
	testStream.context.bufferIndx = 0;
	testStream.buffer.bufLen = 3;
	testStream.buffer.bufContent = 3;
	testStream.buffer.ioStrm.readWriteToStream = NULL;
	testStream.buffer.ioStrm.stream = NULL;
	makeDefaultOpts(&testStream.header.opts);

	err = decodeHeader(&testStream, TRUE);
	fail_unless (err == EXIP_OK, "decodeHeader returns error code %d", err);
	fail_unless (testStream.header.has_cookie == 0,
				"decodeHeader founds EXI cookie");
	fail_unless (testStream.header.has_options == 0,
					"decodeHeader founds options");
	fail_unless (testStream.header.is_preview_version == 0,
					"decodeHeader founds preview version");
	fail_unless (testStream.header.version_number == 1,
					"decodeHeader does not recognize version 1 of the stream");

	testStream2.context.bitPointer = 0;

	buf2[0] = (char) 36;
	buf2[1] = (char) 69;
	buf2[2] = (char) 88;
	buf2[3] = (char) 73;
	buf2[4] = (char) 0x80;
	buf2[5] = (char) 0x60;
	buf2[6] = (char) 0x7C;

	testStream2.buffer.buf = buf2;
	testStream2.context.bufferIndx = 0;
	testStream2.buffer.bufLen = 7;
	testStream2.buffer.bufContent = 7;
	testStream2.buffer.ioStrm.readWriteToStream = NULL;
	testStream2.buffer.ioStrm.stream = NULL;
	makeDefaultOpts(&testStream2.header.opts);

	err = decodeHeader(&testStream2, TRUE);
	fail_unless (err == EXIP_OK, "decodeHeader returns error code %d", err);
	fail_unless (testStream2.header.has_cookie == 1,
				"decodeHeader does not found EXI cookie");
	fail_unless (testStream2.header.has_options == 0,
					"decodeHeader founds options");
	fail_unless (testStream2.header.is_preview_version == 0,
					"decodeHeader founds preview version");
	fail_unless (testStream2.header.version_number == 1,
					"decodeHeader does not recognize version 1 of the stream");
}
END_TEST

/* END: header tests */

/* Captures what closeEXIStream flushes. */
struct flushSink
{
	char data[16];
	size_t len;
};

static size_t flushSinkWrite(void* buf, size_t size, void* stream)
{
	struct flushSink* sink = (struct flushSink*) stream;
	memcpy(sink->data + sink->len, buf, size);
	sink->len += size;
	return size;
}

static errorCode closeWith(char* buf, Index bufferIndx, unsigned char bitPointer, struct flushSink* sink)
{
	EXIStream strm;

	memset(&strm, 0, sizeof strm);
	makeDefaultOpts(&strm.header.opts);
	strm.buffer.buf = buf;
	strm.buffer.bufLen = 8;
	strm.buffer.ioStrm.readWriteToStream = flushSinkWrite;
	strm.buffer.ioStrm.stream = sink;
	strm.context.bufferIndx = bufferIndx;
	strm.context.bitPointer = bitPointer;
	initAllocList(&strm.memList);
	sink->len = 0;
	return closeEXIStream(&strm);
}

/* Only bytes holding stream content are flushed, and the padding of a
 * partial last byte is zero (the buffer here starts full of stale 0x7B bytes). */
START_TEST (test_closeEXIStream_flushesContentOnly)
{
	char buf[8];
	struct flushSink sink;
	errorCode err;

	// Content ends exactly on a byte boundary: 2 bytes, not 3
	memset(buf, 0x7B, sizeof buf);
	err = closeWith(buf, 2, 0, &sink);
	fail_unless (err == EXIP_OK, "closeEXIStream returns error code %d", err);
	fail_unless (sink.len == 2, "flushed %u bytes for 2 bytes of content", (unsigned int) sink.len);

	// 3 bits used in the third byte: 3 bytes, low 5 bits of the last byte zeroed
	memset(buf, 0x7B, sizeof buf);
	buf[2] = (char) 0xFF;
	err = closeWith(buf, 2, 3, &sink);
	fail_unless (err == EXIP_OK, "closeEXIStream returns error code %d", err);
	fail_unless (sink.len == 3, "flushed %u bytes for 2 bytes + 3 bits", (unsigned int) sink.len);
	fail_unless ((unsigned char) sink.data[2] == 0xE0, "last byte 0x%02X, expected 0xE0", (unsigned char) sink.data[2]);

	// Nothing written: nothing flushed
	err = closeWith(buf, 0, 0, &sink);
	fail_unless (err == EXIP_OK && sink.len == 0, "flushed %u bytes for an empty stream", (unsigned int) sink.len);
}
END_TEST

Suite * contentio_suite (void)
{
  Suite *s = suite_create ("ContentIO");

  /* Header test case */
  TCase *tc_header = tcase_create ("EXI Header");
  tcase_add_test (tc_header, test_decodeHeader);
  suite_add_tcase (s, tc_header);

  TCase *tc_close = tcase_create ("EXI stream close");
  tcase_add_test (tc_close, test_closeEXIStream_flushesContentOnly);
  suite_add_tcase (s, tc_close);
  return s;
}

int main (void)
{
	int number_failed;
	Suite *s = contentio_suite();
	SRunner *sr = srunner_create (s);
	srunner_set_fork_status(sr, CK_NOFORK);
#ifdef _MSC_VER
	srunner_set_fork_status(sr, CK_NOFORK);
#endif
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
