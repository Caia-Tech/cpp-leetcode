#include <gtest/gtest.h>
#include <vector>
#include "easy/move_zeroes.h"

using namespace leetcode::easy;

class MoveZeroesTest : public ::testing::Test {
protected:
    void verifyAll(std::vector<int> input, const std::vector<int>& expected) {
        auto v1 = input; MoveZeroesTwoPointer a1; a1.moveZeroes(v1); EXPECT_EQ(v1, expected);
        auto v2 = input; MoveZeroesStablePartition a2; a2.moveZeroes(v2); EXPECT_EQ(v2, expected);
        auto v3 = input; MoveZeroesCountFill a3; a3.moveZeroes(v3); EXPECT_EQ(v3, expected);
        auto v4 = input; MoveZeroesCopyBack a4; a4.moveZeroes(v4); EXPECT_EQ(v4, expected);
        auto v5 = input; MoveZeroesQueue a5; a5.moveZeroes(v5); EXPECT_EQ(v5, expected);
        auto v6 = input; MoveZeroesRemoveFill a6; a6.moveZeroes(v6); EXPECT_EQ(v6, expected);
    }
};

TEST_F(MoveZeroesTest, MixedZeros) {
    verifyAll({0,1,0,3,12}, {1,3,12,0,0});
}

TEST_F(MoveZeroesTest, NoZeros) {
    verifyAll({1,2,3}, {1,2,3});
}

TEST_F(MoveZeroesTest, AllZeros) {
    verifyAll({0,0,0}, {0,0,0});
}

TEST_F(MoveZeroesTest, LeadingZeros) {
    verifyAll({0,0,1,2}, {1,2,0,0});
}

TEST_F(MoveZeroesTest, TrailingZeros) {
    verifyAll({1,2,0,0}, {1,2,0,0});
}

