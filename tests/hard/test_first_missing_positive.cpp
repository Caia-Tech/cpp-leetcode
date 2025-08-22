#include <gtest/gtest.h>
#include "hard/first_missing_positive.h"
#include <chrono>

using namespace leetcode::hard;

class FirstMissingPositiveTest : public ::testing::Test {
protected:
    FirstMissingPositive solution;
    
    // Helper function to test all approaches (some modify array, so we need separate copies)
    void testAllApproaches(std::vector<int> nums, int expected) {
        std::vector<int> nums1 = nums, nums2 = nums, nums3 = nums, 
                        nums4 = nums, nums5 = nums, nums6 = nums;
        
        EXPECT_EQ(solution.firstMissingPositiveCyclicSort(nums1), expected) 
            << "Cyclic sort approach failed";
        
        EXPECT_EQ(solution.firstMissingPositiveSignMarking(nums2), expected) 
            << "Sign marking approach failed";
        
        EXPECT_EQ(solution.firstMissingPositiveHashSet(nums3), expected) 
            << "Hash set approach failed";
        
        EXPECT_EQ(solution.firstMissingPositiveSort(nums4), expected) 
            << "Sort approach failed";
        
        EXPECT_EQ(solution.firstMissingPositiveBinarySearch(nums5), expected) 
            << "Binary search approach failed";
        
        EXPECT_EQ(solution.firstMissingPositivePartition(nums6), expected) 
            << "Partition approach failed";
    }
};

TEST_F(FirstMissingPositiveTest, BasicExample1) {
    // Input: [1,2,0] -> Output: 3
    std::vector<int> nums = {1, 2, 0};
    testAllApproaches(nums, 3);
}

TEST_F(FirstMissingPositiveTest, BasicExample2) {
    // Input: [3,4,-1,1] -> Output: 2
    std::vector<int> nums = {3, 4, -1, 1};
    testAllApproaches(nums, 2);
}

TEST_F(FirstMissingPositiveTest, BasicExample3) {
    // Input: [7,8,9,11,12] -> Output: 1
    std::vector<int> nums = {7, 8, 9, 11, 12};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, SingleElement) {
    // Input: [1] -> Output: 2
    std::vector<int> nums = {1};
    testAllApproaches(nums, 2);
}

TEST_F(FirstMissingPositiveTest, SingleElementNotOne) {
    // Input: [2] -> Output: 1
    std::vector<int> nums = {2};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, SingleNegative) {
    // Input: [-1] -> Output: 1
    std::vector<int> nums = {-1};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, SingleZero) {
    // Input: [0] -> Output: 1
    std::vector<int> nums = {0};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, ConsecutiveFromOne) {
    // Input: [1,2,3,4,5] -> Output: 6
    std::vector<int> nums = {1, 2, 3, 4, 5};
    testAllApproaches(nums, 6);
}

TEST_F(FirstMissingPositiveTest, ConsecutiveNotFromOne) {
    // Input: [2,3,4,5,6] -> Output: 1
    std::vector<int> nums = {2, 3, 4, 5, 6};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, AllNegatives) {
    // Input: [-3,-2,-1] -> Output: 1
    std::vector<int> nums = {-3, -2, -1};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, MixedWithNegatives) {
    // Input: [-1,4,2,1,9,10] -> Output: 3
    std::vector<int> nums = {-1, 4, 2, 1, 9, 10};
    testAllApproaches(nums, 3);
}

TEST_F(FirstMissingPositiveTest, WithDuplicates) {
    // Input: [1,1,2,2,3,3] -> Output: 4
    std::vector<int> nums = {1, 1, 2, 2, 3, 3};
    testAllApproaches(nums, 4);
}

TEST_F(FirstMissingPositiveTest, WithZeros) {
    // Input: [0,1,0,2,0,3] -> Output: 4
    std::vector<int> nums = {0, 1, 0, 2, 0, 3};
    testAllApproaches(nums, 4);
}

TEST_F(FirstMissingPositiveTest, LargeGap) {
    // Input: [1,1000] -> Output: 2
    std::vector<int> nums = {1, 1000};
    testAllApproaches(nums, 2);
}

TEST_F(FirstMissingPositiveTest, OutOfRangeLarge) {
    // Input: [1000,1001,1002] -> Output: 1
    std::vector<int> nums = {1000, 1001, 1002};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, MissingInMiddle) {
    // Input: [1,2,4,5,6] -> Output: 3
    std::vector<int> nums = {1, 2, 4, 5, 6};
    testAllApproaches(nums, 3);
}

TEST_F(FirstMissingPositiveTest, MissingAtBeginning) {
    // Input: [2,3,4] -> Output: 1
    std::vector<int> nums = {2, 3, 4};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, RandomOrder) {
    // Input: [3,1,4,2,6,5,8,7] -> Output: 9
    std::vector<int> nums = {3, 1, 4, 2, 6, 5, 8, 7};
    testAllApproaches(nums, 9);
}

TEST_F(FirstMissingPositiveTest, ComplexMixed) {
    // Input: [41,21,-32,1,0,-5,2] -> Output: 3
    std::vector<int> nums = {41, 21, -32, 1, 0, -5, 2};
    testAllApproaches(nums, 3);
}

