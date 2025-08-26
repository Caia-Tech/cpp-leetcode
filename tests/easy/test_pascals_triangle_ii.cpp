#include <gtest/gtest.h>
#include "../../src/easy/pascals_triangle_ii.h"
#include <vector>

using namespace leetcode::easy;

// Test fixture for Pascal's Triangle II
class PascalsTriangleIITest : public ::testing::Test {
protected:
    void testAllApproaches(int rowIndex, const std::vector<int>& expected) {
        EXPECT_EQ(PascalsTriangleII::getRowDP(rowIndex), expected) << "DP approach failed for row " << rowIndex;
        EXPECT_EQ(PascalsTriangleII::getRowMath(rowIndex), expected) << "Math approach failed for row " << rowIndex;
        EXPECT_EQ(PascalsTriangleII::getRowSpaceOptimized(rowIndex), expected) << "Space optimized failed for row " << rowIndex;
        EXPECT_EQ(PascalsTriangleII::getRowRecursive(rowIndex), expected) << "Recursive approach failed for row " << rowIndex;
        EXPECT_EQ(PascalsTriangleII::getRowIterative(rowIndex), expected) << "Iterative approach failed for row " << rowIndex;
        EXPECT_EQ(PascalsTriangleII::getRowBinomial(rowIndex), expected) << "Binomial approach failed for row " << rowIndex;
    }
};

// Test Case 1: Base case - row 0
TEST_F(PascalsTriangleIITest, Row0) {
    testAllApproaches(0, {1});
}

// Test Case 2: Row 1
TEST_F(PascalsTriangleIITest, Row1) {
    testAllApproaches(1, {1, 1});
}

// Test Case 3: Row 2
TEST_F(PascalsTriangleIITest, Row2) {
    testAllApproaches(2, {1, 2, 1});
}

// Test Case 4: Row 3 (LeetCode example)
TEST_F(PascalsTriangleIITest, Row3) {
    testAllApproaches(3, {1, 3, 3, 1});
}

// Test Case 5: Row 4
TEST_F(PascalsTriangleIITest, Row4) {
    testAllApproaches(4, {1, 4, 6, 4, 1});
}

// Test Case 6: Row 5
TEST_F(PascalsTriangleIITest, Row5) {
    testAllApproaches(5, {1, 5, 10, 10, 5, 1});
}

// Test Case 7: Row 6
TEST_F(PascalsTriangleIITest, Row6) {
    testAllApproaches(6, {1, 6, 15, 20, 15, 6, 1});
}

// Test Case 8: Row 10 (medium size)
TEST_F(PascalsTriangleIITest, Row10) {
    testAllApproaches(10, {1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1});
}

// Test Case 9: Row 15 (larger size)
TEST_F(PascalsTriangleIITest, Row15) {
    testAllApproaches(15, {1, 15, 105, 455, 1365, 3003, 5005, 6435, 6435, 5005, 3003, 1365, 455, 105, 15, 1});
}

// Test Case 10: Row 20 (stress test)
TEST_F(PascalsTriangleIITest, Row20) {
    std::vector<int> expected = {1, 20, 190, 1140, 4845, 15504, 38760, 77520, 125970, 167960, 
                                184756, 167960, 125970, 77520, 38760, 15504, 4845, 1140, 190, 20, 1};
    testAllApproaches(20, expected);
}

// Test Case 11: Symmetry property test
TEST_F(PascalsTriangleIITest, SymmetryProperty) {
    for (int row = 0; row <= 10; ++row) {
        auto result = PascalsTriangleII::getRowDP(row);
        
        // Check symmetry: result[i] should equal result[row-i]
        for (int i = 0; i <= row; ++i) {
            EXPECT_EQ(result[i], result[row - i]) << "Symmetry failed at row " << row << ", position " << i;
        }
    }
}

// Test Case 12: Sum property test (2^n)
TEST_F(PascalsTriangleIITest, SumProperty) {
    for (int row = 0; row <= 20; ++row) {
        auto result = PascalsTriangleII::getRowDP(row);
        
        int sum = 0;
        for (int val : result) {
            sum += val;
        }
        
        int expected_sum = 1 << row; // 2^row
        EXPECT_EQ(sum, expected_sum) << "Sum property failed for row " << row;
    }
}

