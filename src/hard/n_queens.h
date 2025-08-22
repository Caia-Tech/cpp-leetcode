#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

namespace leetcode {
namespace hard {

/**
 * Problem 51: N-Queens
 * 
 * The n-queens puzzle is the problem of placing n chess queens on an n×n 
 * chessboard such that no two queens attack each other.
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle. 
 * You may return the answer in any order.
 * 
 * Each solution contains a distinct board configuration of the n-queens' 
 * placement, where 'Q' and '.' both indicate a queen and an empty space, 
 * respectively.
 * 
 * Constraints:
 * - 1 <= n <= 9
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class NQueens {
public:
    /**
     * Approach 1: Classic Backtracking with Full Board (Educational)
     * 
     * Use backtracking with explicit board representation and conflict checking.
     * 
     * Reasoning: This is the most intuitive approach that directly models the problem.
     * Maintain an n×n board, place queens one by one, and for each placement check
     * if it conflicts with previously placed queens. Use backtracking to explore
     * all possibilities: place queen, recurse, backtrack if no solution found.
     * Check conflicts by examining rows, columns, and diagonals explicitly.
     * 
     * Time Complexity: O(n!) - at most n! ways to place n queens
     * Space Complexity: O(n²) - explicit board storage plus recursion depth O(n)
     * 
     * Best when: Learning backtracking, need explicit board visualization
     * Worst when: Want optimal space usage, performance is critical
     */
    std::vector<std::vector<std::string>> solveNQueensBacktracking(int n);

    /**
     * Approach 2: Optimized Backtracking with Conflict Sets (Efficient)
     * 
     * Use backtracking with sets to track column and diagonal conflicts.
     * 
     * Reasoning: Instead of checking entire board for conflicts, maintain sets
     * of occupied columns, positive diagonals (row+col), and negative diagonals
     * (row-col). This reduces conflict checking from O(n) to O(1) per placement.
     * Only store queen positions, not full board, reducing space complexity.
     * Generate board representation only when solution is found.
     * 
     * Time Complexity: O(n!) - same number of recursive calls but faster pruning
     * Space Complexity: O(n) - only track positions and conflict sets
     * 
     * Best when: Want optimal performance, understand coordinate mathematics
     * Worst when: Diagonal indexing seems complex, prefer explicit board checking
     */
    std::vector<std::vector<std::string>> solveNQueensOptimized(int n);

    /**
     * Approach 3: Bit Manipulation Backtracking (Advanced)
     * 
     * Use bit operations to represent and check conflicts ultra-efficiently.
     * 
     * Reasoning: Represent column and diagonal conflicts as integers where each
     * bit indicates if that position is under attack. Use bitwise operations
     * to quickly find available positions and update conflict masks. This approach
     * minimizes memory usage and maximizes speed by leveraging processor-level
     * bit operations. Particularly effective for problems with n <= 32.
     * 
     * Time Complexity: O(n!) - same recursive structure but fastest per operation
     * Space Complexity: O(n) - only integers for bit masks plus recursion depth
     * 
     * Best when: Maximum performance needed, comfortable with bit manipulation
     * Worst when: Bit operations seem complex, n might exceed integer bit width
     */
    std::vector<std::vector<std::string>> solveNQueensBitwise(int n);

    /**
     * Approach 4: Iterative with Explicit Stack (Non-Recursive)
     * 
     * Convert recursive backtracking to iterative approach using explicit stack.
     * 
     * Reasoning: Some environments or constraints prefer iterative solutions to
     * avoid recursion stack limits. Use explicit stack to store search states
     * (current row, column positions, conflict sets). This approach gives exact
     * control over memory usage and can be easier to debug or modify. Useful
     * when recursion depth might be a concern.
     * 
     * Time Complexity: O(n!) - same search space as recursive approaches
     * Space Complexity: O(n²) - explicit stack can store many partial solutions
     * 
     * Best when: Avoid recursion, need explicit control over search process
     * Worst when: Stack management complexity outweighs recursion benefits
     */
    std::vector<std::vector<std::string>> solveNQueensIterative(int n);

