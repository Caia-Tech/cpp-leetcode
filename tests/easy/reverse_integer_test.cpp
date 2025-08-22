#include <gtest/gtest.h>
#include "easy/reverse_integer.h"
#include <climits>

using namespace leetcode::easy;

class ReverseIntegerTest : public ::testing::Test {
protected:
    ReverseInteger solution;
    
    void verifyAllApproaches(int input, int expected) {
        EXPECT_EQ(solution.reverseMath(input), expected) << "Math approach failed for input: " << input;
        EXPECT_EQ(solution.reverseString(input), expected) << "String approach failed for input: " << input;
        EXPECT_EQ(solution.reverseLong(input), expected) << "Long approach failed for input: " << input;
        EXPECT_EQ(solution.reverseArray(input), expected) << "Array approach failed for input: " << input;
        EXPECT_EQ(solution.reverseRecursive(input), expected) << "Recursive approach failed for input: " << input;
        EXPECT_EQ(solution.reversePreemptive(input), expected) << "Preemptive approach failed for input: " << input;
    }
};

TEST_F(ReverseIntegerTest, PositiveNumber) {
    verifyAllApproaches(123, 321);
}

TEST_F(ReverseIntegerTest, NegativeNumber) {
    verifyAllApproaches(-123, -321);
}

TEST_F(ReverseIntegerTest, NumberWithTrailingZeros) {
    verifyAllApproaches(120, 21);
}

TEST_F(ReverseIntegerTest, Zero) {
    verifyAllApproaches(0, 0);
}

TEST_F(ReverseIntegerTest, SingleDigitPositive) {
    verifyAllApproaches(9, 9);
}

TEST_F(ReverseIntegerTest, SingleDigitNegative) {
    verifyAllApproaches(-5, -5);
}

TEST_F(ReverseIntegerTest, OverflowCase1) {
    verifyAllApproaches(1534236469, 0);
}

TEST_F(ReverseIntegerTest, OverflowCase2) {
    verifyAllApproaches(-2147483648, 0);
}

TEST_F(ReverseIntegerTest, MaxInt) {
    verifyAllApproaches(2147483647, 0);
}

TEST_F(ReverseIntegerTest, MinInt) {
    verifyAllApproaches(-2147483648, 0);
}

TEST_F(ReverseIntegerTest, AlmostOverflowPositive) {
    verifyAllApproaches(1463847412, 2147483641);
}

TEST_F(ReverseIntegerTest, AlmostOverflowNegative) {
    verifyAllApproaches(-1463847412, -2147483641);
}

TEST_F(ReverseIntegerTest, Palindrome) {
    verifyAllApproaches(121, 121);
}

TEST_F(ReverseIntegerTest, NegativePalindrome) {
    verifyAllApproaches(-121, -121);
}

TEST_F(ReverseIntegerTest, LargeNumberNoOverflow) {
    verifyAllApproaches(1234567, 7654321);
}

TEST_F(ReverseIntegerTest, MultipleZerosInMiddle) {
    verifyAllApproaches(100021, 120001);
}

TEST_F(ReverseIntegerTest, AlternatingDigits) {
    verifyAllApproaches(123456789, 987654321);
}

TEST_F(ReverseIntegerTest, PowerOfTen) {
    verifyAllApproaches(1000, 1);
}

TEST_F(ReverseIntegerTest, NegativePowerOfTen) {
    verifyAllApproaches(-1000, -1);
}

TEST_F(ReverseIntegerTest, AllSameDigits) {
    verifyAllApproaches(1111, 1111);
}

TEST_F(ReverseIntegerTest, TwoDigitPositive) {
    verifyAllApproaches(42, 24);
}

TEST_F(ReverseIntegerTest, TwoDigitNegative) {
    verifyAllApproaches(-89, -98);
}

TEST_F(ReverseIntegerTest, BoundaryNearMaxInt) {
    verifyAllApproaches(2147447412, 2147447412);
}

TEST_F(ReverseIntegerTest, ReversedWouldBeMaxIntPlusOne) {
    verifyAllApproaches(8463847412, 0);
}

TEST_F(ReverseIntegerTest, ConsecutiveDigits) {
    verifyAllApproaches(123456, 654321);
}