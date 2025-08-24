#include <gtest/gtest.h>
#include "../../src/easy/pascals_triangle.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class PascalsTriangleTest : public ::testing::Test {
protected:
    // Helper to compare triangles for equality
    void testAllApproaches(int numRows, const std::vector<std::vector<int>>& expected) {
        PascalsTriangle solution;
        
        EXPECT_EQ(solution.generateIterative(numRows), expected) 
            << "Iterative approach failed for numRows: " << numRows;
        EXPECT_EQ(solution.generateCombinatorial(numRows), expected) 
            << "Combinatorial approach failed for numRows: " << numRows;
        EXPECT_EQ(solution.generateRecursive(numRows), expected) 
            << "Recursive approach failed for numRows: " << numRows;
        EXPECT_EQ(solution.generateSpaceOptimized(numRows), expected) 
            << "Space-optimized approach failed for numRows: " << numRows;
        EXPECT_EQ(solution.generateBitwise(numRows), expected) 
            << "Bitwise approach failed for numRows: " << numRows;
        EXPECT_EQ(solution.generateFunctional(numRows), expected) 
            << "Functional approach failed for numRows: " << numRows;
    }
};

// LeetCode Example Test Cases

TEST_F(PascalsTriangleTest, LeetCodeExample1) {
    // Input: numRows = 5
    // Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1}
    };
    testAllApproaches(5, expected);
}

TEST_F(PascalsTriangleTest, LeetCodeExample2) {
    // Input: numRows = 1
    // Output: [[1]]
    std::vector<std::vector<int>> expected = {{1}};
    testAllApproaches(1, expected);
}

// Edge Cases

TEST_F(PascalsTriangleTest, TwoRows) {
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1}
    };
    testAllApproaches(2, expected);
}

TEST_F(PascalsTriangleTest, ThreeRows) {
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1}
    };
    testAllApproaches(3, expected);
}

TEST_F(PascalsTriangleTest, FourRows) {
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1}
    };
    testAllApproaches(4, expected);
}

// Systematic Row Testing

TEST_F(PascalsTriangleTest, SixRows) {
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1},
        {1, 5, 10, 10, 5, 1}
    };
    testAllApproaches(6, expected);
}

TEST_F(PascalsTriangleTest, SevenRows) {
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1},
        {1, 5, 10, 10, 5, 1},
        {1, 6, 15, 20, 15, 6, 1}
    };
    testAllApproaches(7, expected);
}

TEST_F(PascalsTriangleTest, EightRows) {
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1},
        {1, 5, 10, 10, 5, 1},
        {1, 6, 15, 20, 15, 6, 1},
        {1, 7, 21, 35, 35, 21, 7, 1}
    };
    testAllApproaches(8, expected);
}

// Mathematical Property Tests

TEST_F(PascalsTriangleTest, RowSumProperty) {
    // Test that sum of each row equals 2^row_index
    PascalsTriangle solution;
    auto triangle = solution.generateIterative(10);
    
    for (int row = 0; row < 10; ++row) {
        int sum = 0;
        for (int val : triangle[row]) {
            sum += val;
        }
        EXPECT_EQ(sum, 1 << row) << "Row " << row << " sum should be " << (1 << row);
    }
}

TEST_F(PascalsTriangleTest, SymmetryProperty) {
    // Test that each row is symmetric
    PascalsTriangle solution;
    auto triangle = solution.generateIterative(10);
    
    for (int row = 0; row < 10; ++row) {
        const auto& currentRow = triangle[row];
        int size = currentRow.size();
        
        for (int i = 0; i < size / 2; ++i) {
            EXPECT_EQ(currentRow[i], currentRow[size - 1 - i]) 
                << "Row " << row << " is not symmetric";
        }
    }
}

TEST_F(PascalsTriangleTest, EdgeValuesProperty) {
    // Test that first and last elements of each row are 1
    PascalsTriangle solution;
    auto triangle = solution.generateIterative(15);
    
    for (int row = 0; row < 15; ++row) {
        const auto& currentRow = triangle[row];
        EXPECT_EQ(currentRow[0], 1) << "First element of row " << row << " should be 1";
        EXPECT_EQ(currentRow.back(), 1) << "Last element of row " << row << " should be 1";
    }
}

// Larger Triangles

TEST_F(PascalsTriangleTest, TenRows) {
    std::vector<std::vector<int>> expected = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1},
        {1, 5, 10, 10, 5, 1},
        {1, 6, 15, 20, 15, 6, 1},
        {1, 7, 21, 35, 35, 21, 7, 1},
        {1, 8, 28, 56, 70, 56, 28, 8, 1},
        {1, 9, 36, 84, 126, 126, 84, 36, 9, 1}
    };
    testAllApproaches(10, expected);
}

TEST_F(PascalsTriangleTest, FifteenRows) {
    // Test specific known values in row 14
    PascalsTriangle solution;
    auto triangle = solution.generateIterative(15);
    
    // Row 14: [1, 14, 91, 364, 1001, 2002, 3003, 3432, 3003, 2002, 1001, 364, 91, 14, 1]
    const auto& row14 = triangle[14];
    EXPECT_EQ(row14[0], 1);
    EXPECT_EQ(row14[1], 14);
    EXPECT_EQ(row14[2], 91);
    EXPECT_EQ(row14[3], 364);
    EXPECT_EQ(row14[4], 1001);
    EXPECT_EQ(row14[7], 3432); // Peak value
    EXPECT_EQ(row14[14], 1);
}

// Stress Testing

