cmake_minimum_required(VERSION 3.22)
project(TestSocket)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(Server server/Server.cpp)
add_executable(Client client/Client.cpp)
