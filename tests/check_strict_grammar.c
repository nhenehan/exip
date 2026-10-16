/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file check_strict_grammar.c
 * @brief Tests decoding documents using strict grammar
 *
 * @date Mar 29, 2012
 * @author Ken Bannister
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: check_strict_grammar.c 360 2015-04-19 19:44:06Z kjussakov $
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "EXISerializer.h"
#include "EXIParser.h"
#include "stringManipulate.h"
#include "grammarGenerator.h"
#include "memManagement.h"
#include "sTables.h"

#define INPUT_BUFFER_SIZE 200
#define OUTPUT_BUFFER_SIZE 200
#define MAX_PATH_LEN 200

/* Location for external test data */
static char *dataDir;

struct appData {
    unsigned int eventCount;
    unsigned short expectAttributeData;
    AllocList allocList;
    String eventCode;
    String uri;
    String localName;
};
typedef struct appData appData;

/* Helper functions */

size_t readFileInputStream(void* buf, size_t readSize, void* stream) {
    FILE *infile = (FILE*) stream;
    return fread(buf, 1, readSize, infile);
}

size_t writeFileOutputStream(void* buf, size_t readSize, void* stream) {
    FILE *outfile = (FILE*) stream;
    return fwrite(buf, 1, readSize, outfile);
}

static void parseSchema(const char* fileName, EXIPSchema* schema) {
    FILE *schemaFile;
    BinaryBuffer buffer;
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    size_t pathlen = strlen(dataDir);
    char exipath[MAX_PATH_LEN + strlen(fileName)];

    memcpy(exipath, dataDir, pathlen);
    exipath[pathlen] = '/';
    memcpy(&exipath[pathlen + 1], fileName, strlen(fileName) + 1);
    schemaFile = fopen(exipath, "rb");
    if (!schemaFile) {
        fail("Unable to open file %s", exipath);
    } else {
        //Get file length
        fseek(schemaFile, 0, SEEK_END);
        buffer.bufLen = ftell(schemaFile) + 1;
        fseek(schemaFile, 0, SEEK_SET);

        //Allocate memory
        buffer.buf = (char *) malloc(buffer.bufLen);
        if (!buffer.buf) {
            fclose(schemaFile);
            fail("Memory allocation error!");
        }

        //Read file contents into buffer
        if (fread(buffer.buf, 1, buffer.bufLen - 1, schemaFile) != buffer.bufLen - 1) {
            fclose(schemaFile);
            fail("Unable to read the schema file");
        }
        fclose(schemaFile);

        buffer.bufContent = buffer.bufLen;
        buffer.ioStrm.readWriteToStream = NULL;
        buffer.ioStrm.stream = NULL;

        tmp_err_code = generateSchemaInformedGrammars(&buffer, 1, SCHEMA_FORMAT_XSD_EXI, NULL, schema, NULL);

        if (tmp_err_code != EXIP_OK) {
            fail("\n Error reading schema: %d", tmp_err_code);
        }

        free(buffer.buf);
    }
}

/* Document callbacks */

static errorCode sample_fatalError(const errorCode code, const char* msg, void* app_data) {
	EXIP_UNUSED(app_data);
    printf("\n%3d : FATAL ERROR: %s\n", code, msg);
    return EXIP_HANDLER_STOP;
}

static errorCode sample_startDocument(void* app_data) {
    appData* appD = (appData*) app_data;
    asciiToString("SD", &appD->eventCode, &appD->allocList, TRUE);

    return EXIP_OK;
}

static errorCode sample_endDocument(void* app_data) {
    appData* appD = (appData*) app_data;
    asciiToString("ED", &appD->eventCode, &appD->allocList, TRUE);

    return EXIP_OK;
}

static errorCode sample_startElement(QName qname, void* app_data) {
    appData* appD = (appData*) app_data;
    asciiToString("SE", &appD->eventCode, &appD->allocList, TRUE);
    cloneStringManaged(qname.uri, &appD->uri, &appD->allocList);
    cloneStringManaged(qname.localName, &appD->localName, &appD->allocList);

    return EXIP_OK;
}

static errorCode sample_endElement(void* app_data) {
    appData* appD = (appData*) app_data;
    asciiToString("EE", &appD->eventCode, &appD->allocList, TRUE);

    return EXIP_OK;
}

static errorCode sample_attribute(QName qname, void* app_data) {
	EXIP_UNUSED(qname);
	EXIP_UNUSED(app_data);
    appData* appD = (appData*) app_data;
    asciiToString("AT", &appD->eventCode, &appD->allocList, TRUE);

    /*
    printString(qname.uri);
    printf(" ");
    printString(qname.localName);
    printf("=\"");
     */

    appD->expectAttributeData = 1;

    return EXIP_OK;
}

static errorCode sample_stringData(const String value, void* app_data) {
	EXIP_UNUSED(value);
	EXIP_UNUSED(app_data);
    appData* appD = (appData*) app_data;
    if (appD->expectAttributeData) {
        asciiToString("AT", &appD->eventCode, &appD->allocList, TRUE);
        /*
        printString(&value);
        printf("\"\n");
         */
        appD->expectAttributeData = 0;
    } else {
        asciiToString("CH", &appD->eventCode, &appD->allocList, TRUE);
        /*
        printString(&value);
        printf("\n");
         */
    }

    return EXIP_OK;
}

static errorCode sample_decimalData(Decimal value, void* app_data) {
	EXIP_UNUSED(value);
	EXIP_UNUSED(app_data);
    appData* appD = (appData*) app_data;
    if (appD->expectAttributeData) {
        asciiToString("AT", &appD->eventCode, &appD->allocList, TRUE);
        /*
        printf("%.1f\"\n", (double) value);
         */
        appD->expectAttributeData = 0;
    } else {
        asciiToString("CH", &appD->eventCode, &appD->allocList, TRUE);
    }

    return EXIP_OK;
}

static errorCode sample_intData(Integer int_val, void* app_data) {
	EXIP_UNUSED(int_val);
	EXIP_UNUSED(app_data);
    appData* appD = (appData*) app_data;
    /* char tmp_buf[30]; */
    if (appD->expectAttributeData) {
        asciiToString("AT", &appD->eventCode, &appD->allocList, TRUE);
        /*
        sprintf(tmp_buf, "%lld", int_val);
        printf("%s", tmp_buf);
        printf("\"\n");
         */
        appD->expectAttributeData = 0;
    } else {
        asciiToString("CH", &appD->eventCode, &appD->allocList, TRUE);
        /*
        sprintf(tmp_buf, "%lld", int_val);
        printf("%s", tmp_buf);
        printf("\n");
         */
    }

    return EXIP_OK;
}

static errorCode sample_floatData(Float fl_val, void* app_data) {
	EXIP_UNUSED(fl_val);
	EXIP_UNUSED(app_data);
    appData* appD = (appData*) app_data;
    /* char tmp_buf[30]; */
    if (appD->expectAttributeData) {
        asciiToString("AT", &appD->eventCode, &appD->allocList, TRUE);
        /*
        sprintf(tmp_buf, "%lldE%d", fl_val.mantissa, fl_val.exponent);
        printf("%s", tmp_buf);
        printf("\"\n");
         */
        appD->expectAttributeData = 0;
    } else {
        asciiToString("CH", &appD->eventCode, &appD->allocList, TRUE);
        /*
        printf("%3d CH ", appD->eventCount);
        sprintf(tmp_buf, "%lldE%d", fl_val.mantissa, fl_val.exponent);
        printf("%s", tmp_buf);
        printf("\n");
         */
    }

    return EXIP_OK;
}

/* Tests */

/* Compares document structure, including minOccurs/maxOccurs. */
START_TEST(test_acceptance_for_A_01) {
    EXIPSchema schema;
    FILE *infile;
    Parser testParser;
    char buf[INPUT_BUFFER_SIZE];
    const char *schemafname = "testStates/acceptance-xsd.exi";
    const char *exifname = "testStates/acceptance_a_01.exi";
    char exipath[MAX_PATH_LEN + strlen(exifname)];
    struct appData parsingData;
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    BinaryBuffer buffer;

    buffer.buf = buf;
    buffer.bufContent = 0;
    buffer.bufLen = INPUT_BUFFER_SIZE;

    // Parsing steps:

    // I.A: First, read in the schema
    parseSchema(schemafname, &schema);

    // I.B: Define an external stream for the input to the parser if any
    size_t pathlen = strlen(dataDir);
    memcpy(exipath, dataDir, pathlen);
    exipath[pathlen] = '/';
    memcpy(&exipath[pathlen + 1], exifname, strlen(exifname) + 1);

    infile = fopen(exipath, "rb");
    if (!infile)
        fail("Unable to open file %s", exipath);

    buffer.ioStrm.readWriteToStream = readFileInputStream;
    buffer.ioStrm.stream = infile;

    // II: Second, initialize the parser object
    tmp_err_code = initParser(&testParser, buffer, &parsingData);
    fail_unless(tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

    // III: Initialize the parsing data and hook the callback handlers to the parser object
    parsingData.eventCount = 0;
    parsingData.expectAttributeData = 0;
    if (EXIP_OK != initAllocList(&parsingData.allocList))
        fail("Memory allocation error!");


    testParser.handler.fatalError = sample_fatalError;
    testParser.handler.error = sample_fatalError;
    testParser.handler.startDocument = sample_startDocument;
    testParser.handler.endDocument = sample_endDocument;
    testParser.handler.startElement = sample_startElement;
    testParser.handler.attribute = sample_attribute;
    testParser.handler.stringData = sample_stringData;
    testParser.handler.endElement = sample_endElement;
    testParser.handler.decimalData = sample_decimalData;
    testParser.handler.intData = sample_intData;
    testParser.handler.floatData = sample_floatData;

    // IV: Parse the header of the stream
    tmp_err_code = parseHeader(&testParser, FALSE);
    fail_unless(tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

    tmp_err_code = setSchema(&testParser, &schema);
    fail_unless(tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);
    // V: Parse the body of the EXI stream
    while (tmp_err_code == EXIP_OK) {
        switch (parsingData.eventCount) {
            case 0:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SD"));
                break;
            case 1:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SE"));
                fail_unless(stringEqualToAscii(parsingData.uri, "urn:foo"));
                fail_unless(stringEqualToAscii(parsingData.localName, "A"));
                break;
            case 2:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SE"));
                fail_unless(stringEqualToAscii(parsingData.uri, "urn:foo"));
                fail_unless(stringEqualToAscii(parsingData.localName, "AB"));
                break;
            case 3:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "CH"));
                break;
            case 4:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "EE"));
                break;
            case 5:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SE"));
                fail_unless(stringEqualToAscii(parsingData.uri, "urn:foo"));
                fail_unless(stringEqualToAscii(parsingData.localName, "AC"));
                break;
            case 6:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "CH"));
                break;
            case 7:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "EE"));
                break;
            case 8:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SE"));
                fail_unless(stringEqualToAscii(parsingData.uri, "urn:foo"));
                fail_unless(stringEqualToAscii(parsingData.localName, "AC"));
                break;
            case 9:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "CH"));
                break;
            case 10:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "EE"));
                break;
            case 11:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SE"));
                fail_unless(stringEqualToAscii(parsingData.uri, "urn:foo"));
                fail_unless(stringEqualToAscii(parsingData.localName, "AD"));
                break;
            case 12:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "CH"));
                break;
            case 13:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "EE"));
                break;
            case 14:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SE"));
                fail_unless(stringEqualToAscii(parsingData.uri, "urn:foo"));
                fail_unless(stringEqualToAscii(parsingData.localName, "AE"));
                break;
            case 15:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "CH"));
                break;
            case 16:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "EE"));
                break;
            case 17:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "EE"));
                break;
            case 18:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "ED"));
                break;
            default:
                // Unexpected event count caught below.
                break;
        }
        tmp_err_code = parseNext(&testParser);

        parsingData.eventCount++;

    }

    fail_unless(stringEqualToAscii(parsingData.eventCode, "ED"));

    fail_unless(parsingData.eventCount == 18,
            "Unexpected event count: %u", parsingData.eventCount);

    // VI: Free the memory allocated by the parser object
    freeAllocList(&parsingData.allocList);
    destroyParser(&testParser);
    destroySchema(&schema);
    fclose(infile);
    fail_unless(tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
}

END_TEST

/* Verifies a single global element also used as a reference. */
START_TEST(test_acceptance_for_A_01_exip1) {
    EXIPSchema schema;
    FILE *infile;
    Parser testParser;
    char buf[INPUT_BUFFER_SIZE];
    const char *schemafname = "testStates/acceptance-xsd.exi";
    const char *exifname = "testStates/acceptance_a_01a.exi";
    char exipath[MAX_PATH_LEN + strlen(exifname)];
    struct appData parsingData;
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    BinaryBuffer buffer;

    buffer.buf = buf;
    buffer.bufContent = 0;
    buffer.bufLen = INPUT_BUFFER_SIZE;

    // Parsing steps:

    // I.A: First, read in the schema
    parseSchema(schemafname, &schema);

    // I.B: Define an external stream for the input to the parser if any
    size_t pathlen = strlen(dataDir);
    memcpy(exipath, dataDir, pathlen);
    exipath[pathlen] = '/';
    memcpy(&exipath[pathlen + 1], exifname, strlen(exifname) + 1);

    infile = fopen(exipath, "rb");
    if (!infile)
        fail("Unable to open file %s", exipath);

    buffer.ioStrm.readWriteToStream = readFileInputStream;
    buffer.ioStrm.stream = infile;

    // II: Second, initialize the parser object
    tmp_err_code = initParser(&testParser, buffer, &parsingData);
    fail_unless(tmp_err_code == EXIP_OK, "initParser returns an error code %d", tmp_err_code);

    // III: Initialize the parsing data and hook the callback handlers to the parser object
    parsingData.eventCount = 0;
    parsingData.expectAttributeData = 0;
    if (EXIP_OK != initAllocList(&parsingData.allocList))
        fail("Memory allocation error!");

    testParser.handler.fatalError = sample_fatalError;
    testParser.handler.error = sample_fatalError;
    testParser.handler.startDocument = sample_startDocument;
    testParser.handler.endDocument = sample_endDocument;
    testParser.handler.startElement = sample_startElement;
    testParser.handler.attribute = sample_attribute;
    testParser.handler.stringData = sample_stringData;
    testParser.handler.endElement = sample_endElement;
    testParser.handler.decimalData = sample_decimalData;
    testParser.handler.intData = sample_intData;
    testParser.handler.floatData = sample_floatData;

    // IV: Parse the header of the stream
    tmp_err_code = parseHeader(&testParser, FALSE);
    fail_unless(tmp_err_code == EXIP_OK, "parsing the header returns an error code %d", tmp_err_code);

    tmp_err_code = setSchema(&testParser, &schema);
    fail_unless(tmp_err_code == EXIP_OK, "setSchema() returns an error code %d", tmp_err_code);

    // V: Parse the body of the EXI stream
    while (tmp_err_code == EXIP_OK) {
        switch (parsingData.eventCount) {
            case 0:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SD"));
                break;
            case 1:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "SE"));
                fail_unless(stringEqualToAscii(parsingData.uri, "urn:foo"));
                fail_unless(stringEqualToAscii(parsingData.localName, "AB"));
                break;
            case 2:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "CH"));
                break;
            case 3:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "EE"));
                break;
            case 4:
                fail_unless(stringEqualToAscii(parsingData.eventCode, "ED"));
                break;
            default:
                // Unexpected event count caught below.
                break;
        }

        tmp_err_code = parseNext(&testParser);
        parsingData.eventCount++;
    }

    fail_unless(stringEqualToAscii(parsingData.eventCode, "ED"));

    fail_unless(parsingData.eventCount == 4,
            "Unexpected event count: %u", parsingData.eventCount);

    // VI: Free the memory allocated by the parser object
    freeAllocList(&parsingData.allocList);
    destroyParser(&testParser);
    destroySchema(&schema);
    fclose(infile);
    fail_unless(tmp_err_code == EXIP_PARSING_COMPLETE, "Error during parsing of the EXI body %d", tmp_err_code);
}

