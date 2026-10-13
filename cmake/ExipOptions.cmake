# EXIP configuration options.
#
# EXIP_CFG_PRESET seeds the defaults of the other EXIP_CFG_* options when they are first
# created (an option given with -D always wins; later preset changes do not reseed):
#   host   the former platform/gcc/pc/exipConfig.h: debug on, 64-bit integers, size_t
#          indexes, hash tables, implicit conversions
#   small  the former platform/gcc/contiki/exipConfig.h with the libc allocator: debug
#          off, 32-bit integers, 16/8-bit indexes, no hash tables, no implicit conversions
# The legacy EXIP_PLATFORM_PROFILE (deprecated) sets EXIP_SEED_<option> variables before
# this file is included.
#
# The options are written to ${EXIP_GENERATED_INCLUDE_DIR}/exip_build_config.h, which
# include/exipConfig.h includes when EXIP_HAVE_BUILD_CONFIG is defined (target exip_config).

function(exip_option name type doc default)
    if(DEFINED EXIP_SEED_${name})
        set(default "${EXIP_SEED_${name}}")
    endif()
    set(${name} "${default}" CACHE ${type} "${doc}")
endfunction()

exip_option(EXIP_CFG_PRESET STRING "Configuration preset: host or small" host)
set_property(CACHE EXIP_CFG_PRESET PROPERTY STRINGS host small)
if(NOT EXIP_CFG_PRESET MATCHES "^(host|small)$")
    message(FATAL_ERROR "EXIP_CFG_PRESET must be host or small, not '${EXIP_CFG_PRESET}'")
endif()
if(EXIP_CFG_PRESET STREQUAL "small")
    set(_small ON)
else()
    set(_small OFF)
endif()

macro(_exip_pick var host_value small_value)
    if(_small)
        set(${var} "${small_value}")
    else()
        set(${var} "${host_value}")
    endif()
endmacro()

_exip_pick(_d_debug ON OFF)
_exip_pick(_d_intbits 64 32)
_exip_pick(_d_index size 16)
_exip_pick(_d_small size 8)
_exip_pick(_d_hash ON OFF)
_exip_pick(_d_hash_initial 6151 53)
_exip_pick(_d_hash_max 32000 3000)
_exip_pick(_d_implicit ON OFF)
_exip_pick(_d_grammar_table 300 40)
_exip_pick(_d_simple_grammar_table 75 55)

exip_option(EXIP_CFG_DEBUG BOOL "Debug support (EXIP_DEBUG); the test suites need it" ${_d_debug})
exip_option(EXIP_CFG_DEBUG_LEVEL STRING "Debug level: INFO, WARNING or ERROR" INFO)
set_property(CACHE EXIP_CFG_DEBUG_LEVEL PROPERTY STRINGS INFO WARNING ERROR)
exip_option(EXIP_CFG_DEBUG_MODULES STRING
    "Modules with debug output (list of STREAM_IO, COMMON, CONTENT_IO, GRAMMAR_GEN)" "")
exip_option(EXIP_CFG_ALLOCATOR STRING "Allocator: libc, dmem (src/common/alloc) or custom" libc)
set_property(CACHE EXIP_CFG_ALLOCATOR PROPERTY STRINGS libc dmem custom)
exip_option(EXIP_CFG_MALLOC STRING "custom allocator: malloc function" "")
exip_option(EXIP_CFG_REALLOC STRING "custom allocator: realloc function" "")
exip_option(EXIP_CFG_FREE STRING "custom allocator: free function" "")
exip_option(EXIP_CFG_ALLOCATOR_HEADER STRING "custom allocator: header declaring it" "")
exip_option(EXIP_CFG_INTEGER_BITS STRING "Integer value width: 64 or 32" ${_d_intbits})
set_property(CACHE EXIP_CFG_INTEGER_BITS PROPERTY STRINGS 64 32)
exip_option(EXIP_CFG_INDEX_BITS STRING "Index width: size (size_t), 32 or 16" ${_d_index})
set_property(CACHE EXIP_CFG_INDEX_BITS PROPERTY STRINGS size 32 16)
exip_option(EXIP_CFG_SMALL_INDEX_BITS STRING "SmallIndex width: size (size_t), 32, 16 or 8" ${_d_small})
set_property(CACHE EXIP_CFG_SMALL_INDEX_BITS PROPERTY STRINGS size 32 16 8)
exip_option(EXIP_CFG_HASH_TABLES BOOL "Hash tables for the string tables (HASH_TABLE_USE)" ${_d_hash})
exip_option(EXIP_CFG_HASH_TABLE_INITIAL STRING "INITIAL_HASH_TABLE_SIZE" ${_d_hash_initial})
exip_option(EXIP_CFG_HASH_TABLE_MAX STRING "MAX_HASH_TABLE_SIZE" ${_d_hash_max})
exip_option(EXIP_CFG_PROFILE_DEFAULT BOOL "EXI Profile default parameters (EXI_PROFILE_DEFAULT)" OFF)
if(EXIP_CFG_PROFILE_DEFAULT)
    set(_d_profile_feature OFF)
