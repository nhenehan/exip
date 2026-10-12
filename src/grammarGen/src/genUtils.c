/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file genUtils.c
 * @brief Implementation of utility functions for generating Schema-informed Grammar definitions
 * @date Nov 23, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: genUtils.c 332 2014-05-05 18:22:55Z kjussakov $
 */

#include "genUtils.h"
#include "memManagement.h"
#include "stringManipulate.h"
#include "grammars.h"
#include "ioUtil.h"
#include "initSchemaInstance.h"

/** This function @returns TRUE is the two grammar rules represent the same state. Otherwise false */
static char rulesEqual(ProtoGrammar* g1, Index ruleIndx1, ProtoGrammar* g2, Index ruleIndx2);

/** Collision aware addition of all the productions from grammar rule right[ruleIndxR]
 * to the grammar rule left[ruleIndxL] */
static errorCode addProductionsToARule(ProtoGrammar* left, Index ruleIndxL, ProtoGrammar* right, Index ruleIndxR,
									   unsigned int* currRuleIndex, unsigned int initialLeftRulesCount);

errorCode concatenateGrammars(ProtoGrammar* left, ProtoGrammar* right)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	unsigned int ruleIterL = 0;
	unsigned int ruleIterR = 0;
	unsigned int prodIterL = 0;
	unsigned int prodIterR = 0;
	unsigned int currRuleIndex;
	unsigned int initialLeftRulesCount;
	ProtoRuleEntry* pRuleEntry;

	assert(left);

	if(right == NULL)
		return EXIP_OK;

	/* 
	 * Concatentation works as follows:
	 * Add each rule apart from the first one on the RHS to the LHS.
	 * Example:
	 * LHS has two rules already:
	 *     left->rule[2]
	 * RHS has four rules to concatentate:
	 *     right->rule[4]
	 * Append all RHS rule productions excluding the first rule directly to LHS
	 *     left->rule[2] = right->rule[1]
	 *     left->rule[3] = right->rule[2]
	 *     left->rule[4] = right->rule[3]
	 * Merge all LHS rule productions with the first RHS rule productions ("+=" means merge)
	 *     left->rule[0] += right->rule[0]
	 *     left->rule[1] += right->rule[0]
	 * Merging occurs after the EE production; this is replaced with the first production
	 * to be merged
	 * Resolve any collisions
	 */

	/* Make a note of how many rules are currently in LHS for the new non terminal IDs */
	initialLeftRulesCount = left->count;

	/* Add in rules from the RHS */
	for(ruleIterR = 1; ruleIterR < right->count; ruleIterR++)
	{
		/* Create new rule entry in LHS proto grammar */
		TRY(addProtoRule(left, right->rule[ruleIterR].count, &pRuleEntry));

		/* Copy the RHS productions into the new rule entry, adjusting the non terminal ID */
		for(prodIterR = 0; prodIterR < right->rule[ruleIterR].count; prodIterR++)
		{
			TRY(addOrderedProduction(pRuleEntry, GET_PROD_EXI_EVENT(right->rule[ruleIterR].prod[prodIterR].content),
										 right->rule[ruleIterR].prod[prodIterR].typeId,
										 right->rule[ruleIterR].prod[prodIterR].qnameId,
										 GET_PROD_NON_TERM(right->rule[ruleIterR].prod[prodIterR].content) + ((GET_PROD_EXI_EVENT(right->rule[ruleIterR].prod[prodIterR].content) == EVENT_EE)?0:(initialLeftRulesCount-1)), right->rule[ruleIterR].prod[prodIterR].order));
		}
	}

	currRuleIndex = left->count;

	for(ruleIterL = 0; ruleIterL < initialLeftRulesCount; ruleIterL++)
	{
		for(prodIterL = 0; prodIterL < left->rule[ruleIterL].count; prodIterL++)
		{
			if(GET_PROD_EXI_EVENT(left->rule[ruleIterL].prod[prodIterL].content) == EVENT_EE)
			{
				if(!rulesEqual(left, ruleIterL, right, 0))
				{
					/* Remove the EE production */
					delDynEntry(&left->rule[ruleIterL].dynArray, prodIterL);

					if(left->rule[ruleIterL].count == 0)
					{
						// Just copy all the production...
						for(prodIterR = 0; prodIterR < right->rule[0].count; prodIterR++)
						{
							TRY(addOrderedProduction(&left->rule[ruleIterL],
														 GET_PROD_EXI_EVENT(right->rule[0].prod[prodIterR].content),
														 right->rule[0].prod[prodIterR].typeId,
														 right->rule[0].prod[prodIterR].qnameId,
														 GET_PROD_NON_TERM(right->rule[0].prod[prodIterR].content) + ((GET_PROD_EXI_EVENT(right->rule[0].prod[prodIterR].content) == EVENT_EE)?0:(initialLeftRulesCount-1)), right->rule[0].prod[prodIterR].order));
						}
					}
					else
					{
						/* Merge productions from RHS rule 0 into each left rule */
						TRY(addProductionsToARule(left,
												 ruleIterL,
												 right,
												 0,
												 &currRuleIndex,
												 initialLeftRulesCount - 1));
					}
				}
				break;
			}
		}
	}

	return EXIP_OK;
}

