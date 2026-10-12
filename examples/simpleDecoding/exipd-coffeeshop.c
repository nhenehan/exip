/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#include "decodeTestEXI.h"
#include "grammarGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_XSD_FILES_COUNT 10

static void printfHelp(void);
static void parseSchema(char* xsdList, EXIPSchema* schema);
static void parseOpsMask(char* mask, EXIOptions* ops);
size_t readFileInputStream(void* buf, size_t readSize, void* stream);

int main(int argc, char *argv[])
{
    FILE *infile = stdin;
    char sourceFileName[500];
    EXIPSchema schema;
    EXIPSchema* schemaPtr = NULL;
    EXIOptions ops;
    EXIOptions* opsPtr = NULL;
    exip_bool outOfBandOpts = FALSE;
    unsigned char outFlag = OUT_EXI;
    unsigned int argIndex = 1;
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;

    strcpy(sourceFileName, "stdin");
    makeDefaultOpts(&ops);

    if(argc > 1)
    {
        if(strcmp(argv[argIndex], "-help") == 0)
        {
            printfHelp();
            return 0;
        }
        else if(strcmp(argv[argIndex], "-exi") == 0)
        {
            outFlag = OUT_EXI;
            if(argc == 2)
            {
                printfHelp();
                return 0;
            }
            argIndex += 1;
        }
        else if(strcmp(argv[argIndex], "-xml") == 0)
        {
            outFlag = OUT_XML;
            if(argc == 2)
            {
                printfHelp();
                return 0;
            }
            argIndex += 1;
        }

        if(strstr(argv[argIndex], "-ops") != NULL)
        {
            char *mask = argv[argIndex] + 4;
            outOfBandOpts = TRUE;
            parseOpsMask(mask, &ops);
            opsPtr = &ops;
            argIndex += 1;
        }

        if(strstr(argv[argIndex], "-schema") != NULL)
        {
            char *xsdList = argv[argIndex] + 7;
            parseSchema(xsdList, &schema);
            schemaPtr = &schema;
            argIndex += 1;
        }
    }

    if(argIndex < argc)
    {
        strcpy(sourceFileName, argv[argIndex]);
        infile = fopen(sourceFileName, "rb" );
        if(!infile)
        {
            fprintf(stderr, "Unable to open file %s\n", sourceFileName);
            exit(1);
        }
    }

    tmp_err_code = decode(schemaPtr, outFlag, infile, outOfBandOpts, opsPtr, readFileInputStream);

    if(schemaPtr != NULL)
        destroySchema(schemaPtr);
    fclose(infile);

    if(tmp_err_code != EXIP_OK)
    {
        printf("\nError (code: %d) during CoffeeShop parsing of EXI stream: %s\n", tmp_err_code, sourceFileName);
        return 1;
    }

    printf("\nSuccessful CoffeeShop parsing of EXI stream: %s\n", sourceFileName);
    return 0;
}

static void printfHelp(void)
{
    printf("\n");
    printf("Usage: exipd-coffeeshop [options] [exi_in]\n\n");
    printf("Options: [-help | [ -xml | -exi ] [-ops=<ops_mask>] -schema=<xsd_in>]\n");
    printf("-schema : Comma-separated list of EXI-encoded schema files\n");
    printf("-ops    : Out-of-band EXI options mask (same format as exipd)\n");
    printf("-exi    : EXI-like event output [default]\n");
    printf("-xml    : XML formatted output\n");
    printf("-help   : Prints this help message\n\n");
}

size_t readFileInputStream(void* buf, size_t readSize, void* stream)
{
    FILE *infile = (FILE*) stream;
    return fread(buf, 1, readSize, infile);
}

