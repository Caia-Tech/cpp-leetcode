#include <gtest/gtest.h>
#include <vector>
#include "easy/single_number.h"

using namespace leetcode::easy;

class SingleNumberTest : public ::testing::Test {
protected:
    void verifyAll(std::vector<int> nums, int expected) {
        auto v = nums; SingleNumberSort a1; EXPECT_EQ(a1.singleNumber(v), expected);
        v = nums; SingleNumberHashMap a2; EXPECT_EQ(a2.singleNumber(v), expected);
        v = nums; SingleNumberXOR a3; EXPECT_EQ(a3.singleNumber(v), expected);
        v = nums; SingleNumberBitCount a4; EXPECT_EQ(a4.singleNumber(v), expected);
        v = nums; SingleNumberMath a5; EXPECT_EQ(a5.singleNumber(v), expected);
        v = nums; SingleNumberSetToggle a6; EXPECT_EQ(a6.singleNumber(v), expected);
    }
};

TEST_F(SingleNumberTest, Basic) {
    verifyAll({2,2,1}, 1);
}

TEST_F(SingleNumberTest, Larger) {
    verifyAll({4,1,2,1,2}, 4);
}

TEST_F(SingleNumberTest, Negative) {
    verifyAll({-1,-1,-2}, -2);
}

TEST_F(SingleNumberTest, SingleElement) {
    verifyAll({7}, 7);
}

TEST_F(SingleNumberTest, MixedSigns) {
    verifyAll({0,1,0,-1,1}, -1);
}

TEST_F(SingleNumberTest, LargeArray) {
    std::vector<int> nums; nums.reserve(2001);
    for(int i=1;i<=1000;++i){ nums.push_back(i); nums.push_back(i); }
    nums.push_back(9999);
    verifyAll(nums, 9999);
}