static errorCode addProductionsToARule(ProtoGrammar* left, Index ruleIndxL, ProtoGrammar* right, Index ruleIndxR,
									   unsigned int* currRuleIndex, unsigned int initialLeftRulesCount)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	unsigned int prodIterL = 0;
	unsigned int prodIterR = 0;
	exip_bool rProdFoundInLeft = FALSE;
	Index nonTermRight;
	unsigned int prodCountR = right->rule[ruleIndxR].count; // Needed as left might be the same grammar as right

	for(prodIterR = 0; prodIterR < prodCountR; prodIterR++)
	{
		/* Check for equivalent productions */
		rProdFoundInLeft = FALSE;

		/* The use case when the Non-Terminal RHS symbol of the production is pointing to the same grammar rule
		 * can cause problems when the rules are merged. Few possible outcomes:
		 * - If all the productions from the right rule are contained in the left rule then the Non-Terminal RHS symbol
		 * can again point to the same rule safely
		 * - If that is not the case, try to find a rule in the left grammar that is equivalent to the
		 * right rule and make the Non-Terminal RHS symbol point to that grammar instead
		 * - If non of these is true then we need to create a new grammar rule on the left that is
		 * equivalent to the right rule and point the Non-Terminal RHS symbol to it */
		if(GET_PROD_NON_TERM(right->rule[ruleIndxR].prod[prodIterR].content) == 0)
		{
			ProtoRuleEntry* pRuleEntry;
			unsigned int tmpIterL, tmpIterR;
			exip_bool equalRRuleFound = FALSE;
			exip_bool allRProdIn = TRUE;
			exip_bool rProdFound = FALSE;

			// It is only an issue if we have productions in (right, ruleIndxR) that are not in (left, ruleIndxL); EE excluded
			for(tmpIterR = 0; tmpIterR < right->rule[ruleIndxR].count; tmpIterR++)
			{
				if(GET_PROD_EXI_EVENT(right->rule[ruleIndxR].prod[tmpIterR].content) != EVENT_EE)
				{
					rProdFound = FALSE;
					for(tmpIterL = 0; tmpIterL < left->rule[ruleIndxL].count; tmpIterL++)
					{
						if(GET_PROD_EXI_EVENT(right->rule[ruleIndxR].prod[tmpIterR].content) == GET_PROD_EXI_EVENT(left->rule[ruleIndxL].prod[tmpIterL].content))
						{
							rProdFound = TRUE;
							break;
						}
					}

					if(rProdFound == FALSE)
					{
						allRProdIn = FALSE;
						break;
					}
				}
			}

			if(allRProdIn)
			{
				// All productions in (right, ruleIndxR) are available in (left, ruleIndxL)
				nonTermRight = ruleIndxL;
			}
			else
			{
				// Try to find a rule in left, different from ruleIndxL that is equal to (right,ruleIndxR)
				for(tmpIterL = 0; tmpIterL < left->count; tmpIterL++)
				{
					if(tmpIterL != ruleIndxL && rulesEqual(left, tmpIterL, right, ruleIndxR))
					{
						// We found a rule that is equal, then make the Non-TermS on the RHS pointing to it
						nonTermRight = tmpIterL;
						equalRRuleFound = TRUE;
						break;
					}
				}

				if(equalRRuleFound == FALSE)
				{
					// Creating a new rule ...

					nonTermRight = *currRuleIndex;

					/* Create new rule entry in LHS proto grammar */
					TRY(addProtoRule(left, right->rule[ruleIndxR].count, &pRuleEntry));

					/* Copy the RHS productions into the new rule entry, adjusting the non terminal ID */
					for(tmpIterR = 0; tmpIterR < right->rule[ruleIndxR].count; tmpIterR++)
					{
						TRY(addOrderedProduction(pRuleEntry, GET_PROD_EXI_EVENT(right->rule[ruleIndxR].prod[tmpIterR].content),
								right->rule[ruleIndxR].prod[tmpIterR].typeId, right->rule[ruleIndxR].prod[tmpIterR].qnameId,
													 GET_PROD_NON_TERM(right->rule[ruleIndxR].prod[tmpIterR].content) + ((GET_PROD_EXI_EVENT(right->rule[ruleIndxR].prod[tmpIterR].content) == EVENT_EE)?0:(initialLeftRulesCount-1)), right->rule[ruleIndxR].prod[tmpIterR].order));
					}

					*currRuleIndex += 1;
				}
			}
		}
		else
			nonTermRight = GET_PROD_NON_TERM(right->rule[ruleIndxR].prod[prodIterR].content) + ((GET_PROD_EXI_EVENT(right->rule[ruleIndxR].prod[prodIterR].content) == EVENT_EE)?0:initialLeftRulesCount);

		for(prodIterL = 0; prodIterL < left->rule[ruleIndxL].count; prodIterL++)
		{
			/* Check for the same terminal symbol e.g. SE(qname) */
			if(GET_PROD_EXI_EVENT(left->rule[ruleIndxL].prod[prodIterL].content) == GET_PROD_EXI_EVENT(right->rule[ruleIndxR].prod[prodIterR].content) &&
					left->rule[ruleIndxL].prod[prodIterL].typeId == right->rule[ruleIndxR].prod[prodIterR].typeId &&
					left->rule[ruleIndxL].prod[prodIterL].qnameId.uriId == right->rule[ruleIndxR].prod[prodIterR].qnameId.uriId &&
					left->rule[ruleIndxL].prod[prodIterL].qnameId.lnId == right->rule[ruleIndxR].prod[prodIterR].qnameId.lnId)
			{
				/* Now check the non-terminal ID (noting that EE's don't have a non-terminal ID) */
				if(GET_PROD_EXI_EVENT(left->rule[ruleIndxL].prod[prodIterL].content) == EVENT_EE ||
				   GET_PROD_NON_TERM(left->rule[ruleIndxL].prod[prodIterL].content) == nonTermRight)
				{
					/*
					 * If the NonTerminals are the same as well, no need to add
					 * the production as it's already there
					 */
					rProdFoundInLeft = TRUE;
					/* Check the next production in LHS... */
					break;
				}
				else
				{
					// The LHS non-terminals are different for the two productions with the same terminal
					// Check if the rules that are indicated by the terminals are equal
					if(rulesEqual(left, GET_PROD_NON_TERM(left->rule[ruleIndxL].prod[prodIterL].content), left, nonTermRight))
					{
						// NonTerminals are different indexes but are otherwise equal
						// no need to add the production as it's already there
						rProdFoundInLeft = TRUE;
						/* Check the next production in LHS... */
						break;
					}
					// Otherwise equal terminals lead to different states: the production is
					// added and eliminateDuplicateTerminals() merges them (8.5.4.2.2)
				}
			}
		}

		if(rProdFoundInLeft == FALSE)
		{
			/*
			 * We have been through all LHS productions and there were no clashes
			 * so just add the production
			 */
			TRY(addOrderedProduction(&left->rule[ruleIndxL],
										 GET_PROD_EXI_EVENT(right->rule[ruleIndxR].prod[prodIterR].content),
										 right->rule[ruleIndxR].prod[prodIterR].typeId,
										 right->rule[ruleIndxR].prod[prodIterR].qnameId,
										 nonTermRight, right->rule[ruleIndxR].prod[prodIterR].order));
		}
	}
	return EXIP_OK;
}

