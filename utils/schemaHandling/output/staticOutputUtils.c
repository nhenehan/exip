/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file staticOutputUtils.c
 * @brief Implement utility functions for storing EXIPSchema instances as static code
 * @date May 7, 2012
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: staticOutputUtils.c 352 2014-11-25 16:37:24Z kjussakov $
 */

#include "schemaOutputUtils.h"
#include "hashtable.h"
#include "sTables.h"
#include <stdio.h>

static void setProdStrings(IndexStrings *indexStrings, Production *prod)
{
	char *indexMaxStr = "INDEX_MAX";
	char *uriMaxStr = "URI_MAX";
	char *lnMaxStr = "LN_MAX";

	if (prod->typeId == INDEX_MAX)
	{
		strcpy(indexStrings->typeIdStr, indexMaxStr);
	}
	else
	{
		sprintf(indexStrings->typeIdStr, "%u", (unsigned int) prod->typeId);
	}
	if (prod->qnameId.uriId == URI_MAX)
	{
		strcpy(indexStrings->uriIdStr, uriMaxStr);
	}
	else
	{
		sprintf(indexStrings->uriIdStr, "%u", (unsigned int) prod->qnameId.uriId);
	}
	if (prod->qnameId.lnId == LN_MAX)
	{
		strcpy(indexStrings->lnIdStr, lnMaxStr);
	}
	else
	{
		sprintf(indexStrings->lnIdStr, "%u", (unsigned int) prod->qnameId.lnId);
	}
}

void staticStringDefOutput(String* str, char* varName, FILE* out)
{
	Index charIter, charMax, displayLen;
	char displayStr[VAR_BUFFER_MAX_LENGTH];

	charMax = str->length;
	if(charMax > 0)
	{
		fprintf(out, "CONST CharType %s[] = {", varName);
		for(charIter = 0; charIter < charMax; charIter++)
		{
			unsigned char byte = (unsigned char) str->str[charIter];

			// Strings are UTF-8. A byte from 0x80 up is written as a character
			// literal, which fits CharType whether char is signed or not; "0x%x" of a
			// signed char printed 0xffffffc5 (D31). ASCII keeps the old form.
			if(byte < 0x80)
				fprintf(out, "0x%x", byte);
			else
				fprintf(out, "'\\x%02x'", byte);
			if(charIter < charMax - 1)
				fprintf(out, ", ");
		}

		// The comment shows the string: bounded to the buffer (the copy used to be
		// unbounded, D31), cut at a UTF-8 character boundary, with control characters
		// and the end of a comment ("*/") made harmless
		displayLen = 0;
		for(charIter = 0; charIter < charMax && displayLen < VAR_BUFFER_MAX_LENGTH - 4; charIter++)
		{
			unsigned char byte = (unsigned char) str->str[charIter];

			if(byte < 0x20 || byte == 0x7f)
				byte = '?';
			else if(byte == '/' && displayLen > 0 && displayStr[displayLen - 1] == '*')
				byte = '?';
			displayStr[displayLen++] = (char) byte;
		}
		if(charIter < charMax)
		{
			// Truncated: drop a partial UTF-8 sequence at the end, then mark the cut
			while(displayLen > 0 && (((unsigned char) displayStr[displayLen - 1]) & 0xC0) == 0x80)
				displayLen--;
			if(displayLen > 0 && ((unsigned char) displayStr[displayLen - 1]) >= 0xC0)
				displayLen--;
			displayStr[displayLen++] = '.';
			displayStr[displayLen++] = '.';
			displayStr[displayLen++] = '.';
		}
		displayStr[displayLen] = '\0';
		fprintf(out, "}; /* %s */\n", displayStr);
	}
}

