project(AX)
cmake_minimum_required(VERSION 2.8)
enable_testing()

add_definitions("-std=c++11")
set(CMAKE_CXX_COMPILER clang++-3.6)

add_subdirectory(test)
