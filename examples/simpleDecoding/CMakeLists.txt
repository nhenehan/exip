cmake_minimum_required (VERSION 2.8.12)
project (exipd)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(EXIP_LIBS
    "exip.grammarGen"
    "exip.contentIO"
    "exip.grammar"
    "exip.streamIO"
    "exip.common"
)

set(PROJECT_SOURCE_FILES
  "exipd.c"
  "decodeTestEXI.c"
)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/common/include
  ${CMAKE_SOURCE_DIR}/src/stringTables/include
  ${CMAKE_SOURCE_DIR}/src/grammar/include
  ${CMAKE_SOURCE_DIR}/src/streamIO/include
  ${CMAKE_SOURCE_DIR}/src/contentIO/include
  "."
)

if (UNIX)
  include_directories(${CMAKE_SOURCE_DIR}/platform/gcc/pc)
else(UNIX)
  include_directories(${CMAKE_SOURCE_DIR}/platform/vs2010)
endif (UNIX)

add_executable(exipd ${PROJECT_SOURCE_FILES})

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/wd4018")
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/wd4267")
endif()

target_link_libraries(exipd PRIVATE
    ${EXIP_LIBS}
    Threads::Threads
)

message("Added Executable ${PROJECT_NAME}")
foreach(src ${PROJECT_SOURCE_FILES})
  message(STATUS "Added Source File='${src}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Added Include Dir='${dir}'")
endforeach()