/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file genUtils.h
 * @brief Definition and utility functions for generating Schema-informed Grammar definitions
 * @date Nov 23, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: genUtils.h 332 2014-05-05 18:22:55Z kjussakov $
 */

#ifndef GENUTILS_H_
#define GENUTILS_H_

#include "errorHandle.h"
#include "procTypes.h"
#include "dynamicArray.h"
#include "sTables.h"
#include "protoGrammars.h"
#include "treeTableSchema.h"

/**
 * @brief Grammar Concatenation Operator - extends the rules and productions in the left ProtoGrammar
 * The grammar concatenation operator ⊕ is a binary, associative
 * operator that creates a new grammar from its left and right
 * grammar operands. The new grammar accepts any set of symbols
 * accepted by its left operand followed by any set of symbols
 * accepted by its right operand.
 * As opposed to the operator in the specification, the implementation here automatically
 * normalize the resulting grammar
 *
 * @param[in, out] left left operand - grammar
 * @param[in] right right operand - grammar
 * @return Error handling code
 */
errorCode concatenateGrammars(ProtoGrammar* left, ProtoGrammar* right);

/**
 * @brief Creates Simple Type Grammar from XML Schema simple type definition
 *
 * @param[in] typeId index of the type in the simple type table
 * @param[in, out] simpleGrammar The simple proto-grammar
 * @return Error handling code
 */
errorCode createSimpleTypeGrammar(Index typeId, ProtoGrammar* simpleGrammar);

/**
 * @brief Creates Complex Type Proto-Grammar from XML Schema complex type definition
 * Sort the attribute use grammars first by qname local-name, then by qname uri.
 * If {content type} is type definition T-j , generate a grammar Content-i as grammar Type-j
 * Then create a copy H-i  of each attribute use grammar
 * Result: Type-i = H-0 ⊕ H-1 ⊕ … ⊕ H-n−1 ⊕ Content-i
 *
 * @param[in] attrUseArray array of attribute uses grammars included in this complex type
 *            It should be lexicographically sorted
 * @param[in] contentTypeGrammar the proto-grammar of the complex type content: either Simple Type Grammar,
 * or Particle grammar or empty
 * @param[in] isMixedContent if the complex types has mixed content type (TRUE) or not (FALSE)
 * @param[in, out] complexGrammar the resulted proto-grammar
 * @return Error handling code
 */
errorCode createComplexTypeGrammar(ProtoGrammarArray* attrUseArray, ProtoGrammar* contentTypeGrammar,
								boolean isMixedContent, ProtoGrammar* complexGrammar);

/**
 * @brief Creates Complex Ur-Type Grammar from XML Schema complex ur-type
 *
 * @param[out] result the resulted proto-grammar
 * @return Error handling code
 */
errorCode createComplexUrTypeGrammar(ProtoGrammar* result);

/**
 * @brief Creates Attribute Use Grammar from XML Schema Attribute Use
 *
 * @param[in] required 0 - false; otherwise true
 * @param[in] typeId the id of the attribute type in the simpleTypeTable
 * @param[out] attrGrammar the resulted proto-grammar
 * @param[in] qnameID uri/ln indices in the unsorted string tables
 * @return Error handling code
 */
errorCode createAttributeUseGrammar(boolean required, Index typeId,
									ProtoGrammar* attrGrammar, QNameID qnameID);

/**
 * @brief Creates Particle Proto-Grammar from XML Schema particle
 *
 * @param[in] minOccurs particle's {min Occurs}
 * @param[in] maxOccurs particle's {max Occurs}. If less than 0 then the value is {unbounded}
 * @param[in] termGrammar the grammar created from the particle's term: Element Term, Wildcard Term or Model Group Term
 * @param[out] particleGrammar the resulted proto-grammar
 * @return Error handling code
 */
errorCode createParticleGrammar(int minOccurs, int maxOccurs, ProtoGrammar* termGrammar, ProtoGrammar* particleGrammar);

/**
 * @brief Creates Element Term Proto-Grammar from Particle term that is XML Schema element declaration
 *
 * @param[out] elemGrammar the resulted proto-grammar
 * @param[in] qnameGrArr array of uri/ln indices of the element in the string tables and the associated grammar indices
 * to be used for processing this SE(qnameID) element
 * @param[in] count
 * @return Error handling code
 */
errorCode createElementTermGrammar(ProtoGrammar* elemGrammar, QNameIDGrIndx* qnameGrArr, Index count);

/**
 * @brief Creates Wildcard Term Proto-Grammar from Particle term that is XML Schema wildcard
 *
 * @param[in] wildcardArray array of strings. Possible values: "any" or a set of namespace names and "absent"
 * or 'not' and a namespace name or "not" and "absent"
 * @param[in] wildcardArraySize the size of the wildcard array
 * @param[in] uriT the URI string table
 * @param[out] wildcardGrammar the resulted proto-grammar
 * @return Error handling code
 */
errorCode createWildcardTermGrammar(String* wildcardArray, Index wildcardArraySize, UriTable* uriT, ProtoGrammar* wildcardGrammar);

/**
 * @brief Creates Sequence Model Group Proto-Grammar from Particle term that is XML Schema Model Group with {compositor} equal to "sequence"
 *
 * @param[in] grArray array of proto ParticleTerm grammars included in the sequence Model Group
 * @param[in] arrSize the size of the array of proto ParticleTerm grammars
 * @param[out] sequenceGrammar the resulted proto-grammar
 * @return Error handling code
 */
errorCode createSequenceModelGroupsGrammar(ProtoGrammar** grArray, unsigned int arrSize, ProtoGrammar* sequenceGrammar);

/**
 * @brief Creates Choice Model Group Proto-Grammar from Particle term that is XML Schema Model Group with {compositor} equal to "choice"
 *
 * @param[in, out] pgArray array of ParticleTerm grammars included in the Choice Model Group
 * @param[out] modGrpGrammar the resulted proto-grammar
 * @return Error handling code
 */
errorCode createChoiceModelGroupsGrammar(ProtoGrammarArray* pgArray, ProtoGrammar* modGrpGrammar);

/**
 * @brief Creates All Model Group Proto-Grammar from Particle term that is XML Schema Model Group with {compositor} equal to "all"
 *
 * @param[in] pTermArray an array of ParticleTerm grammars included in the All Model Group
 * @param[in] pTermArraySize the size of the ParticleTerm grammar array
 * @param[out] modGrpGrammar the resulted proto-grammar
 * @return Error handling code
 */
errorCode createAllModelGroupsGrammar(ProtoGrammar* pTermArray, unsigned int pTermArraySize, ProtoGrammar* modGrpGrammar);

/**
 * @brief Compare lexicographically two qnames: first by qname local-name, then by qname uri
 * NOTE: Relies on the fact that the sting tables are sorted beforehand!
 *
 * @param[in] qnameID1 qnameId of the first qname
 * @param[in] qnameID2 qnameId of the second qname
 * @param[in] uriTbl string table reference
 * @return 0 when the qnames are equal; negative int when qnameID1<qnameID2; positive when qnameID1>qnameID2
 */
int compareQNameID(const void* qnameID1, const void* qnameID2, UriTable* uriTbl);

/**
 * @brief Adds a EE production to a proto grammar rule
 *
 * @param[in] rule proto grammar rule
 * @return Error handling code
 */
errorCode addEEProduction(ProtoRuleEntry* rule);

#endif /* GENUTILS_H_ */
