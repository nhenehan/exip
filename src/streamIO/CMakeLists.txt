cmake_minimum_required(VERSION 2.8.12...3.28)
project (exip.streamIO)

set(PROJECT_SOURCE_FILES
  src/ioUtil.c
  src/streamDecode.c
  src/streamEncode.c
  src/streamRead.c
  src/streamWrite.c
)

add_library(exip.streamIO STATIC ${PROJECT_SOURCE_FILES})

target_include_directories(exip.streamIO PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/common/include
  include
)
target_include_directories(exip.streamIO PRIVATE ${EXIP_PLATFORM_INCLUDE_DIR})

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