cmake_minimum_required(VERSION 2.8.12...3.28)
project (exip.contentIO)

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

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/common/include
  ${CMAKE_SOURCE_DIR}/src/stringTables/include
  ${CMAKE_SOURCE_DIR}/src/grammar/include
  ${CMAKE_SOURCE_DIR}/src/streamIO/include
  include
)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXIP_PLATFORM_INCLUDE_DIR})

if(EXIP_USE_ZLIB)
	target_include_directories(${PROJECT_NAME} PRIVATE ${EXIP_ZLIB_INCLUDE_DIRS})
	target_compile_definitions(${PROJECT_NAME} PRIVATE EXIP_USE_ZLIB)
	target_link_libraries(${PROJECT_NAME} ${EXIP_ZLIB_LIBRARIES})
endif()

if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_options(${PROJECT_NAME} PRIVATE /wd4267)
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