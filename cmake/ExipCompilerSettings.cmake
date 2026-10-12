# Compiler settings shared by every exip target.
#
#   exip_warnings       warning policy per compiler family; -Werror or /WX behind
#                       EXIP_WARNINGS_AS_ERRORS
#   exip_test_warnings  exip_warnings plus the approved Check exception
#   exip_includes       the library's include directories and the configuration
#                       (exip_config from cmake/ExipOptions.cmake, included before this file)
#
# Link them PRIVATE: target_link_libraries(<t> PRIVATE exip_warnings exip_includes).

option(EXIP_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

add_library(exip_warnings INTERFACE)
if(MSVC)
    # MSVC and clang-cl, Visual Studio 2015 or later. Sources are UTF-8.
    # The ISO C names (strcpy, fopen, ...) are used on purpose: no "secure"/POSIX-name
    # deprecation warnings.
    target_compile_definitions(exip_warnings INTERFACE
        _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE)
    # Disabled /W4 warnings, each also not enforced for GCC/Clang:
    #   C4244, C4267  integer narrowing conversions (-Wconversion is not part of the policy)
    #   C4127         conditional expression is constant: the configuration switches are
    #                 used in if() conditions (DEBUG_MSG, EXIP_DEBUG == ON)
    target_compile_options(exip_warnings INTERFACE /W4 /utf-8 /wd4244 /wd4267 /wd4127)
    if(MSVC_VERSION GREATER_EQUAL 1928)
        # C11 (Visual Studio 2019 16.8): _Static_assert, no "nonstandard extension" warnings
        # for C99 initializers
        target_compile_options(exip_warnings INTERFACE /std:c11)
    else()
        # C89 mode: C4204/C4221 report C99 aggregate initializers as extensions
        target_compile_options(exip_warnings INTERFACE /wd4204 /wd4221)
    endif()
    if(EXIP_WARNINGS_AS_ERRORS)
        target_compile_options(exip_warnings INTERFACE /WX)
    endif()
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(exip_warnings INTERFACE -Wall -Wextra -Wpedantic)
    if(EXIP_WARNINGS_AS_ERRORS)
        target_compile_options(exip_warnings INTERFACE -Werror)
    endif()
    # DWARF 4 until valgrind supporting DWARF 5 is in debian-stable; not for optimised
    # release configurations
    target_compile_options(exip_warnings INTERFACE
        $<$<NOT:$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>>:-gdwarf-4>)
endif()

add_library(exip_test_warnings INTERFACE)
target_link_libraries(exip_test_warnings INTERFACE exip_warnings)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    # Check's fail_unless/fail_if/fail pass the user format and arguments after a fixed
    # prefix string, which -Wformat-extra-args reports. Approved exception.
    target_compile_options(exip_test_warnings INTERFACE -Wno-format-extra-args)
endif()

add_library(exip_includes INTERFACE)
target_include_directories(exip_includes INTERFACE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/common/include
    ${CMAKE_SOURCE_DIR}/src/grammar/include
    ${CMAKE_SOURCE_DIR}/src/grammarGen/include
    ${CMAKE_SOURCE_DIR}/src/streamIO/include
    ${CMAKE_SOURCE_DIR}/src/contentIO/include
)
target_link_libraries(exip_includes INTERFACE exip_config)
