#include <gtest/gtest.h>
#include "medium/three_sum.h"
#include "utils/test_utils.h"
#include <algorithm>
#include <set>

using namespace leetcode::medium;
using namespace leetcode::utils;

class ThreeSumTest : public ::testing::Test {
protected:
    ThreeSum solution;
    
    bool compareResults(std::vector<std::vector<int>> result1, 
                       std::vector<std::vector<int>> result2) {
        if (result1.size() != result2.size()) return false;
        
        std::set<std::vector<int>> set1, set2;
        for (auto& triplet : result1) {
            std::sort(triplet.begin(), triplet.end());
            set1.insert(triplet);
        }
        for (auto& triplet : result2) {
            std::sort(triplet.begin(), triplet.end());
            set2.insert(triplet);
        }
        
        return set1 == set2;
    }
    
    void verifyAllApproaches(std::vector<int> nums, 
                           std::vector<std::vector<int>> expected) {
        auto nums1 = nums, nums2 = nums, nums3 = nums;
        auto nums4 = nums, nums5 = nums, nums6 = nums;
        
        auto result1 = solution.threeSumBruteForce(nums1);
        auto result2 = solution.threeSumTwoPointers(nums2);
        auto result3 = solution.threeSumHashSet(nums3);
        auto result4 = solution.threeSumHashMap(nums4);
        auto result5 = solution.threeSumBinarySearch(nums5);
        auto result6 = solution.threeSumOptimized(nums6);
        
        EXPECT_TRUE(compareResults(result1, expected)) << "Brute Force failed";
        EXPECT_TRUE(compareResults(result2, expected)) << "Two Pointers failed";
        EXPECT_TRUE(compareResults(result3, expected)) << "Hash Set failed";
        EXPECT_TRUE(compareResults(result4, expected)) << "Hash Map failed";
        EXPECT_TRUE(compareResults(result5, expected)) << "Binary Search failed";
        EXPECT_TRUE(compareResults(result6, expected)) << "Optimized failed";
    }
};

TEST_F(ThreeSumTest, BasicCase) {
    verifyAllApproaches({-1, 0, 1, 2, -1, -4}, 
                       {{-1, -1, 2}, {-1, 0, 1}});
}

TEST_F(ThreeSumTest, NoSolution) {
    verifyAllApproaches({0, 1, 1}, {});
}

TEST_F(ThreeSumTest, AllZeros) {
    verifyAllApproaches({0, 0, 0}, {{0, 0, 0}});
}

TEST_F(ThreeSumTest, MinimalInput) {
    verifyAllApproaches({0, 0, 0, 0}, {{0, 0, 0}});
}

TEST_F(ThreeSumTest, SingleSolution) {
    verifyAllApproaches({-2, 0, 1, 1, 2}, {{-2, 0, 2}, {-2, 1, 1}});
}

TEST_F(ThreeSumTest, AllNegative) {
    verifyAllApproaches({-5, -4, -3, -2, -1}, {});
}

TEST_F(ThreeSumTest, AllPositive) {
    verifyAllApproaches({1, 2, 3, 4, 5}, {});
}

TEST_F(ThreeSumTest, MixedWithZero) {
    verifyAllApproaches({-1, 0, 1}, {{-1, 0, 1}});
}

TEST_F(ThreeSumTest, MultipleDuplicates) {
    verifyAllApproaches({-2, 0, 0, 2, 2}, {{-2, 0, 2}});
}

TEST_F(ThreeSumTest, LargeRange) {
    verifyAllApproaches({-4, -2, -1, 0, 1, 2, 4}, 
                       {{-4, 0, 4}, {-2, 0, 2}, {-2, -1, 3}, {-1, 0, 1}});
}

TEST_F(ThreeSumTest, ConsecutiveNumbers) {
    verifyAllApproaches({-3, -2, -1, 0, 1, 2, 3}, 
                       {{-3, 0, 3}, {-3, 1, 2}, {-2, -1, 3}, {-2, 0, 2}, {-1, 0, 1}});
}

TEST_F(ThreeSumTest, TwoElements) {
    verifyAllApproaches({1, -1}, {});
}

TEST_F(ThreeSumTest, ThreeElementsNoSolution) {
    verifyAllApproaches({1, 2, 3}, {});
}

TEST_F(ThreeSumTest, SymmetricArray) {
    verifyAllApproaches({-3, -1, 0, 1, 3}, {{-3, 0, 3}, {-1, 0, 1}});
}

TEST_F(ThreeSumTest, RepeatingPattern) {
    verifyAllApproaches({1, -1, 1, -1}, {{-1, -1, 2}, {-1, 0, 1}});
}

TEST_F(ThreeSumTest, SingleNegativeMultiplePositive) {
    verifyAllApproaches({-4, 1, 1, 1, 1, 2, 2}, {{-4, 2, 2}});
}

TEST_F(ThreeSumTest, AlternatingPositiveNegative) {
    verifyAllApproaches({1, -1, 2, -2, 3, -3}, 
                       {{-3, 1, 2}, {-2, -1, 3}});
}

TEST_F(ThreeSumTest, LargeNumbers) {
    verifyAllApproaches({100, -50, -50, 25, 25}, {{-50, -50, 100}});
}

TEST_F(ThreeSumTest, SmallNumbers) {
    verifyAllApproaches({-1, -1, 0, 1, 1}, {{-1, 0, 1}});
}

TEST_F(ThreeSumTest, ManyZeros) {
    verifyAllApproaches({0, 0, 0, 0, 0}, {{0, 0, 0}});
}

TEST_F(ThreeSumTest, ComplexMixed) {
    verifyAllApproaches({-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6},
                       {{-4, -2, 6}, {-4, 0, 4}, {-4, 1, 3}, {-4, 2, 2}, 
                        {-2, -2, 4}, {-2, 0, 2}});
}

TEST_F(ThreeSumTest, EdgeCaseNegative) {
    verifyAllApproaches({-1, -1, 2}, {{-1, -1, 2}});
}

TEST_F(ThreeSumTest, EdgeCasePositive) {
    verifyAllApproaches({1, 1, -2}, {{-2, 1, 1}});
}

TEST_F(ThreeSumTest, LongSequence) {
    verifyAllApproaches({-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5},
                       {{-5, 0, 5}, {-5, 1, 4}, {-5, 2, 3}, 
                        {-4, -1, 5}, {-4, 0, 4}, {-4, 1, 3}, 
                        {-3, -2, 5}, {-3, -1, 4}, {-3, 0, 3}, {-3, 1, 2},
                        {-2, -1, 3}, {-2, 0, 2}, {-1, 0, 1}});
}