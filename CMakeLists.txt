cmake_minimum_required(VERSION 3.27)
project(Net)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(ASIO_STANDALONE)

add_executable(Net main.cpp
        headers/common.h)

target_include_directories(Net PRIVATE /Users/rezatabrizi/dev/sdk/asio/include)