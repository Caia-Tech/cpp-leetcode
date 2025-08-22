#include <gtest/gtest.h>
#include <string>
#include "easy/add_binary.h"

using namespace leetcode::easy;

class AddBinaryTest : public ::testing::Test {
protected:
    void verifyAll(const std::string& a, const std::string& b, const std::string& expected) {
        AddBinary s;
        EXPECT_EQ(s.addBinaryTwoPointers(a,b), expected);
        EXPECT_EQ(s.addBinaryPadding(a,b), expected);
        EXPECT_EQ(s.addBinaryReverse(a,b), expected);
        EXPECT_EQ(s.addBinaryRecursive(a,b), expected);
        EXPECT_EQ(s.addBinaryBitwise(a,b), expected);
        EXPECT_EQ(s.addBinaryBitset(a,b), expected);
    }
};

TEST_F(AddBinaryTest, SimpleCases) {
    verifyAll("11", "1", "100");
    verifyAll("1010", "1011", "10101");
}

TEST_F(AddBinaryTest, ZeroCase) {
    verifyAll("0", "0", "0");
}