errorCode createSimpleTypeGrammar(Index typeId, ProtoGrammar* simpleGrammar)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	QNameID qnameID = {URI_MAX, LN_MAX};
	ProtoRuleEntry* pRuleEntry;

	TRY(createProtoGrammar(2, simpleGrammar));

	TRY(addProtoRule(simpleGrammar, 3, &pRuleEntry));
	TRY(addProduction(pRuleEntry, EVENT_CH, typeId, qnameID, 1));
	TRY(addProtoRule(simpleGrammar, 2, &pRuleEntry));
	TRY(addEEProduction(pRuleEntry));

	return EXIP_OK;
}

errorCode createComplexTypeGrammar(ProtoGrammarArray* attrUseArray, ProtoGrammar* contentTypeGrammar,
							exip_bool isMixedContent, ProtoGrammar* complexGrammar)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	unsigned int i;

	if(isMixedContent && contentTypeGrammar != NULL)
	{
		/* If {content type} is a content model particle with mixed content, add a production for each non-terminal
		 * Content-i,j  in Content-i  as follows:
		 *  	Content-i,j  : CH [untyped value] Content-i,j
		 */
		QNameID dummyQId = {URI_MAX, LN_MAX};
		for(i = 0; i < contentTypeGrammar->count; i++)
		{
			TRY(addProduction(&contentTypeGrammar->rule[i], EVENT_CH, INDEX_MAX, dummyQId, i));
		}
	}

	if(attrUseArray->count > 0)
	{
		ProtoRuleEntry* pRuleEntry;

		TRY(createProtoGrammar(10, complexGrammar));
		TRY(addProtoRule(complexGrammar, 10, &pRuleEntry));
		TRY(addEEProduction(pRuleEntry));

		for(i = 0; i < attrUseArray->count; i++)
		{
			TRY(concatenateGrammars(complexGrammar, attrUseArray->pg[i]));
		}

		complexGrammar->contentIndex = complexGrammar->count - 1;

		if(contentTypeGrammar != NULL)
		{
			TRY(concatenateGrammars(complexGrammar, contentTypeGrammar));
		}
	}
	else
	{
		if(contentTypeGrammar != NULL)
		{
			TRY(cloneProtoGrammar(contentTypeGrammar, complexGrammar));
		}
		complexGrammar->contentIndex = 0;
	}

	return EXIP_OK;
}

errorCode createComplexUrTypeGrammar(ProtoGrammar* result)
{
	EXIP_UNUSED(result);
	return EXIP_NOT_IMPLEMENTED_YET;
}

errorCode createAttributeUseGrammar(exip_bool required, Index typeId,
									ProtoGrammar* attrGrammar, QNameID qnameID)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ProtoRuleEntry* pRuleEntry;

	TRY(createProtoGrammar(2, attrGrammar));

	TRY(addProtoRule(attrGrammar, 4, &pRuleEntry));
	TRY(addProduction(pRuleEntry, EVENT_AT_QNAME, typeId, qnameID, 1));

	if(!required)
	{
		TRY(addEEProduction(pRuleEntry));
	}

	TRY(addProtoRule(attrGrammar, 4, &pRuleEntry));
	TRY(addEEProduction(pRuleEntry));

	return EXIP_OK;
}

errorCode createParticleGrammar(int minOccurs, int maxOccurs,
								ProtoGrammar* termGrammar, ProtoGrammar* particleGrammar)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ProtoRuleEntry* pRuleEntry;
	int i;

	TRY(createProtoGrammar(minOccurs + 10, particleGrammar));

	TRY(addProtoRule(particleGrammar, 5, &pRuleEntry));
	TRY(addEEProduction(pRuleEntry));

	for(i = 0; i < minOccurs; i++)
	{
		TRY(concatenateGrammars(particleGrammar, termGrammar));
	}

	if(maxOccurs - minOccurs > 0 || maxOccurs < 0) // Only if maxOccurs is unbounded or maxOccurs > minOccurs
	{
		exip_bool prodEEFound = FALSE;
		for(i = 0; i < (int)termGrammar->rule[0].count; i++)
		{
			if(GET_PROD_EXI_EVENT(termGrammar->rule[0].prod[i].content) == EVENT_EE)
			{
				prodEEFound = TRUE;
				break;
			}
		}
		if(prodEEFound == FALSE) //	There is no production Gi,0 : EE so add one
		{
			TRY(addEEProduction(&termGrammar->rule[0]));
		}

		if(maxOccurs >= 0) // {max occurs} is not unbounded
		{
			for(i = 0; i < maxOccurs - minOccurs; i++)
			{
				TRY(concatenateGrammars(particleGrammar, termGrammar));
			}
		}
		else // {max occurs} is unbounded
		{
			Index j = 0;
			unsigned int currRuleIndex = termGrammar->count;

			// Excluding the first rule
			for(i = 1; i < (int)termGrammar->count; i++)
			{
				for(j = 0; j < termGrammar->rule[i].count; j++)
				{
					if(GET_PROD_EXI_EVENT(termGrammar->rule[i].prod[j].content) == EVENT_EE)
					{
						if(!rulesEqual(termGrammar, i, termGrammar, 0))
						{
							/* Remove the EE production */
							delDynEntry(&termGrammar->rule[i].dynArray, j);

							if(termGrammar->rule[i].count == 0)
							{
								Index prodIterR;
								// Just copy all the production...
								for(prodIterR = 0; prodIterR < termGrammar->rule[0].count; prodIterR++)
								{
									TRY(addOrderedProduction(&termGrammar->rule[i],
																 GET_PROD_EXI_EVENT(termGrammar->rule[0].prod[prodIterR].content),
																 termGrammar->rule[0].prod[prodIterR].typeId,
																 termGrammar->rule[0].prod[prodIterR].qnameId,
																 GET_PROD_NON_TERM(termGrammar->rule[0].prod[prodIterR].content), termGrammar->rule[0].prod[prodIterR].order));
								}
							}
							else
							{
								/* Merge productions from RHS rule 0 into each left rule */
								TRY(addProductionsToARule(termGrammar,
																	 i,
																	 termGrammar,
																	 0,
																	 &currRuleIndex,
																	 0));
							}
						}
						break;
					}
				}
			}

			TRY(concatenateGrammars(particleGrammar, termGrammar));
		}
	}

	return EXIP_OK;
}

errorCode createElementTermGrammar(ProtoGrammar* elemGrammar, QNameIDGrIndx* qnameGrArr, Index count, Index* schemaOrder)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ProtoRuleEntry* pRuleEntry;
	Index i;

	assert(qnameGrArr != NULL);

	TRY(createProtoGrammar(2, elemGrammar));
	TRY(addProtoRule(elemGrammar, 5, &pRuleEntry));
	for(i = 0; i < count; i++)
	{
		*schemaOrder += 1;
		TRY(addOrderedProduction(pRuleEntry, EVENT_SE_QNAME, qnameGrArr[i].grIndex, qnameGrArr[i].qnameId, 1, *schemaOrder));
	}

	TRY(addProtoRule(elemGrammar, 3, &pRuleEntry));
	TRY(addEEProduction(pRuleEntry));

	return EXIP_OK;
}

errorCode createWildcardTermGrammar(String* wildcardArray, Index wildcardArraySize, UriTable* uriT, ProtoGrammar* wildcardGrammar, Index* schemaOrder)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ProtoRuleEntry* pRuleEntry;
	QNameID qnameID;

	TRY(createProtoGrammar(2, wildcardGrammar));

	TRY(addProtoRule(wildcardGrammar, wildcardArraySize + 1, &pRuleEntry));
	if(wildcardArraySize == 0 ||		// default is "##any"
		(wildcardArraySize == 1 &&
				(stringEqualToAscii(wildcardArray[0], "##any") || stringEqualToAscii(wildcardArray[0], "##other"))
		)
	  )
	{
		qnameID.uriId = URI_MAX;
		qnameID.lnId = LN_MAX;
		TRY(addProduction(pRuleEntry, EVENT_SE_ALL, INDEX_MAX, qnameID, 1));
	}
	else if(wildcardArraySize >= 1)
	{
		Index i;

		qnameID.lnId = LN_MAX;
		for(i = 0; i < wildcardArraySize; i++)
		{
			if(!lookupUri(uriT, wildcardArray[i], &qnameID.uriId))
			 	return EXIP_UNEXPECTED_ERROR;
			// SE(uri:*) of one wildcard follow its namespace list. 8.5.4.3 says
			// "schema order" but does not order the uris of one wildcard; EXIficient 1.0.7
			// keeps insertion order ("sorted in schema order --> new event comes after"):
			// https://github.com/EXIficient/exificient-core/blob/9d853cb456a9d5557fa9d4544917a894c576ab96/src/main/java/com/siemens/ct/exi/core/grammars/grammar/AbstractSchemaInformedGrammar.java#L204-L206
			*schemaOrder += 1;
			TRY(addOrderedProduction(pRuleEntry, EVENT_SE_URI, INDEX_MAX, qnameID, 1, *schemaOrder));
		}
	}
	else
		return EXIP_UNEXPECTED_ERROR;

	TRY(addProtoRule(wildcardGrammar, 2, &pRuleEntry));
	TRY(addEEProduction(pRuleEntry));

	return EXIP_OK;
}

errorCode createSequenceModelGroupsGrammar(ProtoGrammar** grArray, unsigned int arrSize, ProtoGrammar* seqGrammar)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ProtoRuleEntry* pRuleEntry;

	if(arrSize == 0)
	{
		TRY(createProtoGrammar(3, seqGrammar));
		TRY(addProtoRule(seqGrammar, 3, &pRuleEntry));
		TRY(addEEProduction(pRuleEntry));
	}
	else
	{
		unsigned int i;

		TRY(createProtoGrammar(10, seqGrammar));
		TRY(addProtoRule(seqGrammar, 5, &pRuleEntry));
		TRY(addEEProduction(pRuleEntry));

		for(i = 0; i < arrSize; i++)
		{
			TRY(concatenateGrammars(seqGrammar, grArray[i]));
		}
	}
	return EXIP_OK;
}

errorCode createChoiceModelGroupsGrammar(ProtoGrammarArray* pgArray, ProtoGrammar* modGrpGrammar)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Index i;
	unsigned int ruleIterTerm = 0;
	unsigned int prodIterTerm = 0;
	unsigned int currRuleIndex;
	unsigned int initialResultRulesCount;
	ProtoGrammar* tmpGrammar;
	ProtoRuleEntry* pRuleEntry;

	TRY(createProtoGrammar(10, modGrpGrammar));

	TRY(addProtoRule(modGrpGrammar, 5, &pRuleEntry));
	TRY(addEEProduction(pRuleEntry));

	// Spec 8.5.4.1.8.2: a choice with no particles is ParticleTerm_0 : EE, which is
	// what was just built. Reading pg[0] of an empty array crashed.
	if(pgArray->count == 0)
		return EXIP_OK;

	tmpGrammar = pgArray->pg[0];
	if(tmpGrammar == NULL)
		return EXIP_NULL_POINTER_REF;

	TRY(concatenateGrammars(modGrpGrammar, tmpGrammar));

	for(i = 1; i < pgArray->count; i++)
	{

		tmpGrammar = pgArray->pg[i];

		if(tmpGrammar == NULL)
			return EXIP_NULL_POINTER_REF;

		initialResultRulesCount = modGrpGrammar->count;

		for(ruleIterTerm = 1; ruleIterTerm < tmpGrammar->count; ruleIterTerm++)
		{
			TRY(addProtoRule(modGrpGrammar, 5, &pRuleEntry));

			for(prodIterTerm = 0; prodIterTerm < tmpGrammar->rule[ruleIterTerm].count; prodIterTerm++)
			{
				TRY(addOrderedProduction(pRuleEntry,
											 GET_PROD_EXI_EVENT(tmpGrammar->rule[ruleIterTerm].prod[prodIterTerm].content),
											 tmpGrammar->rule[ruleIterTerm].prod[prodIterTerm].typeId,
											 tmpGrammar->rule[ruleIterTerm].prod[prodIterTerm].qnameId,
											 GET_PROD_NON_TERM(tmpGrammar->rule[ruleIterTerm].prod[prodIterTerm].content) + ((GET_PROD_EXI_EVENT(tmpGrammar->rule[ruleIterTerm].prod[prodIterTerm].content) == EVENT_EE)?0:(initialResultRulesCount-1)), tmpGrammar->rule[ruleIterTerm].prod[prodIterTerm].order));
			}
		}

		currRuleIndex = modGrpGrammar->count;

		if(!rulesEqual(modGrpGrammar, 0, tmpGrammar, 0))
		{
			if(modGrpGrammar->rule[0].count == 0)
			{
				Index prodIterR;
				// Just copy all the production...
				for(prodIterR = 0; prodIterR < tmpGrammar->rule[0].count; prodIterR++)
				{
					TRY(addOrderedProduction(&modGrpGrammar->rule[0],
												 GET_PROD_EXI_EVENT(tmpGrammar->rule[0].prod[prodIterR].content),
												 tmpGrammar->rule[0].prod[prodIterR].typeId,
												 tmpGrammar->rule[0].prod[prodIterR].qnameId,
												 GET_PROD_NON_TERM(tmpGrammar->rule[0].prod[prodIterR].content) + ((GET_PROD_EXI_EVENT(tmpGrammar->rule[0].prod[prodIterR].content) == EVENT_EE)?0:(initialResultRulesCount-1)), tmpGrammar->rule[0].prod[prodIterR].order));
				}
			}
			else
			{
				/* Merge productions from RHS rule 0 into each left rule */
				TRY(addProductionsToARule(modGrpGrammar,
													 0,
													 tmpGrammar,
													 0,
													 &currRuleIndex,
													 initialResultRulesCount - 1));
			}
		}
	}

	return EXIP_OK;
}

