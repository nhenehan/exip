cmake_minimum_required(VERSION 3.16...3.28)
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
  "decodeCoffeeShopEXI.c"
  "exampleDecodeRegistry.c"
)

add_executable(exipd ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ".")

target_link_libraries(exipd PRIVATE
    exip_warnings
    exip_includes
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