    /**
     * Approach 5: Permutation-Based Search (Mathematical)
     * 
     * Generate all permutations of column positions and filter valid ones.
     * 
     * Reasoning: Since exactly one queen must be placed in each row and column,
     * valid solutions are permutations of column indices [0,1,2,...,n-1].
     * Generate all n! permutations and check which ones satisfy diagonal
     * constraints. While this explores more invalid states than backtracking,
     * it provides a different algorithmic perspective and can be parallelized.
     * 
     * Time Complexity: O(n! * n) - generate n! permutations, O(n) check each
     * Space Complexity: O(n) - permutation array and checking variables
     * 
     * Best when: Mathematical approach preferred, potential for parallelization
     * Worst when: Less efficient than backtracking, generates many invalid states
     */
    std::vector<std::vector<std::string>> solveNQueensPermutation(int n);

    /**
     * Approach 6: Dynamic Programming with Memoization (Experimental)
     * 
     * Use memoization to cache partial solutions for reuse.
     * 
     * Reasoning: While N-Queens doesn't have obvious overlapping subproblems,
     * we can memoize based on conflict state signatures. When we reach the same
     * combination of column and diagonal conflicts, the remaining possibilities
     * are the same. This approach explores whether memoization can help despite
     * the exponential nature of the problem. More of academic interest than
     * practical improvement.
     * 
     * Time Complexity: O(n!) - potentially better with good memoization hits
     * Space Complexity: O(2^n) - exponential memoization table in worst case
     * 
     * Best when: Exploring advanced optimization techniques, academic interest
     * Worst when: Memory usage concerns, simple backtracking is sufficient
     */
    std::vector<std::vector<std::string>> solveNQueensMemoization(int n);

private:
    // Helper functions for different approaches
    void backtrackHelper(std::vector<std::string>& board, int row, 
                        std::vector<std::vector<std::string>>& solutions);
    
    void optimizedHelper(int n, int row, std::vector<int>& queens,
                        std::unordered_set<int>& cols, std::unordered_set<int>& diag1,
                        std::unordered_set<int>& diag2, std::vector<std::vector<std::string>>& solutions);
    
    void bitwiseHelper(int n, int row, std::vector<int>& queens,
                      int colMask, int diag1Mask, int diag2Mask,
                      std::vector<std::vector<std::string>>& solutions);
    
    bool isValidPosition(const std::vector<std::string>& board, int row, int col, int n);
    bool isValidPermutation(const std::vector<int>& permutation);
    std::vector<std::string> createBoard(const std::vector<int>& queens, int n);
    
    // Iterative search state
    struct SearchState {
        int row;
        std::vector<int> queens;
        std::unordered_set<int> cols;
        std::unordered_set<int> diag1;
        std::unordered_set<int> diag2;
        
        SearchState(int r) : row(r) {}
        SearchState(int r, const std::vector<int>& q, const std::unordered_set<int>& c,
                   const std::unordered_set<int>& d1, const std::unordered_set<int>& d2)
            : row(r), queens(q), cols(c), diag1(d1), diag2(d2) {}
    };
    
    // Memoization key and cache
    struct MemoKey {
        int row;
        int colMask;
        int diag1Mask;
        int diag2Mask;
        
        bool operator==(const MemoKey& other) const {
            return row == other.row && colMask == other.colMask && 
                   diag1Mask == other.diag1Mask && diag2Mask == other.diag2Mask;
        }
    };
    
    struct MemoKeyHash {
        std::size_t operator()(const MemoKey& key) const {
            return std::hash<int>()(key.row) ^ 
                   (std::hash<int>()(key.colMask) << 1) ^
                   (std::hash<int>()(key.diag1Mask) << 2) ^
                   (std::hash<int>()(key.diag2Mask) << 3);
        }
    };
    
    mutable std::unordered_map<MemoKey, std::vector<std::vector<int>>, MemoKeyHash> memoCache;
    std::vector<std::vector<int>> memoHelper(int n, int row, int colMask, int diag1Mask, int diag2Mask);
};

}
}