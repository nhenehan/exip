/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file check_compression.c
 * @brief Tests the decoding of EXI bodies in channels: compression and pre-compression
 *
 *
 * The fixtures in test-set/compression are encoded by EXIficient (gen.sh): each document
 * bit-packed and in channels. Decoding the channel encodings, from one buffer and from a
 * stream read in small pieces, must give the same events as the bit-packed encoding.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "procTypes.h"
#include "EXIParser.h"
#include "EXISerializer.h"
#include "stringManipulate.h"
#include "grammarGenerator.h"

#define PATH_LEN 512
#define STREAM_CHUNK 64

/* Compression needs exip built with zlib (EXIP_USE_ZLIB, set for this test by CMake);
 * without it, only pre-compression is tested */
#if defined(EXIP_USE_ZLIB)
#  define HAVE_ZLIB TRUE
#else
#  define HAVE_ZLIB FALSE
#endif

static char *dataDir;

/* The events of a decoded document, one per line */
typedef struct
{
	char* text;
	size_t len;
	size_t cap;
} Dump;

static void dumpf(Dump* d, const char* fmt, ...)
{
	char line[512];
	va_list args;
	int n;

	va_start(args, fmt);
	n = vsnprintf(line, sizeof line, fmt, args);
	va_end(args);
	if(n < 0)
		return;
	if((size_t) n >= sizeof line)
		n = sizeof line - 1;
	if(d->len + (size_t) n + 1 > d->cap)
	{
		d->cap = (d->cap + (size_t) n + 1) * 2;
		d->text = realloc(d->text, d->cap);
		ck_assert(d->text != NULL);
	}
	memcpy(d->text + d->len, line, (size_t) n + 1);
	d->len += (size_t) n;
}

static void dumpString(Dump* d, const char* tag, const String* s)
{
	dumpf(d, "%s %.*s\n", tag, s == NULL ? 0 : (int) s->length, s == NULL || s->str == NULL ? "" : s->str);
}

static void dumpQName(Dump* d, const char* tag, const QName* q)
{
	dumpf(d, "%s {%.*s}%.*s\n", tag, (int) q->uri->length, q->uri->str == NULL ? "" : q->uri->str,
			(int) q->localName->length, q->localName->str == NULL ? "" : q->localName->str);
}

static errorCode onStartElement(QName qname, void* app) { dumpQName(app, "SE", &qname); return EXIP_OK; }
static errorCode onEndElement(void* app) { dumpf(app, "EE\n"); return EXIP_OK; }
static errorCode onAttribute(QName qname, void* app) { dumpQName(app, "AT", &qname); return EXIP_OK; }
static errorCode onEndDocument(void* app) { dumpf(app, "ED\n"); return EXIP_OK; }
static errorCode onString(const String s, void* app) { dumpString(app, "CH", &s); return EXIP_OK; }
static errorCode onInt(Integer i, void* app) { dumpf(app, "INT %lld\n", (long long) i); return EXIP_OK; }
static errorCode onBoolean(exip_bool b, void* app) { dumpf(app, "BOOL %d\n", (int) b); return EXIP_OK; }
static errorCode onFloat(Float f, void* app)
{
	dumpf(app, "FLOAT %lld E %d\n", (long long) f.mantissa, (int) f.exponent);
	return EXIP_OK;
}
static errorCode onDecimal(Decimal f, void* app)
{
	dumpf(app, "DEC %lld E %d\n", (long long) f.mantissa, (int) f.exponent);
	return EXIP_OK;
}
static errorCode onDateTime(EXIPDateTime dt, void* app)
{
	dumpf(app, "DT %d-%d-%d %d:%d:%d mask %u tz %d\n", dt.dateTime.tm_year, dt.dateTime.tm_mon,
			dt.dateTime.tm_mday, dt.dateTime.tm_hour, dt.dateTime.tm_min, dt.dateTime.tm_sec,
			(unsigned int) dt.presenceMask, (int) dt.TimeZone);
	return EXIP_OK;
}
static errorCode onBinary(const char* data, Index n, void* app)
{
	Index i;
	dumpf(app, "BIN %u:", (unsigned int) n);
	for(i = 0; i < n; i++)
		dumpf(app, "%02x", (unsigned char) data[i]);
	dumpf(app, "\n");
	return EXIP_OK;
}
static errorCode onList(EXITypeClass t, unsigned int count, void* app)
{
	dumpf(app, "LIST %d %u\n", (int) t, count);
	return EXIP_OK;
}
static errorCode onQName(const QName q, void* app) { dumpQName(app, "QNAME", &q); return EXIP_OK; }
static errorCode onNamespace(const String ns, const String pfx, exip_bool local, void* app)
{
	dumpf(app, "NS %.*s %.*s %d\n", (int) ns.length, ns.str == NULL ? "" : ns.str, (int) pfx.length,
			pfx.str == NULL ? "" : pfx.str, (int) local);
	return EXIP_OK;
}

