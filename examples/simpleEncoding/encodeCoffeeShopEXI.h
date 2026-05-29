/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#ifndef ENCODE_COFFEE_SHOP_EXI_H_
#define ENCODE_COFFEE_SHOP_EXI_H_

#include "procTypes.h"
#include <stdio.h>

errorCode encodeCoffeeShop(EXIPSchema* schemaPtr, FILE *outfile, size_t (*outputStream)(void* buf, size_t size, void* stream));

#endif /* ENCODE_COFFEE_SHOP_EXI_H_ */
