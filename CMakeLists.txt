cmake_minimum_required(VERSION 2.8.12...3.28)
project (exip)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CheckCCompilerFlag)
set (VERSION_MAJOR 0)
set (VERSION_MINOR 5)
set (VERSION_PATCH 5)
set (VERSION_BUILD b)

option(SKIP_TESTS "To build without building tests." OFF)
if (WIN32)
  set(SKIP_TESTS ON)
endif()

option(SKIP_VALGRIND "To build without valgrind tests." OFF)
if (WIN32)
    set(SKIP_VALGRIND ON)
endif()

set(EXIP_PLATFORM_PROFILE "" CACHE STRING "EXIP platform profile (pc, mingw, contiki, riot)")
if("${EXIP_PLATFORM_PROFILE}" STREQUAL "")
    if(WIN32)
        set(EXIP_PLATFORM_PROFILE mingw CACHE STRING "EXIP platform profile (pc, mingw, contiki, riot)" FORCE)
    else()
        set(EXIP_PLATFORM_PROFILE pc CACHE STRING "EXIP platform profile (pc, mingw, contiki, riot)" FORCE)
    endif()
endif()
if(EXIP_PLATFORM_PROFILE STREQUAL "vs2010")
    set(EXIP_PLATFORM_PROFILE mingw)
endif()
set_property(CACHE EXIP_PLATFORM_PROFILE PROPERTY STRINGS pc mingw contiki riot)

