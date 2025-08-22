#include <gtest/gtest.h>
#include <vector>
#include "easy/contains_duplicate.h"

using namespace leetcode::easy;

class ContainsDuplicateTest : public ::testing::Test {
protected:
    void verifyAll(std::vector<int> nums, bool expected) {
        auto v = nums; ContainsDuplicateSort a1; EXPECT_EQ(a1.containsDuplicate(v), expected);
        ContainsDuplicateHashSet a2; EXPECT_EQ(a2.containsDuplicate(nums), expected);
        ContainsDuplicateHashMap a3; EXPECT_EQ(a3.containsDuplicate(nums), expected);
        ContainsDuplicateBitVector a4; EXPECT_EQ(a4.containsDuplicate(nums), expected);
        auto v2 = nums; ContainsDuplicateBinarySearch a5; EXPECT_EQ(a5.containsDuplicate(v2), expected);
        ContainsDuplicateSetSize a6; EXPECT_EQ(a6.containsDuplicate(nums), expected);
    }
};

TEST_F(ContainsDuplicateTest, HasDuplicates) {
    verifyAll({1,2,3,1}, true);
}

TEST_F(ContainsDuplicateTest, NoDuplicates) {
    verifyAll({1,2,3,4}, false);
}

TEST_F(ContainsDuplicateTest, NegativeNumbers) {
    verifyAll({-1,-2,-3,-1}, true);
}

TEST_F(ContainsDuplicateTest, LargeArray) {
    std::vector<int> nums;
    for(int i=0;i<1000;++i) nums.push_back(i);
    nums.push_back(500);
    verifyAll(nums, true);
}

TEST_F(ContainsDuplicateTest, SingleElement) {
    verifyAll({42}, false);
}

