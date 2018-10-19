cmake_minimum_required(VERSION 3.12)
project(IF767-pmt)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(IF767-pmt ./src/main.cpp)