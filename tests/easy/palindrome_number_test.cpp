#include <gtest/gtest.h>
#include "easy/palindrome_number.h"

using namespace leetcode::easy;

class PalindromeNumberTest : public ::testing::Test {
protected:
    PalindromeNumber solution;
    
    void verifyAllApproaches(int input, bool expected) {
        EXPECT_EQ(solution.isPalindromeFullReverse(input), expected) 
            << "Full Reverse failed for input: " << input;
        EXPECT_EQ(solution.isPalindromeHalfReverse(input), expected) 
            << "Half Reverse failed for input: " << input;
        EXPECT_EQ(solution.isPalindromeString(input), expected) 
            << "String approach failed for input: " << input;
        EXPECT_EQ(solution.isPalindromeArray(input), expected) 
            << "Array approach failed for input: " << input;
        EXPECT_EQ(solution.isPalindromeRecursive(input), expected) 
            << "Recursive approach failed for input: " << input;
        EXPECT_EQ(solution.isPalindromeDivision(input), expected) 
            << "Division approach failed for input: " << input;
    }
};

TEST_F(PalindromeNumberTest, SingleDigit) {
    verifyAllApproaches(7, true);
}

TEST_F(PalindromeNumberTest, TwoDigitPalindrome) {
    verifyAllApproaches(11, true);
}

TEST_F(PalindromeNumberTest, TwoDigitNonPalindrome) {
    verifyAllApproaches(10, false);
}

TEST_F(PalindromeNumberTest, ThreeDigitPalindrome) {
    verifyAllApproaches(121, true);
}

TEST_F(PalindromeNumberTest, ThreeDigitNonPalindrome) {
    verifyAllApproaches(123, false);
}

TEST_F(PalindromeNumberTest, NegativeNumber) {
    verifyAllApproaches(-121, false);
}

TEST_F(PalindromeNumberTest, Zero) {
    verifyAllApproaches(0, true);
}

TEST_F(PalindromeNumberTest, TrailingZero) {
    verifyAllApproaches(10, false);
}

TEST_F(PalindromeNumberTest, LargePalindrome) {
    verifyAllApproaches(123454321, true);
}

TEST_F(PalindromeNumberTest, LargeNonPalindrome) {
    verifyAllApproaches(123456789, false);
}

TEST_F(PalindromeNumberTest, AllSameDigits) {
    verifyAllApproaches(1111, true);
}

TEST_F(PalindromeNumberTest, AlternatingDigits) {
    verifyAllApproaches(1212, false);
}

TEST_F(PalindromeNumberTest, EvenLengthPalindrome) {
    verifyAllApproaches(1221, true);
}

TEST_F(PalindromeNumberTest, OddLengthPalindrome) {
    verifyAllApproaches(12321, true);
}

TEST_F(PalindromeNumberTest, MaxInt) {
    verifyAllApproaches(2147483647, false);
}

TEST_F(PalindromeNumberTest, PowerOfTenMinusOne) {
    verifyAllApproaches(999, true);
}

TEST_F(PalindromeNumberTest, PowerOfTen) {
    verifyAllApproaches(1000, false);
}

TEST_F(PalindromeNumberTest, MirroredPairs) {
    verifyAllApproaches(12021, true);
}

TEST_F(PalindromeNumberTest, AlmostPalindrome) {
    verifyAllApproaches(12322, false);
}

TEST_F(PalindromeNumberTest, RepeatingPattern) {
    verifyAllApproaches(123321, true);
}

TEST_F(PalindromeNumberTest, SingleNonZeroDigit) {
    verifyAllApproaches(1, true);
}

TEST_F(PalindromeNumberTest, LongPalindrome) {
    verifyAllApproaches(1234554321, true);
}

TEST_F(PalindromeNumberTest, MinimalNonPalindrome) {
    verifyAllApproaches(12, false);
}

TEST_F(PalindromeNumberTest, SymmetricNumber) {
    verifyAllApproaches(98789, true);
}

TEST_F(PalindromeNumberTest, ConsecutiveDigitsPalindrome) {
    verifyAllApproaches(123321, true);
}