cmake_minimum_required(VERSION 3.16...3.28)
project (exip.test)

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(EXIP_LIBS
    "exip.grammarGen"
    "exip.contentIO"
    "exip.grammar"
#    "exip.stringtables"
    "exip.streamIO"
    "exip.common"
)

include_directories(include)

# Warning policy and include directories from cmake/ExipCompilerSettings.cmake; extra
# arguments are added compile options (e.g. -gdwarf-2)
function(set_exip_test_compile_options target)
target_link_libraries(${target} PRIVATE exip_test_warnings exip_includes)
if(ARGN AND NOT MSVC)
    target_compile_options(${target} PRIVATE ${ARGN})
endif()
endfunction()

add_executable(check_exip check_exip.c)
target_link_libraries(check_exip PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_exip)

add_executable(check_compression check_compression.c)
target_link_libraries(check_compression PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_compression)
if(EXIP_ZLIB_ENABLED)
    target_compile_definitions(check_compression PRIVATE EXIP_USE_ZLIB)
endif()

add_executable(check_xsi_type check_xsi_type.c)
target_link_libraries(check_xsi_type PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_xsi_type -gdwarf-2)

add_executable(check_stringTables check_stringTables.c)
target_link_libraries(check_stringTables PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_stringTables)

add_executable(check_strict_grammar check_strict_grammar.c)
target_link_libraries(check_strict_grammar PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_strict_grammar)

add_executable(check_streamIO check_streamIO.c)
target_link_libraries(check_streamIO PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_streamIO)

add_executable(check_profile check_profile.c)
target_link_libraries(check_profile PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_profile)

add_executable(check_grammar check_grammar.c)
target_link_libraries(check_grammar PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_grammar)

add_executable(check_emptyType check_emptyType.c)
target_link_libraries(check_emptyType PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_emptyType)

add_executable(check_contentIO check_contentIO.c)
target_link_libraries(check_contentIO PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_contentIO)

add_executable(check_builtin_grammar check_builtin_grammar.c)
target_link_libraries(check_builtin_grammar PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_builtin_grammar)
