cmake_minimum_required(VERSION 3.8)
project(project4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp variable.h variable.cpp graph.h graph.cpp function.h function.cpp)
add_executable(project4 ${SOURCE_FILES})