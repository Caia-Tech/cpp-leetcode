#include <gtest/gtest.h>
#include "medium/unique_paths.h"
#include <chrono>

using namespace leetcode::medium;

class UniquePathsTest : public ::testing::Test {
protected:
    UniquePaths solution;
    
    // Helper function to test all approaches (except pure recursion for large inputs)
    void testAllApproaches(int m, int n, int expected) {
        EXPECT_EQ(solution.uniquePathsDP2D(m, n), expected) << "DP 2D approach failed";
        EXPECT_EQ(solution.uniquePathsDP1D(m, n), expected) << "DP 1D approach failed";
        EXPECT_EQ(solution.uniquePathsMemo(m, n), expected) << "Memoization approach failed";
        EXPECT_EQ(solution.uniquePathsMath(m, n), expected) << "Mathematical approach failed";
        EXPECT_EQ(solution.uniquePathsBFS(m, n), expected) << "BFS approach failed";
        
        // Only test pure recursion for small inputs to avoid timeout
        if (m <= 10 && n <= 10) {
            EXPECT_EQ(solution.uniquePathsRecursive(m, n), expected) << "Recursive approach failed";
        }
    }
};

TEST_F(UniquePathsTest, BasicExample1) {
    // Input: m = 3, n = 7
    // Output: 28
    testAllApproaches(3, 7, 28);
}

TEST_F(UniquePathsTest, BasicExample2) {
    // Input: m = 3, n = 2
    // Output: 3
    // Paths: Right->Down->Down, Down->Right->Down, Down->Down->Right
    testAllApproaches(3, 2, 3);
}

TEST_F(UniquePathsTest, SingleCell) {
    // Input: m = 1, n = 1
    // Output: 1 (already at destination)
    testAllApproaches(1, 1, 1);
}

TEST_F(UniquePathsTest, SingleRow) {
    // Input: m = 1, n = 5
    // Output: 1 (only one path: right, right, right, right)
    testAllApproaches(1, 5, 1);
}

TEST_F(UniquePathsTest, SingleColumn) {
    // Input: m = 5, n = 1
    // Output: 1 (only one path: down, down, down, down)
    testAllApproaches(5, 1, 1);
}

TEST_F(UniquePathsTest, SmallSquare) {
    // Input: m = 2, n = 2
    // Output: 2
    // Paths: Right->Down, Down->Right
    testAllApproaches(2, 2, 2);
}

TEST_F(UniquePathsTest, Rectangle3x3) {
    // Input: m = 3, n = 3
    // Output: 6
    testAllApproaches(3, 3, 6);
}

TEST_F(UniquePathsTest, Rectangle4x4) {
    // Input: m = 4, n = 4
    // Output: 20
    testAllApproaches(4, 4, 20);
}

TEST_F(UniquePathsTest, AsymmetricGrid) {
    // Input: m = 2, n = 10
    // Output: 10 (choose 1 down move out of 9 total moves)
    testAllApproaches(2, 10, 10);
}

TEST_F(UniquePathsTest, AsymmetricGridReverse) {
    // Input: m = 10, n = 2
    // Output: 10 (choose 1 right move out of 9 total moves)
    testAllApproaches(10, 2, 10);
}

TEST_F(UniquePathsTest, MediumGrid) {
    // Input: m = 5, n = 5
    // Output: 70
    testAllApproaches(5, 5, 70);
}

TEST_F(UniquePathsTest, LargerGrid) {
    // Input: m = 6, n = 6
    // Output: 252
    testAllApproaches(6, 6, 252);
}

TEST_F(UniquePathsTest, RectangularGrid) {
    // Input: m = 7, n = 3
    // Output: 28 (same as 3x7 due to symmetry)
    testAllApproaches(7, 3, 28);
}

TEST_F(UniquePathsTest, SymmetryTest) {
    // Test that uniquePaths(m, n) == uniquePaths(n, m)
    int m = 5, n = 8;
    int result1 = solution.uniquePathsDP2D(m, n);
    int result2 = solution.uniquePathsDP2D(n, m);
    EXPECT_EQ(result1, result2) << "Results should be symmetric";
}

