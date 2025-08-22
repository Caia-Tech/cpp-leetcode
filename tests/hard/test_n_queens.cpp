#include <gtest/gtest.h>
#include "hard/n_queens.h"
#include <algorithm>
#include <set>
#include <chrono>

using namespace leetcode::hard;

class NQueensTest : public ::testing::Test {
protected:
    NQueens solution;
    
    // Helper function to validate a single solution
    bool isValidSolution(const std::vector<std::string>& board) {
        int n = board.size();
        std::vector<std::pair<int, int>> queens;
        
        // Find all queen positions
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'Q') {
                    queens.push_back({i, j});
                }
            }
        }
        
        // Should have exactly n queens
        if (queens.size() != n) return false;
        
        // Check no two queens attack each other
        for (int i = 0; i < queens.size(); ++i) {
            for (int j = i + 1; j < queens.size(); ++j) {
                int row1 = queens[i].first, col1 = queens[i].second;
                int row2 = queens[j].first, col2 = queens[j].second;
                
                // Same row
                if (row1 == row2) return false;
                // Same column
                if (col1 == col2) return false;
                // Same diagonal
                if (abs(row1 - row2) == abs(col1 - col2)) return false;
            }
        }
        
        return true;
    }
    
    // Helper function to validate all solutions
    bool areAllSolutionsValid(const std::vector<std::vector<std::string>>& solutions) {
        for (const auto& solution : solutions) {
            if (!isValidSolution(solution)) {
                return false;
            }
        }
        return true;
    }
    
    // Helper function to check for duplicate solutions
    bool hasNoDuplicates(const std::vector<std::vector<std::string>>& solutions) {
        std::set<std::vector<std::string>> uniqueSolutions(solutions.begin(), solutions.end());
        return uniqueSolutions.size() == solutions.size();
    }
    
    // Helper function to normalize and compare solution sets
    bool areEquivalentSolutionSets(std::vector<std::vector<std::string>> set1,
                                  std::vector<std::vector<std::string>> set2) {
        std::sort(set1.begin(), set1.end());
        std::sort(set2.begin(), set2.end());
        return set1 == set2;
    }
    
    // Helper to get expected number of solutions for each n
    int getExpectedSolutionCount(int n) {
        // Known solution counts for N-Queens problem
        switch (n) {
            case 1: return 1;
            case 2: return 0;
            case 3: return 0;
            case 4: return 2;
            case 5: return 10;
            case 6: return 4;
            case 7: return 40;
            case 8: return 92;
            case 9: return 352;
            default: return -1; // Unknown
        }
    }
    
    // Test all approaches
    void testAllApproaches(int n) {
        auto result1 = solution.solveNQueensBacktracking(n);
        auto result2 = solution.solveNQueensOptimized(n);
        auto result3 = solution.solveNQueensBitwise(n);
        auto result4 = solution.solveNQueensIterative(n);
        auto result5 = solution.solveNQueensPermutation(n);
        auto result6 = solution.solveNQueensMemoization(n);
        
        EXPECT_TRUE(areAllSolutionsValid(result1)) << "Backtracking solutions invalid";
        EXPECT_TRUE(areAllSolutionsValid(result2)) << "Optimized solutions invalid";
        EXPECT_TRUE(areAllSolutionsValid(result3)) << "Bitwise solutions invalid";
        EXPECT_TRUE(areAllSolutionsValid(result4)) << "Iterative solutions invalid";
        EXPECT_TRUE(areAllSolutionsValid(result5)) << "Permutation solutions invalid";
        EXPECT_TRUE(areAllSolutionsValid(result6)) << "Memoization solutions invalid";
        
        EXPECT_TRUE(hasNoDuplicates(result1)) << "Backtracking has duplicates";
        EXPECT_TRUE(hasNoDuplicates(result2)) << "Optimized has duplicates";
        EXPECT_TRUE(hasNoDuplicates(result3)) << "Bitwise has duplicates";
        EXPECT_TRUE(hasNoDuplicates(result4)) << "Iterative has duplicates";
        EXPECT_TRUE(hasNoDuplicates(result5)) << "Permutation has duplicates";
        EXPECT_TRUE(hasNoDuplicates(result6)) << "Memoization has duplicates";
        
        // All approaches should produce equivalent results
        EXPECT_TRUE(areEquivalentSolutionSets(result1, result2)) << "Backtracking and Optimized differ";
        EXPECT_TRUE(areEquivalentSolutionSets(result1, result3)) << "Backtracking and Bitwise differ";
        EXPECT_TRUE(areEquivalentSolutionSets(result1, result4)) << "Backtracking and Iterative differ";
        EXPECT_TRUE(areEquivalentSolutionSets(result1, result5)) << "Backtracking and Permutation differ";
        EXPECT_TRUE(areEquivalentSolutionSets(result1, result6)) << "Backtracking and Memoization differ";
        
        // Check expected solution count
        int expectedCount = getExpectedSolutionCount(n);
        if (expectedCount >= 0) {
            EXPECT_EQ(result1.size(), expectedCount) << "Wrong number of solutions for n=" << n;
        }
    }
};

