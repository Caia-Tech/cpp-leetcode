#pragma once

#include <vector>
#include <unordered_set>
#include <bitset>

namespace leetcode {
namespace medium {

/**
 * Problem 36: Valid Sudoku
 * 
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated 
 * according to the following rules:
 * 
 * 1. Each row must contain the digits 1-9 without repetition.
 * 2. Each column must contain the digits 1-9 without repetition.
 * 3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
 * 
 * Note:
 * - A Sudoku board (partially filled) could be valid but is not necessarily solvable.
 * - Only the filled cells need to be validated according to the mentioned rules.
 * 
 * Constraints:
 * - board.length == 9
 * - board[i].length == 9
 * - board[i][j] is a digit 1-9 or '.'.
 */
class ValidSudoku {
public:
    /**
     * Approach 1: Hash Sets for Each Constraint (Optimal)
     * 
     * Use hash sets to track seen digits in each row, column, and 3x3 box.
     * 
     * Reasoning: This is the optimal approach. Maintain separate hash sets for
     * each row (9 sets), each column (9 sets), and each 3x3 box (9 sets).
     * For each filled cell, check if digit already exists in corresponding
     * row/column/box sets. If not, add to sets; if yes, board is invalid.
     * Single pass with O(1) lookups makes this very efficient.
     * 
     * Time Complexity: O(1) - fixed 81 cells, each with O(1) operations
     * Space Complexity: O(1) - fixed number of sets with at most 9 elements each
     * 
     * Best when: Need optimal performance, clear constraint separation
     * Worst when: Memory usage for multiple sets is a concern
     */
    bool isValidSudokuHashSets(const std::vector<std::vector<char>>& board);

    /**
     * Approach 2: Single Pass with Encoding
     * 
     * Encode row/column/box constraints into single strings and use one set.
     * 
     * Reasoning: Clever encoding where each digit occurrence is represented as
     * multiple strings: "row_i_digit", "col_j_digit", "box_k_digit". Use single
     * hash set to track all constraint violations. This reduces memory overhead
     * by using one set instead of 27 separate sets, though string operations
     * may have slight overhead.
     * 
     * Time Complexity: O(1) - fixed board size with O(1) string operations
     * Space Complexity: O(1) - single set with at most 3*9*9 entries
     * 
     * Best when: Want memory optimization, prefer single data structure
     * Worst when: String operations overhead is undesirable
     */
    bool isValidSudokuEncoded(const std::vector<std::vector<char>>& board);

    /**
     * Approach 3: Bit Manipulation
     * 
     * Use bitsets to represent digit presence for each constraint.
     * 
     * Reasoning: Use bitsets where each bit represents presence of digit 1-9.
     * For each row, column, and box, maintain a 9-bit integer where bit i
     * indicates if digit i+1 is present. Check and set bits using bitwise
     * operations. This is very space-efficient and potentially faster than
     * hash operations on some architectures.
     * 
     * Time Complexity: O(1) - fixed board with O(1) bit operations
     * Space Complexity: O(1) - 27 integers for bit storage
     * 
     * Best when: Need maximum memory efficiency, bitwise operations preferred
     * Worst when: Bit manipulation logic is less readable than sets
     */
    bool isValidSudokuBitManipulation(const std::vector<std::vector<char>>& board);

    /**
     * Approach 4: Three Separate Passes
     * 
     * Check rows, columns, and boxes in separate passes.
     * 
     * Reasoning: Conceptually simple approach that checks each constraint type
     * separately. First pass validates all rows, second pass all columns,
     * third pass all 3x3 boxes. While clear and easy to understand, this
     * requires three complete board traversals instead of one integrated pass.
     * 
     * Time Complexity: O(1) - three passes through fixed 81 cells
     * Space Complexity: O(1) - temporary set for each constraint check
     * 
     * Best when: Code clarity is prioritized, separate validation logic desired
     * Worst when: Single-pass efficiency is preferred
     */
    bool isValidSudokuThreePasses(const std::vector<std::vector<char>>& board);

    /**
     * Approach 5: Array-Based Tracking
     * 
     * Use 2D boolean arrays instead of hash sets for digit tracking.
     * 
     * Reasoning: Replace hash sets with 2D boolean arrays: rows[9][10],
     * cols[9][10], boxes[9][10] where second dimension tracks digits 1-9
     * (index 0 unused). This provides O(1) access like hash sets but with
     * potentially better cache locality and no hash computation overhead.
     * 
     * Time Complexity: O(1) - fixed board with O(1) array access
     * Space Complexity: O(1) - fixed-size boolean arrays
     * 
     * Best when: Want array access over hash operations, predictable memory layout
     * Worst when: Hash sets provide cleaner interface
     */
    bool isValidSudokuArrays(const std::vector<std::vector<char>>& board);

    /**
     * Approach 6: Recursive Validation with Early Termination
     * 
     * Recursively validate board with early termination on first violation.
     * 
     * Reasoning: Use recursive approach to validate board systematically.
     * At each cell, if filled, recursively verify it doesn't violate constraints
     * in its row, column, and box. Early termination on first violation can
     * save computation. While this demonstrates recursive thinking, it's less
     * efficient than direct approaches for this problem.
     * 
     * Time Complexity: O(1) worst case, potentially better with early termination
     * Space Complexity: O(1) - recursion depth limited by board size
     * 
     * Best when: Recursive validation pattern is preferred, educational purposes
     * Worst when: Direct single-pass validation is more efficient
     */
    bool isValidSudokuRecursive(const std::vector<std::vector<char>>& board);

private:
    // Helper functions
    bool isRowValid(const std::vector<std::vector<char>>& board, int row);
    bool isColumnValid(const std::vector<std::vector<char>>& board, int col);
    bool isBoxValid(const std::vector<std::vector<char>>& board, int startRow, int startCol);
    int getBoxIndex(int row, int col);
    bool isValidCell(const std::vector<std::vector<char>>& board, int row, int col);
    bool checkConstraintsRecursive(const std::vector<std::vector<char>>& board, int row, int col);
    
    // Encoding helper
    std::string encodeConstraint(const std::string& type, int index, char digit);
};

}
}