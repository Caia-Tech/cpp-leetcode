#include <gtest/gtest.h>
#include <vector>
#include "easy/plus_one.h"

using namespace leetcode::easy;

class PlusOneTest : public ::testing::Test {
protected:
    void verifyAll(const std::vector<int>& digits, const std::vector<int>& expected) {
        PlusOne s;
        auto a = digits; EXPECT_EQ(s.plusOneCarry(a), expected);
        auto b = digits; EXPECT_EQ(s.plusOneString(b), expected);
        auto c = digits; EXPECT_EQ(s.plusOneRecursive(c), expected);
        auto d = digits; EXPECT_EQ(s.plusOneSpecialCase(d), expected);
        auto e = digits; EXPECT_EQ(s.plusOneTwoPass(e), expected);
        auto f = digits; EXPECT_EQ(s.plusOneInPlace(f), expected);
    }
};

TEST_F(PlusOneTest, Simple) {
    verifyAll({1,2,3}, {1,2,4});
    verifyAll({9,9,9}, {1,0,0,0});
}

TEST_F(PlusOneTest, SingleDigit) {
    verifyAll({9}, {1,0});
    verifyAll({0}, {1});
}