END_TEST

/* 
 * Verifies error when more elements than schema maxOccurs permits. Attempts 
 * to encode:
 * 
 * <A xmlns='urn:foo'>
 *   <AB/><AC/><AC/><AC/>
 * </A>
 */
START_TEST(test_acceptance_for_A_01b) {
    EXIPSchema schema;
    EXIStream testStrm;
    String uri;
    String ln;
    QName qname = {&uri, &ln, NULL};
    char buf[OUTPUT_BUFFER_SIZE];
    const char *schemafname = "testStates/acceptance-xsd.exi";
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    EXITypeClass valueType;

    const String NS_STR = {"urn:foo", 7};
    const String ELEM_A = {"A", 1};
    const String ELEM_AB = {"AB", 2};
    const String ELEM_AC = {"AC", 2};
    const String CH = {"", 0};

    BinaryBuffer buffer;
    buffer.buf = buf;
    buffer.bufLen = OUTPUT_BUFFER_SIZE;
    buffer.bufContent = 0;

    // Serialization steps:

    // I.A: First, read in the schema
    parseSchema(schemafname, &schema);

    // I: First initialize the header of the stream
    serialize.initHeader(&testStrm);

    // II: Set any options in the header, if different from the defaults
    testStrm.header.has_cookie = TRUE;
    testStrm.header.has_options = TRUE;
    testStrm.header.opts.valueMaxLength = 300;
    testStrm.header.opts.valuePartitionCapacity = 50;
    SET_STRICT(testStrm.header.opts.enumOpt);

    // III: Define an external stream for the output if any
    buffer.ioStrm.readWriteToStream = NULL;
    buffer.ioStrm.stream = NULL;

    // IV: Initialize the stream
    tmp_err_code = serialize.initStream(&testStrm, buffer, &schema);
    fail_unless(tmp_err_code == EXIP_OK, "initStream returns an error code %d", tmp_err_code);

    // V: Start building the stream step by step: header, document, element etc...
    tmp_err_code += serialize.exiHeader(&testStrm);

    tmp_err_code += serialize.startDocument(&testStrm);

    qname.uri = &NS_STR;
    qname.localName = &ELEM_A;
    tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
    fail_unless(tmp_err_code == EXIP_OK, "serialization returns an error code %d", tmp_err_code);

    qname.localName = &ELEM_AB;
    tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
    tmp_err_code += serialize.stringData(&testStrm, CH);
    tmp_err_code += serialize.endElement(&testStrm);
    fail_unless(tmp_err_code == EXIP_OK, "serialization returns an error code %d", tmp_err_code);

    qname.localName = &ELEM_AC;
    tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
    tmp_err_code += serialize.stringData(&testStrm, CH);
    tmp_err_code += serialize.endElement(&testStrm);
    fail_unless(tmp_err_code == EXIP_OK, "serialization returns an error code %d", tmp_err_code);

    tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
    tmp_err_code += serialize.stringData(&testStrm, CH);
    tmp_err_code += serialize.endElement(&testStrm);
    fail_unless(tmp_err_code == EXIP_OK, "serialization returns an error code %d", tmp_err_code);

    /* Expect failure when start third AC element */
    tmp_err_code += serialize.startElement(&testStrm, qname, &valueType);
    fail_unless(tmp_err_code == EXIP_INCONSISTENT_PROC_STATE,
            "Expected EXIP_INCONSISTENT_PROC_STATE, but returns an error code %d", tmp_err_code);

    // VI: Free the memory allocated by the EXI stream object
    tmp_err_code = serialize.closeEXIStream(&testStrm);
    destroySchema(&schema);
}
END_TEST

/* START THE LKAB DEMO SUIT*/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
typedef char error_code; // 0 - OK;  Error otherwise

struct timestamp {
    unsigned int year;
    unsigned int month;
    unsigned int mday;
    unsigned int hour;
    unsigned int min;
    unsigned int sec;
    unsigned int msec;
};

typedef struct timestamp Timestamp;

enum ValueType {
    Bool = 0,
    Long = 1
};

typedef enum ValueType ValueType;

enum Quality {
    Good = 0,
    Good_LocalOverride = 1,

    Uncertain = 2,
    Uncertain_LastUsable = 3,
    Uncertain_SensorCal = 4,
    Uncertain_EGUExeeded = 5,
    Uncertain_SubNormal = 6,

    Bad = 7,
    Bad_ConfigError = 8,
    Bad_NotConnected = 9,
    Bad_DeviceFailure = 10,
    Bad_SensorFailure = 11,
    Bad_CommFailureLastKnownAvailable = 12,
    Bad_CommFailure = 13,
    Bad_OutOfService = 14
};

typedef enum Quality Quality;

struct boolValue {
    Timestamp ts;
    Quality quality;
    unsigned char val;
};

typedef struct boolValue BoolValue;

struct processValueDesc {
    char name[50];
    ValueType type;
    unsigned char isReadOnly; // boolean
    char description[150];
};

typedef struct processValueDesc ProcessValueDesc;

struct devDescribtion {
    char id[50];
    char name[50];
    char type[50];
    char location[100];
    ProcessValueDesc processValue;
};

typedef struct devDescribtion DevDescribtion;

extern const EXISerializer serialize;

const String NS_STR = {"http://imc-aesop.eu/lkab-demo", 29};
const String NS_EMPTY_STR = {NULL, 0};

const String ELEM_BOOL_VAL_STR = {"BoolValue", 9};
const String ELEM_QUAL_STR = {"quality", 7};
const String ELEM_TIMESTAMP_STR = {"timestamp", 9};
const String ELEM_VALUE_STR = {"value", 5};

const String ELEM_DEV_DESC_STR = {"DeviceDescription", 17};
const String ELEM_ID_STR = {"id", 2};
const String ELEM_NAME_STR = {"name", 4};
const String ELEM_TYPE_STR = {"type", 4};

const String ELEM_LOCATION_STR = {"location", 8};
const String ELEM_PROSS_VAL_STR = {"processValues", 13};
const String ELEM_IS_READONLY_STR = {"isReadOnly", 10};
const String ELEM_DESC_STR = {"description", 11};

static String ENUM_DATA_QUALITY[] = {
    {"Good", 4},
    {"Good_LocalOverride", 18},
    {"Uncertain", 9},
    {"Uncertain_LastUsable", 20},
    {"Uncertain_SensorCal", 19},
    {"Uncertain_EGUExeeded", 20},
    {"Uncertain_SubNormal", 19},
    {"Bad", 3},
    {"Bad_ConfigError", 15},
    {"Bad_NotConnected", 16},
    {"Bad_DeviceFailure", 17},
    {"Bad_SensorFailure", 17},
    {"Bad_CommFailureLastKnownAvailable", 33},
    {"Bad_CommFailure", 15},
    {"Bad_OutOfService", 16}};

static String ENUM_DATA_VAL_TYPE[] = {
    {"Bool", 4},
    {"Long", 4}};

struct appDataLKAB {
    BoolValue val;
    DevDescribtion devDesc;
    unsigned int currElementNumber;
};

// Content Handler API
static errorCode lkab_fatalError(const errorCode code, const char* msg, void* app_data);
static errorCode lkab_startElement_io(QName qname, void* app_data);
static errorCode lkab_startElement_desc(QName qname, void* app_data);
static errorCode lkab_endElement(void* app_data);
static errorCode lkab_stringData_io(const String value, void* app_data);
static errorCode lkab_stringData_desc(const String value, void* app_data);
static errorCode lkab_booleanData_io(exip_bool bool_val, void* app_data);
static errorCode lkab_booleanData_desc(exip_bool bool_val, void* app_data);
static errorCode lkab_dateTimeData(EXIPDateTime dt_val, void* app_data);

/**
 * @brief Reads the time-stamp and value data from a EXI message
 *
 * @param[in] buf A buffer containing the EXI stream
 * @param[in] buf_size the size of the buffer in bytes
 * @param[out] val a time-stamp and bool (digital I/O) value read from the message
 * @return Error handling code
 */
static error_code parseIOMsg(char* buf, unsigned int buf_size, BoolValue *val);

/**
 * @brief Reads a DevDescribtion EXI message
 *
 * @param[in] buf A buffer containing the EXI stream
 * @param[in] buf_size the size of the buffer in bytes
 * @param[out] devDesc the description of the device to be read
 * @return Error handling code
 */
static error_code parseDevDescMsg(char* buf, unsigned int buf_size, DevDescribtion* devDesc);

/**
 * @brief Serialize an I/O EXI message
 *
 * @param[in, out] buf An empty buffer for storing the EXI stream
 * @param[in] buf_size the size of the buffer in bytes
 * @param[out] msg_size the size of the serialized message in bytes
 * @param[in] val the time-stamp and bool (digital I/O) value to be written to the message
 * @return Error handling code
 */
static error_code serializeIOMsg(char* buf, unsigned int buf_size, unsigned int* msg_size, BoolValue val);

/**
 * @brief Serialize a DevDescribtion EXI message
 *
 * @param[in, out] buf An empty buffer for storing the EXI stream
 * @param[in] buf_size the size of the buffer in bytes
 * @param[out] msg_size the size of the serialized message in bytes
 * @param[in] devDesc the description of the device to be written
 * @return Error handling code
 */
static error_code serializeDevDescMsg(char* buf, unsigned int buf_size, unsigned int* msg_size, DevDescribtion devDesc);

static error_code serializeIOMsg(char* buf, unsigned int buf_size, unsigned int* msg_size, BoolValue val) {
    EXIStream strm;
    String uri;
    String ln;
    QName qname = {&uri, &ln, NULL};
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    BinaryBuffer buffer;
    EXIPDateTime dt;
    EXIPSchema lkab_schema;
    const char *schemafname = "SchemaStrict/lkab-devices-xsd.exi";
    EXITypeClass valueType;

    buffer.buf = buf;
    buffer.bufLen = buf_size;
    buffer.bufContent = 0;

    // Serialization steps:

    // I.A: First, read in the schema
    parseSchema(schemafname, &lkab_schema);

    // I: First initialize the header of the stream
    serialize.initHeader(&strm);

    // II: Set any options in the header, if different from the defaults
    strm.header.has_options = TRUE;
    SET_STRICT(strm.header.opts.enumOpt);

    // III: Define an external stream for the output if any
    buffer.ioStrm.stream = NULL;
    buffer.ioStrm.readWriteToStream = NULL;

    // IV: Initialize the stream
    tmp_err_code = serialize.initStream(&strm, buffer, &lkab_schema);
    if (tmp_err_code != EXIP_OK)
        return tmp_err_code;

    // V: Start building the stream step by step: header, document, element etc...
    tmp_err_code += serialize.exiHeader(&strm);

    tmp_err_code += serialize.startDocument(&strm);

    qname.uri = &NS_STR;
    qname.localName = &ELEM_BOOL_VAL_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <BoolValue>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_TIMESTAMP_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <timeStamp>

    dt.presenceMask = FRACT_PRESENCE;

    dt.dateTime.tm_year = val.ts.year;
    dt.dateTime.tm_mon = val.ts.month;
    dt.dateTime.tm_mday = val.ts.mday;
    dt.dateTime.tm_hour = val.ts.hour;
    dt.dateTime.tm_min = val.ts.min;
    dt.dateTime.tm_sec = val.ts.sec;
    dt.fSecs.value = val.ts.msec;
    dt.fSecs.offset = 2;

    tmp_err_code += serialize.dateTimeData(&strm, dt);

    tmp_err_code += serialize.endElement(&strm); // </timeStamp>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_QUAL_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <quality>

    tmp_err_code += serialize.stringData(&strm, ENUM_DATA_QUALITY[val.quality]); // quality

    tmp_err_code += serialize.endElement(&strm); // </quality>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_VALUE_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <value>

    tmp_err_code += serialize.booleanData(&strm, val.val);

    tmp_err_code += serialize.endElement(&strm); // </value>

    tmp_err_code += serialize.endElement(&strm); // </BoolValue>

    tmp_err_code += serialize.endDocument(&strm);

    if (tmp_err_code != EXIP_OK)
        return tmp_err_code;

    *msg_size = strm.context.bufferIndx + 1;

    // VI: Free the memory allocated by the EXI stream object
    tmp_err_code = serialize.closeEXIStream(&strm);

    destroySchema(&lkab_schema);
    return EXIP_OK;
}

static error_code serializeDevDescMsg(char* buf, unsigned int buf_size, unsigned int* msg_size, DevDescribtion devDesc) {
    EXIStream strm;
    String uri;
    String ln;
    String ch;
    QName qname = {&uri, &ln, NULL};
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    BinaryBuffer buffer;
    EXIPSchema lkab_schema;
    const char *schemafname = "SchemaStrict/lkab-devices-xsd.exi";
    EXITypeClass valueType;

    buffer.buf = buf;
    buffer.bufLen = buf_size;
    buffer.bufContent = 0;

    // Serialization steps:

    // I.A: First, read in the schema
    parseSchema(schemafname, &lkab_schema);

    // I: First initialize the header of the stream
    serialize.initHeader(&strm);

    // II: Set any options in the header, if different from the defaults
    strm.header.has_options = TRUE;
    SET_STRICT(strm.header.opts.enumOpt);

    // III: Define an external stream for the output if any
    buffer.ioStrm.stream = NULL;
    buffer.ioStrm.readWriteToStream = NULL;

    // IV: Initialize the stream
    tmp_err_code = serialize.initStream(&strm, buffer, &lkab_schema);
    if (tmp_err_code != EXIP_OK)
        return tmp_err_code;

    // V: Start building the stream step by step: header, document, element etc...
    tmp_err_code += serialize.exiHeader(&strm);

    tmp_err_code += serialize.startDocument(&strm);

    qname.uri = &NS_STR;
    qname.localName = &ELEM_DEV_DESC_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <DeviceDescription>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_ID_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <id>

    ch.str = devDesc.id;
    ch.length = strlen(devDesc.id);
    tmp_err_code += serialize.stringData(&strm, ch); // device id

    tmp_err_code += serialize.endElement(&strm); // </id>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_NAME_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <name>

    ch.str = devDesc.name;
    ch.length = strlen(devDesc.name);
    tmp_err_code += serialize.stringData(&strm, ch); // device name

    tmp_err_code += serialize.endElement(&strm); // </name>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_TYPE_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <type>

    ch.str = devDesc.type;
    ch.length = strlen(devDesc.type);
    tmp_err_code += serialize.stringData(&strm, ch); // device type

    tmp_err_code += serialize.endElement(&strm); // </type>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_LOCATION_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <location>

    ch.str = devDesc.location;
    ch.length = strlen(devDesc.location);
    tmp_err_code += serialize.stringData(&strm, ch); // device location

    tmp_err_code += serialize.endElement(&strm); // </location>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_PROSS_VAL_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <processValues>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_NAME_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <name>

    ch.str = devDesc.processValue.name;
    ch.length = strlen(devDesc.processValue.name);
    tmp_err_code += serialize.stringData(&strm, ch); // processValues name

    tmp_err_code += serialize.endElement(&strm); // </name>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_TYPE_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <type>

    tmp_err_code += serialize.stringData(&strm, ENUM_DATA_VAL_TYPE[devDesc.processValue.type]); // processValues type

    tmp_err_code += serialize.endElement(&strm); // </type>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_IS_READONLY_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <isReadOnly>

    tmp_err_code += serialize.booleanData(&strm, 0); // processValues isReadOnly

    tmp_err_code += serialize.endElement(&strm); // </isReadOnly>

    qname.uri = &NS_STR;
    qname.localName = &ELEM_DESC_STR;
    tmp_err_code += serialize.startElement(&strm, qname, &valueType); // <description>

    ch.str = devDesc.processValue.description;
    ch.length = strlen(devDesc.processValue.description);
    tmp_err_code += serialize.stringData(&strm, ch); // processValues description

    tmp_err_code += serialize.endElement(&strm); // </description>

    tmp_err_code += serialize.endElement(&strm); // </processValues>

    tmp_err_code += serialize.endElement(&strm); // </DeviceDescription>

    tmp_err_code += serialize.endDocument(&strm);

    if (tmp_err_code != EXIP_OK)
        return tmp_err_code;

    *msg_size = strm.context.bufferIndx + 1;

    // VI: Free the memory allocated by the EXI stream object
    tmp_err_code = serialize.closeEXIStream(&strm);
    destroySchema(&lkab_schema);

    return EXIP_OK;
}

