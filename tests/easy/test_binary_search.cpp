#include <gtest/gtest.h>
#include "../../src/easy/binary_search.h"
#include <vector>
#include <algorithm>
#include <random>

namespace leetcode {
namespace easy {
namespace test {

class BinarySearchTest : public ::testing::Test {
protected:
    // Test all approaches
    void testAllApproaches(std::vector<int>& nums, int target, int expected) {
        BinarySearch solution;
        
        EXPECT_EQ(solution.searchClassic(nums, target), expected) 
            << "Classic approach failed for target " << target;
        EXPECT_EQ(solution.searchRecursive(nums, target), expected) 
            << "Recursive approach failed for target " << target;
        EXPECT_EQ(solution.searchBitManipulation(nums, target), expected) 
            << "Bit manipulation approach failed for target " << target;
        EXPECT_EQ(solution.searchLowerBound(nums, target), expected) 
            << "Lower bound approach failed for target " << target;
        EXPECT_EQ(solution.searchExponential(nums, target), expected) 
            << "Exponential search approach failed for target " << target;
        EXPECT_EQ(solution.searchInterpolation(nums, target), expected) 
            << "Interpolation search approach failed for target " << target;
    }
    
    // Helper to create sorted array
    std::vector<int> createSortedArray(int start, int end, int step = 1) {
        std::vector<int> result;
        for (int i = start; i <= end; i += step) {
            result.push_back(i);
        }
        return result;
    }
};

// LeetCode Example Test Cases

TEST_F(BinarySearchTest, LeetCodeExample1) {
    // nums = [-1,0,3,5,9,12], target = 9
    // Output: 4
    std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
    testAllApproaches(nums, 9, 4);
}

TEST_F(BinarySearchTest, LeetCodeExample2) {
    // nums = [-1,0,3,5,9,12], target = 2
    // Output: -1 (not found)
    std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
    testAllApproaches(nums, 2, -1);
}

// Edge Cases

TEST_F(BinarySearchTest, SingleElement_Found) {
    std::vector<int> nums = {5};
    testAllApproaches(nums, 5, 0);
}

TEST_F(BinarySearchTest, SingleElement_NotFound) {
    std::vector<int> nums = {5};
    testAllApproaches(nums, 3, -1);
}

TEST_F(BinarySearchTest, TwoElements_First) {
    std::vector<int> nums = {1, 3};
    testAllApproaches(nums, 1, 0);
}

TEST_F(BinarySearchTest, TwoElements_Second) {
    std::vector<int> nums = {1, 3};
    testAllApproaches(nums, 3, 1);
}

TEST_F(BinarySearchTest, TwoElements_NotFound) {
    std::vector<int> nums = {1, 3};
    testAllApproaches(nums, 2, -1);
}

// Target Position Tests

TEST_F(BinarySearchTest, TargetAtBeginning) {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    testAllApproaches(nums, 1, 0);
}

TEST_F(BinarySearchTest, TargetAtEnd) {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    testAllApproaches(nums, 9, 8);
}

TEST_F(BinarySearchTest, TargetInMiddle) {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    testAllApproaches(nums, 5, 4);
}

TEST_F(BinarySearchTest, TargetNotFound_TooSmall) {
    std::vector<int> nums = {10, 20, 30, 40, 50};
    testAllApproaches(nums, 5, -1);
}

TEST_F(BinarySearchTest, TargetNotFound_TooLarge) {
    std::vector<int> nums = {10, 20, 30, 40, 50};
    testAllApproaches(nums, 60, -1);
}

TEST_F(BinarySearchTest, TargetNotFound_InBetween) {
    std::vector<int> nums = {10, 20, 30, 40, 50};
    testAllApproaches(nums, 25, -1);
}

// Special Value Tests

TEST_F(BinarySearchTest, NegativeNumbers) {
    std::vector<int> nums = {-50, -40, -30, -20, -10};
    testAllApproaches(nums, -30, 2);
    testAllApproaches(nums, -25, -1);
}

TEST_F(BinarySearchTest, MixedPositiveNegative) {
    std::vector<int> nums = {-10, -5, 0, 5, 10};
    testAllApproaches(nums, 0, 2);
    testAllApproaches(nums, -5, 1);
    testAllApproaches(nums, 10, 4);
}

TEST_F(BinarySearchTest, LargeNumbers) {
    std::vector<int> nums = {1000, 2000, 3000, 4000, 5000};
    testAllApproaches(nums, 3000, 2);
    testAllApproaches(nums, 3500, -1);
}

// Boundary Value Tests

TEST_F(BinarySearchTest, MinMaxValues) {
    std::vector<int> nums = {-10000, -5000, 0, 5000, 9999};
    testAllApproaches(nums, -10000, 0);
    testAllApproaches(nums, 9999, 4);
    testAllApproaches(nums, 0, 2);
}

// Pattern Tests

TEST_F(BinarySearchTest, ConsecutiveNumbers) {
    auto nums = createSortedArray(1, 10);
    for (int i = 1; i <= 10; ++i) {
        testAllApproaches(nums, i, i - 1);
    }
    testAllApproaches(nums, 0, -1);
    testAllApproaches(nums, 11, -1);
}

TEST_F(BinarySearchTest, EvenSpacedNumbers) {
    std::vector<int> nums = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    testAllApproaches(nums, 0, 0);
    testAllApproaches(nums, 10, 5);
    testAllApproaches(nums, 20, 10);
    testAllApproaches(nums, 5, -1);  // Odd number not in array
}

TEST_F(BinarySearchTest, PowersOfTwo) {
    std::vector<int> nums = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    testAllApproaches(nums, 1, 0);
    testAllApproaches(nums, 64, 6);
    testAllApproaches(nums, 1024, 10);
    testAllApproaches(nums, 100, -1);
}

TEST_F(BinarySearchTest, FibonacciSequence) {
    std::vector<int> nums = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    testAllApproaches(nums, 1, 0);
    testAllApproaches(nums, 21, 6);
    testAllApproaches(nums, 89, 9);
    testAllApproaches(nums, 4, -1);
}

// Large Array Tests

TEST_F(BinarySearchTest, LargeArray_Found) {
    auto nums = createSortedArray(0, 999);
    testAllApproaches(nums, 0, 0);
    testAllApproaches(nums, 500, 500);
    testAllApproaches(nums, 999, 999);
}

TEST_F(BinarySearchTest, LargeArray_NotFound) {
    std::vector<int> nums;
    for (int i = 0; i < 1000; i += 2) {  // Even numbers only
        nums.push_back(i);
    }
    
    BinarySearch solution;
    // Test odd numbers (not in array)
    EXPECT_EQ(solution.searchClassic(nums, 501), -1);
    EXPECT_EQ(solution.searchRecursive(nums, 501), -1);
    EXPECT_EQ(solution.searchBitManipulation(nums, 501), -1);
}

TEST_F(BinarySearchTest, MaximumSizeArray) {
    // Create array with 10000 elements
    auto nums = createSortedArray(0, 9999);
    
    BinarySearch solution;
    // Test various positions
    EXPECT_EQ(solution.searchClassic(nums, 0), 0);
    EXPECT_EQ(solution.searchClassic(nums, 5000), 5000);
    EXPECT_EQ(solution.searchClassic(nums, 9999), 9999);
    EXPECT_EQ(solution.searchClassic(nums, 10000), -1);
}

// Sparse Array Tests

TEST_F(BinarySearchTest, SparseArray) {
    std::vector<int> nums = {-1000, -500, -100, 0, 100, 500, 1000};
    testAllApproaches(nums, -1000, 0);
    testAllApproaches(nums, 0, 3);
    testAllApproaches(nums, 1000, 6);
    testAllApproaches(nums, 50, -1);
}

TEST_F(BinarySearchTest, ExponentialGrowth) {
    std::vector<int> nums = {1, 10, 100, 1000, 10000};
    testAllApproaches(nums, 1, 0);
    testAllApproaches(nums, 100, 2);
    testAllApproaches(nums, 10000, 4);
    testAllApproaches(nums, 5000, -1);
}

// Special Search Cases

TEST_F(BinarySearchTest, AllSameExceptTarget) {
    std::vector<int> nums = {1, 1, 1, 1, 5, 10, 10, 10, 10};
    // Note: This problem states all elements are unique, 
    // but testing behavior anyway
    std::sort(nums.begin(), nums.end());
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    // After removing duplicates: {1, 5, 10}
    testAllApproaches(nums, 5, 1);
}

TEST_F(BinarySearchTest, PrimeNumbers) {
    std::vector<int> nums = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    testAllApproaches(nums, 2, 0);
    testAllApproaches(nums, 17, 6);
    testAllApproaches(nums, 31, 10);
    testAllApproaches(nums, 15, -1);  // Not prime
}

// Stress Tests

TEST_F(BinarySearchTest, RandomizedTest) {
    // Create sorted array with random gaps
    std::vector<int> nums;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    
    int current = 0;
    for (int i = 0; i < 100; ++i) {
        nums.push_back(current);
        current += dis(gen);
    }
    
    BinarySearch solution;
    // Test existing elements
    for (size_t i = 0; i < nums.size(); ++i) {
        EXPECT_EQ(solution.searchClassic(nums, nums[i]), static_cast<int>(i));
    }
    
    // Test non-existing elements
    EXPECT_EQ(solution.searchClassic(nums, -1), -1);
    EXPECT_EQ(solution.searchClassic(nums, current + 1), -1);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode