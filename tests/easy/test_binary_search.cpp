#include <gtest/gtest.h>
#include <vector>
#include "easy/binary_search.h"

using namespace leetcode::easy;

class BinarySearchTest : public ::testing::Test {
protected:
    void verifyAll(const std::vector<int>& nums, int target, int expected) {
        BinarySearchIterative a1; EXPECT_EQ(a1.search(nums, target), expected);
        BinarySearchRecursive a2; EXPECT_EQ(a2.search(nums, target), expected);
        BinarySearchLowerBound a3; EXPECT_EQ(a3.search(nums, target), expected);
        BinarySearchStdBinarySearch a4; EXPECT_EQ(a4.search(nums, target), expected);
        BinarySearchHalfOpen a5; EXPECT_EQ(a5.search(nums, target), expected);
        BinarySearchBitwiseMid a6; EXPECT_EQ(a6.search(nums, target), expected);
    }
};

TEST_F(BinarySearchTest, TargetExists) {
    std::vector<int> nums{1,3,5,7,9};
    verifyAll(nums, 7, 3);
}

TEST_F(BinarySearchTest, TargetAbsent) {
    std::vector<int> nums{1,3,5,7,9};
    verifyAll(nums, 6, -1);
}

TEST_F(BinarySearchTest, FirstElement) {
    std::vector<int> nums{2,4,6,8};
    verifyAll(nums, 2, 0);
}

TEST_F(BinarySearchTest, LastElement) {
    std::vector<int> nums{2,4,6,8};
    verifyAll(nums, 8, 3);
}

TEST_F(BinarySearchTest, SingleElement) {
    std::vector<int> nums{5};
    verifyAll(nums, 5, 0);
    verifyAll(nums, -1, -1);
}

