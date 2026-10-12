/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file exipPortability.h
 * @brief Compiler and C library differences, from predefined macros only
 */

#ifndef EXIPPORTABILITY_H_
#define EXIPPORTABILITY_H_

/* MSVC: Visual Studio 2015 (_MSC_VER 1900) is the first with the C99 library functions exip
 * uses (snprintf, strtoll) and declarations after statements */
#if defined(_MSC_VER) && !defined(__clang__) && _MSC_VER < 1900
#  error "exip needs Visual Studio 2015 or later"
#endif

/** strtoll(); overridable for C libraries that lack it */
#ifndef EXIP_STRTOLL
#  define EXIP_STRTOLL strtoll
#endif

/**
 * Compile-time check at file scope: EXIP_STATIC_ASSERT(condition, identifier);
 * _Static_assert from C11, otherwise a typedef of an array of size -1 on failure.
 */
#ifndef EXIP_STATIC_ASSERT
#  if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#    define EXIP_STATIC_ASSERT(cond, name) _Static_assert(cond, #name)
#  else
#    define EXIP_STATIC_ASSERT(cond, name) typedef char exip_static_assert_##name[(cond) ? 1 : -1]
#  endif
#endif

#endif /* EXIPPORTABILITY_H_ */
