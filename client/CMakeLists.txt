cmake_minimum_required(VERSION 3.20)
project(client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(Client ${SOURCES})

target_include_directories(Client PUBLIC include)

target_link_libraries(Client sfml-graphics sfml-window sfml-system smart_buffer GameEngine)