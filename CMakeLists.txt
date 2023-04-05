cmake_minimum_required(VERSION 3.5)

project(Graph51 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Graph51 src/main.cpp
    src/algorithm.h
    src/bitsequence.h
    src/edge.h
    src/io.h
    src/tree.h
    src/utils.h
    src/vertices_stack.h
    src/vpoint.h
)

add_compile_definitions(TASK_SIZE=64 MAX_TREE=18)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