static void setHandlers(ContentHandler* h)
{
	h->startElement = onStartElement;
	h->endElement = onEndElement;
	h->attribute = onAttribute;
	h->endDocument = onEndDocument;
	h->stringData = onString;
	h->intData = onInt;
	h->booleanData = onBoolean;
	h->floatData = onFloat;
	h->decimalData = onDecimal;
	h->dateTimeData = onDateTime;
	h->binaryData = onBinary;
	h->listData = onList;
	h->qnameData = onQName;
	h->namespaceDeclaration = onNamespace;
}

static size_t readFileChunk(void* buf, size_t size, void* stream)
{
	return fread(buf, 1, size, (FILE*) stream);
}

static void dataPath(char* path, const char* name)
{
	ck_assert(snprintf(path, PATH_LEN, "%s/compression/%s", dataDir, name) < PATH_LEN);
}

/* Reads a fixture into a malloc'ed buffer */
static char* readFixture(const char* name, size_t* size)
{
	char path[PATH_LEN];
	FILE* f;
	long len;
	char* data;

	dataPath(path, name);
	f = fopen(path, "rb");
	ck_assert_msg(f != NULL, "cannot open %s", path);
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	data = malloc((size_t) len + 1);
	ck_assert(data != NULL);
	ck_assert(fread(data, 1, (size_t) len, f) == (size_t) len);
	fclose(f);
	*size = (size_t) len;
	return data;
}

static void loadSchema(const char* name, EXIPSchema* schema)
{
	BinaryBuffer buffer;
	size_t size;

	buffer.buf = readFixture(name, &size);
	buffer.bufLen = size + 1;
	buffer.bufContent = size;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;
	ck_assert(generateSchemaInformedGrammars(&buffer, 1, SCHEMA_FORMAT_XSD_EXI, NULL, schema, NULL) == EXIP_OK);
	free(buffer.buf);
}

/* Options given out of band (oob), or NULL for the options in the header */
typedef struct
{
	unsigned char enumOpt;
	uint32_t blockSize;
} Oob;

/* Decodes a fixture from one buffer, or (stream) through a STREAM_CHUNK byte buffer filled
 * from the file; returns the error code of the decoding, the events in dump */
static errorCode decodeFixture(const char* name, EXIPSchema* schema, const Oob* oob, exip_bool stream, Dump* dump)
{
	Parser parser;
	BinaryBuffer buffer;
	errorCode err;
	char path[PATH_LEN];
	char chunk[STREAM_CHUNK];
	FILE* f = NULL;
	char* data = NULL;
	size_t size;

	memset(dump, 0, sizeof(Dump));
	dumpf(dump, "%s", "");
	if(stream)
	{
		dataPath(path, name);
		f = fopen(path, "rb");
		ck_assert_msg(f != NULL, "cannot open %s", path);
		buffer.buf = chunk;
		buffer.bufLen = STREAM_CHUNK;
		buffer.bufContent = 0;
		buffer.ioStrm.readWriteToStream = readFileChunk;
		buffer.ioStrm.stream = f;
	}
	else
	{
		data = readFixture(name, &size);
		buffer.buf = data;
		buffer.bufLen = size;
		buffer.bufContent = size;
		buffer.ioStrm.readWriteToStream = NULL;
		buffer.ioStrm.stream = NULL;
	}

	err = parse.initParser(&parser, buffer, dump);
	ck_assert(err == EXIP_OK);
	setHandlers(&parser.handler);
	if(oob != NULL)
	{
		parser.strm.header.opts.enumOpt = oob->enumOpt;
		if(oob->blockSize > 0)
			parser.strm.header.opts.blockSize = oob->blockSize;
	}
	err = parse.parseHeader(&parser, oob != NULL);
	if(err == EXIP_OK)
		err = parse.setSchema(&parser, schema);
	while(err == EXIP_OK)
		err = parse.parseNext(&parser);
	parse.destroyParser(&parser);

	if(f != NULL)
		fclose(f);
	free(data);
	return err;
}

