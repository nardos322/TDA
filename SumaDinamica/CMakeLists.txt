cmake_minimum_required(VERSION 3.28)
project(SumaDinamica)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Configurar gtest
FetchContent_MakeAvailable(googletest)
enable_testing()

# Crear la biblioteca principal
add_library(${PROJECT_NAME}_lib
        src/subset_sum/subset_sum_bottomup.cpp
        src/subset_sum/subset_sum_topdown.cpp
        src/subset_sum/backtraking.cpp)

# Configurar includes
target_include_directories(${PROJECT_NAME}_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Ejecutable principal
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${PROJECT_NAME}_lib)

# Test con Google Test
add_executable(${PROJECT_NAME}_tests
    tests/subset_sum_test.cpp
)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        ${PROJECT_NAME}_lib
        GTest::gtest_main
)

# Registrar los test para poder ejecutarlos con CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)