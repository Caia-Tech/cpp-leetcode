#include <gtest/gtest.h>
#include "easy/fizz_buzz.h"

using namespace std;

namespace leetcode {
namespace easy {
namespace test {

class FizzBuzzTest : public ::testing::Test {
protected:
    void verifyAllApproaches(int n, const vector<string>& expected) {
        FizzBuzzIfElse a1; FizzBuzzConcat a2; FizzBuzzMap a3;
        FizzBuzzSwitch a4; FizzBuzzPrecompute a5; FizzBuzzModuloArray a6;
        EXPECT_EQ(a1.fizzBuzz(n), expected);
        EXPECT_EQ(a2.fizzBuzz(n), expected);
        EXPECT_EQ(a3.fizzBuzz(n), expected);
        EXPECT_EQ(a4.fizzBuzz(n), expected);
        EXPECT_EQ(a5.fizzBuzz(n), expected);
        EXPECT_EQ(a6.fizzBuzz(n), expected);
    }
};

TEST_F(FizzBuzzTest, Single) {
    verifyAllApproaches(1, {"1"});
}

TEST_F(FizzBuzzTest, Three) {
    verifyAllApproaches(3, {"1","2","Fizz"});
}

TEST_F(FizzBuzzTest, Five) {
    verifyAllApproaches(5, {"1","2","Fizz","4","Buzz"});
}

TEST_F(FizzBuzzTest, Fifteen) {
    verifyAllApproaches(15, {"1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz","11","Fizz","13","14","FizzBuzz"});
}

} // namespace test
} // namespace easy
} // namespace leetcode

