/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#ifndef C5DE0A77_A311_4F20_8F96_C22831F3C522
#define C5DE0A77_A311_4F20_8F96_C22831F3C522

#ifndef DECODECOFFEESHOP_EXI_H_
#define DECODECOFFEESHOP_EXI_H_

#include "decodeTestEXI.h"

errorCode decodeCoffeeShop(EXIPSchema* schemaPtr, unsigned char outFlag, FILE *infile,
		boolean outOfBandOpts, EXIOptions* opts,
		size_t (*inputStream)(void* buf, size_t size, void* stream));

#endif /* DECODECOFFEESHOP_EXI_H_ */


#endif /* C5DE0A77_A311_4F20_8F96_C22831F3C522 */