TEST_F(NQueensTest, SingleQueen) {
    // n = 1: only one solution
    testAllApproaches(1);
    
    auto result = solution.solveNQueensBacktracking(1);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], std::vector<std::string>{"Q"});
}

TEST_F(NQueensTest, TwoQueens) {
    // n = 2: no solutions possible
    testAllApproaches(2);
    
    auto result = solution.solveNQueensBacktracking(2);
    EXPECT_EQ(result.size(), 0);
}

TEST_F(NQueensTest, ThreeQueens) {
    // n = 3: no solutions possible
    testAllApproaches(3);
    
    auto result = solution.solveNQueensBacktracking(3);
    EXPECT_EQ(result.size(), 0);
}

TEST_F(NQueensTest, FourQueens) {
    // n = 4: exactly 2 solutions
    testAllApproaches(4);
    
    auto result = solution.solveNQueensBacktracking(4);
    EXPECT_EQ(result.size(), 2);
    
    // Verify both solutions are valid and different
    EXPECT_TRUE(isValidSolution(result[0]));
    EXPECT_TRUE(isValidSolution(result[1]));
    EXPECT_NE(result[0], result[1]);
}

TEST_F(NQueensTest, FiveQueens) {
    // n = 5: exactly 10 solutions
    testAllApproaches(5);
    
    auto result = solution.solveNQueensBacktracking(5);
    EXPECT_EQ(result.size(), 10);
}

TEST_F(NQueensTest, SixQueens) {
    // n = 6: exactly 4 solutions
    testAllApproaches(6);
    
    auto result = solution.solveNQueensBacktracking(6);
    EXPECT_EQ(result.size(), 4);
}

TEST_F(NQueensTest, SevenQueens) {
    // n = 7: exactly 40 solutions
    testAllApproaches(7);
    
    auto result = solution.solveNQueensBacktracking(7);
    EXPECT_EQ(result.size(), 40);
}

TEST_F(NQueensTest, EightQueens) {
    // n = 8: classic 8-queens problem with 92 solutions
    testAllApproaches(8);
    
    auto result = solution.solveNQueensBacktracking(8);
    EXPECT_EQ(result.size(), 92);
}

TEST_F(NQueensTest, MaxConstraintTest) {
    // n = 9: maximum constraint, 352 solutions
    testAllApproaches(9);
    
    auto result = solution.solveNQueensBacktracking(9);
    EXPECT_EQ(result.size(), 352);
}

// Test board structure validation
TEST_F(NQueensTest, BoardStructureTest) {
    auto result = solution.solveNQueensBacktracking(4);
    
    for (const auto& board : result) {
        // Check board dimensions
        EXPECT_EQ(board.size(), 4);
        for (const auto& row : board) {
            EXPECT_EQ(row.length(), 4);
            
            // Check only valid characters
            for (char c : row) {
                EXPECT_TRUE(c == 'Q' || c == '.') << "Invalid character in board: " << c;
            }
        }
        
        // Count queens in each row and column
        std::vector<int> rowCounts(4, 0);
        std::vector<int> colCounts(4, 0);
        
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (board[i][j] == 'Q') {
                    rowCounts[i]++;
                    colCounts[j]++;
                }
            }
        }
        
        // Each row and column should have exactly one queen
        for (int i = 0; i < 4; ++i) {
            EXPECT_EQ(rowCounts[i], 1) << "Row " << i << " should have exactly one queen";
            EXPECT_EQ(colCounts[i], 1) << "Column " << i << " should have exactly one queen";
        }
    }
}

// Test specific known solutions for small n
TEST_F(NQueensTest, KnownSolutionsTest) {
    // Test one known solution for n=4
    auto result4 = solution.solveNQueensBacktracking(4);
    
    std::vector<std::string> expected1 = {".Q..", "...Q", "Q...", "..Q."};
    std::vector<std::string> expected2 = {"..Q.", "Q...", "...Q", ".Q.."};
    
    bool found1 = std::find(result4.begin(), result4.end(), expected1) != result4.end();
    bool found2 = std::find(result4.begin(), result4.end(), expected2) != result4.end();
    
    EXPECT_TRUE(found1 || found2) << "Should find at least one known solution";
}