else()
    set(_d_profile_feature ON)
endif()
exip_option(EXIP_CFG_VALUE_CROSSTABLE BOOL "Local value tables (VALUE_CROSSTABLE_USE)" ${_d_profile_feature})
exip_option(EXIP_CFG_BUILTIN_GRAMMARS BOOL "Built-in grammars (BUILD_IN_GRAMMARS_USE)" ${_d_profile_feature})
exip_option(EXIP_CFG_IMPLICIT_CONVERSION BOOL
    "Implicit data type conversions (EXIP_IMPLICIT_DATA_TYPE_CONVERSION)" ${_d_implicit})
exip_option(EXIP_CFG_GRAMMAR_TABLE STRING "DEFAULT_GRAMMAR_TABLE (initial entries)" ${_d_grammar_table})
exip_option(EXIP_CFG_SIMPLE_GRAMMAR_TABLE STRING "DEFAULT_SIMPLE_GRAMMAR_TABLE (initial entries)"
    ${_d_simple_grammar_table})
exip_option(EXIP_CFG_COMPRESSION_TRACE BOOL "Compression decoder traces to stderr" OFF)
exip_option(EXIP_CFG_DEFLATE_LEVEL STRING "zlib level of compression output: -1 (default, 6, as EXIficient) or 0 to 9" -1)

# ---- values for the generated header -------------------------------------
macro(_exip_onoff var value)
    if(${value})
        set(${var} ON)
    else()
        set(${var} OFF)
    endif()
endmacro()

_exip_onoff(EXIP_GEN_DEBUG EXIP_CFG_DEBUG)
if(NOT EXIP_CFG_DEFLATE_LEVEL MATCHES "^(-1|[0-9])$")
    message(FATAL_ERROR "EXIP_CFG_DEFLATE_LEVEL must be -1 or 0 to 9")
endif()
if(NOT EXIP_CFG_DEBUG_LEVEL MATCHES "^(INFO|WARNING|ERROR)$")
    message(FATAL_ERROR "EXIP_CFG_DEBUG_LEVEL must be INFO, WARNING or ERROR")
endif()
foreach(_m STREAM_IO COMMON CONTENT_IO GRAMMAR_GEN)
    set(EXIP_GEN_DEBUG_${_m} OFF)
endforeach()
foreach(_m ${EXIP_CFG_DEBUG_MODULES})
    if(NOT _m MATCHES "^(STREAM_IO|COMMON|CONTENT_IO|GRAMMAR_GEN)$")
        message(FATAL_ERROR "EXIP_CFG_DEBUG_MODULES: unknown module '${_m}'")
    endif()
    set(EXIP_GEN_DEBUG_${_m} ON)
endforeach()

set(EXIP_COMMON_ALLOCATOR_SOURCES)
set(EXIP_GEN_ALLOCATOR "/* libc allocator: exipConfigDefaults.h defaults (malloc, realloc, free) */")
if(EXIP_CFG_ALLOCATOR STREQUAL "dmem")
    set(EXIP_COMMON_ALLOCATOR_SOURCES "${CMAKE_SOURCE_DIR}/src/common/alloc/d_mem.c")
    set(EXIP_GEN_ALLOCATOR "#ifndef EXIP_ALLOCATOR_HEADER\n#define EXIP_ALLOCATOR_HEADER \"d_mem.h\"\n#endif\n#ifndef EXIP_MALLOC\n#define EXIP_MALLOC d_malloc\n#endif\n#ifndef EXIP_REALLOC\n#define EXIP_REALLOC d_realloc\n#endif\n#ifndef EXIP_MFREE\n#define EXIP_MFREE d_free\n#endif")
