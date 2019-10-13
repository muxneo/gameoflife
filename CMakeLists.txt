cmake_minimum_required (VERSION 2.6)
project (GOL)

set (CMAKE_C_FLAGS "-Wall -Wextra -pedantic-errors")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
include_directories(${CMAKE_BINARY_DIR}/../include)
add_executable(gol ${CMAKE_BINARY_DIR}/../src/gol.c)