static error_code parseIOMsg(char* buf, unsigned int buf_size, BoolValue *val) {
    Parser lkabParser;
    BinaryBuffer buffer;
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    struct appDataLKAB parsingData;
    EXIPSchema lkab_schema;
    const char *schemafname = "SchemaStrict/lkab-devices-xsd.exi";

    buffer.buf = buf;
    buffer.bufLen = buf_size;
    buffer.bufContent = buf_size;
    // Parsing steps:

    // I.A: First, read in the schema
    parseSchema(schemafname, &lkab_schema);

    // I: First, define an external stream for the input to the parser if any
    buffer.ioStrm.stream = NULL;

    // II: Second, initialize the parser object
    tmp_err_code = initParser(&lkabParser, buffer, &parsingData);
    if (tmp_err_code != EXIP_OK)
        return tmp_err_code;

    // III: Initialize the parsing data and hook the callback handlers to the parser object

    parsingData.currElementNumber = 0;
    parsingData.val.quality = Good;
    parsingData.val.val = 0;
    parsingData.val.ts.year = 0;
    parsingData.val.ts.month = 0;
    parsingData.val.ts.mday = 0;
    parsingData.val.ts.hour = 0;
    parsingData.val.ts.min = 0;
    parsingData.val.ts.sec = 0;
    parsingData.val.ts.msec = 0;

    lkabParser.handler.fatalError = lkab_fatalError;
    lkabParser.handler.error = lkab_fatalError;
    lkabParser.handler.startElement = lkab_startElement_io;
    lkabParser.handler.stringData = lkab_stringData_io;
    lkabParser.handler.endElement = lkab_endElement;
    lkabParser.handler.booleanData = lkab_booleanData_io;
    lkabParser.handler.dateTimeData = lkab_dateTimeData;

    // IV: Parse the header of the stream

    tmp_err_code = parseHeader(&lkabParser, FALSE);

    tmp_err_code = setSchema(&lkabParser, &lkab_schema);
    // V: Parse the body of the EXI stream

    while (tmp_err_code == EXIP_OK) {
        tmp_err_code = parseNext(&lkabParser);
    }

    // VI: Free the memory allocated by the parser object

    destroyParser(&lkabParser);

    val->ts = parsingData.val.ts;
    val->val = parsingData.val.val;
    val->quality = parsingData.val.quality;
    destroySchema(&lkab_schema);

    if (tmp_err_code == EXIP_PARSING_COMPLETE)
        return EXIP_OK;
    else
        return tmp_err_code;
}

static error_code parseDevDescMsg(char* buf, unsigned int buf_size, DevDescribtion* devDesc) {
    Parser lkabParser;
    BinaryBuffer buffer;
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    struct appDataLKAB parsingData;
    EXIPSchema lkab_schema;
    const char *schemafname = "SchemaStrict/lkab-devices-xsd.exi";

    buffer.buf = buf;
    buffer.bufLen = buf_size;
    buffer.bufContent = buf_size;

    // Parsing steps:

    // I.A: First, read in the schema
    parseSchema(schemafname, &lkab_schema);

    // I: First, define an external stream for the input to the parser if any
    buffer.ioStrm.stream = NULL;

    // II: Second, initialize the parser object
    tmp_err_code = initParser(&lkabParser, buffer, &parsingData);
    if (tmp_err_code != EXIP_OK)
        return tmp_err_code;

    // III: Initialize the parsing data and hook the callback handlers to the parser object

    parsingData.currElementNumber = 0;
    parsingData.devDesc.id[0] = '\0';
    parsingData.devDesc.location[0] = '\0';
    parsingData.devDesc.name[0] = '\0';
    parsingData.devDesc.type[0] = '\0';
    parsingData.devDesc.processValue.description[0] = '\0';
    parsingData.devDesc.processValue.name[0] = '\0';
    parsingData.devDesc.processValue.isReadOnly = 0;
    parsingData.devDesc.processValue.type = Bool;

    lkabParser.handler.fatalError = lkab_fatalError;
    lkabParser.handler.error = lkab_fatalError;
    lkabParser.handler.startElement = lkab_startElement_desc;
    lkabParser.handler.stringData = lkab_stringData_desc;
    lkabParser.handler.endElement = lkab_endElement;
    lkabParser.handler.booleanData = lkab_booleanData_desc;

    // IV: Parse the header of the stream

    tmp_err_code = parseHeader(&lkabParser, FALSE);

    tmp_err_code = setSchema(&lkabParser, &lkab_schema);
    // V: Parse the body of the EXI stream

    while (tmp_err_code == EXIP_OK) {
        tmp_err_code = parseNext(&lkabParser);
    }

    // VI: Free the memory allocated by the parser object

    destroyParser(&lkabParser);

    strcpy(devDesc->id, parsingData.devDesc.id);
    strcpy(devDesc->location, parsingData.devDesc.location);
    strcpy(devDesc->name, parsingData.devDesc.name);
    strcpy(devDesc->type, parsingData.devDesc.type);
    strcpy(devDesc->processValue.description, parsingData.devDesc.processValue.description);
    strcpy(devDesc->processValue.name, parsingData.devDesc.processValue.name);
    devDesc->processValue.isReadOnly = parsingData.devDesc.processValue.isReadOnly;
    devDesc->processValue.type = parsingData.devDesc.processValue.type;

    destroySchema(&lkab_schema);
    if (tmp_err_code == EXIP_PARSING_COMPLETE)
        return EXIP_OK;
    else
        return tmp_err_code;
}

static errorCode lkab_fatalError(const errorCode code, const char* msg, void* app_data) {
	EXIP_UNUSED(code);
	EXIP_UNUSED(msg);
	EXIP_UNUSED(app_data);
    return EXIP_HANDLER_STOP;
}

static errorCode lkab_startElement_io(QName qname, void* app_data) {
    struct appDataLKAB* appD = (struct appDataLKAB*) app_data;
    QName expectedElem;

    appD->currElementNumber += 1;

    expectedElem.uri = &NS_STR;
    switch (appD->currElementNumber) {
        case 1:
            expectedElem.localName = &ELEM_BOOL_VAL_STR;
            break;
        case 2:
            expectedElem.localName = &ELEM_TIMESTAMP_STR;
            break;
        case 3:
            expectedElem.localName = &ELEM_QUAL_STR;
            break;
        case 4:
            expectedElem.localName = &ELEM_VALUE_STR;
            break;
        default:
            return EXIP_HANDLER_STOP;
            break;
    }

    if (!stringEqual(*expectedElem.uri, *(qname.uri)) ||
            !stringEqual(*expectedElem.localName, *(qname.localName))) {
        return EXIP_HANDLER_STOP;
    }

    return EXIP_OK;
}

static errorCode lkab_startElement_desc(QName qname, void* app_data) {
    struct appDataLKAB* appD = (struct appDataLKAB*) app_data;
    QName expectedElem;

    appD->currElementNumber += 1;

    expectedElem.uri = &NS_STR;
    switch (appD->currElementNumber) {
        case 1:
            expectedElem.localName = &ELEM_DEV_DESC_STR;
            break;
        case 2:
            expectedElem.localName = &ELEM_ID_STR;
            break;
        case 3:
            expectedElem.localName = &ELEM_NAME_STR;
            break;
        case 4:
            expectedElem.localName = &ELEM_TYPE_STR;
            break;
        case 5:
            expectedElem.localName = &ELEM_LOCATION_STR;
            break;
        case 6:
            expectedElem.localName = &ELEM_PROSS_VAL_STR;
            break;
        case 7:
            expectedElem.localName = &ELEM_NAME_STR;
            break;
        case 8:
            expectedElem.localName = &ELEM_TYPE_STR;
            break;
        case 9:
            expectedElem.localName = &ELEM_IS_READONLY_STR;
            break;
        case 10:
            expectedElem.localName = &ELEM_DESC_STR;
            break;
        default:
            return EXIP_HANDLER_STOP;
            break;
    }

    if (!stringEqual(*expectedElem.uri, *(qname.uri)) ||
            !stringEqual(*expectedElem.localName, *(qname.localName))) {
        return EXIP_HANDLER_STOP;
    }

    return EXIP_OK;
}

static errorCode lkab_endElement(void* app_data) {
	EXIP_UNUSED(app_data);
    return EXIP_OK;
}

static errorCode lkab_stringData_io(const String value, void* app_data) {
    struct appDataLKAB* appD = (struct appDataLKAB*) app_data;

    if (appD->currElementNumber != 3)
        return EXIP_HANDLER_STOP;
    else {
        int i;
        for (i = 0; i < 15; i++) {
            if (stringEqual(ENUM_DATA_QUALITY[i], value)) {
                appD->val.quality = i;
                return EXIP_OK;
            }
        }
        return EXIP_HANDLER_STOP;
    }
}

static errorCode lkab_stringData_desc(const String value, void* app_data) {
    struct appDataLKAB* appD = (struct appDataLKAB*) app_data;

    switch (appD->currElementNumber) {
        case 2:
            memcpy(appD->devDesc.id, value.str, sizeof (CharType) * value.length);
            appD->devDesc.id[value.length] = '\0';
            break;
        case 3:
            memcpy(appD->devDesc.name, value.str, sizeof (CharType) * value.length);
            appD->devDesc.name[value.length] = '\0';
            break;
        case 4:
            memcpy(appD->devDesc.type, value.str, sizeof (CharType) * value.length);
            appD->devDesc.type[value.length] = '\0';
            break;
        case 5:
            memcpy(appD->devDesc.location, value.str, sizeof (CharType) * value.length);
            appD->devDesc.location[value.length] = '\0';
            break;
        case 7:
            memcpy(appD->devDesc.processValue.name, value.str, sizeof (CharType) * value.length);
            appD->devDesc.processValue.name[value.length] = '\0';
            break;
        case 8:
            if (stringEqual(value, ENUM_DATA_VAL_TYPE[Bool]))
                appD->devDesc.processValue.type = Bool;
            else if (stringEqual(value, ENUM_DATA_VAL_TYPE[Long]))
                appD->devDesc.processValue.type = Long;
            else
                return EXIP_HANDLER_STOP;
            break;
        case 10:
            memcpy(appD->devDesc.processValue.description, value.str, sizeof (CharType) * value.length);
            appD->devDesc.processValue.description[value.length] = '\0';
            break;
        default:
            return EXIP_HANDLER_STOP;
            break;
    }

    return EXIP_OK;
}

static errorCode lkab_booleanData_io(exip_bool bool_val, void* app_data) {
    struct appDataLKAB* appD = (struct appDataLKAB*) app_data;

    if (appD->currElementNumber != 4)
        return EXIP_HANDLER_STOP;
    else {
        appD->val.val = bool_val;
    }

    return EXIP_OK;
}

static errorCode lkab_booleanData_desc(exip_bool bool_val, void* app_data) {
    struct appDataLKAB* appD = (struct appDataLKAB*) app_data;

    if (appD->currElementNumber != 9)
        return EXIP_HANDLER_STOP;
    else {
        appD->devDesc.processValue.isReadOnly = bool_val;
    }

    return EXIP_OK;
}

static errorCode lkab_dateTimeData(EXIPDateTime dt_val, void* app_data) {
    struct appDataLKAB* appD = (struct appDataLKAB*) app_data;

    appD->val.ts.year = dt_val.dateTime.tm_year;
    appD->val.ts.month = dt_val.dateTime.tm_mon;
    appD->val.ts.mday = dt_val.dateTime.tm_mday;
    appD->val.ts.hour = dt_val.dateTime.tm_hour;
    appD->val.ts.min = dt_val.dateTime.tm_min;
    appD->val.ts.sec = dt_val.dateTime.tm_sec;
    appD->val.ts.msec = dt_val.fSecs.value;

    return EXIP_OK;
}

#define LKAB_BUFFER_SIZE 1000

START_TEST(test_lkab_demo_suit) {
    char lkab_buf[LKAB_BUFFER_SIZE];
    unsigned int msg_size;
    BoolValue bVal;
    DevDescribtion devD;
    error_code err;

    memset(lkab_buf, '\0', LKAB_BUFFER_SIZE);

    bVal.ts.hour = 0;
    bVal.ts.mday = 0;
    bVal.ts.min = 10;
    bVal.ts.month = 0;
    bVal.ts.msec = 115;
    bVal.ts.sec = 10;
    bVal.ts.year = 0;
    bVal.quality = Good;
    bVal.val = 1;

    err = serializeIOMsg(lkab_buf, LKAB_BUFFER_SIZE, &msg_size, bVal);

    fail_unless(err == EXIP_OK, "Error during serialization of IO Msg %d", err);
    fail_if(msg_size == 0, "0 Length message size");

    bVal.ts.hour = 10;
    bVal.ts.mday = 30;
    bVal.ts.min = 120;
    bVal.ts.month = 44;
    bVal.ts.msec = 125;
    bVal.ts.sec = 110;
    bVal.ts.year = 4;
    bVal.val = 0;
    bVal.quality = Bad;

    err = parseIOMsg(lkab_buf, LKAB_BUFFER_SIZE, &bVal);

    fail_unless(err == EXIP_OK, "Error during parsing of IO Msg %d", err);
    fail_unless(bVal.quality == Good, "quality not correct");
    fail_unless(bVal.val == 1, "value not correct");
    fail_unless(bVal.ts.min == 10, "min not correct");
    fail_unless(bVal.ts.sec == 10, "sec not correct");
    fail_unless(bVal.ts.msec == 115, "msec not correct");

    strcpy(devD.id, "AirPS");
    strcpy(devD.location, "Grate Support Shaft");
    strcpy(devD.name, "Pressure switch");
    strcpy(devD.type, "Air pressure switch");
    strcpy(devD.processValue.description, "This is an Air pressure switch ON/OFF value");
    strcpy(devD.processValue.name, "Air pressure switch ON/OFF");
    devD.processValue.isReadOnly = 0;
    devD.processValue.type = Bool;

    err = serializeDevDescMsg(lkab_buf, LKAB_BUFFER_SIZE, &msg_size, devD);

    fail_unless(err == EXIP_OK, "Error during serialization of DevDesc Msg %d", err);
    fail_if(msg_size == 0, "0 Length message size");

    strcpy(devD.id, "00000000000");
    strcpy(devD.location, "00000000000");
    strcpy(devD.name, "00000000000");
    strcpy(devD.type, "00000000000");
    strcpy(devD.processValue.description, "00000000000");
    strcpy(devD.processValue.name, "00000000000");
    devD.processValue.isReadOnly = 1;
    devD.processValue.type = Long;

    err = parseDevDescMsg(lkab_buf, LKAB_BUFFER_SIZE, &devD);

    fail_unless(err == EXIP_OK, "Error during parsing of DevDesc Msg %d", err);
    fail_unless(devD.processValue.isReadOnly == 0, "isReadOnly not correct");
    fail_unless(devD.processValue.type == Bool, "type not correct");
    fail_unless(strcmp(devD.id, "AirPS") == 0, "id not correct");
    fail_unless(strcmp(devD.location, "Grate Support Shaft") == 0, "location not correct");
    fail_unless(strcmp(devD.name, "Pressure switch") == 0, "name not correct");
    fail_unless(strcmp(devD.type, "Air pressure switch") == 0, "type not correct");
    fail_unless(strcmp(devD.processValue.description, "This is an Air pressure switch ON/OFF value") == 0, "description not correct");
    fail_unless(strcmp(devD.processValue.name, "Air pressure switch ON/OFF") == 0, "name not correct");
}

END_TEST
/**********************************************************************/
/**********************************************************************/
/* END THE LKAB DEMO SUIT*/

/* Test suite */