static void expectSameEvents(const char* reference, const char* channels, EXIPSchema* schema, const Oob* refOob, const Oob* oob)
{
	Dump ref, out;
	exip_bool stream;

	ck_assert_msg(decodeFixture(reference, schema, refOob, FALSE, &ref) == EXIP_PARSING_COMPLETE, "decoding %s", reference);
	ck_assert_msg(ref.len > 0, "no events in %s", reference);
	for(stream = FALSE; stream <= TRUE; stream++)
	{
		errorCode err = decodeFixture(channels, schema, oob, stream, &out);
		ck_assert_msg(err == EXIP_PARSING_COMPLETE, "decoding %s (%s): error %d", channels, stream ? "stream" : "buffer", (int) err);
		ck_assert_msg(out.len == ref.len && memcmp(out.text, ref.text, ref.len) == 0,
				"%s (%s): events differ from %s", channels, stream ? "stream" : "buffer", reference);
		free(out.text);
	}
	free(ref.text);
}

/* Schema-less, options in the header: one block with channels over 100 values (separate
 * DEFLATE streams), blocks of 64 values, blocks of one value, pre-compression */
START_TEST (test_schemaless_blocks)
{
	if(HAVE_ZLIB)
	{
		expectSameEvents("catalog.bit-packed.exi", "catalog.compression.exi", NULL, NULL, NULL);
		expectSameEvents("catalog.bit-packed.exi", "catalog.compression.64.exi", NULL, NULL, NULL);
		expectSameEvents("catalog.bit-packed.exi", "catalog.compression.1.exi", NULL, NULL, NULL);
	}
	expectSameEvents("catalog.bit-packed.exi", "catalog.pre-compression.exi", NULL, NULL, NULL);
	expectSameEvents("catalog.bit-packed.exi", "catalog.pre-compression.64.exi", NULL, NULL, NULL);
	expectSameEvents("catalog.bit-packed.exi", "catalog.pre-compression.1.exi", NULL, NULL, NULL);
}
END_TEST

/* Schema-informed, strict, typed values (decimal, dateTime, list), xsi:nil */
START_TEST (test_schema_informed)
{
	const char* docs[] = {"telemetry-complex", "readings", "order-complex"};
	unsigned int i;

	for(i = 0; i < sizeof docs / sizeof docs[0]; i++)
	{
		EXIPSchema schema;
		char xsd[PATH_LEN], ref[PATH_LEN], comp[PATH_LEN], comp3[PATH_LEN];
		Oob bitPacked = {0, 0};
		Oob compression = {0, 0};
		Oob compression3 = {0, 3};

		SET_STRICT(bitPacked.enumOpt);
		SET_STRICT(compression.enumOpt);
		SET_COMPRESSION(compression.enumOpt);
		compression3.enumOpt = compression.enumOpt;
		snprintf(xsd, PATH_LEN, "%s-xsd.exi", docs[i]);
		snprintf(ref, PATH_LEN, "%s.bit-packed.exi", docs[i]);
		snprintf(comp, PATH_LEN, "%s.compression.exi", docs[i]);
		snprintf(comp3, PATH_LEN, "%s.compression.3.exi", docs[i]);
		loadSchema(xsd, &schema);
		if(HAVE_ZLIB)
		{
			expectSameEvents(ref, comp, &schema, &bitPacked, &compression);
			expectSameEvents(ref, comp3, &schema, &bitPacked, &compression3);
		}
		{
			Oob pre = {0, 0};
			Oob pre3 = {0, 3};

			SET_STRICT(pre.enumOpt);
			SET_ALIGNMENT(pre.enumOpt, PRE_COMPRESSION);
			pre3.enumOpt = pre.enumOpt;
			snprintf(comp, PATH_LEN, "%s.pre-compression.exi", docs[i]);
			snprintf(comp3, PATH_LEN, "%s.pre-compression.3.exi", docs[i]);
			expectSameEvents(ref, comp, &schema, &bitPacked, &pre);
			expectSameEvents(ref, comp3, &schema, &bitPacked, &pre3);
		}
		destroySchema(&schema);
	}
}
END_TEST