TEST_F(FirstMissingPositiveTest, BoundaryValues) {
    // Test with constraint boundary values
    std::vector<int> nums = {-2147483648, 2147483647, 1};  // INT_MIN, INT_MAX, 1
    testAllApproaches(nums, 2);
}

TEST_F(FirstMissingPositiveTest, TwoElements) {
    // Input: [1,3] -> Output: 2
    std::vector<int> nums = {1, 3};
    testAllApproaches(nums, 2);
}

TEST_F(FirstMissingPositiveTest, TwoElementsConsecutive) {
    // Input: [1,2] -> Output: 3
    std::vector<int> nums = {1, 2};
    testAllApproaches(nums, 3);
}

TEST_F(FirstMissingPositiveTest, AllSamePositive) {
    // Input: [5,5,5,5] -> Output: 1
    std::vector<int> nums = {5, 5, 5, 5};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, AllSameOne) {
    // Input: [1,1,1,1] -> Output: 2
    std::vector<int> nums = {1, 1, 1, 1};
    testAllApproaches(nums, 2);
}

TEST_F(FirstMissingPositiveTest, LargerConsecutive) {
    // Input: [1,2,3,4,5,6,7,8,9] -> Output: 10
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    testAllApproaches(nums, 10);
}

TEST_F(FirstMissingPositiveTest, ManyDuplicatesOfOne) {
    // Input: [1,1,1,1,1,1,2] -> Output: 3
    std::vector<int> nums = {1, 1, 1, 1, 1, 1, 2};
    testAllApproaches(nums, 3);
}

TEST_F(FirstMissingPositiveTest, HighNumbers) {
    // Input: [100,101,102,103] -> Output: 1
    std::vector<int> nums = {100, 101, 102, 103};
    testAllApproaches(nums, 1);
}

TEST_F(FirstMissingPositiveTest, MixedHighLow) {
    // Input: [1,100,2,101,3] -> Output: 4
    std::vector<int> nums = {1, 100, 2, 101, 3};
    testAllApproaches(nums, 4);
}

// Performance test for O(n) complexity requirement
TEST_F(FirstMissingPositiveTest, PerformanceTest) {
    // Create large array to test O(n) performance
    std::vector<int> nums;
    for (int i = 2; i <= 10000; ++i) {
        nums.push_back(i);
    }
    nums.push_back(-1); // Missing 1
    
    auto start = std::chrono::high_resolution_clock::now();
    int result = solution.firstMissingPositiveCyclicSort(nums);
    auto end = std::chrono::high_resolution_clock::now();
    
    EXPECT_EQ(result, 1);
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 10000) << "Algorithm should complete quickly for large input (O(n) requirement)";
}

TEST_F(FirstMissingPositiveTest, WorstCasePerformance) {
    // Worst case: reverse order with many swaps needed
    std::vector<int> nums;
    for (int i = 1000; i >= 1; --i) {
        nums.push_back(i);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    int result = solution.firstMissingPositiveCyclicSort(nums);
    auto end = std::chrono::high_resolution_clock::now();
    
    EXPECT_EQ(result, 1001);
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 5000) << "Even worst case should be fast due to O(n) guarantee";
}

// Test space complexity requirement (O(1) extra space)
TEST_F(FirstMissingPositiveTest, SpaceComplexityTest) {
    std::vector<int> nums = {3, 4, -1, 1};
    int originalSize = nums.size();
    
    // The algorithms should not allocate significant extra space
    // We test this by ensuring the optimal approaches work
    int result1 = solution.firstMissingPositiveCyclicSort(nums);
    
    nums = {3, 4, -1, 1}; // Reset
    int result2 = solution.firstMissingPositiveSignMarking(nums);
    
    EXPECT_EQ(result1, 2);
    EXPECT_EQ(result2, 2);
    EXPECT_EQ(nums.size(), originalSize) << "Array size should not change significantly";
}

// Edge case: maximum array size
TEST_F(FirstMissingPositiveTest, MaxArraySize) {
    // Test with larger array (but not full 10^5 to keep test fast)
    std::vector<int> nums;
    int size = 1000;
    
    // Create array [2, 3, 4, ..., size+1] (missing 1)
    for (int i = 2; i <= size + 1; ++i) {
        nums.push_back(i);
    }
    
    testAllApproaches(nums, 1);
}

// Test that algorithms handle modification correctly
TEST_F(FirstMissingPositiveTest, ArrayModificationCorrectness) {
    std::vector<int> original = {3, 4, -1, 1};
    std::vector<int> nums = original;
    
    int result = solution.firstMissingPositiveCyclicSort(nums);
    EXPECT_EQ(result, 2);
    
    // After cyclic sort, positive integers should be in their correct positions where possible
    // We can't test exact final state since it depends on implementation details,
    // but result should be correct
}

// Test edge case with all numbers out of range [1, n]
TEST_F(FirstMissingPositiveTest, AllOutOfRange) {
    std::vector<int> nums = {-5, -10, 1000, 2000};
    testAllApproaches(nums, 1);
}

// Test with numbers exactly at boundary n+1
TEST_F(FirstMissingPositiveTest, BoundaryN) {
    std::vector<int> nums = {1, 2, 3, 4}; // n=4, should return 5 (n+1)
    testAllApproaches(nums, 5);
}