errorCode createAllModelGroupsGrammar(ProtoGrammarArray* pgArray, ProtoGrammar* modGrpGrammar)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ProtoGrammar choiceGrammar;

	// Any particle, any number of times: each particle's end loops back to the
	// start rule, which also has EE
	TRY(createChoiceModelGroupsGrammar(pgArray, &choiceGrammar));
	tmp_err_code = createParticleGrammar(0, -1, &choiceGrammar, modGrpGrammar);
	destroyProtoGrammar(&choiceGrammar);

	return tmp_err_code;
}

errorCode addEEProduction(ProtoRuleEntry* rule)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	ProtoProduction *prod;
	Index prodId;

	TRY(addEmptyDynEntry(&rule->dynArray, (void**)&prod, &prodId));

	prod->content = 0;
	prod->order = 0;
	SET_PROD_EXI_EVENT(prod->content, EVENT_EE);
	prod->typeId = INDEX_MAX;
	SET_PROD_NON_TERM(prod->content, GR_VOID_NON_TERMINAL);
	prod->qnameId.uriId = URI_MAX;
	prod->qnameId.lnId = LN_MAX;

	return EXIP_OK;
}

int compareQNameID(const void* qnameID1, const void* qnameID2, UriTable* uriTbl)
{
	/**
	 *  The strings in the string tables are sorted beforehand so simple comparison
	 *  of the indexes is enough.
	 */
	QNameID* qId1 = (QNameID*) qnameID1;
	QNameID* qId2 = (QNameID*) qnameID2;

	if(qId1->uriId == qId2->uriId)
	{
		// Within the same namespace
		if(qId1->lnId < qId2->lnId)
		{
			return -1;
		}
		else if(qId1->lnId > qId2->lnId)
		{
			return 1;
		}
	}
	else
	{
		// In different namespaces
		int i;
		i = stringCompare(GET_LN_P_URI_P_QNAME(uriTbl, qId1).lnStr, GET_LN_P_URI_P_QNAME(uriTbl, qId2).lnStr);
		if(i == 0)
		{
			if(qId1->uriId < qId2->uriId)
			{
				return -1;
			}
			else if(qId1->uriId > qId2->uriId)
			{
				return 1;
			}
		}
		else
			return i;
	}

	return 0;
}

static char rulesEqual(ProtoGrammar* g1, Index ruleIndx1, ProtoGrammar* g2, Index ruleIndx2)
{
	Index i, j;
	exip_bool prodFound;

	// TODO: currently it does not follow the right hand side non-terminals to check if the state there is the same...
	// It might not be needed; if needed there will be a recursive call that might lag a lot

	if(g1->rule[ruleIndx1].count != g2->rule[ruleIndx2].count)
		return FALSE;

	for(i = 0; i < g1->rule[ruleIndx1].count; i++)
	{
		prodFound = FALSE;
		for(j = 0; j < g2->rule[ruleIndx2].count; j++)
		{
			if(GET_PROD_EXI_EVENT(g1->rule[ruleIndx1].prod[i].content) == GET_PROD_EXI_EVENT(g2->rule[ruleIndx2].prod[j].content) &&
					g1->rule[ruleIndx1].prod[i].typeId == g2->rule[ruleIndx2].prod[j].typeId &&
					g1->rule[ruleIndx1].prod[i].qnameId.uriId == g2->rule[ruleIndx2].prod[j].qnameId.uriId &&
					g1->rule[ruleIndx1].prod[i].qnameId.lnId == g2->rule[ruleIndx2].prod[j].qnameId.lnId)
			{
				prodFound = TRUE;
				break;
			}
		}

		if(!prodFound)
			return FALSE;
	}

	return TRUE;
}

/* ---- Duplicate terminal elimination (8.5.4.2.2) ---- */

/** Two productions have the same terminal symbol */
static exip_bool sameTerminal(const ProtoProduction* p1, const ProtoProduction* p2)
{
	EventType ev = GET_PROD_EXI_EVENT(p1->content);

	if(ev != GET_PROD_EXI_EVENT(p2->content))
		return FALSE;

	switch(ev)
	{
		case EVENT_SE_QNAME:
		case EVENT_AT_QNAME:
			return p1->qnameId.uriId == p2->qnameId.uriId && p1->qnameId.lnId == p2->qnameId.lnId;
		case EVENT_SE_URI:
		case EVENT_AT_URI:
			return p1->qnameId.uriId == p2->qnameId.uriId;
		case EVENT_CH:
			return p1->typeId == p2->typeId;
		default:
			return TRUE;
	}
}

