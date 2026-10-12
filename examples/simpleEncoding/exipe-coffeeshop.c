/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#include "encodeCoffeeShopEXI.h"
#include "grammarGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_XSD_FILES_COUNT 10

static void printfHelp(void);
static void parseSchema(char* xsdList, EXIPSchema* schema);
size_t writeFileOutputStream(void* buf, size_t readSize, void* stream);

int main(int argc, char *argv[])
{
    errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
    FILE *outfile = stdout;
    char sourceFile[500];
    EXIPSchema schema;
    EXIPSchema* schemaPtr = NULL;
    int argIndex = 1;

    strcpy(sourceFile, "stdout");

    if(argc >= 2)
    {
        if(strcmp(argv[argIndex], "-help") == 0)
        {
            printfHelp();
            return 0;
        }
        else if(strstr(argv[argIndex], "-schema") != NULL)
        {
            char* xsdList = argv[argIndex] + 7;
            parseSchema(xsdList, &schema);
            schemaPtr = &schema;
            argIndex++;
        }
    }

    if(argIndex < argc)
    {
        strcpy(sourceFile, argv[argIndex]);
        outfile = fopen(sourceFile, "wb" );
        if(!outfile)
        {
            fprintf(stderr, "Unable to open file %s", sourceFile);
            return 1;
        }
    }

    tmp_err_code = encodeCoffeeShop(schemaPtr, outfile, writeFileOutputStream);

    if(schemaPtr != NULL)
        destroySchema(schemaPtr);

    if(tmp_err_code != EXIP_OK)
        printf("\nError (code: %d) during CoffeeShop encoding: %s\n", tmp_err_code, sourceFile);
    else
        printf("\nSuccessful CoffeeShop encoding in %s\n", sourceFile);

    fclose(outfile);

    return 0;
}

static void printfHelp(void)
{
    printf("\n");
    printf("Usage: exipe-coffeeshop [options] [exi_out]\n\n");
    printf("Options: [-help | -schema=<xsd_in>]\n");
    printf("-schema : Comma-separated list of EXI-encoded schema files\n");
    printf("-help   : Prints this help message\n\n");
    printf("exi_out : output EXI file (stdout if none specified)\n\n");
}

size_t writeFileOutputStream(void* buf, size_t readSize, void* stream)
{
    FILE *outfile = (FILE*) stream;
    return fwrite(buf, 1, readSize, outfile);
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
