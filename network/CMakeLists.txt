cmake_minimum_required(VERSION 3.20)
project(network)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(Network ${SOURCES})

target_include_directories(Network PUBLIC include ../external/smart-buffer-cpp/include)

target_link_libraries(Network smart_buffer)