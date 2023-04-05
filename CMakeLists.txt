cmake_minimum_required(VERSION 3.5)

project(Graph51 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Graph51 main.cpp
    algorithm.h
    bitsequence.h
    edge.h
    io.h
    tree.h
    utils.h
    vertices_stack.h
    vpoint.h
)

add_compile_definitions(TASK_SIZE=64 MAX_TREE=18)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

