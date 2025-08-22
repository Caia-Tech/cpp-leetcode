#include <gtest/gtest.h>
#include "easy/house_robber.h"
#include <vector>
#include <algorithm>
#include <numeric>

namespace leetcode {
namespace easy {
namespace test {

class HouseRobberTest : public ::testing::Test {
protected:
    HouseRobber solution;
    
    void testAllApproaches(std::vector<int> nums, int expected) {
        std::vector<int> nums1 = nums, nums2 = nums, nums3 = nums;
        std::vector<int> nums4 = nums, nums5 = nums, nums6 = nums;
        
        EXPECT_EQ(solution.rob(nums1), expected) 
            << "DP Array approach failed";
        EXPECT_EQ(solution.robOptimized(nums2), expected) 
            << "Space-Optimized DP approach failed";
        EXPECT_EQ(solution.robRecursive(nums3), expected) 
            << "Recursive with Memoization approach failed";
        EXPECT_EQ(solution.robEvenOdd(nums4), expected) 
            << "Even-Odd Analysis approach failed";
        EXPECT_EQ(solution.robStateMachine(nums5), expected) 
            << "State Machine approach failed";
        EXPECT_EQ(solution.robMathPattern(nums6), expected) 
            << "Mathematical Pattern approach failed";
    }
};

// Basic functionality tests
TEST_F(HouseRobberTest, SingleHouse) {
    testAllApproaches({5}, 5);
    testAllApproaches({0}, 0);
    testAllApproaches({100}, 100);
    testAllApproaches({400}, 400);
}

TEST_F(HouseRobberTest, TwoHouses) {
    testAllApproaches({1, 2}, 2);
    testAllApproaches({2, 1}, 2);
    testAllApproaches({5, 5}, 5);
    testAllApproaches({10, 20}, 20);
    testAllApproaches({100, 50}, 100);
}

TEST_F(HouseRobberTest, ThreeHouses) {
    testAllApproaches({1, 2, 3}, 4);  // Rob houses 0 and 2
    testAllApproaches({2, 1, 1}, 3);  // Rob houses 0 and 2
    testAllApproaches({5, 1, 3}, 8);  // Rob houses 0 and 2
    testAllApproaches({1, 5, 1}, 5);  // Rob house 1 only
}

TEST_F(HouseRobberTest, LeetCodeExamples) {
    testAllApproaches({1, 2, 3, 1}, 4);
    // Rob house 0 (money = 1) and house 2 (money = 3), total = 4
    
    testAllApproaches({2, 7, 9, 3, 1}, 12);
    // Rob house 0 (money = 2), house 2 (money = 9), and house 4 (money = 1), total = 12
    
    testAllApproaches({2, 1, 1, 2}, 4);
    // Rob house 0 and house 3
}

// Edge cases
TEST_F(HouseRobberTest, AllZeros) {
    testAllApproaches({0, 0, 0, 0}, 0);
    testAllApproaches({0, 0}, 0);
}

TEST_F(HouseRobberTest, AlternatingHighLow) {
    testAllApproaches({100, 1, 100, 1}, 200);  // Rob houses 0 and 2
    testAllApproaches({1, 100, 1, 100}, 200);  // Rob houses 1 and 3
    testAllApproaches({50, 1, 50, 1, 50}, 150);  // Rob houses 0, 2, and 4
}

TEST_F(HouseRobberTest, AllSameValue) {
    testAllApproaches({5, 5, 5, 5}, 10);  // Rob any two non-adjacent
    testAllApproaches({10, 10, 10}, 20);  // Rob houses 0 and 2
    testAllApproaches({7, 7, 7, 7, 7}, 21);  // Rob three houses
}

TEST_F(HouseRobberTest, IncreasingValues) {
    testAllApproaches({1, 2, 3, 4, 5}, 9);  // Rob houses 0, 2, 4
    testAllApproaches({1, 3, 5, 7, 9}, 15);  // Rob houses 0, 2, 4
    testAllApproaches({10, 20, 30, 40}, 60);  // Rob houses 0 and 2
}

TEST_F(HouseRobberTest, DecreasingValues) {
    testAllApproaches({5, 4, 3, 2, 1}, 9);  // Rob houses 0, 2, 4
    testAllApproaches({100, 50, 25, 12}, 125);  // Rob houses 0 and 2
    testAllApproaches({9, 7, 5, 3, 1}, 15);  // Rob houses 0, 2, 4
}

// Pattern-based tests
TEST_F(HouseRobberTest, SkipOnePattern) {
    // When is it better to skip just one vs multiple?
    testAllApproaches({1, 10, 1, 10, 1}, 20);  // Rob houses 1 and 3
    testAllApproaches({5, 1, 3, 9, 4}, 14);  // Rob houses 0 and 3
}

TEST_F(HouseRobberTest, LargeGapInMiddle) {
    testAllApproaches({1, 1, 100, 1, 1}, 102);  // Rob houses 0, 2, 4
    testAllApproaches({10, 1, 1, 10, 1}, 20);  // Rob houses 0, 3
    testAllApproaches({5, 2, 100, 2, 5}, 110);  // Rob houses 0, 2, 4
}

TEST_F(HouseRobberTest, BestAtEnds) {
    testAllApproaches({100, 1, 1, 1, 100}, 201);  // Rob houses 0, 2, 4
    testAllApproaches({50, 2, 3, 2, 50}, 103);  // Rob houses 0, 2, 4
}

// Complex scenarios
TEST_F(HouseRobberTest, OptimalRequiresSkipping) {
    testAllApproaches({2, 1, 1, 2, 1, 1, 2}, 6);  
    // Rob houses 0, 3, 6 or similar pattern
    
    testAllApproaches({5, 1, 2, 10, 3, 1, 20}, 35);
    // Rob houses 0, 3, 6
}

TEST_F(HouseRobberTest, MultiplePeaks) {
    testAllApproaches({1, 5, 1, 10, 1, 15, 1}, 30);
    // Rob houses 1, 3, 5
    
    testAllApproaches({3, 20, 3, 15, 3, 25, 3}, 60);
    // Rob houses 1, 3, 5
}

TEST_F(HouseRobberTest, FibonacciLikeSequence) {
    testAllApproaches({1, 1, 2, 3, 5, 8, 13}, 21);
    // Rob houses 0, 2, 4, 6: 1 + 2 + 5 + 13 = 21 or 1, 3, 5, 6: 1 + 3 + 8 + 13 = 25
    // Actually let me check: 1, 3, 6: 1 + 3 + 13 = 17 or 0, 2, 4, 6: 1 + 2 + 5 + 13 = 21
    
    testAllApproaches({1, 2, 3, 5, 8}, 12);
    // Rob houses 0, 2, 4: 1 + 3 + 8 = 12
}

// Maximum value tests
TEST_F(HouseRobberTest, MaxValues) {
    testAllApproaches({400}, 400);
    testAllApproaches({400, 400}, 400);
    testAllApproaches({400, 1, 400}, 800);
    testAllApproaches({400, 400, 400, 400}, 800);
}

// Algorithm-specific validation
TEST_F(HouseRobberTest, RecursiveMemoization) {
    // Test that memoization works correctly
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected = solution.rob(nums);
    EXPECT_EQ(solution.robRecursive(nums), expected);
}

TEST_F(HouseRobberTest, StateMachineConsistency) {
    // Verify state machine gives same results as standard DP
    std::vector<int> testCases[] = {
        {5, 3, 1, 7, 9},
        {10, 5, 2, 7, 8, 1},
        {1, 3, 1, 3, 100}
    };
    
    for (auto& nums : testCases) {
        std::vector<int> nums1 = nums, nums2 = nums;
        EXPECT_EQ(solution.rob(nums1), solution.robStateMachine(nums2));
    }
}

TEST_F(HouseRobberTest, OptimizedSpaceConsistency) {
    // Verify space-optimized version matches standard DP
    std::vector<int> nums = {2, 4, 8, 9, 9, 3, 1, 2};
    std::vector<int> nums1 = nums, nums2 = nums;
    EXPECT_EQ(solution.rob(nums1), solution.robOptimized(nums2));
}

// Stress tests
TEST_F(HouseRobberTest, LongAlternatingPattern) {
    std::vector<int> nums;
    for (int i = 0; i < 50; ++i) {
        nums.push_back(i % 2 == 0 ? 10 : 1);
    }
    testAllApproaches(nums, 250);  // Rob all even indices (25 * 10)
}

TEST_F(HouseRobberTest, LongIncreasingSequence) {
    std::vector<int> nums;
    for (int i = 1; i <= 20; ++i) {
        nums.push_back(i);
    }
    // Sum of odd positions: 1 + 3 + 5 + ... + 19 = 100
    // Sum of even positions: 2 + 4 + 6 + ... + 20 = 110
    testAllApproaches(nums, 110);
}

TEST_F(HouseRobberTest, RandomPattern) {
    testAllApproaches({3, 8, 4, 3, 7, 9, 2, 1, 8}, 28);
    // Optimal selection maximizes total
    
    testAllApproaches({10, 3, 7, 20, 3, 5, 100, 1}, 130);
    // Rob houses 0, 3, 6
}

// Special patterns
TEST_F(HouseRobberTest, TwoDistinctGroups) {
    testAllApproaches({100, 100, 1, 1, 1, 1}, 102);
    // Rob house 0 and houses 2, 4, 5 gives 100 + 1 + 1 = 102
    
    testAllApproaches({1, 1, 1, 100, 100}, 102);
    // Rob houses 0, 2, 4 or optimize for end houses
}

TEST_F(HouseRobberTest, PrimeNumbers) {
    testAllApproaches({2, 3, 5, 7, 11, 13}, 23);
    // Rob houses 1, 3, 5: 3 + 7 + 13 = 23
}

TEST_F(HouseRobberTest, PrimeNumbersCorrected) {
    std::vector<int> primes = {2, 3, 5, 7, 11, 13};
    // Rob houses 1, 3, 5: 3 + 7 + 13 = 23
    std::vector<int> nums1 = primes, nums2 = primes;
    int result = solution.rob(nums1);
    EXPECT_EQ(result, 23);
    EXPECT_EQ(solution.robOptimized(nums2), 23);
}

// Edge case: very small values
TEST_F(HouseRobberTest, SmallValues) {
    testAllApproaches({0, 1, 0, 1, 0}, 2);
    testAllApproaches({1, 0, 1, 0, 1}, 3);
    testAllApproaches({0, 0, 1, 0, 0}, 1);
}

// Mathematical pattern validation
TEST_F(HouseRobberTest, UniformValueOptimization) {
    std::vector<int> uniform(10, 5);  // 10 houses, all value 5
    testAllApproaches(uniform, 25);  // Rob 5 non-adjacent houses
    
    std::vector<int> uniform2(7, 10);  // 7 houses, all value 10
    testAllApproaches(uniform2, 40);  // Rob 4 non-adjacent houses
}

TEST_F(HouseRobberTest, PowersOfTwo) {
    testAllApproaches({1, 2, 4, 8, 16}, 21);
    // Rob houses 0, 2, 4: 1 + 4 + 16 = 21
    
    testAllApproaches({2, 4, 8, 16, 32}, 42);
    // Rob houses 0, 2, 4: 2 + 8 + 32 = 42
}

// Comprehensive coverage
TEST_F(HouseRobberTest, MixedPatterns) {
    testAllApproaches({5, 10, 5, 10, 5, 10}, 30);
    // Rob all odd indices: 10 + 10 + 10 = 30
    
    testAllApproaches({10, 5, 10, 5, 10, 5}, 30);
    // Rob all even indices: 10 + 10 + 10 = 30
    
    testAllApproaches({1, 9, 2, 8, 3, 7}, 24);
    // Rob houses 1, 3, 5: 9 + 8 + 7 = 24
}

}
}
}