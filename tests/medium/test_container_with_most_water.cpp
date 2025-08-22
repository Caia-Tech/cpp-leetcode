#include <gtest/gtest.h>
#include "medium/container_with_most_water.h"
#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {
namespace test {

class ContainerWithMostWaterTest : public ::testing::Test {
protected:
    // Helper function to test all approaches
    void testAllApproaches(const std::vector<int>& height, int expected) {
        ContainerWithMostWater solution;
        
        EXPECT_EQ(solution.maxAreaTwoPointers(height), expected) 
            << "Two Pointers approach failed";
        EXPECT_EQ(solution.maxAreaBruteForce(height), expected) 
            << "Brute Force approach failed";
        EXPECT_EQ(solution.maxAreaDivideConquer(height), expected) 
            << "Divide and Conquer approach failed";
        EXPECT_EQ(solution.maxAreaStack(height), expected) 
            << "Stack approach failed";
        EXPECT_EQ(solution.maxAreaOptimizedBruteForce(height), expected) 
            << "Optimized Brute Force approach failed";
        EXPECT_EQ(solution.maxAreaBinarySearch(height), expected) 
            << "Binary Search approach failed";
    }
};

// LeetCode examples
TEST_F(ContainerWithMostWaterTest, LeetCodeExample1) {
    // height = [1,8,6,2,5,4,8,3,7], expected = 49
    // Container formed by height[1]=8 and height[8]=7: min(8,7) * (8-1) = 7 * 7 = 49
    std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    testAllApproaches(height, 49);
}

TEST_F(ContainerWithMostWaterTest, LeetCodeExample2) {
    // height = [1,1], expected = 1
    // Only one possible container: min(1,1) * (1-0) = 1 * 1 = 1
    std::vector<int> height = {1, 1};
    testAllApproaches(height, 1);
}

// Edge cases
TEST_F(ContainerWithMostWaterTest, MinimumSize) {
    // Minimum constraint: 2 elements
    std::vector<int> height = {2, 3};
    testAllApproaches(height, 2);  // min(2,3) * (1-0) = 2
}

TEST_F(ContainerWithMostWaterTest, TwoEqualHeights) {
    std::vector<int> height = {5, 5};
    testAllApproaches(height, 5);  // min(5,5) * (1-0) = 5
}

TEST_F(ContainerWithMostWaterTest, IncreasingHeights) {
    std::vector<int> height = {1, 2, 3, 4, 5};
    // Best container: indices 1,4: min(2,5) * (4-1) = 2 * 3 = 6
    testAllApproaches(height, 6);
}

TEST_F(ContainerWithMostWaterTest, DecreasingHeights) {
    std::vector<int> height = {5, 4, 3, 2, 1};
    // Best container: indices 0,3: min(5,2) * (3-0) = 2 * 3 = 6
    testAllApproaches(height, 6);
}

TEST_F(ContainerWithMostWaterTest, AllZeros) {
    std::vector<int> height = {0, 0, 0, 0};
    testAllApproaches(height, 0);  // No water can be stored
}

TEST_F(ContainerWithMostWaterTest, SingleHighBar) {
    std::vector<int> height = {1, 10, 1};
    testAllApproaches(height, 2);  // Best: min(1,1) * (2-0) = 1 * 2 = 2
}

TEST_F(ContainerWithMostWaterTest, TwoHighBars) {
    std::vector<int> height = {10, 1, 10};
    testAllApproaches(height, 20);  // min(10,10) * (2-0) = 10 * 2 = 20
}

// Symmetric patterns
TEST_F(ContainerWithMostWaterTest, SymmetricPattern) {
    std::vector<int> height = {1, 3, 5, 3, 1};
    // Best container: indices 1,3: min(3,3) * (3-1) = 3 * 2 = 6
    testAllApproaches(height, 6);
}

TEST_F(ContainerWithMostWaterTest, PyramidPattern) {
    std::vector<int> height = {1, 2, 3, 4, 3, 2, 1};
    // Best container: indices 1,5: min(2,2) * (5-1) = 2 * 4 = 8
    testAllApproaches(height, 8);
}

TEST_F(ContainerWithMostWaterTest, ValleyPattern) {
    std::vector<int> height = {4, 1, 1, 1, 4};
    testAllApproaches(height, 16);  // min(4,4) * (4-0) = 16
}

// Large height differences
TEST_F(ContainerWithMostWaterTest, ExtremeHeightDifference) {
    std::vector<int> height = {1, 10000, 1};
    testAllApproaches(height, 2);  // min(1,1) * (2-0) = 2
}

TEST_F(ContainerWithMostWaterTest, MaxConstraintHeights) {
    // Using maximum constraint: height[i] <= 10^4
    std::vector<int> height = {10000, 1, 10000};
    testAllApproaches(height, 20000);  // min(10000,10000) * (2-0) = 20000
}

// Patterns with optimal solutions not at extremes
TEST_F(ContainerWithMostWaterTest, OptimalInMiddle) {
    std::vector<int> height = {1, 2, 4, 3};
    testAllApproaches(height, 4);  // min(2,3) * (3-1) = 2*2 = 4 or min(1,3) * 3 = 3? Actually min(2,4) * 1 = 2, min(4,3) * 1 = 3, but min(1,3) * 3 = 3, min(2,3) * 2 = 4
}

TEST_F(ContainerWithMostWaterTest, MultipleOptimalSolutions) {
    std::vector<int> height = {2, 1, 2, 1, 2};
    testAllApproaches(height, 8);  // min(2,2) * (4-0) = 8 or other combinations
}

// Longer arrays
TEST_F(ContainerWithMostWaterTest, LongerArray) {
    std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7, 9, 1, 2, 3};
    // Best container calculated by algorithms
    testAllApproaches(height, 64);
}

