#include <gtest/gtest.h>
#include "easy/valid_anagram.h"

using namespace leetcode::easy;

class ValidAnagramTest : public ::testing::Test {
protected:
    void testAll(const std::string& s, const std::string& t, bool expected) {
        ValidAnagramSort a1;  EXPECT_EQ(a1.isAnagram(s, t), expected);
        ValidAnagramCountArray a2;  EXPECT_EQ(a2.isAnagram(s, t), expected);
        ValidAnagramHashMap a3;  EXPECT_EQ(a3.isAnagram(s, t), expected);
        ValidAnagramCountingSort a4;  EXPECT_EQ(a4.isAnagram(s, t), expected);
        ValidAnagramPrimeProduct a5;  EXPECT_EQ(a5.isAnagram(s, t), expected);
        ValidAnagramSinglePass a6;  EXPECT_EQ(a6.isAnagram(s, t), expected);
    }
};

TEST_F(ValidAnagramTest, BasicTrue) {
    testAll("anagram", "nagaram", true);
}

TEST_F(ValidAnagramTest, BasicFalse) {
    testAll("rat", "car", false);
}

TEST_F(ValidAnagramTest, DifferentLengths) {
    testAll("a", "aa", false);
}

TEST_F(ValidAnagramTest, SingleChars) {
    testAll("a", "a", true);
}

TEST_F(ValidAnagramTest, EmptyStrings) {
    testAll("", "", true);
}

TEST_F(ValidAnagramTest, RepeatedChars) {
    testAll("aabb", "bbaa", true);
}

TEST_F(ValidAnagramTest, NonAnagramSameChars) {
    testAll("aabb", "abca", false);
}
