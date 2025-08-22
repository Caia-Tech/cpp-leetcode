#include <gtest/gtest.h>
#include "easy/power_of_three.h"

using namespace leetcode::easy;

TEST(PowerOfThreeIterativeTest, BasicCases) {
    PowerOfThreeIterative solver;
    EXPECT_TRUE(solver.isPowerOfThree(1));
    EXPECT_TRUE(solver.isPowerOfThree(27));
    EXPECT_FALSE(solver.isPowerOfThree(0));
    EXPECT_FALSE(solver.isPowerOfThree(45));
}

TEST(PowerOfThreeRecursiveTest, BasicCases) {
    PowerOfThreeRecursive solver;
    EXPECT_TRUE(solver.isPowerOfThree(9));
    EXPECT_FALSE(solver.isPowerOfThree(10));
}

TEST(PowerOfThreeLogarithmTest, BasicCases) {
    PowerOfThreeLogarithm solver;
    EXPECT_TRUE(solver.isPowerOfThree(81));
    EXPECT_FALSE(solver.isPowerOfThree(82));
}

TEST(PowerOfThreeBase3Test, BasicCases) {
    PowerOfThreeBase3 solver;
    EXPECT_TRUE(solver.isPowerOfThree(3));
    EXPECT_FALSE(solver.isPowerOfThree(12));
}

TEST(PowerOfThreeMaxPowerTest, BasicCases) {
    PowerOfThreeMaxPower solver;
    EXPECT_TRUE(solver.isPowerOfThree(243));
    EXPECT_FALSE(solver.isPowerOfThree(244));
}

TEST(PowerOfThreePrecomputeTest, BasicCases) {
    PowerOfThreePrecompute solver;
    EXPECT_TRUE(solver.isPowerOfThree(729));
    EXPECT_FALSE(solver.isPowerOfThree(730));
}

