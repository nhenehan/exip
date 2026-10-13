/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file streamDecode.c
 * @brief Implementing the interface to a higher-level EXI stream decoder - decode basic EXI types
 *
 * @date Aug 18, 2010
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: streamDecode.c 358 2014-12-11 22:43:03Z kjussakov $
 */

#include "streamDecode.h"
#include "streamRead.h"
#include "stringManipulate.h"
#include "memManagement.h"
#include "ioUtil.h"

errorCode decodeNBitUnsignedInteger(EXIStream* strm, unsigned char n, unsigned long* int_val)
{
	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (%d-bits uint)", n));
	if(n == 0)
	{
		*int_val = 0;
		return EXIP_OK;
	}

	// Compression implies the pre-compression (byte-aligned) representation (EXI 1.0 section 9)
	if(GET_ALIGNMENT(strm->header.opts.enumOpt) == BIT_PACKED && !WITH_COMPRESSION(strm->header.opts.enumOpt))
	{
		return readBits(strm, n, int_val);
	}
	else
	{
		unsigned int byte_number = ((unsigned int) n) / 8 + (n % 8 != 0);
		unsigned long tmp_byte_buf = 0;
		unsigned int i = 0;

		if(strm->buffer.bufContent < strm->context.bufferIndx + byte_number)
		{
			// The buffer end is reached: there are fewer than byte_number left unparsed
			errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;

			TRY(readEXIChunkForParsing(strm, byte_number));
		}

		*int_val = 0;
		for(i = 0; i < byte_number*8; i += 8)
		{
			// buf is char*: read bytes unsigned so values >= 0x80 do not sign-extend
			tmp_byte_buf = ((unsigned long) (unsigned char) strm->buffer.buf[strm->context.bufferIndx]) << i;
			*int_val = *int_val | tmp_byte_buf;
			strm->context.bufferIndx++;
		}
	}
	return EXIP_OK;
}

errorCode decodeBoolean(EXIStream* strm, exip_bool* bool_val)
{
	//TODO:  when pattern facets are available in the schema datatype - handle it differently
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	unsigned long lBoolVal;
	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (bool)"));
	TRY(decodeNBitUnsignedInteger(strm, 1, &lBoolVal));
	*bool_val = (exip_bool) lBoolVal;
	return EXIP_OK;
}

errorCode decodeUnsignedInteger(EXIStream* strm, UnsignedInteger* int_val)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	unsigned int i = 0;
	unsigned long tmp_byte_buf = 0;
	*int_val = 0;

	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (uint)"));
	do
	{
		TRY(readBits(strm, 8, &tmp_byte_buf));

		*int_val += ((UnsignedInteger) (tmp_byte_buf & 0x7F)) << i;
		i += 7;
	}
	while(tmp_byte_buf & 0x80);

	return EXIP_OK;
}

errorCode decodeString(EXIStream* strm, String* string_val)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	UnsignedInteger string_length = 0;
	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (string)"));
	TRY(decodeUnsignedInteger(strm, &string_length));

	return decodeStringOnly(strm, (Index) string_length, string_val, &strm->memList);
}

