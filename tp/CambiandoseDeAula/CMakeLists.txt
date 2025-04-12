cmake_minimum_required(VERSION 3.28)
project(CambiandoseDeAula)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(GoogleTest)
enable_testing()

add_executable(CambiandoseDeAula src/main.cpp)
add_executable(tests tests/tests_main.cpp)
target_compile_definitions(tests PRIVATE LOCAL)
target_link_libraries(tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)