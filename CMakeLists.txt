cmake_minimum_required(VERSION 3.26)
project(Net)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(ASIO_STANDALONE)

add_executable(Net main.cpp
        headers/net_common.h
        headers/net_server.h
        headers/net_client.h
        headers/net_tsqueue.h
        headers/net_message.h
        headers/net.h
        headers/net_connection.h)

target_include_directories(Net PRIVATE /Users/rezatabrizi/dev/sdk/asio/include)