errorCode decodeStringOnly(EXIStream* strm, Index charCount, String* string_val, AllocList* memList)
{
	// Assume no Restricted Character Set is defined
	//TODO: Handle the case when Restricted Character Set is defined
	errorCode tmp_err_code = EXIP_OK;
	Index i;
	Index used = 0;          // bytes written
	Index capacity = charCount;
	CharType* buf = NULL;
	exip_bool onHeap;          // buf is EXIP_MALLOC'ed (not from memList)
	UnsignedInteger code_point = 0;

	string_val->str = NULL;
	string_val->length = 0;
	if(charCount == 0)
		return EXIP_OK;

	if(memList != NULL)
	{
		buf = (CharType*) memManagedAllocate(memList, capacity);
		onHeap = FALSE;
	}
	else
	{
		buf = (CharType*) EXIP_MALLOC(capacity);
		onHeap = TRUE;
	}
	if(buf == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;

	for(i = 0; i < charCount; i++)
	{
		String window;
		Index n;

		tmp_err_code = decodeUnsignedInteger(strm, &code_point);
		if(tmp_err_code != EXIP_OK)
			break;
		if(code_point > 0x10FFFF || !isUnicodeScalarValue((uint32_t) code_point))
		{
			tmp_err_code = EXIP_INVALID_EXI_INPUT;
			break;
		}

		n = getUtf8Length((uint32_t) code_point);
		if(used + n > capacity)
		{
			// Grow on the heap: at least double, and room for this character plus one
			// byte for each one still to come; never more than 4 bytes per character
			Index needed = used + n + (charCount - i - 1);
			Index newCapacity = capacity * 2 > needed ? capacity * 2 : needed;
			CharType* newBuf;

			if(newCapacity > charCount * 4)
				newCapacity = charCount * 4;
			newBuf = (CharType*) EXIP_MALLOC(newCapacity);
			if(newBuf == NULL)
			{
				tmp_err_code = EXIP_MEMORY_ALLOCATION_ERROR;
				break;
			}
			memcpy(newBuf, buf, used);
			if(onHeap)
				EXIP_MFREE(buf);
			buf = newBuf;
			onHeap = TRUE;
			capacity = newCapacity;
		}

		window.str = buf;
		window.length = capacity;
		tmp_err_code = writeCharToString(&window, (uint32_t) code_point, &used);
		if(tmp_err_code != EXIP_OK)
			break;
	}

	if(tmp_err_code != EXIP_OK)
	{
		if(onHeap)
			EXIP_MFREE(buf);
		return tmp_err_code;
	}

	if(memList != NULL && onHeap)
	{
		// Grown on the heap: move it into the allocation list at its final size
		CharType* managed = (CharType*) memManagedAllocate(memList, used);
		if(managed == NULL)
		{
			EXIP_MFREE(buf);
			return EXIP_MEMORY_ALLOCATION_ERROR;
		}
		memcpy(managed, buf, used);
		EXIP_MFREE(buf);
		buf = managed;
	}

	string_val->str = buf;
	string_val->length = used;
	return EXIP_OK;
}

errorCode decodeBinary(EXIStream* strm, char** binary_val, Index* nbytes)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	UnsignedInteger length = 0;
	unsigned long int_val = 0;
	UnsignedInteger i = 0;

	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (binary)"));
	TRY(decodeUnsignedInteger(strm, &length));
	*nbytes = (Index) length;
	(*binary_val) = (char*) EXIP_MALLOC(length); // This memory should be manually freed after the content handler is invoked
	if((*binary_val) == NULL)
		return EXIP_MEMORY_ALLOCATION_ERROR;

	for(i = 0; i < length; i++)
	{
		TRY_CATCH(readBits(strm, 8, &int_val), EXIP_MFREE(*binary_val));
		(*binary_val)[i]=(char) int_val;
	}
	return EXIP_OK;
}

errorCode decodeIntegerValue(EXIStream* strm, Integer* sint_val)
{
	// TODO: If there is associated schema datatype handle differently!
	// TODO: check if the result fit into int type
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	exip_bool bool_val = 0;
	UnsignedInteger val;

	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (int)"));

	TRY(decodeBoolean(strm, &bool_val));
	TRY(decodeUnsignedInteger(strm, &val));

	if(bool_val == 0) // A sign value of zero (0) is used to represent positive integers
		*sint_val = (Integer) val;
	else if(bool_val == 1) // A sign value of one (1) is used to represent negative integers
	{
		val += 1;
		*sint_val = -((Integer) val);
	}
	else
		return EXIP_UNEXPECTED_ERROR;
	return EXIP_OK;
}

errorCode decodeDecimalValue(EXIStream* strm, Decimal* dec_val)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	exip_bool sign;
	UnsignedInteger integr_part = 0;
	UnsignedInteger fract_part = 0;
	UnsignedInteger fract_part_rev = 0;
	unsigned int e;

	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (decimal)"));

	// TODO: implement checks on type overflow

	TRY(decodeBoolean(strm, &sign));
	TRY(decodeUnsignedInteger(strm, &integr_part));
	TRY(decodeUnsignedInteger(strm, &fract_part));

	dec_val->exponent = 0;
	fract_part_rev = 0;
	while(fract_part > 0)
	{
		fract_part_rev = fract_part_rev*10 + fract_part%10;
		fract_part = fract_part/10;
		dec_val->exponent -= 1;
	}

	dec_val->mantissa = integr_part;

	e = dec_val->exponent;
	if(e != 0)
	{
		while(e)
		{
			dec_val->mantissa *= 10;
			e++;
		}

		dec_val->mantissa += fract_part_rev;
	}

	if(sign == TRUE) // negative number
		dec_val->mantissa = -dec_val->mantissa;

	return EXIP_OK;
}

