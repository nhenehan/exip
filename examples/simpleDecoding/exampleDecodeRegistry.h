/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

#ifndef EB66F18B_53ED_4CD5_B972_788336975951
#define EB66F18B_53ED_4CD5_B972_788336975951

#ifndef EXAMPLEDECODEREGISTRY_H_
#define EXAMPLEDECODEREGISTRY_H_

#include "decodeTestEXI.h"

typedef errorCode (*DecodeExampleFunction)(EXIPSchema* schemaPtr, unsigned char outFlag,
		FILE *infile, boolean outOfBandOpts, EXIOptions* opts,
		size_t (*inputStream)(void* buf, size_t size, void* stream));

DecodeExampleFunction resolveDecodeExample(const char* name);
void printAvailableDecodeExamples(void);

#endif /* EXAMPLEDECODEREGISTRY_H_ */


#endif /* EB66F18B_53ED_4CD5_B972_788336975951 */