/* Namespaces named only by xs:any / xs:anyAttribute lists join the uri
 * partition, sorted with the target namespaces, and "##local" as the last token of a
 * list is the empty namespace. The expected partition is EXIficient 1.0.7's
 * (exi-oracle dump-grammars on SchemaStrict/wildcard-namespaces.xsd). */
START_TEST(test_wildcard_namespaces_in_uri_partition) {
    EXIPSchema schema;
    const char *expected[] = {
        "urn:b-only-in-anyAttribute", "urn:mid", "urn:only-in-any", "urn:t",
        "urn:zz-only-in-anyAttribute"
    };
    Index i;

    // Used to fail with EXIP_UNEXPECTED_ERROR: the namespaces were never registered
    parseSchema("SchemaStrict/wildcard-namespaces-xsd.exi", &schema);

    fail_unless(schema.uriTable.count == 4 + 5,
            "uri partition has %u entries, expected 9", (unsigned int) schema.uriTable.count);
    for (i = 0; i < 5; i++) {
        fail_unless(stringEqualToAscii(schema.uriTable.uri[4 + i].uriStr, expected[i]),
                "uri %u is \"%.*s\", expected \"%s\"", (unsigned int) (4 + i),
                (int) schema.uriTable.uri[4 + i].uriStr.length, schema.uriTable.uri[4 + i].uriStr.str,
                expected[i]);
    }
    destroySchema(&schema);
}
END_TEST

/* A choice with no particles (spec 8.5.4.1.8.2, ParticleTerm_0 : EE),
 * as in W3C schemaInformedGrammar/acceptance.xsd, crashed the grammar generator.
 * The runner does not fork, so a crash ends the run with a failure status. */
START_TEST(test_empty_choice_loads) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/empty-choice-xsd.exi", &schema);
    destroySchema(&schema);
}
END_TEST

/* Substitution-group members are global; with elementFormDefault
 * unqualified exip looked their names up in the empty namespace and failed to load
 * the schema. EXIficient 1.0.7 and the fixed exip both encode
 * <sg:list><sg:head>a</sg:head><sg:member>b</sg:member></sg:list> as 8040361406c500. */
START_TEST(test_substitution_group_member_loads) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/substitution-group-xsd.exi", &schema);
    destroySchema(&schema);
}
END_TEST

/* The TypeEmpty grammar (spec 8.5.4.1.3.1), on
 * SchemaStrict/nillable.xsd. The reference bytes are EXIficient 1.0.7's (strict,
 * bit-packed, no options in the header), except for xsi:nil="false", which
 * EXIficient drops: there rexi's and Nagasena's (identical) are the reference. */

#define NIL_BUF_SIZE 64

enum nilEvKind { NIL_SD, NIL_SE, NIL_NIL, NIL_AT, NIL_CH, NIL_EE, NIL_ED, NIL_XT, NIL_NIL_REJECTED, NIL_END };

struct nilEv {
    enum nilEvKind kind;
    const char *name; // SE local name; AT local name, or {uri}local
    const char *value; // CH / AT value ("t...": string, else int / 1.5), "1" / "0" for xsi:nil,
                       // urn:n local name for xsi:type
};

struct nilSink {
    char data[NIL_BUF_SIZE];
    size_t len;
};

static size_t nilSinkWrite(void* buf, size_t size, void* stream) {
    struct nilSink *sink = (struct nilSink*) stream;
    if (sink->len + size > NIL_BUF_SIZE)
        return 0;
    memcpy(&sink->data[sink->len], buf, size);
    sink->len += size;
    return size;
}

/* valueMaxLength for the next streams (INDEX_MAX: unbounded) */
static Index nilValueMaxLength = INDEX_MAX;

static void nilOptions(EXIOptions* opts) {
    makeDefaultOpts(opts);
    SET_STRICT(opts->enumOpt);
    opts->valueMaxLength = nilValueMaxLength;
}

static void encodeNilDoc(EXIPSchema* schema, const struct nilEv* evs, struct nilSink* sink) {
    EXIStream strm;
    char buf[NIL_BUF_SIZE];
    BinaryBuffer buffer;
    String ns, xsiNs, xsiNil, xsiType, ln, val;
    QName qname;
    EXITypeClass valueType;
    errorCode err = EXIP_OK;
    unsigned int i;

    memset(buf, 0, sizeof buf);
    buffer.buf = buf;
    buffer.bufLen = sizeof buf;
    buffer.bufContent = 0;
    buffer.ioStrm.readWriteToStream = nilSinkWrite;
    buffer.ioStrm.stream = sink;
    sink->len = 0;

    asciiToString("urn:n", &ns, NULL, FALSE);
    asciiToString("http://www.w3.org/2001/XMLSchema-instance", &xsiNs, NULL, FALSE);
    asciiToString("nil", &xsiNil, NULL, FALSE);
    asciiToString("type", &xsiType, NULL, FALSE);

    serialize.initHeader(&strm);
    strm.header.has_cookie = FALSE;
    strm.header.has_options = FALSE;
    nilOptions(&strm.header.opts);
    err = serialize.initStream(&strm, buffer, schema);
    fail_unless(err == EXIP_OK, "initStream returns error code %d", err);
    err = serialize.exiHeader(&strm);
    fail_unless(err == EXIP_OK, "exiHeader returns error code %d", err);

    for (i = 0; evs[i].kind != NIL_END; i++) {
        switch (evs[i].kind) {
            case NIL_SD:
                err = serialize.startDocument(&strm);
                break;
            case NIL_SE:
                // "local" (urn:n) or "{uri}local"
                if (evs[i].name[0] == '{') {
                    const char *end = strchr(evs[i].name, '}');
                    val.str = (CharType*) (evs[i].name + 1);
                    val.length = (Index) (end - evs[i].name - 1);
                    asciiToString(end + 1, &ln, NULL, FALSE);
                    qname.uri = &val;
                } else {
                    asciiToString(evs[i].name, &ln, NULL, FALSE);
                    qname.uri = &ns;
                }
                qname.localName = &ln;
                qname.prefix = NULL;
                err = serialize.startElement(&strm, qname, &valueType);
                break;
            case NIL_NIL:
                qname.uri = &xsiNs;
                qname.localName = &xsiNil;
                qname.prefix = NULL;
                err = serialize.attribute(&strm, qname, TRUE, &valueType);
                if (err == EXIP_OK) {
                    // Used to be the element's type: EXIP_NOT_IMPLEMENTED_YET or
                    // EXIP_INCONSISTENT_PROC_STATE, or the flag written as a string
                    fail_unless(valueType == VALUE_TYPE_BOOLEAN_CLASS,
                            "event %u: xsi:nil value type %d, expected boolean", i, (int) valueType);
                    err = serialize.booleanData(&strm, evs[i].value[0] == '1');
                }
                break;
            case NIL_XT:
                qname.uri = &xsiNs;
                qname.localName = &xsiType;
                qname.prefix = NULL;
                err = serialize.attribute(&strm, qname, TRUE, &valueType);
                if (err == EXIP_OK) {
                    asciiToString(evs[i].value, &ln, NULL, FALSE);
                    qname.uri = &ns;
                    qname.localName = &ln;
                    err = serialize.qnameData(&strm, qname);
                }
                break;
            case NIL_NIL_REJECTED:
                qname.uri = &xsiNs;
                qname.localName = &xsiNil;
                qname.prefix = NULL;
                err = serialize.attribute(&strm, qname, TRUE, &valueType);
                fail_unless(err != EXIP_OK, "event %u: xsi:nil accepted", i);
                serialize.closeEXIStream(&strm);
                return;
            case NIL_AT:
                // "local" (no namespace) or "{uri}local"
                if (evs[i].name[0] == '{') {
                    const char *end = strchr(evs[i].name, '}');
                    val.str = (CharType*) (evs[i].name + 1);
                    val.length = (Index) (end - evs[i].name - 1);
                    asciiToString(end + 1, &ln, NULL, FALSE);
                } else {
                    asciiToString(evs[i].name, &ln, NULL, FALSE);
                    getEmptyString(&val);
                }
                qname.uri = &val;
                qname.localName = &ln;
                qname.prefix = NULL;
                err = serialize.attribute(&strm, qname, TRUE, &valueType);
                if (err == EXIP_OK && valueType == VALUE_TYPE_BOOLEAN_CLASS)
                    err = serialize.booleanData(&strm, strcmp(evs[i].value, "true") == 0);
                else if (err == EXIP_OK && evs[i].value[0] == 't') {
                    String str;
                    asciiToString(evs[i].value, &str, NULL, FALSE);
                    err = serialize.stringData(&strm, str);
                } else if (err == EXIP_OK)
                    err = serialize.intData(&strm, atoi(evs[i].value));
                break;
            case NIL_CH:
                if (evs[i].value[0] == 't' || valueType == VALUE_TYPE_STRING_CLASS) {
                    asciiToString(evs[i].value, &val, NULL, FALSE);
                    err = serialize.stringData(&strm, val);
                } else {
                    Float f = {15, -1}; // the only float in these documents: 1.5
                    err = serialize.floatData(&strm, f);
                }
                break;
            case NIL_EE:
                err = serialize.endElement(&strm);
                break;
            case NIL_ED:
                err = serialize.endDocument(&strm);
                break;
            default:
                err = EXIP_UNEXPECTED_ERROR;
        }
        fail_unless(err == EXIP_OK, "event %u returns error code %d", i, err);
    }
    err = serialize.closeEXIStream(&strm);
    fail_unless(err == EXIP_OK, "closeEXIStream returns error code %d", err);
}

static void checkNilEncoding(EXIPSchema* schema, const struct nilEv* evs, const char* expected,
        size_t expectedLen, const char* what) {
    struct nilSink sink;
    size_t i;

    encodeNilDoc(schema, evs, &sink);
    for (i = 0; i < sink.len && i < expectedLen; i++)
        if (sink.data[i] != expected[i])
            break;
    fail_unless(sink.len == expectedLen && i == expectedLen,
            "%s: %u bytes, byte %u is 0x%02X, expected 0x%02X", what, (unsigned int) sink.len,
            (unsigned int) i, i < sink.len ? (unsigned char) sink.data[i] : 0,
            i < expectedLen ? (unsigned char) expected[i] : 0);
}

#define NIL_SDR {NIL_SD, NULL, NULL}, {NIL_SE, "r", NULL}
#define NIL_EED {NIL_EE, NULL, NULL}, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL}

static const struct nilEv NIL_DOC_D[] = {
    NIL_SDR, {NIL_SE, "d", NULL}, {NIL_NIL, NULL, "1"}, {NIL_EE, NULL, NULL}, NIL_EED
};
static const struct nilEv NIL_DOC_S[] = {
    NIL_SDR, {NIL_SE, "s", NULL}, {NIL_NIL, NULL, "1"}, {NIL_EE, NULL, NULL}, NIL_EED
};
static const struct nilEv NIL_DOC_C[] = {
    NIL_SDR, {NIL_SE, "c", NULL}, {NIL_NIL, NULL, "1"}, {NIL_AT, "k", "5"}, {NIL_EE, NULL, NULL}, NIL_EED
};
static const struct nilEv NIL_DOC_C_EMPTY[] = {
    NIL_SDR, {NIL_SE, "c", NULL}, {NIL_NIL, NULL, "1"}, {NIL_EE, NULL, NULL}, NIL_EED
};
static const struct nilEv NIL_DOC_FALSE[] = {
    NIL_SDR, {NIL_SE, "d", NULL}, {NIL_NIL, NULL, "0"}, {NIL_CH, NULL, "1.5"}, {NIL_EE, NULL, NULL},
    {NIL_SE, "s", NULL}, {NIL_NIL, NULL, "0"}, {NIL_CH, NULL, "t"}, {NIL_EE, NULL, NULL}, NIL_EED
};

/* The xsi:nil value is xs:boolean whatever the element's type. */
START_TEST(test_xsi_nil_value_is_boolean) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/nillable-xsd.exi", &schema);
    checkNilEncoding(&schema, NIL_DOC_D, "\x80\x1c", 2, "xs:double xsi:nil=true");
    checkNilEncoding(&schema, NIL_DOC_S, "\x80\x3c", 2, "xs:string xsi:nil=true");
    checkNilEncoding(&schema, NIL_DOC_FALSE, "\x80\x10\x1f\x00\x20\x1b\xa4", 7, "xsi:nil=false");
    destroySchema(&schema);
}
END_TEST

/* After xsi:nil="true" the element continues in its TypeEmpty grammar
 * (spec 8.5.4.1.3.1): the content is replaced by EE, so EE follows the attribute
 * productions in every rule before the content, whether or not the type's rule has
 * one. exip used the type's rule: it rejected EE (EXIP_INCONSISTENT_PROC_STATE) and
 * coded AT(k) with an extra bit; its decoder read 8056 as <c><x/></c>. */
START_TEST(test_xsi_nil_type_empty_grammar) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/nillable-xsd.exi", &schema);
    checkNilEncoding(&schema, NIL_DOC_C, "\x80\x54\x05", 3, "complex xsi:nil=true k=5");
    checkNilEncoding(&schema, NIL_DOC_C_EMPTY, "\x80\x56", 2, "complex xsi:nil=true");
    destroySchema(&schema);
}
END_TEST

struct nilTrace {
    char text[256];
    size_t len;
};

static void nilAppend(struct nilTrace* t, const char* s, const String* str) {
    size_t n = strlen(s);
    if (t->len + n + (str ? str->length : 0) + 2 >= sizeof t->text)
        return;
    memcpy(&t->text[t->len], s, n);
    t->len += n;
    if (str) {
        memcpy(&t->text[t->len], str->str, str->length);
        t->len += str->length;
    }
    t->text[t->len++] = ' ';
    t->text[t->len] = '\0';
}

static errorCode nil_fatal(const errorCode code, const char* msg, void* app_data) {
    (void) code; (void) msg; (void) app_data;
    return EXIP_HANDLER_STOP;
}

static errorCode nil_sd(void* app_data) {
    nilAppend((struct nilTrace*) app_data, "SD", NULL);
    return EXIP_OK;
}

static errorCode nil_ed(void* app_data) {
    nilAppend((struct nilTrace*) app_data, "ED", NULL);
    return EXIP_OK;
}

static errorCode nil_se(QName qname, void* app_data) {
    nilAppend((struct nilTrace*) app_data, "SE:", qname.localName);
    return EXIP_OK;
}

static errorCode nil_ee(void* app_data) {
    nilAppend((struct nilTrace*) app_data, "EE", NULL);
    return EXIP_OK;
}

static errorCode nil_at(QName qname, void* app_data) {
    nilAppend((struct nilTrace*) app_data, "AT:", qname.localName);
    return EXIP_OK;
}

static errorCode nil_bool(exip_bool bool_val, void* app_data) {
    nilAppend((struct nilTrace*) app_data, bool_val ? "true" : "false", NULL);
    return EXIP_OK;
}

static errorCode nil_int(Integer int_val, void* app_data) {
    char num[24];
    snprintf(num, sizeof num, "%ld", (long) int_val);
    nilAppend((struct nilTrace*) app_data, num, NULL);
    return EXIP_OK;
}

static errorCode nil_qname(QName qname, void* app_data) {
    nilAppend((struct nilTrace*) app_data, "QN:", qname.localName);
    return EXIP_OK;
}

static errorCode nil_str(const String value, void* app_data) {
    nilAppend((struct nilTrace*) app_data, "CH:", &value);
    return EXIP_OK;
}

