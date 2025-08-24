#pragma once

#include <vector>
#include <functional>

namespace leetcode {
namespace easy {

/**
 * Problem 118: Pascal's Triangle
 * 
 * Given an integer numRows, return the first numRows of Pascal's triangle.
 * 
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 * 
 * Constraints:
 * - 1 <= numRows <= 30
 */
class PascalsTriangle {
public:
    /**
     * Approach 1: Iterative Row-by-Row Construction (Optimal)
     * 
     * Build Pascal's triangle row by row using the recurrence relation.
     * 
     * Reasoning: This is the most straightforward and efficient approach.
     * Each row in Pascal's triangle can be computed from the previous row
     * using the property that each element (except edges) is the sum of
     * two elements above it. Start with row 0: [1], then for each subsequent
     * row, compute elements as sum of previous row's adjacent elements.
     * Edge elements are always 1.
     * 
     * Time Complexity: O(numRows²) - generate numRows rows, row i has i+1 elements
     * Space Complexity: O(numRows²) - store all rows of the triangle
     * 
     * Best when: Always - this is the standard optimal solution
     * Worst when: Never - this approach is universally preferred
     */
    std::vector<std::vector<int>> generateIterative(int numRows);

    /**
     * Approach 2: Mathematical Formula with Combinations
     * 
     * Calculate each element using binomial coefficient formula.
     * 
     * Reasoning: Each element in Pascal's triangle at position (row, col)
     * equals the binomial coefficient C(row, col) = row! / (col! * (row-col)!).
     * Instead of computing factorials directly (which can overflow), use
     * the iterative formula: C(n,k) = C(n,k-1) * (n-k+1) / k.
     * This approach demonstrates the mathematical foundation of Pascal's triangle.
     * 
     * Time Complexity: O(numRows²) - compute C(row, col) for each position
     * Space Complexity: O(numRows²) - store the result triangle
     * 
     * Best when: Educational purposes, demonstrating mathematical properties
     * Worst when: Potential integer overflow for large values
     */
    std::vector<std::vector<int>> generateCombinatorial(int numRows);

    /**
     * Approach 3: Recursive with Memoization
     * 
     * Build triangle recursively with memoization for efficiency.
     * 
     * Reasoning: Define recursive relation: pascal(row, col) = 1 if col = 0 or col = row,
     * otherwise pascal(row, col) = pascal(row-1, col-1) + pascal(row-1, col).
     * Use memoization to avoid recomputing the same values multiple times.
     * This approach clearly shows the recursive nature of Pascal's triangle
     * construction but requires careful memory management.
     * 
     * Time Complexity: O(numRows²) - each element computed once with memoization
     * Space Complexity: O(numRows²) - memoization table plus result storage
     * 
     * Best when: Demonstrating recursive structure, educational purposes
     * Worst when: Stack depth concerns for large inputs
     */
    std::vector<std::vector<int>> generateRecursive(int numRows);

    /**
     * Approach 4: Space-Optimized Single Array
     * 
     * Generate triangle using only O(numRows) extra space for computation.
     * 
     * Reasoning: Instead of storing all previous rows, maintain only the current
     * row being computed. For each new row, update the array from right to left
     * to avoid overwriting values needed for computation. This approach is
     * memory efficient but only suitable when we need the final result,
     * not the entire triangle structure.
     * 
     * Time Complexity: O(numRows²) - same computation as iterative approach
     * Space Complexity: O(numRows) - only current row stored during computation
     * 
     * Best when: Memory constraints, only need specific rows
     * Worst when: Need to preserve all rows of the triangle
     */
    std::vector<std::vector<int>> generateSpaceOptimized(int numRows);

    /**
     * Approach 5: Bitwise Generation using Powers of 11
     * 
     * Generate rows using mathematical pattern with powers of 11.
     * 
     * Reasoning: For small rows, Pascal's triangle rows correspond to
     * digits of powers of 11: 11^0=1, 11^1=11, 11^2=121, 11^3=1331, etc.
     * However, this pattern breaks when carries occur (row 5 and beyond).
     * This approach works only for the first few rows but demonstrates
     * an interesting mathematical property. For larger rows, fall back
     * to standard computation.
     * 
     * Time Complexity: O(numRows²) - fallback to standard method for larger rows
     * Space Complexity: O(numRows²) - store result triangle
     * 
     * Best when: Demonstrating mathematical patterns, small triangle sizes
     * Worst when: Large triangle sizes where pattern doesn't hold
     */
    std::vector<std::vector<int>> generateBitwise(int numRows);

    /**
     * Approach 6: Functional Programming with Lambda
     * 
     * Use functional programming paradigms with lambda expressions.
     * 
     * Reasoning: Demonstrate functional approach using higher-order functions
     * and lambda expressions. Create composable functions for triangle
     * generation, row computation, and element calculation. While potentially
     * less efficient due to function call overhead, this approach shows
     * how mathematical problems can be expressed in functional style.
     * 
     * Time Complexity: O(numRows²) - same logic as iterative approach
     * Space Complexity: O(numRows²) - store result plus function call overhead
     * 
     * Best when: Functional programming environment, code reusability
     * Worst when: Performance critical applications
     */
    std::vector<std::vector<int>> generateFunctional(int numRows);

private:
    // Helper for recursive approach with memoization
    int pascalElement(int row, int col, std::vector<std::vector<int>>& memo);
    
    // Helper for combinatorial approach
    long long binomialCoeff(int n, int k);
    
    // Helper for functional approach
    std::function<std::vector<int>(int)> createRowGenerator();
    std::function<int(int, int)> createElementCalculator();
    
    // Memoization table for recursive approach
    mutable std::vector<std::vector<int>> memoTable;
};

}  // namespace easy
}  // namespace leetcode