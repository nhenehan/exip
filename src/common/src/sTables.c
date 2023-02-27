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

errorCode createValueTable(ValueTable* valueTable)
{
	errorCode tmp_err_code;

	TRY(createDynArray(&valueTable->dynArray, sizeof(ValueEntry), DEFAULT_VALUE_ENTRIES_NUMBER));

	valueTable->globalId = 0;
#if HASH_TABLE_USE
	valueTable->hashTbl = NULL;
#endif
	return EXIP_OK;
}

errorCode addUriEntry(UriTable* uriTable, String uriStr, SmallIndex* uriEntryId)
{
	errorCode tmp_err_code;
	UriEntry* uriEntry;
	Index uriLEntryId;

	TRY(addEmptyDynEntry(&uriTable->dynArray, (void**)&uriEntry, &uriLEntryId));

	// Fill in URI entry
	uriEntry->uriStr = uriStr;

	// Create an empty prefix table
	TRY(createDynArray(&uriEntry->pfxTable.dynArray, sizeof(String), DEFAULT_PFX_ENTRIES_NUMBER));

	// Create local names table for this URI
	TRY(createDynArray(&uriEntry->lnTable.dynArray, sizeof(LnEntry), DEFAULT_LN_ENTRIES_NUMBER));

	*uriEntryId = (SmallIndex)uriLEntryId;
	return EXIP_OK;
}

errorCode addLnEntry(LnTable* lnTable, String lnStr, Index* lnEntryId)
{
	errorCode tmp_err_code;
	LnEntry* lnEntry;

	TRY(addEmptyDynEntry(&lnTable->dynArray, (void**)&lnEntry, lnEntryId));

	// Fill in local names entry
	lnEntry->lnStr = lnStr;
	lnEntry->elemGrammar = INDEX_MAX;
	lnEntry->typeGrammar = INDEX_MAX;
#if VALUE_CROSSTABLE_USE
	// The Vx table is created on-demand (additions to value cross table are done when a value is inserted in the value table)
	lnEntry->vxTable = NULL;
#endif
	return EXIP_OK;
}

errorCode addValueEntry(EXIStream* strm, String valueStr, QNameID qnameID)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ValueEntry* valueEntry = NULL;
	Index valueEntryId;

#if VALUE_CROSSTABLE_USE
	Index vxEntryId;
	{
		struct LnEntry* lnEntry;
		VxEntry vxEntry;

		// Find the local name entry from QNameID
		lnEntry = &GET_LN_URI_QNAME(strm->schema->uriTable, qnameID);

		// Add entry to the local name entry's value cross table (vxTable)
		if(lnEntry->vxTable == NULL)
		{
			lnEntry->vxTable = memManagedAllocate(&strm->memList, sizeof(VxTable));
			if(lnEntry->vxTable == NULL)
				return EXIP_MEMORY_ALLOCATION_ERROR;

			// First value entry - create the vxTable
			TRY(createDynArray(&lnEntry->vxTable->dynArray, sizeof(VxEntry), DEFAULT_VX_ENTRIES_NUMBER));
		}

		assert(lnEntry->vxTable->vx);

		// Set the global ID in the value cross table entry
		vxEntry.globalId = strm->valueTable.globalId;

		// Add the entry
		TRY(addDynEntry(&lnEntry->vxTable->dynArray, (void*) &vxEntry, &vxEntryId));
	}
#endif

	// If the global ID is less than the actual array size, we must have wrapped around
	// In this case, we must reuse an existing entry
	if(strm->valueTable.globalId < strm->valueTable.count)
	{
		// Get the existing value entry
		valueEntry = &strm->valueTable.value[strm->valueTable.globalId];

#if VALUE_CROSSTABLE_USE
		assert(GET_LN_URI_QNAME(strm->schema->uriTable, valueEntry->locValuePartition.forQNameId).vxTable);
		// Null out the existing cross table entry
		GET_LN_URI_QNAME(strm->schema->uriTable, valueEntry->locValuePartition.forQNameId).vxTable->vx[valueEntry->locValuePartition.vxEntryId].globalId = INDEX_MAX;
#endif

#if HASH_TABLE_USE
		// Remove existing value string from hash table (if present)
		if(strm->valueTable.hashTbl != NULL)
		{
			hashtable_remove(strm->valueTable.hashTbl, valueEntry->valueStr);
		}
#endif
		// Free the memory allocated by the previous string entry
		EXIP_MFREE(valueEntry->valueStr.str);
	}
	else
	{
		// We are filling up the array and have not wrapped round yet
		// See http://www.w3.org/TR/exi/#encodingOptimizedForMisses
		TRY(addEmptyDynEntry(&strm->valueTable.dynArray, (void**)&valueEntry, &valueEntryId));
	}

	// Set the value entry fields
	valueEntry->valueStr = valueStr;
#if VALUE_CROSSTABLE_USE
	valueEntry->locValuePartition.forQNameId = qnameID;
	valueEntry->locValuePartition.vxEntryId = vxEntryId;
#endif

#if HASH_TABLE_USE
	// Add value string to hash table (if present)
	if(strm->valueTable.hashTbl != NULL)
	{
		TRY(hashtable_insert(strm->valueTable.hashTbl, valueStr, strm->valueTable.globalId));
	}
#endif

	// Increment global ID
	strm->valueTable.globalId++;

	// The value table is limited by valuePartitionCapacity. If we have exceeded, we wrap around
	// to the beginning of the value table and null out existing IDs in the corresponding
	// cross table IDs
	if(strm->valueTable.globalId == strm->header.opts.valuePartitionCapacity)
		strm->valueTable.globalId = 0;

	return EXIP_OK;
}

errorCode addPfxEntry(PfxTable* pfxTable, String pfxStr, SmallIndex* pfxEntryId)
{
	errorCode tmp_err_code;
	String* strEntry;

	TRY(addEmptyDynEntry(&pfxTable->dynArray, (void**)&strEntry, pfxEntryId));

	// Fill in local names entry
	strEntry->length = pfxStr.length;
	strEntry->str = pfxStr.str;

	return EXIP_OK;
}

errorCode createUriTableEntry(UriTable* uriTable, const String uri, int createPfx, const String pfx, const String* lnBase, Index lnSize)
{
	errorCode tmp_err_code;
	Index i;
	SmallIndex pfxEntryId;
	SmallIndex uriEntryId;
	Index lnEntryId;
	UriEntry* uriEntry;

	// Add resulting String to URI table (creates lnTable as well)
	TRY(addUriEntry(uriTable, uri, &uriEntryId));

	// Get ptr. to URI Entry
	uriEntry = &uriTable->uri[uriEntryId];

	if(createPfx)
		TRY(addPfxEntry(&uriEntry->pfxTable, pfx, &pfxEntryId));

	for(i = 0; i < lnSize; i++)
	{
		TRY(addLnEntry(&uriEntry->lnTable, lnBase[i], &lnEntryId));
	}
	return EXIP_OK;
}
