cmake_minimum_required(VERSION 3.28)
project(magicuadrados)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip

)
FetchContent_MakeAvailable(GoogleTest)

enable_testing()
add_executable(magicuadrados src/main.cpp
        src/magicuadrados.cpp)
add_executable(tests tests/tests_magic.cpp
                src/magicuadrados.cpp)
target_include_directories(magicuadrados PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tests GTest::gtest_main GTest::gtest)
include(GoogleTest)

gtest_discover_tests(tests)


