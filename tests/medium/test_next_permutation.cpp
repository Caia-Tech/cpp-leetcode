#include <gtest/gtest.h>
#include "medium/next_permutation.h"

using namespace leetcode::medium;

class NextPermutationTest : public ::testing::Test {
protected:
    NextPermutation solution;
    
    // Helper function to test all approaches
    void testAllApproaches(std::vector<int> input, const std::vector<int>& expected) {
        std::vector<int> nums1 = input, nums2 = input, nums3 = input, 
                        nums4 = input, nums5 = input, nums6 = input;
        
        solution.nextPermutationStandard(nums1);
        EXPECT_EQ(nums1, expected) << "Standard approach failed";
        
        solution.nextPermutationSTL(nums2);
        EXPECT_EQ(nums2, expected) << "STL approach failed";
        
        solution.nextPermutationRecursive(nums3);
        EXPECT_EQ(nums3, expected) << "Recursive approach failed";
        
        solution.nextPermutationDigitIncrement(nums4);
        EXPECT_EQ(nums4, expected) << "Digit increment approach failed";
        
        solution.nextPermutationTwoPointers(nums5);
        EXPECT_EQ(nums5, expected) << "Two pointers approach failed";
        
        solution.nextPermutationSegmentBased(nums6);
        EXPECT_EQ(nums6, expected) << "Segment-based approach failed";
    }
};

TEST_F(NextPermutationTest, BasicExample1) {
    // Input: [1,2,3] -> Output: [1,3,2]
    std::vector<int> input = {1, 2, 3};
    std::vector<int> expected = {1, 3, 2};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, BasicExample2) {
    // Input: [3,2,1] -> Output: [1,2,3] (largest permutation wraps to smallest)
    std::vector<int> input = {3, 2, 1};
    std::vector<int> expected = {1, 2, 3};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, BasicExample3) {
    // Input: [1,1,5] -> Output: [1,5,1]
    std::vector<int> input = {1, 1, 5};
    std::vector<int> expected = {1, 5, 1};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, SingleElement) {
    // Input: [1] -> Output: [1] (only one permutation)
    std::vector<int> input = {1};
    std::vector<int> expected = {1};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, TwoElements) {
    // Input: [1,2] -> Output: [2,1]
    std::vector<int> input = {1, 2};
    std::vector<int> expected = {2, 1};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, TwoElementsReversed) {
    // Input: [2,1] -> Output: [1,2] (largest wraps to smallest)
    std::vector<int> input = {2, 1};
    std::vector<int> expected = {1, 2};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, AllSameElements) {
    // Input: [1,1,1] -> Output: [1,1,1] (no next permutation)
    std::vector<int> input = {1, 1, 1};
    std::vector<int> expected = {1, 1, 1};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, LargerExample) {
    // Input: [1,2,3,4] -> Output: [1,2,4,3]
    std::vector<int> input = {1, 2, 3, 4};
    std::vector<int> expected = {1, 2, 4, 3};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, ComplexCase1) {
    // Input: [1,3,2] -> Output: [2,1,3]
    std::vector<int> input = {1, 3, 2};
    std::vector<int> expected = {2, 1, 3};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, ComplexCase2) {
    // Input: [2,3,1] -> Output: [3,1,2]
    std::vector<int> input = {2, 3, 1};
    std::vector<int> expected = {3, 1, 2};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, WithDuplicates1) {
    // Input: [1,5,1] -> Output: [5,1,1]
    std::vector<int> input = {1, 5, 1};
    std::vector<int> expected = {5, 1, 1};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, WithDuplicates2) {
    // Input: [2,2,3] -> Output: [2,3,2]
    std::vector<int> input = {2, 2, 3};
    std::vector<int> expected = {2, 3, 2};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, LongerSequence) {
    // Input: [1,2,3,4,5] -> Output: [1,2,3,5,4]
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 5, 4};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, DescendingSequence) {
    // Input: [5,4,3,2,1] -> Output: [1,2,3,4,5] (largest to smallest)
    std::vector<int> input = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, MixedWithDuplicates) {
    // Input: [1,3,2,2] -> Output: [2,1,2,3]
    std::vector<int> input = {1, 3, 2, 2};
    std::vector<int> expected = {2, 1, 2, 3};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, EdgeCaseZeros) {
    // Input: [0,1,2] -> Output: [0,2,1]
    std::vector<int> input = {0, 1, 2};
    std::vector<int> expected = {0, 2, 1};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, LargeNumbers) {
    // Input: [97,98,99] -> Output: [97,99,98]
    std::vector<int> input = {97, 98, 99};
    std::vector<int> expected = {97, 99, 98};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, PivotAtBeginning) {
    // Input: [1,4,3,2] -> Output: [2,1,3,4]
    std::vector<int> input = {1, 4, 3, 2};
    std::vector<int> expected = {2, 1, 3, 4};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, MultipleDuplicates) {
    // Input: [2,2,2,1] -> Output: [1,2,2,2]
    std::vector<int> input = {2, 2, 2, 1};
    std::vector<int> expected = {1, 2, 2, 2};
    testAllApproaches(input, expected);
}

TEST_F(NextPermutationTest, AlternatingPattern) {
    // Input: [1,3,2,4] -> Output: [1,4,2,3]
    std::vector<int> input = {1, 3, 2, 4};
    std::vector<int> expected = {1, 4, 2, 3};
    testAllApproaches(input, expected);
}

// Performance test for larger inputs
TEST_F(NextPermutationTest, PerformanceTest) {
    // Test with larger array to ensure O(n) performance
    std::vector<int> input;
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i);
    }
    
    // Expected: increment last two elements [1,2,...,48,50,49]
    std::vector<int> expected = input;
    std::swap(expected[48], expected[49]);
    
    auto start = std::chrono::high_resolution_clock::now();
    solution.nextPermutationStandard(input);
    auto end = std::chrono::high_resolution_clock::now();
    
    EXPECT_EQ(input, expected);
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 1000) << "Algorithm should complete in under 1ms for size 50";
}

// Test edge cases with boundary values
TEST_F(NextPermutationTest, BoundaryValues) {
    // Test with constraint boundary values (0 <= nums[i] <= 100)
    std::vector<int> input = {0, 100};
    std::vector<int> expected = {100, 0};
    testAllApproaches(input, expected);
}

// Test correctness of lexicographical ordering
TEST_F(NextPermutationTest, LexicographicalCorrectness) {
    std::vector<int> current = {1, 2, 3};
    std::vector<std::vector<int>> allPermutations;
    
    // Generate all permutations using our algorithm
    do {
        allPermutations.push_back(current);
        solution.nextPermutationStandard(current);
    } while (current != std::vector<int>{1, 2, 3}); // Stop when we cycle back
    
    // Verify we have all 6 permutations of [1,2,3]
    EXPECT_EQ(allPermutations.size(), 6);
    
    // Verify they're in lexicographical order
    for (int i = 1; i < allPermutations.size(); ++i) {
        EXPECT_LT(allPermutations[i-1], allPermutations[i]) 
            << "Permutations should be in lexicographical order";
    }
}