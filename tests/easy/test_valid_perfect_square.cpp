#include <gtest/gtest.h>
#include "easy/valid_perfect_square.h"

using namespace leetcode::easy;

class ValidPerfectSquareTest : public ::testing::Test {
protected:
    void verifyAll(int num, bool expected) {
        ValidPerfectSquareBruteForce a1; EXPECT_EQ(a1.isPerfectSquare(num), expected);
        ValidPerfectSquareBinarySearch a2; EXPECT_EQ(a2.isPerfectSquare(num), expected);
        ValidPerfectSquareNewton a3; EXPECT_EQ(a3.isPerfectSquare(num), expected);
        ValidPerfectSquareSumOdd a4; EXPECT_EQ(a4.isPerfectSquare(num), expected);
        ValidPerfectSquareBit a5; EXPECT_EQ(a5.isPerfectSquare(num), expected);
        ValidPerfectSquareSqrt a6; EXPECT_EQ(a6.isPerfectSquare(num), expected);
    }
};

TEST_F(ValidPerfectSquareTest, PerfectSquares) {
    verifyAll(1, true);
    verifyAll(16, true);
    verifyAll(808201, true); // 899^2
    verifyAll(2147395600, true); // 46340^2
}

TEST_F(ValidPerfectSquareTest, NonSquares) {
    verifyAll(2, false);
    verifyAll(14, false);
    verifyAll(2147395600 + 1, false);
}

TEST_F(ValidPerfectSquareTest, LargePrime) {
    verifyAll(2147483647, false); // largest 32-bit int, not a square
}

