cmake_minimum_required(VERSION 3.16...3.28)
project (exip)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CheckCCompilerFlag)
set (VERSION_MAJOR 0)
set (VERSION_MINOR 5)
set (VERSION_PATCH 5)
set (VERSION_BUILD b)

# ---------------------------------------------------------------------------
# What to build. Tools and examples need a target with an OS (not a
# bare-metal CMAKE_SYSTEM_NAME Generic toolchain); the test suites must run, so they are
# off when cross-compiling.
# ---------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME STREQUAL "Generic")
    set(_exip_hosted OFF)
else()
    set(_exip_hosted ON)
endif()
if(CMAKE_CROSSCOMPILING)
    set(_exip_native OFF)
else()
    set(_exip_native ON)
endif()
option(EXIP_BUILD_TOOLS "Build the exipg schema compiler" ${_exip_hosted})
option(EXIP_BUILD_EXAMPLES "Build the exipe/exipd examples" ${_exip_hosted})
option(EXIP_BUILD_TESTS "Build the test suites, golden and smoke tests" ${_exip_native})
set(EXIP_VALGRIND AUTO CACHE STRING "Valgrind variants of the test suites: AUTO (when valgrind is found), ON or OFF")
set_property(CACHE EXIP_VALGRIND PROPERTY STRINGS AUTO ON OFF)
set(EXIP_USE_ZLIB AUTO CACHE STRING "zlib for EXI compression: AUTO (native host build with zlib found), ON or OFF")
set_property(CACHE EXIP_USE_ZLIB PROPERTY STRINGS AUTO ON OFF)

# Deprecated switches: they override the options above for this run
if(DEFINED SKIP_TESTS)
    message(DEPRECATION "SKIP_TESTS is deprecated: use EXIP_BUILD_TESTS")
    if(SKIP_TESTS)
        set(EXIP_BUILD_TESTS OFF)
    endif()
endif()
if(DEFINED SKIP_VALGRIND)
    message(DEPRECATION "SKIP_VALGRIND is deprecated: use EXIP_VALGRIND")
    if(SKIP_VALGRIND)
        set(EXIP_VALGRIND OFF)
    endif()
endif()
foreach(_v EXIP_VALGRIND EXIP_USE_ZLIB)
    if(NOT ${_v} MATCHES "^(AUTO|ON|OFF)$")
        message(FATAL_ERROR "${_v} must be AUTO, ON or OFF (is '${${_v}}')")
    endif()
endforeach()

# ---------------------------------------------------------------------------
# Configuration: EXIP_CFG_PRESET (host, small) and the EXIP_CFG_* options
# of cmake/ExipOptions.cmake, written to the generated exip_build_config.h.
# EXIP_PLATFORM_PROFILE is deprecated: it only seeds those options.
# ---------------------------------------------------------------------------
set(EXIP_PLATFORM_PROFILE "" CACHE STRING "Deprecated: pc, mingw, contiki or riot (use EXIP_CFG_PRESET and the EXIP_CFG_* options)")
set_property(CACHE EXIP_PLATFORM_PROFILE PROPERTY STRINGS "" pc mingw contiki riot)
set(EXIP_LEGACY_PROFILE "${EXIP_PLATFORM_PROFILE}")
if(EXIP_LEGACY_PROFILE STREQUAL "vs2010")
    set(EXIP_LEGACY_PROFILE mingw)
endif()
if(EXIP_LEGACY_PROFILE STREQUAL "pc" OR EXIP_LEGACY_PROFILE STREQUAL "mingw")
    set(EXIP_SEED_EXIP_CFG_PRESET host)
elseif(EXIP_LEGACY_PROFILE STREQUAL "contiki")
    set(EXIP_SEED_EXIP_CFG_PRESET small)
    set(EXIP_SEED_EXIP_CFG_ALLOCATOR dmem)
elseif(EXIP_LEGACY_PROFILE STREQUAL "riot")
    # the former platform/gcc/riot/exipConfig.h: the pc settings with debug off and
    # smaller hash tables
    set(EXIP_SEED_EXIP_CFG_PRESET host)
    set(EXIP_SEED_EXIP_CFG_DEBUG OFF)
    set(EXIP_SEED_EXIP_CFG_HASH_TABLE_INITIAL 1021)
    set(EXIP_SEED_EXIP_CFG_HASH_TABLE_MAX 8192)