TEST_F(UniquePathsTest, LargeInput) {
    // Test with larger inputs (within constraints)
    testAllApproaches(15, 15, 40116600);
}

TEST_F(UniquePathsTest, EdgeCaseMin) {
    // Test minimum constraint values
    testAllApproaches(1, 1, 1);
    testAllApproaches(1, 2, 1);
    testAllApproaches(2, 1, 1);
}

TEST_F(UniquePathsTest, ConstraintBoundary) {
    // Test near boundary values (but not full 100x100 to keep test fast)
    testAllApproaches(20, 20, 35345263800LL);
}

TEST_F(UniquePathsTest, MathematicalVerification) {
    // Verify mathematical approach against smaller values we can calculate manually
    
    // For 3x3: total moves = 4, choose 2 down moves = C(4,2) = 6
    EXPECT_EQ(solution.uniquePathsMath(3, 3), 6);
    
    // For 4x2: total moves = 4, choose 1 right move = C(4,1) = 4
    EXPECT_EQ(solution.uniquePathsMath(4, 2), 4);
    
    // For 2x4: total moves = 4, choose 1 down move = C(4,1) = 4  
    EXPECT_EQ(solution.uniquePathsMath(2, 4), 4);
}

TEST_F(UniquePathsTest, ManualCalculationVerification) {
    // Manually verify small cases
    
    // 2x3 grid: RRD, RDR, DRR = 3 paths
    testAllApproaches(2, 3, 3);
    
    // 3x2 grid: DDR, DRD, RDD = 3 paths  
    testAllApproaches(3, 2, 3);
    
    // 2x2 grid: RD, DR = 2 paths
    testAllApproaches(2, 2, 2);
}

// Performance tests
TEST_F(UniquePathsTest, PerformanceComparison) {
    int m = 20, n = 20;
    
    // Test DP 2D approach
    auto start = std::chrono::high_resolution_clock::now();
    int result1 = solution.uniquePathsDP2D(m, n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test DP 1D approach
    start = std::chrono::high_resolution_clock::now();
    int result2 = solution.uniquePathsDP1D(m, n);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test mathematical approach
    start = std::chrono::high_resolution_clock::now();
    int result3 = solution.uniquePathsMath(m, n);
    end = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // All results should match
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, result3);
    
    // Mathematical approach should be fastest
    EXPECT_LT(duration3.count(), duration1.count()) << "Math approach should be faster than DP 2D";
    EXPECT_LT(duration2.count(), duration1.count()) << "DP 1D should be faster than DP 2D";
    
    // All should complete quickly
    EXPECT_LT(duration1.count(), 1000) << "DP 2D should complete quickly";
    EXPECT_LT(duration2.count(), 500) << "DP 1D should complete quickly";  
    EXPECT_LT(duration3.count(), 100) << "Math approach should complete very quickly";
}

TEST_F(UniquePathsTest, RecursivePerformanceLimit) {
    // Test pure recursion with small inputs only
    EXPECT_EQ(solution.uniquePathsRecursive(1, 1), 1);
    EXPECT_EQ(solution.uniquePathsRecursive(2, 2), 2);
    EXPECT_EQ(solution.uniquePathsRecursive(3, 3), 6);
    EXPECT_EQ(solution.uniquePathsRecursive(4, 3), 10);
    
    // Don't test larger values with pure recursion due to exponential complexity
}

TEST_F(UniquePathsTest, MemoizationEfficiency) {
    // Test that memoization significantly improves over pure recursion
    int m = 10, n = 10;
    
    auto start = std::chrono::high_resolution_clock::now();
    int result1 = solution.uniquePathsMemo(m, n);
    auto end = std::chrono::high_resolution_clock::now();
    auto memoDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Compare with DP approach
    start = std::chrono::high_resolution_clock::now();
    int result2 = solution.uniquePathsDP2D(m, n);
    end = std::chrono::high_resolution_clock::now();
    auto dpDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    EXPECT_EQ(result1, result2);
    EXPECT_LT(memoDuration.count(), 1000) << "Memoization should be efficient";
    
    // Memoization might be slightly slower due to map overhead, but should be reasonable
    EXPECT_LT(memoDuration.count(), dpDuration.count() * 5) << "Memoization should be reasonably competitive";
}

