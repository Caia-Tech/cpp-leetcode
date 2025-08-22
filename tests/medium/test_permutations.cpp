#include <gtest/gtest.h>
#include "medium/permutations.h"
#include <algorithm>
#include <set>
#include <chrono>

using namespace leetcode::medium;

class PermutationsTest : public ::testing::Test {
protected:
    Permutations solution;
    
    // Helper function to normalize results for comparison (order-independent)
    void normalizeResult(std::vector<std::vector<int>>& result) {
        for (auto& permutation : result) {
            // Individual permutations should maintain order, but we sort the collection
            // of permutations for comparison purposes
        }
        std::sort(result.begin(), result.end());
    }
    
    bool areResultsEquivalent(std::vector<std::vector<int>> result1, std::vector<std::vector<int>> result2) {
        normalizeResult(result1);
        normalizeResult(result2);
        return result1 == result2;
    }
    
    // Helper function to verify result correctness
    bool isValidPermutationSet(const std::vector<std::vector<int>>& result, const std::vector<int>& nums) {
        int n = nums.size();
        int expectedCount = 1;
        for (int i = 1; i <= n; ++i) expectedCount *= i; // n!
        
        if (result.size() != expectedCount) return false;
        
        // Convert to set to check uniqueness
        std::set<std::vector<int>> uniquePerms(result.begin(), result.end());
        if (uniquePerms.size() != result.size()) return false;
        
        // Check each permutation contains exactly the same elements as nums
        std::vector<int> sortedNums = nums;
        std::sort(sortedNums.begin(), sortedNums.end());
        
        for (const auto& perm : result) {
            if (perm.size() != nums.size()) return false;
            
            std::vector<int> sortedPerm = perm;
            std::sort(sortedPerm.begin(), sortedPerm.end());
            
            if (sortedPerm != sortedNums) return false;
        }
        
        return true;
    }
    
    // Helper function to test all approaches
    void testAllApproaches(std::vector<int> nums) {
        std::vector<int> nums1 = nums, nums2 = nums, nums3 = nums,
                        nums4 = nums, nums5 = nums, nums6 = nums;
        
        auto result1 = solution.permuteBacktracking(nums1);
        auto result2 = solution.permuteSwapping(nums2);
        auto result3 = solution.permuteNextPermutation(nums3);
        auto result4 = solution.permuteHeaps(nums4);
        auto result5 = solution.permuteIterative(nums5);
        auto result6 = solution.permuteFactorialSystem(nums6);
        
        EXPECT_TRUE(isValidPermutationSet(result1, nums)) << "Backtracking approach failed validation";
        EXPECT_TRUE(isValidPermutationSet(result2, nums)) << "Swapping approach failed validation";
        EXPECT_TRUE(isValidPermutationSet(result3, nums)) << "Next permutation approach failed validation";
        EXPECT_TRUE(isValidPermutationSet(result4, nums)) << "Heaps algorithm approach failed validation";
        EXPECT_TRUE(isValidPermutationSet(result5, nums)) << "Iterative approach failed validation";
        EXPECT_TRUE(isValidPermutationSet(result6, nums)) << "Factorial system approach failed validation";
        
        // All approaches should produce equivalent results
        EXPECT_TRUE(areResultsEquivalent(result1, result2)) << "Backtracking and Swapping differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result3)) << "Backtracking and Next Permutation differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result4)) << "Backtracking and Heaps differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result5)) << "Backtracking and Iterative differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result6)) << "Backtracking and Factorial System differ";
    }
};

