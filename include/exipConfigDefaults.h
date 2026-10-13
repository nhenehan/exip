/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file exipConfigDefaults.h
 * @brief Defaults and checks for every EXIP configuration setting
 *
 * Included by exipConfig.h after the user and build configuration; only settings
 * that are still undefined get a value here. The defaults are those of the former
 * platform/gcc/pc/exipConfig.h (the CMake "host" preset). The integer, float and
 * index types have their defaults in procTypes.h.
 */

#ifndef EXIPCONFIGDEFAULTS_H_
#define EXIPCONFIGDEFAULTS_H_

#include <stdlib.h>

#ifndef ON
#  define ON  1
#endif
#ifndef OFF
#  define OFF 0
#endif

/** Debug message levels, for EXIP_DEBUG_LEVEL and DEBUG_MSG() */
#define EXIP_LOG_INFO    1
#define EXIP_LOG_WARNING 2
#define EXIP_LOG_ERROR   3

/* The former names of the levels. They clash with windows.h (ERROR), so they are left out
 * on Windows and when EXIP_NO_LEGACY_LOG_LEVELS is defined. Same tokens as before, so an
 * identical definition elsewhere is not a redefinition. */
#if !defined(EXIP_NO_LEGACY_LOG_LEVELS) && !defined(_WIN32)
#  define INFO    1
#  define WARNING 2
#  define ERROR   3
#endif

/**
 * @def EXIP_DEBUG
 * 		Turn the debugging ON/OFF; host builds and the test suites need it ON (the
 * 		module switches below keep it silent)
 * @def EXIP_DEBUG_LEVEL
 * 		Sets the debugging level (EXIP_LOG_INFO, EXIP_LOG_WARNING or EXIP_LOG_ERROR)
 * @def DEBUG_STREAM_IO
 * 		Turns the debugging ON/OFF for the STREAM_IO module
 * @def DEBUG_COMMON
 * 		Turns the debugging ON/OFF for the COMMON module
 * @def DEBUG_CONTENT_IO
 * 		Turns the debugging ON/OFF for the CONTENT_IO module
 * @def DEBUG_GRAMMAR_GEN
 * 		Turns the debugging ON/OFF for the GRAMMAR_GEN module
 * @ref debugging */
#ifndef EXIP_DEBUG
#  define EXIP_DEBUG ON
#endif
#ifndef EXIP_DEBUG_LEVEL
#  define EXIP_DEBUG_LEVEL EXIP_LOG_INFO
#endif
#ifndef DEBUG_STREAM_IO
#  define DEBUG_STREAM_IO OFF
#endif
#ifndef DEBUG_COMMON
#  define DEBUG_COMMON OFF
#endif
#ifndef DEBUG_CONTENT_IO
#  define DEBUG_CONTENT_IO OFF
#endif
#ifndef DEBUG_GRAMMAR_GEN
#  define DEBUG_GRAMMAR_GEN OFF
#endif

/* Assertions follow EXIP_DEBUG unless the build decides (e.g. CMake Release defines NDEBUG) */
#if EXIP_DEBUG != ON && !defined(NDEBUG)
#  define NDEBUG
#endif
#include <assert.h>

/**
 * @name mem_group Memory allocation functions
 * EXIP_ALLOCATOR_HEADER, if defined, is included first (e.g. "d_mem.h").
 */
/**@{*/
#ifdef EXIP_ALLOCATOR_HEADER
#  include EXIP_ALLOCATOR_HEADER
#endif
#ifndef EXIP_MALLOC
#  define EXIP_MALLOC malloc
#endif
#ifndef EXIP_REALLOC
#  define EXIP_REALLOC realloc
#endif
#ifndef EXIP_MFREE
#  define EXIP_MFREE free
#endif
/**@}*/

/** Hash tables for the string tables (sizes in entries) */
#ifndef HASH_TABLE_USE
#  define HASH_TABLE_USE ON
#endif
#ifndef INITIAL_HASH_TABLE_SIZE
#  define INITIAL_HASH_TABLE_SIZE 6151
#endif
#ifndef MAX_HASH_TABLE_SIZE
#  define MAX_HASH_TABLE_SIZE 32000
#endif

/** Dynamic arrays (growable tables); OFF is not supported by the library code today */
#ifndef DYN_ARRAY_USE
#  define DYN_ARRAY_USE ON
#endif

/** Conversions between typed values and strings in the API (e.g. stringData for an int) */
#ifndef EXIP_IMPLICIT_DATA_TYPE_CONVERSION
#  define EXIP_IMPLICIT_DATA_TYPE_CONVERSION ON
#endif

