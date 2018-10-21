cmake_minimum_required(VERSION 3.5)
project(pmt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -O2)
set(EXECUTABLE_OUTPUT_PATH ./bin)

add_executable(pmt ./src/main.cpp ./src/string_searching_algorithm.h ./src/string_searching_algorithm.cpp ./src/aho_corasick.h ./src/aho_corasick.cpp ./src/boyer_moore.h ./src/boyer_moore.cpp ./src/shift_or.h ./src/shift_or.cpp ./src/ukkonen.h ./src/ukkonen.cpp ./src/wu_manber.h ./src/wu_manber.cpp)
