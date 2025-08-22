#!/bin/bash

# Script to verify test coverage for all implemented problems

echo "======================================"
echo "LeetCode C++ Test Coverage Verification"
echo "======================================"
echo

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
total_problems=0
total_tests=0
missing_tests=0

echo "Checking test coverage..."
echo

# Check Easy problems
echo "EASY PROBLEMS:"
echo "--------------"
for header in src/easy/*.h; do
    if [[ $(basename "$header") == "*.h" ]]; then
        continue
    fi
    
    problem_name=$(basename "$header" .h)
    test_file="tests/easy/${problem_name}_test.cpp"
    
    ((total_problems++))
    
    if [ -f "$test_file" ]; then
        test_count=$(grep -c "TEST_F\|TEST" "$test_file" 2>/dev/null || echo 0)
        echo -e "${GREEN}✓${NC} $problem_name: $test_count test cases"
        ((total_tests+=test_count))
    else
        echo -e "${RED}✗${NC} $problem_name: MISSING TEST FILE"
        ((missing_tests++))
    fi
done

echo

# Check Medium problems
echo "MEDIUM PROBLEMS:"
echo "----------------"
for header in src/medium/*.h; do
    if [[ $(basename "$header") == "*.h" ]]; then
        continue
    fi
    
    problem_name=$(basename "$header" .h)
    test_file="tests/medium/${problem_name}_test.cpp"
    
    ((total_problems++))
    
    if [ -f "$test_file" ]; then
        test_count=$(grep -c "TEST_F\|TEST" "$test_file" 2>/dev/null || echo 0)
        echo -e "${GREEN}✓${NC} $problem_name: $test_count test cases"
        ((total_tests+=test_count))
    else
        echo -e "${RED}✗${NC} $problem_name: MISSING TEST FILE"
        ((missing_tests++))
    fi
done

echo

# Check Hard problems
echo "HARD PROBLEMS:"
echo "--------------"
for header in src/hard/*.h; do
    if [[ $(basename "$header") == "*.h" ]]; then
        continue
    fi
    
    problem_name=$(basename "$header" .h)
    test_file="tests/hard/${problem_name}_test.cpp"
    
    ((total_problems++))
    
    if [ -f "$test_file" ]; then
        test_count=$(grep -c "TEST_F\|TEST" "$test_file" 2>/dev/null || echo 0)
        echo -e "${GREEN}✓${NC} $problem_name: $test_count test cases"
        ((total_tests+=test_count))
    else
        echo -e "${RED}✗${NC} $problem_name: MISSING TEST FILE"
        ((missing_tests++))
    fi
done

echo
echo "======================================"
echo "SUMMARY:"
echo "======================================"
echo "Total Problems Implemented: $total_problems"
echo "Total Test Cases: $total_tests"
echo "Average Tests per Problem: $((total_tests / total_problems))"
echo "Missing Test Files: $missing_tests"

if [ $missing_tests -eq 0 ]; then
    echo -e "${GREEN}✓ 100% Test Coverage!${NC}"
else
    echo -e "${RED}✗ Missing $missing_tests test files${NC}"
fi

echo
echo "======================================"

# Check if all approaches are tested
echo
echo "Checking if all 6 approaches are tested..."
echo

for test_file in tests/*/*.cpp; do
    problem_name=$(basename "$test_file" _test.cpp)
    
    # Count verify calls (should test all 6 approaches)
    verify_count=$(grep -c "verifyAllApproaches\|EXPECT_EQ.*solution\." "$test_file" 2>/dev/null || echo 0)
    
    if [ $verify_count -gt 0 ]; then
        echo -e "${GREEN}✓${NC} $problem_name: Tests multiple approaches"
    else
        echo -e "${YELLOW}⚠${NC} $problem_name: May not test all approaches"
    fi
done