if(EXIP_PLATFORM_PROFILE STREQUAL "pc")
    set(EXIP_PLATFORM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/platform/gcc/pc")
    set(EXIP_COMMON_PLATFORM_SOURCES)
    set(EXIP_BUILD_HOST_TOOLS ON)
elseif(EXIP_PLATFORM_PROFILE STREQUAL "mingw")
    set(EXIP_PLATFORM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/platform/vs2010")
    set(EXIP_COMMON_PLATFORM_SOURCES)
    set(EXIP_BUILD_HOST_TOOLS ON)
    set(SKIP_TESTS ON)
    set(SKIP_VALGRIND ON)
elseif(EXIP_PLATFORM_PROFILE STREQUAL "contiki")
    set(EXIP_PLATFORM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/platform/gcc/contiki")
    set(EXIP_COMMON_PLATFORM_SOURCES "${CMAKE_SOURCE_DIR}/platform/gcc/contiki/d_mem.c")
    set(EXIP_BUILD_HOST_TOOLS ON)
    set(SKIP_TESTS ON)
    set(SKIP_VALGRIND ON)
elseif(EXIP_PLATFORM_PROFILE STREQUAL "riot")
    set(EXIP_PLATFORM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/platform/gcc/riot")
    set(EXIP_COMMON_PLATFORM_SOURCES)
    set(EXIP_BUILD_HOST_TOOLS ON)
    set(SKIP_TESTS ON)
    set(SKIP_VALGRIND ON)
else()
    message(FATAL_ERROR "Unsupported EXIP_PLATFORM_PROFILE='${EXIP_PLATFORM_PROFILE}'. Supported values: pc, mingw, contiki, riot")
endif()

message(STATUS "EXIP platform profile: ${EXIP_PLATFORM_PROFILE}")

find_package(ZLIB)
if(EXIP_PLATFORM_PROFILE STREQUAL "pc" AND ZLIB_FOUND)
    set(EXIP_USE_ZLIB ON)
    set(EXIP_ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    set(EXIP_ZLIB_LIBRARIES ${ZLIB_LIBRARIES})
    message(STATUS "EXIP zlib compression support enabled")
else()
    set(EXIP_USE_ZLIB OFF)
    message(STATUS "EXIP zlib compression support disabled")
endif()

# ---------------------------------------------------------------------------
# Security hardening (GCC/Clang, UNIX only, opt-out for embedded/legacy)
# Disable with -DEXIP_HARDENING=OFF e.g. for RHEL6 or bare-metal targets
# ---------------------------------------------------------------------------
option(EXIP_HARDENING "Enable security hardening compiler/linker flags" ON)
if(EXIP_HARDENING AND UNIX AND NOT WIN32 AND EXIP_PLATFORM_PROFILE STREQUAL "pc")
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
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,relro -Wl,-z,now")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,relro -Wl,-z,now")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-z,relro -Wl,-z,now")
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
if(EXIP_BUILD_HOST_TOOLS)
    add_subdirectory (utils/schemaHandling)
    add_subdirectory (examples/simpleDecoding)
    add_subdirectory (examples/simpleEncoding)
else()
    message(STATUS "Skipping host-only tools and examples for profile ${EXIP_PLATFORM_PROFILE}")
endif()

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
if(EXIP_BUILD_HOST_TOOLS)
    install(TARGETS exipg RUNTIME DESTINATION bin)
endif()
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/exip
    FILES_MATCHING PATTERN "*.h"
)

if(SKIP_TESTS)
    message("Skipping build of test cases")

    if(EXIP_PLATFORM_PROFILE STREQUAL "contiki" OR EXIP_PLATFORM_PROFILE STREQUAL "riot" OR EXIP_PLATFORM_PROFILE STREQUAL "mingw")
        include(CTest)
    endif()

    if(EXIP_PLATFORM_PROFILE STREQUAL "contiki" OR EXIP_PLATFORM_PROFILE STREQUAL "riot")
        add_executable(exip_embedded_smoke tests/embedded_profile_smoke.c)
        target_include_directories(exip_embedded_smoke PRIVATE
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src/common/include
            ${EXIP_PLATFORM_INCLUDE_DIR})
        target_link_libraries(exip_embedded_smoke PRIVATE
            exip.grammarGen
            exip.contentIO
            exip.grammar
            exip.streamIO
            exip.common)
        if(EXIP_PLATFORM_PROFILE STREQUAL "contiki")
            target_compile_definitions(exip_embedded_smoke PRIVATE EXIP_SMOKE_CONTIKI=1)
        endif()

        add_test(NAME smoke_exipe_help COMMAND exipe -help)
        add_test(NAME smoke_exipd_help COMMAND exipd -help)
        add_test(NAME smoke_embedded_profile COMMAND exip_embedded_smoke)
        set_tests_properties(
            smoke_exipe_help smoke_exipd_help smoke_embedded_profile
            PROPERTIES LABELS "smoke;embedded;${EXIP_PLATFORM_PROFILE}")
    endif()

    if(EXIP_PLATFORM_PROFILE STREQUAL "mingw")
        add_test(
            NAME smoke_mingw_artifacts
            COMMAND ${CMAKE_COMMAND}
                -DEXIP_BUILD_DIR=${CMAKE_BINARY_DIR}
                -P ${CMAKE_SOURCE_DIR}/cmake/verify-mingw-artifacts.cmake)
        set_tests_properties(smoke_mingw_artifacts PROPERTIES LABELS "smoke;mingw")
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
    add_test(NAME check_strict_grammar COMMAND check_strict_grammar "${EXIP_TEST_SET}")
    add_test(NAME check_emptyType COMMAND check_emptyType "${EXIP_TEST_SET}")
    add_test(NAME check_profile COMMAND check_profile "${EXIP_TEST_SET}")

    set_tests_properties(
        check_exip check_xsi_type check_strict_grammar
        check_emptyType check_profile
        PROPERTIES LABELS "integration" WORKING_DIRECTORY "${EXIP_TEST_WORKDIR}")

    # -----------------------------------------------------------------------
    # Valgrind memory-check variants (UNIX only)
    # Shell redirection is not available in add_test; valgrind output goes to
    # CTest's captured stderr. Use --error-exitcode=1 so leaks fail the test.
    # -----------------------------------------------------------------------
    if(UNIX)
        foreach(_t
            check_streamIO check_grammar check_stringTables
            check_contentIO check_builtin_grammar
            check_exip check_xsi_type check_strict_grammar
            check_emptyType check_profile)
            add_test(NAME check_valgrind_${_t}
                COMMAND valgrind --leak-check=yes --error-exitcode=1
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
            check_valgrind_check_profile
            PROPERTIES LABELS "integration;valgrind" WORKING_DIRECTORY "${EXIP_TEST_WORKDIR}")
    endif(UNIX)

    # -----------------------------------------------------------------------
    # Golden output tests: verify exipg produces stable, deterministic output
    # -----------------------------------------------------------------------
    if(EXIP_PLATFORM_PROFILE STREQUAL "pc" OR EXIP_PLATFORM_PROFILE STREQUAL "")
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
                    -I${CMAKE_SOURCE_DIR}/include -I${CMAKE_SOURCE_DIR}/platform/gcc/pc
                    ${EXIP_GOLDEN_DIR}/utf8.static.golden -x c)
            set_tests_properties(golden_exipg_static_utf8_compiles_${_charsign} PROPERTIES LABELS "golden;generator")
        endforeach()
    endif()

endif(SKIP_TESTS)
