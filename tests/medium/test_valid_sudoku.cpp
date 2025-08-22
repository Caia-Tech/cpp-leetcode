#include <gtest/gtest.h>
#include "medium/valid_sudoku.h"

using namespace leetcode::medium;

class ValidSudokuTest : public ::testing::Test {
protected:
    ValidSudoku solution;
    
    // Helper function to test all approaches
    void testAllApproaches(const std::vector<std::vector<char>>& board, bool expected) {
        EXPECT_EQ(solution.isValidSudokuHashSets(board), expected) 
            << "Hash sets approach failed";
        
        EXPECT_EQ(solution.isValidSudokuEncoded(board), expected) 
            << "Encoded approach failed";
        
        EXPECT_EQ(solution.isValidSudokuBitManipulation(board), expected) 
            << "Bit manipulation approach failed";
        
        EXPECT_EQ(solution.isValidSudokuThreePasses(board), expected) 
            << "Three passes approach failed";
        
        EXPECT_EQ(solution.isValidSudokuArrays(board), expected) 
            << "Arrays approach failed";
        
        EXPECT_EQ(solution.isValidSudokuRecursive(board), expected) 
            << "Recursive approach failed";
    }
    
    // Helper to create valid empty board
    std::vector<std::vector<char>> createEmptyBoard() {
        return std::vector<std::vector<char>>(9, std::vector<char>(9, '.'));
    }
};

TEST_F(ValidSudokuTest, ValidExample1) {
    std::vector<std::vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, InvalidExample1) {
    std::vector<std::vector<char>> board = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    // Invalid because there are two 8's in first column
    testAllApproaches(board, false);
}

TEST_F(ValidSudokuTest, EmptyBoard) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, SingleDigitBoard) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    board[0][0] = '1';
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, RowDuplicateInvalid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    board[0][0] = '1';
    board[0][8] = '1'; // Duplicate in same row
    testAllApproaches(board, false);
}

TEST_F(ValidSudokuTest, ColumnDuplicateInvalid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    board[0][0] = '2';
    board[8][0] = '2'; // Duplicate in same column
    testAllApproaches(board, false);
}

TEST_F(ValidSudokuTest, BoxDuplicateInvalid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    board[0][0] = '3';
    board[2][2] = '3'; // Duplicate in same 3x3 box
    testAllApproaches(board, false);
}

TEST_F(ValidSudokuTest, AllDigitsInRowValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    // Fill first row with digits 1-9
    for (int i = 0; i < 9; ++i) {
        board[0][i] = '1' + i;
    }
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, AllDigitsInColumnValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    // Fill first column with digits 1-9
    for (int i = 0; i < 9; ++i) {
        board[i][0] = '1' + i;
    }
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, AllDigitsInBoxValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    // Fill top-left 3x3 box with digits 1-9
    int digit = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = '0' + digit++;
        }
    }
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, MultipleBoxesValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Fill top-left box
    board[0][0] = '1'; board[0][1] = '2'; board[0][2] = '3';
    board[1][0] = '4'; board[1][1] = '5'; board[1][2] = '6';
    board[2][0] = '7'; board[2][1] = '8'; board[2][2] = '9';
    
    // Fill center box with different arrangement
    board[3][3] = '9'; board[3][4] = '8'; board[3][5] = '7';
    board[4][3] = '6'; board[4][4] = '5'; board[4][5] = '4';
    board[5][3] = '3'; board[5][4] = '2'; board[5][5] = '1';
    
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, PartiallyFilledValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Add some valid scattered digits
    board[0][0] = '5';
    board[1][1] = '3';
    board[2][2] = '7';
    board[3][6] = '1';
    board[4][7] = '8';
    board[8][8] = '9';
    
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, NearlyCompleteValid) {
    std::vector<std::vector<char>> board = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','.'}
    };
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, EdgeCaseAllSameDigitInvalid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    // Put '5' in multiple places that would violate constraints
    board[0][0] = '5';
    board[0][1] = '5'; // Same row
    testAllApproaches(board, false);
}

TEST_F(ValidSudokuTest, DiagonalPlacementValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    // Place digits along diagonal (should be valid as they're in different rows, columns, and boxes)
    for (int i = 0; i < 9; ++i) {
        board[i][i] = '1' + (i % 9);
    }
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, BoxBoundaryTest) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Test digits at box boundaries
    board[2][2] = '1'; // Bottom-right of top-left box
    board[2][3] = '1'; // Bottom-left of top-center box (should be valid)
    board[3][2] = '1'; // Top-right of middle-left box (should be valid)
    
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, AllBoxesDifferentDigits) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Place different digits in center of each box
    board[1][1] = '1'; // Top-left box
    board[1][4] = '2'; // Top-center box
    board[1][7] = '3'; // Top-right box
    board[4][1] = '4'; // Middle-left box
    board[4][4] = '5'; // Middle-center box
    board[4][7] = '6'; // Middle-right box
    board[7][1] = '7'; // Bottom-left box
    board[7][4] = '8'; // Bottom-center box
    board[7][7] = '9'; // Bottom-right box
    
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, MaximumDigitsInBoxValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Fill one box completely with digits 1-9
    int digit = 1;
    for (int i = 3; i < 6; ++i) {
        for (int j = 3; j < 6; ++j) {
            board[i][j] = '0' + digit++;
        }
    }
    
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, CornerCasesValid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Test corner positions
    board[0][0] = '1'; // Top-left corner
    board[0][8] = '2'; // Top-right corner
    board[8][0] = '3'; // Bottom-left corner
    board[8][8] = '4'; // Bottom-right corner
    board[4][4] = '5'; // Center
    
    testAllApproaches(board, true);
}

TEST_F(ValidSudokuTest, MultipleViolationsInvalid) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Create multiple constraint violations
    board[0][0] = '1';
    board[0][1] = '1'; // Row violation
    board[1][0] = '1'; // Column violation
    board[1][1] = '1'; // Box violation
    
    testAllApproaches(board, false);
}

// Performance test to ensure O(1) complexity
TEST_F(ValidSudokuTest, PerformanceTest) {
    // Create a complex but valid board
    std::vector<std::vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    
    auto start = std::chrono::high_resolution_clock::now();
    bool result = solution.isValidSudokuHashSets(board);
    auto end = std::chrono::high_resolution_clock::now();
    
    EXPECT_TRUE(result);
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 1000) << "Algorithm should complete very quickly for 9x9 board";
}

TEST_F(ValidSudokuTest, SpecificBoxIndexTest) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Test each box specifically
    // Box 0 (top-left)
    board[0][0] = '1';
    board[1][1] = '1'; // Should be invalid - same box
    testAllApproaches(board, false);
    
    // Reset and test box 8 (bottom-right)
    board = createEmptyBoard();
    board[6][6] = '2';
    board[8][8] = '2'; // Should be invalid - same box
    testAllApproaches(board, false);
}

TEST_F(ValidSudokuTest, BoundaryDigitsTest) {
    std::vector<std::vector<char>> board = createEmptyBoard();
    
    // Test with boundary digit values (1 and 9)
    board[0][0] = '1';
    board[1][1] = '9';
    board[2][2] = '1'; // Different box, should be valid
    
    testAllApproaches(board, true);
}