TEST_F(PascalsTriangleTest, TwentyRows) {
    // Test that all approaches produce same result for larger input
    PascalsTriangle solution;
    
    auto iterative = solution.generateIterative(20);
    auto combinatorial = solution.generateCombinatorial(20);
    auto recursive = solution.generateRecursive(20);
    auto spaceOptimized = solution.generateSpaceOptimized(20);
    auto bitwise = solution.generateBitwise(20);
    auto functional = solution.generateFunctional(20);
    
    EXPECT_EQ(iterative, combinatorial);
    EXPECT_EQ(iterative, recursive);
    EXPECT_EQ(iterative, spaceOptimized);
    EXPECT_EQ(iterative, bitwise);
    EXPECT_EQ(iterative, functional);
}

TEST_F(PascalsTriangleTest, MaxConstraintSize) {
    // Test at maximum constraint size
    PascalsTriangle solution;
    
    // Generate triangle with 30 rows (maximum constraint)
    auto triangle = solution.generateIterative(30);
    
    EXPECT_EQ(triangle.size(), 30);
    EXPECT_EQ(triangle[29].size(), 30); // Last row has 30 elements
    EXPECT_EQ(triangle[29][0], 1);      // First element is 1
    EXPECT_EQ(triangle[29][29], 1);     // Last element is 1
}

// Specific Value Verification

TEST_F(PascalsTriangleTest, KnownCombinationValues) {
    PascalsTriangle solution;
    auto triangle = solution.generateIterative(11);
    
    // Test some known combination values
    EXPECT_EQ(triangle[10][0], 1);      // C(10,0) = 1
    EXPECT_EQ(triangle[10][1], 10);     // C(10,1) = 10
    EXPECT_EQ(triangle[10][2], 45);     // C(10,2) = 45
    EXPECT_EQ(triangle[10][3], 120);    // C(10,3) = 120
    EXPECT_EQ(triangle[10][5], 252);    // C(10,5) = 252
}

// Algorithm-Specific Tests

TEST_F(PascalsTriangleTest, BitwisePatternsSmallRows) {
    // Test that bitwise approach handles small rows correctly
    PascalsTriangle solution;
    
    // Test rows 0-4 where powers of 11 pattern applies
    for (int numRows = 1; numRows <= 5; ++numRows) {
        auto iterative = solution.generateIterative(numRows);
        auto bitwise = solution.generateBitwise(numRows);
        EXPECT_EQ(iterative, bitwise) << "Bitwise fails for numRows: " << numRows;
    }
}

TEST_F(PascalsTriangleTest, RecursiveMemoization) {
    // Test that recursive approach with memoization works correctly
    PascalsTriangle solution;
    
    auto result1 = solution.generateRecursive(8);
    auto result2 = solution.generateRecursive(8); // Should use memoized values
    
    EXPECT_EQ(result1, result2);
    
    // Verify specific memoized calculations
    auto expected = solution.generateIterative(8);
    EXPECT_EQ(result1, expected);
}

// Performance Boundary Tests

TEST_F(PascalsTriangleTest, ConsistencyAcrossApproaches) {
    // Verify all approaches give same results for various sizes
    std::vector<int> testSizes = {1, 5, 10, 15, 20};
    
    PascalsTriangle solution;
    
    for (int size : testSizes) {
        auto baseline = solution.generateIterative(size);
        
        EXPECT_EQ(solution.generateCombinatorial(size), baseline) 
            << "Combinatorial differs at size " << size;
        EXPECT_EQ(solution.generateRecursive(size), baseline) 
            << "Recursive differs at size " << size;
        EXPECT_EQ(solution.generateSpaceOptimized(size), baseline) 
            << "Space-optimized differs at size " << size;
        EXPECT_EQ(solution.generateBitwise(size), baseline) 
            << "Bitwise differs at size " << size;
        EXPECT_EQ(solution.generateFunctional(size), baseline) 
            << "Functional differs at size " << size;
    }
}

// Structure Validation Tests

TEST_F(PascalsTriangleTest, TriangleStructure) {
    PascalsTriangle solution;
    auto triangle = solution.generateIterative(12);
    
    // Verify triangle structure
    EXPECT_EQ(triangle.size(), 12);
    
    for (int row = 0; row < 12; ++row) {
        EXPECT_EQ(triangle[row].size(), row + 1) 
            << "Row " << row << " should have " << (row + 1) << " elements";
    }
}

TEST_F(PascalsTriangleTest, ElementRecursionProperty) {
    // Test that each interior element equals sum of two elements above it
    PascalsTriangle solution;
    auto triangle = solution.generateIterative(10);
    
    for (int row = 2; row < 10; ++row) {
        for (int col = 1; col < row; ++col) {
            int expected = triangle[row - 1][col - 1] + triangle[row - 1][col];
            EXPECT_EQ(triangle[row][col], expected)
                << "Element at (" << row << "," << col << ") should be " << expected;
        }
    }
}

// Edge Case Verification

TEST_F(PascalsTriangleTest, SingleRowTriangle) {
    std::vector<std::vector<int>> expected = {{1}};
    testAllApproaches(1, expected);
}

TEST_F(PascalsTriangleTest, RowCountConsistency) {
    // Verify that numRows parameter is respected
    for (int numRows = 1; numRows <= 10; ++numRows) {
        PascalsTriangle solution;
        auto result = solution.generateIterative(numRows);
        EXPECT_EQ(result.size(), numRows) 
            << "Triangle should have exactly " << numRows << " rows";
    }
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode