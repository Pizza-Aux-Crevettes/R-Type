cmake_minimum_required(VERSION 3.20)
project(network)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES src/*.cpp src/**/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp include/**/*.hpp)

add_executable(Network ${SOURCES} ${HEADERS})

target_include_directories(Network PUBLIC include ../external/smart-buffer-cpp/include)

target_link_libraries(Network PRIVATE smart_buffer)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries(Network PRIVATE Qt6::Widgets)
