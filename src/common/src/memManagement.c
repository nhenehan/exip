/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file memManagement.c
 * @brief Implementation of handling memory operations - allocation, deallocation etc.
 * @date Oct 25, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: memManagement.c 352 2014-11-25 16:37:24Z kjussakov $
 */

#include "memManagement.h"
#include "hashtable.h"
#include "dynamicArray.h"
#include "sTables.h"
#include "grammars.h"

errorCode initAllocList(AllocList* list)
{
	list->firstBlock = EXIP_MALLOC(sizeof(struct allocBlock));
	if(list->firstBlock == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;
	list->firstBlock->nextBlock = NULL;
	list->lastBlock = list->firstBlock;
	list->currAllocSlot = 0;

	return EXIP_OK;
}

void* memManagedAllocate(AllocList* list, size_t size)
{
	void* ptr = EXIP_MALLOC(size);
	if(ptr != NULL)
	{
		if(list->currAllocSlot == ALLOCATION_ARRAY_SIZE)
		{
			struct allocBlock* newBlock = EXIP_MALLOC(sizeof(struct allocBlock));
			if(newBlock == NULL)
				return NULL;

			newBlock->nextBlock = NULL;
			list->lastBlock->nextBlock = newBlock;
			list->lastBlock = newBlock;
			list->currAllocSlot = 0;
		}

		list->lastBlock->allocation[list->currAllocSlot] = ptr;
		list->currAllocSlot += 1;
	}
	return ptr;
}

void freeAllMem(EXIStream* strm)
{
	Index i;

	if(strm->schema != NULL) // can be, in case of error during EXIStream initialization
	{
#if BUILD_IN_GRAMMARS_USE
		{
		Index g;
		DynGrammarRule* tmp_rule;
		// Explicitly free the memory for any build-in grammars
		for(g = strm->schema->staticGrCount; g < strm->schema->grammarTable.count; g++)
		{
			for(i = 0; i < strm->schema->grammarTable.grammar[g].count; i++)
			{
				tmp_rule = &((DynGrammarRule*) strm->schema->grammarTable.grammar[g].rule)[i];
				if(tmp_rule->production != NULL)
					EXIP_MFREE(tmp_rule->production);
			}
			EXIP_MFREE(strm->schema->grammarTable.grammar[g].rule);
		}

		strm->schema->grammarTable.count = strm->schema->staticGrCount;
		}
#else
		assert(strm->schema->grammarTable.count == strm->schema->staticGrCount);
#endif

#if VALUE_CROSSTABLE_USE
		// Freeing the value cross tables
		{
		Index j;
		for(i = 0; i < strm->schema->uriTable.count; i++)
		{
			for(j = 0; j < strm->schema->uriTable.uri[i].lnTable.count; j++)
			{
				if(GET_LN_URI_IDS(strm->schema->uriTable, i, j).vxTable != NULL)
				{
					assert(GET_LN_URI_IDS(strm->schema->uriTable, i, j).vxTable->vx);
					destroyDynArray(&GET_LN_URI_IDS(strm->schema->uriTable, i, j).vxTable->dynArray);
					GET_LN_URI_IDS(strm->schema->uriTable, i, j).vxTable = NULL;
				}
			}
		}
		}
#endif

		// In case a default schema was used for this stream
		if(strm->schema->staticGrCount <= SIMPLE_TYPE_COUNT)
		{
			// No schema-informed grammars. This is an empty EXIPSchema container that needs to be freed
			// Freeing the string tables

			for(i = 0; i < strm->schema->uriTable.count; i++)
			{
				destroyDynArray(&strm->schema->uriTable.uri[i].pfxTable.dynArray);
				destroyDynArray(&strm->schema->uriTable.uri[i].lnTable.dynArray);
			}

			destroyDynArray(&strm->schema->uriTable.dynArray);
			destroyDynArray(&strm->schema->grammarTable.dynArray);
			if(strm->schema->simpleTypeTable.sType != NULL)
				destroyDynArray(&strm->schema->simpleTypeTable.dynArray);
			freeAllocList(&strm->schema->memList);
		}
		else
		{
			// Possible additions of string table entries must be removed
			for(i = 0; i < strm->schema->uriTable.dynArray.chunkEntries; i++)
			{
				strm->schema->uriTable.uri[i].pfxTable.count = strm->schema->uriTable.uri[i].pfxTable.dynArray.chunkEntries;
				strm->schema->uriTable.uri[i].lnTable.count = strm->schema->uriTable.uri[i].lnTable.dynArray.chunkEntries;
			}

			for(i = strm->schema->uriTable.dynArray.chunkEntries; i < strm->schema->uriTable.count; i++)
			{
				destroyDynArray(&strm->schema->uriTable.uri[i].pfxTable.dynArray);
				destroyDynArray(&strm->schema->uriTable.uri[i].lnTable.dynArray);
			}

			strm->schema->uriTable.count = strm->schema->uriTable.dynArray.chunkEntries;
		}
	}

	// Hash tables are freed separately
	// #DOCUMENT#
#if HASH_TABLE_USE
	if(strm->valueTable.hashTbl != NULL)
		hashtable_destroy(strm->valueTable.hashTbl);
#endif

	// Freeing the value table if present
	if(strm->valueTable.value != NULL)
	{
		Index i;
		for(i = 0; i < strm->valueTable.count; i++)
		{
			EXIP_MFREE(strm->valueTable.value[i].valueStr.str);
		}

		destroyDynArray(&strm->valueTable.dynArray);
	}

	freeAllocList(&(strm->memList));
}

void freeAllocList(AllocList* list)
{
	struct allocBlock* tmpBlock = list->firstBlock;
	struct allocBlock* rmBl;
	unsigned int i = 0;
	unsigned int allocLimitInBlock;

	while(tmpBlock != NULL)
	{
		if(tmpBlock->nextBlock != NULL)
			allocLimitInBlock = ALLOCATION_ARRAY_SIZE;
		else
			allocLimitInBlock = list->currAllocSlot;

		for(i = 0; i < allocLimitInBlock; i++)
			EXIP_MFREE(tmpBlock->allocation[i]);

		rmBl = tmpBlock;
		tmpBlock = tmpBlock->nextBlock;
		EXIP_MFREE(rmBl);
	}
}