/* pushEXIData() cannot feed a body in channels */
START_TEST (test_push_rejected)
{
	Parser parser;
	BinaryBuffer buffer;
	size_t size;
	char more[4] = {0, 0, 0, 0};
	unsigned int bytesRead = 0;
	Dump dump;

	memset(&dump, 0, sizeof(Dump));
	buffer.buf = readFixture("catalog.pre-compression.64.exi", &size);
	buffer.bufLen = size;
	buffer.bufContent = size;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;
	ck_assert(parse.initParser(&parser, buffer, &dump) == EXIP_OK);
	ck_assert(parse.parseHeader(&parser, FALSE) == EXIP_OK);
	ck_assert(parse.pushEXIData(more, sizeof more, &bytesRead, &parser) == EXIP_NOT_IMPLEMENTED_YET);
	parse.destroyParser(&parser);
	free(buffer.buf);
	free(dump.text);
}
END_TEST

/* A truncated compressed body ends in an error, not in a crash or a complete document */
START_TEST (test_truncated)
{
	Parser parser;
	BinaryBuffer buffer;
	size_t size;
	errorCode err;
	Dump dump;

	if(!HAVE_ZLIB)
		return;
	memset(&dump, 0, sizeof(Dump));
	buffer.buf = readFixture("catalog.compression.exi", &size);
	buffer.bufLen = size / 2;
	buffer.bufContent = size / 2;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;
	ck_assert(parse.initParser(&parser, buffer, &dump) == EXIP_OK);
	setHandlers(&parser.handler);
	err = parse.parseHeader(&parser, FALSE);
	if(err == EXIP_OK)
		err = parse.setSchema(&parser, NULL);
	while(err == EXIP_OK)
		err = parse.parseNext(&parser);
	ck_assert_msg(err != EXIP_PARSING_COMPLETE, "a truncated stream decoded completely");
	parse.destroyParser(&parser);
	free(buffer.buf);
	free(dump.text);
}
END_TEST

/******* Encoding: a decoded document re-encoded through the serializer *******/

/* Encoded bytes, through the serializer's output stream */
typedef struct
{
	char* data;
	size_t len;
	size_t cap;
} Bytes;

static size_t writeBytes(void* buf, size_t size, void* stream)
{
	Bytes* b = (Bytes*) stream;
	if(b->len + size > b->cap)
	{
		b->cap = (b->len + size) * 2;
		b->data = realloc(b->data, b->cap);
		ck_assert(b->data != NULL);
	}
	memcpy(b->data + b->len, buf, size);
	b->len += size;
	return size;
}

typedef struct
{
	EXIStream out;
	EXITypeClass valueType;
} Transcoder;

static errorCode tcStartElement(QName q, void* app) { Transcoder* t = app; return serialize.startElement(&t->out, q, &t->valueType); }
static errorCode tcEndElement(void* app) { Transcoder* t = app; return serialize.endElement(&t->out); }
static errorCode tcAttribute(QName q, void* app) { Transcoder* t = app; return serialize.attribute(&t->out, q, TRUE, &t->valueType); }
static errorCode tcEndDocument(void* app) { Transcoder* t = app; return serialize.endDocument(&t->out); }
static errorCode tcString(const String v, void* app) { Transcoder* t = app; return serialize.stringData(&t->out, v); }
static errorCode tcInt(Integer v, void* app) { Transcoder* t = app; return serialize.intData(&t->out, v); }
static errorCode tcBoolean(exip_bool v, void* app) { Transcoder* t = app; return serialize.booleanData(&t->out, v); }
static errorCode tcFloat(Float v, void* app) { Transcoder* t = app; return serialize.floatData(&t->out, v); }
static errorCode tcDecimal(Decimal v, void* app) { Transcoder* t = app; return serialize.decimalData(&t->out, v); }
static errorCode tcDateTime(EXIPDateTime v, void* app) { Transcoder* t = app; return serialize.dateTimeData(&t->out, v); }
static errorCode tcBinary(const char* v, Index n, void* app) { Transcoder* t = app; return serialize.binaryData(&t->out, v, n); }
static errorCode tcList(EXITypeClass c, unsigned int n, void* app) { Transcoder* t = app; (void) c; return serialize.listData(&t->out, n); }
static errorCode tcQName(const QName q, void* app) { Transcoder* t = app; return serialize.qnameData(&t->out, q); }
static errorCode tcNamespace(const String ns, const String pfx, exip_bool local, void* app)
{
	Transcoder* t = app;
	return serialize.namespaceDeclaration(&t->out, ns, pfx, local);
}

