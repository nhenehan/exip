/*
 * ExipRoundTrip: encodes a small schema-less EXI document into a RAM buffer, decodes it
 * again and prints the decoded events and the sizes to Serial.
 *
 *   <sensor id="t1"><value>21.5</value><unit>Cel</unit></sensor>
 *
 * The exip API is in namespace exip in C++ (exip::String would otherwise clash with
 * Arduino's String). Builds with the PlatformIO library (library.json) or the Arduino
 * library bundle (cmake --build <build> --target arduino_bundle).
 */
#include <Arduino.h>
#include <stdarg.h>
#include <exip.h>

#define CHECK(call) do { err = (call); if (err != exip::EXIP_OK) return err; } while (0)

static char exiBuffer[128];

static exip::errorCode text(const char* ascii, exip::String* out)
{
    return exip::asciiToString(ascii, out, NULL, exip::EXIP_FALSE);
}

static exip::errorCode encodeDocument(unsigned int* exiSize)
{
    exip::errorCode err = exip::EXIP_OK;
    exip::EXIStream strm;
    exip::BinaryBuffer buffer;
    exip::String noUri, sensor, id, value, unit, chars;
    exip::QName qname = {&noUri, NULL, NULL};
    exip::EXITypeClass valueType;

    buffer.buf = exiBuffer;
    buffer.bufLen = sizeof exiBuffer;
    buffer.bufContent = 0;
    buffer.ioStrm.readWriteToStream = NULL; // everything stays in exiBuffer
    buffer.ioStrm.stream = NULL;

    CHECK(text("", &noUri));
    CHECK(text("sensor", &sensor));
    CHECK(text("id", &id));
    CHECK(text("value", &value));
    CHECK(text("unit", &unit));

    exip::serialize.initHeader(&strm);
    CHECK(exip::serialize.initStream(&strm, buffer, NULL)); // no schema
    CHECK(exip::serialize.exiHeader(&strm));
    CHECK(exip::serialize.startDocument(&strm));

    qname.localName = &sensor;
    CHECK(exip::serialize.startElement(&strm, qname, &valueType));
    qname.localName = &id;
    CHECK(exip::serialize.attribute(&strm, qname, exip::EXIP_TRUE, &valueType));
    CHECK(text("t1", &chars));
    CHECK(exip::serialize.stringData(&strm, chars));

    qname.localName = &value;
    CHECK(exip::serialize.startElement(&strm, qname, &valueType));
    CHECK(text("21.5", &chars));
    CHECK(exip::serialize.stringData(&strm, chars));
    CHECK(exip::serialize.endElement(&strm));

    qname.localName = &unit;
    CHECK(exip::serialize.startElement(&strm, qname, &valueType));
    CHECK(text("Cel", &chars));
    CHECK(exip::serialize.stringData(&strm, chars));
    CHECK(exip::serialize.endElement(&strm));

    CHECK(exip::serialize.endElement(&strm));
    CHECK(exip::serialize.endDocument(&strm));

    *exiSize = strm.context.bufferIndx + (strm.context.bitPointer != 0 ? 1 : 0);
    return exip::serialize.closeEXIStream(&strm);
}

static void printString(const exip::String* s)
{
    Serial.write((const uint8_t*) s->str, s->length);
}

static exip::errorCode onStartElement(exip::QName qname, void* appData)
{
    (void) appData;
    Serial.print("SE ");
    printString(qname.localName);
    Serial.println();
    return exip::EXIP_OK;
}

static exip::errorCode onAttribute(exip::QName qname, void* appData)
{
    (void) appData;
    Serial.print("AT ");
    printString(qname.localName);
    Serial.println();
    return exip::EXIP_OK;
}

static exip::errorCode onStringData(const exip::String value, void* appData)
{
    (void) appData;
    Serial.print("CH \"");
    printString(&value);
    Serial.println("\"");
    return exip::EXIP_OK;
}

static exip::errorCode onEndElement(void* appData)
{
    (void) appData;
    Serial.println("EE");
    return exip::EXIP_OK;
}

static exip::errorCode onError(const exip::errorCode code, const char* msg, void* appData)
{
    (void) appData;
    Serial.print("error ");
    Serial.print((int) code);
    Serial.print(": ");
    Serial.println(msg);
    return exip::EXIP_HANDLER_STOP;
}

static exip::errorCode decodeDocument(unsigned int exiSize)
{
    exip::errorCode err = exip::EXIP_OK;
    exip::Parser parser;
    exip::BinaryBuffer buffer;

    buffer.buf = exiBuffer;
    buffer.bufLen = sizeof exiBuffer;
    buffer.bufContent = exiSize;
    buffer.ioStrm.readWriteToStream = NULL;
    buffer.ioStrm.stream = NULL;

    CHECK(exip::parse.initParser(&parser, buffer, NULL));
    parser.handler.startElement = onStartElement;
    parser.handler.attribute = onAttribute;
    parser.handler.stringData = onStringData;
    parser.handler.endElement = onEndElement;
    parser.handler.error = onError;
    parser.handler.fatalError = onError;

    // The stream has no options document: both sides use the default options, given
    // to the decoder "out of band"
    exip::makeDefaultOpts(&parser.strm.header.opts);
    err = exip::parse.parseHeader(&parser, exip::EXIP_TRUE);
    if (err == exip::EXIP_OK)
        err = exip::parse.setSchema(&parser, NULL);
    while (err == exip::EXIP_OK)
        err = exip::parse.parseNext(&parser);
    exip::parse.destroyParser(&parser);

    return err == exip::EXIP_PARSING_COMPLETE ? exip::EXIP_OK : err;
}

#if EXIP_DEBUG == ON
/* exip's debug output (EXIP_DEBUG=ON), see exip_arduino_config.h */
extern "C" int exip_debug_printf(const char* format, ...)
{
    char line[128];
    va_list args;
    va_start(args, format);
    int n = vsnprintf(line, sizeof line, format, args);
    va_end(args);
    Serial.print(line);
    return n;
}
#endif

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    unsigned int exiSize = 0;
    exip::errorCode err = encodeDocument(&exiSize);
    if (err != exip::EXIP_OK)
    {
        Serial.print("encoding failed: ");
        Serial.println((int) err);
        return;
    }
    Serial.print("EXI: ");
    Serial.print(exiSize);
    Serial.println(" bytes (the XML text is 60 bytes)");

    err = decodeDocument(exiSize);
    if (err != exip::EXIP_OK)
    {
        Serial.print("decoding failed: ");
        Serial.println((int) err);
        return;
    }
    Serial.println("round trip OK");
}

void loop()
{
}
