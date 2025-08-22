#include <gtest/gtest.h>
#include "medium/longest_substring_without_repeating.h"

using namespace leetcode::medium;

class LongestSubstringWithoutRepeatingTest : public ::testing::Test {
protected:
    LongestSubstringWithoutRepeating solution;
    
    void verifyAllApproaches(const std::string& input, int expected) {
        EXPECT_EQ(solution.lengthOfLongestSubstringBruteForce(input), expected) 
            << "Brute Force failed for input: " << input;
        EXPECT_EQ(solution.lengthOfLongestSubstringHashSet(input), expected) 
            << "Hash Set failed for input: " << input;
        EXPECT_EQ(solution.lengthOfLongestSubstringHashMap(input), expected) 
            << "Hash Map failed for input: " << input;
        EXPECT_EQ(solution.lengthOfLongestSubstringASCII(input), expected) 
            << "ASCII Array failed for input: " << input;
        EXPECT_EQ(solution.lengthOfLongestSubstringDP(input), expected) 
            << "DP failed for input: " << input;
        EXPECT_EQ(solution.lengthOfLongestSubstringTwoPointers(input), expected) 
            << "Two Pointers failed for input: " << input;
    }
};

TEST_F(LongestSubstringWithoutRepeatingTest, BasicCase) {
    verifyAllApproaches("abcabcbb", 3);
}

TEST_F(LongestSubstringWithoutRepeatingTest, AllSameCharacter) {
    verifyAllApproaches("bbbbb", 1);
}

TEST_F(LongestSubstringWithoutRepeatingTest, AlternatingPattern) {
    verifyAllApproaches("pwwkew", 3);
}

TEST_F(LongestSubstringWithoutRepeatingTest, EmptyString) {
    verifyAllApproaches("", 0);
}

TEST_F(LongestSubstringWithoutRepeatingTest, SingleCharacter) {
    verifyAllApproaches("a", 1);
}

TEST_F(LongestSubstringWithoutRepeatingTest, AllUnique) {
    verifyAllApproaches("abcdefg", 7);
}

TEST_F(LongestSubstringWithoutRepeatingTest, TwoCharactersRepeating) {
    verifyAllApproaches("abba", 2);
}

TEST_F(LongestSubstringWithoutRepeatingTest, SpaceCharacter) {
    verifyAllApproaches(" ", 1);
}

TEST_F(LongestSubstringWithoutRepeatingTest, WithSpaces) {
    verifyAllApproaches("abc def", 7);
}

TEST_F(LongestSubstringWithoutRepeatingTest, NumbersAndLetters) {
    verifyAllApproaches("a1b2c3d4", 8);
}

TEST_F(LongestSubstringWithoutRepeatingTest, SpecialCharacters) {
    verifyAllApproaches("!@#$%^&*()", 10);
}

TEST_F(LongestSubstringWithoutRepeatingTest, LongRepeatingPattern) {
    verifyAllApproaches("abcabcabcabc", 3);
}

TEST_F(LongestSubstringWithoutRepeatingTest, ConsecutiveDuplicates) {
    verifyAllApproaches("aabbccdd", 2);
}

TEST_F(LongestSubstringWithoutRepeatingTest, PatternAtEnd) {
    verifyAllApproaches("abcdefgg", 7);
}

TEST_F(LongestSubstringWithoutRepeatingTest, PatternAtStart) {
    verifyAllApproaches("aabcdef", 6);
}

TEST_F(LongestSubstringWithoutRepeatingTest, ComplexPattern) {
    verifyAllApproaches("dvdf", 3);
}

TEST_F(LongestSubstringWithoutRepeatingTest, LongUniqueSequence) {
    verifyAllApproaches("abcdefghijklmnopqrstuvwxyz", 26);
}

TEST_F(LongestSubstringWithoutRepeatingTest, RepeatingPairs) {
    verifyAllApproaches("abab", 2);
}

TEST_F(LongestSubstringWithoutRepeatingTest, ThreeCharacterCycle) {
    verifyAllApproaches("abcabc", 3);
}

TEST_F(LongestSubstringWithoutRepeatingTest, NestedPattern) {
    verifyAllApproaches("anviaj", 5);
}

TEST_F(LongestSubstringWithoutRepeatingTest, MixedCase) {
    verifyAllApproaches("aAbBcC", 6);
}

TEST_F(LongestSubstringWithoutRepeatingTest, NumbersOnly) {
    verifyAllApproaches("1234567890", 10);
}

TEST_F(LongestSubstringWithoutRepeatingTest, AlternatingTwo) {
    verifyAllApproaches("ababababab", 2);
}

TEST_F(LongestSubstringWithoutRepeatingTest, GradualIncrease) {
    verifyAllApproaches("aabacbebebe", 4);
}

TEST_F(LongestSubstringWithoutRepeatingTest, ComplexMixed) {
    verifyAllApproaches("tmmzuxt", 5);
}