void staticStringTblDefsOutput(UriTable* uriTbl, char* prefix, FILE* out)
{
	Index uriIter, pfxIter, lnIter;
	char varName[VAR_BUFFER_MAX_LENGTH];

	fprintf(out, "/** START_STRINGS_DEFINITONS */\n\n");

	for(uriIter = 0; uriIter < uriTbl->count; uriIter++)
	{
		// Printing of a uri string
		sprintf(varName, "%sURI_%u", prefix, (unsigned int) uriIter);
		staticStringDefOutput(&uriTbl->uri[uriIter].uriStr, varName, out);

		// Printing of a pfx strings if any
		for(pfxIter = 0; pfxIter < uriTbl->uri[uriIter].pfxTable.count; pfxIter++)
		{
			sprintf(varName, "%sPFX_%u_%u", prefix, (unsigned int) uriIter, (unsigned int) pfxIter);
			staticStringDefOutput(&uriTbl->uri[uriIter].pfxTable.pfx[pfxIter], varName, out);
		}

		// Printing of all local names for that uri
		for(lnIter = 0; lnIter < uriTbl->uri[uriIter].lnTable.count; lnIter++)
		{
			sprintf(varName, "%sLN_%u_%u", prefix, (unsigned int) uriIter, (unsigned int) lnIter);
			staticStringDefOutput(&uriTbl->uri[uriIter].lnTable.ln[lnIter].lnStr, varName, out);
		}
	}

	fprintf(out, "\n/** END_STRINGS_DEFINITONS */\n\n");
}

void staticProductionsOutput(EXIGrammar* gr, char* prefix, Index grId, FILE* out)
{
	Index ruleIter;
	char varName[VAR_BUFFER_MAX_LENGTH];
	Index prodIter;
	IndexStrings indexStrings;

	for(ruleIter = 0; ruleIter < gr->count; ruleIter++)
	{
		if (gr->rule[ruleIter].pCount)
		{
			// Printing of the Production variable string
			sprintf(varName, "%sprod_%u_%u", prefix, (unsigned int) grId, (unsigned int) ruleIter);

			fprintf(out, "static CONST Production %s[%u] =\n{\n", varName, (unsigned int) gr->rule[ruleIter].pCount);

			for(prodIter = 0; prodIter < gr->rule[ruleIter].pCount; prodIter++)
			{
				setProdStrings(&indexStrings, &gr->rule[ruleIter].production[prodIter]);
				fprintf(out,
						"    {\n        %u, %s,\n        {%s, %s}}%s",
						gr->rule[ruleIter].production[prodIter].content,
						indexStrings.typeIdStr,
						indexStrings.uriIdStr,
						indexStrings.lnIdStr,
						prodIter==(gr->rule[ruleIter].pCount - 1) ? "\n};\n\n" : ",\n");
			}
		}
	}
}

void staticRulesOutput(EXIGrammar* gr, char* prefix, Index grId, FILE* out)
{
	Index ruleIter;

	fprintf(out,
		    "static CONST GrammarRule %srule_%u[%u] =\n{",
			prefix,
			(unsigned int) grId,
			(unsigned int) gr->count);

	for(ruleIter = 0; ruleIter < gr->count; ruleIter++)
	{
		fprintf(out, "\n    {");
		if (gr->rule[ruleIter].pCount > 0)
		{
			fprintf(out,
			        "%sprod_%u_%u, ",
					prefix,
					(unsigned int) grId,
					(unsigned int) ruleIter);
		}
		else
			fprintf(out, "NULL, ");

		fprintf(out, "%u, ", (unsigned int) gr->rule[ruleIter].pCount);
		fprintf(out, "%u", (unsigned int) gr->rule[ruleIter].meta);
		fprintf(out, "}%s", ruleIter != (gr->count-1)?",":"");

	}

	fprintf(out, "\n};\n\n");
}