/* Decodes with nilOptions (strict), or non-strict and, if prefixes, Preserve.prefixes */
static void checkDecodingWith(EXIPSchema* schema, const char* exi, size_t len, const char* expected,
        exip_bool nonStrict, exip_bool prefixes) {
    Parser parser;
    BinaryBuffer buffer;
    char buf[NIL_BUF_SIZE];
    struct nilTrace trace;
    errorCode err;

    memcpy(buf, exi, len);
    buffer.buf = buf;
    buffer.bufLen = len;
    buffer.bufContent = len;
    buffer.ioStrm.readWriteToStream = NULL;
    buffer.ioStrm.stream = NULL;
    trace.len = 0;
    trace.text[0] = '\0';

    err = initParser(&parser, buffer, &trace);
    fail_unless(err == EXIP_OK, "initParser returns error code %d", err);
    nilOptions(&parser.strm.header.opts);
    if (nonStrict)
        parser.strm.header.opts.enumOpt &= (unsigned char) ~EXIP_STRICT;
    if (prefixes)
        SET_PRESERVED(parser.strm.header.opts.preserve, PRESERVE_PREFIXES);
    parser.handler.fatalError = nil_fatal;
    parser.handler.error = nil_fatal;
    parser.handler.startDocument = nil_sd;
    parser.handler.endDocument = nil_ed;
    parser.handler.startElement = nil_se;
    parser.handler.endElement = nil_ee;
    parser.handler.attribute = nil_at;
    parser.handler.booleanData = nil_bool;
    parser.handler.intData = nil_int;
    parser.handler.qnameData = nil_qname;
    parser.handler.stringData = nil_str;

    err = parseHeader(&parser, TRUE);
    fail_unless(err == EXIP_OK, "parseHeader returns error code %d", err);
    err = setSchema(&parser, schema);
    fail_unless(err == EXIP_OK, "setSchema returns error code %d", err);
    while ((err = parseNext(&parser)) == EXIP_OK)
        ;
    destroyParser(&parser);
    fail_unless(err == EXIP_PARSING_COMPLETE, "parsing returns error code %d after \"%s\"", err, trace.text);
    fail_unless(strcmp(trace.text, expected) == 0, "decoded \"%s\", expected \"%s\"", trace.text, expected);
}

static void checkNilDecoding(EXIPSchema* schema, const char* exi, size_t len, const char* expected) {
    checkDecodingWith(schema, exi, len, expected, FALSE, FALSE);
}

START_TEST(test_xsi_nil_type_empty_grammar_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/nillable-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x54\x05", 3, "SD SE:r SE:c AT:nil true AT:k 5 EE EE ED ");
    checkNilDecoding(&schema, "\x80\x56", 2, "SD SE:r SE:c AT:nil true EE EE ED ");
    checkNilDecoding(&schema, "\x80\x1c", 2, "SD SE:r SE:d AT:nil true EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/nillable-types.xsd: nillable belongs to the element
 * declaration. exip stored it on the type grammar, so an element of a type whose
 * grammar already existed (b, n, g) lost it, and every element of a type first
 * created by a nillable element (q, after p) gained it. The reference bytes are
 * EXIficient 1.0.7's; rexi writes the same. */

#define NIL_EL(n) {NIL_SE, n, NULL}
#define NIL_TRUE {NIL_NIL, NULL, "1"}
#define NIL_K5 {NIL_AT, "k", "5"}
#define NIL_15 {NIL_CH, NULL, "1.5"}
#define NIL_E {NIL_EE, NULL, NULL}
#define NIL_ROOT(n) {NIL_SD, NULL, NULL}, NIL_EL(n)

static const struct nilEv NILT_DOC_B[] = { NIL_SDR, NIL_EL("b"), NIL_TRUE, NIL_E, NIL_EED };
static const struct nilEv NILT_DOC_N[] = { NIL_SDR, NIL_EL("n"), NIL_TRUE, NIL_E, NIL_EED };
static const struct nilEv NILT_DOC_P[] = { NIL_SDR, NIL_EL("p"), NIL_TRUE, NIL_K5, NIL_E, NIL_EED };
static const struct nilEv NILT_DOC_PQ[] = {
    NIL_SDR, NIL_EL("p"), NIL_K5, NIL_E, NIL_EL("q"), NIL_K5, NIL_E, NIL_EED
};
static const struct nilEv NILT_DOC_A[] = { NIL_SDR, NIL_EL("a"), NIL_TRUE, NIL_E, NIL_EED };
static const struct nilEv NILT_DOC_BN[] = {
    NIL_SDR, NIL_EL("b"), NIL_15, NIL_E, NIL_EL("n"), NIL_15, NIL_E, NIL_EED
};
static const struct nilEv NILT_DOC_G[] = { NIL_ROOT("g"), NIL_TRUE, NIL_E, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL} };
static const struct nilEv NILT_DOC_G15[] = { NIL_ROOT("g"), NIL_15, NIL_E, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL} };
static const struct nilEv NILT_DOC_H[] = { NIL_ROOT("h"), NIL_15, NIL_E, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL} };

START_TEST(test_nillable_element_grammars) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/nillable-types-xsd.exi", &schema);
    checkNilEncoding(&schema, NILT_DOC_B, "\x80\x87\x80", 3, "built-in type xsi:nil=true");
    checkNilEncoding(&schema, NILT_DOC_N, "\x80\x8f\x80", 3, "named simple type xsi:nil=true");
    checkNilEncoding(&schema, NILT_DOC_P, "\x80\x95\x01\x60", 4, "named complex type xsi:nil=true");
    checkNilEncoding(&schema, NILT_DOC_PQ, "\x80\x90\x05\x00\x58", 5, "nillable p, non-nillable q");
    checkNilEncoding(&schema, NILT_DOC_A, "\x80\xa6", 2, "anonymous type xsi:nil=true");
    checkNilEncoding(&schema, NILT_DOC_BN, "\x80\x80\x1f\x00\x00\x7c\x03", 7, "b and n values");
    checkNilEncoding(&schema, NILT_DOC_G, "\x80\x30", 2, "global g xsi:nil=true");
    checkNilEncoding(&schema, NILT_DOC_G15, "\x80\x00\xf8\x00", 4, "global g value");
    checkNilEncoding(&schema, NILT_DOC_H, "\x80\x41\xf0\x00", 4, "global h value");
    destroySchema(&schema);
}
END_TEST

START_TEST(test_nillable_element_grammars_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/nillable-types-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x87\x80", 3, "SD SE:r SE:b AT:nil true EE EE ED ");
    checkNilDecoding(&schema, "\x80\x8f\x80", 3, "SD SE:r SE:n AT:nil true EE EE ED ");
    checkNilDecoding(&schema, "\x80\x95\x01\x60", 4, "SD SE:r SE:p AT:nil true AT:k 5 EE EE ED ");
    checkNilDecoding(&schema, "\x80\x90\x05\x00\x58", 5, "SD SE:r SE:p AT:k 5 EE SE:q AT:k 5 EE EE ED ");
    checkNilDecoding(&schema, "\x80\xa6", 2, "SD SE:r SE:a AT:nil true EE EE ED ");
    checkNilDecoding(&schema, "\x80\x30", 2, "SD SE:g AT:nil true EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/xsi-type.xsd: after xsi:type the element continues in
 * the target type grammar, and its start rule has no xsi:type / xsi:nil escape
 * (spec 8.5.4.4.2). exip took the escapes from the type grammar's properties, so a
 * cast to a type with named sub-types coded the next attribute one bit too wide.
 * The reference bytes are EXIficient 1.0.7's; rexi writes the same. */

#define XT(t) {NIL_XT, NULL, t}
#define XT_LABEL {NIL_SE, "Label", NULL}, {NIL_CH, NULL, "t"}, NIL_E

static const struct nilEv XT_DOC_SHAPE[] = {
    NIL_SDR, NIL_EL("Shape"), XT("Shape"), {NIL_AT, "id", "4"}, XT_LABEL, NIL_E, NIL_EED
};
static const struct nilEv XT_DOC_CIRCLE[] = {
    NIL_SDR, NIL_EL("Shape"), XT("Circle"), {NIL_AT, "id", "4"}, XT_LABEL, NIL_E, NIL_EED
};
static const struct nilEv XT_DOC_NESTED[] = {
    NIL_SDR, NIL_EL("Shape"), XT("Circle"), {NIL_AT, "id", "1"}, XT_LABEL,
    NIL_EL("Inner"), XT("Shape"), {NIL_AT, "id", "2"}, XT_LABEL, NIL_E, NIL_E, NIL_EED
};
static const struct nilEv XT_DOC_NONE[] = {
    NIL_SDR, NIL_EL("Shape"), {NIL_AT, "id", "4"}, XT_LABEL, NIL_E, NIL_EED
};
static const struct nilEv XT_DOC_NILLABLE[] = {
    NIL_SDR, NIL_EL("ns"), XT("Shape"), {NIL_AT, "id", "4"}, XT_LABEL, NIL_E, NIL_EED
};
static const struct nilEv XT_DOC_NIL_AFTER_TYPE[] = {
    NIL_SDR, NIL_EL("ns"), XT("Shape"), {NIL_NIL_REJECTED, NULL, "1"}, {NIL_END, NULL, NULL}
};

START_TEST(test_xsi_type_cast_no_escapes) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/xsi-type-xsd.exi", &schema);
    checkNilEncoding(&schema, XT_DOC_SHAPE, "\x80\x1a\x00\xc0\x80\x37\x48", 7, "cast to Shape");
    checkNilEncoding(&schema, XT_DOC_CIRCLE, "\x80\x1a\x00\x00\x80\x37\x4c", 7, "cast to Circle");
    checkNilEncoding(&schema, XT_DOC_NESTED, "\x80\x1a\x00\x00\x20\x37\x46\x80\x30\x10\x02", 11,
            "cast inside a cast");
    checkNilEncoding(&schema, XT_DOC_NONE, "\x80\x00\x20\x0d\xd2", 5, "no cast");
    checkNilEncoding(&schema, XT_DOC_NILLABLE, "\x80\x35\x00\x60\x40\x1b\xa0", 7, "cast of a nillable element");
    encodeNilDoc(&schema, XT_DOC_NIL_AFTER_TYPE, &(struct nilSink){{0}, 0});
    destroySchema(&schema);
}
END_TEST

START_TEST(test_xsi_type_cast_no_escapes_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/xsi-type-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x1a\x00\xc0\x80\x37\x48", 7,
            "SD SE:r SE:Shape AT:type QN:Shape AT:id 4 SE:Label CH:t EE EE EE ED ");
    checkNilDecoding(&schema, "\x80\x1a\x00\x00\x80\x37\x4c", 7,
            "SD SE:r SE:Shape AT:type QN:Circle AT:id 4 SE:Label CH:t EE EE EE ED ");
    checkNilDecoding(&schema, "\x80\x1a\x00\x00\x20\x37\x46\x80\x30\x10\x02", 11,
            "SD SE:r SE:Shape AT:type QN:Circle AT:id 1 SE:Label CH:t EE "
            "SE:Inner AT:type QN:Shape AT:id 2 SE:Label CH:t EE EE EE EE ED ");
    checkNilDecoding(&schema, "\x80\x35\x00\x60\x40\x1b\xa0", 7,
            "SD SE:r SE:ns AT:type QN:Shape AT:id 4 SE:Label CH:t EE EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* With Preserve.prefixes, AT(xsi:type) and AT(xsi:nil) of the undeclared
 * productions (non-strict, spec 8.5.4.4.1) carry the attribute's prefix like every other
 * AT event (spec 7.1.7). The prefix "i" is a second prefix of the xsi namespace (after
 * the initial "xsi"), so it takes one bit. EXIficient 1.0.7 streams of
 *   <r xmlns="urn:n" xmlns:i="http://www.w3.org/2001/XMLSchema-instance">
 *     <Shape i:type="Circle" id="4"><Label>t</Label></Shape></r>   and
 *     <ns i:nil="true" id="4"/></r>
 * non-strict, Preserve.prefixes, bit-packed, no options in the header. */
START_TEST(test_xsi_attribute_prefixes_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/xsi-type-xsd.exi", &schema);
    checkDecodingWith(&schema, "\x80\x72\x80\x78\xc0\x2d\x22\x74\x00\x00\x80\x1b\xa1\x80", 14,
            "SD SE:r SE:Shape AT:type QN:Circle AT:id 4 SE:Label CH:t EE EE EE ED ", TRUE, TRUE);
    checkDecodingWith(&schema, "\x80\x72\x80\x78\xc0\x2d\x26\xb0\x10", 9,
            "SD SE:r SE:ns AT:nil true AT:id 4 EE EE ED ", TRUE, TRUE);
    destroySchema(&schema);
}
END_TEST

/* In a schema-less stream xsi:nil is an ordinary attribute with a string value
 * (spec 8.4.3; only xsi:type has a QName value there). EXIficient 1.0.7 stream of
 *   <r xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
 *     <a xsi:nil="true"/><c xsi:nil="maybe"/></r>
 * (bit-packed, no options in the header). */
START_TEST(test_schemaless_xsi_nil_decode) {
    checkDecodingWith(NULL, "\x80\x40\x9c\xa4\x09\x85\xc0\x00\xce\x8e\x4e\xac\xb2\x40\x98\xdc\x00\x0e"
            "\xda\xc2\xf2\xc4\xcb\x10", 24, "SD SE:r SE:a AT:nil CH:true EE SE:c AT:nil CH:maybe EE EE ED ", TRUE, FALSE);
}
END_TEST

/* On SchemaStrict/anytype-wildcard.xsd (EXIficient 1.0.7 and rexi agree).
 * xsi:nil / xsi:type on an xs:anyType element used to match its AT(*), which the
 * encoder then rejected (EXIP_INCONSISTENT_PROC_STATE). The TypeEmpty rule after
 * xsi:nil="true" is AT(*) | EE, EE in one bit. namespace="urn:b urn:b ##local urn:b
 * ##local" is a set of two namespaces, not five AT(uri:*) productions. */

static const struct nilEv ANY_DOC_NIL[] = {
    NIL_ROOT("any"), NIL_TRUE, NIL_E, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL}
};
static const struct nilEv ANY_DOC_TYPE[] = {
    NIL_ROOT("any"), XT("T"), {NIL_AT, "k", "5"}, NIL_E, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL}
};
static const struct nilEv ANY_DOC_PAIR[] = {
    NIL_ROOT("pair"), NIL_EL("any"), NIL_TRUE, NIL_E, NIL_EL("any"), NIL_TRUE, NIL_E, NIL_E,
    {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL}
};
static const struct nilEv WILD_DOC_W[] = {
    NIL_ROOT("w"), {NIL_CH, NULL, "t"}, NIL_E, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL}
};

START_TEST(test_anytype_xsi_and_namespace_set) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/anytype-wildcard-xsd.exi", &schema);
    checkNilEncoding(&schema, ANY_DOC_NIL, "\x80\x27", 2, "anyType xsi:nil=true");
    checkNilEncoding(&schema, ANY_DOC_TYPE, "\x80\x23\x00\x00\x28", 5, "anyType xsi:type");
    checkNilEncoding(&schema, ANY_DOC_PAIR, "\x80\x67\x4e", 3, "two anyType xsi:nil=true");
    checkNilEncoding(&schema, WILD_DOC_W, "\x80\xa0\x37\x40", 4, "namespace set");
    destroySchema(&schema);
}
END_TEST

START_TEST(test_anytype_xsi_and_namespace_set_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/anytype-wildcard-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x27", 2, "SD SE:any AT:nil true EE ED ");
    checkNilDecoding(&schema, "\x80\x23\x00\x00\x28", 5, "SD SE:any AT:type QN:T AT:k 5 EE ED ");
    checkNilDecoding(&schema, "\x80\x67\x4e", 3, "SD SE:pair SE:any AT:nil true EE SE:any AT:nil true EE EE ED ");
    checkNilDecoding(&schema, "\x80\xa0\x37\x40", 4, "SD SE:w CH:t EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/wildcard-uri.xsd (EXIficient 1.0.7; rexi does not
 * support these wildcards yet). SE(uri:*) and AT(uri:*) code only the local name
 * (the uri is implied); exip failed with EXIP_NOT_IMPLEMENTED_YET in both directions.
 * X extends B, so its wildcard is {urn:b} union {urn:n}; the restriction R has none.
 * After xsi:nil="true", the rule at the content index keeps its AT(uri:*). */

#define WU_G NIL_SDR, NIL_EL("g"), {NIL_CH, NULL, "t"}, NIL_E

static const struct nilEv WU_DOC_SE[] = { WU_G, NIL_EED };
static const struct nilEv WU_DOC_EXT[] = {
    WU_G, NIL_EL("e"), {NIL_AT, "{urn:b}x", "t"}, {NIL_AT, "{urn:n}y", "t"}, NIL_E, NIL_EED
};
static const struct nilEv WU_DOC_NIL[] = {
    WU_G, NIL_EL("n"), NIL_TRUE, {NIL_AT, "{urn:b}x", "t"}, NIL_E, NIL_EED
};
static const struct nilEv WU_DOC_RES[] = { WU_G, NIL_EL("q"), NIL_E, NIL_EED };

START_TEST(test_uri_wildcards) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/wildcard-uri-xsd.exi", &schema);
    checkNilEncoding(&schema, WU_DOC_SE, "\x80\x40\x14\x06\xe9\x80", 6, "SE(uri:*)");
    checkNilEncoding(&schema, WU_DOC_EXT, "\x80\x40\x14\x06\xe8\x00\x4f\x00\x28\x13\xc8\x0d\x00", 13,
            "AT(uri:*), extension wildcard union");
    checkNilEncoding(&schema, WU_DOC_NIL, "\x80\x40\x14\x06\xe8\xd0\x13\xc0\x0e", 9, "xsi:nil, AT(uri:*)");
    checkNilEncoding(&schema, WU_DOC_RES, "\x80\x40\x14\x06\xe9\x00", 6, "restriction without wildcard");
    destroySchema(&schema);
}
END_TEST

