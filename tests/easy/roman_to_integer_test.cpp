#include <gtest/gtest.h>
#include "easy/roman_to_integer.h"

using namespace leetcode::easy;

class RomanToIntegerTest : public ::testing::Test {
protected:
    RomanToInteger solution;
    
    void verifyAllApproaches(const std::string& input, int expected) {
        EXPECT_EQ(solution.romanToIntHashMap(input), expected) 
            << "Hash Map failed for input: " << input;
        EXPECT_EQ(solution.romanToIntSwitch(input), expected) 
            << "Switch failed for input: " << input;
        EXPECT_EQ(solution.romanToIntRightToLeft(input), expected) 
            << "Right to Left failed for input: " << input;
        EXPECT_EQ(solution.romanToIntReplace(input), expected) 
            << "Replace failed for input: " << input;
        EXPECT_EQ(solution.romanToIntStateMachine(input), expected) 
            << "State Machine failed for input: " << input;
        EXPECT_EQ(solution.romanToIntArray(input), expected) 
            << "Array failed for input: " << input;
    }
};

TEST_F(RomanToIntegerTest, SingleDigits) {
    verifyAllApproaches("I", 1);
    verifyAllApproaches("V", 5);
    verifyAllApproaches("X", 10);
    verifyAllApproaches("L", 50);
    verifyAllApproaches("C", 100);
    verifyAllApproaches("D", 500);
    verifyAllApproaches("M", 1000);
}

TEST_F(RomanToIntegerTest, BasicNumbers) {
    verifyAllApproaches("III", 3);
    verifyAllApproaches("LVIII", 58);
    verifyAllApproaches("MCMXCIV", 1994);
}

TEST_F(RomanToIntegerTest, SubtractionCases) {
    verifyAllApproaches("IV", 4);
    verifyAllApproaches("IX", 9);
    verifyAllApproaches("XL", 40);
    verifyAllApproaches("XC", 90);
    verifyAllApproaches("CD", 400);
    verifyAllApproaches("CM", 900);
}

TEST_F(RomanToIntegerTest, ComplexNumbers) {
    verifyAllApproaches("MMMDCCXLIX", 3749);
    verifyAllApproaches("MMMCMXCIX", 3999);
    verifyAllApproaches("MDCLXVI", 1666);
}

TEST_F(RomanToIntegerTest, MinimumValue) {
    verifyAllApproaches("I", 1);
}

TEST_F(RomanToIntegerTest, MaximumValue) {
    verifyAllApproaches("MMMCMXCIX", 3999);
}

TEST_F(RomanToIntegerTest, YearExamples) {
    verifyAllApproaches("MMXXIV", 2024);
    verifyAllApproaches("MCMLIV", 1954);
    verifyAllApproaches("MCMXC", 1990);
}

TEST_F(RomanToIntegerTest, RepeatingCharacters) {
    verifyAllApproaches("III", 3);
    verifyAllApproaches("XXX", 30);
    verifyAllApproaches("CCC", 300);
    verifyAllApproaches("MMM", 3000);
}

TEST_F(RomanToIntegerTest, MixedPatterns) {
    verifyAllApproaches("DCXXI", 621);
    verifyAllApproaches("XLII", 42);
    verifyAllApproaches("LXXXVII", 87);
}

TEST_F(RomanToIntegerTest, ConsecutiveSubtractions) {
    verifyAllApproaches("XCIV", 94);
    verifyAllApproaches("CDXLIV", 444);
    verifyAllApproaches("CMXCIX", 999);
}

TEST_F(RomanToIntegerTest, RoundNumbers) {
    verifyAllApproaches("X", 10);
    verifyAllApproaches("C", 100);
    verifyAllApproaches("M", 1000);
    verifyAllApproaches("MM", 2000);
}

TEST_F(RomanToIntegerTest, SpecialCombinations) {
    verifyAllApproaches("XLIX", 49);
    verifyAllApproaches("XCIX", 99);
    verifyAllApproaches("CDXCIX", 499);
    verifyAllApproaches("CMXCIX", 999);
}

TEST_F(RomanToIntegerTest, SmallNumbers) {
    verifyAllApproaches("II", 2);
    verifyAllApproaches("XII", 12);
    verifyAllApproaches("XXVII", 27);
}

TEST_F(RomanToIntegerTest, MediumNumbers) {
    verifyAllApproaches("CCCLIV", 354);
    verifyAllApproaches("DCCVII", 707);
    verifyAllApproaches("DCCCXC", 890);
}

TEST_F(RomanToIntegerTest, LargeNumbers) {
    verifyAllApproaches("MMDCCCXLV", 2845);
    verifyAllApproaches("MMMCDLVI", 3456);
    verifyAllApproaches("MMMCDXLIV", 3444);
}

TEST_F(RomanToIntegerTest, AlternatingAddSub) {
    verifyAllApproaches("MCMXCIV", 1994);
    verifyAllApproaches("CDXLIV", 444);
}

TEST_F(RomanToIntegerTest, AllSubtractionCases) {
    verifyAllApproaches("IVXLCDM", 444);
}

TEST_F(RomanToIntegerTest, DescendingOrder) {
    verifyAllApproaches("MDCLXVI", 1666);
}

TEST_F(RomanToIntegerTest, AscendingWithSub) {
    verifyAllApproaches("XCIX", 99);
}

TEST_F(RomanToIntegerTest, CommonYears) {
    verifyAllApproaches("MCMXLV", 1945);
    verifyAllApproaches("MMXXI", 2021);
    verifyAllApproaches("MMXXII", 2022);
    verifyAllApproaches("MMXXIII", 2023);
}

TEST_F(RomanToIntegerTest, EdgePatterns) {
    verifyAllApproaches("XLVIII", 48);
    verifyAllApproaches("XCVIII", 98);
    verifyAllApproaches("CDXCVIII", 498);
    verifyAllApproaches("CMXCVIII", 998);
}