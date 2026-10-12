cmake_minimum_required(VERSION 3.16...3.28)
project (exip.common)

set(PROJECT_SOURCE_FILES
  src/hashtable.c
  src/contentHandler.c
  src/UTF8_stringManipulate.c
  src/memManagement.c
  src/dynamicArray.c
  src/procTypes.c
  src/sTables.c
)

add_library(exip.common STATIC ${PROJECT_SOURCE_FILES} ${EXIP_COMMON_ALLOCATOR_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE exip_warnings exip_includes)

message("Added Lib ${PROJECT_NAME}")
foreach(src ${PROJECT_SOURCE_FILES})
  message(STATUS "Added Source File='${src}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Added Include Dir='${dir}'")
endforeach()

#target_link_libraries( ... )