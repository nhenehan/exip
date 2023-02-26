/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file sTables.c
 * @brief Implementation of functions describing EXI sting tables operations
 * @date Sep 21, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: sTables.c 353 2014-11-25 16:43:28Z kjussakov $
 */

#include "sTables.h"
#include "stringManipulate.h"
#include "memManagement.h"
#include "hashtable.h"
#include "dynamicArray.h"

/********* BEGIN: String table default entries ***************/

extern CharType ops_URI_1[];
extern CharType ops_PFX_1_0[];
extern CharType ops_LN_1_0[];
extern CharType ops_LN_1_1[];
extern CharType ops_LN_1_2[];
extern CharType ops_LN_1_3[];
extern CharType ops_URI_2[];
extern CharType ops_PFX_2_0[];
extern CharType ops_LN_2_0[];
extern CharType ops_LN_2_1[];
extern CharType ops_URI_3[];
extern CharType ops_LN_3_0[];
extern CharType ops_LN_3_1[];
extern CharType ops_LN_3_2[];
extern CharType ops_LN_3_3[];
extern CharType ops_LN_3_4[];
extern CharType ops_LN_3_5[];
extern CharType ops_LN_3_6[];
extern CharType ops_LN_3_7[];
extern CharType ops_LN_3_8[];
extern CharType ops_LN_3_9[];
extern CharType ops_LN_3_10[];
extern CharType ops_LN_3_11[];
extern CharType ops_LN_3_12[];
extern CharType ops_LN_3_13[];
extern CharType ops_LN_3_14[];
extern CharType ops_LN_3_15[];
extern CharType ops_LN_3_16[];
extern CharType ops_LN_3_17[];
extern CharType ops_LN_3_18[];
extern CharType ops_LN_3_19[];
extern CharType ops_LN_3_20[];
extern CharType ops_LN_3_21[];
extern CharType ops_LN_3_22[];
extern CharType ops_LN_3_23[];
extern CharType ops_LN_3_24[];
extern CharType ops_LN_3_25[];
extern CharType ops_LN_3_26[];
extern CharType ops_LN_3_27[];
extern CharType ops_LN_3_28[];
extern CharType ops_LN_3_29[];
extern CharType ops_LN_3_30[];
extern CharType ops_LN_3_31[];
extern CharType ops_LN_3_32[];
extern CharType ops_LN_3_33[];
extern CharType ops_LN_3_34[];
extern CharType ops_LN_3_35[];
extern CharType ops_LN_3_36[];
extern CharType ops_LN_3_37[];
extern CharType ops_LN_3_38[];
extern CharType ops_LN_3_39[];
extern CharType ops_LN_3_40[];
extern CharType ops_LN_3_41[];
extern CharType ops_LN_3_42[];
extern CharType ops_LN_3_43[];
extern CharType ops_LN_3_44[];
extern CharType ops_LN_3_45[];

const String XML_NAMESPACE = {ops_URI_1, 36};
const String XML_SCHEMA_INSTANCE = {ops_URI_2, 41};
const String XML_SCHEMA_NAMESPACE = {ops_URI_3, 32};

const String URI_1_PFX = {ops_PFX_1_0, 3};
static const String URI_2_PFX = {ops_PFX_2_0, 3};

#define URI_1_LN_SIZE 4
static const String URI_1_LN[] = {{ops_LN_1_0, 4}, {ops_LN_1_1, 2}, {ops_LN_1_2, 4}, {ops_LN_1_3, 5}};

#define URI_2_LN_SIZE 2
const String URI_2_LN[] = {{ops_LN_2_0, 3}, {ops_LN_2_1, 4}};

#define URI_3_LN_SIZE 46
static const String URI_3_LN[] = {
			{ops_LN_3_0, 8},
			{ops_LN_3_1, 6},
			{ops_LN_3_2, 2},
			{ops_LN_3_3, 5},
			{ops_LN_3_4, 6},
			{ops_LN_3_5, 6},
			{ops_LN_3_6, 7},
			{ops_LN_3_7, 8},
			{ops_LN_3_8, 8},
			{ops_LN_3_9, 4},
			{ops_LN_3_10, 5},
			{ops_LN_3_11, 13},
			{ops_LN_3_12, 7},
			{ops_LN_3_13, 6},
			{ops_LN_3_14, 12},
			{ops_LN_3_15, 7},
			{ops_LN_3_16, 4},
			{ops_LN_3_17, 4},
			{ops_LN_3_18, 8},
			{ops_LN_3_19, 7},
			{ops_LN_3_20, 6},
			{ops_LN_3_21, 8},
			{ops_LN_3_22, 5},
			{ops_LN_3_23, 4},
			{ops_LN_3_24, 6},
			{ops_LN_3_25, 9},
			{ops_LN_3_26, 5},
			{ops_LN_3_27, 10},
			{ops_LN_3_28, 9},
			{ops_LN_3_29, 3},
			{ops_LN_3_30, 7},
			{ops_LN_3_31, 8},
			{ops_LN_3_32, 4},
			{ops_LN_3_33, 15},
			{ops_LN_3_34, 18},
			{ops_LN_3_35, 18},
			{ops_LN_3_36, 16},
			{ops_LN_3_37, 15},
			{ops_LN_3_38, 5},
			{ops_LN_3_39, 6},
			{ops_LN_3_40, 4},
			{ops_LN_3_41, 5},
			{ops_LN_3_42, 12},
			{ops_LN_3_43, 11},
			{ops_LN_3_44, 12},
			{ops_LN_3_45, 13}
	};

