cmake_minimum_required(VERSION 2.8.12...3.28)
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

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/common/include
  ${CMAKE_SOURCE_DIR}/src/stringTables/include
  ${CMAKE_SOURCE_DIR}/src/grammar/include
  ${CMAKE_SOURCE_DIR}/src/streamIO/include
  ${CMAKE_SOURCE_DIR}/src/contentIO/include
  "include"
)

include_directories(${EXIP_PLATFORM_INCLUDE_DIR})

function(set_exip_test_compile_options target)
if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(${target} PRIVATE ${ARGN}
    -Wall -Wextra -Wpedantic -Werror
    -Wno-format-extra-args   # Check macro expansion: fail_unless/fail_if/fail pass
                             # user fmt+args after a fixed prefix string; GCC fires
                             # -Wformat-extra-args on the fixed prefix. Approved exception.
    -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()
endfunction()

add_executable(check_exip check_exip.c)
target_link_libraries(check_exip PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)
set_exip_test_compile_options(check_exip)

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
