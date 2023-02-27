cmake_minimum_required (VERSION 2.8.12)
project (exip.contentIO)

get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

set(PROJECT_SOURCE_FILES
  src/EXIParser.c
  src/EXISerializer.c
  src/bodyDecode.c
  src/bodyEncode.c
  src/headerDecode.c
  src/headerEncode.c
  src/initSchemaInstance.c
  src/staticEXIOptions.c
  src/sTableDefault.c
)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/common/include
  ${CMAKE_SOURCE_DIR}/src/stringTables/include
  ${CMAKE_SOURCE_DIR}/src/grammar/include
  ${CMAKE_SOURCE_DIR}/src/streamIO/include
  "include"
)

if (UNIX)
  include_directories(${CMAKE_SOURCE_DIR}/platform/gcc/pc)
else(UNIX)
  include_directories(${CMAKE_SOURCE_DIR}/platform/vs2010)
endif (UNIX)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/wd4267")
endif()

message("Added Lib ${PROJECT_NAME}")
foreach(src ${PROJECT_SOURCE_FILES})
  message(STATUS "Added Source File='${src}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Added Include Dir='${dir}'")
endforeach()