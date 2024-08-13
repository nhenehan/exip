cmake_minimum_required (VERSION 2.8.12)
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

if (UNIX)
  include_directories(${CMAKE_SOURCE_DIR}/platform/gcc/pc)
endif (UNIX)

add_executable(check_exip check_exip.c)
target_link_libraries(check_exip PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_exip PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_xsi_type check_xsi_type.c)
target_link_libraries(check_xsi_type PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_xsi_type PRIVATE -gdwarf-2 -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
## (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_stringTables check_stringTables.c)
target_link_libraries(check_stringTables PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_stringTables PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_strict_grammar check_strict_grammar.c)
target_link_libraries(check_strict_grammar PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_strict_grammar PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_streamIO check_streamIO.c)
target_link_libraries(check_streamIO PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_streamIO PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_profile check_profile.c)
target_link_libraries(check_profile PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_profile PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_grammar check_grammar.c)
target_link_libraries(check_grammar PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_grammar PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_emptyType check_emptyType.c)
target_link_libraries(check_emptyType PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_emptyType PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_contentIO check_contentIO.c)
target_link_libraries(check_contentIO PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_contentIO PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

add_executable(check_builtin_grammar check_builtin_grammar.c)
target_link_libraries(check_builtin_grammar PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
    ${CHECK_LIBRARIES}
)

if(MSVC)
# Not Yet - target_compile_options(xxxxx PRIVATE /W4 /WX)
else()
target_compile_options(check_builtin_grammar PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()