void staticDocGrammarOutput(EXIGrammar* docGr, char* prefix, FILE* out)
{
	char varNameContent[VAR_BUFFER_MAX_LENGTH];
	char varNameEnd[VAR_BUFFER_MAX_LENGTH];
	Index prodIter;
	IndexStrings indexStrings;

	// Printing of the Production variable string
	sprintf(varNameContent, "%sprod_doc_content", prefix);

	/* Build the document grammar, DocContent productions */

	fprintf(out, "static CONST Production %s[%u] =\n{\n", varNameContent, (unsigned int) docGr->rule[GR_DOC_CONTENT].pCount);

	for(prodIter = 0; prodIter < docGr->rule[GR_DOC_CONTENT].pCount; prodIter++)
	{
		setProdStrings(&indexStrings, &docGr->rule[GR_DOC_CONTENT].production[prodIter]);
		fprintf(out,
				"    {\n        %u, %s,\n        {%s, %s}}%s",
				(unsigned int) docGr->rule[GR_DOC_CONTENT].production[prodIter].content,
				indexStrings.typeIdStr,
				indexStrings.uriIdStr,
				indexStrings.lnIdStr,
				prodIter==(docGr->rule[GR_DOC_CONTENT].pCount - 1) ? "\n};\n\n" : ",\n");
	}

	// Printing of the Production variable string
	sprintf(varNameEnd, "%sprod_doc_end", prefix);

	/* Build the document grammar, DocEnd productions */

	fprintf(out, "static CONST Production %s[%u] =\n{\n", varNameEnd, 1);
	fprintf(out,"    {\n        0xAFFFFFF, INDEX_MAX,\n        {URI_MAX, LN_MAX}}\n};\n\n");

	/* Build the document grammar rules */
	fprintf(out, "static CONST GrammarRule %sdocGrammarRule[2] =\n{\n", prefix);
	fprintf(out, "    {%s, %u, 0},\n\
    {%s, 1, 0}\n};\n\n", varNameContent, (unsigned int) docGr->rule[GR_DOC_CONTENT].pCount, varNameEnd);
}

void staticPrefixOutput(PfxTable* pfxTbl, char* prefix, Index uriId, Deviations dvis, FILE* out)
{
	Index pfxIter;
	if(pfxTbl->count > 0)
	{
		fprintf(out, "static CONST String %sPfxEntry_%u[%u] =\n{\n", prefix, (unsigned int) uriId, (unsigned int) pfxTbl->count + dvis.pfx);

		for(pfxIter = 0; pfxIter < pfxTbl->count; pfxIter++)
		{
			if(pfxTbl->pfx[pfxIter].length > 0)
				fprintf(out, "    {%sPFX_%u_%u, %u}%s", prefix, (unsigned int) uriId, (unsigned int) pfxIter, (unsigned int) pfxTbl->pfx[pfxIter].length,
						pfxIter==pfxTbl->count + dvis.pfx - 1?"\n};\n\n" : ",\n");
			else
				fprintf(out, "    {NULL, 0}%s", pfxIter==pfxTbl->count + dvis.pfx - 1?"\n};\n\n" : ",\n");
		}

		for(pfxIter = 0; pfxIter < dvis.pfx; pfxIter++)
		{
			fprintf(out, "    {NULL, 0}%s", pfxIter==dvis.pfx - 1?"\n};\n\n" : ",\n");
		}
	}
}