/* Decodes a fixture (header options, or oob) and encodes its events with the options of
 * outOpts (in the header when inHeader) into out: through a stream, or (stream FALSE) into
 * one buffer of outBufLen bytes; returns the error of the encoding. The decoder and the
 * encoder need a schema object each: a stream keeps its local value tables in the schema's
 * string tables, so two streams cannot use one schema at the same time */
static errorCode transcode(const char* source, EXIPSchema* schema, EXIPSchema* outSchema, const Oob* srcOob,
		const EXIOptions* outOpts, exip_bool inHeader, exip_bool stream, size_t outBufLen, Bytes* out)
{
	Parser parser;
	BinaryBuffer in, outBuf;
	Transcoder t;
	char* data;
	char* fixed = NULL;
	char chunk[STREAM_CHUNK];
	size_t size;
	errorCode err;

	memset(out, 0, sizeof(Bytes));
	data = readFixture(source, &size);
	in.buf = data;
	in.bufLen = size;
	in.bufContent = size;
	in.ioStrm.readWriteToStream = NULL;
	in.ioStrm.stream = NULL;

	if(stream)
	{
		outBuf.buf = chunk;
		outBuf.bufLen = STREAM_CHUNK;
		outBuf.ioStrm.readWriteToStream = writeBytes;
		outBuf.ioStrm.stream = out;
	}
	else
	{
		fixed = malloc(outBufLen);
		ck_assert(fixed != NULL);
		outBuf.buf = fixed;
		outBuf.bufLen = outBufLen;
		outBuf.ioStrm.readWriteToStream = NULL;
		outBuf.ioStrm.stream = NULL;
	}
	outBuf.bufContent = 0;

	serialize.initHeader(&t.out);
	t.out.header.has_options = inHeader;
	t.out.header.opts = *outOpts;
	err = serialize.initStream(&t.out, outBuf, outSchema);
	ck_assert(err == EXIP_OK);
	err = serialize.exiHeader(&t.out);
	if(err == EXIP_OK)
		err = serialize.startDocument(&t.out);

	ck_assert(parse.initParser(&parser, in, &t) == EXIP_OK);
	parser.handler.startElement = tcStartElement;
	parser.handler.endElement = tcEndElement;
	parser.handler.attribute = tcAttribute;
	parser.handler.endDocument = tcEndDocument;
	parser.handler.stringData = tcString;
	parser.handler.intData = tcInt;
	parser.handler.booleanData = tcBoolean;
	parser.handler.floatData = tcFloat;
	parser.handler.decimalData = tcDecimal;
	parser.handler.dateTimeData = tcDateTime;
	parser.handler.binaryData = tcBinary;
	parser.handler.listData = tcList;
	parser.handler.qnameData = tcQName;
	parser.handler.namespaceDeclaration = tcNamespace;
	if(srcOob != NULL)
	{
		parser.strm.header.opts.enumOpt = srcOob->enumOpt;
		if(srcOob->blockSize > 0)
			parser.strm.header.opts.blockSize = srcOob->blockSize;
	}
	if(err == EXIP_OK)
		err = parse.parseHeader(&parser, srcOob != NULL);
	if(err == EXIP_OK)
		err = parse.setSchema(&parser, schema);
	while(err == EXIP_OK)
		err = parse.parseNext(&parser);
	if(err == EXIP_PARSING_COMPLETE)
		err = EXIP_OK;
	parse.destroyParser(&parser);

	if(!stream && err == EXIP_OK)
		writeBytes(fixed, t.out.buffer.bufContent, out);
	{
		errorCode closeErr = serialize.closeEXIStream(&t.out);
		if(err == EXIP_OK)
			err = closeErr;
	}

	free(fixed);
	free(data);
	return err;
}

/* The bytes of a fixture */
static int sameAsFixture(const Bytes* b, const char* name)
{
	size_t size;
	char* data = readFixture(name, &size);
	int same = size == b->len && memcmp(data, b->data, size) == 0;
	free(data);
	return same;
}