elseif(NOT EXIP_LEGACY_PROFILE STREQUAL "")
    message(FATAL_ERROR "Unsupported EXIP_PLATFORM_PROFILE='${EXIP_PLATFORM_PROFILE}'. Supported values: pc, mingw, contiki, riot")
endif()
if(NOT EXIP_LEGACY_PROFILE STREQUAL "")
    message(DEPRECATION "EXIP_PLATFORM_PROFILE=${EXIP_PLATFORM_PROFILE} is deprecated: it maps to EXIP_CFG_PRESET and EXIP_CFG_* options (see doc/build.md)")
endif()

include(ExipOptions)
include(ExipCompilerSettings)

# What kind of build this is, for zlib and which tests run:
#   pc        debug on: the test suites
#   mingw     Windows build: no test suites, artifact check
#   embedded  debug off (small preset, contiki, riot): no test suites, smoke tests
if(EXIP_LEGACY_PROFILE STREQUAL "mingw" OR (EXIP_LEGACY_PROFILE STREQUAL "" AND WIN32))
    set(EXIP_BUILD_KIND mingw)
elseif(EXIP_LEGACY_PROFILE STREQUAL "contiki" OR EXIP_LEGACY_PROFILE STREQUAL "riot" OR NOT EXIP_CFG_DEBUG)
    set(EXIP_BUILD_KIND embedded)
else()
    set(EXIP_BUILD_KIND pc)
endif()
if(EXIP_LEGACY_PROFILE STREQUAL "")
    set(EXIP_SMOKE_LABEL "${EXIP_CFG_PRESET}")
else()
    set(EXIP_SMOKE_LABEL "${EXIP_LEGACY_PROFILE}")
endif()

message(STATUS "EXIP build kind: ${EXIP_BUILD_KIND}")

set(EXIP_ZLIB_ENABLED OFF)
if(EXIP_USE_ZLIB STREQUAL "ON")
    find_package(ZLIB REQUIRED)
    set(EXIP_ZLIB_ENABLED ON)
elseif(EXIP_USE_ZLIB STREQUAL "AUTO" AND EXIP_BUILD_KIND STREQUAL "pc" AND NOT CMAKE_CROSSCOMPILING)
    find_package(ZLIB)
    if(ZLIB_FOUND)
        set(EXIP_ZLIB_ENABLED ON)
    endif()
