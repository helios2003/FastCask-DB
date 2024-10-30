cmake_minimum_required(VERSION 3.10)

project(FastCask VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(headers)

set(SRCS 
    main.cpp 
    src/keydir.cpp 
    src/logger.cpp 
    src/parser.cpp 
    src/utils.cpp
)

add_executable(fastcask.out ${SRCS})

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "fastcask.out")
