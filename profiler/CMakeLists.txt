cmake_minimum_required(VERSION 3.5)

project(profiler)

add_executable(profiler main.cc)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -std=c++17")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})