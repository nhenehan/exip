/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file grammars.h
 * @brief Types and functions describing EXI grammars
 * @date Sep 7, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: grammars.h 335 2014-05-05 18:23:26Z kjussakov $
 */

#ifndef GRAMMARS_H_
#define GRAMMARS_H_

#include "errorHandle.h"
#include "procTypes.h"
#include "contentHandler.h"

// Defines the initial dimension of the dynamic array - production
#define DEFAULT_PROD_ARRAY_DIM 10

/**
 * Get global element EXIGrammar from the SchemaGrammarTable by given QNameID.
 * Returns NULL if the grammar does not exists in the SchemaGrammarTable
 * (i.e. the index of the grammar in the string table is INDEX_MAX)
 */
#define GET_ELEM_GRAMMAR_QNAMEID(schema, qnameID) GET_LN_URI_QNAME((schema)->uriTable, qnameID).elemGrammar == INDEX_MAX?NULL:&((schema)->grammarTable.grammar[GET_LN_URI_QNAME((schema)->uriTable, qnameID).elemGrammar])

/**
 * Get global type EXIGrammar from the SchemaGrammarTable by given QNameID.
 * Returns NULL if the grammar does not exists in the SchemaGrammarTable
 * (i.e. the index of the grammar in the string table is INDEX_MAX)
 */
#define GET_TYPE_GRAMMAR_QNAMEID(schema, qnameID) GET_LN_URI_QNAME((schema)->uriTable, qnameID).typeGrammar == INDEX_MAX?NULL:&((schema)->grammarTable.grammar[GET_LN_URI_QNAME((schema)->uriTable, qnameID).typeGrammar])

/**
 * @brief Push a grammar on top of the Grammar Stack
 * 
 * @param[in, out] gStack the Grammar Stack
 * @param[in] currQNameID the currently proccessed element QNameID that is having this grammar
 * @param[in] grammar a EXI grammar
 * @return Error handling code
 */
errorCode pushGrammar(EXIGrammarStack** gStack, QNameID currQNameID, EXIGrammar* grammar);

/**
 * @brief Pop a grammar off the top of the Grammar Stack
 * 
 * @param[in, out] gStack the Grammar stack
 */
void popGrammar(EXIGrammarStack** gStack);

/**
 * @brief Creates an instance of the EXI Built-in Document Grammar or Schema-Informed Document Grammar
 * 
 * If elQnameArr is NULL then it creates EXI Built-in Document Grammar, otherwise
 * it creates Schema-Informed Document Grammar with global elements stored (sorted) in elQnameArr
 *
 * @param[in, out] schema the schema describing the document
 * @param[in] elQnameArr array of QNameIds of global element definitions if any; NULL otherwise (schema-less mode)
 * @param[in] qnameCount the number of global element definitions if any; 0 otherwise
 * @return Error handling code
 */
errorCode createDocGrammar(EXIPSchema* schema, QNameID* elQnameArr, Index qnameCount);

/**
 * @brief Creates an instance of the EXI Built-in Fragment Grammar or Schema-Informed Fragment Grammar
 * 
 * If elQnameArr is NULL then it creates EXI Built-in Fragment Grammar, otherwise
 * it creates Schema-Informed Fragment Grammar
 *
 * @param[in, out] schema the schema describing the document
 * @param[in] elQnameArr array of QNameIds of element definitions if any; NULL otherwise (schema-less mode)
 * @param[in] qnameCount the number of global element definitions if any; 0 otherwise
 * @return Error handling code
 */
errorCode createFragmentGrammar(EXIPSchema* schema, QNameID* elQnameArr, Index qnameCount);

#if BUILD_IN_GRAMMARS_USE
	/**
	 * @brief Creates an instance of EXI Built-in Element Grammar
	 *
	 * @param[in] elementGrammar empty grammar container
	 * @param[in, out] strm EXI stream for which the allocation is made
	 * @return Error handling code
	 */
	errorCode createBuiltInElementGrammar(EXIGrammar* elementGrammar, EXIStream* strm);

	/**
	 * @brief Inserts a Production to a Grammar Rule (with LeftHandSide) with an event code 0
	 * Note! It increments the first part of the event code of each production
	 * in the current grammar with the non-terminal LeftHandSide on the left-hand side
	 * Used only for Built-in Document Grammar and Built-in Fragment Grammar
	 * @param[in, out] rule a Grammar Rule
	 * @param[in] evnt event type
	 * @param[in] nonTermID unique identifier of right-hand side Non-terminal
	 * @param[in] qname qname identifier of the Event Type corresponding to the inserted production
	 * @param[in] hasSecondLevelProd FALSE if there are no second level productions (only possible in Fragment Grammar);
	 * otherwise TRUE
	 * @return Error handling code
	 */
	errorCode insertZeroProduction(DynGrammarRule* rule, EventType evnt, SmallIndex nonTermID, QNameID* qname, boolean hasSecondLevelProd);
#endif

/**
 * @brief For a given grammar and a rule from it, returns the number of bits needed to encode a production from that rule
 * @param[in] strm EXI stream
 * @param[in] prodCount number of productions in the current grammar rule
 * @param[in] currentRuleIndx the index of the concrete grammar rule
 * @return number of bits needed to encode a production
 */
unsigned int getBitsFirstPartCode(EXIStream* strm, Index prodCount, SmallIndex currentRuleIndx);

#if EXIP_DEBUG == ON
/**
 * @brief Prints a grammar rule
 * Note! This is only for debugging purposes!
 * @param[in] nonTermID The left hand side nonTerminal of the Rule
 * @param[in] rule a Grammar Rule to be printed
 * @param[in] schema for string tables
 * @return Error handling code
 */
errorCode printGrammarRule(SmallIndex nonTermID, GrammarRule* rule, EXIPSchema *schema);

#endif // EXIP_DEBUG

#endif /* GRAMMARS_H_ */
