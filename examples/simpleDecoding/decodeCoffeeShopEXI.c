/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#include "decodeCoffeeShopEXI.h"

errorCode decodeCoffeeShop(EXIPSchema* schemaPtr, unsigned char outFlag, FILE *infile,
		exip_bool outOfBandOpts, EXIOptions* opts,
		size_t (*inputStream)(void* buf, size_t size, void* stream))
{
	return decode(schemaPtr, outFlag, infile, outOfBandOpts, opts, inputStream);
}