endif()
if(EXIP_ZLIB_ENABLED)
    set(EXIP_ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    set(EXIP_ZLIB_LIBRARIES ${ZLIB_LIBRARIES})
    message(STATUS "EXIP zlib compression support enabled")
else()
    message(STATUS "EXIP zlib compression support disabled")
endif()

# ---------------------------------------------------------------------------
# Security hardening: native UNIX builds with GCC or Clang (no -z relro/now on Apple).
# Disable with -DEXIP_HARDENING=OFF e.g. for RHEL6
# ---------------------------------------------------------------------------
option(EXIP_HARDENING "Enable security hardening compiler/linker flags" ON)
if(EXIP_HARDENING AND UNIX AND NOT CMAKE_CROSSCOMPILING AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        set(EXIP_STACK_PROTECTOR_FLAG "")
        add_compile_options(-D_FORTIFY_SOURCE=2)
        check_c_compiler_flag(-fstack-protector-strong EXIP_HAS_STACK_PROTECTOR_STRONG)
        if(EXIP_HAS_STACK_PROTECTOR_STRONG)
                set(EXIP_STACK_PROTECTOR_FLAG -fstack-protector-strong)
        else()
                check_c_compiler_flag(-fstack-protector EXIP_HAS_STACK_PROTECTOR)
                if(EXIP_HAS_STACK_PROTECTOR)
                        set(EXIP_STACK_PROTECTOR_FLAG -fstack-protector)
                endif()
        endif()
        if(NOT "${EXIP_STACK_PROTECTOR_FLAG}" STREQUAL "")
                add_compile_options(${EXIP_STACK_PROTECTOR_FLAG})
        endif()
        if(NOT APPLE)
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,relro -Wl,-z,now")
                set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,relro -Wl,-z,now")
                set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-z,relro -Wl,-z,now")
        endif()
        message(STATUS "EXIP hardening flags enabled")
else()
    message(STATUS "EXIP hardening flags disabled")
endif()

#add_subdirectory (src/stringTables)
add_subdirectory (src/common)
add_subdirectory (src/streamIO)
add_subdirectory (src/contentIO)
add_subdirectory (src/grammar)
add_subdirectory (src/grammarGen)
if(EXIP_BUILD_TOOLS)
    add_subdirectory (utils/schemaHandling)
endif()
if(EXIP_BUILD_EXAMPLES)
    add_subdirectory (examples/simpleDecoding)
    add_subdirectory (examples/simpleEncoding)
endif()
message(STATUS "EXIP build: tools ${EXIP_BUILD_TOOLS}, examples ${EXIP_BUILD_EXAMPLES}, tests ${EXIP_BUILD_TESTS}")

# Code size of the libraries (berkeley format, per library): the size tool of the
# toolchain (EXIP_SIZE_TOOL, set by cmake/toolchains/*.cmake), else "<prefix>size" next to
# a "<prefix>gcc" cross compiler, else the host size for a native build
if(NOT EXIP_SIZE_TOOL)
    get_filename_component(_exip_cc_name "${CMAKE_C_COMPILER}" NAME)
    if(_exip_cc_name MATCHES "^(.+-)gcc(-[0-9.]+)?(\\.exe)?$")
        find_program(EXIP_SIZE_TOOL NAMES ${CMAKE_MATCH_1}size)
    elseif(NOT CMAKE_CROSSCOMPILING)
        find_program(EXIP_SIZE_TOOL NAMES size)
    endif()
endif()
if(EXIP_SIZE_TOOL)
    add_custom_target(size_report
        COMMAND ${CMAKE_COMMAND} -DSIZE_TOOL=${EXIP_SIZE_TOOL}
            "-DLIBS=$<TARGET_FILE:exip.common>;$<TARGET_FILE:exip.streamIO>;$<TARGET_FILE:exip.grammar>;$<TARGET_FILE:exip.contentIO>;$<TARGET_FILE:exip.grammarGen>"
            -P ${CMAKE_SOURCE_DIR}/cmake/size-report.cmake
        DEPENDS exip.common exip.streamIO exip.grammar exip.contentIO exip.grammarGen
        VERBATIM)
endif()

# Arduino library bundle: <build>/arduino/exip, and a zip of it
set(EXIP_VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
add_custom_target(arduino_bundle
    COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_SOURCE_DIR} -DOUT_DIR=${CMAKE_BINARY_DIR}/arduino
        -DVERSION=${EXIP_VERSION_STRING} -P ${CMAKE_SOURCE_DIR}/cmake/MakeArduinoBundle.cmake
    VERBATIM)
add_custom_target(arduino_bundle_zip
    COMMAND ${CMAKE_COMMAND} -E tar cf exip-arduino-${EXIP_VERSION_STRING}.zip --format=zip exip
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/arduino
    DEPENDS arduino_bundle
    VERBATIM)

# ---------------------------------------------------------------------------
# Install rules
# Default prefix: /usr/local  (override with -DCMAKE_INSTALL_PREFIX=...)
# Libraries  -> ${prefix}/lib
# Headers    -> ${prefix}/include/exip
# Executables-> ${prefix}/bin
# ---------------------------------------------------------------------------
install(TARGETS
    exip.common
    exip.streamIO
    exip.contentIO
    exip.grammar
    exip.grammarGen
    ARCHIVE DESTINATION lib
)
if(EXIP_BUILD_TOOLS)
    install(TARGETS exipg RUNTIME DESTINATION bin)
endif()
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/exip
    FILES_MATCHING PATTERN "*.h"
)
# The configuration this library was built with; consumers compile with
# -DEXIP_HAVE_BUILD_CONFIG=1 so that exipConfig.h picks it up
install(FILES ${EXIP_GENERATED_INCLUDE_DIR}/exip_build_config.h DESTINATION include/exip)

if(NOT EXIP_BUILD_TESTS)
    message(STATUS "EXIP tests not built")
elseif(NOT EXIP_BUILD_KIND STREQUAL "pc")
    # Smoke tests only: the test suites need the debug build (and Check, not used on Windows)
    include(CTest)
    if(NOT CMAKE_CROSSCOMPILING OR CMAKE_CROSSCOMPILING_EMULATOR)
        set(_exip_can_run ON)
    else()
        set(_exip_can_run OFF)
    endif()
    if(EXIP_BUILD_KIND STREQUAL "mingw")
        set(_exip_smoke_labels "smoke;windows;${EXIP_SMOKE_LABEL}")
    else()
        set(_exip_smoke_labels "smoke;embedded;${EXIP_SMOKE_LABEL}")
    endif()

    # The example programs: help output and an encode/decode round trip
    if(EXIP_BUILD_EXAMPLES AND _exip_can_run)
        add_test(NAME smoke_exipe_help COMMAND exipe -help)
        add_test(NAME smoke_exipd_help COMMAND exipd -help)
        set_tests_properties(smoke_exipe_help smoke_exipd_help
            PROPERTIES LABELS "${_exip_smoke_labels}" TIMEOUT 60)
    endif()
    # The d_mem heap (4 KB) is too small for the example document
    if(EXIP_BUILD_EXAMPLES AND _exip_can_run AND NOT EXIP_CFG_ALLOCATOR STREQUAL "dmem")
        add_test(NAME smoke_roundtrip
            COMMAND ${CMAKE_COMMAND}
                -DEXIPE=$<TARGET_FILE:exipe> -DEXIPD=$<TARGET_FILE:exipd>
                "-DEMULATOR=${CMAKE_CROSSCOMPILING_EMULATOR}"
                -DWORK=${CMAKE_BINARY_DIR}/smoke
                -P ${CMAKE_SOURCE_DIR}/cmake/smoke-roundtrip.cmake)
        set_tests_properties(smoke_roundtrip PROPERTIES LABELS "${_exip_smoke_labels}" TIMEOUT 60)
    endif()

    if(EXIP_BUILD_KIND STREQUAL "embedded" AND _exip_can_run)
        add_executable(exip_embedded_smoke tests/embedded_profile_smoke.c)
        target_link_libraries(exip_embedded_smoke PRIVATE
            exip_warnings
            exip_includes
            exip.grammarGen
            exip.contentIO
            exip.grammar
            exip.streamIO
            exip.common)
        if(EXIP_CFG_ALLOCATOR STREQUAL "dmem")
            target_compile_definitions(exip_embedded_smoke PRIVATE EXIP_SMOKE_DMEM=1)
        endif()
        # the configured widths, checked at run time
        math(EXPR _int_bytes "${EXIP_CFG_INTEGER_BITS} / 8")
        target_compile_definitions(exip_embedded_smoke PRIVATE EXIP_SMOKE_INTEGER_BYTES=${_int_bytes})
        if(NOT EXIP_CFG_INDEX_BITS STREQUAL "size")
            math(EXPR _index_bytes "${EXIP_CFG_INDEX_BITS} / 8")
            target_compile_definitions(exip_embedded_smoke PRIVATE EXIP_SMOKE_INDEX_BYTES=${_index_bytes})
        endif()
        if(NOT EXIP_CFG_SMALL_INDEX_BITS STREQUAL "size")
            math(EXPR _small_bytes "${EXIP_CFG_SMALL_INDEX_BITS} / 8")
            target_compile_definitions(exip_embedded_smoke PRIVATE EXIP_SMOKE_SMALL_INDEX_BYTES=${_small_bytes})
        endif()

        add_test(NAME smoke_embedded_profile COMMAND exip_embedded_smoke)
        set_tests_properties(smoke_embedded_profile PROPERTIES LABELS "${_exip_smoke_labels}" TIMEOUT 60)
    endif()

    # Windows: the programs are Windows executables (also checked when cross-compiled)
    if(EXIP_BUILD_KIND STREQUAL "mingw" AND EXIP_BUILD_TOOLS AND EXIP_BUILD_EXAMPLES)
        add_test(
            NAME smoke_windows_artifacts
            COMMAND ${CMAKE_COMMAND}
                "-DEXIP_ARTIFACTS=$<TARGET_FILE:exipe>;$<TARGET_FILE:exipd>;$<TARGET_FILE:exipg>"
                -P ${CMAKE_SOURCE_DIR}/cmake/verify-windows-artifacts.cmake)
        set_tests_properties(smoke_windows_artifacts PROPERTIES LABELS "${_exip_smoke_labels}")
    endif()
else()
    include(CTest)
    add_subdirectory(tests)

    set(EXIP_TEST_SET "${CMAKE_SOURCE_DIR}/tests/test-set")
    set(EXIP_TEST_WORKDIR "${CMAKE_BINARY_DIR}/tests")

    # -----------------------------------------------------------------------
    # Unit tests: no schema file I/O, exercise core codec and stream logic
    # -----------------------------------------------------------------------
    add_test(NAME check_streamIO COMMAND check_streamIO "${EXIP_TEST_SET}")
    add_test(NAME check_grammar COMMAND check_grammar "${EXIP_TEST_SET}")
    add_test(NAME check_stringTables COMMAND check_stringTables "${EXIP_TEST_SET}")
    add_test(NAME check_contentIO COMMAND check_contentIO "${EXIP_TEST_SET}")
    add_test(NAME check_builtin_grammar COMMAND check_builtin_grammar "${EXIP_TEST_SET}")

    set_tests_properties(
        check_streamIO check_grammar check_stringTables
        check_contentIO check_builtin_grammar
        PROPERTIES LABELS "unit" WORKING_DIRECTORY "${EXIP_TEST_WORKDIR}")

    # -----------------------------------------------------------------------
    # Integration tests: schema-aware encode/decode, type and profile tests
    # -----------------------------------------------------------------------
    add_test(NAME check_exip COMMAND check_exip "${EXIP_TEST_SET}")
    add_test(NAME check_xsi_type COMMAND check_xsi_type "${EXIP_TEST_SET}")
    add_test(NAME check_compression COMMAND check_compression "${EXIP_TEST_SET}")
    add_test(NAME check_strict_grammar COMMAND check_strict_grammar "${EXIP_TEST_SET}")
    add_test(NAME check_emptyType COMMAND check_emptyType "${EXIP_TEST_SET}")
    add_test(NAME check_profile COMMAND check_profile "${EXIP_TEST_SET}")

    set_tests_properties(
        check_exip check_xsi_type check_strict_grammar
        check_emptyType check_profile check_compression
        PROPERTIES LABELS "integration" WORKING_DIRECTORY "${EXIP_TEST_WORKDIR}")

    # -----------------------------------------------------------------------
    # Valgrind memory-check variants (UNIX only)
    # Shell redirection is not available in add_test; valgrind output goes to
    # CTest's captured stderr. Use --error-exitcode=1 so leaks fail the test.
    # -----------------------------------------------------------------------
    if(EXIP_VALGRIND STREQUAL "AUTO" AND UNIX AND NOT APPLE)
        find_program(EXIP_VALGRIND_EXECUTABLE valgrind)
    elseif(EXIP_VALGRIND STREQUAL "ON")
        find_program(EXIP_VALGRIND_EXECUTABLE valgrind REQUIRED)
    endif()
    if(NOT EXIP_VALGRIND STREQUAL "OFF" AND EXIP_VALGRIND_EXECUTABLE)
        foreach(_t
            check_streamIO check_grammar check_stringTables
            check_contentIO check_builtin_grammar
            check_exip check_xsi_type check_strict_grammar
            check_emptyType check_profile check_compression)
            add_test(NAME check_valgrind_${_t}
                COMMAND ${EXIP_VALGRIND_EXECUTABLE} --leak-check=yes --error-exitcode=1
                    "${CMAKE_BINARY_DIR}/tests/${_t}" "${EXIP_TEST_SET}")
        endforeach()

        set_tests_properties(
            check_valgrind_check_streamIO check_valgrind_check_grammar
            check_valgrind_check_stringTables check_valgrind_check_contentIO
            check_valgrind_check_builtin_grammar
            PROPERTIES LABELS "unit;valgrind" WORKING_DIRECTORY "${EXIP_TEST_WORKDIR}")
        set_tests_properties(
            check_valgrind_check_exip check_valgrind_check_xsi_type
            check_valgrind_check_strict_grammar check_valgrind_check_emptyType
            check_valgrind_check_profile check_valgrind_check_compression
            PROPERTIES LABELS "integration;valgrind" WORKING_DIRECTORY "${EXIP_TEST_WORKDIR}")
    endif()

    # -----------------------------------------------------------------------
    # Golden output tests: verify exipg produces stable, deterministic output
    # -----------------------------------------------------------------------
    if(EXIP_BUILD_TOOLS)
        set(EXIP_GOLDEN_DIR "${CMAKE_SOURCE_DIR}/tests/golden/exipg")

        foreach(_fixture NonBlockingStreaming emptyType SenML utf8)
            if(_fixture STREQUAL "NonBlockingStreaming")
                set(_schema "${EXIP_TEST_SET}/exip/NonBlockingStreaming-xsd.exi")
            elseif(_fixture STREQUAL "emptyType")
                set(_schema "${EXIP_TEST_SET}/EmptyTypes/emptyTypeSchema-xsd.exi")
            elseif(_fixture STREQUAL "SenML")
                set(_schema "${EXIP_TEST_SET}/exip/SenML-xsd.exi")
            elseif(_fixture STREQUAL "utf8")
                set(_schema "${EXIP_TEST_SET}/SchemaStrict/utf8-xsd.exi")
            endif()

            add_test(NAME golden_exipg_text_${_fixture}
                COMMAND ${CMAKE_COMMAND}
                    -DEXIPG=$<TARGET_FILE:exipg>
                    -DMODE=-text
                    -DSCHEMA=${_schema}
                    -DGOLDEN=${EXIP_GOLDEN_DIR}/${_fixture}.text.golden
                    -DTMP=${CMAKE_BINARY_DIR}/tests/golden_${_fixture}_text.out
                    -P ${CMAKE_SOURCE_DIR}/cmake/compare-exipg-output.cmake)
            set_tests_properties(golden_exipg_text_${_fixture} PROPERTIES LABELS "golden;generator")
        endforeach()

        foreach(_fixture NonBlockingStreaming emptyType utf8)
            if(_fixture STREQUAL "NonBlockingStreaming")
                set(_schema "${EXIP_TEST_SET}/exip/NonBlockingStreaming-xsd.exi")
                set(_pfx "nbs_")
            elseif(_fixture STREQUAL "emptyType")
                set(_schema "${EXIP_TEST_SET}/EmptyTypes/emptyTypeSchema-xsd.exi")
                set(_pfx "empty_")
            elseif(_fixture STREQUAL "utf8")
                set(_schema "${EXIP_TEST_SET}/SchemaStrict/utf8-xsd.exi")
                set(_pfx "u8_")
            endif()

            add_test(NAME golden_exipg_static_${_fixture}
                COMMAND ${CMAKE_COMMAND}
                    -DEXIPG=$<TARGET_FILE:exipg>
                    -DMODE=-static
                    -DPFX=${_pfx}
                    -DSCHEMA=${_schema}
                    -DGOLDEN=${EXIP_GOLDEN_DIR}/${_fixture}.static.golden
                    -DTMP=${CMAKE_BINARY_DIR}/tests/golden_${_fixture}_static.out
                    -P ${CMAKE_SOURCE_DIR}/cmake/compare-exipg-output.cmake)
            set_tests_properties(golden_exipg_static_${_fixture} PROPERTIES LABELS "golden;generator")
        endforeach()

        # The static output of a schema with non-ASCII names compiles cleanly,
        # whether char is signed or not
        foreach(_charsign signed unsigned)
            add_test(NAME golden_exipg_static_utf8_compiles_${_charsign}
                COMMAND ${CMAKE_C_COMPILER} -fsyntax-only -Wall -Werror -f${_charsign}-char
                    -I${CMAKE_SOURCE_DIR}/include -I${EXIP_GENERATED_INCLUDE_DIR} -DEXIP_HAVE_BUILD_CONFIG=1
                    -x c ${EXIP_GOLDEN_DIR}/utf8.static.golden)
            set_tests_properties(golden_exipg_static_utf8_compiles_${_charsign} PROPERTIES LABELS "golden;generator")
        endforeach()
    endif()

endif()