TEST_F(PermutationsTest, BasicExample1) {
    // Input: nums = [1,2,3]
    // Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    std::vector<int> nums = {1, 2, 3};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, BasicExample2) {
    // Input: nums = [0,1]
    // Output: [[0,1],[1,0]]
    std::vector<int> nums = {0, 1};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, SingleElement) {
    // Input: nums = [1]
    // Output: [[1]]
    std::vector<int> nums = {1};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, TwoElements) {
    // Input: nums = [1,2]
    // Output: [[1,2],[2,1]]
    std::vector<int> nums = {1, 2};
    auto result = solution.permuteBacktracking(nums);
    
    std::vector<std::vector<int>> expected = {{1, 2}, {2, 1}};
    EXPECT_TRUE(areResultsEquivalent(result, expected));
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, NegativeNumbers) {
    // Input: nums = [-1,0,1]
    std::vector<int> nums = {-1, 0, 1};
    testAllApproaches(nums);
    
    auto result = solution.permuteBacktracking(nums);
    EXPECT_EQ(result.size(), 6); // 3! = 6
}

TEST_F(PermutationsTest, FourElements) {
    // Input: nums = [1,2,3,4]
    std::vector<int> nums = {1, 2, 3, 4};
    testAllApproaches(nums);
    
    auto result = solution.permuteBacktracking(nums);
    EXPECT_EQ(result.size(), 24); // 4! = 24
}

TEST_F(PermutationsTest, UnorderedInput) {
    // Input: nums = [3,1,2] (not sorted)
    std::vector<int> nums = {3, 1, 2};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, LargeNumbers) {
    // Input: nums = [10, -10, 5]
    std::vector<int> nums = {10, -10, 5};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, MaxSize) {
    // Test with maximum constraint size (6 elements)
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    testAllApproaches(nums);
    
    auto result = solution.permuteBacktracking(nums);
    EXPECT_EQ(result.size(), 720); // 6! = 720
}

TEST_F(PermutationsTest, MinMaxBoundaries) {
    // Test with boundary values
    std::vector<int> nums = {-10, 10};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, AllNegative) {
    // Input: nums = [-5, -2, -8]
    std::vector<int> nums = {-5, -2, -8};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, AllPositive) {
    // Input: nums = [7, 3, 9]
    std::vector<int> nums = {7, 3, 9};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, ContainsZero) {
    // Input: nums = [0, -1, 1, 2]
    std::vector<int> nums = {0, -1, 1, 2};
    testAllApproaches(nums);
    
    auto result = solution.permuteBacktracking(nums);
    EXPECT_EQ(result.size(), 24); // 4! = 24
}

TEST_F(PermutationsTest, FiveElements) {
    // Input: nums = [1, 2, 3, 4, 5]
    std::vector<int> nums = {1, 2, 3, 4, 5};
    testAllApproaches(nums);
    
    auto result = solution.permuteBacktracking(nums);
    EXPECT_EQ(result.size(), 120); // 5! = 120
}

TEST_F(PermutationsTest, ReversedOrder) {
    // Input: nums = [3, 2, 1]
    std::vector<int> nums = {3, 2, 1};
    testAllApproaches(nums);
}

TEST_F(PermutationsTest, MixedSigns) {
    // Input: nums = [-1, 2, -3, 4]
    std::vector<int> nums = {-1, 2, -3, 4};
    testAllApproaches(nums);
}

// Test uniqueness of permutations
TEST_F(PermutationsTest, UniquenessTest) {
    std::vector<int> nums = {1, 2, 3};
    auto result = solution.permuteBacktracking(nums);
    
    // Convert to set to check uniqueness
    std::set<std::vector<int>> uniquePerms(result.begin(), result.end());
    EXPECT_EQ(result.size(), uniquePerms.size()) << "Result should not contain duplicate permutations";
}

// Test that each permutation has correct length
TEST_F(PermutationsTest, PermutationLengthTest) {
    std::vector<int> nums = {5, 1, 8};
    auto result = solution.permuteBacktracking(nums);
    
    for (const auto& perm : result) {
        EXPECT_EQ(perm.size(), nums.size()) << "Each permutation should have same length as input";
    }
}