/* Decodes encoded bytes: the events must be those of the reference */
static void expectRoundTrip(const Bytes* b, EXIPSchema* schema, const Oob* oob, const char* reference, const Oob* refOob)
{
	Dump ref, got;
	Parser parser;
	BinaryBuffer buffer;
	errorCode err;

	ck_assert(decodeFixture(reference, schema, refOob, FALSE, &ref) == EXIP_PARSING_COMPLETE);
	memset(&got, 0, sizeof(Dump));
	dumpf(&got, "%s", "");
	buffer.buf = b->data;
	buffer.bufLen = b->len;
	buffer.bufContent = b->len;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;
	ck_assert(parse.initParser(&parser, buffer, &got) == EXIP_OK);
	setHandlers(&parser.handler);
	if(oob != NULL)
	{
		parser.strm.header.opts.enumOpt = oob->enumOpt;
		if(oob->blockSize > 0)
			parser.strm.header.opts.blockSize = oob->blockSize;
	}
	err = parse.parseHeader(&parser, oob != NULL);
	if(err == EXIP_OK)
		err = parse.setSchema(&parser, schema);
	while(err == EXIP_OK)
		err = parse.parseNext(&parser);
	parse.destroyParser(&parser);
	ck_assert_msg(err == EXIP_PARSING_COMPLETE, "decoding exip's encoding: error %d", (int) err);
	ck_assert_msg(got.len == ref.len && memcmp(got.text, ref.text, ref.len) == 0, "exip's encoding decodes to other events than %s", reference);
	free(got.text);
	free(ref.text);
}

static void setChannels(EXIOptions* opts, exip_bool compression)
{
	if(compression)
		SET_COMPRESSION(opts->enumOpt);
	else
		SET_ALIGNMENT(opts->enumOpt, PRE_COMPRESSION);
}

/* Schema-less, options in the header: EXIficient's bytes in blocks of 64, of the default size
 * (four channels over 100 values) and of 1 value; more block sizes by round trip; output
 * through a stream and into one buffer */
START_TEST (test_encode_schemaless)
{
	uint32_t blockSizes[] = {64, 0, 1, 7, 100, 101, 1300};
	exip_bool compression;

	for(compression = FALSE; compression <= HAVE_ZLIB; compression++)
	{
		unsigned int i;

		for(i = 0; i < sizeof blockSizes / sizeof blockSizes[0]; i++)
		{
			EXIOptions opts;
			Bytes out;
			exip_bool stream;
			char fixture[PATH_LEN];

			makeDefaultOpts(&opts);
			setChannels(&opts, compression);
			if(blockSizes[i] > 0)
				opts.blockSize = blockSizes[i];
			if(blockSizes[i] == 0)
				snprintf(fixture, PATH_LEN, "catalog.%s.exi", compression ? "compression" : "pre-compression");
			else if(blockSizes[i] == 64 || blockSizes[i] == 1)
				snprintf(fixture, PATH_LEN, "catalog.%s.%u.exi", compression ? "compression" : "pre-compression", blockSizes[i]);
			else
				fixture[0] = '\0';
			for(stream = FALSE; stream <= TRUE; stream++)
			{
				errorCode err = transcode("catalog.bit-packed.exi", NULL, NULL, NULL, &opts, TRUE, stream, 64 * 1024, &out);
				ck_assert_msg(err == EXIP_OK, "%s blockSize %u (%s): error %d", compression ? "compression" : "pre-compression",
						blockSizes[i], stream ? "stream" : "buffer", (int) err);
				if(fixture[0] != '\0')
					ck_assert_msg(sameAsFixture(&out, fixture), "blockSize %u (%s): bytes differ from %s",
							blockSizes[i], stream ? "stream" : "buffer", fixture);
				expectRoundTrip(&out, NULL, NULL, "catalog.bit-packed.exi", NULL);
				free(out.data);
			}
		}
	}
}
END_TEST

/* Schema-informed, strict, options out of band: EXIficient's bytes in default blocks and
 * blocks of 3, and for order-complex in blocks of 9 (its value count: the last block is
 * empty and writes nothing); blocks of 1 and 2 by round trip (EXIficient 1.0.7 writes
 * invalid streams there) */
