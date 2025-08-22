#include <gtest/gtest.h>
#include "medium/longest_increasing_subsequence.h"
#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {
namespace test {

class LongestIncreasingSubsequenceTest : public ::testing::Test {
protected:
    LongestIncreasingSubsequence solution;
    
    void testAllApproaches(std::vector<int> nums, int expected) {
        std::vector<int> nums1 = nums, nums2 = nums, nums3 = nums;
        std::vector<int> nums4 = nums, nums5 = nums, nums6 = nums;
        
        EXPECT_EQ(solution.lengthOfLISDP(nums1), expected) 
            << "DP approach failed for input";
        EXPECT_EQ(solution.lengthOfLISBinarySearch(nums2), expected) 
            << "Binary Search approach failed for input";
        EXPECT_EQ(solution.lengthOfLISSegmentTree(nums3), expected) 
            << "Segment Tree approach failed for input";
        EXPECT_EQ(solution.lengthOfLISFenwickTree(nums4), expected) 
            << "Fenwick Tree approach failed for input";
        EXPECT_EQ(solution.lengthOfLISStack(nums5), expected) 
            << "Stack approach failed for input";
        EXPECT_EQ(solution.lengthOfLISDivideConquer(nums6), expected) 
            << "Divide & Conquer approach failed for input";
    }
};

// Basic functionality tests
TEST_F(LongestIncreasingSubsequenceTest, SingleElement) {
    testAllApproaches({1}, 1);
    testAllApproaches({-1}, 1);
    testAllApproaches({0}, 1);
}

TEST_F(LongestIncreasingSubsequenceTest, TwoElements) {
    testAllApproaches({1, 2}, 2);
    testAllApproaches({2, 1}, 1);
    testAllApproaches({1, 1}, 1);
    testAllApproaches({-1, 0}, 2);
}

TEST_F(LongestIncreasingSubsequenceTest, StandardExample) {
    testAllApproaches({10, 9, 2, 5, 3, 7, 101, 18}, 4);
    // LIS: [2, 3, 7, 18] or [2, 3, 7, 101]
}

TEST_F(LongestIncreasingSubsequenceTest, LeetCodeExamples) {
    testAllApproaches({10, 22, 9, 33, 21, 50, 41, 60}, 5);
    // LIS: [10, 22, 33, 50, 60]
    
    testAllApproaches({0, 1, 0, 3, 2, 3}, 4);
    // LIS: [0, 1, 2, 3]
}

// Edge cases
TEST_F(LongestIncreasingSubsequenceTest, StrictlyDecreasing) {
    testAllApproaches({7, 6, 5, 4, 3, 2, 1}, 1);
    testAllApproaches({10, 9, 8, 7, 6}, 1);
}

TEST_F(LongestIncreasingSubsequenceTest, StrictlyIncreasing) {
    testAllApproaches({1, 2, 3, 4, 5, 6, 7}, 7);
    testAllApproaches({-3, -2, -1, 0, 1, 2}, 6);
}

TEST_F(LongestIncreasingSubsequenceTest, AllSameElements) {
    testAllApproaches({5, 5, 5, 5, 5}, 1);
    testAllApproaches({0, 0, 0, 0}, 1);
    testAllApproaches({-1, -1, -1}, 1);
}

TEST_F(LongestIncreasingSubsequenceTest, NegativeNumbers) {
    testAllApproaches({-10, -5, -2, 0, 3, 7}, 6);
    testAllApproaches({-7, -3, 0, 2, 5}, 5);
    testAllApproaches({-1, -2, -3, 1, 2}, 3); // LIS: [-3, 1, 2]
}

TEST_F(LongestIncreasingSubsequenceTest, MixedPositiveNegative) {
    testAllApproaches({-4, -1, 0, 3, 10, 5, 15}, 6);
    // LIS: [-4, -1, 0, 3, 10, 15]
    
    testAllApproaches({3, -1, 4, 1, 5, 9}, 4);
    // LIS: [-1, 1, 5, 9]
}

TEST_F(LongestIncreasingSubsequenceTest, DuplicatesWithIncreasing) {
    testAllApproaches({1, 3, 2, 3, 4, 5}, 5);
    // LIS: [1, 2, 3, 4, 5]
    
    testAllApproaches({4, 10, 4, 3, 8, 9}, 3);
    // LIS: [4, 8, 9] or [3, 8, 9]
}

// Pattern-based tests
TEST_F(LongestIncreasingSubsequenceTest, AlternatingPattern) {
    testAllApproaches({1, 5, 2, 6, 3, 7, 4, 8}, 5);
    // LIS: [1, 5, 6, 7, 8] or [1, 2, 6, 7, 8]
}

TEST_F(LongestIncreasingSubsequenceTest, PlateauPattern) {
    testAllApproaches({1, 2, 2, 3, 3, 3, 4}, 4);
    // LIS: [1, 2, 3, 4]
}

TEST_F(LongestIncreasingSubsequenceTest, MountainPattern) {
    testAllApproaches({1, 2, 3, 4, 5, 4, 3, 2, 1}, 5);
    // LIS: [1, 2, 3, 4, 5]
    
    testAllApproaches({3, 7, 4, 8, 5, 9, 1}, 4);
    // LIS: [3, 4, 5, 9] or [3, 7, 8, 9]
}

TEST_F(LongestIncreasingSubsequenceTest, VPattern) {
    testAllApproaches({5, 4, 3, 2, 1, 6, 7, 8}, 4);
    // LIS: [1, 6, 7, 8]
}

// Complex patterns
TEST_F(LongestIncreasingSubsequenceTest, MultipleEqualLengthLIS) {
    testAllApproaches({1, 7, 3, 9, 5, 11}, 4);
    // Multiple LIS of length 4: [1, 3, 5, 11], [1, 7, 9, 11]
}

TEST_F(LongestIncreasingSubsequenceTest, LargeGaps) {
    testAllApproaches({1, 1000, 2, 2000, 3, 3000}, 3);
    // LIS: [1, 2, 3] or [1, 1000, 2000, 3000]
}

TEST_F(LongestIncreasingSubsequenceTest, MinMaxValues) {
    testAllApproaches({-10000, 0, 10000}, 3);
    testAllApproaches({10000, -10000, 0}, 2);
    // LIS: [-10000, 0]
}

// Performance edge cases
TEST_F(LongestIncreasingSubsequenceTest, RepeatedSmallPattern) {
    std::vector<int> pattern;
    for (int i = 0; i < 20; ++i) {
        pattern.insert(pattern.end(), {1, 2, 3});
    }
    testAllApproaches(pattern, 20); // Can pick one element from each group
}

TEST_F(LongestIncreasingSubsequenceTest, LargeStrictlyIncreasing) {
    std::vector<int> increasing;
    for (int i = 1; i <= 100; ++i) {
        increasing.push_back(i);
    }
    testAllApproaches(increasing, 100);
}

TEST_F(LongestIncreasingSubsequenceTest, LargeStrictlyDecreasing) {
    std::vector<int> decreasing;
    for (int i = 100; i >= 1; --i) {
        decreasing.push_back(i);
    }
    testAllApproaches(decreasing, 1);
}

// Algorithm-specific validation tests
TEST_F(LongestIncreasingSubsequenceTest, BinarySearchEdgeCases) {
    // Test specific scenarios for binary search approach
    std::vector<int> nums = {4, 10, 4, 3, 8, 9};
    EXPECT_EQ(solution.lengthOfLISBinarySearch(nums), 3);
    
    nums = {2, 2, 2, 2};
    EXPECT_EQ(solution.lengthOfLISBinarySearch(nums), 1);
}

TEST_F(LongestIncreasingSubsequenceTest, DPConsistency) {
    // Verify DP gives same result as optimal solution
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    
    std::vector<int> nums1 = nums, nums2 = nums;
    int dpResult = solution.lengthOfLISDP(nums1);
    int bsResult = solution.lengthOfLISBinarySearch(nums2);
    
    EXPECT_EQ(dpResult, bsResult);
}

TEST_F(LongestIncreasingSubsequenceTest, TreeStructureValidation) {
    // Test segment tree and fenwick tree approaches
    std::vector<int> nums = {-1, 3, 4, 5, 2, 2, 2, 2};
    
    std::vector<int> nums1 = nums, nums2 = nums;
    int segTreeResult = solution.lengthOfLISSegmentTree(nums1);
    int fenwickResult = solution.lengthOfLISFenwickTree(nums2);
    
    EXPECT_EQ(segTreeResult, fenwickResult);
    EXPECT_EQ(segTreeResult, 4); // [-1, 3, 4, 5]
}

TEST_F(LongestIncreasingSubsequenceTest, StackApproachValidation) {
    // Verify stack approach maintains correct ordering
    std::vector<int> nums = {5, 2, 8, 6, 3, 6, 9, 7};
    
    std::vector<int> nums1 = nums, nums2 = nums;
    int stackResult = solution.lengthOfLISStack(nums1);
    int optimalResult = solution.lengthOfLISBinarySearch(nums2);
    
    EXPECT_EQ(stackResult, optimalResult);
}

TEST_F(LongestIncreasingSubsequenceTest, DivideConquerConsistency) {
    // Test divide and conquer approach for consistency
    std::vector<int> nums = {1, 4, 2, 5, 3, 6};
    
    std::vector<int> nums1 = nums, nums2 = nums;
    int dcResult = solution.lengthOfLISDivideConquer(nums1);
    int optimalResult = solution.lengthOfLISBinarySearch(nums2);
    
    EXPECT_EQ(dcResult, optimalResult);
    EXPECT_EQ(dcResult, 4); // [1, 2, 3, 6] or [1, 4, 5, 6]
}

// Stress tests
TEST_F(LongestIncreasingSubsequenceTest, RandomPatterns) {
    testAllApproaches({8, 2, 6, 1, 9, 5, 3, 7, 4}, 3); // LIS: [1, 5, 7] or [2, 6, 9]
    testAllApproaches({15, 27, 14, 38, 26, 55, 46, 65, 85}, 6);
}

TEST_F(LongestIncreasingSubsequenceTest, PowerOfTwo) {
    testAllApproaches({1, 2, 4, 8, 16, 32}, 6);
    testAllApproaches({32, 16, 8, 4, 2, 1}, 1);
}

TEST_F(LongestIncreasingSubsequenceTest, FibonacciPattern) {
    testAllApproaches({1, 1, 2, 3, 5, 8, 13}, 6);
    // LIS: [1, 2, 3, 5, 8, 13] (skip first 1)
}

}
}
}