errorCode decodeFloatValue(EXIStream* strm, Float* fl_val)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Integer mantissa;
	Integer exponent;

	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (float)"));

	TRY(decodeIntegerValue(strm, &mantissa));	//decode mantissa
	TRY(decodeIntegerValue(strm, &exponent));	//decode exponent

	DEBUG_MSG(EXIP_LOG_ERROR, DEBUG_STREAM_IO, (">Float value: %ldE%ld\n", (long int)mantissa, (long int)exponent));

//  TODO: Improve the below validation: it should be independent of how the Float is defined
//
//	if(exponent >= (1 << 14) || exponent < -(1 << 14)
//			|| mantissa >= ((uint64_t) 1 << 63) ||
//			(mantissa < 0 && -mantissa > ((uint64_t) 1 << 63))
//			)
//	{
//		DEBUG_MSG(ERROR, DEBUG_STREAM_IO, (">Invalid float value: %lldE%lld\n", mantissa, exponent));
//		return EXIP_INVALID_EXI_INPUT;
//	}

	fl_val->mantissa = mantissa;
	fl_val->exponent = (int16_t)exponent; /* TODO not using exip_config.h */

	return EXIP_OK;
}

errorCode decodeDateTimeValue(EXIStream* strm, EXIType dtType, EXIPDateTime* dt_val)
{
	errorCode tmp_err_code = EXIP_UNEXPECTED_ERROR;
	Integer year;
	unsigned long monDay = 0;
	unsigned long timeVal = 0;
	exip_bool presence = FALSE;

	dt_val->presenceMask = 0;

	DEBUG_MSG(EXIP_LOG_INFO, DEBUG_STREAM_IO, (">> (dateTime)"));

	if(dtType == VALUE_TYPE_DATE_TIME || dtType == VALUE_TYPE_DATE || dtType == VALUE_TYPE_YEAR)
	{
		/* Year component */
		TRY(decodeIntegerValue(strm, &year));
		dt_val->dateTime.tm_year = (int) year + 100;
	}
	else
	{
		dt_val->dateTime.tm_year = INT_MIN;
	}

	if(dtType == VALUE_TYPE_DATE_TIME || dtType == VALUE_TYPE_DATE || dtType == VALUE_TYPE_MONTH)
	{
		/* MonthDay component */
		TRY(decodeNBitUnsignedInteger(strm, 9, &monDay));
		dt_val->dateTime.tm_mon = (int) monDay / 32 - 1;
		dt_val->dateTime.tm_mday = (int) monDay % 32;
	}
	else
	{
		dt_val->dateTime.tm_mon = INT_MIN;
		dt_val->dateTime.tm_mday = INT_MIN;
	}

	if(dtType == VALUE_TYPE_DATE_TIME || dtType == VALUE_TYPE_TIME)
	{
		/* Time component */
		TRY(decodeNBitUnsignedInteger(strm, 17, &timeVal));
		dt_val->dateTime.tm_hour = (timeVal / 64) / 64;
		dt_val->dateTime.tm_min = (timeVal / 64) % 64;
		dt_val->dateTime.tm_sec = timeVal % 64;

		/* FractionalSecs presence component */
		TRY(decodeBoolean(strm, &presence));
		if(presence)
		{
			UnsignedInteger fSecs = 0;
			unsigned int tmp = 0;

			dt_val->presenceMask = dt_val->presenceMask | FRACT_PRESENCE;
			dt_val->fSecs.offset = 0;
			dt_val->fSecs.value = 0;

			/* FractionalSecs component */
			TRY(decodeUnsignedInteger(strm, &fSecs));

			while(fSecs != 0)
			{
				tmp = fSecs % 10;
				dt_val->fSecs.offset++;

				if(tmp != 0)
				{
					dt_val->fSecs.value = dt_val->fSecs.value*10 + tmp;
				}

				fSecs = fSecs / 10;
			}
			dt_val->fSecs.offset -= 1;
		}
	}
	else
	{
		dt_val->dateTime.tm_hour = INT_MIN;
		dt_val->dateTime.tm_min = INT_MIN;
		dt_val->dateTime.tm_sec = INT_MIN;
	}

	/* TimeZone presence component */
	TRY(decodeBoolean(strm, &presence));

	if(presence)
	{
		unsigned long tzone = 0;
		dt_val->presenceMask = dt_val->presenceMask | TZONE_PRESENCE;
		TRY(decodeNBitUnsignedInteger(strm, 11, &tzone));

		if(tzone > 1851)
		{
			tzone = 1851;
			DEBUG_MSG(EXIP_LOG_WARNING, DEBUG_STREAM_IO, (">Invalid TimeZone value: %lu\n", tzone));
		}

		dt_val->TimeZone = (int16_t) tzone - 896;
	}

	return EXIP_OK;
}
