/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file exip.h
 * @brief The exip API in one header: types, serializer, parser, string helpers
 *
 * In C++ the API is declared in namespace exip with C linkage, so that exip's String does
 * not clash with other String types (Arduino's String class): use exip::String,
 * exip::serialize, exip::parse and so on. The macros (TRY, SET_STRICT, TRUE, ...) are global.
 * Include this header rather than the individual exip headers from C++.
 */

#ifndef EXIP_H_
#define EXIP_H_

#ifdef __cplusplus
/* The C library headers that exip includes, declared outside the namespace first */
#  include <assert.h>
#  include <limits.h>
#  include <stddef.h>
#  include <stdint.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>
#  include <time.h>
namespace exip {
extern "C" {
#endif

#include "procTypes.h"
#include "stringManipulate.h"
#include "EXISerializer.h"
#include "EXIParser.h"

#ifdef __cplusplus
} /* extern "C" */
} /* namespace exip */
#endif

#endif /* EXIP_H_ */