/** The layout of a DynArray container (see dynamicArray.c) */
struct dynContainer
{
	DynArray dynArray;
	void* base;
	Index count;
};

/** A set of rules of the grammar being normalised, as a bit set over its original rules */
struct ruleSet
{
	unsigned char* bits;
};

struct mergedProduction
{
	ProtoProduction prod;
	unsigned char* targets; /* bit set over the original rules; unused for EE */
};

#define SET_BYTES(n) (((n) + 7) / 8)
#define SET_HAS(set, i) (((set)[(i) / 8] >> ((i) % 8)) & 1)
#define SET_ADD(set, i) ((set)[(i) / 8] |= (unsigned char) (1 << ((i) % 8)))

static Index setCount(const unsigned char* set, Index n, Index* first)
{
	Index i, c = 0;

	for(i = 0; i < n; i++)
	{
		if(SET_HAS(set, i))
		{
			if(c == 0)
				*first = i;
			c++;
		}
	}
	return c;
}

static errorCode reachableRules(ProtoGrammar* pg, unsigned char* reached, Index* order)
{
	Index head = 0, tail = 0, i;

	memset(reached, 0, SET_BYTES(pg->count));
	SET_ADD(reached, 0);
	order[tail++] = 0;
	if(pg->contentIndex < pg->count && !SET_HAS(reached, pg->contentIndex))
	{
		SET_ADD(reached, pg->contentIndex);
		order[tail++] = pg->contentIndex;
	}

	while(head < tail)
	{
		Index r = order[head++];
		for(i = 0; i < pg->rule[r].count; i++)
		{
			Index nt;
			if(GET_PROD_EXI_EVENT(pg->rule[r].prod[i].content) == EVENT_EE)
				continue;
			nt = GET_PROD_NON_TERM(pg->rule[r].prod[i].content);
			if(nt < pg->count && !SET_HAS(reached, nt))
			{
				SET_ADD(reached, nt);
				order[tail++] = nt;
			}
		}
	}
	return EXIP_OK;
}

