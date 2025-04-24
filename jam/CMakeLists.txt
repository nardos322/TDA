cmake_minimum_required(VERSION 3.28)
project(jam)

set(CMAKE_CXX_STANDARD 20)

add_executable(jam main.cpp
        dfs.cpp)
