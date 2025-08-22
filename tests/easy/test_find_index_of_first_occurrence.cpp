#include <gtest/gtest.h>
#include <string>
#include "easy/find_index_of_first_occurrence.h"

using namespace leetcode::easy;

class FindIndexTest : public ::testing::Test {
protected:
    void verifyAll(const std::string& haystack, const std::string& needle, int expected) {
        FindIndexOfFirstOccurrence s;
        EXPECT_EQ(s.strStrBruteForce(haystack, needle), expected);
        EXPECT_EQ(s.strStrSTL(haystack, needle), expected);
        EXPECT_EQ(s.strStrKMP(haystack, needle), expected);
        EXPECT_EQ(s.strStrRabinKarp(haystack, needle), expected);
        EXPECT_EQ(s.strStrTwoPointers(haystack, needle), expected);
        EXPECT_EQ(s.strStrBoyerMooreSimple(haystack, needle), expected);
    }
};

TEST_F(FindIndexTest, FoundCases) {
    verifyAll("sadbutsad", "sad", 0);
    verifyAll("abc", "c", 2);
}

TEST_F(FindIndexTest, NotFoundCases) {
    verifyAll("leetcode", "leeto", -1);
    verifyAll("aaaaa", "bba", -1);
}

