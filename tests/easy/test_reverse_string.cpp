#include <gtest/gtest.h>
#include "easy/reverse_string.h"
#include <vector>
#include <string>

namespace leetcode {
namespace easy {
namespace test {

class ReverseStringTest : public ::testing::Test {
protected:
    void testAllApproaches(const std::string& input, const std::string& expected) {
        std::vector<char> s1(input.begin(), input.end());
        std::vector<char> s2 = s1;
        std::vector<char> s3 = s1;
        std::vector<char> s4 = s1;
        std::vector<char> s5 = s1;
        std::vector<char> s6 = s1;

        ReverseStringTwoPointer sol1;
        ReverseStringStdReverse sol2;
        ReverseStringStack sol3;
        ReverseStringRecursive sol4;
        ReverseStringXor sol5;
        ReverseStringDeque sol6;

        sol1.reverseString(s1);
        sol2.reverseString(s2);
        sol3.reverseString(s3);
        sol4.reverseString(s4);
        sol5.reverseString(s5);
        sol6.reverseString(s6);

        std::vector<char> exp(expected.begin(), expected.end());
        EXPECT_EQ(s1, exp);
        EXPECT_EQ(s2, exp);
        EXPECT_EQ(s3, exp);
        EXPECT_EQ(s4, exp);
        EXPECT_EQ(s5, exp);
        EXPECT_EQ(s6, exp);
    }
};

TEST_F(ReverseStringTest, BasicOddLength) {
    testAllApproaches("hello", "olleh");
}

TEST_F(ReverseStringTest, EvenLength) {
    testAllApproaches("abcd", "dcba");
}

TEST_F(ReverseStringTest, SingleCharacter) {
    testAllApproaches("a", "a");
}

TEST_F(ReverseStringTest, EmptyString) {
    testAllApproaches("", "");
}

TEST_F(ReverseStringTest, Palindrome) {
    testAllApproaches("level", "level");
}

TEST_F(ReverseStringTest, MixedCharacters) {
    testAllApproaches("A1b2C3", "3C2b1A");
}

} // namespace test
} // namespace easy
} // namespace leetcode

