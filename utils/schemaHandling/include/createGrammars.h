/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file createGrammars.h
 * @brief Interface to functions to Generate EXI grammars from XML schema definition
 *
 * @date Oct 13, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: createGrammars.h 352 2014-11-25 16:37:24Z kjussakov $
 */
#ifndef CREATEGRAMMARS_H_
#define CREATEGRAMMARS_H_

#include "procTypes.h"

typedef struct
{
	unsigned int url;
	unsigned int ln;
	unsigned int grammar;
	unsigned int pfx;
} Deviations;

errorCode toText(EXIPSchema* schemaPtr, FILE *outfile);

errorCode toStaticSrc(EXIPSchema* schemaPtr, char* prefix, FILE *outfile, Deviations dvis);

errorCode toDynSrc(EXIPSchema* schemaPtr, FILE *outfile);

errorCode toEXIP(EXIPSchema* schemaPtr, FILE *outfile);

#endif /* CREATEGRAMMARS_H_ */