static void parseSchema(char* xsdList, EXIPSchema* schema)
{
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    FILE *schemaFile;
    BinaryBuffer buffer[MAX_XSD_FILES_COUNT];
    char schemaFileName[500];
    unsigned int schemaFilesCount = 0;
    unsigned int i;
    char *token;

    for (token = strtok(xsdList, "=,"), i = 0; token != NULL; token = strtok(NULL, "=,"), i++)
    {
        schemaFilesCount++;
        if(schemaFilesCount > MAX_XSD_FILES_COUNT)
        {
            fprintf(stderr, "Too many xsd files given as an input: %d", schemaFilesCount);
            exit(1);
        }

        strcpy(schemaFileName, token);
        schemaFile = fopen(schemaFileName, "rb" );
        if(!schemaFile)
        {
            fprintf(stderr, "Unable to open file %s", schemaFileName);
            exit(1);
        }

        fseek(schemaFile, 0, SEEK_END);
        buffer[i].bufLen = ftell(schemaFile) + 1;
        fseek(schemaFile, 0, SEEK_SET);

        buffer[i].buf = (char *) malloc(buffer[i].bufLen);
        if (!buffer[i].buf)
        {
            fprintf(stderr, "Memory allocation error!");
            fclose(schemaFile);
            exit(1);
        }

        fread(buffer[i].buf, buffer[i].bufLen, 1, schemaFile);
        fclose(schemaFile);

        buffer[i].bufContent = buffer[i].bufLen;
        buffer[i].ioStrm.readWriteToStream = NULL;
        buffer[i].ioStrm.stream = NULL;
    }

    tmp_err_code = generateSchemaInformedGrammars(buffer, schemaFilesCount, SCHEMA_FORMAT_XSD_EXI, NULL, schema, NULL);

    for(i = 0; i < schemaFilesCount; i++)
        free(buffer[i].buf);

    if(tmp_err_code != EXIP_OK)
    {
        printf("\nGrammar generation error occurred: %d", tmp_err_code);
        exit(1);
    }
}

static void parseOpsMask(char* mask, EXIOptions* ops)
{
    unsigned int i;
    char *token;

    for (token = strtok(mask, "=%"), i = 0; token != NULL; token = strtok(NULL, "=%"), i++)
    {
        switch(i)
        {
            case 0:
            if(strcmp(token, "-"))
            {
                if(strstr(token, "c") != NULL)
                    SET_PRESERVED(ops->preserve, PRESERVE_COMMENTS);
                if(strstr(token, "d") != NULL)
                    SET_PRESERVED(ops->preserve, PRESERVE_DTD);
                if(strstr(token, "l") != NULL)
                    SET_PRESERVED(ops->preserve, PRESERVE_LEXVALUES);
                if(strstr(token, "p") != NULL)
                    SET_PRESERVED(ops->preserve, PRESERVE_PIS);
                if(strstr(token, "x") != NULL)
                    SET_PRESERVED(ops->preserve, PRESERVE_PREFIXES);
            }
            break;
            case 1:
            if(strcmp(token, "-"))
            {
                if(strstr(token, "v") != NULL)
                    SET_STRICT(ops->enumOpt);
                if(strstr(token, "f") != NULL)
                    SET_FRAGMENT(ops->enumOpt);
                if(strstr(token, "r") != NULL)
                    SET_SELF_CONTAINED(ops->enumOpt);
                if(strstr(token, "c") != NULL)
                    SET_COMPRESSION(ops->enumOpt);
                if(strstr(token, "p") != NULL)
                    SET_ALIGNMENT(ops->enumOpt, PRE_COMPRESSION);
                else if(strstr(token, "a") != NULL)
                    SET_ALIGNMENT(ops->enumOpt, BYTE_ALIGNMENT);
            }
            break;
            case 2:
            if(strcmp(token, "-"))
                ops->valuePartitionCapacity = (Index) strtol(token, NULL, 10);
            break;
            case 3:
            if(strcmp(token, "-"))
                ops->valueMaxLength = (Index) strtol(token, NULL, 10);
            break;
            case 4:
            if(strcmp(token, "-"))
                ops->blockSize = (uint32_t) strtol(token, NULL, 10);
            break;
            default:
            {
                fprintf(stderr, "Wrong options mask: %s", mask);
                exit(1);
            }
        }
    }
}
