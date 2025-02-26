cmake_minimum_required(VERSION 3.14)
project(neofind)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -O3
    -Wall
    -Wextra
    -Wpedantic
)

# suppress warning
# see https://cmake.org/cmake/help/latest/policy/CMP0135.html
cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(generate_conwaylife_inference_test src/GenerateConwaylifeInferenceFunctionTest.cpp)

add_executable(conwaylife_inference_test src/ConwaylifeInferenceFunctionTest.cpp)
target_link_libraries(conwaylife_inference_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(conwaylife_inference_test)