START_TEST(test_uri_wildcards_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/wildcard-uri-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x40\x14\x06\xe9\x80", 6, "SD SE:r SE:g CH:t EE EE ED ");
    checkNilDecoding(&schema, "\x80\x40\x14\x06\xe8\x00\x4f\x00\x28\x13\xc8\x0d\x00", 13,
            "SD SE:r SE:g CH:t EE SE:e AT:x CH:t AT:y CH:t EE EE ED ");
    checkNilDecoding(&schema, "\x80\x40\x14\x06\xe8\xd0\x13\xc0\x0e", 9,
            "SD SE:r SE:g CH:t EE SE:n AT:nil true AT:x CH:t EE EE ED ");
    checkNilDecoding(&schema, "\x80\x40\x14\x06\xe9\x00", 6, "SD SE:r SE:g CH:t EE SE:q EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/global-attributes.xsd (EXIficient 1.0.7; rexi does not
 * support attribute wildcard values). An attribute matched by AT(*) or AT(uri:*)
 * whose qname has a global declaration is typed by it (b boolean, i int, d 0..7 in
 * 3 bits); exip wrote and read every such value as a string. x has no global
 * declaration and stays a string. l uses d through ref="d". */

#define GA_W NIL_SDR, NIL_EL("w")

static const struct nilEv GA_DOC_ANY[] = {
    GA_W, {NIL_AT, "{urn:n}b", "true"}, {NIL_AT, "{urn:n}i", "-5"}, {NIL_AT, "x", "t"}, NIL_E, NIL_EED
};
static const struct nilEv GA_DOC_URI[] = {
    GA_W, NIL_E, NIL_EL("u"), {NIL_AT, "{urn:n}b", "false"}, {NIL_AT, "{urn:n}d", "5"}, NIL_E, NIL_EED
};
static const struct nilEv GA_DOC_REF[] = { GA_W, NIL_E, NIL_EL("l"), {NIL_AT, "{urn:n}d", "5"}, NIL_E, NIL_EED };
static const struct nilEv GA_DOC_ALL[] = {
    GA_W, {NIL_AT, "{urn:n}d", "3"}, NIL_E, NIL_EL("u"), {NIL_AT, "{urn:n}i", "7"}, NIL_E,
    NIL_EL("l"), {NIL_AT, "{urn:n}d", "2"}, NIL_E, NIL_EED
};

START_TEST(test_global_attribute_types) {
    EXIPSchema schema;
    QNameID qnameId;
    String str;

    parseSchema("SchemaStrict/global-attributes-xsd.exi", &schema);
    checkNilEncoding(&schema, GA_DOC_ANY, "\x80\x28\x00\xa8\x02\x82\x08\x13\xc0\x1b\xa6", 11, "AT(*) typed and untyped");
    checkNilEncoding(&schema, GA_DOC_URI, "\x80\x40\x00\x00\x0d\xc0", 6, "AT(uri:*) typed");
    checkNilEncoding(&schema, GA_DOC_REF, "\x80\x55", 2, "ref to a global attribute");
    checkNilEncoding(&schema, GA_DOC_ALL, "\x80\x28\x01\x70\x00\x80\xf1\x00", 8, "anonymous type, both wildcards");

    // The global attribute types are in the string tables; local names without one are not typed
    asciiToString("urn:n", &str, NULL, FALSE);
    fail_unless(lookupUri(&schema.uriTable, str, &qnameId.uriId), "urn:n not in the uri table");
    asciiToString("b", &str, NULL, FALSE);
    fail_unless(lookupLn(&schema.uriTable.uri[qnameId.uriId].lnTable, str, &qnameId.lnId), "b not in the ln table");
    fail_unless(GET_LN_URI_QNAME(schema.uriTable, qnameId).attrTypeId == SIMPLE_TYPE_BOOLEAN, "b is not xs:boolean");
    asciiToString("w", &str, NULL, FALSE);
    fail_unless(lookupLn(&schema.uriTable.uri[qnameId.uriId].lnTable, str, &qnameId.lnId), "w not in the ln table");
    fail_unless(GET_LN_URI_QNAME(schema.uriTable, qnameId).attrTypeId == INDEX_MAX, "w has an attribute type");
    destroySchema(&schema);
}
END_TEST

START_TEST(test_global_attribute_types_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/global-attributes-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x28\x00\xa8\x02\x82\x08\x13\xc0\x1b\xa6", 11,
            "SD SE:r SE:w AT:b true AT:i -5 AT:x CH:t EE EE ED ");
    checkNilDecoding(&schema, "\x80\x40\x00\x00\x0d\xc0", 6, "SD SE:r SE:w EE SE:u AT:b false AT:d 5 EE EE ED ");
    checkNilDecoding(&schema, "\x80\x55", 2, "SD SE:r SE:w EE SE:l AT:d 5 EE EE ED ");
    checkNilDecoding(&schema, "\x80\x28\x01\x70\x00\x80\xf1\x00", 8,
            "SD SE:r SE:w AT:d 3 EE SE:u AT:i 7 EE SE:l AT:d 2 EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/value-types.xsd (EXIficient 1.0.7 and rexi agree).
 * startElement reported a value type only when the start rule's last production was CH,
 * so simple content after attributes came back as VALUE_TYPE_NONE_CLASS, and nothing
 * reported the type an xsi:type cast selects. serialize.valueType reports the type in
 * the current state (e has no type: xs:anyType, mixed). Each event checks the type reported (startElement's for SE, then
 * serialize.valueType's), and the value is sent with it. */

enum vtKind { VT_SE, VT_AT, VT_XT, VT_CH, VT_EE, VT_END };

struct vtEv {
    enum vtKind kind;
    const char* text;      /* element, attribute or xsi:type local name; CH value */
    EXITypeClass expected; /* SE: startElement's report; AT, XT, CH: serialize.valueType's */
};

static void encodeValueTypeDoc(EXIPSchema* schema, const struct vtEv* evs, const char* exi, size_t len, const char* what) {
    EXIStream strm;
    char buf[NIL_BUF_SIZE];
    BinaryBuffer buffer;
    struct nilSink sink;
    String ns, xsNs, xsiNs, xsiType, ln, val, emptyStr;
    QName qname;
    EXITypeClass valueType;
    errorCode err;
    unsigned int i;

    memset(buf, 0, sizeof buf);
    buffer.buf = buf;
    buffer.bufLen = sizeof buf;
    buffer.bufContent = 0;
    buffer.ioStrm.readWriteToStream = nilSinkWrite;
    buffer.ioStrm.stream = &sink;
    sink.len = 0;
    asciiToString("urn:n", &ns, NULL, FALSE);
    asciiToString("http://www.w3.org/2001/XMLSchema", &xsNs, NULL, FALSE);
    asciiToString("http://www.w3.org/2001/XMLSchema-instance", &xsiNs, NULL, FALSE);
    asciiToString("type", &xsiType, NULL, FALSE);
    getEmptyString(&emptyStr);

    serialize.initHeader(&strm);
    strm.header.has_cookie = FALSE;
    strm.header.has_options = FALSE;
    nilOptions(&strm.header.opts);
    err = serialize.initStream(&strm, buffer, schema);
    fail_unless(err == EXIP_OK, "%s: initStream returns error code %d", what, err);
    err = serialize.exiHeader(&strm);
    fail_unless(err == EXIP_OK, "%s: exiHeader returns error code %d", what, err);
    err = serialize.startDocument(&strm);
    fail_unless(err == EXIP_OK, "%s: startDocument returns error code %d", what, err);

    for (i = 0; evs[i].kind != VT_END; i++) {
        qname.prefix = NULL;
        switch (evs[i].kind) {
            case VT_SE:
                asciiToString(evs[i].text, &ln, NULL, FALSE);
                qname.uri = &ns;
                qname.localName = &ln;
                err = serialize.startElement(&strm, qname, &valueType);
                break;
            case VT_AT:
                asciiToString(evs[i].text, &ln, NULL, FALSE);
                qname.uri = &emptyStr;
                qname.localName = &ln;
                err = serialize.attribute(&strm, qname, TRUE, &valueType);
                break;
            case VT_XT:
                qname.uri = &xsiNs;
                qname.localName = &xsiType;
                err = serialize.attribute(&strm, qname, TRUE, &valueType);
                if (err == EXIP_OK) {
                    asciiToString(evs[i].text, &ln, NULL, FALSE);
                    qname.uri = &xsNs;
                    qname.localName = &ln;
                    err = serialize.qnameData(&strm, qname);
                }
                break;
            case VT_CH:
                err = EXIP_OK;
                break;
            case VT_EE:
                err = serialize.endElement(&strm);
                break;
            default:
                err = EXIP_UNEXPECTED_ERROR;
        }
        fail_unless(err == EXIP_OK, "%s: event %u returns error code %d", what, i, err);

        if (evs[i].kind == VT_EE)
            continue;
        if (evs[i].kind != VT_SE) {
            err = serialize.valueType(&strm, &valueType);
            fail_unless(err == EXIP_OK, "%s: event %u: valueType returns error code %d", what, i, err);
        }
        fail_unless(valueType == evs[i].expected, "%s: event %u: value type %d, expected %d",
                what, i, (int) valueType, (int) evs[i].expected);

        if (evs[i].kind == VT_AT || evs[i].kind == VT_CH) {
            const char* v = evs[i].kind == VT_AT ? "t" : evs[i].text;
            if (evs[i].kind == VT_AT && evs[i].text[0] == 'k')
                v = "1";
            if (valueType == VALUE_TYPE_DATE_TIME_CLASS) {
                EXIPDateTime dt;
                memset(&dt, 0, sizeof dt);
                dt.dateTime.tm_hour = dt.dateTime.tm_min = dt.dateTime.tm_sec = INT_MIN;
                dt.dateTime.tm_year = atoi(v) - 1900;
                dt.dateTime.tm_mon = atoi(v + 5) - 1;
                dt.dateTime.tm_mday = atoi(v + 8);
                err = serialize.dateTimeData(&strm, dt);
            } else if (valueType == VALUE_TYPE_INTEGER_CLASS)
                err = serialize.intData(&strm, atoi(v));
            else if (valueType == VALUE_TYPE_BOOLEAN_CLASS)
                err = serialize.booleanData(&strm, strcmp(v, "true") == 0);
            else {
                asciiToString(v, &val, NULL, FALSE);
                err = serialize.stringData(&strm, val);
            }
            fail_unless(err == EXIP_OK, "%s: event %u: value returns error code %d", what, i, err);
        }
    }
    err = serialize.endDocument(&strm);
    fail_unless(err == EXIP_OK, "%s: endDocument returns error code %d", what, err);
    err = serialize.closeEXIStream(&strm);
    fail_unless(err == EXIP_OK, "%s: closeEXIStream returns error code %d", what, err);
    fail_unless(sink.len >= len && memcmp(sink.data, exi, len) == 0, "%s: encoding differs from EXIficient", what);
}

#define VT_D {VT_SE, "d", VALUE_TYPE_DATE_TIME_CLASS}, {VT_AT, "a", VALUE_TYPE_STRING_CLASS}, \
    {VT_CH, "2010-03-11", VALUE_TYPE_DATE_TIME_CLASS}, {VT_EE, NULL, 0}
#define VT_R {VT_SE, "r", VALUE_TYPE_NONE_CLASS}

static const struct vtEv VT_DOC_D[] = { VT_R, VT_D, {VT_EE, NULL, 0}, {VT_END, NULL, 0} };
static const struct vtEv VT_DOC_O[] = {
    VT_R, VT_D, {VT_SE, "o", VALUE_TYPE_INTEGER_CLASS}, {VT_AT, "k", VALUE_TYPE_INTEGER_CLASS},
    {VT_CH, "5", VALUE_TYPE_INTEGER_CLASS}, {VT_EE, NULL, 0}, {VT_EE, NULL, 0}, {VT_END, NULL, 0}
};
static const struct vtEv VT_DOC_M[] = {
    VT_R, VT_D, {VT_SE, "o", VALUE_TYPE_INTEGER_CLASS}, {VT_CH, "5", VALUE_TYPE_INTEGER_CLASS}, {VT_EE, NULL, 0},
    {VT_SE, "m", VALUE_TYPE_UNTYPED_CLASS}, {VT_SE, "e", VALUE_TYPE_UNTYPED_CLASS}, {VT_EE, NULL, 0},
    {VT_CH, "t", VALUE_TYPE_UNTYPED_CLASS}, {VT_EE, NULL, 0}, {VT_EE, NULL, 0}, {VT_END, NULL, 0}
};
static const struct vtEv VT_DOC_CAST[] = {
    {VT_SE, "any", VALUE_TYPE_UNTYPED_CLASS}, {VT_XT, "date", VALUE_TYPE_DATE_TIME_CLASS},
    {VT_CH, "2010-04-29", VALUE_TYPE_DATE_TIME_CLASS}, {VT_EE, NULL, 0}, {VT_END, NULL, 0}
};

START_TEST(test_value_type_reporting) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/value-types-xsd.exi", &schema);
    encodeValueTypeDoc(&schema, VT_DOC_D, "\x80\x40\xdd\x01\x46\xb4", 6, "simple content after a required attribute");
    encodeValueTypeDoc(&schema, VT_DOC_O, "\x80\x40\xdd\x01\x46\xb0\x00\x81\x60", 9, "simple content after an optional attribute");
    encodeValueTypeDoc(&schema, VT_DOC_M, "\x80\x40\xdd\x01\x46\xb1\x02\x85\x01\x00", 10, "mixed content");
    encodeValueTypeDoc(&schema, VT_DOC_CAST, "\x80\x24\x00\x44\x14\x9d\x00", 7, "xsi:type cast to xs:date");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/schema-order.xsd (EXIficient 1.0.7; rexi agrees on loop, q
 * e0 and r). SE(qname) in schema order, also after a loop back into a choice.
 * AT(uri:*) lexically by uri ("a:x" before the XML namespace), SE(uri:*) in namespace
 * list order (urn:z, urn:a). The named empty type E0 has a sub-type; the anonymous
 * empty type of q must not become typecastable with it. */

#define SO_ROOT(n) {NIL_SD, NULL, NULL}, NIL_EL(n)
#define SO_END NIL_E, {NIL_ED, NULL, NULL}, {NIL_END, NULL, NULL}

static const struct nilEv SO_DOC_LOOP[] = {
    SO_ROOT("loop"), NIL_EL("b"), NIL_E, NIL_EL("c"), NIL_E, NIL_EL("b"), NIL_E, NIL_EL("c"), NIL_E,
    NIL_EL("a"), NIL_E, SO_END
};
static const struct nilEv SO_DOC_LOOP_A[] = {
    SO_ROOT("loop"), NIL_EL("a"), NIL_E, NIL_EL("b"), NIL_E, NIL_EL("c"), NIL_E, NIL_EL("a"), NIL_E, SO_END
};
static const struct nilEv SO_DOC_SE_URI[] = {
    SO_ROOT("wild"), NIL_EL("{urn:a}x"), NIL_E, NIL_EL("{urn:z}y"), NIL_E, SO_END
};
static const struct nilEv SO_DOC_AT_URI[] = {
    SO_ROOT("wild"), {NIL_AT, "{a:x}k", "t"}, {NIL_AT, "{http://www.w3.org/XML/1998/namespace}lang", "te"},
    NIL_EL("{urn:a}x"), NIL_E, SO_END
};
static const struct nilEv SO_DOC_Q[] = { SO_ROOT("q"), SO_END };
static const struct nilEv SO_DOC_E0[] = { SO_ROOT("e0"), XT("E1"), SO_END };
static const struct nilEv SO_DOC_R[] = { SO_ROOT("r"), NIL_EL("q"), NIL_E, NIL_EL("e0"), NIL_E, NIL_EL("q"), NIL_E, SO_END };

START_TEST(test_schema_order) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/schema-order-xsd.exi", &schema);
    checkNilEncoding(&schema, SO_DOC_LOOP, "\x80\x34\x94\x85\x00", 5, "SE(qname) after a loop back");
    checkNilEncoding(&schema, SO_DOC_LOOP_A, "\x80\x24\xa4\x28", 4, "SE(qname) in schema order");
    checkNilEncoding(&schema, SO_DOC_SE_URI, "\x80\x98\x13\xc0\x01\x3c\x80", 7, "SE(uri:*) in namespace list order");
    checkNilEncoding(&schema, SO_DOC_AT_URI, "\x80\x80\x13\x58\x1b\xa2\x01\x02\x3a\x32\xe0\x4f\x04", 13,
            "AT(uri:*) lexically by uri");
    checkNilEncoding(&schema, SO_DOC_Q, "\x80\x40", 2, "anonymous empty type not typecastable");
    checkNilEncoding(&schema, SO_DOC_E0, "\x80\x17\x00\x10", 4, "named empty type with a sub-type");
    checkNilEncoding(&schema, SO_DOC_R, "\x80\x64\x40", 3, "empty types after one another");
    destroySchema(&schema);
}
END_TEST

START_TEST(test_schema_order_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/schema-order-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x34\x94\x85\x00", 5, "SD SE:loop SE:b EE SE:c EE SE:b EE SE:c EE SE:a EE EE ED ");
    checkNilDecoding(&schema, "\x80\x24\xa4\x28", 4, "SD SE:loop SE:a EE SE:b EE SE:c EE SE:a EE EE ED ");
    checkNilDecoding(&schema, "\x80\x98\x13\xc0\x01\x3c\x80", 7, "SD SE:wild SE:x EE SE:y EE EE ED ");
    checkNilDecoding(&schema, "\x80\x80\x13\x58\x1b\xb2\x01\x02\x32\xb7\x60\x4f\x04", 13,
            "SD SE:wild AT:k CH:v AT:lang CH:en SE:x EE EE ED ");
    checkNilDecoding(&schema, "\x80\x40", 2, "SD SE:q EE ED ");
    checkNilDecoding(&schema, "\x80\x17\x00\x10", 4, "SD SE:e0 AT:type QN:E1 EE ED ");
    checkNilDecoding(&schema, "\x80\x64\x40", 3, "SD SE:r SE:q EE SE:e0 EE SE:q EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/duplicate-terminals.xsd (EXIficient 1.0.7 and rexi agree).
 * A terminal that leads to two states (continue a repeated particle, or start the
 * next iteration of the enclosing group) is one production to the union of both states
 * (8.5.4.2.2). exip asserted in Debug and wrote wrong codes in Release. */

#define DT_EL(n) NIL_EL(n), NIL_E

static const struct nilEv DT_DOC_SSC[] = { SO_ROOT("r"), DT_EL("s"), DT_EL("s"), DT_EL("c"), SO_END };
static const struct nilEv DT_DOC_SS[] = { SO_ROOT("r"), DT_EL("s"), DT_EL("s"), SO_END };
static const struct nilEv DT_DOC_SC[] = { SO_ROOT("r"), DT_EL("s"), DT_EL("c"), SO_END };
static const struct nilEv DT_DOC_CSS[] = { SO_ROOT("r"), DT_EL("c"), DT_EL("s"), DT_EL("s"), SO_END };
static const struct nilEv DT_DOC_XXYX[] = { SO_ROOT("m"), DT_EL("x"), DT_EL("x"), DT_EL("y"), DT_EL("x"), SO_END };
static const struct nilEv DT_DOC_XYXY[] = { SO_ROOT("m"), DT_EL("x"), DT_EL("y"), DT_EL("x"), DT_EL("y"), SO_END };

START_TEST(test_duplicate_terminals) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/duplicate-terminals-xsd.exi", &schema);
    checkNilEncoding(&schema, DT_DOC_SSC, "\x80\x48\x4a", 3, "s s c");
    checkNilEncoding(&schema, DT_DOC_SS, "\x80\x48\x50", 3, "s s");
    checkNilEncoding(&schema, DT_DOC_SC, "\x80\x49\x40", 3, "s c");
    checkNilEncoding(&schema, DT_DOC_CSS, "\x80\x68\x44", 3, "c s s");
    checkNilEncoding(&schema, DT_DOC_XXYX, "\x80\x10\x94\x50", 4, "x x y x");
    checkNilEncoding(&schema, DT_DOC_XYXY, "\x80\x12\x89\x40", 4, "x y x y");
    destroySchema(&schema);
}
END_TEST

START_TEST(test_duplicate_terminals_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/duplicate-terminals-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x48\x4a", 3, "SD SE:r SE:s EE SE:s EE SE:c EE EE ED ");
    checkNilDecoding(&schema, "\x80\x48\x50", 3, "SD SE:r SE:s EE SE:s EE EE ED ");
    checkNilDecoding(&schema, "\x80\x49\x40", 3, "SD SE:r SE:s EE SE:c EE EE ED ");
    checkNilDecoding(&schema, "\x80\x68\x44", 3, "SD SE:r SE:c EE SE:s EE SE:s EE EE ED ");
    checkNilDecoding(&schema, "\x80\x10\x94\x50", 4, "SD SE:m SE:x EE SE:x EE SE:y EE SE:x EE EE ED ");
    checkNilDecoding(&schema, "\x80\x12\x89\x40", 4, "SD SE:m SE:x EE SE:y EE SE:x EE SE:y EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/all-group.xsd (EXIficient 1.0.7 and rexi agree). An
 * xs:all group is its particles in any order (8.5.4.1.8.3); exip could not load a schema
 * with one (EXIP_NOT_IMPLEMENTED_YET). */

#define AG_EMPTY(n) {VT_SE, n, VALUE_TYPE_UNTYPED_CLASS}, {VT_EE, NULL, 0}
#define AG_END {VT_EE, NULL, 0}, {VT_END, NULL, 0}

static const struct vtEv AG_DOC_AB[] = { {VT_SE, "r", VALUE_TYPE_NONE_CLASS}, AG_EMPTY("a"), AG_EMPTY("b"), AG_END };
static const struct vtEv AG_DOC_BA[] = { {VT_SE, "r", VALUE_TYPE_NONE_CLASS}, AG_EMPTY("b"), AG_EMPTY("a"), AG_END };
static const struct vtEv AG_DOC_A[] = { {VT_SE, "r", VALUE_TYPE_NONE_CLASS}, AG_EMPTY("a"), AG_END };
static const struct vtEv AG_DOC_O[] = {
    {VT_SE, "o", VALUE_TYPE_NONE_CLASS}, {VT_AT, "k", VALUE_TYPE_INTEGER_CLASS},
    {VT_SE, "z", VALUE_TYPE_BOOLEAN_CLASS}, {VT_CH, "true", VALUE_TYPE_BOOLEAN_CLASS}, {VT_EE, NULL, 0},
    {VT_SE, "x", VALUE_TYPE_INTEGER_CLASS}, {VT_CH, "5", VALUE_TYPE_INTEGER_CLASS}, {VT_EE, NULL, 0},
    {VT_SE, "y", VALUE_TYPE_STRING_CLASS}, {VT_CH, "t", VALUE_TYPE_STRING_CLASS}, {VT_EE, NULL, 0}, AG_END
};
static const struct vtEv AG_DOC_O_EMPTY[] = { {VT_SE, "o", VALUE_TYPE_NONE_CLASS}, AG_END };
static const struct vtEv AG_DOC_G[] = { {VT_SE, "g", VALUE_TYPE_NONE_CLASS}, AG_EMPTY("q"), AG_EMPTY("p"), AG_END };

START_TEST(test_all_group) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/all-group-xsd.exi", &schema);
    encodeValueTypeDoc(&schema, AG_DOC_AB, "\x80\x84\xa8", 3, "a b");
    encodeValueTypeDoc(&schema, AG_DOC_BA, "\x80\x94\x28", 3, "b a");
    encodeValueTypeDoc(&schema, AG_DOC_A, "\x80\x85\x00", 3, "a only");
    encodeValueTypeDoc(&schema, AG_DOC_O, "\x80\x40\x06\x80\x2a\x03\x74\xc0", 8, "optional all, any order, typed");
    encodeValueTypeDoc(&schema, AG_DOC_O_EMPTY, "\x80\x60", 2, "optional all, empty");
    encodeValueTypeDoc(&schema, AG_DOC_G, "\x80\x14\x28", 3, "all in a named group");
    destroySchema(&schema);
}
END_TEST

START_TEST(test_all_group_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/all-group-xsd.exi", &schema);
    checkNilDecoding(&schema, "\x80\x84\xa8", 3, "SD SE:r SE:a EE SE:b EE EE ED ");
    checkNilDecoding(&schema, "\x80\x94\x28", 3, "SD SE:r SE:b EE SE:a EE EE ED ");
    checkNilDecoding(&schema, "\x80\x85\x00", 3, "SD SE:r SE:a EE EE ED ");
    checkNilDecoding(&schema, "\x80\x40\x06\x80\x2a\x03\x74\xc0", 8,
            "SD SE:o AT:k 1 SE:z true EE SE:x 5 EE SE:y CH:t EE EE ED ");
    checkNilDecoding(&schema, "\x80\x60", 2, "SD SE:o EE ED ");
    checkNilDecoding(&schema, "\x80\x14\x28", 3, "SD SE:g SE:q EE SE:p EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/utf8.xsd (EXIficient 1.0.7 and rexi agree).
 * non-ASCII local names and values (the repeated one is a value-table hit, the last
 * title has a 4-byte character); List content of an element, whose items are values
 * of the element (the repeated x is a hit in its local partition). Strings are UTF-8. */

#define U8_SLOWNIK "S\xC5\x82ownik"
#define U8_JEZYK "j\xC4\x99zyk"
#define U8_TYTUL "Tytu\xC5\x82"
#define U8_LEKSEIS "\xCE\x9B\xCE\xAD\xCE\xBE\xCE\xB5\xCE\xB9\xCF\x82"
#define U8_CHINESE "\xE4\xB8\xAD\xE6\x96\x87"
#define U8_POEM "\xE9\x9D\x99\xE5\xA4\x9C\xE6\x80\x9D"
#define U8_ZAZOLC "Za\xC5\xBC\xC3\xB3\xC5\x82\xC4\x87 \xF0\x9D\x84\x9E"
#define U8_MOON "\xE6\x9C\x88\xE5\x85\x89"
#define U8_RARE "\xF0\xA0\x80\x8B"

static void encodeUtf8Doc(EXIPSchema* schema, exip_bool full, const char* exi, size_t len) {
    EXIStream strm;
    char buf[NIL_BUF_SIZE];
    BinaryBuffer buffer;
    struct nilSink sink;
    String ns, ln, val, empty;
    QName qname;
    EXITypeClass valueType;
    errorCode err = EXIP_OK;
    const char* titles[3] = {U8_POEM, U8_POEM, U8_ZAZOLC};
    const char* items[4] = {U8_MOON, U8_RARE, "x", "x"};
    unsigned int i, nTitles = full ? 3 : 1, nItems = full ? 4 : 2;

    memset(buf, 0, sizeof buf);
    buffer.buf = buf;
    buffer.bufLen = sizeof buf;
    buffer.bufContent = 0;
    buffer.ioStrm.readWriteToStream = nilSinkWrite;
    buffer.ioStrm.stream = &sink;
    sink.len = 0;
    asciiToString("urn:n", &ns, NULL, FALSE);
    getEmptyString(&empty);
    qname.prefix = NULL;

    serialize.initHeader(&strm);
    strm.header.has_cookie = FALSE;
    strm.header.has_options = FALSE;
    nilOptions(&strm.header.opts);
    err += serialize.initStream(&strm, buffer, schema);
    err += serialize.exiHeader(&strm);
    err += serialize.startDocument(&strm);
    qname.uri = &ns;
    asciiToString(U8_SLOWNIK, &ln, NULL, FALSE);
    qname.localName = &ln;
    err += serialize.startElement(&strm, qname, &valueType);
    if (full) {
        qname.uri = &empty;
        asciiToString(U8_JEZYK, &ln, NULL, FALSE);
        err += serialize.attribute(&strm, qname, TRUE, &valueType);
        asciiToString(U8_CHINESE, &val, NULL, FALSE);
        err += serialize.stringData(&strm, val);
    }
    fail_unless(err == EXIP_OK, "start returns error code %d", err);
    for (i = 0; i < nTitles; i++) {
        qname.uri = &ns;
        asciiToString(U8_TYTUL, &ln, NULL, FALSE);
        err = serialize.startElement(&strm, qname, &valueType);
        asciiToString(full ? titles[i] : "a", &val, NULL, FALSE);
        if (err == EXIP_OK)
            err = serialize.stringData(&strm, val);
        if (err == EXIP_OK)
            err = serialize.endElement(&strm);
        fail_unless(err == EXIP_OK, "title %u returns error code %d", i, err);
    }
    qname.uri = &ns;
    asciiToString(U8_LEKSEIS, &ln, NULL, FALSE);
    err = serialize.startElement(&strm, qname, &valueType);
    fail_unless(err == EXIP_OK && valueType == VALUE_TYPE_LIST_CLASS, "list element: error %d, value type %d", err, (int) valueType);
    err = serialize.listData(&strm, nItems);
    fail_unless(err == EXIP_OK, "listData returns error code %d", err);
    for (i = 0; i < nItems; i++) {
        asciiToString(full ? items[i] : (i == 0 ? "b" : "c"), &val, NULL, FALSE);
        err = serialize.stringData(&strm, val);
        fail_unless(err == EXIP_OK, "list item %u returns error code %d", i, err);
    }
    err += serialize.endElement(&strm);
    err += serialize.endElement(&strm);
    err += serialize.endDocument(&strm);
    err += serialize.closeEXIStream(&strm);
    fail_unless(err == EXIP_OK, "end returns error code %d", err);
    if (sink.len < len || memcmp(sink.data, exi, len) != 0) {
        char hex[2 * NIL_BUF_SIZE + 1];
        size_t k;
        for (k = 0; k < sink.len && k < NIL_BUF_SIZE; k++)
            snprintf(&hex[2 * k], 3, "%02x", (unsigned char) sink.data[k]);
        hex[2 * k] = '\0';
        for (k = 0; k < len && k < sink.len && sink.data[k] == exi[k]; k++)
            ;
        fail("encoding %s (%u bytes) differs from EXIficient (%u bytes) at byte %u", hex, (unsigned) sink.len, (unsigned) len, (unsigned) k);
    }
}

#define U8_FULL_EXI "\x80\x00\x95\xb3\x80\x30\xf9\x60\x20\x5d\x9a\xe0\x29\xcb\x20\x19\xdc\x00\x10\x00\x02\x96\x98\x7f\x00\xbc\xc0\x70\x80\xa1\xc0\x88\x27\xa8\x81\xd0\x40\x48\x8c\xe0\x1c\x9a\x20\x10\x38\xb8\x00\x80\x37\x80\x08"
#define U8_SHORT_EXI "\x80\x20\x36\x14\x08\x0d\x88\x0d\x8c"

START_TEST(test_utf8_strings) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/utf8-xsd.exi", &schema);
    encodeUtf8Doc(&schema, TRUE, U8_FULL_EXI, 51);
    encodeUtf8Doc(&schema, FALSE, U8_SHORT_EXI, 9);
    destroySchema(&schema);
}
END_TEST

START_TEST(test_utf8_strings_decode) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/utf8-xsd.exi", &schema);
    checkNilDecoding(&schema, U8_FULL_EXI, 51,
            "SD SE:" U8_SLOWNIK " AT:" U8_JEZYK " CH:" U8_CHINESE " SE:" U8_TYTUL " CH:" U8_POEM " EE SE:"
            U8_TYTUL " CH:" U8_POEM " EE SE:" U8_TYTUL " CH:" U8_ZAZOLC " EE SE:" U8_LEKSEIS
            " CH:" U8_MOON " CH:" U8_RARE " CH:x CH:x EE EE ED ");
    checkNilDecoding(&schema, U8_SHORT_EXI, 9,
            "SD SE:" U8_SLOWNIK " SE:" U8_TYTUL " CH:a EE SE:" U8_LEKSEIS " CH:b CH:c EE EE ED ");
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/value-max-length.xsd, valueMaxLength=3. The limit
 * counts characters (7.3.3), so a 3-character value of 6 or 6+ bytes is added to the
 * value partitions and its repeat is a hit. The first vector is EXIficient 1.0.7's (=
 * rexi); for the second, with a non-BMP character, EXIficient counts UTF-16 units and
 * differs, and the vector is rexi's (the spec's), see the schema's header. */

#define VM_S(v) NIL_EL("s"), {NIL_CH, NULL, v}, NIL_E
#define U8_ZOL "\xC5\xBC\xC3\xB3\xC5\x82"
#define U8_AB_CLEF "ab\xF0\x9D\x84\x9E"

static const struct nilEv VM_DOC_BMP[] = {
    SO_ROOT("r"), VM_S("abc"), VM_S("abc"), VM_S(U8_ZOL), VM_S(U8_ZOL), VM_S("abcd"), VM_S("abcd"), SO_END
};
static const struct nilEv VM_DOC_CLEF[] = { SO_ROOT("r"), VM_S(U8_AB_CLEF), VM_S(U8_AB_CLEF), SO_END };

START_TEST(test_value_max_length_characters) {
    EXIPSchema schema;

    parseSchema("SchemaStrict/value-max-length-xsd.exi", &schema);
    nilValueMaxLength = 3;
    checkNilEncoding(&schema, VM_DOC_BMP,
            "\x80\x01\x58\x58\x98\xc0\x00\x17\xf0\x0b\xcc\x07\x08\x08\x00\x80\xcc\x2c\x4c\x6c\x80\x33\x0b\x13\x1b\x24",
            26, "BMP values");
    checkNilEncoding(&schema, VM_DOC_CLEF, "\x80\x01\x58\x58\xa7\xa8\x81\xc0\x08", 9, "non-BMP value");
    checkNilDecoding(&schema,
            "\x80\x01\x58\x58\x98\xc0\x00\x17\xf0\x0b\xcc\x07\x08\x08\x00\x80\xcc\x2c\x4c\x6c\x80\x33\x0b\x13\x1b\x24",
            26, "SD SE:r SE:s CH:abc EE SE:s CH:abc EE SE:s CH:" U8_ZOL " EE SE:s CH:" U8_ZOL
            " EE SE:s CH:abcd EE SE:s CH:abcd EE EE ED ");
    checkNilDecoding(&schema, "\x80\x01\x58\x58\xa7\xa8\x81\xc0\x08", 9,
            "SD SE:r SE:s CH:" U8_AB_CLEF " EE SE:s CH:" U8_AB_CLEF " EE EE ED ");
    nilValueMaxLength = INDEX_MAX;
    destroySchema(&schema);
}
END_TEST

/* On SchemaStrict/binary-types.xsd (EXIficient 1.0.7 and rexi agree).
 * serialize.exiType and parse.valueExiType tell xs:hexBinary (and Hex4, derived from
 * it) from xs:base64Binary (and B64), which share VALUE_TYPE_BINARY_CLASS. */

#define BT_EXI "\x80\x00\x60\x00\x20\x40\x20\xa0\xb0\x16\x57\xf0\x0c\x04\x08\x0c\x0a\xfb\xbc\x0c\x10\x14\x18"

struct btValue {
    const char* name;    /* attribute (no namespace) or element in urn:n */
    exip_bool isAttr;
    const char* bytes;
    Index nbytes;
    EXIType expected;
};

static const struct btValue BT_VALUES[] = {
    {"b", TRUE, "\x00\x01\x02", 3, VALUE_TYPE_BINARY},
    {"h", TRUE, "\x0a\x0b", 2, VALUE_TYPE_HEX_BINARY},
    {"hx", FALSE, "\xca\xfe", 2, VALUE_TYPE_HEX_BINARY},
    {"b6", FALSE, "\x01\x02\x03", 3, VALUE_TYPE_BINARY},
    {"dh", FALSE, "\xbe\xef", 2, VALUE_TYPE_HEX_BINARY},
    {"db", FALSE, "\x04\x05\x06", 3, VALUE_TYPE_BINARY}
};

START_TEST(test_binary_value_types) {
    EXIPSchema schema;
    EXIStream strm;
    char buf[NIL_BUF_SIZE];
    BinaryBuffer buffer;
    struct nilSink sink;
    String ns, empty, ln;
    QName qname;
    EXITypeClass valueType;
    EXIType exiType;
    errorCode err = EXIP_OK;
    unsigned int i;

    parseSchema("SchemaStrict/binary-types-xsd.exi", &schema);
    memset(buf, 0, sizeof buf);
    buffer.buf = buf;
    buffer.bufLen = sizeof buf;
    buffer.bufContent = 0;
    buffer.ioStrm.readWriteToStream = nilSinkWrite;
    buffer.ioStrm.stream = &sink;
    sink.len = 0;
    asciiToString("urn:n", &ns, NULL, FALSE);
    getEmptyString(&empty);
    qname.prefix = NULL;

    serialize.initHeader(&strm);
    strm.header.has_cookie = FALSE;
    strm.header.has_options = FALSE;
    nilOptions(&strm.header.opts);
    err += serialize.initStream(&strm, buffer, &schema);
    err += serialize.exiHeader(&strm);
    err += serialize.startDocument(&strm);
    qname.uri = &ns;
    asciiToString("r", &ln, NULL, FALSE);
    qname.localName = &ln;
    err += serialize.startElement(&strm, qname, &valueType);
    fail_unless(err == EXIP_OK, "start returns error code %d", err);

    for (i = 0; i < sizeof BT_VALUES / sizeof BT_VALUES[0]; i++) {
        const struct btValue* v = &BT_VALUES[i];
        qname.uri = v->isAttr ? &empty : &ns;
        asciiToString(v->name, &ln, NULL, FALSE);
        qname.localName = &ln;
        err = v->isAttr ? serialize.attribute(&strm, qname, TRUE, &valueType)
                        : serialize.startElement(&strm, qname, &valueType);
        fail_unless(err == EXIP_OK, "%s returns error code %d", v->name, err);
        fail_unless(serialize.valueType(&strm, &valueType) == EXIP_OK && valueType == VALUE_TYPE_BINARY_CLASS,
                "%s: value type class %d", v->name, (int) valueType);
        fail_unless(serialize.exiType(&strm, &exiType) == EXIP_OK && exiType == v->expected,
                "%s: exiType %d, expected %d", v->name, (int) exiType, (int) v->expected);
        err = serialize.binaryData(&strm, v->bytes, v->nbytes);
        if (err == EXIP_OK && !v->isAttr)
            err = serialize.endElement(&strm);
        fail_unless(err == EXIP_OK, "%s value returns error code %d", v->name, err);
    }
    err += serialize.endElement(&strm);
    err += serialize.endDocument(&strm);
    err += serialize.closeEXIStream(&strm);
    fail_unless(err == EXIP_OK, "end returns error code %d", err);
    fail_unless(sink.len >= 23 && memcmp(sink.data, BT_EXI, 23) == 0, "encoding differs from EXIficient");
    destroySchema(&schema);
}
END_TEST

struct btDecode {
    Parser* parser;
    unsigned int count;
    EXIType types[8];
    char bytes[8][4];
};

static errorCode bt_binary(const char* binary_val, Index nbytes, void* app_data) {
    struct btDecode* d = (struct btDecode*) app_data;
    if (d->count >= 8 || nbytes > 4 || parse.valueExiType(d->parser, &d->types[d->count]) != EXIP_OK)
        return EXIP_HANDLER_STOP;
    memcpy(d->bytes[d->count], binary_val, nbytes);
    d->count++;
    return EXIP_OK;
}

START_TEST(test_binary_value_types_decode) {
    EXIPSchema schema;
    Parser parser;
    BinaryBuffer buffer;
    char buf[NIL_BUF_SIZE];
    struct btDecode d;
    errorCode err;
    unsigned int i;

    parseSchema("SchemaStrict/binary-types-xsd.exi", &schema);
    memcpy(buf, BT_EXI, 23);
    buffer.buf = buf;
    buffer.bufLen = 23;
    buffer.bufContent = 23;
    buffer.ioStrm.readWriteToStream = NULL;
    buffer.ioStrm.stream = NULL;
    memset(&d, 0, sizeof d);
    d.parser = &parser;

    err = initParser(&parser, buffer, &d);
    fail_unless(err == EXIP_OK, "initParser returns error code %d", err);
    nilOptions(&parser.strm.header.opts);
    parser.handler.binaryData = bt_binary;
    err = parseHeader(&parser, TRUE);
    fail_unless(err == EXIP_OK, "parseHeader returns error code %d", err);
    err = setSchema(&parser, &schema);
    fail_unless(err == EXIP_OK, "setSchema returns error code %d", err);
    while ((err = parseNext(&parser)) == EXIP_OK)
        ;
    destroyParser(&parser);
    fail_unless(err == EXIP_PARSING_COMPLETE, "parsing returns error code %d", err);
    fail_unless(d.count == 6, "%u binary values decoded", d.count);
    for (i = 0; i < 6; i++) {
        fail_unless(d.types[i] == BT_VALUES[i].expected, "%s: valueExiType %d, expected %d",
                BT_VALUES[i].name, (int) d.types[i], (int) BT_VALUES[i].expected);
        fail_unless(memcmp(d.bytes[i], BT_VALUES[i].bytes, BT_VALUES[i].nbytes) == 0, "%s: bytes", BT_VALUES[i].name);
    }
    destroySchema(&schema);
}
END_TEST

static Index nilQNameGrammar(EXIPSchema* schema, const char* ln, exip_bool elem) {
    String str;
    QNameID qnameId;

    asciiToString("urn:n", &str, NULL, FALSE);
    fail_unless(lookupUri(&schema->uriTable, str, &qnameId.uriId), "urn:n not in the uri partition");
    asciiToString(ln, &str, NULL, FALSE);
    fail_unless(lookupLn(&schema->uriTable.uri[qnameId.uriId].lnTable, str, &qnameId.lnId),
            "%s not in the urn:n local names", ln);
    return elem ? GET_LN_URI_QNAME(schema->uriTable, qnameId).elemGrammar
            : GET_LN_URI_QNAME(schema->uriTable, qnameId).typeGrammar;
}

/* The type grammars stay non-nillable (xsi:type casts and other elements use them);
 * a nillable element of a named type gets its own grammar sharing the type's rules. */
START_TEST(test_nillable_type_grammars_shared) {
    EXIPSchema schema;
    Index num, pt, g, h;

    parseSchema("SchemaStrict/nillable-types-xsd.exi", &schema);
    num = nilQNameGrammar(&schema, "Num", FALSE);
    pt = nilQNameGrammar(&schema, "Pt", FALSE);
    g = nilQNameGrammar(&schema, "g", TRUE);
    h = nilQNameGrammar(&schema, "h", TRUE);

    fail_if(IS_NILLABLE(schema.grammarTable.grammar[num].props), "type grammar Num is nillable");
    fail_if(IS_NILLABLE(schema.grammarTable.grammar[pt].props), "type grammar Pt is nillable");
    fail_unless(h == num, "h uses grammar %u, expected Num's %u", (unsigned int) h, (unsigned int) num);
    fail_unless(g != num && IS_NILLABLE(schema.grammarTable.grammar[g].props),
            "g uses grammar %u (Num's is %u), nillable %d", (unsigned int) g, (unsigned int) num,
            IS_NILLABLE(schema.grammarTable.grammar[g].props));
    fail_unless(schema.grammarTable.grammar[g].rule == schema.grammarTable.grammar[num].rule,
            "g does not share Num's rules");
    destroySchema(&schema);
}
END_TEST

Suite* exip_suite(void) {
    Suite *s = suite_create("Strict Grammar");

    {
        TCase *tc_builtin = tcase_create("Strict Grammar");
        tcase_add_test(tc_builtin, test_acceptance_for_A_01);
        tcase_add_test(tc_builtin, test_acceptance_for_A_01_exip1);
        tcase_add_test(tc_builtin, test_acceptance_for_A_01b);
        tcase_add_test(tc_builtin, test_lkab_demo_suit);
        tcase_add_test(tc_builtin, test_wildcard_namespaces_in_uri_partition);
        tcase_add_test(tc_builtin, test_empty_choice_loads);
        tcase_add_test(tc_builtin, test_substitution_group_member_loads);
        tcase_add_test(tc_builtin, test_xsi_nil_value_is_boolean);
        tcase_add_test(tc_builtin, test_xsi_nil_type_empty_grammar);
        tcase_add_test(tc_builtin, test_xsi_nil_type_empty_grammar_decode);
        tcase_add_test(tc_builtin, test_nillable_element_grammars);
        tcase_add_test(tc_builtin, test_nillable_element_grammars_decode);
        tcase_add_test(tc_builtin, test_nillable_type_grammars_shared);
        tcase_add_test(tc_builtin, test_xsi_type_cast_no_escapes);
        tcase_add_test(tc_builtin, test_xsi_type_cast_no_escapes_decode);
        tcase_add_test(tc_builtin, test_xsi_attribute_prefixes_decode);
        tcase_add_test(tc_builtin, test_schemaless_xsi_nil_decode);
        tcase_add_test(tc_builtin, test_anytype_xsi_and_namespace_set);
        tcase_add_test(tc_builtin, test_anytype_xsi_and_namespace_set_decode);
        tcase_add_test(tc_builtin, test_uri_wildcards);
        tcase_add_test(tc_builtin, test_uri_wildcards_decode);
        tcase_add_test(tc_builtin, test_global_attribute_types);
        tcase_add_test(tc_builtin, test_global_attribute_types_decode);
        tcase_add_test(tc_builtin, test_value_type_reporting);
        tcase_add_test(tc_builtin, test_schema_order);
        tcase_add_test(tc_builtin, test_schema_order_decode);
        tcase_add_test(tc_builtin, test_duplicate_terminals);
        tcase_add_test(tc_builtin, test_duplicate_terminals_decode);
        tcase_add_test(tc_builtin, test_all_group);
        tcase_add_test(tc_builtin, test_all_group_decode);
        tcase_add_test(tc_builtin, test_utf8_strings);
        tcase_add_test(tc_builtin, test_utf8_strings_decode);
        tcase_add_test(tc_builtin, test_value_max_length_characters);
        tcase_add_test(tc_builtin, test_binary_value_types);
        tcase_add_test(tc_builtin, test_binary_value_types_decode);
        suite_add_tcase(s, tc_builtin);
    }

    return s;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERR: Expected test data directory\n");
        exit(1);
    }
    if (strlen(argv[1]) > MAX_PATH_LEN) {
        printf("ERR: Test data pathname too long: %u", (unsigned int) strlen(argv[1]));
        exit(1);
    }
    dataDir = argv[1];

    int number_failed;
    Suite *s = exip_suite();
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
#ifdef _MSC_VER
    srunner_set_fork_status(sr, CK_NOFORK);
#endif
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

