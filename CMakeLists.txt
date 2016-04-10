project(AX)
cmake_minimum_required(VERSION 2.8)
enable_testing()

include_directories("${CMAKE_SOURCE_DIR}/src")

add_definitions("-std=c++11")

add_subdirectory(test)
