#include <gtest/gtest.h>
#include <vector>
#include "easy/squares_of_a_sorted_array.h"

using namespace leetcode::easy;

class SortedSquaresTest : public ::testing::Test {
protected:
    void verifyAll(const std::vector<int>& nums, const std::vector<int>& expected) {
        SortedSquares s;
        EXPECT_EQ(s.squareAndSort(nums), expected);
        EXPECT_EQ(s.twoPointers(nums), expected);
        EXPECT_EQ(s.splitAndMerge(nums), expected);
        EXPECT_EQ(s.heapApproach(nums), expected);
        EXPECT_EQ(s.dequeApproach(nums), expected);
        EXPECT_EQ(s.countingMap(nums), expected);
    }
};

TEST_F(SortedSquaresTest, MixedValues) {
    verifyAll({-4,-1,0,3,10}, {0,1,9,16,100});
}

TEST_F(SortedSquaresTest, NegativeValues) {
    verifyAll({-7,-3,-1}, {1,9,49});
}

TEST_F(SortedSquaresTest, PositiveValues) {
    verifyAll({1,2,3}, {1,4,9});
}

TEST_F(SortedSquaresTest, SingleValue) {
    verifyAll({0}, {0});
}

