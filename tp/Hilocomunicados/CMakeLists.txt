cmake_minimum_required(VERSION 3.28)
project(Hilocomunicados)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(GoogleTest)
enable_testing()

add_executable(Hilocomunicados
    src/main.cpp)
add_executable(tests tests/tests_hilo.cpp)
target_link_libraries(tests GTest::gtest_main GTest::gtest)
include(GoogleTest)
gtest_discover_tests(tests)