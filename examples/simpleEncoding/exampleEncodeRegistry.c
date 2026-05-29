/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#include "exampleEncodeRegistry.h"
#include "encodeCoffeeShopEXI.h"
#include <stdio.h>
#include <string.h>

typedef struct EncodeExampleEntry
{
	const char* name;
	EncodeExampleFunction function;
} EncodeExampleEntry;

static const EncodeExampleEntry ENCODE_EXAMPLES[] = {
	{"test", encode},
	{"coffeeshop", encodeCoffeeShop},
	/* GENERATED ENCODE ENTRIES */
};

EncodeExampleFunction resolveEncodeExample(const char* name)
{
	unsigned int i;

	for(i = 0; i < sizeof(ENCODE_EXAMPLES)/sizeof(ENCODE_EXAMPLES[0]); i++)
	{
		if(strcmp(ENCODE_EXAMPLES[i].name, name) == 0)
			return ENCODE_EXAMPLES[i].function;
	}

	return NULL;
}

void printAvailableEncodeExamples(void)
{
	unsigned int i;
	printf("Available encode examples:\n");
	for(i = 0; i < sizeof(ENCODE_EXAMPLES)/sizeof(ENCODE_EXAMPLES[0]); i++)
		printf("  %s\n", ENCODE_EXAMPLES[i].name);
}