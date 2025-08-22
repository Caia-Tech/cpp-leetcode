#include <gtest/gtest.h>
#include "easy/climbing_stairs.h"

using namespace leetcode::easy;

class ClimbingStairsTest : public ::testing::Test {
protected:
    ClimbingStairs solution;
    
    void verifyAllApproaches(int n, int expected) {
        EXPECT_EQ(solution.climbStairsRecursive(n), expected) 
            << "Recursive failed for n=" << n;
        EXPECT_EQ(solution.climbStairsMemoization(n), expected) 
            << "Memoization failed for n=" << n;
        EXPECT_EQ(solution.climbStairsDP(n), expected) 
            << "DP failed for n=" << n;
        EXPECT_EQ(solution.climbStairsFibonacci(n), expected) 
            << "Fibonacci failed for n=" << n;
        EXPECT_EQ(solution.climbStairsMatrix(n), expected) 
            << "Matrix failed for n=" << n;
        EXPECT_EQ(solution.climbStairsBinet(n), expected) 
            << "Binet failed for n=" << n;
    }
};

TEST_F(ClimbingStairsTest, OneStep) {
    verifyAllApproaches(1, 1);
}

TEST_F(ClimbingStairsTest, TwoSteps) {
    verifyAllApproaches(2, 2);
}

TEST_F(ClimbingStairsTest, ThreeSteps) {
    verifyAllApproaches(3, 3);
}

TEST_F(ClimbingStairsTest, FourSteps) {
    verifyAllApproaches(4, 5);
}

TEST_F(ClimbingStairsTest, FiveSteps) {
    verifyAllApproaches(5, 8);
}

TEST_F(ClimbingStairsTest, SixSteps) {
    verifyAllApproaches(6, 13);
}

TEST_F(ClimbingStairsTest, SevenSteps) {
    verifyAllApproaches(7, 21);
}

TEST_F(ClimbingStairsTest, EightSteps) {
    verifyAllApproaches(8, 34);
}

TEST_F(ClimbingStairsTest, NineSteps) {
    verifyAllApproaches(9, 55);
}

TEST_F(ClimbingStairsTest, TenSteps) {
    verifyAllApproaches(10, 89);
}

TEST_F(ClimbingStairsTest, FifteenSteps) {
    verifyAllApproaches(15, 987);
}

TEST_F(ClimbingStairsTest, TwentySteps) {
    verifyAllApproaches(20, 10946);
}

TEST_F(ClimbingStairsTest, TwentyFiveSteps) {
    verifyAllApproaches(25, 121393);
}

TEST_F(ClimbingStairsTest, ThirtySteps) {
    verifyAllApproaches(30, 1346269);
}

TEST_F(ClimbingStairsTest, ThirtyFiveSteps) {
    verifyAllApproaches(35, 14930352);
}

TEST_F(ClimbingStairsTest, FortySteps) {
    verifyAllApproaches(40, 165580141);
}

TEST_F(ClimbingStairsTest, FortyFourSteps) {
    verifyAllApproaches(44, 1134903170);
}

TEST_F(ClimbingStairsTest, FortyFiveSteps) {
    verifyAllApproaches(45, 1836311903);
}

TEST_F(ClimbingStairsTest, MinimumInput) {
    verifyAllApproaches(1, 1);
}

TEST_F(ClimbingStairsTest, FibonacciPattern) {
    EXPECT_EQ(solution.climbStairsDP(3), 
              solution.climbStairsDP(1) + solution.climbStairsDP(2));
    EXPECT_EQ(solution.climbStairsDP(4), 
              solution.climbStairsDP(2) + solution.climbStairsDP(3));
}

TEST_F(ClimbingStairsTest, SequentialGrowth) {
    int prev = solution.climbStairsDP(10);
    int curr = solution.climbStairsDP(11);
    EXPECT_GT(curr, prev);
}

TEST_F(ClimbingStairsTest, LargerThanInput) {
    int n = 10;
    int result = solution.climbStairsDP(n);
    EXPECT_GT(result, n);
}

TEST_F(ClimbingStairsTest, PowersOfTwo) {
    verifyAllApproaches(8, 34);
    verifyAllApproaches(16, 1597);
    verifyAllApproaches(32, 3524578);
}

TEST_F(ClimbingStairsTest, ConsistencyCheck) {
    for (int i = 1; i <= 10; ++i) {
        int expected = solution.climbStairsFibonacci(i);
        EXPECT_EQ(solution.climbStairsDP(i), expected);
        EXPECT_EQ(solution.climbStairsMemoization(i), expected);
    }
}