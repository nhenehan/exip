/*==================================================================*\
|                EXIP - Embeddable EXI Processor in C                |
|--------------------------------------------------------------------|
|          This work is licensed under BSD 3-Clause License          |
|  The full license terms and conditions are located in LICENSE.txt  |
\===================================================================*/

/**
 * @file exip_arduino_config.h
 * @brief exip configuration for Arduino and PlatformIO boards
 *
 * Selected with EXIP_USER_CONFIG_FILE="exip_arduino_config.h" (library.json, the Arduino
 * library bundle). Lean settings for 32-bit ARM and ESP32 boards: no debug output, 32-bit
 * integers, 16-bit indexes, no hash tables. Every setting can be overridden with a -D build
 * flag (PlatformIO build_flags), since each one is only defined here if still undefined.
 *
 * With EXIP_DEBUG=ON the debug output goes to exip_debug_printf(), which the application
 * provides, for example by forwarding to Serial.
 */

#ifndef EXIP_ARDUINO_CONFIG_H_
#define EXIP_ARDUINO_CONFIG_H_

#include <stdint.h>

#ifndef ON
#  define ON  1
#endif
#ifndef OFF
#  define OFF 0
#endif

#ifndef EXIP_DEBUG
#  define EXIP_DEBUG OFF
#endif

/* 32-bit integers and float mantissa; the 16-bit exponent covers the EXI range and costs no
 * space (the struct is padded to 8 bytes either way) */
#ifndef EXIP_UNSIGNED_INTEGER
#  define EXIP_UNSIGNED_INTEGER uint32_t
#endif
#ifndef EXIP_INTEGER
#  define EXIP_INTEGER int32_t
#endif
#ifndef EXIP_FLOAT_MANTISSA_T
#  define EXIP_FLOAT_MANTISSA_T int32_t
#endif
#ifndef EXIP_FLOAT_EXPONENT_T
#  define EXIP_FLOAT_EXPONENT_T int16_t
#endif

/* 16-bit table indexes, 8-bit grammar rule indexes */
#ifndef EXIP_INDEX
#  define EXIP_INDEX uint16_t
#  define EXIP_INDEX_MAX UINT16_MAX
#endif
#ifndef EXIP_SMALL_INDEX
#  define EXIP_SMALL_INDEX uint8_t
#  define EXIP_SMALL_INDEX_MAX UINT8_MAX
#endif

#ifndef HASH_TABLE_USE
#  define HASH_TABLE_USE OFF
#endif
#ifndef EXIP_IMPLICIT_DATA_TYPE_CONVERSION
#  define EXIP_IMPLICIT_DATA_TYPE_CONVERSION OFF
#endif
#ifndef EXIP_COMPRESSION_TRACE
#  define EXIP_COMPRESSION_TRACE OFF
#endif
#ifndef DEFAULT_GRAMMAR_TABLE
#  define DEFAULT_GRAMMAR_TABLE 40
#endif
#ifndef DEFAULT_SIMPLE_GRAMMAR_TABLE
#  define DEFAULT_SIMPLE_GRAMMAR_TABLE 55
#endif

/* Arduino cores and ESP-IDF have their own boolean, ERROR and STRICT */
#ifndef EXIP_NO_LEGACY_BOOLEAN
#  define EXIP_NO_LEGACY_BOOLEAN
#endif
#ifndef EXIP_NO_LEGACY_LOG_LEVELS
#  define EXIP_NO_LEGACY_LOG_LEVELS
#endif
#ifndef EXIP_NO_LEGACY_STRICT
#  define EXIP_NO_LEGACY_STRICT
#endif

#if EXIP_DEBUG == ON
#  ifdef __cplusplus
extern "C"
#  endif
int exip_debug_printf(const char* format, ...);
#  ifndef DEBUG_OUTPUT
#    define DEBUG_OUTPUT(msg) do { exip_debug_printf msg; } while(0)
#  endif
#  ifndef DEBUG_CHAR_OUTPUT
#    define DEBUG_CHAR_OUTPUT(character) do { exip_debug_printf("%c", character); } while(0)
#  endif
#endif

#endif /* EXIP_ARDUINO_CONFIG_H_ */