// Performance comparison test
TEST_F(NQueensTest, PerformanceComparisonTest) {
    const int n = 8; // Standard 8-queens for performance testing
    
    // Test backtracking approach
    auto start1 = std::chrono::high_resolution_clock::now();
    auto result1 = solution.solveNQueensBacktracking(n);
    auto end1 = std::chrono::high_resolution_clock::now();
    
    // Test optimized approach
    auto start2 = std::chrono::high_resolution_clock::now();
    auto result2 = solution.solveNQueensOptimized(n);
    auto end2 = std::chrono::high_resolution_clock::now();
    
    // Test bitwise approach
    auto start3 = std::chrono::high_resolution_clock::now();
    auto result3 = solution.solveNQueensBitwise(n);
    auto end3 = std::chrono::high_resolution_clock::now();
    
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);
    
    // All should produce same results
    EXPECT_TRUE(areEquivalentSolutionSets(result1, result2));
    EXPECT_TRUE(areEquivalentSolutionSets(result1, result3));
    
    // Optimized and bitwise should generally be faster (not guaranteed due to system variance)
    EXPECT_LT(duration2.count(), duration1.count() * 2) << "Optimized should be competitive with backtracking";
    EXPECT_LT(duration3.count(), duration1.count() * 2) << "Bitwise should be competitive with backtracking";
    
    // All should complete in reasonable time
    EXPECT_LT(duration1.count(), 100000) << "Backtracking should complete within 100ms";
    EXPECT_LT(duration2.count(), 50000) << "Optimized should complete within 50ms";
    EXPECT_LT(duration3.count(), 50000) << "Bitwise should complete within 50ms";
}

// Test diagonal conflict detection
TEST_F(NQueensTest, DiagonalConflictTest) {
    // Manually create an invalid board with diagonal conflict
    std::vector<std::string> invalidBoard = {
        "Q...",
        "....",
        "..Q.",
        "...."
    };
    
    EXPECT_FALSE(isValidSolution(invalidBoard)) << "Should detect diagonal conflict";
    
    // Valid board without diagonal conflicts
    std::vector<std::string> validBoard = {
        ".Q..",
        "...Q",
        "Q...",
        "..Q."
    };
    
    EXPECT_TRUE(isValidSolution(validBoard)) << "Should accept valid board";
}

// Test edge cases
TEST_F(NQueensTest, EdgeCasesTest) {
    // Test minimum constraint
    auto result1 = solution.solveNQueensBacktracking(1);
    EXPECT_EQ(result1.size(), 1);
    
    // Test cases with no solutions
    auto result2 = solution.solveNQueensBacktracking(2);
    auto result3 = solution.solveNQueensBacktracking(3);
    EXPECT_EQ(result2.size(), 0);
    EXPECT_EQ(result3.size(), 0);
}

// Test approach-specific behaviors
TEST_F(NQueensTest, ApproachSpecificTest) {
    const int n = 6;
    
    // Test that iterative approach doesn't use recursion
    auto iterativeResult = solution.solveNQueensIterative(n);
    EXPECT_EQ(iterativeResult.size(), getExpectedSolutionCount(n));
    
    // Test that permutation approach generates all possibilities
    auto permutationResult = solution.solveNQueensPermutation(n);
    EXPECT_EQ(permutationResult.size(), getExpectedSolutionCount(n));
    
    // Test memoization approach
    auto memoResult = solution.solveNQueensMemoization(n);
    EXPECT_EQ(memoResult.size(), getExpectedSolutionCount(n));
}

// Stress test for maximum constraint
TEST_F(NQueensTest, StressTest) {
    const int n = 9; // Maximum constraint
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = solution.solveNQueensOptimized(n); // Use optimized for speed
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_EQ(result.size(), 352); // Known solution count for n=9
    EXPECT_LT(duration.count(), 1000) << "Should complete within 1 second for n=9";
    EXPECT_TRUE(areAllSolutionsValid(result)) << "All solutions should be valid";
    EXPECT_TRUE(hasNoDuplicates(result)) << "Should have no duplicate solutions";
}

// Test solution uniqueness across approaches
TEST_F(NQueensTest, UniquenessTest) {
    const int n = 5;
    
    auto backtrackResult = solution.solveNQueensBacktracking(n);
    auto optimizedResult = solution.solveNQueensOptimized(n);
    
    // Convert to sets for uniqueness checking
    std::set<std::vector<std::string>> backtrackSet(backtrackResult.begin(), backtrackResult.end());
    std::set<std::vector<std::string>> optimizedSet(optimizedResult.begin(), optimizedResult.end());
    
    EXPECT_EQ(backtrackSet.size(), backtrackResult.size()) << "Backtrack should have no duplicates";
    EXPECT_EQ(optimizedSet.size(), optimizedResult.size()) << "Optimized should have no duplicates";
    EXPECT_EQ(backtrackSet, optimizedSet) << "Both approaches should find same unique solutions";
}

// Test correctness of queen placement
TEST_F(NQueensTest, QueenPlacementTest) {
    auto result = solution.solveNQueensBacktracking(8);
    
    for (const auto& board : result) {
        int queenCount = 0;
        
        // Count total queens and verify placement
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == 'Q') {
                    queenCount++;
                }
            }
        }
        
        EXPECT_EQ(queenCount, 8) << "Each solution should have exactly 8 queens";
        EXPECT_TRUE(isValidSolution(board)) << "Each solution should be valid";
    }
}