START_TEST (test_encode_schema_informed)
{
	const char* docs[] = {"telemetry-complex", "readings", "order-complex"};
	uint32_t blockSizes[] = {0, 3, 9, 1, 2};
	unsigned int i, j;
	exip_bool compression;

	for(i = 0; i < sizeof docs / sizeof docs[0]; i++)
	{
		EXIPSchema schema, outSchema;
		char xsd[PATH_LEN], ref[PATH_LEN], fixture[PATH_LEN];
		Oob bitPacked = {0, 0};

		SET_STRICT(bitPacked.enumOpt);
		snprintf(xsd, PATH_LEN, "%s-xsd.exi", docs[i]);
		snprintf(ref, PATH_LEN, "%s.bit-packed.exi", docs[i]);
		loadSchema(xsd, &schema);
		loadSchema(xsd, &outSchema);
		for(compression = FALSE; compression <= HAVE_ZLIB; compression++)
		{
			const char* al = compression ? "compression" : "pre-compression";

			for(j = 0; j < sizeof blockSizes / sizeof blockSizes[0]; j++)
			{
				EXIOptions opts;
				Oob oob = {0, 0};
				Bytes out;

				makeDefaultOpts(&opts);
				SET_STRICT(opts.enumOpt);
				setChannels(&opts, compression);
				if(blockSizes[j] > 0)
					opts.blockSize = blockSizes[j];
				oob.enumOpt = opts.enumOpt;
				oob.blockSize = blockSizes[j];
				ck_assert(transcode(ref, &schema, &outSchema, &bitPacked, &opts, FALSE, TRUE, 0, &out) == EXIP_OK);
				fixture[0] = '\0';
				if(blockSizes[j] == 0)
					snprintf(fixture, PATH_LEN, "%s.%s.exi", docs[i], al);
				else if(blockSizes[j] == 3)
					snprintf(fixture, PATH_LEN, "%s.%s.3.exi", docs[i], al);
				else if(blockSizes[j] == 9 && compression && i == 2)
					snprintf(fixture, PATH_LEN, "%s.compression.9.exi", docs[i]);
				if(fixture[0] != '\0')
					ck_assert_msg(sameAsFixture(&out, fixture), "%s: bytes differ from %s", docs[i], fixture);
				expectRoundTrip(&out, &schema, &oob, ref, &bitPacked);
				free(out.data);
			}
		}
		destroySchema(&schema);
		destroySchema(&outSchema);
	}
}
END_TEST

/* flushEXIData() cannot drain a body in channels; a full buffer is an error */
START_TEST (test_encode_limits)
{
	EXIOptions opts;
	Bytes out;
	EXIStream strm;
	BinaryBuffer buffer;
	char buf[256];
	char drain[256];
	unsigned int n;

	makeDefaultOpts(&opts);
	SET_ALIGNMENT(opts.enumOpt, PRE_COMPRESSION);
	ck_assert_msg(transcode("catalog.bit-packed.exi", NULL, NULL, NULL, &opts, TRUE, FALSE, 512, &out) == EXIP_BUFFER_END_REACHED,
			"a too small output buffer must fail");
	free(out.data);

	buffer.buf = buf;
	buffer.bufLen = sizeof buf;
	buffer.bufContent = 0;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;
	serialize.initHeader(&strm);
	strm.header.opts = opts;
	ck_assert(serialize.initStream(&strm, buffer, NULL) == EXIP_OK);
	ck_assert(serialize.exiHeader(&strm) == EXIP_OK);
	ck_assert(serialize.flushEXIData(&strm, drain, sizeof drain, &n) == EXIP_NOT_IMPLEMENTED_YET);
	serialize.closeEXIStream(&strm);
}
END_TEST


Suite* compression_suite(void)
{
	Suite *s = suite_create("Compression");
	TCase *tc = tcase_create("Channels");
	tcase_add_test(tc, test_schemaless_blocks);
	tcase_add_test(tc, test_schema_informed);
	tcase_add_test(tc, test_push_rejected);
	tcase_add_test(tc, test_truncated);
	tcase_add_test(tc, test_encode_schemaless);
	tcase_add_test(tc, test_encode_schema_informed);
	tcase_add_test(tc, test_encode_limits);
	suite_add_tcase(s, tc);
	return s;
}

int main(int argc, char *argv[])
{
	int number_failed;
	Suite *s = compression_suite();
	SRunner *sr = srunner_create(s);

	if(argc < 2)
	{
		printf("ERR: Expected test data directory\n");
		exit(1);
	}
	dataDir = argv[1];

#ifdef _MSC_VER
	srunner_set_fork_status(sr, CK_NOFORK);
#endif
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
