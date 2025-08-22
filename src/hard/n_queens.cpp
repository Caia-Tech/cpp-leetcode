#include "n_queens.h"
#include <stack>
#include <algorithm>

namespace leetcode {
namespace hard {

std::vector<std::vector<std::string>> NQueens::solveNQueensBacktracking(int n) {
    std::vector<std::vector<std::string>> solutions;
    std::vector<std::string> board(n, std::string(n, '.'));
    
    backtrackHelper(board, 0, solutions);
    return solutions;
}

std::vector<std::vector<std::string>> NQueens::solveNQueensOptimized(int n) {
    std::vector<std::vector<std::string>> solutions;
    std::vector<int> queens;
    std::unordered_set<int> cols, diag1, diag2;
    
    optimizedHelper(n, 0, queens, cols, diag1, diag2, solutions);
    return solutions;
}

std::vector<std::vector<std::string>> NQueens::solveNQueensBitwise(int n) {
    std::vector<std::vector<std::string>> solutions;
    std::vector<int> queens;
    
    bitwiseHelper(n, 0, queens, 0, 0, 0, solutions);
    return solutions;
}

std::vector<std::vector<std::string>> NQueens::solveNQueensIterative(int n) {
    std::vector<std::vector<std::string>> solutions;
    std::stack<SearchState> stack;
    
    // Start with initial state
    stack.push(SearchState(0));
    
    while (!stack.empty()) {
        SearchState current = stack.top();
        stack.pop();
        
        // Solution found
        if (current.row == n) {
            solutions.push_back(createBoard(current.queens, n));
            continue;
        }
        
        // Try placing queen in each column of current row
        for (int col = 0; col < n; ++col) {
            // Check if position is safe
            if (current.cols.count(col) || 
                current.diag1.count(current.row + col) || 
                current.diag2.count(current.row - col)) {
                continue;
            }
            
            // Create new state with queen placed
            SearchState newState = current;
            newState.row++;
            newState.queens.push_back(col);
            newState.cols.insert(col);
            newState.diag1.insert(current.row + col);
            newState.diag2.insert(current.row - col);
            
            stack.push(newState);
        }
    }
    
    return solutions;
}

std::vector<std::vector<std::string>> NQueens::solveNQueensPermutation(int n) {
    std::vector<std::vector<std::string>> solutions;
    std::vector<int> permutation(n);
    
    // Initialize permutation with column indices
    for (int i = 0; i < n; ++i) {
        permutation[i] = i;
    }
    
    // Check all permutations
    do {
        if (isValidPermutation(permutation)) {
            solutions.push_back(createBoard(permutation, n));
        }
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    
    return solutions;
}

std::vector<std::vector<std::string>> NQueens::solveNQueensMemoization(int n) {
    memoCache.clear();
    std::vector<std::vector<std::string>> solutions;
    
    auto queensPositions = memoHelper(n, 0, 0, 0, 0);
    
    for (const auto& positions : queensPositions) {
        solutions.push_back(createBoard(positions, n));
    }
    
    return solutions;
}

void NQueens::backtrackHelper(std::vector<std::string>& board, int row, 
                             std::vector<std::vector<std::string>>& solutions) {
    int n = board.size();
    
    // Base case: all queens placed
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    
    // Try placing queen in each column of current row
    for (int col = 0; col < n; ++col) {
        if (isValidPosition(board, row, col, n)) {
            // Place queen
            board[row][col] = 'Q';
            
            // Recursively place remaining queens
            backtrackHelper(board, row + 1, solutions);
            
            // Backtrack
            board[row][col] = '.';
        }
    }
}

void NQueens::optimizedHelper(int n, int row, std::vector<int>& queens,
                             std::unordered_set<int>& cols, std::unordered_set<int>& diag1,
                             std::unordered_set<int>& diag2, std::vector<std::vector<std::string>>& solutions) {
    // Base case: all queens placed
    if (row == n) {
        solutions.push_back(createBoard(queens, n));
        return;
    }
    
    // Try placing queen in each column of current row
    for (int col = 0; col < n; ++col) {
        // Check conflicts using sets
        if (cols.count(col) || diag1.count(row + col) || diag2.count(row - col)) {
            continue;
        }
        
        // Place queen
        queens.push_back(col);
        cols.insert(col);
        diag1.insert(row + col);
        diag2.insert(row - col);
        
        // Recurse to next row
        optimizedHelper(n, row + 1, queens, cols, diag1, diag2, solutions);
        
        // Backtrack
        queens.pop_back();
        cols.erase(col);
        diag1.erase(row + col);
        diag2.erase(row - col);
    }
}

void NQueens::bitwiseHelper(int n, int row, std::vector<int>& queens,
                           int colMask, int diag1Mask, int diag2Mask,
                           std::vector<std::vector<std::string>>& solutions) {
    // Base case: all queens placed
    if (row == n) {
        solutions.push_back(createBoard(queens, n));
        return;
    }
    
    // Find available positions (bits set to 1 indicate conflicts)
    int availableMask = ((1 << n) - 1) & (~(colMask | diag1Mask | diag2Mask));
    
    // Try each available position
    while (availableMask) {
        // Get rightmost available position
        int position = availableMask & (-availableMask);
        availableMask ^= position; // Remove this position from available mask
        
        // Convert position to column index
        int col = 0;
        int temp = position;
        while (temp > 1) {
            temp >>= 1;
            col++;
        }
        
        // Place queen
        queens.push_back(col);
        
        // Update masks for next row
        bitwiseHelper(n, row + 1, queens,
                     colMask | position,                    // Column conflict
                     (diag1Mask | position) << 1,         // Positive diagonal (/)
                     (diag2Mask | position) >> 1,         // Negative diagonal (\)
                     solutions);
        
        // Backtrack
        queens.pop_back();
    }
}

bool NQueens::isValidPosition(const std::vector<std::string>& board, int row, int col, int n) {
    // Check column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }
    
    // Check positive diagonal (top-left to bottom-right)
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    
    // Check negative diagonal (top-right to bottom-left)
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    
    return true;
}

bool NQueens::isValidPermutation(const std::vector<int>& permutation) {
    int n = permutation.size();
    
    // Check diagonal conflicts
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Check if queens are on same diagonal
            if (abs(permutation[i] - permutation[j]) == abs(i - j)) {
                return false;
            }
        }
    }
    