/********* END: String table default entries ***************/

errorCode createUriTableEntries(UriTable* uriTable, boolean withSchema)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	String emptyStr;
	getEmptyString(&emptyStr);

	// See http://www.w3.org/TR/exi/#initialUriValues

	// URI 0: "" (empty string)
	TRY(createUriTableEntry(uriTable,
									   emptyStr,   // Namespace - empty string
									   TRUE, // Create prefix entry
									   emptyStr,   // Prefix entry - empty string
									   NULL, // No local names
									   0));

	// URI 1: "http://www.w3.org/XML/1998/namespace"
	TRY(createUriTableEntry(uriTable,
									   XML_NAMESPACE,     // URI: "http://www.w3.org/XML/1998/namespace"
									   TRUE,      // Create prefix entry
									   URI_1_PFX, // Prefix: "xml"
									   URI_1_LN,  // Add local names
									   URI_1_LN_SIZE));

	// URI 2: "http://www.w3.org/2001/XMLSchema-instance"
	TRY(createUriTableEntry(uriTable,
									   XML_SCHEMA_INSTANCE,     // URI: "http://www.w3.org/2001/XMLSchema-instance"
									   TRUE,		// Create prefix entry
									   URI_2_PFX, // Prefix: "xsi"
									   URI_2_LN,  // Add local names
									   URI_2_LN_SIZE));

	if(withSchema == TRUE)
	{
		// URI 3: "http://www.w3.org/2001/XMLSchema"
		TRY(createUriTableEntry(uriTable,
										   XML_SCHEMA_NAMESPACE,    // URI: "http://www.w3.org/2001/XMLSchema"
										   FALSE,    // No prefix entry (see http://www.w3.org/TR/exi/#initialPrefixValues) 
										   emptyStr,     // (no prefix)
										   URI_3_LN, // Add local names
										   URI_3_LN_SIZE));
	}

	return EXIP_OK;
}

boolean lookupUri(UriTable* uriTable, String uriStr, SmallIndex* uriEntryId)
{
	SmallIndex i;

	if(uriTable == NULL)
		return FALSE;

	for(i = 0; i < uriTable->count; i++)
	{
		if(stringEqual(uriTable->uri[i].uriStr, uriStr))
		{
			*uriEntryId = i;
			return TRUE;
		}
	}
	return FALSE;
}

boolean lookupLn(LnTable* lnTable, String lnStr, Index* lnEntryId)
{
	Index i;

	if(lnTable == NULL)
		return FALSE;
	for(i = 0; i < lnTable->count; i++)
	{
		if(stringEqual(lnTable->ln[i].lnStr, lnStr))
		{
			*lnEntryId = i;
			return TRUE;
		}
	}
	return FALSE;
}

boolean lookupPfx(PfxTable* pfxTable, String pfxStr, SmallIndex* pfxEntryId)
{
	SmallIndex i;

	for(i = 0; i < pfxTable->count; i++)
	{
		if(stringEqual(pfxTable->pfx[i], pfxStr))
		{
			*pfxEntryId = i;
			return TRUE;
		}
	}
	return FALSE;
}

#if VALUE_CROSSTABLE_USE
boolean lookupVx(ValueTable* valueTable, VxTable* vxTable, String valueStr, Index* vxEntryId)
{
	Index i;
	VxEntry* vxEntry;
	ValueEntry* valueEntry;

	if(vxTable == NULL || vxTable->vx == NULL)
		return FALSE;

	for(i = 0; i < vxTable->count; i++)
	{
		vxEntry = vxTable->vx + i;
		if(vxEntry->globalId == INDEX_MAX) // The value was removed from the local value partition
			continue;
		valueEntry = valueTable->value + vxEntry->globalId;
		if(stringEqual(valueEntry->valueStr, valueStr))
		{
			*vxEntryId = i;
			return TRUE;
		}
	}
	return FALSE;
}
#endif

boolean lookupValue(ValueTable* valueTable, String valueStr, Index* valueEntryId)
{
	Index i;
	ValueEntry* valueEntry;

	assert(valueTable);

#if HASH_TABLE_USE
	if(valueTable->hashTbl != NULL)
	{
		// Use hash table search
		i = hashtable_search(valueTable->hashTbl, valueStr);
		if(i != INDEX_MAX)
		{
			*valueEntryId = i;
			return TRUE;
		}
	}
	else
#endif
	{
		// No hash table - linear search
		for(i = 0; i < valueTable->count; i++)
		{
			valueEntry = valueTable->value + i;
			if(stringEqual(valueEntry->valueStr, valueStr))
			{
				*valueEntryId = i;
				return TRUE;
			}
		}
	}

	return FALSE;
}