void staticLnEntriesOutput(LnTable* lnTbl, char* prefix, Index uriId, Deviations dvis, FILE* out)
{
	Index lnIter;
	char elemGrammar[20];
	char typeGrammar[20];
	char attrTypeId[20];

	if(lnTbl->count + dvis.ln> 0)
	{
		fprintf(out, "static CONST LnEntry %sLnEntry_%u[%u] =\n{\n", prefix, (unsigned int) uriId, (unsigned int) lnTbl->count  + dvis.ln);

		for(lnIter = 0; lnIter < lnTbl->count; lnIter++)
		{
			if(lnTbl->ln[lnIter].elemGrammar == INDEX_MAX)
				strcpy(elemGrammar, "INDEX_MAX");
			else
				sprintf(elemGrammar, "%u", (unsigned int) lnTbl->ln[lnIter].elemGrammar);

			if(lnTbl->ln[lnIter].typeGrammar == INDEX_MAX)
				strcpy(typeGrammar, "INDEX_MAX");
			else
				sprintf(typeGrammar, "%u", (unsigned int) lnTbl->ln[lnIter].typeGrammar);

			if(lnTbl->ln[lnIter].attrTypeId == INDEX_MAX)
				strcpy(attrTypeId, "INDEX_MAX");
			else
				sprintf(attrTypeId, "%u", (unsigned int) lnTbl->ln[lnIter].attrTypeId);

			fprintf(out, "    {\n#if VALUE_CROSSTABLE_USE\n         NULL,\n#endif\n");
			if(lnTbl->ln[lnIter].lnStr.length > 0)
				fprintf(out, "        {%sLN_%u_%u, %u},\n        %s, %s, %s\n", prefix, (unsigned int) uriId, (unsigned int) lnIter, (unsigned int) lnTbl->ln[lnIter].lnStr.length, elemGrammar, typeGrammar, attrTypeId);
			else
				fprintf(out, "        {NULL, 0},\n        %s, %s, %s\n", elemGrammar, typeGrammar, attrTypeId);
			fprintf(out, "%s", lnIter==(lnTbl->count-1) + dvis.ln?"    }\n};\n\n":"    },\n");
		}

		strcpy(elemGrammar, "INDEX_MAX");
		strcpy(typeGrammar, "INDEX_MAX");
		strcpy(attrTypeId, "INDEX_MAX");

		for(lnIter = 0; lnIter < dvis.ln; lnIter++)
		{
			fprintf(out, "    {\n#if VALUE_CROSSTABLE_USE\n         NULL,\n#endif\n");
			fprintf(out, "        {NULL, 0},\n        %s, %s, %s\n", elemGrammar, typeGrammar, attrTypeId);
			fprintf(out, "%s", lnIter==dvis.ln - 1?"    }\n};\n\n":"    },\n");
		}
	} /* END if(lnTableSize > 0) */
}

void staticUriTableOutput(UriTable* uriTbl, char* prefix, Deviations dvis, FILE* out)
{
	Index uriIter;
	fprintf(out, "static CONST UriEntry %suriEntry[%u] =\n{\n", prefix, (unsigned int) uriTbl->count + dvis.url);

	for(uriIter = 0; uriIter < uriTbl->count; uriIter++)
	{
		if(uriTbl->uri[uriIter].lnTable.count > 0)
        {
			fprintf(out,
                    "    {\n        {{sizeof(LnEntry), %u, %u}, %sLnEntry_%u, %u},\n",
                    (unsigned int) uriTbl->uri[uriIter].lnTable.count,
                    (unsigned int) uriTbl->uri[uriIter].lnTable.count + dvis.ln,
                    prefix,
                    (unsigned int) uriIter,
                    (unsigned int) uriTbl->uri[uriIter].lnTable.count);
        }
		else
        {
			fprintf(out, "    {\n        {{sizeof(LnEntry), %d, %d}, NULL, 0},\n", 0, 0);
        }

		if(uriTbl->uri[uriIter].pfxTable.count > 0)
		{
			fprintf(out, "        {{sizeof(String), %u, %u}, %sPfxEntry_%u, %u},\n",
					(unsigned int) uriTbl->uri[uriIter].pfxTable.count,
					(unsigned int) uriTbl->uri[uriIter].pfxTable.count + dvis.pfx,
					prefix,
					(unsigned int) uriIter,
					(unsigned int) uriTbl->uri[uriIter].pfxTable.count);
		}
		else
		{
			fprintf(out, "        {{sizeof(String), %d, %d}, NULL, 0},\n", 0, 0);
		}

		if(uriTbl->uri[uriIter].uriStr.length > 0)
			fprintf(out, "        {%sURI_%u, %u}%s", prefix, (unsigned int) uriIter, (unsigned int) uriTbl->uri[uriIter].uriStr.length,
                uriIter==(uriTbl->count-1) + dvis.url?"\n    }\n};\n\n":"\n    },\n");
		else
			fprintf(out, "        {NULL, 0}%s", uriIter==(uriTbl->count-1) + dvis.url?"\n    }\n};\n\n":"\n    },\n");
	}

	for(uriIter = 0; uriIter < dvis.url; uriIter++)
	{
		fprintf(out, "    {\n        {{sizeof(LnEntry), %d, %d}, NULL, 0},\n", dvis.ln, dvis.ln);
		fprintf(out, "        {{sizeof(String), %d, %d}, NULL, 0},\n", 0, 0);
		fprintf(out, "        {NULL, 0}%s", uriIter==dvis.url - 1?"\n    }\n};\n\n":"\n    },\n");
	}
}

