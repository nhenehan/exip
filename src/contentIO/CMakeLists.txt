cmake_minimum_required(VERSION 3.16...3.28)
project (exip.contentIO)

set(PROJECT_SOURCE_FILES
  src/EXIParser.c
  src/EXISerializer.c
  src/bodyDecode.c
  src/bodyEncode.c
  src/compressionDecode.c
  src/compressionEncode.c
  src/headerDecode.c
  src/headerEncode.c
  src/initSchemaInstance.c
  src/staticEXIOptions.c
  src/sTableDefault.c
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE exip_warnings exip_includes)

if(EXIP_ZLIB_ENABLED)
	target_include_directories(${PROJECT_NAME} PRIVATE ${EXIP_ZLIB_INCLUDE_DIRS})
	target_compile_definitions(${PROJECT_NAME} PRIVATE EXIP_USE_ZLIB)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${EXIP_ZLIB_LIBRARIES})
endif()

message("Added Lib ${PROJECT_NAME}")
foreach(src ${PROJECT_SOURCE_FILES})
  message(STATUS "Added Source File='${src}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Added Include Dir='${dir}'")
endforeach()