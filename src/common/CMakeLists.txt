cmake_minimum_required(VERSION 2.8.12...3.28)
project (exip.common)

set(PROJECT_SOURCE_FILES
  src/hashtable.c
  src/contentHandler.c
  src/ASCII_stringManipulate.c
  src/memManagement.c
  src/dynamicArray.c
  src/procTypes.c
  src/sTables.c
)

add_library(exip.common STATIC ${PROJECT_SOURCE_FILES} ${EXIP_COMMON_PLATFORM_SOURCES})

target_include_directories(exip.common PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/stringTables/include
  ${CMAKE_SOURCE_DIR}/src/grammar/include
  ${CMAKE_SOURCE_DIR}/src/common/include
  include
)
target_include_directories(exip.common PRIVATE ${EXIP_PLATFORM_INCLUDE_DIR})

if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_options(${PROJECT_NAME} PRIVATE /wd4244 /wd4267)
  # Not Yet - /W4 /WX
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
  # (-Werror) deferred until the pre-existing warnings are resolved
  # (-gdwarf-4) Until valgrind supporting dwarf-5 is in debian-stable
endif()

message("Added Lib ${PROJECT_NAME}")
foreach(src ${PROJECT_SOURCE_FILES})
  message(STATUS "Added Source File='${src}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Added Include Dir='${dir}'")
endforeach()

#target_link_libraries( ... )