cmake_minimum_required(VERSION 3.20)
project(GAME_ENGINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(GameEngine ${SOURCES})

target_include_directories(GameEngine PUBLIC include)

target_link_libraries(GameEngine sfml-graphics sfml-window sfml-system)