cmake_minimum_required(VERSION 3.16...3.28)
project (exip.streamIO)

set(PROJECT_SOURCE_FILES
  src/ioUtil.c
  src/streamDecode.c
  src/streamEncode.c
  src/streamRead.c
  src/streamWrite.c
)

add_library(exip.streamIO STATIC ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE exip_warnings exip_includes)

message("Added Lib ${PROJECT_NAME}")
foreach(src ${PROJECT_SOURCE_FILES})
  message(STATUS "Added Source File='${src}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Added Include Dir='${dir}'")
endforeach()