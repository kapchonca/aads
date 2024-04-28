cmake_minimum_required(VERSION 3.8)

project(pumpkin)

add_executable(pumpkin main.cc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -std=c++17")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
