#include <gtest/gtest.h>
#include <vector>
#include "easy/majority_element.h"

using namespace leetcode::easy;

class MajorityElementTest : public ::testing::Test {
protected:
    void testAll(std::vector<int> nums, int expected) {
        std::vector<int> copy;
        copy = nums; MajorityElementSort a1; EXPECT_EQ(a1.majorityElement(copy), expected);
        copy = nums; MajorityElementHashMap a2; EXPECT_EQ(a2.majorityElement(copy), expected);
        copy = nums; MajorityElementRandomized a3; EXPECT_EQ(a3.majorityElement(copy), expected);
        copy = nums; MajorityElementDivideConquer a4; EXPECT_EQ(a4.majorityElement(copy), expected);
        copy = nums; MajorityElementBit a5; EXPECT_EQ(a5.majorityElement(copy), expected);
        copy = nums; MajorityElementBoyerMoore a6; EXPECT_EQ(a6.majorityElement(copy), expected);
    }
};

TEST_F(MajorityElementTest, Basic) {
    testAll({3,2,3}, 3);
}

TEST_F(MajorityElementTest, Mixed) {
    testAll({2,2,1,1,1,2,2}, 2);
}

TEST_F(MajorityElementTest, SingleElement) {
    testAll({1}, 1);
}

TEST_F(MajorityElementTest, AllSame) {
    testAll({5,5,5,5}, 5);
}

TEST_F(MajorityElementTest, NegativeNumbers) {
    testAll({-1,-1,-1,2}, -1);
}

TEST_F(MajorityElementTest, MajorityAtEnd) {
    testAll({4,4,2,4,2,4,4}, 4);
}

TEST_F(MajorityElementTest, LargeArray) {
    std::vector<int> nums(100, 7);
    nums[0] = 3; nums[1] = 3; nums[2] = 3; // still majority 7
    testAll(nums, 7);
}

TEST_F(MajorityElementTest, TwoCandidates) {
    testAll({1,2,1,2,1,2,1}, 1);
}

