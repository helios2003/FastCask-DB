cmake_minimum_required(VERSION 3.10)

project(RunTests)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../headers)

find_package(Catch2 REQUIRED)

set(TEST_SRCS test.cpp)

set(PROJECT_SRCS
    ../src/keydir.cpp
    ../src/logger.cpp
    ../src/parser.cpp
    ../src/utils.cpp
)

add_executable(benchmark ${TEST_SRCS} ${PROJECT_SRCS})
target_link_libraries(benchmark PRIVATE Catch2::Catch2WithMain)
