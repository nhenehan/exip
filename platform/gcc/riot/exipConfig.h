/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file riot/exipConfig.h
 * @brief Configuration parameters of the EXIP library for RIOT OS targets
 */

#include <stdlib.h>

#ifndef EXIPCONFIG_H_
#define EXIPCONFIG_H_

#define ON  1
#define OFF 0

#define EXIP_DEBUG        OFF
#define EXIP_DEBUG_LEVEL  INFO

#define DEBUG_STREAM_IO   OFF
#define DEBUG_COMMON      OFF
#define DEBUG_CONTENT_IO  OFF
#define DEBUG_GRAMMAR     OFF
#define DEBUG_GRAMMAR_GEN OFF
#define DEBUG_STRING_TBLS OFF

#if EXIP_DEBUG != ON
# define NDEBUG
#endif

#include <assert.h>

/* RIOT profile keeps the allocator contract explicit for portability. */
#define EXIP_MALLOC malloc
#define EXIP_REALLOC realloc
#define EXIP_MFREE free

#define HASH_TABLE_USE ON
#define INITIAL_HASH_TABLE_SIZE 1021
#define MAX_HASH_TABLE_SIZE 8192

#define DYN_ARRAY_USE ON

/* 24-bit max non-terminal marker for table-safe grammar indexing. */
#define GR_VOID_NON_TERMINAL 0xFFFFFF

#define EXIP_IMPLICIT_DATA_TYPE_CONVERSION ON

#define EXI_PROFILE_DEFAULT OFF

#if EXI_PROFILE_DEFAULT
# define VALUE_CROSSTABLE_USE  OFF
# define BUILD_IN_GRAMMARS_USE OFF
#else
# define VALUE_CROSSTABLE_USE  ON
# define BUILD_IN_GRAMMARS_USE ON
#endif

#endif /* EXIPCONFIG_H_ */
