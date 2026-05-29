/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#include "exampleDecodeRegistry.h"
#include "decodeCoffeeShopEXI.h"
#include <stdio.h>
#include <string.h>

typedef struct DecodeExampleEntry
{
	const char* name;
	DecodeExampleFunction function;
} DecodeExampleEntry;

static const DecodeExampleEntry DECODE_EXAMPLES[] = {
	{"test", decode},
	{"coffeeshop", decodeCoffeeShop},
	/* GENERATED DECODE ENTRIES */
};

DecodeExampleFunction resolveDecodeExample(const char* name)
{
	unsigned int i;

	for(i = 0; i < sizeof(DECODE_EXAMPLES)/sizeof(DECODE_EXAMPLES[0]); i++)
	{
		if(strcmp(DECODE_EXAMPLES[i].name, name) == 0)
			return DECODE_EXAMPLES[i].function;
	}

	return NULL;
}

void printAvailableDecodeExamples(void)
{
	unsigned int i;
	printf("Available decode examples:\n");
	for(i = 0; i < sizeof(DECODE_EXAMPLES)/sizeof(DECODE_EXAMPLES[0]); i++)
		printf("  %s\n", DECODE_EXAMPLES[i].name);
}