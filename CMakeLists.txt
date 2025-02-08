cmake_minimum_required(VERSION 3.21)
project(parallel_game_of_life)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -fopenmp")
add_executable(parallel_game_of_life main.cpp)
