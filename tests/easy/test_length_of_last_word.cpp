#include <gtest/gtest.h>
#include <string>
#include "easy/length_of_last_word.h"

using namespace leetcode::easy;

class LengthOfLastWordTest : public ::testing::Test {
protected:
    void verifyAll(const std::string& s, int expected) {
        LengthOfLastWord solver;
        EXPECT_EQ(solver.lengthOfLastWordReverse(s), expected);
        EXPECT_EQ(solver.lengthOfLastWordForward(s), expected);
        EXPECT_EQ(solver.lengthOfLastWordStringStream(s), expected);
        EXPECT_EQ(solver.lengthOfLastWordFindLast(s), expected);
        EXPECT_EQ(solver.lengthOfLastWordRFind(s), expected);
        EXPECT_EQ(solver.lengthOfLastWordSplit(s), expected);
    }
};

TEST_F(LengthOfLastWordTest, TypicalSentences) {
    verifyAll("Hello World", 5);
    verifyAll("   fly me   to   the moon  ", 4);
    verifyAll("luffy is still joyboy", 6);
}

