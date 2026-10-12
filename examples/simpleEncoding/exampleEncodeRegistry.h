/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#ifndef EXAMPLEENCODEREGISTRY_H_
#define EXAMPLEENCODEREGISTRY_H_

#include "encodeTestEXI.h"

typedef errorCode (*EncodeExampleFunction)(EXIPSchema* schemaPtr, FILE *outfile,
                                           size_t (*outputStream)(void* buf, size_t size, void* stream));

EncodeExampleFunction resolveEncodeExample(const char* name);
void printAvailableEncodeExamples(void);

#endif /* EXAMPLEENCODEREGISTRY_H_ */
