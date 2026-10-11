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

/* Strings hold UTF-8; String.length is a byte count */

Index getUtf8Length(uint32_t code_point)
{
	if(code_point < 0x80)
		return 1;
	else if(code_point < 0x800)
		return 2;
	else if(code_point < 0x10000)
		return 3;
	else
		return 4;
}

boolean isUnicodeScalarValue(uint32_t code_point)
{
	return code_point <= 0x10FFFF && (code_point < 0xD800 || code_point > 0xDFFF);
}

errorCode writeCharToString(String* str, uint32_t code_point, Index* writerPosition)
{
	unsigned char* out;
	Index n;

	if(!isUnicodeScalarValue(code_point))
		return EXIP_INVALID_STRING_OPERATION;

	n = getUtf8Length(code_point);
	if(*writerPosition + n > str->length)
		return EXIP_OUT_OF_BOUND_BUFFER;

	out = (unsigned char*) str->str + *writerPosition;
	switch(n)
	{
		case 1:
			out[0] = (unsigned char) code_point;
			break;
		case 2:
			out[0] = (unsigned char) (0xC0 | (code_point >> 6));
			out[1] = (unsigned char) (0x80 | (code_point & 0x3F));
			break;
		case 3:
			out[0] = (unsigned char) (0xE0 | (code_point >> 12));
			out[1] = (unsigned char) (0x80 | ((code_point >> 6) & 0x3F));
			out[2] = (unsigned char) (0x80 | (code_point & 0x3F));
			break;
		default:
			out[0] = (unsigned char) (0xF0 | (code_point >> 18));
			out[1] = (unsigned char) (0x80 | ((code_point >> 12) & 0x3F));
			out[2] = (unsigned char) (0x80 | ((code_point >> 6) & 0x3F));
			out[3] = (unsigned char) (0x80 | (code_point & 0x3F));
			break;
	}
	*writerPosition += n;
	return EXIP_OK;
}

/**
 * Decodes the UTF-8 sequence at *position. Rejects truncated sequences, stray
 * continuation bytes, overlong forms, surrogates and values above U+10FFFF.
 */
static errorCode decodeUtf8(const String* str, Index* position, uint32_t* code_point)
{
	const unsigned char* s = (const unsigned char*) str->str + *position;
	Index left = str->length - *position;
	uint32_t cp;
	Index n, i;

	if(left == 0)
		return EXIP_INVALID_STRING_OPERATION;

	if(s[0] < 0x80)
	{
		*code_point = s[0];
		*position += 1;
		return EXIP_OK;
	}
	else if((s[0] & 0xE0) == 0xC0)
	{
		n = 2;
		cp = s[0] & 0x1F;
	}
	else if((s[0] & 0xF0) == 0xE0)
	{
		n = 3;
		cp = s[0] & 0x0F;
	}
	else if((s[0] & 0xF8) == 0xF0)
	{
		n = 4;
		cp = s[0] & 0x07;
	}
	else
		return EXIP_INVALID_STRING_OPERATION;

	if(left < n)
		return EXIP_INVALID_STRING_OPERATION;

	for(i = 1; i < n; i++)
	{
		if((s[i] & 0xC0) != 0x80)
			return EXIP_INVALID_STRING_OPERATION;
		cp = (cp << 6) | (s[i] & 0x3F);
	}

	if(getUtf8Length(cp) != n || !isUnicodeScalarValue(cp))
		return EXIP_INVALID_STRING_OPERATION;

	*code_point = cp;
	*position += n;
	return EXIP_OK;
}

errorCode getCharCount(const String* str, Index* charCount)
{
	Index position = 0;
	uint32_t cp;
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;

	*charCount = 0;
	while(position < str->length)
	{
		TRY(decodeUtf8(str, &position, &cp));
		*charCount += 1;
	}
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
			// unsigned: for UTF-8, byte order is code-point order (spec 1.2)
			diff = (int) ((unsigned char) str1.str[i]) - (int) ((unsigned char) str2.str[i]);
			if(diff)
				return diff; // There is a difference in the characters at index i
		}
		/* Up to index i the strings have the same characters and might differ only in length*/
		return str1.length - str2.length;
	}
}

uint32_t readCharFromString(const String* str, Index* readerPosition)
{
	uint32_t cp;

	assert(*readerPosition < str->length);
	if(decodeUtf8(str, readerPosition, &cp) != EXIP_OK)
	{
		// Only reached when the caller skipped getCharCount(): consume one byte
		*readerPosition += 1;
		return 0xFFFD;
	}
	return cp;
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