void staticEnumTableOutput(EXIPSchema* schema, char* prefix, FILE* out)
{
	EnumDefinition* tmpDef;
	char varName[VAR_BUFFER_MAX_LENGTH];
	Index i, j;

	if(schema->enumTable.count == 0)
		return;

	for(i = 0; i < schema->enumTable.count; i++)
	{
		tmpDef = &schema->enumTable.enumDef[i];
		switch(GET_EXI_TYPE(schema->simpleTypeTable.sType[tmpDef->typeId].content))
		{
			case VALUE_TYPE_STRING:
			{
				String* tmpStr;
				for(j = 0; j < tmpDef->count; j++)
				{
					tmpStr = &((String*) tmpDef->values)[j];
					sprintf(varName, "%sENUM_%u_%u", prefix, (unsigned int) i, (unsigned int) j);
					staticStringDefOutput(tmpStr, varName, out);
				}
				fprintf(out, "\nstatic CONST String %senumValues_%u[%u] = { \n", prefix, (unsigned int) i, (unsigned int) tmpDef->count);
				for(j = 0; j < tmpDef->count; j++)
				{
					tmpStr = &((String*) tmpDef->values)[j];
					if(tmpStr->str != NULL)
						fprintf(out, "   {%sENUM_%u_%u, %u}", prefix, (unsigned int) i, (unsigned int) j, (unsigned int) tmpStr->length);
					else
						fprintf(out, "   {NULL, 0}");

					if(j < tmpDef->count - 1)
						fprintf(out, ",\n");
					else
						fprintf(out, "\n};\n\n");
				}
			} break;
			case VALUE_TYPE_BOOLEAN:
				// NOT_IMPLEMENTED
				assert(FALSE);
				break;
			case VALUE_TYPE_DATE_TIME:
			case VALUE_TYPE_YEAR:
			case VALUE_TYPE_DATE:
			case VALUE_TYPE_MONTH:
			case VALUE_TYPE_TIME:
				// NOT_IMPLEMENTED
				assert(FALSE);
				break;
			case VALUE_TYPE_DECIMAL:
				// NOT_IMPLEMENTED
				assert(FALSE);
				break;
			case VALUE_TYPE_FLOAT:
				// NOT_IMPLEMENTED
				assert(FALSE);
				break;
			case VALUE_TYPE_INTEGER:
				// NOT_IMPLEMENTED
				assert(FALSE);
				break;
			case VALUE_TYPE_SMALL_INTEGER:
				// NOT_IMPLEMENTED
				assert(FALSE);
				break;
			case VALUE_TYPE_NON_NEGATIVE_INT:
				fprintf(out, "\nstatic CONST UnsignedInteger %senumValues_%u[%u] = { \n", prefix, (unsigned int) i, (unsigned int) tmpDef->count);
				for(j = 0; j < tmpDef->count; j++)
				{
					fprintf(out, "   0x%016lX", (long unsigned) ((UnsignedInteger*) tmpDef->values)[j]);

					if(j < tmpDef->count - 1)
						fprintf(out, ",\n");
					else
						fprintf(out, "\n};\n\n");
				}
				break;
		}
	}

	fprintf(out, "static CONST EnumDefinition %senumTable[%u] = { \n", prefix, (unsigned int) schema->enumTable.count);
	for(i = 0; i < schema->enumTable.count; i++)
	{
		tmpDef = &schema->enumTable.enumDef[i];
		fprintf(out, "   {%u, %senumValues_%u, %u}", (unsigned int) tmpDef->typeId, prefix, (unsigned int) i, (unsigned int) tmpDef->count);

		if(i < schema->enumTable.count - 1)
			fprintf(out, ",\n");
		else
			fprintf(out, "\n};\n\n");
	}
}
