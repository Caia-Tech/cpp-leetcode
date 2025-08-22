cmake_minimum_required(VERSION 3.16)
project(cpp_leetcode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags for debugging and optimization
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(src)

# Find required packages
find_package(GTest)
find_package(benchmark)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Create library
add_library(leetcode_lib ${SOURCES})

# Test executable
if(GTest_FOUND)
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
    add_executable(leetcode_tests ${TEST_SOURCES})
    target_link_libraries(leetcode_tests leetcode_lib GTest::gtest GTest::gtest_main pthread)
    
    enable_testing()
    add_test(NAME leetcode_unit_tests COMMAND leetcode_tests)
else()
    message(WARNING "Google Test not found. Tests will not be built.")
endif()

# Benchmark executable
if(benchmark_FOUND)
    add_executable(leetcode_benchmarks benchmarks/benchmark_main.cpp)
    target_link_libraries(leetcode_benchmarks leetcode_lib benchmark::benchmark pthread)
else()
    message(WARNING "Google Benchmark not found. Benchmarks will not be built.")
endif()