// Test Case 13: Size verification
TEST_F(PascalsTriangleIITest, SizeVerification) {
    for (int row = 0; row <= 15; ++row) {
        auto result = PascalsTriangleII::getRowDP(row);
        EXPECT_EQ(result.size(), static_cast<size_t>(row + 1)) << "Size incorrect for row " << row;
    }
}

// Test Case 14: Edge case - maximum constraint
TEST_F(PascalsTriangleIITest, MaxConstraint) {
    // Test row 33 (maximum per constraints)
    auto result = PascalsTriangleII::getRowBinomial(33);
    EXPECT_EQ(result.size(), 34);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[33], 1);
    EXPECT_EQ(result[1], 33);
    EXPECT_EQ(result[32], 33);
}

// Test Case 15: Binomial coefficient property
TEST_F(PascalsTriangleIITest, BinomialProperty) {
    // Test that C(n,k) = C(n,n-k)
    for (int n = 5; n <= 10; ++n) {
        auto row = PascalsTriangleII::getRowMath(n);
        for (int k = 0; k <= n; ++k) {
            EXPECT_EQ(row[k], row[n - k]) << "Binomial symmetry failed for C(" << n << "," << k << ")";
        }
    }
}

// Test Case 16: Pascal's triangle recurrence relation
TEST_F(PascalsTriangleIITest, RecurrenceRelation) {
    // Test that Pascal(n,k) = Pascal(n-1,k-1) + Pascal(n-1,k)
    for (int n = 2; n <= 10; ++n) {
        auto current_row = PascalsTriangleII::getRowDP(n);
        auto prev_row = PascalsTriangleII::getRowDP(n - 1);
        
        for (int k = 1; k < n; ++k) {
            int expected = prev_row[k - 1] + prev_row[k];
            EXPECT_EQ(current_row[k], expected) 
                << "Recurrence relation failed for Pascal(" << n << "," << k << ")";
        }
    }
}

// Test Case 17: Performance comparison test
TEST_F(PascalsTriangleIITest, PerformanceTest) {
    const int test_row = 25;
    
    // All approaches should give the same result
    auto dp_result = PascalsTriangleII::getRowDP(test_row);
    auto math_result = PascalsTriangleII::getRowMath(test_row);
    auto space_result = PascalsTriangleII::getRowSpaceOptimized(test_row);
    auto recursive_result = PascalsTriangleII::getRowRecursive(test_row);
    auto iterative_result = PascalsTriangleII::getRowIterative(test_row);
    auto binomial_result = PascalsTriangleII::getRowBinomial(test_row);
    
    EXPECT_EQ(dp_result, math_result);
    EXPECT_EQ(dp_result, space_result);
    EXPECT_EQ(dp_result, recursive_result);
    EXPECT_EQ(dp_result, iterative_result);
    EXPECT_EQ(dp_result, binomial_result);
}

// Test Case 18: Boundary elements test
TEST_F(PascalsTriangleIITest, BoundaryElements) {
    for (int row = 0; row <= 15; ++row) {
        auto result = PascalsTriangleII::getRowDP(row);
        
        // First and last elements should always be 1
        EXPECT_EQ(result[0], 1) << "First element not 1 for row " << row;
        EXPECT_EQ(result[row], 1) << "Last element not 1 for row " << row;
    }
}

// Test Case 19: Mathematical identity test
TEST_F(PascalsTriangleIITest, MathematicalIdentity) {
    // Test Pascal's identity: C(n,k) = C(n-1,k-1) + C(n-1,k)
    for (int n = 2; n <= 12; ++n) {
        for (int k = 1; k < n; ++k) {
            auto row_n = PascalsTriangleII::getRowBinomial(n);
            auto row_n_minus_1 = PascalsTriangleII::getRowBinomial(n - 1);
            
            int identity_result = row_n_minus_1[k - 1] + row_n_minus_1[k];
            EXPECT_EQ(row_n[k], identity_result) 
                << "Pascal's identity failed for n=" << n << ", k=" << k;
        }
    }
}

// Test Case 20: Zero row verification
TEST_F(PascalsTriangleIITest, ZeroRowVerification) {
    auto result = PascalsTriangleII::getRowDP(0);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 1);
    
    // Test all approaches for row 0
    testAllApproaches(0, {1});
}

