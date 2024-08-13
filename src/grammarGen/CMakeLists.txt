cmake_minimum_required (VERSION 2.8.12)
project (exip.grammarGen)

set(PROJECT_SOURCE_FILES
  src/genUtils.c
  src/grammarGenerator.c
  src/protoGrammars.c
  src/treeTableBuild.c
  src/treeTableManipulate.c
  src/treeTableToGrammars.c
  xmlSchema/staticXmlSchema.c
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
else(UNIX)
  include_directories(${CMAKE_SOURCE_DIR}/platform/vs2010)
endif (UNIX)

add_library(exip.grammarGen STATIC ${PROJECT_SOURCE_FILES})

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/wd4244")
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/wd4267")
endif()

if(MSVC)
# Not Yet - target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -gdwarf-4)
# (-gdwarf-4)  Until valgrind supporting dwarf-5 is in debian-stable
endif()

message("Added Lib ${PROJECT_NAME}")
foreach(src ${PROJECT_SOURCE_FILES})
  message(STATUS "Added Source File='${src}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Added Include Dir='${dir}'")
endforeach()