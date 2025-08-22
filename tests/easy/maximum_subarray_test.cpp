#include <gtest/gtest.h>
#include "easy/maximum_subarray.h"
#include <climits>

using namespace leetcode::easy;

class MaximumSubarrayTest : public ::testing::Test {
protected:
    MaximumSubarray solution;
    
    void verifyAllApproaches(std::vector<int> nums, int expected) {
        auto n1 = nums, n2 = nums, n3 = nums;
        auto n4 = nums, n5 = nums, n6 = nums;
        
        EXPECT_EQ(solution.maxSubArrayBruteForce(n1), expected) 
            << "Brute Force failed";
        EXPECT_EQ(solution.maxSubArrayKadane(n2), expected) 
            << "Kadane's failed";
        EXPECT_EQ(solution.maxSubArrayDivideConquer(n3), expected) 
            << "Divide and Conquer failed";
        EXPECT_EQ(solution.maxSubArrayDP(n4), expected) 
            << "DP failed";
        EXPECT_EQ(solution.maxSubArrayPrefixSum(n5), expected) 
            << "Prefix Sum failed";
        EXPECT_EQ(solution.maxSubArrayWithIndices(n6), expected) 
            << "With Indices failed";
    }
};

TEST_F(MaximumSubarrayTest, BasicCase) {
    verifyAllApproaches({-2,1,-3,4,-1,2,1,-5,4}, 6);
}

TEST_F(MaximumSubarrayTest, SingleElement) {
    verifyAllApproaches({5}, 5);
}

TEST_F(MaximumSubarrayTest, AllNegative) {
    verifyAllApproaches({-5,-2,-8,-1,-4}, -1);
}

TEST_F(MaximumSubarrayTest, AllPositive) {
    verifyAllApproaches({1,2,3,4,5}, 15);
}

TEST_F(MaximumSubarrayTest, MixedWithZero) {
    verifyAllApproaches({-2,0,-1}, 0);
}

TEST_F(MaximumSubarrayTest, LargePositiveSum) {
    verifyAllApproaches({5,4,-1,7,8}, 23);
}

TEST_F(MaximumSubarrayTest, AlternatingPosNeg) {
    verifyAllApproaches({1,-1,1,-1,1}, 1);
}

TEST_F(MaximumSubarrayTest, SingleNegative) {
    verifyAllApproaches({-1}, -1);
}

TEST_F(MaximumSubarrayTest, TwoElements) {
    verifyAllApproaches({-2,1}, 1);
}

TEST_F(MaximumSubarrayTest, StartWithPositive) {
    verifyAllApproaches({1,-3,2,-1}, 2);
}

TEST_F(MaximumSubarrayTest, EndWithPositive) {
    verifyAllApproaches({-1,2,-3,4}, 4);
}

TEST_F(MaximumSubarrayTest, MaxAtBeginning) {
    verifyAllApproaches({6,-3,-2,-1}, 6);
}

TEST_F(MaximumSubarrayTest, MaxAtEnd) {
    verifyAllApproaches({-3,-2,-1,6}, 6);
}

TEST_F(MaximumSubarrayTest, MaxInMiddle) {
    verifyAllApproaches({-1,5,5,-3}, 10);
}

TEST_F(MaximumSubarrayTest, AllSamePositive) {
    verifyAllApproaches({3,3,3,3}, 12);
}

TEST_F(MaximumSubarrayTest, AllSameNegative) {
    verifyAllApproaches({-2,-2,-2,-2}, -2);
}

TEST_F(MaximumSubarrayTest, LargeNegativeSmallPositive) {
    verifyAllApproaches({-100,1,2,3}, 6);
}

TEST_F(MaximumSubarrayTest, SmallNegativeLargePositive) {
    verifyAllApproaches({-1,100,200}, 300);
}

TEST_F(MaximumSubarrayTest, ZeroArray) {
    verifyAllApproaches({0,0,0}, 0);
}

TEST_F(MaximumSubarrayTest, SingleZero) {
    verifyAllApproaches({0}, 0);
}

TEST_F(MaximumSubarrayTest, IncreasingSequence) {
    verifyAllApproaches({-5,-4,-3,-2,-1}, -1);
}

TEST_F(MaximumSubarrayTest, DecreasingSequence) {
    verifyAllApproaches({5,4,3,2,1}, 15);
}

TEST_F(MaximumSubarrayTest, SubarrayInMiddle) {
    verifyAllApproaches({-10,5,2,-1,3,-10}, 9);
}

TEST_F(MaximumSubarrayTest, MultipleMaxSubarrays) {
    verifyAllApproaches({1,2,-5,4,3,-2,6,1}, 12); // [4,3,-2,6,1] = 12
}

TEST_F(MaximumSubarrayTest, PrefixSuffixTest) {
    verifyAllApproaches({3,-2,5,-1,2}, 7);
}