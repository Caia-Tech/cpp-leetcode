#pragma once

#ifndef LEETCODE_EASY_PASCALS_TRIANGLE_II_H
#define LEETCODE_EASY_PASCALS_TRIANGLE_II_H

#include <vector>

namespace leetcode {
namespace easy {

// Problem 119: Pascal's Triangle II
// Given an integer rowIndex, return the rowIndexth (0-indexed) row of Pascal's triangle.
// In Pascal's triangle, each number is the sum of the two numbers directly above it.
//
// Example 1:
// Input: rowIndex = 3
// Output: [1,3,3,1]
//
// Example 2:
// Input: rowIndex = 0
// Output: [1]
//
// Example 3:
// Input: rowIndex = 1
// Output: [1,1]
//
// Constraints: 0 <= rowIndex <= 33
//
// This class implements 6 different algorithmic approaches to solve the problem:
// 1. Dynamic Programming (Bottom-up): Build each row from previous row
// 2. Mathematical Formula: Use combination formula C(n,k) = n!/(k!(n-k)!)
// 3. Space-Optimized DP: Single array, update in-place from right to left
// 4. Recursive with Memoization: Top-down approach with caching
// 5. Iterative Row Generation: Generate row by row using addition
// 6. Binomial Coefficient: Use iterative binomial coefficient calculation

class PascalsTriangleII {
public:
    // Approach 1: Dynamic Programming (Bottom-up)
    // Time: O(rowIndex^2), Space: O(rowIndex^2)
    // Build the entire triangle up to the desired row
    static std::vector<int> getRowDP(int rowIndex);
    
    // Approach 2: Mathematical Formula using Combinations
    // Time: O(rowIndex), Space: O(1) excluding output
    // Use the formula C(n,k) = n!/(k!(n-k)!) for each element
    static std::vector<int> getRowMath(int rowIndex);
    
    // Approach 3: Space-Optimized DP (Single Array)
    // Time: O(rowIndex^2), Space: O(rowIndex)
    // Use single array and update from right to left to avoid overwrites
    static std::vector<int> getRowSpaceOptimized(int rowIndex);
    
    // Approach 4: Recursive with Memoization
    // Time: O(rowIndex^2), Space: O(rowIndex^2) for memoization
    // Top-down recursive approach with caching for efficiency
    static std::vector<int> getRowRecursive(int rowIndex);
    
    // Approach 5: Iterative Row Generation
    // Time: O(rowIndex^2), Space: O(rowIndex)
    // Generate each row iteratively using the recurrence relation
    static std::vector<int> getRowIterative(int rowIndex);
    
    // Approach 6: Binomial Coefficient Calculation
    // Time: O(rowIndex), Space: O(1) excluding output
    // Calculate binomial coefficients iteratively to avoid overflow
    static std::vector<int> getRowBinomial(int rowIndex);

private:
    // Helper function for recursive approach
    static int getPascalValue(int row, int col, std::vector<std::vector<int>>& memo);
    
    // Helper function to calculate binomial coefficient C(n,k)
    static long long binomialCoeff(int n, int k);
    
    // Helper function to safely multiply avoiding overflow
    static int safeMult(long long a, long long b, long long c);
};

} // namespace easy
} // namespace leetcode

#endif // LEETCODE_EASY_PASCALS_TRIANGLE_II_H