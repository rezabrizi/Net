cmake_minimum_required(VERSION 3.26)
project(Net)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(ASIO_STANDALONE)

add_executable(Net main.cpp
        include/net_common.h
        include/net_server.h
        include/net_client.h
        include/net_tsqueue.h
        include/net_message.h
        include/net.h
        include/net_connection.h)

target_include_directories(Net PRIVATE /Users/rezatabrizi/dev/sdk/asio/include)