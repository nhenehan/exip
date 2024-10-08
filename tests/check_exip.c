/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file check_exip.c
 * @brief Tests the whole EXIP library with some test input data
 *
 * @date Nov 4, 2011
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: check_exip.c 360 2015-04-19 19:44:06Z kjussakov $
 */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "procTypes.h"
#include "EXISerializer.h"
#include "EXIParser.h"
#include "stringManipulate.h"
#include "grammarGenerator.h"
#include "memManagement.h"

#define MAX_PATH_LEN 200
#define OUTPUT_BUFFER_SIZE 2000
/* Location for external test data */
static char *dataDir;

static size_t writeFileOutputStream(void* buf, size_t readSize, void* stream);
static size_t readFileInputStream(void* buf, size_t readSize, void* stream);
static void parseSchema(char** xsdList, int count, EXIPSchema* schema);

#define TRY_CATCH_ENCODE(func) TRY_CATCH(func, serialize.closeEXIStream(&testStrm))

/* BEGIN: SchemaLess tests */

START_TEST (test_default_options)
{
	EXIStream testStrm;
	Parser testParser;
	String uri;
	String ln;
	QName qname= {&uri, &ln, NULL};
	String chVal;
	char buf[OUTPUT_BUFFER_SIZE];
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	BinaryBuffer buffer;
	EXITypeClass valueType;

	buffer.buf = buf;
	buffer.bufContent = 0;
	buffer.bufLen = OUTPUT_BUFFER_SIZE;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// Serialization steps:

	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header, if different from the defaults

	// III: Define an external stream for the output if any

	// IV: Initialize the stream
	tmp_err_code = serialize.initStream(&testStrm, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initStream returns an error code %d", tmp_err_code);

	// V: Start building the stream step by step: header, document, element etc...
	tmp_err_code = serialize.exiHeader(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.exiHeader returns an error code %d", tmp_err_code);

	tmp_err_code = serialize.startDocument(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.startDocument returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("http://www.ltu.se/EISLAB/schema-test", &uri, &testStrm.memList, FALSE);
	tmp_err_code += asciiToString("EXIPEncoder", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.startElement returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("", &uri, &testStrm.memList, FALSE);
	tmp_err_code += asciiToString("version", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.attribute returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("0.2", &chVal, &testStrm.memList, FALSE);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.stringData returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("", &uri, &testStrm.memList, FALSE);
	tmp_err_code += asciiToString("status", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.attribute returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("alpha", &chVal, &testStrm.memList, FALSE);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.stringData returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("This is an example of serializing EXI streams using EXIP low level API", &chVal, &testStrm.memList, FALSE);
	tmp_err_code += serialize.stringData(&testStrm, chVal);

	tmp_err_code += serialize.endElement(&testStrm);
	tmp_err_code += serialize.endDocument(&testStrm);

	if(tmp_err_code != EXIP_OK)
		fail_unless (tmp_err_code == EXIP_OK, "serialization ended with error code %d", tmp_err_code);

	// V: Free the memory allocated by the EXI stream object
	tmp_err_code = serialize.closeEXIStream(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.closeEXIStream ended with error code %d", tmp_err_code);


	buffer.bufContent = OUTPUT_BUFFER_SIZE;
	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any

	// II: Second, initialize the parser object
	tmp_err_code = initParser(&testParser, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object

	// IV: Parse the header of the stream

	tmp_err_code = parseHeader(&testParser, TRUE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = setSchema(&testParser, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);

	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parseNext(&testParser);
	}

	// VI: Free the memory allocated by the parser object

	destroyParser(&testParser);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
}
END_TEST

START_TEST (test_fragment_option)
{
	EXIStream testStrm;
	Parser testParser;
	String uri;
	String ln;
	QName qname= {&uri, &ln, NULL};
	String chVal;
	char buf[OUTPUT_BUFFER_SIZE];
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	BinaryBuffer buffer;
	EXITypeClass valueType;

	buffer.buf = buf;
	buffer.bufContent = 0;
	buffer.bufLen = OUTPUT_BUFFER_SIZE;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// Serialization steps:

	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header, if different from the defaults
	testStrm.header.has_cookie = TRUE;
	testStrm.header.has_options = TRUE;
	SET_FRAGMENT(testStrm.header.opts.enumOpt);

	// III: Define an external stream for the output if any

	// IV: Initialize the stream
	tmp_err_code = serialize.initStream(&testStrm, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initStream returns an error code %d", tmp_err_code);

	// V: Start building the stream step by step: header, document, element etc...
	tmp_err_code = serialize.exiHeader(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.exiHeader returns an error code %d", tmp_err_code);

	tmp_err_code = serialize.startDocument(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.startDocument returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("http://www.ltu.se/EISLAB/schema-test", &uri, &testStrm.memList, FALSE);
	tmp_err_code += asciiToString("EXIPEncoder", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.startElement returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("", &uri, &testStrm.memList, FALSE);
	tmp_err_code += asciiToString("version", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.attribute returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("0.2", &chVal, &testStrm.memList, FALSE);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.stringData returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("", &uri, &testStrm.memList, FALSE);
	tmp_err_code += asciiToString("status", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.attribute returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("alpha", &chVal, &testStrm.memList, FALSE);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.stringData returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("Test", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.startElement returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("beta tests", &chVal, &testStrm.memList, FALSE);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.stringData returns an error code %d", tmp_err_code);

	tmp_err_code += serialize.endElement(&testStrm);

	tmp_err_code += serialize.endElement(&testStrm);

	tmp_err_code += asciiToString("Test2", &ln, &testStrm.memList, FALSE);
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.startElement returns an error code %d", tmp_err_code);

	tmp_err_code += asciiToString("beta tests -> second root element", &chVal, &testStrm.memList, FALSE);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.stringData returns an error code %d", tmp_err_code);

	tmp_err_code = serialize.endElement(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.endElement returns an error code %d", tmp_err_code);

	tmp_err_code = serialize.endDocument(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.endDocument returns an error code %d", tmp_err_code);

	if(tmp_err_code != EXIP_OK)
		fail_unless (tmp_err_code == EXIP_OK, "serialization ended with error code %d", tmp_err_code);

	// V: Free the memory allocated by the EXI stream object
	tmp_err_code = serialize.closeEXIStream(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.closeEXIStream ended with error code %d", tmp_err_code);

	buffer.bufContent = OUTPUT_BUFFER_SIZE;

	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any

	// II: Second, initialize the parser object
	tmp_err_code = initParser(&testParser, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object

	// IV: Parse the header of the stream

	tmp_err_code = parseHeader(&testParser, FALSE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = setSchema(&testParser, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);
	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parseNext(&testParser);
	}

	// VI: Free the memory allocated by the parser object

	destroyParser(&testParser);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
}
END_TEST

START_TEST (test_value_part_zero)
{
	const String NS_EMPTY_STR = {NULL, 0};
	const String ELEM_COBS_STR = {"cobs", 4};
	const String ELEM_TM_STAMP_STR = {"timestamp", 9};
	const String ELEM_RPM_STR = {"rpm", 3};
	const String ELEM_ACC_RNDS_STR = {"accRounds", 9};
	const String ELEM_TEMP_STR = {"temp", 4};
	const String ELEM_LEFT_STR = {"left", 4};
	const String ELEM_RIGHT_STR = {"right", 5};
	const String ELEM_RSSI_STR = {"RSSI", 4};
	const String ELEM_MIN_STR = {"min", 3};
	const String ELEM_MAX_STR = {"max", 3};
	const String ELEM_AVG_STR = {"avg", 3};
	const String ELEM_BATTERY_STR = {"battery", 7};
	const String ATTR_NODE_ID_STR = {"nodeId", 6};

	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	EXIStream testStrm;
	String uri;
	String ln;
	QName qname = {&uri, &ln, NULL};
	String chVal;
	BinaryBuffer buffer;
	EXITypeClass valueType;
	char valStr[50];
	char buf[OUTPUT_BUFFER_SIZE];
	Parser testParser;

	buffer.buf = buf;
	buffer.bufLen = OUTPUT_BUFFER_SIZE;
	buffer.bufContent = 0;

	// Serialization steps:

	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header, if different from the defaults
	testStrm.header.has_options = TRUE;
	testStrm.header.opts.valuePartitionCapacity = 0;

	// III: Define an external stream for the output if any
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// IV: Initialize the stream
	tmp_err_code = serialize.initStream(&testStrm, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initStream returns an error code %d", tmp_err_code);

	// V: Start building the stream step by step: header, document, element etc...
	tmp_err_code += serialize.exiHeader(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "exiHeader returns an error code %d", tmp_err_code);

	tmp_err_code += serialize.startDocument(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_COBS_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <cobs>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_NODE_ID_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // nodeId="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%d", 111);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_TM_STAMP_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <timestamp>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	chVal.str = "2012-12-31T12:09:3.44";
	chVal.length = strlen("2012-12-31T12:09:3.44");
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </timestamp>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_RPM_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <rpm>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%d", 222);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </rpm>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_ACC_RNDS_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <accRounds>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%d", 4212);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </accRounds>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_TEMP_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <temp>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_LEFT_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <left>
	sprintf(valStr, "%f", 32.2);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	tmp_err_code += serialize.endElement(&testStrm); // </left>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_RIGHT_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <right>
	sprintf(valStr, "%f", 34.23);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	tmp_err_code += serialize.endElement(&testStrm); // </right>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </temp>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_RSSI_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <RSSI>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_AVG_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <avg>
	sprintf(valStr, "%d", 123);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	tmp_err_code += serialize.endElement(&testStrm); // </avg>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_MAX_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <max>
	sprintf(valStr, "%d", 2746);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	tmp_err_code += serialize.endElement(&testStrm); // </max>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_MIN_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <min>
	sprintf(valStr, "%d", 112);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	tmp_err_code += serialize.endElement(&testStrm); // </min>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </RSSI>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_BATTERY_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <battery>
	sprintf(valStr, "%f", 1.214);
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	tmp_err_code += serialize.endElement(&testStrm); // </battery>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </cobs>
	tmp_err_code += serialize.endDocument(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	// VI: Free the memory allocated by the EXI stream object
	tmp_err_code += serialize.closeEXIStream(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	buffer.bufContent = OUTPUT_BUFFER_SIZE;
	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any

	// II: Second, initialize the parser object
	tmp_err_code = initParser(&testParser, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object

	// IV: Parse the header of the stream

	tmp_err_code = parseHeader(&testParser, TRUE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = setSchema(&testParser, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);
	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parseNext(&testParser);
	}

	// VI: Free the memory allocated by the parser object

	destroyParser(&testParser);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
}
END_TEST

START_TEST (test_recursive_defs)
{
	const String NS_EMPTY_STR = {NULL, 0};
	const String ELEM_OBJ_STR = {"obj", 3};
	const String ELEM_STR_STR = {"str", 3};
	const String ELEM_LIST_STR = {"list", 4};

	const String ATTR_XSTR_STR = {"xsss", 4};
	const String ATTR_XTEMP_STR = {"x-template", 10};
	const String ATTR_NAME_STR = {"name", 4};
	const String ATTR_VAL_STR = {"val", 3};

	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	EXIStream testStrm;
	String uri;
	String ln;
	QName qname = {&uri, &ln, NULL};
	String chVal;
	BinaryBuffer buffer;
	EXITypeClass valueType;
	char valStr[50];
	char buf[OUTPUT_BUFFER_SIZE];
	Parser testParser;

	buffer.buf = buf;
	buffer.bufLen = OUTPUT_BUFFER_SIZE;
	buffer.bufContent = 0;

	// Serialization steps:

	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header, if different from the defaults
	testStrm.header.has_options = TRUE;
	SET_STRICT(testStrm.header.opts.enumOpt);
	SET_ALIGNMENT(testStrm.header.opts.enumOpt, BYTE_ALIGNMENT);

	// III: Define an external stream for the output if any
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// IV: Initialize the stream
	tmp_err_code = serialize.initStream(&testStrm, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initStream returns an error code %d", tmp_err_code);

	// V: Start building the stream step by step: header, document, element etc...
	tmp_err_code += serialize.exiHeader(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "exiHeader returns an error code %d", tmp_err_code);

	tmp_err_code += serialize.startDocument(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_OBJ_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <obj>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_XSTR_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // xsss="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "http://obix.org/ns/schema/1.1");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_XTEMP_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // x-template="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "ipu_inst.xml");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_STR_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_NAME_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // name="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "interworkingProxyID");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_VAL_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // val="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "IPU_6LoWPAN");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_LIST_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <list>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_NAME_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // name="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "supportedTechnologies");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ELEM_OBJ_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <obj>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	qname.localName = &ELEM_STR_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_NAME_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // name="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "anPhysical");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_VAL_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // val="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "2003_2_4GHz");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	qname.localName = &ELEM_STR_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_NAME_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // name="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "anStandard");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_VAL_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // val="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "Bee_1_0");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);


	qname.localName = &ELEM_STR_STR;
	tmp_err_code += serialize.startElement(&testStrm, qname, &valueType); // <str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_NAME_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // name="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "anProfile");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	qname.localName = &ATTR_VAL_STR;
	tmp_err_code += serialize.attribute(&testStrm, qname, TRUE, &valueType); // val="..."
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	sprintf(valStr, "%s", "Bee_HA");
	chVal.str = valStr;
	chVal.length = strlen(valStr);
	tmp_err_code += serialize.stringData(&testStrm, chVal);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	tmp_err_code += serialize.endElement(&testStrm); // </str>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	tmp_err_code += serialize.endElement(&testStrm); // </obj>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	tmp_err_code += serialize.endElement(&testStrm); // </list>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	tmp_err_code += serialize.endElement(&testStrm); // </obj>
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	tmp_err_code += serialize.endDocument(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);
	// VI: Free the memory allocated by the EXI stream object
	tmp_err_code += serialize.closeEXIStream(&testStrm);
	fail_unless (tmp_err_code == EXIP_OK, "serialize.* returns an error code %d", tmp_err_code);

	buffer.bufContent = OUTPUT_BUFFER_SIZE;
	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any

	// II: Second, initialize the parser object
	tmp_err_code = initParser(&testParser, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object

	// IV: Parse the header of the stream

	tmp_err_code = parseHeader(&testParser, FALSE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = setSchema(&testParser, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);

	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parseNext(&testParser);
	}

	// VI: Free the memory allocated by the parser object

	destroyParser(&testParser);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
}
END_TEST

errorCode encodeWithDynamicTypes(char* buf, int buf_size, int *strmSize);

/**
 * Example use of the xsi:type switch for dynamic typing of
 * element and attribute values. Note that schemaId must be set
 * to SCHEMA_ID_EMPTY in order to use the built-in schema types.
 * Encodes the following XML:
 *
 * <trivial xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 * xmlns:xsd="http://www.w3.org/2001/XMLSchema">
 *    <anElement xsi:type="xsd:date">2014-01-31T16:15:25+02:00</anElement>
 * </trivial>
 */
START_TEST (test_built_in_dynamic_types)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	char buf[OUTPUT_BUFFER_SIZE];
	int strmSize = 0;
	BinaryBuffer buffer;
	Parser testParser;

	tmp_err_code = encodeWithDynamicTypes(buf, OUTPUT_BUFFER_SIZE, &strmSize);
	fail_unless(tmp_err_code == EXIP_OK, "There is an error in the encoding of dynamic types through xsi:type switch.");
	fail_unless(strmSize > 0, "Encoding of dynamic types through xsi:type switch produces empty streams.");

	buffer.bufContent = strmSize;
	buffer.buf = buf;
	buffer.bufLen = OUTPUT_BUFFER_SIZE;

	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any

	// II: Second, initialize the parser object
	tmp_err_code = initParser(&testParser, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object

	// IV: Parse the header of the stream

	tmp_err_code = parseHeader(&testParser, FALSE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = setSchema(&testParser, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);

	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parseNext(&testParser);
	}

	// VI: Free the memory allocated by the parser object

	destroyParser(&testParser);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
}
END_TEST

errorCode encodeWithDynamicTypes(char* buf, int buf_size, int *strmSize)
{
	EXIP_UNUSED(buf_size);
	EXIP_UNUSED(strmSize);
	const String NS_EMPTY = {NULL, 0};
	const String NS_XSI = {"http://www.w3.org/2001/XMLSchema-instance", 41};
	const String NS_XSD = {"http://www.w3.org/2001/XMLSchema", 32};

	const String ELEM_TRIVIAL = {"trivial", 7};
	const String ELEM_AN_ELEMENT = {"anElement", 9};

	const String PREFIX_XSI = {"xsi", 3};

	const String ATTR_TYPE = {"type", 4};

	const String VALUE_DATE = {"dateTime", 8};

	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	EXIStream testStrm;
	String uri;
	String ln;
	QName qname = {&uri, &ln, NULL};

	BinaryBuffer buffer;
	EXITypeClass valueType;
	EXIPDateTime dt_val;

	buffer.buf = buf;
	buffer.bufLen = OUTPUT_BUFFER_SIZE;
	buffer.bufContent = 0;

	// Serialization steps:

	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header (including schemaID and schemaIDMode), if different from the defaults.
	testStrm.header.has_options = TRUE;
	SET_PRESERVED(testStrm.header.opts.preserve, PRESERVE_PREFIXES);
	testStrm.header.opts.schemaIDMode = SCHEMA_ID_EMPTY;

	// III: Define an external stream for the output if any, otherwise set to NULL
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// IV: Initialize the stream
	TRY_CATCH_ENCODE(serialize.initStream(&testStrm, buffer, NULL));

	// V: Start building the stream step by step: header, document, element etc...
	TRY_CATCH_ENCODE(serialize.exiHeader(&testStrm));

	TRY_CATCH_ENCODE(serialize.startDocument(&testStrm));

	qname.uri = &NS_EMPTY;
	qname.localName = &ELEM_TRIVIAL;
	TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // <trivial>

	TRY_CATCH_ENCODE(serialize.namespaceDeclaration(&testStrm, NS_XSI, PREFIX_XSI, FALSE)); // xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"

	qname.uri = &NS_EMPTY;
	qname.localName = &ELEM_AN_ELEMENT;
	TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // <anElement>

	qname.uri = &NS_XSI;
	qname.localName = &ATTR_TYPE;
	TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // xsi:type="

	qname.uri = &NS_XSD;
	qname.localName = &VALUE_DATE;
	TRY_CATCH_ENCODE(serialize.qnameData(&testStrm, qname)); // xsd:date

	dt_val.dateTime.tm_year = 114; // + 1900 offset = 2014
	dt_val.dateTime.tm_mon = 0; // 0 = Jan
	dt_val.dateTime.tm_mday = 31;
	dt_val.dateTime.tm_hour = 16;
	dt_val.dateTime.tm_min = 15;
	dt_val.dateTime.tm_sec = 25;
	dt_val.presenceMask = 0;
	dt_val.presenceMask |= TZONE_PRESENCE;
	dt_val.TimeZone = 2*64; // UTC + 2
	TRY_CATCH_ENCODE(serialize.dateTimeData(&testStrm, dt_val)); // dateTime: 2014-01-31T16:15:25+02:00

	TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // </anElement>
	TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // </trivial>

	TRY_CATCH_ENCODE(serialize.endDocument(&testStrm));

	*strmSize = testStrm.context.bufferIndx + 1;

	// VI: Free the memory allocated by the EXI stream object
	TRY_CATCH_ENCODE(serialize.closeEXIStream(&testStrm));

	return EXIP_OK;
}

/* END: SchemaLess tests */

#define OUTPUT_BUFFER_SIZE_LARGE_DOC 20000
#define MAX_XSD_FILES_COUNT 10 // up to 10 XSD files

/* BEGIN: Schema-mode tests */
START_TEST (test_large_doc_str_pattern)
{
	const String NS_EMPTY_STR = {NULL, 0};

	const String ELEM_CONFIGURATION = {"configuration", 13};
	const String ELEM_CAPSWITCH = {"capable-switch", 14};
	const String ELEM_RESOURCES = {"resources", 9};
	const String ELEM_PORT = {"port", 4};
	const String ELEM_RESID = {"resource-id", 11};
	const String ELEM_ADMIN_STATE = {"admin-state", 11};
	const String ELEM_NORECEIVE = {"no-receive", 10};
	const String ELEM_NOFORWARD = {"no-forward", 10};
	const String ELEM_NOPACKET = {"no-packet-in", 12};

	const String ELEM_LOGSWITCHES = {"logical-switches", 16};
	const String ELEM_SWITCH = {"switch", 6};
	const String ELEM_ID = {"id", 2};
	const String ELEM_DATAPATHID = {"datapath-id", 11};
	const String ELEM_ENABLED = {"enabled", 7};
	const String ELEM_LOSTCONNBEH = {"lost-connection-behavior", 24};
	const String ELEM_CONTROLLERS = {"controllers", 11};
	const String ELEM_CONTROLLER = {"controller", 10};
	const String ELEM_ROLE = {"role", 4};
	const String ELEM_IPADDR = {"ip-address", 10};
	const String ELEM_PROTOCOL = {"protocol", 8};
	const String ELEM_STATE = {"state", 5};
	const String ELEM_CONNSTATE = {"connection-state", 16};
	const String ELEM_CURRVER = {"current-version", 15};

	const char * PORT_STR = "port";
	const char * SWITCH_STR = "switch";
	const char * STATE_UP_STR = "up";
	const char * DATAPATH_STR = "10:14:56:7C:89:46:7A:";
	const char * LOST_CONN_BEHAVIOR_STR = "failSecureMode";
	const char * CTRL_STR = "ctrl";
	const char * ROLE_STR = "equal";
	const char * IPADDR_STR = "10.10.10.";
	const char * PROTOCOL_STR = "tcp";
	const char * VER_STR = "1.0";

	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	FILE *outfile;
	char* sourceFile = "testOutputFile.exi";
	EXIPSchema schema;
//	struct timespec start;
//	struct timespec end;
	char* schemafname[1] = {"exip/schema_demo.exi"};
	EXIStream testStrm;
	String uri;
	String ln;
	QName qname = {&uri, &ln, NULL};
	String chVal;
	char buf[OUTPUT_BUFFER_SIZE_LARGE_DOC];
	BinaryBuffer buffer;
	int i, j;
	char strbuffer[32];

	buffer.buf = buf;
	buffer.bufLen = OUTPUT_BUFFER_SIZE_LARGE_DOC;
	buffer.bufContent = 0;

	parseSchema(schemafname, 1, &schema);

	outfile = fopen(sourceFile, "wb" );
	fail_if(!outfile, "Unable to open file %s", sourceFile);

	// Serialization steps:

	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header, if different from the defaults
	testStrm.header.has_cookie = TRUE;
	testStrm.header.has_options = TRUE;
	testStrm.header.opts.valueMaxLength = 300;
	testStrm.header.opts.valuePartitionCapacity = INDEX_MAX;
	SET_STRICT(testStrm.header.opts.enumOpt);

	// III: Define an external stream for the output if any
	buffer.ioStrm.readWriteToStream = writeFileOutputStream;
	buffer.ioStrm.stream = outfile;
	//buffer.ioStrm.readWriteToStream = NULL;
	//buffer.ioStrm.stream = NULL;
// printf("line:%d: %d\n", __LINE__, tmp_err_code);
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	// IV: Initialize the stream
	tmp_err_code = serialize.initStream(&testStrm, buffer, &schema);
	fail_unless(tmp_err_code == EXIP_OK);

//printf("line:%d: %d\n", __LINE__, tmp_err_code);
//                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	// V: Start building the stream step by step: header, document, element etc...
	tmp_err_code += serialize.exiHeader(&testStrm);
// printf("line:%d: %d\n", __LINE__, tmp_err_code);
	tmp_err_code += serialize.startDocument(&testStrm);
// printf("line:%d: %d\n", __LINE__, tmp_err_code);
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_CONFIGURATION;
	EXITypeClass typeClass;
	tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_CAPSWITCH;
	tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_RESOURCES;
	tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

// printf("line:%d: %d\n", __LINE__, tmp_err_code);
	for (i = 0; i < 100; i++)
	{
		qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_PORT;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_RESID;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	    sprintf(strbuffer, "%s%d", PORT_STR, i);
	    tmp_err_code += asciiToString(strbuffer, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_CONFIGURATION;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_ADMIN_STATE;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += asciiToString(STATE_UP_STR, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_NORECEIVE;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += serialize.booleanData(&testStrm, FALSE);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_NOFORWARD;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += serialize.booleanData(&testStrm, FALSE);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_NOPACKET;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += serialize.booleanData(&testStrm, TRUE);
		tmp_err_code += serialize.endElement(&testStrm);

		tmp_err_code += serialize.endElement(&testStrm);

		tmp_err_code += serialize.endElement(&testStrm);
	}
	tmp_err_code += serialize.endElement(&testStrm);

	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_LOGSWITCHES;
	tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	for (i = 0; i < 20; i++)
	{
	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_SWITCH;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_ID;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

		sprintf(strbuffer, "%s%d", SWITCH_STR, i);
	    tmp_err_code += asciiToString(strbuffer, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_DATAPATHID;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

		sprintf(strbuffer, "%s%d", DATAPATH_STR, 10 + i);
	    tmp_err_code += asciiToString(strbuffer, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_ENABLED;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += serialize.booleanData(&testStrm, TRUE);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_LOSTCONNBEH;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += asciiToString(LOST_CONN_BEHAVIOR_STR, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);
// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
//		if ( i == 0 )
//		{
	        qname.uri = &NS_EMPTY_STR;
	        qname.localName = &ELEM_RESOURCES;
	        tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

			for (j = 0; j < 100; j++)
			{
	            qname.uri = &NS_EMPTY_STR;
	            qname.localName = &ELEM_PORT;
	            tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

				sprintf(strbuffer, "%s%d", PORT_STR, j);
	            tmp_err_code += asciiToString(strbuffer, &chVal, &testStrm.memList, FALSE);
	            tmp_err_code += serialize.stringData(&testStrm, chVal);
				tmp_err_code += serialize.endElement(&testStrm);
			}
			tmp_err_code += serialize.endElement(&testStrm);
//		}
// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_CONTROLLERS;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_CONTROLLER;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_ID;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
		sprintf(strbuffer, "%s%d", CTRL_STR, i);
	    tmp_err_code += asciiToString(strbuffer, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);
// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_ROLE;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += asciiToString(ROLE_STR, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_IPADDR;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
		sprintf(strbuffer, "%s%d", IPADDR_STR, i);
	    tmp_err_code += asciiToString(strbuffer, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_PORT;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += serialize.intData(&testStrm, 6620);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_PROTOCOL;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += asciiToString(PROTOCOL_STR, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_STATE;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);

	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_CONNSTATE;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
	    tmp_err_code += asciiToString(STATE_UP_STR, &chVal, &testStrm.memList, FALSE);
	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
	    qname.uri = &NS_EMPTY_STR;
	    qname.localName = &ELEM_CURRVER;
	    tmp_err_code += serialize.startElement(&testStrm, qname, &typeClass);
// printf("in loop(%d) line:%d: %d\n", i, __LINE__, tmp_err_code);
	    tmp_err_code += asciiToString(VER_STR, &chVal, &testStrm.memList, FALSE);

	    tmp_err_code += serialize.stringData(&testStrm, chVal);
		tmp_err_code += serialize.endElement(&testStrm);

		tmp_err_code += serialize.endElement(&testStrm);

		tmp_err_code += serialize.endElement(&testStrm);

		tmp_err_code += serialize.endElement(&testStrm);

		tmp_err_code += serialize.endElement(&testStrm);
	}

	tmp_err_code += serialize.endElement(&testStrm);

	tmp_err_code += serialize.endElement(&testStrm);

	tmp_err_code += serialize.endElement(&testStrm);
	tmp_err_code += serialize.endDocument(&testStrm);
	fail_unless(tmp_err_code == EXIP_OK);

//	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	// VI: Free the memory allocated by the EXI stream object
	tmp_err_code = serialize.closeEXIStream(&testStrm);

//                        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
//                total += ((end.tv_sec * SEC2NANO) + end.tv_nsec) - ((start.tv_sec * SEC2NANO) + start.tv_nsec);

    fclose(outfile);
    destroySchema(&schema);

    /* DECODE */
    {
    	Parser testParser;
    	FILE *infile;

    	buffer.buf = buf;
    	buffer.bufContent = 0;
    	buffer.bufLen = OUTPUT_BUFFER_SIZE_LARGE_DOC;
    	unsigned int eventCount;

    	// Parsing steps:

    	// I.A: First, read in the schema
    	parseSchema(schemafname, 1, &schema);

    	// I.B: Define an external stream for the input to the parser if any
    	infile = fopen(sourceFile, "rb" );
    	if(!infile)
    		fail("Unable to open file %s", sourceFile);

    	buffer.ioStrm.readWriteToStream = readFileInputStream;
    	buffer.ioStrm.stream = infile;

    	// II: Second, initialize the parser object
    	tmp_err_code = initParser(&testParser, buffer, &eventCount);
    	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

    	// IV: Parse the header of the stream
		tmp_err_code = parseHeader(&testParser, FALSE);
		fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

		tmp_err_code = setSchema(&testParser, &schema);
		fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);

		// V: Parse the body of the EXI stream
		while(tmp_err_code == EXIP_OK)
		{
			tmp_err_code = parseNext(&testParser);
		}

		// VI: Free the memory allocated by the parser object
		destroyParser(&testParser);
		fclose(infile);
		fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
    }

    remove(sourceFile);
	destroySchema(&schema);
}
END_TEST

#define INPUT_BUFFER_SIZE 200

/* Test substitution groups */
START_TEST (test_substitution_groups)
{
	EXIPSchema schema;
	FILE *infile;
	Parser testParser;
	char buf[INPUT_BUFFER_SIZE];
	char* schemafname[2] = {"exip/subsGroups/root-xsd.exi","exip/subsGroups/sub-xsd.exi"};
	char *exifname = "exip/subsGroups/root.exi";
	char exipath[MAX_PATH_LEN + strlen(exifname)];
	unsigned int eventCount;
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	BinaryBuffer buffer;

	buffer.buf = buf;
	buffer.bufContent = 0;
	buffer.bufLen = INPUT_BUFFER_SIZE;

	// Parsing steps:

	// I.A: First, read in the schema
	parseSchema(schemafname, 2, &schema);

	// I.B: Define an external stream for the input to the parser if any
	size_t pathlen = strlen(dataDir);
	memcpy(exipath, dataDir, pathlen);
	exipath[pathlen] = '/';
	memcpy(&exipath[pathlen+1], exifname, strlen(exifname)+1);

	infile = fopen(exipath, "rb" );
	if(!infile)
		fail("Unable to open file %s", exipath);

	buffer.ioStrm.readWriteToStream = readFileInputStream;
	buffer.ioStrm.stream = infile;

	// II: Second, initialize the parser object
	tmp_err_code = initParser(&testParser, buffer, &eventCount);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object
	eventCount = 0;

	// IV: Parse the header of the stream
	tmp_err_code = parseHeader(&testParser, FALSE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = setSchema(&testParser,  &schema);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);
	// V: Parse the body of the EXI stream
	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parseNext(&testParser);
		eventCount++;
	}

	fail_unless(eventCount == 38,
	            "Unexpected event count: %u", eventCount);

	// VI: Free the memory allocated by the parser object
	destroyParser(&testParser);
	fclose(infile);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
	destroySchema(&schema);
}
END_TEST

errorCode encodeNonBlockingStreaming(EXIPSchema* schema, char* flushBuf, int buf_size, int *strmSize, unsigned char alignment);

START_TEST (test_non_blocking_streaming)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	char flushBuf[OUTPUT_BUFFER_SIZE];
	int strmSize = 0;
	BinaryBuffer buffer;
	Parser testParser;
	char* schemafname[1] = {"exip/NonBlockingStreaming-xsd.exi"};
	EXIPSchema schema;
	char tmpBuf[40];
	unsigned int flushMarker;
	unsigned int bytesRead;

	parseSchema(schemafname, 1, &schema);

	tmp_err_code = encodeNonBlockingStreaming(&schema, flushBuf, OUTPUT_BUFFER_SIZE, &strmSize, BIT_PACKED);
	fail_unless(tmp_err_code == EXIP_OK, "There is an error in the encoding of non blocking EXI stream");
	fail_unless(strmSize > 0, "Encoding using non blocking flushing produces empty streams.");

	flushMarker = 20;
	memcpy(tmpBuf, flushBuf, flushMarker);

	buffer.bufContent = flushMarker;
	buffer.buf = tmpBuf;
	buffer.bufLen = 40;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any

	// II: Second, initialize the parser object
	tmp_err_code = parse.initParser(&testParser, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object

	// IV: Parse the header of the stream

	tmp_err_code = parse.parseHeader(&testParser, FALSE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = parse.setSchema(&testParser, &schema);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);

	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parse.parseNext(&testParser);
	}

	while (tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		tmp_err_code = parse.pushEXIData(flushBuf + flushMarker, strmSize - flushMarker, &bytesRead, &testParser);
		if(tmp_err_code != EXIP_OK)
			break;
		flushMarker += bytesRead;

		while(tmp_err_code == EXIP_OK)
		{
			tmp_err_code = parse.parseNext(&testParser);
		}
	}

	// VI: Free the memory allocated by the parser object
        //testParser.strm.valueTable.count
        //testParser.strm.valueTable.value[vxTable->vx[vxEntryId].globalId].valueStr
        //freeAllMem(&testParser.strm.buffer);
	parse.destroyParser(&testParser);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
	destroySchema(&schema);
}
END_TEST

START_TEST (test_non_blocking_streaming_bytealigned)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	char flushBuf[OUTPUT_BUFFER_SIZE];
	int strmSize = 0;
	BinaryBuffer buffer;
	Parser testParser;
	char* schemafname[1] = {"exip/NonBlockingStreaming-xsd.exi"};
	EXIPSchema schema;
	char tmpBuf[40];
	unsigned int flushMarker;
	unsigned int bytesRead;

	parseSchema(schemafname, 1, &schema);

	tmp_err_code = encodeNonBlockingStreaming(&schema, flushBuf, OUTPUT_BUFFER_SIZE, &strmSize, BYTE_ALIGNMENT);
	fail_unless(tmp_err_code == EXIP_OK, "There is an error in the encoding of non blocking EXI stream");
	fail_unless(strmSize > 0, "Encoding using non blocking flushing produces empty streams.");

	flushMarker = 20;
	memcpy(tmpBuf, flushBuf, flushMarker);

	buffer.bufContent = flushMarker;
	buffer.buf = tmpBuf;
	buffer.bufLen = 40;
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any

	// II: Second, initialize the parser object
	tmp_err_code = parse.initParser(&testParser, buffer, NULL);
	fail_unless (tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

	// III: Initialize the parsing data and hook the callback handlers to the parser object

	// IV: Parse the header of the stream

	tmp_err_code = parse.parseHeader(&testParser, FALSE);
	fail_unless (tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

	tmp_err_code = parse.setSchema(&testParser, &schema);
	fail_unless (tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);

	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parse.parseNext(&testParser);
	}

	while (tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		tmp_err_code = parse.pushEXIData(flushBuf + flushMarker, strmSize - flushMarker, &bytesRead, &testParser);
		if(tmp_err_code != EXIP_OK)
			break;
		flushMarker += bytesRead;

		while(tmp_err_code == EXIP_OK)
		{
			tmp_err_code = parse.parseNext(&testParser);
		}
	}

	// VI: Free the memory allocated by the parser object

	parse.destroyParser(&testParser);
	fail_unless (tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
	destroySchema(&schema);
}
END_TEST

errorCode encodeNonBlockingStreaming(EXIPSchema* schema, char* flushBuf, int buf_size, int *strmSize, unsigned char alignment)
{
	const String NS_EMPTY_STR = {NULL, 0};
	const String NS_URN_STR = {"non:blocking:check", 18};

	const String ELEM_TEST = {"test", 4};
	const String ELEM_LONG_TEST = {"long-test", 9};

	const String ATTR_SAMPLE = {"sample", 6};
	const String ATTR_SAMPLE_2 = {"sample-2", 8};

	const String LONG_DATA_STR = {"Test data.", 10};
	const String SHORT_DATA_STR = {"echo-echoo-echooo", 17};
	const String LT1_DATA_STR = {"long-test 1 data", 16};
	const String LT2_DATA_STR = {"long-test 2 data", 16};
	const String LT3_DATA_STR = {"long-test 3 data", 16};

	const String SCHEMA_ID_STR = {"schemaID=test", 13};

	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	EXIStream testStrm;
	BinaryBuffer buffer;
	String uri;
	String ln;
	QName qname = {&uri, &ln, NULL};
	EXITypeClass valueType;
	char smallBuf[40];
	StreamContext savedContext;
	SmallIndex savedNonTerminalIndex;
	unsigned int bytesFlushed = 0;

	buffer.buf = smallBuf;
	buffer.bufLen = 40;
	buffer.bufContent = 0;

	*strmSize = 0;

	// Serialization steps:
	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header (including schemaID and schemaIDMode), if different from the defaults.
	testStrm.header.has_options = TRUE;
	SET_ALIGNMENT(testStrm.header.opts.enumOpt, alignment);
	testStrm.header.opts.schemaIDMode = SCHEMA_ID_SET;
	testStrm.header.opts.schemaID = SCHEMA_ID_STR;

	// III: Define an external stream for the output if any, otherwise set to NULL
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// IV: Initialize the stream
	TRY_CATCH_ENCODE(serialize.initStream(&testStrm, buffer, schema));

	// V: Start building the stream step by step: header, document, element etc...
	TRY_CATCH_ENCODE(serialize.exiHeader(&testStrm));

	TRY_CATCH_ENCODE(serialize.startDocument(&testStrm));

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_URN_STR;
	qname.localName = &ELEM_TEST;
	tmp_err_code = serialize.startElement(&testStrm, qname, &valueType); // <test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // redo the <test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ATTR_SAMPLE;
	tmp_err_code = serialize.attribute(&testStrm, qname, TRUE, &valueType); // sample="
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // redo sample="
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, SHORT_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, SHORT_DATA_STR)); // redo SHORT_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_LONG_TEST;
	tmp_err_code = serialize.startElement(&testStrm, qname, &valueType); // <long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // redo the <long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ATTR_SAMPLE_2;
	tmp_err_code = serialize.attribute(&testStrm, qname, TRUE, &valueType); // sample-2="
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // redo sample-2="
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, SHORT_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, SHORT_DATA_STR)); // redo SHORT_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, LONG_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, LONG_DATA_STR)); // redo LONG_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.endElement(&testStrm); // </long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // redo the </long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	// ***************************

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_LONG_TEST;
	tmp_err_code = serialize.startElement(&testStrm, qname, &valueType); // <long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // redo the <long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ATTR_SAMPLE_2;
	tmp_err_code = serialize.attribute(&testStrm, qname, TRUE, &valueType); // sample-2="
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // redo sample-2="
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, SHORT_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, SHORT_DATA_STR)); // redo SHORT_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, LT1_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, LT1_DATA_STR)); // redo LT1_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.endElement(&testStrm); // </long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // redo the </long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	// *************************

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_LONG_TEST;
	tmp_err_code = serialize.startElement(&testStrm, qname, &valueType); // <long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // redo the <long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ATTR_SAMPLE_2;
	tmp_err_code = serialize.attribute(&testStrm, qname, TRUE, &valueType); // sample-2="
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // redo sample-2="
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, SHORT_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, SHORT_DATA_STR)); // redo SHORT_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, LT2_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, LT2_DATA_STR)); // redo LT2_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.endElement(&testStrm); // </long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // redo the </long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	// ********************************************

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_LONG_TEST;
	tmp_err_code = serialize.startElement(&testStrm, qname, &valueType); // <long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // redo the <long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ATTR_SAMPLE_2;
	tmp_err_code = serialize.attribute(&testStrm, qname, TRUE, &valueType); // sample-2="
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // redo sample-2="
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, SHORT_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, SHORT_DATA_STR)); // redo SHORT_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, LT3_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, LT3_DATA_STR)); // redo LT2_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.endElement(&testStrm); // </long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // redo the </long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	// ************************

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ELEM_LONG_TEST;
	tmp_err_code = serialize.startElement(&testStrm, qname, &valueType); // <long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // redo the <long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	qname.uri = &NS_EMPTY_STR;
	qname.localName = &ATTR_SAMPLE_2;
	tmp_err_code = serialize.attribute(&testStrm, qname, TRUE, &valueType); // sample-2="
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // redo sample-2="
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, SHORT_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, LONG_DATA_STR)); // redo SHORT_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.stringData(&testStrm, LONG_DATA_STR);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, LONG_DATA_STR)); // redo LONG_DATA_STR encoding
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.endElement(&testStrm); // </long-test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // redo the </long-test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	// ************************

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.endElement(&testStrm); // </test>
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // redo the </test>
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	savedContext = testStrm.context;
	savedNonTerminalIndex = testStrm.gStack->currNonTermID;
	tmp_err_code = serialize.endDocument(&testStrm);
	if(tmp_err_code == EXIP_BUFFER_END_REACHED)
	{
		testStrm.context = savedContext;
		testStrm.gStack->currNonTermID = savedNonTerminalIndex;
		TRY_CATCH_ENCODE(flushEXIData(&testStrm, flushBuf + *strmSize, buf_size - *strmSize, &bytesFlushed));
		*strmSize += bytesFlushed;
		TRY_CATCH_ENCODE(serialize.endDocument(&testStrm));
	}
	else if(tmp_err_code != EXIP_OK)
		return tmp_err_code;

	if(buf_size - *strmSize < (int)testStrm.buffer.bufContent)
		return EXIP_UNEXPECTED_ERROR;

	memcpy(flushBuf + *strmSize, testStrm.buffer.buf, testStrm.buffer.bufContent);
	*strmSize += testStrm.buffer.bufContent;

	// VI: Free the memory allocated by the EXI stream object
	TRY_CATCH_ENCODE(serialize.closeEXIStream(&testStrm));

	return EXIP_OK;
}

#define BN_STR_SIZE  50
#define ALL_STR_SIZE 20

typedef struct
{
	char n[ALL_STR_SIZE];  // "" for N/A
	char u[ALL_STR_SIZE];  // "" for N/A
	Float v;     // Float.exponent == INT16_MAX for N/A
	char sv[ALL_STR_SIZE]; // "" for N/A
	unsigned char bv; // boolean: 0 False, 1 true, else N/A
	Decimal s;   // Decimal.exponent == INT16_MAX for N/A
	int t;       // INT_MAX for N/A
	int ut;      // INT_MAX for N/A
} senml_elem;

typedef struct
{
	char bn[BN_STR_SIZE]; // "" for N/A
	long bt;     // LONG_MAX for N/A
	int version; // -1 for N/A
	char bu[ALL_STR_SIZE]; // "" for N/A
	senml_elem* eArray;   // Statically assigned array
	size_t eArrayCount; // The number of e elements in the array
	size_t eArraySize; // The total number of elements allocated in the array
} senml;


/**
 * Given an input of senmlData, it encodes an EXI stream (using default EXI options)
 * in buf and returns the size of the resultion stream in size.
 */
errorCode encodeSenML(EXIPSchema* schema, senml senmlData, char* buf, int buflen, size_t* size);

/**
 * Given an input EXI stream of SenML data (using default EXI options),
 * it decodes the data from the stream into senmlData output argument.
 */
errorCode decodeSenML(EXIPSchema* schema, char* buf, int buflen, senml* senmlData);

const String NS_SENML_STR = {"urn:ietf:params:xml:ns:senml", 28};
const String NS_EMPTY_STR = {NULL, 0};

const String ELEM_E_STR = {"e", 1};
const String ELEM_SENML_STR = {"senml", 5};

const String ATTR_BN_STR = {"bn", 2};
const String ATTR_BT_STR = {"bt", 2};
const String ATTR_BU_STR = {"bu", 2};
const String ATTR_VER_STR = {"ver", 3};

const String ATTR_N_STR = {"n", 1};
const String ATTR_U_STR = {"u", 1};
const String ATTR_V_STR = {"v", 1};
const String ATTR_SV_STR = {"sv", 2};
const String ATTR_BV_STR = {"bv", 2};
const String ATTR_S_STR = {"s", 1};
const String ATTR_T_STR = {"t", 1};
const String ATTR_UT_STR = {"ut", 2};

errorCode encodeSenML(EXIPSchema* schema, senml senmlData, char* buf, int buflen, size_t* size)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	EXIStream testStrm;
	String uri;
	String ln;
	QName qname = {&uri, &ln, NULL};
	BinaryBuffer buffer;
	EXITypeClass valueType;
	size_t e;
	String chVal;

	buffer.buf = buf;
	buffer.bufLen = buflen;
	buffer.bufContent = buflen;

	// Serialization steps:

	// I: First initialize the header of the stream
	serialize.initHeader(&testStrm);

	// II: Set any options in the header (including schemaID and schemaIDMode), if different from the defaults.
	testStrm.header.has_options = TRUE;

	// III: Define an external stream for the output if any, otherwise set to NULL
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	// IV: Initialize the stream
	TRY_CATCH_ENCODE(serialize.initStream(&testStrm, buffer, schema));

	// V: Start building the stream step by step: header, document, element etc...
	TRY_CATCH_ENCODE(serialize.exiHeader(&testStrm));

	TRY_CATCH_ENCODE(serialize.startDocument(&testStrm));

	qname.uri = &NS_SENML_STR;
	qname.localName = &ELEM_SENML_STR;
	TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // <senml>

	if(senmlData.bn[0] != '\0')
	{
		qname.uri = &NS_EMPTY_STR;
		qname.localName = &ATTR_BN_STR;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // bn=""

		TRY_CATCH_ENCODE(asciiToString(senmlData.bn, &chVal, &testStrm.memList, FALSE));
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
	}

	if(senmlData.bt != LONG_MAX)
	{
		qname.uri = &NS_EMPTY_STR;
		qname.localName = &ATTR_BT_STR;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // bt=""

		TRY_CATCH_ENCODE(serialize.intData(&testStrm, (Integer) senmlData.bt));
	}

	if(senmlData.bu[0] != '\0')
	{
		qname.uri = &NS_EMPTY_STR;
		qname.localName = &ATTR_BU_STR;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // bu=""
		TRY_CATCH_ENCODE(asciiToString(senmlData.bu, &chVal, &testStrm.memList, FALSE));
		TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
	}

	if(senmlData.version != -1)
	{
		qname.uri = &NS_EMPTY_STR;
		qname.localName = &ATTR_VER_STR;
		TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // ver=""
		TRY_CATCH_ENCODE(serialize.intData(&testStrm, (Integer) senmlData.version));
	}

	for(e = 0; e < senmlData.eArrayCount; e++)
	{
		qname.uri = &NS_SENML_STR;
		qname.localName = &ELEM_E_STR;
		TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType)); // <e>

		if(senmlData.eArray[e].bv == 0 || senmlData.eArray[e].bv == 1)
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_BV_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // bv=""
			TRY_CATCH_ENCODE(serialize.booleanData(&testStrm, (boolean) senmlData.eArray[e].bv));
		}

		if(senmlData.eArray[e].n[0] != '\0')
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_N_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // n=""
			TRY_CATCH_ENCODE(asciiToString(senmlData.eArray[e].n, &chVal, &testStrm.memList, FALSE));
			TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
		}

		if(senmlData.eArray[e].s.exponent != INT16_MAX)
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_S_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // s=""
			TRY_CATCH_ENCODE(serialize.decimalData(&testStrm, senmlData.eArray[e].s));
		}

		if(senmlData.eArray[e].sv[0] != '\0')
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_SV_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // sv=""
			TRY_CATCH_ENCODE(asciiToString(senmlData.eArray[e].sv, &chVal, &testStrm.memList, FALSE));
			TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
		}

		if(senmlData.eArray[e].t != INT_MAX)
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_T_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // t=""
			TRY_CATCH_ENCODE(serialize.intData(&testStrm, (Integer) senmlData.eArray[e].t));
		}

		if(senmlData.eArray[e].u[0] != '\0')
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_U_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // u=""
			TRY_CATCH_ENCODE(asciiToString(senmlData.eArray[e].u, &chVal, &testStrm.memList, FALSE));
			TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
		}

		if(senmlData.eArray[e].ut != INT_MAX)
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_UT_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // ut=""
			TRY_CATCH_ENCODE(serialize.intData(&testStrm, (Integer) senmlData.eArray[e].ut));
		}

		if(senmlData.eArray[e].v.exponent != INT16_MAX)
		{
			qname.uri = &NS_EMPTY_STR;
			qname.localName = &ATTR_V_STR;
			TRY_CATCH_ENCODE(serialize.attribute(&testStrm, qname, TRUE, &valueType)); // v=""
			TRY_CATCH_ENCODE(serialize.floatData(&testStrm, senmlData.eArray[e].v));
		}

		TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // </e>
	}

	TRY_CATCH_ENCODE(serialize.endElement(&testStrm)); // </senml>

	TRY_CATCH_ENCODE(serialize.endDocument(&testStrm));

	// VI: Free the memory allocated by the EXI stream object
	TRY_CATCH_ENCODE(serialize.closeEXIStream(&testStrm));

	*size = testStrm.buffer.bufContent;

	return tmp_err_code;
}

typedef enum {
	BN   = 0,
	BT   = 1,
	BU   = 2,
	VER  = 3,
	BV   = 4,
	N    = 5,
	S    = 6,
	SV   = 7,
	T    = 8,
	U    = 9,
	UT  = 10,
	V   = 11,
	NON = 12
} Attr;

typedef enum {
	ELEM_SEN_ML = 0,
	ELEM_E      = 1,
	ELEM_NON    = 2
} Elem;

typedef struct
{
	senml* data;
	Attr currAttr;
	Elem currElem;
	int eIndex;
} AppData;

static errorCode sample_startElement(QName qname, void* app_data);
static errorCode sample_attribute(QName qname, void* app_data);
static errorCode sample_stringData(const String value, void* app_data);
static errorCode sample_floatData(Float fl_val, void* app_data);
static errorCode sample_booleanData(boolean bool_val, void* app_data);
static errorCode sample_decimalData(Decimal value, void* app_data);
static errorCode sample_intData(Integer int_val, void* app_data);

errorCode decodeSenML(EXIPSchema* schema, char* buf, int buflen, senml* senmlData)
{
	Parser testParser;
	BinaryBuffer buffer;
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	AppData parsingData;

	buffer.buf = buf;
	buffer.bufLen = buflen;
	buffer.bufContent = buflen;
	// Parsing steps:

	// I: First, define an external stream for the input to the parser if any, otherwise set to NULL
	buffer.ioStrm.readWriteToStream = NULL;
	buffer.ioStrm.stream = NULL;

	parsingData.currElem = ELEM_NON;
	parsingData.currAttr = NON;
	parsingData.data = senmlData;
	parsingData.eIndex = -1;
	senmlData->eArrayCount = 0;

	// II: Second, initialize the parser object
	TRY(initParser(&testParser, buffer, &parsingData));

	// III: Initialize the parsing data and hook the callback handlers to the parser object.
	//      If out-of-band options are defined use testParser.strm.header.opts to set them

	testParser.handler.startElement = sample_startElement;
	testParser.handler.attribute = sample_attribute;
	testParser.handler.stringData = sample_stringData;
	testParser.handler.floatData = sample_floatData;
	testParser.handler.booleanData = sample_booleanData;
	testParser.handler.decimalData = sample_decimalData;
	testParser.handler.intData = sample_intData;

	// IV: Parse the header of the stream

	TRY(parseHeader(&testParser, FALSE));

	// IV.1: Set the schema to be used for parsing.
	// The schemaID mode and schemaID field can be read at
	// parser.strm.header.opts.schemaIDMode and
	// parser.strm.header.opts.schemaID respectively
	// If schemaless mode, use setSchema(&parser, NULL);

	TRY(setSchema(&testParser, schema));

	// V: Parse the body of the EXI stream

	while(tmp_err_code == EXIP_OK)
	{
		tmp_err_code = parseNext(&testParser);
	}

	// VI: Free the memory allocated by the parser

	destroyParser(&testParser);

	if(tmp_err_code == EXIP_PARSING_COMPLETE)
		return EXIP_OK;
	else
		return tmp_err_code;
}

static errorCode sample_startElement(QName qname, void* app_data)
{
	AppData* appD = (AppData*) app_data;

	if(appD->currElem == ELEM_NON)
	{
		// must senml
		if(stringCompare(*qname.uri, NS_SENML_STR) == 0 && stringCompare(*qname.localName, ELEM_SENML_STR) == 0)
		{
			appD->currElem = ELEM_SEN_ML;
		}
		else
			return EXIP_HANDLER_STOP;
	}
	else if (appD->currElem == ELEM_SEN_ML)
	{
		// must e
		if(stringCompare(*qname.uri, NS_SENML_STR) == 0 && stringCompare(*qname.localName, ELEM_E_STR) == 0)
		{
			appD->currElem = ELEM_E;
		}
		else
			return EXIP_HANDLER_STOP;

	}

	if (appD->currElem == ELEM_E)
	{
		appD->data->eArrayCount += 1;
		if(appD->data->eArrayCount > appD->data->eArraySize)
			return EXIP_HANDLER_STOP;

		appD->eIndex += 1;
	}

	return EXIP_OK;
}

static errorCode sample_attribute(QName qname, void* app_data)
{
	AppData* appD = (AppData*) app_data;

	// must have empty namespace
	if(stringCompare(*qname.uri, NS_EMPTY_STR) != 0)
		return EXIP_HANDLER_STOP;

	if(appD->currElem == ELEM_SEN_ML)
	{
		if(stringCompare(*qname.localName, ATTR_BN_STR) == 0)
			appD->currAttr = BN;
		else if(stringCompare(*qname.localName, ATTR_BT_STR) == 0)
			appD->currAttr = BT;
		else if(stringCompare(*qname.localName, ATTR_BU_STR) == 0)
			appD->currAttr = BU;
		else if(stringCompare(*qname.localName, ATTR_VER_STR) == 0)
			appD->currAttr = VER;
	}
	else if(appD->currElem == ELEM_E)
	{
		if(stringCompare(*qname.localName, ATTR_N_STR) == 0)
			appD->currAttr = N;
		else if(stringCompare(*qname.localName, ATTR_U_STR) == 0)
			appD->currAttr = U;
		else if(stringCompare(*qname.localName, ATTR_V_STR) == 0)
			appD->currAttr = V;
		else if(stringCompare(*qname.localName, ATTR_SV_STR) == 0)
			appD->currAttr = SV;
		else if(stringCompare(*qname.localName, ATTR_BV_STR) == 0)
			appD->currAttr = BV;
		else if(stringCompare(*qname.localName, ATTR_S_STR) == 0)
			appD->currAttr = S;
		else if(stringCompare(*qname.localName, ATTR_T_STR) == 0)
			appD->currAttr = T;
		else if(stringCompare(*qname.localName, ATTR_UT_STR) == 0)
			appD->currAttr = UT;
	}
	else
		return EXIP_HANDLER_STOP;

	return EXIP_OK;
}

static errorCode sample_stringData(const String value, void* app_data)
{
	AppData* appD = (AppData*) app_data;

	switch(appD->currAttr)
	{
		case BN:
			if(value.length < BN_STR_SIZE)
			{
				memcpy(appD->data->bn, value.str, value.length);
				appD->data->bn[value.length] = '\0';
			}
			else
				return EXIP_HANDLER_STOP;
		break;
		case BU:
			if(value.length < ALL_STR_SIZE)
			{
				memcpy(appD->data->bu, value.str, value.length);
				appD->data->bu[value.length] = '\0';
			}
			else
				return EXIP_HANDLER_STOP;
		break;
		case N:
			if(value.length < ALL_STR_SIZE)
			{
				memcpy(appD->data->eArray[appD->eIndex].n, value.str, value.length);
				appD->data->eArray[appD->eIndex].n[value.length] = '\0';
			}
			else
				return EXIP_HANDLER_STOP;
		break;
		case U:
			if(value.length < ALL_STR_SIZE)
			{
				memcpy(appD->data->eArray[appD->eIndex].u, value.str, value.length);
				appD->data->eArray[appD->eIndex].u[value.length] = '\0';
			}
			else
				return EXIP_HANDLER_STOP;
		break;
		case SV:
			if(value.length < ALL_STR_SIZE)
			{
				memcpy(appD->data->eArray[appD->eIndex].sv, value.str, value.length);
				appD->data->eArray[appD->eIndex].sv[value.length] = '\0';
			}
			else
				return EXIP_HANDLER_STOP;
		break;
		default:
			return EXIP_HANDLER_STOP;
	}

	return EXIP_OK;
}

static errorCode sample_floatData(Float fl_val, void* app_data)
{
	AppData* appD = (AppData*) app_data;

	if(appD->currAttr == V)
	{
		appD->data->eArray[appD->eIndex].v = fl_val;
	}
	else
		return EXIP_HANDLER_STOP;

	return EXIP_OK;
}

static errorCode sample_booleanData(boolean bool_val, void* app_data)
{
	AppData* appD = (AppData*) app_data;

	if(appD->currAttr == BV)
	{
		appD->data->eArray[appD->eIndex].bv = bool_val;
	}
	else
		return EXIP_HANDLER_STOP;

	return EXIP_OK;
}

static errorCode sample_decimalData(Decimal value, void* app_data)
{
	AppData* appD = (AppData*) app_data;

	if(appD->currAttr == S)
	{
		appD->data->eArray[appD->eIndex].s = value;
	}
	else
		return EXIP_HANDLER_STOP;

	return EXIP_OK;
}

static errorCode sample_intData(Integer int_val, void* app_data)
{
	AppData* appD = (AppData*) app_data;

	switch(appD->currAttr)
	{
		case BT:
			appD->data->bt = int_val;
		break;
		case VER:
			appD->data->version = int_val;
		break;
		case T:
			appD->data->eArray[appD->eIndex].t = int_val;
		break;
		case UT:
			appD->data->eArray[appD->eIndex].ut = int_val;
		break;
		default:
			return EXIP_HANDLER_STOP;
	}
	return EXIP_OK;
}

#define E_ELEM_COUNT   7  // The number of e elems in the senML to be encoded is 7

START_TEST (test_various_senml)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	char buf[OUTPUT_BUFFER_SIZE];
	char* schemafname[1] = {"exip/SenML-xsd.exi"};
	EXIPSchema schema;
	size_t exiSize = 0;
	senml_elem eArr[E_ELEM_COUNT];
	senml senML_instance;
	senml_elem eArrParsed[E_ELEM_COUNT];
	senml senMLParsed;
	int i;

	parseSchema(schemafname, 1, &schema);

	strcpy(senML_instance.bn, "urn:dev:mac:0024befffe804ff1");
	senML_instance.bt = 1415355691;
	senML_instance.version = 1;
	senML_instance.bu[0] = '\0';
	senML_instance.eArrayCount = E_ELEM_COUNT;
	senML_instance.eArraySize = E_ELEM_COUNT;
	senML_instance.eArray = eArr;

	// E elem 0
	strcpy(eArr[0].n, "pktid");
	strcpy(eArr[0].u, "count");
	eArr[0].v.mantissa = 1;
	eArr[0].v.exponent = 0;

	// E elem 1
	strcpy(eArr[1].n, "rpm");
	strcpy(eArr[1].u, "r/m");
	eArr[1].v.mantissa = 352;
	eArr[1].v.exponent = 0;

	// E elem 2
	strcpy(eArr[2].n, "rpm_av");
	strcpy(eArr[2].u, "r/m");
	eArr[2].v.mantissa = 352;
	eArr[2].v.exponent = 0;

	// E elem 3
	strcpy(eArr[3].n, "totrounds");
	strcpy(eArr[3].u, "count");
	eArr[3].v.mantissa = 461;
	eArr[3].v.exponent = 3;   // 461000

	// E elem 4
	strcpy(eArr[4].n, "totrounds_r");
	strcpy(eArr[4].u, "count");
	eArr[4].v.mantissa = 0;
	eArr[4].v.exponent = 0;

	// E elem 5
	strcpy(eArr[5].n, "bearingtemp");
	strcpy(eArr[5].u, "Cel");
	eArr[5].v.mantissa = 454;
	eArr[5].v.exponent = -1; // 45.4

	// E elem 6
	strcpy(eArr[6].n, "rssi");
	strcpy(eArr[6].u, "%");
	eArr[6].v.mantissa = 9;
	eArr[6].v.exponent = 1; // 90

	// All the other fileds are set to N/A
	for(i = 0; i < E_ELEM_COUNT; i++)
	{
		eArr[i].bv = 5;
		eArr[i].s.exponent = INT16_MAX;
		eArr[i].sv[0] = '\0';
		eArr[i].t = INT_MAX;
		eArr[i].ut = INT_MAX;
	}

	tmp_err_code = encodeSenML(&schema, senML_instance, buf, OUTPUT_BUFFER_SIZE, &exiSize);
	fail_unless(tmp_err_code == EXIP_OK, "There is an error in the encoding of an EXI SenML stream");
	fail_unless(exiSize > 0, "Encoding SenML produces empty streams.");

	senMLParsed.eArray = eArrParsed;
	senMLParsed.bn[0] = '\0';
	senMLParsed.bt = LONG_MAX;
	senMLParsed.version = -1;
	senMLParsed.bu[0] = '\0';
	senMLParsed.eArrayCount = 0;
	senMLParsed.eArraySize = E_ELEM_COUNT;
	senMLParsed.eArray = eArr;

	for(i = 0; i < E_ELEM_COUNT; i++)
	{
		eArrParsed[i].n[0] = '\0';
		eArrParsed[i].u[0] = '\0';
		eArrParsed[i].v.exponent = INT16_MAX;
		eArrParsed[i].bv = 5;
		eArrParsed[i].s.exponent = INT16_MAX;
		eArrParsed[i].sv[0] = '\0';
		eArrParsed[i].t = INT_MAX;
		eArrParsed[i].ut = INT_MAX;
	}

	tmp_err_code = decodeSenML(&schema, buf, OUTPUT_BUFFER_SIZE, &senMLParsed);
	destroySchema(&schema);
	fail_unless(tmp_err_code == EXIP_OK, "There is an error in the decoding of an EXI SenML stream");
	fail_unless(!strcmp(senMLParsed.bn, senML_instance.bn), "SenML BN value error");
	fail_unless(senMLParsed.bt == senML_instance.bt, "SenML BT value error");
	fail_unless(senMLParsed.version == senML_instance.version, "SenML version value error");

	for(i = 0; i < (int)senMLParsed.eArrayCount; i++)
	{
		fail_unless(!strcmp(senMLParsed.eArray[i].n, senML_instance.eArray[i].n), "SenML N value error");
		fail_unless(!strcmp(senMLParsed.eArray[i].u, senML_instance.eArray[i].u), "SenML U value error");
		fail_unless(senMLParsed.eArray[i].v.mantissa == senML_instance.eArray[i].v.mantissa, "SenML V value error");
		fail_unless(senMLParsed.eArray[i].v.exponent == senML_instance.eArray[i].v.exponent, "SenML V value error");
	}

}
END_TEST

/* END: Schema-mode tests */

/* Helper functions */
static size_t writeFileOutputStream(void* buf, size_t readSize, void* stream)
{
	FILE *outfile = (FILE*) stream;
	return fwrite(buf, 1, readSize, outfile);
}

static size_t readFileInputStream(void* buf, size_t readSize, void* stream)
{
	FILE *infile = (FILE*) stream;
	return fread(buf, 1, readSize, infile);
}

static void parseSchema(char** xsdList, int count, EXIPSchema* schema)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	FILE *schemaFile;
	BinaryBuffer buffer[MAX_XSD_FILES_COUNT]; // up to 10 XSD files
	size_t pathlen = strlen(dataDir);
	char exipath[MAX_PATH_LEN + strlen(xsdList[0])];
	int i;

	for (i = 0; i < count; i++)
	{
		memcpy(exipath, dataDir, pathlen);
		exipath[pathlen] = '/';
		memcpy(&exipath[pathlen+1], xsdList[i], strlen(xsdList[i])+1);
		schemaFile = fopen(exipath, "rb" );
		if(!schemaFile)
		{
			fail("Unable to open file %s", exipath);
			return;
		}
		else
		{
			//Get file length
			fseek(schemaFile, 0, SEEK_END);
			buffer[i].bufLen = ftell(schemaFile) + 1;
			fseek(schemaFile, 0, SEEK_SET);

			//Allocate memory
			buffer[i].buf = (char *) malloc(buffer[i].bufLen);
			if (!buffer[i].buf)
			{
				fclose(schemaFile);
				fail("Memory allocation error!");
			}

			//Read file contents into buffer
			fread(buffer[i].buf, buffer[i].bufLen, 1, schemaFile);
			fclose(schemaFile);

			buffer[i].bufContent = buffer[i].bufLen;
			buffer[i].ioStrm.readWriteToStream = NULL;
			buffer[i].ioStrm.stream = NULL;
		}
	}

	// Generate the EXI grammars based on the schema information
	tmp_err_code = generateSchemaInformedGrammars(buffer, count, SCHEMA_FORMAT_XSD_EXI, NULL, schema, NULL);

	for(i = 0; i < count; i++)
	{
		free(buffer[i].buf);
	}

	if(tmp_err_code != EXIP_OK)
	{
		fail("\nGrammar generation error occurred: %d", tmp_err_code);
	}
}


Suite* exip_suite(void)
{
	Suite *s = suite_create("EXIP");
	{
		/* Schema-less test case */
		TCase *tc_SchLess = tcase_create ("SchemaLess");
		tcase_add_test (tc_SchLess, test_default_options);
		tcase_add_test (tc_SchLess, test_fragment_option);
		tcase_add_test (tc_SchLess, test_value_part_zero);
		tcase_add_test (tc_SchLess, test_recursive_defs);
		tcase_add_test (tc_SchLess, test_built_in_dynamic_types);
		suite_add_tcase (s, tc_SchLess);
	}
	{
		/* Schema-mode test case */
		TCase *tc_Schema = tcase_create ("Schema-mode");
		tcase_add_test (tc_Schema, test_large_doc_str_pattern);
		tcase_add_test (tc_Schema, test_substitution_groups);
		tcase_add_test (tc_Schema, test_non_blocking_streaming);
		tcase_add_test (tc_Schema, test_non_blocking_streaming_bytealigned);
		tcase_add_test (tc_Schema, test_various_senml);
		suite_add_tcase (s, tc_Schema);
	}

	return s;
}

int main (int argc, char *argv[])
{
	int number_failed;
	Suite *s = exip_suite();
	SRunner *sr = srunner_create (s);

	if (argc < 2)
	{
		printf("ERR: Expected test data directory\n");
		exit(1);
	}
	if (strlen(argv[1]) > MAX_PATH_LEN)
	{
		printf("ERR: Test data pathname too long: %u", (unsigned int) strlen(argv[1]));
		exit(1);
	}

	dataDir = argv[1];
	srunner_set_fork_status(sr, CK_NOFORK);
#ifdef _MSC_VER
	srunner_set_fork_status(sr, CK_NOFORK);
#endif
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

