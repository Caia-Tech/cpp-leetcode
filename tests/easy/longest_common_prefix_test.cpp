#include <gtest/gtest.h>
#include "easy/longest_common_prefix.h"

using namespace leetcode::easy;

class LongestCommonPrefixTest : public ::testing::Test {
protected:
    LongestCommonPrefix solution;
    
    void verifyAllApproaches(std::vector<std::string> strs, const std::string& expected) {
        auto s1 = strs, s2 = strs, s3 = strs;
        auto s4 = strs, s5 = strs, s6 = strs;
        
        EXPECT_EQ(solution.longestCommonPrefixVertical(s1), expected) 
            << "Vertical Scanning failed";
        EXPECT_EQ(solution.longestCommonPrefixHorizontal(s2), expected) 
            << "Horizontal Scanning failed";
        EXPECT_EQ(solution.longestCommonPrefixDivideConquer(s3), expected) 
            << "Divide and Conquer failed";
        EXPECT_EQ(solution.longestCommonPrefixBinarySearch(s4), expected) 
            << "Binary Search failed";
        EXPECT_EQ(solution.longestCommonPrefixTrie(s5), expected) 
            << "Trie failed";
        EXPECT_EQ(solution.longestCommonPrefixSort(s6), expected) 
            << "Sort failed";
    }
};

TEST_F(LongestCommonPrefixTest, BasicExample) {
    verifyAllApproaches({"flower", "flow", "flight"}, "fl");
}

TEST_F(LongestCommonPrefixTest, NoCommonPrefix) {
    verifyAllApproaches({"dog", "racecar", "car"}, "");
}

TEST_F(LongestCommonPrefixTest, SingleString) {
    verifyAllApproaches({"alone"}, "alone");
}

TEST_F(LongestCommonPrefixTest, AllSameString) {
    verifyAllApproaches({"test", "test", "test"}, "test");
}

TEST_F(LongestCommonPrefixTest, EmptyStringInArray) {
    verifyAllApproaches({"flower", "", "flight"}, "");
}

TEST_F(LongestCommonPrefixTest, SingleCharacterStrings) {
    verifyAllApproaches({"a", "a", "a"}, "a");
}

TEST_F(LongestCommonPrefixTest, SingleCharacterMixed) {
    verifyAllApproaches({"a", "b", "c"}, "");
}

TEST_F(LongestCommonPrefixTest, OneStringIsPrefix) {
    verifyAllApproaches({"abc", "abcdef", "abcd"}, "abc");
}

TEST_F(LongestCommonPrefixTest, CommonPrefixAtStart) {
    verifyAllApproaches({"interview", "internet", "internal"}, "inte");
}

TEST_F(LongestCommonPrefixTest, VeryLongCommonPrefix) {
    verifyAllApproaches({
        "abcdefghijklmnopqrstuvwxyz123", 
        "abcdefghijklmnopqrstuvwxyz456", 
        "abcdefghijklmnopqrstuvwxyz789"
    }, "abcdefghijklmnopqrstuvwxyz");
}

TEST_F(LongestCommonPrefixTest, DifferentLengths) {
    verifyAllApproaches({"a", "ab", "abc", "abcd"}, "a");
}

TEST_F(LongestCommonPrefixTest, ReverseOrder) {
    verifyAllApproaches({"abcd", "abc", "ab", "a"}, "a");
}

TEST_F(LongestCommonPrefixTest, TwoStrings) {
    verifyAllApproaches({"hello", "help"}, "hel");
}

TEST_F(LongestCommonPrefixTest, PartialMatch) {
    verifyAllApproaches({"prefix", "prepare", "present"}, "pre");
}

TEST_F(LongestCommonPrefixTest, NoMatchAfterFirst) {
    verifyAllApproaches({"abc", "def", "ghi"}, "");
}

TEST_F(LongestCommonPrefixTest, LexicographicOrder) {
    verifyAllApproaches({"apple", "application", "apply"}, "appl");
}

TEST_F(LongestCommonPrefixTest, SingleLetter) {
    verifyAllApproaches({"c", "c"}, "c");
}

TEST_F(LongestCommonPrefixTest, MixedCaseIgnored) {
    // Note: Problem states lowercase only, but testing implementation robustness
    verifyAllApproaches({"test", "testing", "tester"}, "test");
}

TEST_F(LongestCommonPrefixTest, AlphabeticalStart) {
    verifyAllApproaches({"abcd", "abce", "abcf"}, "abc");
}

TEST_F(LongestCommonPrefixTest, FirstCharDifferent) {
    verifyAllApproaches({"xello", "yello", "zello"}, "");
}

TEST_F(LongestCommonPrefixTest, LongStringsNoPrefix) {
    verifyAllApproaches({
        "thisisaverylongstring", 
        "xhisisaverylongstring", 
        "yhisisaverylongstring"
    }, "");
}

TEST_F(LongestCommonPrefixTest, SimilarButDifferent) {
    verifyAllApproaches({"abc", "abd", "abe"}, "ab");
}

TEST_F(LongestCommonPrefixTest, OneCharacterDifference) {
    verifyAllApproaches({"abcde", "abcdf", "abcdg"}, "abcd");
}

TEST_F(LongestCommonPrefixTest, RepeatedCharacters) {
    verifyAllApproaches({"aaaaab", "aaaaac", "aaaaad"}, "aaaaa");
}

TEST_F(LongestCommonPrefixTest, AlmostIdentical) {
    verifyAllApproaches({"programming", "program", "programmer"}, "program");
}

TEST_F(LongestCommonPrefixTest, ManyStrings) {
    verifyAllApproaches({
        "common", "communicate", "community", "command", 
        "commit", "complete", "compare", "computer"
    }, "com");
}

TEST_F(LongestCommonPrefixTest, EdgeCaseLengths) {
    verifyAllApproaches({"", "a", "ab"}, "");
}