/** zlib level of EXI compression output: Z_DEFAULT_COMPRESSION (-1, that is 6), as
 * EXIficient (java.util.zip.Deflater.DEFAULT_COMPRESSION); 0 to 9 otherwise */
#ifndef EXIP_DEFLATE_LEVEL
#  define EXIP_DEFLATE_LEVEL (-1)
#endif

/** Initial sizes of the grammar tables built for a schema (initSchemaInstance.c) */
#ifndef DEFAULT_GRAMMAR_TABLE
#  define DEFAULT_GRAMMAR_TABLE 300
#endif
#ifndef DEFAULT_SIMPLE_GRAMMAR_TABLE
#  define DEFAULT_SIMPLE_GRAMMAR_TABLE 75
#endif
#ifndef DEFAULT_ENUM_TABLE
#  define DEFAULT_ENUM_TABLE 5
#endif

/** The EXI Profile default parameters (no local value tables, no built-in grammars) */
#ifndef EXI_PROFILE_DEFAULT
#  define EXI_PROFILE_DEFAULT OFF
#endif
#if EXI_PROFILE_DEFAULT
#  ifndef VALUE_CROSSTABLE_USE
#    define VALUE_CROSSTABLE_USE OFF
#  endif
#  ifndef BUILD_IN_GRAMMARS_USE
#    define BUILD_IN_GRAMMARS_USE OFF
#  endif
#else
/** Whether to implement the local value string table */
#  ifndef VALUE_CROSSTABLE_USE
#    define VALUE_CROSSTABLE_USE ON
#  endif
/** Whether to enable the use of built-in grammars */
#  ifndef BUILD_IN_GRAMMARS_USE
#    define BUILD_IN_GRAMMARS_USE ON
#  endif
#endif

/* ---- checks ---------------------------------------------------------- */

#if (EXIP_DEBUG != ON && EXIP_DEBUG != OFF) || (DEBUG_STREAM_IO != ON && DEBUG_STREAM_IO != OFF) || \
    (DEBUG_COMMON != ON && DEBUG_COMMON != OFF) || (DEBUG_CONTENT_IO != ON && DEBUG_CONTENT_IO != OFF) || \
    (DEBUG_GRAMMAR_GEN != ON && DEBUG_GRAMMAR_GEN != OFF)
#  error "exip configuration: the debug switches must be ON or OFF"
#endif
#if EXIP_DEBUG_LEVEL < EXIP_LOG_INFO || EXIP_DEBUG_LEVEL > EXIP_LOG_ERROR
#  error "exip configuration: EXIP_DEBUG_LEVEL must be EXIP_LOG_INFO, EXIP_LOG_WARNING or EXIP_LOG_ERROR"
#endif
#if (HASH_TABLE_USE != ON && HASH_TABLE_USE != OFF) || (DYN_ARRAY_USE != ON && DYN_ARRAY_USE != OFF) || \
    (EXIP_IMPLICIT_DATA_TYPE_CONVERSION != ON && EXIP_IMPLICIT_DATA_TYPE_CONVERSION != OFF) || \
    (EXI_PROFILE_DEFAULT != ON && EXI_PROFILE_DEFAULT != OFF) || \
    (VALUE_CROSSTABLE_USE != ON && VALUE_CROSSTABLE_USE != OFF) || \
    (BUILD_IN_GRAMMARS_USE != ON && BUILD_IN_GRAMMARS_USE != OFF)
#  error "exip configuration: the feature switches must be ON or OFF"
#endif
#if EXI_PROFILE_DEFAULT == ON && (VALUE_CROSSTABLE_USE == ON || BUILD_IN_GRAMMARS_USE == ON)
#  error "exip configuration: EXI_PROFILE_DEFAULT requires VALUE_CROSSTABLE_USE and BUILD_IN_GRAMMARS_USE OFF"
#endif
#if EXIP_DEFLATE_LEVEL < -1 || EXIP_DEFLATE_LEVEL > 9
#  error "exip configuration: EXIP_DEFLATE_LEVEL must be -1 (zlib's default) or 0 to 9"
#endif
#if INITIAL_HASH_TABLE_SIZE > MAX_HASH_TABLE_SIZE
#  error "exip configuration: INITIAL_HASH_TABLE_SIZE is larger than MAX_HASH_TABLE_SIZE"
#endif

#endif /* EXIPCONFIGDEFAULTS_H_ */
