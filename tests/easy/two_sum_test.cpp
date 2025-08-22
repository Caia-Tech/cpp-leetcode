#include <gtest/gtest.h>
#include "easy/two_sum.h"
#include "utils/test_utils.h"
#include <algorithm>

using namespace leetcode::easy;
using namespace leetcode::utils;

class TwoSumTest : public ::testing::Test {
protected:
    TwoSum solution;
    
    void verifyAllApproaches(const std::vector<int>& nums, int target, const std::vector<int>& expected) {
        auto result1 = solution.twoSumBruteForce(nums, target);
        auto result2 = solution.twoSumHashMapOnePass(nums, target);
        auto result3 = solution.twoSumHashMapTwoPass(nums, target);
        auto result4 = solution.twoSumSortedTwoPointers(nums, target);
        auto result5 = solution.twoSumHashSet(nums, target);
        auto result6 = solution.twoSumBinarySearch(nums, target);
        
        std::sort(result1.begin(), result1.end());
        std::sort(result2.begin(), result2.end());
        std::sort(result3.begin(), result3.end());
        std::sort(result4.begin(), result4.end());
        std::sort(result5.begin(), result5.end());
        std::sort(result6.begin(), result6.end());
        
        auto expectedSorted = expected;
        std::sort(expectedSorted.begin(), expectedSorted.end());
        
        EXPECT_EQ(result1, expectedSorted) << "Brute Force failed";
        EXPECT_EQ(result2, expectedSorted) << "Hash Map One Pass failed";
        EXPECT_EQ(result3, expectedSorted) << "Hash Map Two Pass failed";
        EXPECT_EQ(result4, expectedSorted) << "Sorted Two Pointers failed";
        EXPECT_EQ(result5, expectedSorted) << "Hash Set failed";
        EXPECT_EQ(result6, expectedSorted) << "Binary Search failed";
    }
};

TEST_F(TwoSumTest, BasicCase) {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    verifyAllApproaches(nums, target, {0, 1});
}

TEST_F(TwoSumTest, NegativeNumbers) {
    std::vector<int> nums = {-3, 4, 3, 90};
    int target = 0;
    verifyAllApproaches(nums, target, {0, 2});
}

TEST_F(TwoSumTest, DuplicateElements) {
    std::vector<int> nums = {3, 3};
    int target = 6;
    verifyAllApproaches(nums, target, {0, 1});
}

TEST_F(TwoSumTest, ZeroSum) {
    std::vector<int> nums = {0, 4, 3, 0};
    int target = 0;
    verifyAllApproaches(nums, target, {0, 3});
}

TEST_F(TwoSumTest, MinimalInput) {
    std::vector<int> nums = {1, 2};
    int target = 3;
    verifyAllApproaches(nums, target, {0, 1});
}

TEST_F(TwoSumTest, LargeNumbers) {
    std::vector<int> nums = {1000000000, -1000000000, 500000000, 300000000};
    int target = 0;
    verifyAllApproaches(nums, target, {0, 1});
}

TEST_F(TwoSumTest, FirstAndLastElements) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int target = 6;
    verifyAllApproaches(nums, target, {0, 4});
}

TEST_F(TwoSumTest, AdjacentElements) {
    std::vector<int> nums = {1, 5, 3, 4, 2};
    int target = 6;
    verifyAllApproaches(nums, target, {0, 1});
}

TEST_F(TwoSumTest, AllNegativeNumbers) {
    std::vector<int> nums = {-1, -2, -3, -4, -5};
    int target = -8;
    verifyAllApproaches(nums, target, {2, 4});
}

TEST_F(TwoSumTest, MixedPositiveNegative) {
    std::vector<int> nums = {-10, -1, 1, 3, 10};
    int target = 0;
    verifyAllApproaches(nums, target, {0, 4});
}

TEST_F(TwoSumTest, TargetIsZero) {
    std::vector<int> nums = {-5, -3, 0, 3, 5};
    int target = 0;
    verifyAllApproaches(nums, target, {0, 4});
}

TEST_F(TwoSumTest, SingleDigitNumbers) {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 17;
    verifyAllApproaches(nums, target, {7, 8});
}

TEST_F(TwoSumTest, RepeatedValuesDifferentIndices) {
    std::vector<int> nums = {5, 5, 11, 2};
    int target = 10;
    verifyAllApproaches(nums, target, {0, 1});
}

TEST_F(TwoSumTest, LargeArraySmallTarget) {
    std::vector<int> nums = {100, 200, 300, 1, 2, 400};
    int target = 3;
    verifyAllApproaches(nums, target, {3, 4});
}

TEST_F(TwoSumTest, ConsecutiveNumbers) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int target = 9;
    verifyAllApproaches(nums, target, {3, 4});
}

TEST_F(TwoSumTest, PowersOfTwo) {
    std::vector<int> nums = {1, 2, 4, 8, 16, 32};
    int target = 48;
    verifyAllApproaches(nums, target, {4, 5});
}

TEST_F(TwoSumTest, FibonacciSequence) {
    std::vector<int> nums = {1, 1, 2, 3, 5, 8, 13};
    int target = 21;
    verifyAllApproaches(nums, target, {5, 6});
}

TEST_F(TwoSumTest, PrimeNumbers) {
    std::vector<int> nums = {2, 3, 5, 7, 11, 13};
    int target = 18;
    verifyAllApproaches(nums, target, {2, 5});
}

TEST_F(TwoSumTest, SquareNumbers) {
    std::vector<int> nums = {1, 4, 9, 16, 25, 36};
    int target = 45;
    verifyAllApproaches(nums, target, {2, 5});
}

TEST_F(TwoSumTest, AlternatingPositiveNegative) {
    std::vector<int> nums = {1, -1, 2, -2, 3, -3};
    int target = 0;
    verifyAllApproaches(nums, target, {0, 1});
}

TEST_F(TwoSumTest, ExtremeBoundaryValues) {
    std::vector<int> nums = {-1000000000, 0, 1000000000};
    int target = 0;
    verifyAllApproaches(nums, target, {0, 2});
}

TEST_F(TwoSumTest, AllSameExceptTwo) {
    std::vector<int> nums = {5, 5, 5, 5, 3, 7};
    int target = 10;
    verifyAllApproaches(nums, target, {4, 5});
}

TEST_F(TwoSumTest, DescendingOrder) {
    std::vector<int> nums = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int target = 11;
    verifyAllApproaches(nums, target, {0, 9});
}

TEST_F(TwoSumTest, RandomUnsortedArray) {
    std::vector<int> nums = {15, 7, 23, 4, 11, 9, 31, 2};
    int target = 13;
    verifyAllApproaches(nums, target, {3, 5});
}