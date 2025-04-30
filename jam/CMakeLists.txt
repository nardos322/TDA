cmake_minimum_required(VERSION 3.28)
project(jam)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}_lib
        src/dfs.cpp
        src/grafo.cpp
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