// Algorithm-specific tests
TEST_F(UniquePathsTest, BFSSpecificTest) {
    // BFS should produce same results as other approaches
    int m = 5, n = 4;
    int expected = solution.uniquePathsDP2D(m, n);
    EXPECT_EQ(solution.uniquePathsBFS(m, n), expected);
}

TEST_F(UniquePathsTest, SpaceComplexityVerification) {
    // Verify that 1D DP uses less space conceptually
    // (We can't measure actual memory usage in unit test easily,
    // but we verify correctness of space-optimized version)
    
    for (int m = 2; m <= 10; ++m) {
        for (int n = 2; n <= 10; ++n) {
            int result2D = solution.uniquePathsDP2D(m, n);
            int result1D = solution.uniquePathsDP1D(m, n);
            EXPECT_EQ(result2D, result1D) << "1D DP should match 2D DP for m=" << m << ", n=" << n;
        }
    }
}

TEST_F(UniquePathsTest, CombinatorialVerification) {
    // Verify mathematical formula: C(m+n-2, m-1)
    
    // Manual verification for small values
    // 3x3: need 2 down, 2 right = 4 total moves, choose 2 = C(4,2) = 6
    int totalMoves = 3 + 3 - 2; // 4
    int downMoves = 3 - 1; // 2
    // C(4,2) = 4!/(2!*2!) = 24/4 = 6
    EXPECT_EQ(solution.uniquePathsMath(3, 3), 6);
    
    // 4x2: need 3 down, 1 right = 4 total moves, choose 3 = C(4,3) = 4
    EXPECT_EQ(solution.uniquePathsMath(4, 2), 4);
}

TEST_F(UniquePathsTest, OverflowHandling) {
    // Test that mathematical approach handles large values without overflow
    // (within the constraint limits)
    
    int m = 50, n = 50;
    
    // Mathematical approach should handle this without overflow
    int mathResult = solution.uniquePathsMath(m, n);
    int dpResult = solution.uniquePathsDP1D(m, n);
    
    EXPECT_EQ(mathResult, dpResult) << "Math approach should handle large values correctly";
    EXPECT_GT(mathResult, 0) << "Result should be positive";
}

TEST_F(UniquePathsTest, EdgeCaseBoundary) {
    // Test edge cases at constraint boundaries
    
    // Minimum values
    testAllApproaches(1, 1, 1);
    testAllApproaches(1, 100, 1);
    testAllApproaches(100, 1, 1);
    
    // Various small rectangles
    testAllApproaches(2, 3, 3);
    testAllApproaches(3, 4, 10);
    testAllApproaches(4, 5, 35);
}

TEST_F(UniquePathsTest, ConsistencyAcrossApproaches) {
    // Test multiple grid sizes for consistency
    std::vector<std::pair<int, int>> testCases = {
        {1, 1}, {1, 10}, {10, 1}, {2, 2}, {2, 5}, {5, 2},
        {3, 3}, {3, 7}, {7, 3}, {4, 6}, {6, 4}, {5, 8}, {8, 5}
    };
    
    for (const auto& testCase : testCases) {
        int m = testCase.first;
        int n = testCase.second;
        
        // Get expected result from DP approach
        int expected = solution.uniquePathsDP2D(m, n);
        
        // Test all approaches
        testAllApproaches(m, n, expected);
    }
}

TEST_F(UniquePathsTest, RealWorldScenario) {
    // Test with realistic robot grid scenarios
    
    // Small room: 5x5
    testAllApproaches(5, 5, 70);
    
    // Narrow corridor: 2x20
    testAllApproaches(2, 20, 20);
    
    // Wide corridor: 20x2  
    testAllApproaches(20, 2, 20);
    
    // Square room: 10x10
    testAllApproaches(10, 10, 48620);
}