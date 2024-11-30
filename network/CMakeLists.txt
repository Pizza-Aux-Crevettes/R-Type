cmake_minimum_required(VERSION 3.20)
project(network)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(Network src/main.cpp)

target_include_directories(Network PUBLIC include)