errorCode eliminateDuplicateTerminals(ProtoGrammar* pg)
{
	errorCode tmp_err_code = EXIP_OK;
	Index n = pg->count;
	Index setBytes = SET_BYTES(n);
	Index r, i, j;
	exip_bool found = FALSE;
	ProtoProduction** orig = NULL;
	Index* origCount = NULL;
	struct ruleSet* unions = NULL; /* unions[k]: the set of rule n + k */
	Index unionCount = 0, unionCap = 0;
	struct mergedProduction* merged = NULL;
	Index mergedCap = 0;

	/* Anything to do? */
	for(r = 0; r < n && !found; r++)
	{
		for(i = 0; i < pg->rule[r].count && !found; i++)
		{
			for(j = i + 1; j < pg->rule[r].count; j++)
			{
				if(sameTerminal(&pg->rule[r].prod[i], &pg->rule[r].prod[j]) &&
						GET_PROD_EXI_EVENT(pg->rule[r].prod[i].content) != EVENT_EE &&
						GET_PROD_NON_TERM(pg->rule[r].prod[i].content) != GET_PROD_NON_TERM(pg->rule[r].prod[j].content))
				{
					found = TRUE;
					break;
				}
			}
		}
	}
	if(!found)
		return EXIP_OK;

	/* The original productions: every state, original or union, is built from them */
	orig = (ProtoProduction**) EXIP_MALLOC(sizeof(ProtoProduction*) * n);
	origCount = (Index*) EXIP_MALLOC(sizeof(Index) * n);
	if(orig == NULL || origCount == NULL)
	{
		tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
		goto done;
	}
	for(r = 0; r < n; r++)
		orig[r] = NULL;
	for(r = 0; r < n; r++)
	{
		origCount[r] = pg->rule[r].count;
		orig[r] = (ProtoProduction*) EXIP_MALLOC(sizeof(ProtoProduction) * (origCount[r] + 1));
		if(orig[r] == NULL)
		{
			tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
			goto done;
		}
		memcpy(orig[r], pg->rule[r].prod, sizeof(ProtoProduction) * origCount[r]);
	}

	/* Subset construction: rule s (s < n is the set {s}) gets the productions of all the
	 * rules in its set; productions with the same terminal become one, to the rule for
	 * the union of their targets, created once per set. */
	for(r = 0; r < pg->count; r++)
	{
		Index mergedCount = 0;
		Index m;

		for(m = 0; m < n; m++)
		{
			if(r < n ? (m != r) : !SET_HAS(unions[r - n].bits, m))
				continue;

			for(i = 0; i < origCount[m]; i++)
			{
				ProtoProduction* p = &orig[m][i];
				Index k;

				for(k = 0; k < mergedCount; k++)
				{
					if(sameTerminal(&merged[k].prod, p))
						break;
				}

				if(k == mergedCount)
				{
					if(mergedCount == mergedCap)
					{
						struct mergedProduction* tmp;
						Index c;
						mergedCap = mergedCap * 2 + 8;
						tmp = (struct mergedProduction*) EXIP_REALLOC(merged, sizeof(struct mergedProduction) * mergedCap);
						if(tmp == NULL)
						{
							tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
							goto done;
						}
						merged = tmp;
						for(c = mergedCount; c < mergedCap; c++)
							merged[c].targets = NULL;
					}
					if(merged[k].targets == NULL)
					{
						merged[k].targets = (unsigned char*) EXIP_MALLOC(setBytes);
						if(merged[k].targets == NULL)
						{
							tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
							goto done;
						}
					}
					memset(merged[k].targets, 0, setBytes);
					merged[k].prod = *p;
					mergedCount++;
				}
				else if(p->order < merged[k].prod.order)
					merged[k].prod.order = p->order; /* the earliest particle */

				if(GET_PROD_EXI_EVENT(p->content) != EVENT_EE)
					SET_ADD(merged[k].targets, GET_PROD_NON_TERM(p->content));
			}
		}

		/* Resolve the targets and rewrite the rule */
		pg->rule[r].count = 0;
		for(i = 0; i < mergedCount; i++)
		{
			ProtoProduction* p = &merged[i].prod;
			Index first = 0;

			if(GET_PROD_EXI_EVENT(p->content) != EVENT_EE)
			{
				Index c = setCount(merged[i].targets, n, &first);
				Index target = first;

				if(c > 1)
				{
					Index u;
					for(u = 0; u < unionCount; u++)
					{
						if(memcmp(unions[u].bits, merged[i].targets, setBytes) == 0)
							break;
					}
					if(u == unionCount)
					{
						ProtoRuleEntry* newRule;
						if(unionCount == unionCap)
						{
							struct ruleSet* tmp;
							unionCap = unionCap * 2 + 4;
							tmp = (struct ruleSet*) EXIP_REALLOC(unions, sizeof(struct ruleSet) * unionCap);
							if(tmp == NULL)
							{
								tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
								goto done;
							}
							unions = tmp;
						}
						unions[u].bits = (unsigned char*) EXIP_MALLOC(setBytes);
						if(unions[u].bits == NULL)
						{
							tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
							goto done;
						}
						memcpy(unions[u].bits, merged[i].targets, setBytes);
						unionCount++;
						tmp_err_code = addProtoRule(pg, 5, &newRule);
						if(tmp_err_code != EXIP_OK)
							goto done;
					}
					target = n + u;
				}
				SET_PROD_NON_TERM(p->content, target);
			}

			tmp_err_code = addOrderedProduction(&pg->rule[r], GET_PROD_EXI_EVENT(p->content), p->typeId, p->qnameId,
					GET_PROD_NON_TERM(p->content), p->order);
			if(tmp_err_code != EXIP_OK)
				goto done;
		}
	}

	/* Remove the rules no longer reachable (8.5.4.2.2 leaves them; Appendix H.2) */
	{
		unsigned char* reached = (unsigned char*) EXIP_MALLOC(SET_BYTES(pg->count));
		Index* queue = (Index*) EXIP_MALLOC(sizeof(Index) * pg->count);
		Index* newIndex = (Index*) EXIP_MALLOC(sizeof(Index) * pg->count);
		Index next = 0;

		if(reached == NULL || queue == NULL || newIndex == NULL)
		{
			EXIP_MFREE(reached);
			EXIP_MFREE(queue);
			EXIP_MFREE(newIndex);
			tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
			goto done;
		}

		reachableRules(pg, reached, queue);
		for(r = 0; r < pg->count; r++)
			newIndex[r] = SET_HAS(reached, r) ? next++ : INDEX_MAX;

		for(r = 0; r < pg->count; r++)
		{
			if(newIndex[r] == INDEX_MAX)
				continue;
			for(i = 0; i < pg->rule[r].count; i++)
			{
				if(GET_PROD_EXI_EVENT(pg->rule[r].prod[i].content) != EVENT_EE)
					SET_PROD_NON_TERM(pg->rule[r].prod[i].content, newIndex[GET_PROD_NON_TERM(pg->rule[r].prod[i].content)]);
			}
		}

		for(r = 0; r < pg->count; r++)
		{
			if(newIndex[r] == INDEX_MAX)
				destroyDynArray(&pg->rule[r].dynArray);
			else if(newIndex[r] != r)
				pg->rule[newIndex[r]] = pg->rule[r];
		}
		if(pg->contentIndex < pg->count && newIndex[pg->contentIndex] != INDEX_MAX)
			pg->contentIndex = (unsigned int) newIndex[pg->contentIndex];
		/* The count is kept by the rule DynArray, after its base pointer (dynamicArray.c) */
		((struct dynContainer*) pg)->count = next;

		EXIP_MFREE(reached);
		EXIP_MFREE(queue);
		EXIP_MFREE(newIndex);
	}

done:
	if(orig != NULL)
	{
		for(r = 0; r < n; r++)
			EXIP_MFREE(orig[r]);
	}
	EXIP_MFREE(orig);
	EXIP_MFREE(origCount);
	if(unions != NULL)
	{
		for(i = 0; i < unionCount; i++)
			EXIP_MFREE(unions[i].bits);
		EXIP_MFREE(unions);
	}
	if(merged != NULL)
	{
		for(i = 0; i < mergedCap; i++)
			EXIP_MFREE(merged[i].targets);
		EXIP_MFREE(merged);
	}
	return tmp_err_code;
}