elseif(EXIP_CFG_ALLOCATOR STREQUAL "custom")
    if(EXIP_CFG_MALLOC STREQUAL "" OR EXIP_CFG_REALLOC STREQUAL "" OR EXIP_CFG_FREE STREQUAL "")
        message(FATAL_ERROR "EXIP_CFG_ALLOCATOR=custom needs EXIP_CFG_MALLOC, EXIP_CFG_REALLOC and EXIP_CFG_FREE")
    endif()
    set(EXIP_GEN_ALLOCATOR "#ifndef EXIP_MALLOC\n#define EXIP_MALLOC ${EXIP_CFG_MALLOC}\n#endif\n#ifndef EXIP_REALLOC\n#define EXIP_REALLOC ${EXIP_CFG_REALLOC}\n#endif\n#ifndef EXIP_MFREE\n#define EXIP_MFREE ${EXIP_CFG_FREE}\n#endif")
    if(NOT EXIP_CFG_ALLOCATOR_HEADER STREQUAL "")
        set(EXIP_GEN_ALLOCATOR "#ifndef EXIP_ALLOCATOR_HEADER\n#define EXIP_ALLOCATOR_HEADER \"${EXIP_CFG_ALLOCATOR_HEADER}\"\n#endif\n${EXIP_GEN_ALLOCATOR}")
    endif()
elseif(NOT EXIP_CFG_ALLOCATOR STREQUAL "libc")
    message(FATAL_ERROR "EXIP_CFG_ALLOCATOR must be libc, dmem or custom")
endif()

if(EXIP_CFG_INTEGER_BITS STREQUAL "64")
    set(EXIP_GEN_UNSIGNED_INTEGER uint64_t)
    set(EXIP_GEN_INTEGER int64_t)
    set(EXIP_GEN_FLOAT_MANTISSA int64_t)
    set(EXIP_GEN_FLOAT_EXPONENT int16_t)
elseif(EXIP_CFG_INTEGER_BITS STREQUAL "32")
    set(EXIP_GEN_UNSIGNED_INTEGER uint32_t)
    set(EXIP_GEN_INTEGER int32_t)
    set(EXIP_GEN_FLOAT_MANTISSA int32_t)
    set(EXIP_GEN_FLOAT_EXPONENT int8_t)
else()
    message(FATAL_ERROR "EXIP_CFG_INTEGER_BITS must be 64 or 32")
endif()

function(_exip_index_type prefix bits allowed)
    if(bits STREQUAL "size")
        set(${prefix}_TYPE size_t PARENT_SCOPE)
        set(${prefix}_MAX SIZE_MAX PARENT_SCOPE)
    elseif(bits MATCHES "^(${allowed})$")
        set(${prefix}_TYPE uint${bits}_t PARENT_SCOPE)
        set(${prefix}_MAX UINT${bits}_MAX PARENT_SCOPE)
    else()
        message(FATAL_ERROR "${prefix}: unsupported width '${bits}' (size or ${allowed})")
    endif()
endfunction()
_exip_index_type(EXIP_GEN_INDEX "${EXIP_CFG_INDEX_BITS}" "32|16")
_exip_index_type(EXIP_GEN_SMALL_INDEX "${EXIP_CFG_SMALL_INDEX_BITS}" "32|16|8")

_exip_onoff(EXIP_GEN_HASH_TABLES EXIP_CFG_HASH_TABLES)
_exip_onoff(EXIP_GEN_PROFILE_DEFAULT EXIP_CFG_PROFILE_DEFAULT)
_exip_onoff(EXIP_GEN_VALUE_CROSSTABLE EXIP_CFG_VALUE_CROSSTABLE)
_exip_onoff(EXIP_GEN_BUILTIN_GRAMMARS EXIP_CFG_BUILTIN_GRAMMARS)
_exip_onoff(EXIP_GEN_IMPLICIT_CONVERSION EXIP_CFG_IMPLICIT_CONVERSION)
_exip_onoff(EXIP_GEN_COMPRESSION_TRACE EXIP_CFG_COMPRESSION_TRACE)

set(EXIP_GENERATED_INCLUDE_DIR "${CMAKE_BINARY_DIR}/generated/include")
configure_file(${CMAKE_SOURCE_DIR}/cmake/exip_build_config.h.in
    ${EXIP_GENERATED_INCLUDE_DIR}/exip_build_config.h @ONLY)

add_library(exip_config INTERFACE)
target_include_directories(exip_config INTERFACE
    ${EXIP_GENERATED_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/common/alloc)
target_compile_definitions(exip_config INTERFACE EXIP_HAVE_BUILD_CONFIG=1)

message(STATUS "EXIP configuration: preset ${EXIP_CFG_PRESET}, debug ${EXIP_GEN_DEBUG}, "
    "${EXIP_CFG_INTEGER_BITS}-bit integers, Index ${EXIP_GEN_INDEX_TYPE}, SmallIndex ${EXIP_GEN_SMALL_INDEX_TYPE}, "
    "allocator ${EXIP_CFG_ALLOCATOR}, hash tables ${EXIP_GEN_HASH_TABLES}")
