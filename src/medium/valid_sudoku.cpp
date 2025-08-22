#include "valid_sudoku.h"
#include <string>

namespace leetcode {
namespace medium {

bool ValidSudoku::isValidSudokuHashSets(const std::vector<std::vector<char>>& board) {
    // Create hash sets for rows, columns, and boxes
    std::vector<std::unordered_set<char>> rows(9);
    std::vector<std::unordered_set<char>> cols(9);
    std::vector<std::unordered_set<char>> boxes(9);
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            char digit = board[i][j];
            
            if (digit == '.') continue;
            
            // Check if digit already exists in row, column, or box
            if (rows[i].count(digit) || cols[j].count(digit) || boxes[getBoxIndex(i, j)].count(digit)) {
                return false;
            }
            
            // Add digit to corresponding sets
            rows[i].insert(digit);
            cols[j].insert(digit);
            boxes[getBoxIndex(i, j)].insert(digit);
        }
    }
    
    return true;
}

int ValidSudoku::getBoxIndex(int row, int col) {
    return (row / 3) * 3 + (col / 3);
}

bool ValidSudoku::isValidSudokuEncoded(const std::vector<std::vector<char>>& board) {
    std::unordered_set<std::string> seen;
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            char digit = board[i][j];
            
            if (digit == '.') continue;
            
            // Create encoded strings for row, column, and box constraints
            std::string rowConstraint = encodeConstraint("row", i, digit);
            std::string colConstraint = encodeConstraint("col", j, digit);
            std::string boxConstraint = encodeConstraint("box", getBoxIndex(i, j), digit);
            
            // Check if any constraint already exists
            if (seen.count(rowConstraint) || seen.count(colConstraint) || seen.count(boxConstraint)) {
                return false;
            }
            
            // Add constraints to seen set
            seen.insert(rowConstraint);
            seen.insert(colConstraint);
            seen.insert(boxConstraint);
        }
    }
    
    return true;
}

std::string ValidSudoku::encodeConstraint(const std::string& type, int index, char digit) {
    return type + "_" + std::to_string(index) + "_" + digit;
}

bool ValidSudoku::isValidSudokuBitManipulation(const std::vector<std::vector<char>>& board) {
    // Use bitsets to track digit presence (bits 1-9, bit 0 unused)
    std::vector<std::bitset<10>> rows(9);
    std::vector<std::bitset<10>> cols(9);
    std::vector<std::bitset<10>> boxes(9);
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            char digit = board[i][j];
            
            if (digit == '.') continue;
            
            int digitIndex = digit - '0';
            int boxIndex = getBoxIndex(i, j);
            
            // Check if digit already exists in row, column, or box
            if (rows[i][digitIndex] || cols[j][digitIndex] || boxes[boxIndex][digitIndex]) {
                return false;
            }
            
            // Set bits for digit presence
            rows[i][digitIndex] = 1;
            cols[j][digitIndex] = 1;
            boxes[boxIndex][digitIndex] = 1;
        }
    }
    
    return true;
}

bool ValidSudoku::isValidSudokuThreePasses(const std::vector<std::vector<char>>& board) {
    // Check all rows
    for (int i = 0; i < 9; ++i) {
        if (!isRowValid(board, i)) {
            return false;
        }
    }
    
    // Check all columns
    for (int j = 0; j < 9; ++j) {
        if (!isColumnValid(board, j)) {
            return false;
        }
    }
    
    // Check all 3x3 boxes
    for (int boxRow = 0; boxRow < 3; ++boxRow) {
        for (int boxCol = 0; boxCol < 3; ++boxCol) {
            if (!isBoxValid(board, boxRow * 3, boxCol * 3)) {
                return false;
            }
        }
    }
    
    return true;
}

bool ValidSudoku::isRowValid(const std::vector<std::vector<char>>& board, int row) {
    std::unordered_set<char> seen;
    
    for (int j = 0; j < 9; ++j) {
        char digit = board[row][j];
        
        if (digit == '.') continue;
        
        if (seen.count(digit)) {
            return false;
        }
        
        seen.insert(digit);
    }
    
    return true;
}

bool ValidSudoku::isColumnValid(const std::vector<std::vector<char>>& board, int col) {
    std::unordered_set<char> seen;
    
    for (int i = 0; i < 9; ++i) {
        char digit = board[i][col];
        
        if (digit == '.') continue;
        
        if (seen.count(digit)) {
            return false;
        }
        
        seen.insert(digit);
    }
    
    return true;
}

bool ValidSudoku::isBoxValid(const std::vector<std::vector<char>>& board, int startRow, int startCol) {
    std::unordered_set<char> seen;
    
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            char digit = board[i][j];
            
            if (digit == '.') continue;
            
            if (seen.count(digit)) {
                return false;
            }
            
            seen.insert(digit);
        }
    }
    
    return true;
}

bool ValidSudoku::isValidSudokuArrays(const std::vector<std::vector<char>>& board) {
    // Use 2D boolean arrays for tracking (index 0 unused, 1-9 for digits)
    bool rows[9][10] = {false};
    bool cols[9][10] = {false};
    bool boxes[9][10] = {false};
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            char digit = board[i][j];
            
            if (digit == '.') continue;
            
            int digitIndex = digit - '0';
            int boxIndex = getBoxIndex(i, j);
            
            // Check if digit already exists in row, column, or box
            if (rows[i][digitIndex] || cols[j][digitIndex] || boxes[boxIndex][digitIndex]) {
                return false;
            }
            
            // Mark digit as seen
            rows[i][digitIndex] = true;
            cols[j][digitIndex] = true;
            boxes[boxIndex][digitIndex] = true;
        }
    }
    
    return true;
}

bool ValidSudoku::isValidSudokuRecursive(const std::vector<std::vector<char>>& board) {
    // Validate each filled cell recursively
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] != '.' && !checkConstraintsRecursive(board, i, j)) {
                return false;
            }
        }
    }
    
    return true;
}

bool ValidSudoku::checkConstraintsRecursive(const std::vector<std::vector<char>>& board, int row, int col) {
    char digit = board[row][col];
    
    // Check row constraint
    for (int j = 0; j < 9; ++j) {
        if (j != col && board[row][j] == digit) {
            return false;
        }
    }
    
    // Check column constraint
    for (int i = 0; i < 9; ++i) {
        if (i != row && board[i][col] == digit) {
            return false;
        }
    }
    
    // Check box constraint
    int boxStartRow = (row / 3) * 3;
    int boxStartCol = (col / 3) * 3;
    
    for (int i = boxStartRow; i < boxStartRow + 3; ++i) {
        for (int j = boxStartCol; j < boxStartCol + 3; ++j) {
            if ((i != row || j != col) && board[i][j] == digit) {
                return false;
            }
        }
    }
    
    return true;
}

}
}