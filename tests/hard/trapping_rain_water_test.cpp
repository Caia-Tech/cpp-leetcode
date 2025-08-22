#include <gtest/gtest.h>
#include "hard/trapping_rain_water.h"

using namespace leetcode::hard;

class TrappingRainWaterTest : public ::testing::Test {
protected:
    TrappingRainWater solution;
    
    void verifyAllApproaches(std::vector<int> height, int expected) {
        auto h1 = height, h2 = height, h3 = height;
        auto h4 = height, h5 = height, h6 = height;
        
        EXPECT_EQ(solution.trapBruteForce(h1), expected) 
            << "Brute Force failed";
        EXPECT_EQ(solution.trapDP(h2), expected) 
            << "DP failed";
        EXPECT_EQ(solution.trapStack(h3), expected) 
            << "Stack failed";
        EXPECT_EQ(solution.trapTwoPointers(h4), expected) 
            << "Two Pointers failed";
        EXPECT_EQ(solution.trapHorizontal(h5), expected) 
            << "Horizontal failed";
        EXPECT_EQ(solution.trapOptimized(h6), expected) 
            << "Optimized failed";
    }
};

TEST_F(TrappingRainWaterTest, BasicCase) {
    verifyAllApproaches({0,1,0,2,1,0,1,3,2,1,2,1}, 6);
}

TEST_F(TrappingRainWaterTest, SimpleValley) {
    verifyAllApproaches({4,2,0,3,2,5}, 9);
}

TEST_F(TrappingRainWaterTest, NoWater) {
    verifyAllApproaches({1,2,3,4,5}, 0);
}

TEST_F(TrappingRainWaterTest, DecreasingHeights) {
    verifyAllApproaches({5,4,3,2,1}, 0);
}

TEST_F(TrappingRainWaterTest, SingleBar) {
    verifyAllApproaches({5}, 0);
}

TEST_F(TrappingRainWaterTest, TwoBars) {
    verifyAllApproaches({3,5}, 0);
}

TEST_F(TrappingRainWaterTest, FlatSurface) {
    verifyAllApproaches({3,3,3,3}, 0);
}

TEST_F(TrappingRainWaterTest, SingleValley) {
    verifyAllApproaches({3,0,2}, 2);
}

TEST_F(TrappingRainWaterTest, MultipleValleys) {
    verifyAllApproaches({3,0,2,0,4}, 7);
}

TEST_F(TrappingRainWaterTest, ComplexTerrain) {
    verifyAllApproaches({5,2,1,2,1,5}, 14);
}

TEST_F(TrappingRainWaterTest, EmptyArray) {
    verifyAllApproaches({}, 0);
}

TEST_F(TrappingRainWaterTest, SymmetricMountain) {
    verifyAllApproaches({1,2,3,2,1}, 0);
}

TEST_F(TrappingRainWaterTest, SymmetricValley) {
    verifyAllApproaches({3,2,1,2,3}, 4);
}

TEST_F(TrappingRainWaterTest, AlternatingHeights) {
    verifyAllApproaches({2,1,2,1,2}, 2);
}

TEST_F(TrappingRainWaterTest, LargeWaterTrap) {
    verifyAllApproaches({10,0,0,0,10}, 30);
}

TEST_F(TrappingRainWaterTest, StairPattern) {
    verifyAllApproaches({1,2,1,2,1,2}, 1);
}

TEST_F(TrappingRainWaterTest, PeakInMiddle) {
    verifyAllApproaches({1,2,3,4,3,2,1}, 0);
}

TEST_F(TrappingRainWaterTest, ValleyInMiddle) {
    verifyAllApproaches({4,3,2,1,2,3,4}, 9);
}

TEST_F(TrappingRainWaterTest, AllZeros) {
    verifyAllApproaches({0,0,0,0}, 0);
}

TEST_F(TrappingRainWaterTest, ZeroAtEnds) {
    verifyAllApproaches({0,2,0}, 0);
}

TEST_F(TrappingRainWaterTest, HighWalls) {
    verifyAllApproaches({100,0,100}, 100);
}

TEST_F(TrappingRainWaterTest, GradualSlope) {
    verifyAllApproaches({5,4,3,4,5}, 4);
}

TEST_F(TrappingRainWaterTest, MultipleSmallPools) {
    verifyAllApproaches({2,0,2,0,2,0,2}, 6);
}

TEST_F(TrappingRainWaterTest, IrregularTerrain) {
    verifyAllApproaches({3,1,2,5,2,3,1,4}, 7);
}

TEST_F(TrappingRainWaterTest, LongFlatWithDips) {
    verifyAllApproaches({3,3,1,3,1,3,3}, 4);
}