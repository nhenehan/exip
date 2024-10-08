/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file ASCII_stringManipulate.c
 * @brief String manipulation functions used for UCS <-> ASCII transformations
 *
 * @date Sep 3, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: ASCII_stringManipulate.c 357 2014-12-05 09:54:22Z kjussakov $
 */

#include "stringManipulate.h"
#include "memManagement.h"

#define PARSING_STRING_MAX_LENGTH 100

errorCode allocateStringMemory(CharType** str, Index UCSchars)
{
	*str = EXIP_MALLOC(sizeof(CharType)*UCSchars);
	if((*str) == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;
	return EXIP_OK;
}

errorCode allocateStringMemoryManaged(CharType** str, Index UCSchars, AllocList* memList)
{
	(*str) = (CharType*) memManagedAllocate(memList, sizeof(CharType)*UCSchars);
	if((*str) == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;
	return EXIP_OK;
}

/**
 * Simple translation working only for ASCII characters
 */
errorCode writeCharToString(String* str, uint32_t code_point, Index* writerPosition)
{
	if(*writerPosition >= str->length)
		return EXIP_OUT_OF_BOUND_BUFFER;
	str->str[*writerPosition] = (CharType) code_point;
	*writerPosition += 1;
	return EXIP_OK;
}

void getEmptyString(String* emptyStr)
{
	emptyStr->length = 0;
	emptyStr->str = NULL;
}

boolean isStringEmpty(const String* str)
{
	if(str == NULL || str->length == 0)
		return 1;
	return 0;
}

errorCode asciiToString(const char* inStr, String* outStr, AllocList* memList, boolean clone)
{
	outStr->length = strlen(inStr);
	if(outStr->length > 0)  // If == 0 -> empty string
	{
		if(clone == FALSE)
		{
			outStr->str = (CharType*) inStr;
			return EXIP_OK;
		}
		else
		{
			outStr->str = (CharType*) memManagedAllocate(memList, sizeof(CharType)*(outStr->length));
			if(outStr->str == NULL)
				return EXIP_MEMORY_ALLOCATION_ERROR;
			memcpy(outStr->str, inStr, outStr->length);
			return EXIP_OK;
		}
	}
	else
		outStr->str = NULL;
	return EXIP_OK;
}

boolean stringEqual(const String str1, const String str2)
{
	if(str1.length != str2.length)
		return 0;
	else if(str1.length == 0)
		return 1;
	else // The strings have the same length
	{
		Index i;
		for(i = 0; i < str1.length; i++)
		{
			if(str1.str[i] != str2.str[i])
				return 0;
		}
		return 1;
	}
}

boolean stringEqualToAscii(const String str1, const char* str2)
{
	if(str1.length != strlen(str2))
		return 0;
	else // The strings have the same length
	{
		Index i;
		for(i = 0; i < str1.length; i++)
		{
			if(str1.str[i] != str2[i])
				return 0;
		}
		return 1;
	}
}

int stringCompare(const String str1, const String str2)
{
	/* Check for NULL string pointers */
	if(str1.str == NULL)
	{
		if(str2.str == NULL)
			return 0;
		return -1;
	}
	else if(str2.str == NULL)
		return 1;
	else // None of the strings is NULL
	{
		int diff;
		Index i;
		for(i = 0; i < str1.length && i < str2.length; i++)
		{
			diff = str1.str[i] - str2.str[i];
			if(diff)
				return diff; // There is a difference in the characters at index i
		}
		/* Up to index i the strings have the same characters and might differ only in length*/
		return str1.length - str2.length;
	}
}

uint32_t readCharFromString(const String* str, Index* readerPosition)
{
	assert(*readerPosition < str->length);
	*readerPosition += 1;
	return (uint32_t) str->str[*readerPosition - 1];
}

errorCode cloneString(const String* src, String* newStr)
{
	if(newStr == NULL)
		return EXIP_NULL_POINTER_REF;
	newStr->str = EXIP_MALLOC(sizeof(CharType)*src->length);
	if(newStr->str == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;
	newStr->length = src->length;
	memcpy(newStr->str, src->str, src->length);
	return EXIP_OK;
}

errorCode cloneStringManaged(const String* src, String* newStr, AllocList* memList)
{
	if(newStr == NULL)
		return EXIP_NULL_POINTER_REF;
	newStr->str = memManagedAllocate(memList, sizeof(CharType)*src->length);
	if(newStr->str == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;
	newStr->length = src->length;
	memcpy(newStr->str, src->str, src->length);
	return EXIP_OK;
}

Index getIndexOfChar(const String* src, CharType sCh)
{
	Index i;

	for(i = 0; i < src->length; i++)
	{
		if(src->str[i] == sCh)
			return i;
	}
	return INDEX_MAX;
}

errorCode stringToInteger(const String* src, int* number)
{
	char buff[PARSING_STRING_MAX_LENGTH];
	long result;
	char *endPointer;

	if(src->length == 0 || src->length >= PARSING_STRING_MAX_LENGTH)
		return EXIP_INVALID_STRING_OPERATION;

	memcpy(buff, src->str, src->length);
	buff[src->length] = '\0';

	result = strtol(buff, &endPointer, 10);

	if(result == LONG_MAX || result == LONG_MIN || *src->str == *endPointer)
		return EXIP_INVALID_STRING_OPERATION;

	if(result >= INT_MAX || result <= INT_MIN)
		return EXIP_OUT_OF_BOUND_BUFFER;

	*number = (int) result;

	return EXIP_OK;
}

errorCode stringToInt64(const String* src, int64_t* number)
{
	char buff[PARSING_STRING_MAX_LENGTH];
	long long result;
	char *endPointer;

	if(src->length == 0 || src->length >= PARSING_STRING_MAX_LENGTH)
		return EXIP_INVALID_STRING_OPERATION;

	memcpy(buff, src->str, src->length);
	buff[src->length] = '\0';

	result = EXIP_STRTOLL(buff, &endPointer, 10);

	if(result == LLONG_MAX || result == LLONG_MIN || *src->str == *endPointer)
		return EXIP_INVALID_STRING_OPERATION;

	if(result >= LLONG_MAX || result <= LLONG_MIN)
		return EXIP_OUT_OF_BOUND_BUFFER;

	*number = (int64_t) result;

	return EXIP_OK;
}

#if EXIP_IMPLICIT_DATA_TYPE_CONVERSION

errorCode integerToString(Integer number, String* outStr)
{
	EXIP_UNUSED(number);
	EXIP_UNUSED(outStr);
	return EXIP_NOT_IMPLEMENTED_YET;
}

errorCode booleanToString(boolean b, String* outStr)
{
	EXIP_UNUSED(b);
	EXIP_UNUSED(outStr);
	return EXIP_NOT_IMPLEMENTED_YET;
}

errorCode floatToString(Float f, String* outStr)
{
	EXIP_UNUSED(f);
	EXIP_UNUSED(outStr);
	return EXIP_NOT_IMPLEMENTED_YET;
}

errorCode decimalToString(Decimal d, String* outStr)
{
	EXIP_UNUSED(d);
	EXIP_UNUSED(outStr);
	return EXIP_NOT_IMPLEMENTED_YET;
}

errorCode dateTimeToString(EXIPDateTime dt, String* outStr)
{
	EXIP_UNUSED(dt);
	EXIP_UNUSED(outStr);
	return EXIP_NOT_IMPLEMENTED_YET;
}

#endif /* EXIP_IMPLICIT_DATA_TYPE_CONVERSION */

#if EXIP_DEBUG == ON

void printString(const String* inStr)
{
	if(inStr->length == 0)
		return;

	DEBUG_OUTPUT(("%.*s", (int) inStr->length, inStr->str));
}

#endif /* EXIP_DEBUG */
