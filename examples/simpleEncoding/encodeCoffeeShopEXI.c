/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#include "encodeCoffeeShopEXI.h"
#include "EXISerializer.h"
#include "stringManipulate.h"

#define OUTPUT_BUFFER_SIZE 256
#define TRY_CATCH_ENCODE(func) TRY_CATCH(func, serialize.closeEXIStream(&testStrm))

static const String NS_COFFEE_SHOP_STR = {"http://example.com/coffeeshop", 29};
static const String NS_EMPTY_STR = {NULL, 0};

static const String ELEM_COFFEE_SHOP_STR = {"CoffeeShop", 10};
static const String ELEM_SHOP_NAME_STR = {"shopName", 8};
static const String ELEM_IS_OPEN_STR = {"isOpen", 6};
static const String ELEM_MENU_ITEM_STR = {"menuItem", 8};
static const String ELEM_NAME_STR = {"name", 4};
static const String ELEM_PRICE_CENTS_STR = {"priceCents", 10};
static const String ELEM_SEASONAL_STR = {"seasonal", 8};

errorCode encodeCoffeeShop(EXIPSchema* schemaPtr, FILE *outfile, size_t (*outputStream)(void* buf, size_t size, void* stream))
{
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    EXIStream testStrm;
    String uri;
    String ln;
    QName qname = {&uri, &ln, NULL};
    String chVal;
    char buf[OUTPUT_BUFFER_SIZE];
    BinaryBuffer buffer;
    EXITypeClass valueType;

    buffer.buf = buf;
    buffer.bufLen = OUTPUT_BUFFER_SIZE;
    buffer.bufContent = 0;

    serialize.initHeader(&testStrm);

    testStrm.header.has_cookie = TRUE;
    testStrm.header.has_options = TRUE;
    testStrm.header.opts.valueMaxLength = 300;
    testStrm.header.opts.valuePartitionCapacity = 50;
    SET_STRICT(testStrm.header.opts.enumOpt);

    buffer.ioStrm.readWriteToStream = outputStream;
    buffer.ioStrm.stream = outfile;

    TRY_CATCH_ENCODE(serialize.initStream(&testStrm, buffer, schemaPtr));
    TRY_CATCH_ENCODE(serialize.exiHeader(&testStrm));
    TRY_CATCH_ENCODE(serialize.startDocument(&testStrm));

    qname.uri = &NS_COFFEE_SHOP_STR;
    qname.localName = &ELEM_COFFEE_SHOP_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));

    qname.localName = &ELEM_SHOP_NAME_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    TRY_CATCH_ENCODE(asciiToString("Binary Bean", &chVal, &testStrm.memList, FALSE));
    TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.localName = &ELEM_IS_OPEN_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    if(schemaPtr != NULL)
        TRY_CATCH_ENCODE(serialize.booleanData(&testStrm, TRUE));
    else
    {
        TRY_CATCH_ENCODE(asciiToString("true", &chVal, &testStrm.memList, FALSE));
        TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    }
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.localName = &ELEM_MENU_ITEM_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));

    qname.localName = &ELEM_NAME_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    TRY_CATCH_ENCODE(asciiToString("Espresso", &chVal, &testStrm.memList, FALSE));
    TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.localName = &ELEM_PRICE_CENTS_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    if(schemaPtr != NULL)
        TRY_CATCH_ENCODE(serialize.intData(&testStrm, 325));
    else
    {
        TRY_CATCH_ENCODE(asciiToString("325", &chVal, &testStrm.memList, FALSE));
        TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    }
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.localName = &ELEM_SEASONAL_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    if(schemaPtr != NULL)
        TRY_CATCH_ENCODE(serialize.booleanData(&testStrm, FALSE));
    else
    {
        TRY_CATCH_ENCODE(asciiToString("false", &chVal, &testStrm.memList, FALSE));
        TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    }
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.uri = &NS_COFFEE_SHOP_STR;
    qname.localName = &ELEM_MENU_ITEM_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));

    qname.localName = &ELEM_NAME_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    TRY_CATCH_ENCODE(asciiToString("Latte", &chVal, &testStrm.memList, FALSE));
    TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.localName = &ELEM_PRICE_CENTS_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    if(schemaPtr != NULL)
        TRY_CATCH_ENCODE(serialize.intData(&testStrm, 475));
    else
    {
        TRY_CATCH_ENCODE(asciiToString("475", &chVal, &testStrm.memList, FALSE));
        TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    }
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.localName = &ELEM_SEASONAL_STR;
    TRY_CATCH_ENCODE(serialize.startElement(&testStrm, qname, &valueType));
    if(schemaPtr != NULL)
        TRY_CATCH_ENCODE(serialize.booleanData(&testStrm, TRUE));
    else
    {
        TRY_CATCH_ENCODE(asciiToString("true", &chVal, &testStrm.memList, FALSE));
        TRY_CATCH_ENCODE(serialize.stringData(&testStrm, chVal));
    }
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));

    qname.uri = &NS_EMPTY_STR;
    qname.localName = &ELEM_COFFEE_SHOP_STR;
    TRY_CATCH_ENCODE(serialize.endElement(&testStrm));
    TRY_CATCH_ENCODE(serialize.endDocument(&testStrm));
    TRY_CATCH_ENCODE(serialize.closeEXIStream(&testStrm));

    return tmp_err_code;
}