// Test that each permutation contains all original elements
TEST_F(PermutationsTest, ElementPreservationTest) {
    std::vector<int> nums = {7, -2, 4, 0};
    auto result = solution.permuteBacktracking(nums);
    
    std::vector<int> sortedNums = nums;
    std::sort(sortedNums.begin(), sortedNums.end());
    
    for (const auto& perm : result) {
        std::vector<int> sortedPerm = perm;
        std::sort(sortedPerm.begin(), sortedPerm.end());
        EXPECT_EQ(sortedPerm, sortedNums) << "Each permutation should contain exactly the same elements";
    }
}

// Test correct count of permutations
TEST_F(PermutationsTest, PermutationCountTest) {
    // Test factorial count for different sizes
    std::vector<std::vector<int>> testCases = {
        {1},           // 1! = 1
        {1, 2},        // 2! = 2
        {1, 2, 3},     // 3! = 6
        {1, 2, 3, 4}   // 4! = 24
    };
    
    std::vector<int> expectedCounts = {1, 2, 6, 24};
    
    for (int i = 0; i < testCases.size(); ++i) {
        auto result = solution.permuteBacktracking(testCases[i]);
        EXPECT_EQ(result.size(), expectedCounts[i]) 
            << "Size " << testCases[i].size() << " should have " << expectedCounts[i] << " permutations";
    }
}

// Performance test
TEST_F(PermutationsTest, PerformanceTest) {
    // Test with moderate size to ensure reasonable performance
    std::vector<int> nums = {1, 2, 3, 4, 5};
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = solution.permuteBacktracking(nums);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    EXPECT_LT(duration.count(), 50) << "Algorithm should complete within 50ms for 5 elements";
    
    EXPECT_EQ(result.size(), 120); // 5! = 120
}

// Test with maximum constraint size (performance boundary)
TEST_F(PermutationsTest, MaxSizePerformance) {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = solution.permuteBacktracking(nums);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    EXPECT_LT(duration.count(), 500) << "Algorithm should complete within 500ms for max size (6 elements)";
    
    EXPECT_EQ(result.size(), 720); // 6! = 720
}

// Test approach comparison for correctness
TEST_F(PermutationsTest, ApproachComparisonTest) {
    std::vector<int> nums = {2, 1, 3};
    
    auto backtrack = solution.permuteBacktracking(nums);
    nums = {2, 1, 3}; // Reset for next approach
    auto swapping = solution.permuteSwapping(nums);
    nums = {2, 1, 3}; // Reset for next approach
    auto nextPerm = solution.permuteNextPermutation(nums);
    
    EXPECT_TRUE(areResultsEquivalent(backtrack, swapping)) 
        << "Backtracking and swapping should produce equivalent results";
    EXPECT_TRUE(areResultsEquivalent(backtrack, nextPerm)) 
        << "Backtracking and next_permutation should produce equivalent results";
}

// Test STL next_permutation specific behavior
TEST_F(PermutationsTest, NextPermutationOrderTest) {
    std::vector<int> nums = {1, 2, 3};
    auto result = solution.permuteNextPermutation(nums);
    
    // next_permutation generates in lexicographic order
    std::vector<std::vector<int>> expected = {
        {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}
    };
    
    EXPECT_EQ(result, expected) << "Next permutation should generate in lexicographic order";
}

// Test edge case with different numeric ranges
TEST_F(PermutationsTest, NumericRangeTest) {
    // Test with values at constraint boundaries
    std::vector<int> nums = {-10, 0, 10};
    testAllApproaches(nums);
    
    auto result = solution.permuteBacktracking(nums);
    EXPECT_EQ(result.size(), 6); // 3! = 6
}

// Test factorial system approach specific verification
TEST_F(PermutationsTest, FactorialSystemVerification) {
    std::vector<int> nums = {1, 2, 3};
    auto result = solution.permuteFactorialSystem(nums);
    
    EXPECT_EQ(result.size(), 6); // 3! = 6
    EXPECT_TRUE(isValidPermutationSet(result, nums));
}