TEST_F(ContainerWithMostWaterTest, AlternatingHeights) {
    std::vector<int> height = {1, 5, 1, 5, 1, 5};
    testAllApproaches(height, 20);  // min(5,5) * (5-1) = 20 or min(5,5) * (3-1) = 10? Actually (5-1)=4, so 5*4=20
}

// Plateau patterns
TEST_F(ContainerWithMostWaterTest, PlateauPattern) {
    std::vector<int> height = {1, 3, 3, 3, 1};
    // Best container: indices 1,3: min(3,3) * (3-1) = 3 * 2 = 6
    testAllApproaches(height, 6);
}

TEST_F(ContainerWithMostWaterTest, MultiplePlateaus) {
    std::vector<int> height = {2, 2, 1, 3, 3, 3, 1, 2, 2};
    testAllApproaches(height, 16);  // min(2,2) * (8-0) = 16
}

// Rising and falling patterns
TEST_F(ContainerWithMostWaterTest, StepsUp) {
    std::vector<int> height = {1, 2, 3, 4, 5, 6};
    testAllApproaches(height, 9);  // Need to calculate optimal
}

TEST_F(ContainerWithMostWaterTest, StepsDown) {
    std::vector<int> height = {6, 5, 4, 3, 2, 1};
    testAllApproaches(height, 9);  // Mirror of above
}

// Complex patterns
TEST_F(ContainerWithMostWaterTest, ZigzagPattern) {
    std::vector<int> height = {1, 3, 2, 4, 1, 5, 2};
    testAllApproaches(height, 12);  // Verified by algorithms
}

TEST_F(ContainerWithMostWaterTest, RandomPattern) {
    std::vector<int> height = {3, 7, 1, 9, 2, 5, 8, 4, 6};
    testAllApproaches(height, 42);  // Verified by algorithms
}

// Boundary testing
TEST_F(ContainerWithMostWaterTest, AllSameHeight) {
    std::vector<int> height = {5, 5, 5, 5, 5};
    testAllApproaches(height, 20);  // min(5,5) * (4-0) = 20
}

TEST_F(ContainerWithMostWaterTest, OnlyTwoNonZero) {
    std::vector<int> height = {0, 7, 0, 0, 3, 0};
    testAllApproaches(height, 9);  // min(7,3) * (4-1) = 3 * 3 = 9
}

// Large width scenarios
TEST_F(ContainerWithMostWaterTest, WideContainer) {
    std::vector<int> height = {2, 1, 1, 1, 1, 1, 1, 1, 1, 2};
    testAllApproaches(height, 18);  // min(2,2) * (9-0) = 18
}

TEST_F(ContainerWithMostWaterTest, WideWithHighEnds) {
    std::vector<int> height(20, 1);  // 20 elements of height 1
    height[0] = 5;
    height[19] = 5;
    testAllApproaches(height, 95);  // min(5,5) * (19-0) = 95
}

// Performance edge cases
TEST_F(ContainerWithMostWaterTest, WorstCaseTwoPointers) {
    // Case where two pointers might not immediately find optimal
    std::vector<int> height = {2, 3, 4, 5, 18, 17, 6};
    testAllApproaches(height, 17);  // Need to verify
}

TEST_F(ContainerWithMostWaterTest, ManySmallContainers) {
    std::vector<int> height = {1, 2, 1, 2, 1, 2, 1, 2};
    testAllApproaches(height, 12);  // min(2,2) * (7-1) = 12
}

// Special mathematical cases
TEST_F(ContainerWithMostWaterTest, FibonacciHeights) {
    std::vector<int> height = {1, 1, 2, 3, 5, 8};
    testAllApproaches(height, 6);  // Verified by algorithms
}

TEST_F(ContainerWithMostWaterTest, PowerOfTwoHeights) {
    std::vector<int> height = {1, 2, 4, 8, 16, 32};
    testAllApproaches(height, 16);  // Need to calculate
}

// Maximum constraint testing
TEST_F(ContainerWithMostWaterTest, MaxSizeArray) {
    // Test with larger array (but not full 10^5 for test speed)
    std::vector<int> height(100, 1);
    height[0] = 50;
    height[99] = 50;
    testAllApproaches(height, 4950);  // min(50,50) * (99-0) = 4950
}

TEST_F(ContainerWithMostWaterTest, CornerCaseOptimal) {
    std::vector<int> height = {1, 2, 4, 8, 4, 2, 1};
    testAllApproaches(height, 8);  // min(8,1) * 6 = 6? or min(4,4) * 4 = 16? Actually min(4,4) at indices 2,4: (4-2)*4 = 8
}

// Stress test patterns
TEST_F(ContainerWithMostWaterTest, AlternatingHighLow) {
    std::vector<int> height = {10, 1, 10, 1, 10, 1, 10};
    testAllApproaches(height, 60);  // min(10,10) * (6-0) = 60
}

TEST_F(ContainerWithMostWaterTest, GradualIncrease) {
    std::vector<int> height;
    for (int i = 1; i <= 10; i++) {
        height.push_back(i);
    }
    testAllApproaches(height, 25);  // Need to verify optimal
}

}
}
}