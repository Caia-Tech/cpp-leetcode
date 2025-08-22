#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "easy/ransom_note.h"

using namespace leetcode::easy;

class RansomNoteTest : public ::testing::Test {
protected:
    void verifyAll(const std::string& note, const std::string& mag, bool expected) {
        RansomNote s;
        EXPECT_EQ(s.canConstructCountArray(note, mag), expected);
        EXPECT_EQ(s.canConstructHashMap(note, mag), expected);
        EXPECT_EQ(s.canConstructSorting(note, mag), expected);
        EXPECT_EQ(s.canConstructSinglePass(note, mag), expected);
        EXPECT_EQ(s.canConstructMultiset(note, mag), expected);
        EXPECT_EQ(s.canConstructMap(note, mag), expected);
    }
};

TEST_F(RansomNoteTest, BasicCases) {
    verifyAll("a", "b", false);
    verifyAll("aa", "ab", false);
    verifyAll("aa", "aab", true);
    verifyAll("abc", "cba", true);
    verifyAll("aab", "baa", true);
}