    return true;
}

std::vector<std::string> NQueens::createBoard(const std::vector<int>& queens, int n) {
    std::vector<std::string> board(n, std::string(n, '.'));
    
    for (int row = 0; row < n; ++row) {
        board[row][queens[row]] = 'Q';
    }
    
    return board;
}

std::vector<std::vector<int>> NQueens::memoHelper(int n, int row, int colMask, int diag1Mask, int diag2Mask) {
    // Base case
    if (row == n) {
        return {{}};
    }
    
    // Check memoization
    MemoKey key = {row, colMask, diag1Mask, diag2Mask};
    if (memoCache.count(key)) {
        return memoCache[key];
    }
    
    std::vector<std::vector<int>> result;
    
    // Find available positions
    int availableMask = ((1 << n) - 1) & (~(colMask | diag1Mask | diag2Mask));
    
    // Try each available position
    while (availableMask) {
        int position = availableMask & (-availableMask);
        availableMask ^= position;
        
        // Convert to column
        int col = 0;
        int temp = position;
        while (temp > 1) {
            temp >>= 1;
            col++;
        }
        
        // Get solutions for remaining rows
        auto subResults = memoHelper(n, row + 1,
                                   colMask | position,
                                   (diag1Mask | position) << 1,
                                   (diag2Mask | position) >> 1);
        
        // Add current column to each sub-result
        for (auto subResult : subResults) {
            subResult.insert(subResult.begin(), col);
            result.push_back(subResult);
        }
    }
    
    memoCache[key] = result;
    return result;
}

}
}