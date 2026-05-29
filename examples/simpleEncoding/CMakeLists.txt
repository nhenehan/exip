cmake_minimum_required(VERSION 2.8.12...3.28)
project (exipe)

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
  "exipe.c"
  "encodeTestEXI.c"
  "encodeCoffeeShopEXI.c"
  "exampleEncodeRegistry.c"
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

include_directories(${EXIP_PLATFORM_INCLUDE_DIR})

add_executable(exipe ${PROJECT_SOURCE_FILES})

if(MSVC)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_options(${PROJECT_NAME} PRIVATE /wd4018 /wd4267)
endif()

target_link_libraries(exipe PRIVATE
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

