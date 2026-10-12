/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file exipe.c
 * @brief Command-line utility for testing the EXI encoder
 *
 * @date Nov 5, 2012
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: exipe.c 337 2014-08-02 09:32:36Z kjussakov $
 */

#include "encodeTestEXI.h"
#include "exampleEncodeRegistry.h"
#include "grammarGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_XSD_FILES_COUNT 10 // up to 10 XSD files

static void printfHelp(void);
size_t writeFileOutputStream(void* buf, size_t readSize, void* stream);
static void parseSchema(char* xsdList, EXIPSchema* schema);

int main(int argc, char *argv[])
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	EncodeExampleFunction encodeFunction = encode;
	FILE *outfile = stdout; // Default is the standard output
	char sourceFile[500];
	EXIPSchema schema;
	EXIPSchema* schemaPtr = NULL;
	unsigned int argIndex;

	strcpy(sourceFile, "stdout");

	for(argIndex = 1; argIndex < (unsigned int) argc; argIndex++)
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
		}
		else if(strstr(argv[argIndex], "-example") != NULL)
		{
			char* exampleName = argv[argIndex] + 9;
			encodeFunction = resolveEncodeExample(exampleName);
			if(encodeFunction == NULL)
			{
				fprintf(stderr, "Unknown encode example: %s\n", exampleName);
				printAvailableEncodeExamples();
				return 1;
			}
		}
		else
		{
			strcpy(sourceFile, argv[argIndex]);

			outfile = fopen(sourceFile, "wb" );
			if(!outfile)
			{
				fprintf(stderr, "Unable to open file %s", sourceFile);
				return 1;
			}
		}
	}

	tmp_err_code = encodeFunction(schemaPtr, outfile, writeFileOutputStream);

	if(schemaPtr != NULL)
		destroySchema(schemaPtr);

	if(tmp_err_code != EXIP_OK)
		printf("\nError (code: %d) during encoding of: %s\n", tmp_err_code, sourceFile);
	else
		printf("\nSuccessful encoding in %s\n", sourceFile);

	fclose(outfile);

	return tmp_err_code == EXIP_OK ? 0 : 1;
}

static void printfHelp(void)
{
    printf("\n" );
    printf("  EXIP     Copyright (c) 2010 - 2012, EISLAB - Luleå University of Technology Version 0.4 \n");
    printf("           Author: Rumen Kyusakov\n");
    printf("  Usage:   exipe [options] [exi_out]\n\n");
	printf("           Options: [-help | -schema=<xsd_in> | -example=<name>] \n");
    printf("           -schema :   uses schema defined in <xsd_in> for encoding. All referenced schema files should be included in <xsd_in>\n");
	printf("           -example:   selects which encode function to run (default: test)\n");
    printf("           <xsd_in>:   Comma-separated list of schema documents encoded in EXI with Preserve.prefixes. The first schema is the\n");
    printf("                       main one and the rest are schemas that are referenced from the main one through the <xs:import> statement.\n");
    printf("           -help   :   Prints this help message\n\n");
	printAvailableEncodeExamples();
	printf("\n");
    printf("           exi_out :   output file for the EXI stream (stdout if none specified)\n\n");
    printf("  Purpose: This program tests the EXIP encoding functionality\n");
    printf("\n" );
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
	BinaryBuffer buffer[MAX_XSD_FILES_COUNT]; // up to 10 XSD files
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
				fprintf(stderr, "Memory allocation error!");
				fclose(schemaFile);
				exit(1);
			}

			//Read file contents into buffer
			// bufLen is the file size plus one spare byte (zeroed; bufContent includes it, as before)
			if(fread(buffer[i].buf, 1, buffer[i].bufLen - 1, schemaFile) != (size_t) (buffer[i].bufLen - 1))
			{
				fprintf(stderr, "Unable to read schema file %s\n", schemaFileName);
				fclose(schemaFile);
				exit(1);
			}
			buffer[i].buf[buffer[i].bufLen - 1] = 0;
			fclose(schemaFile);

			buffer[i].bufContent = buffer[i].bufLen;
			buffer[i].ioStrm.readWriteToStream = NULL;
			buffer[i].ioStrm.stream = NULL;
		}
	}

	// Generate the EXI grammars based on the schema information
	tmp_err_code = generateSchemaInformedGrammars(buffer, schemaFilesCount, SCHEMA_FORMAT_XSD_EXI, NULL, schema, NULL);

	for(i = 0; i < schemaFilesCount; i++)
	{
		free(buffer[i].buf);
	}

	if(tmp_err_code != EXIP_OK)
	{
		printf("\nGrammar generation error occurred: %d", tmp_err_code);
		exit(1);
	}
}
