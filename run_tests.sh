#!/bin/bash

# Script to build and run all tests with coverage information

echo "======================================"
echo "LeetCode C++ Test Runner"
echo "======================================"
echo

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

cd build

# Configure with CMake
echo "Configuring project with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

if [ $? -ne 0 ]; then
    echo -e "${RED}CMake configuration failed!${NC}"
    exit 1
fi

echo
echo "Building project..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

echo
echo -e "${GREEN}Build successful!${NC}"
echo

# Check if test executable exists
if [ ! -f "leetcode_tests" ]; then
    echo -e "${RED}Test executable not found! Make sure Google Test is installed.${NC}"
    exit 1
fi

echo "======================================"
echo "Running Tests..."
echo "======================================"
echo

# Run tests with detailed output
./leetcode_tests --gtest_color=yes

TEST_RESULT=$?

echo
echo "======================================"
echo "Test Summary:"
echo "======================================"

if [ $TEST_RESULT -eq 0 ]; then
    echo -e "${GREEN}✓ All tests passed!${NC}"

    # Count total tests
    TOTAL_TESTS=$(./leetcode_tests --gtest_list_tests | grep -c "  ")
    echo "Total test cases executed: $TOTAL_TESTS"
else
    echo -e "${RED}✗ Some tests failed!${NC}"
    echo "Exit code: $TEST_RESULT"
fi

echo
echo "For more options:"
echo "  Run specific test: ./leetcode_tests --gtest_filter=TestSuite.TestName"
echo "  Verbose output: ./leetcode_tests --gtest_verbose"
echo "  XML output: ./leetcode_tests --gtest_output=xml:results.xml"
echo "  List all tests: ./leetcode_tests --gtest_list_tests"
echo

exit $TEST_RESULT
