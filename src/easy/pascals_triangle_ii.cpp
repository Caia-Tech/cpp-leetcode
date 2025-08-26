#include "pascals_triangle_ii.h"
#include <algorithm>
#include <unordered_map>

namespace leetcode {
namespace easy {

// Approach 1: Dynamic Programming (Bottom-up)
// Detailed Reasoning: Build the entire Pascal's triangle from row 0 to rowIndex.
// Each row is constructed by adding adjacent elements from the previous row.
// This approach is intuitive and follows the definition of Pascal's triangle directly.
std::vector<int> PascalsTriangleII::getRowDP(int rowIndex) {
    std::vector<std::vector<int>> triangle(rowIndex + 1);
    
    // Initialize first row
    triangle[0] = {1};
    
    // Build each subsequent row
    for (int i = 1; i <= rowIndex; ++i) {
        triangle[i].resize(i + 1);
        triangle[i][0] = 1;  // First element is always 1
        triangle[i][i] = 1;  // Last element is always 1
        
        // Fill middle elements using recurrence relation
        for (int j = 1; j < i; ++j) {
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
        }
    }
    
    return triangle[rowIndex];
}

// Approach 2: Mathematical Formula using Combinations
// Detailed Reasoning: The kth element in row n is C(n,k) = n!/(k!(n-k)!).
// We can calculate each binomial coefficient directly using the mathematical formula.
// This avoids building intermediate rows but requires careful handling of large factorials.
std::vector<int> PascalsTriangleII::getRowMath(int rowIndex) {
    std::vector<int> result(rowIndex + 1);
    
    for (int k = 0; k <= rowIndex; ++k) {
        result[k] = static_cast<int>(binomialCoeff(rowIndex, k));
    }
    
    return result;
}

// Approach 3: Space-Optimized DP (Single Array)
// Detailed Reasoning: Instead of storing all rows, use a single array and update it
// in-place. We must update from right to left to avoid overwriting values we still need.
// This optimizes space from O(n^2) to O(n) while maintaining the same time complexity.
std::vector<int> PascalsTriangleII::getRowSpaceOptimized(int rowIndex) {
    std::vector<int> row(rowIndex + 1, 1);
    
    // For each row from 1 to rowIndex
    for (int i = 1; i <= rowIndex; ++i) {
        // Update from right to left to avoid overwriting needed values
        for (int j = i - 1; j > 0; --j) {
            row[j] = row[j] + row[j - 1];
        }
    }
    
    return row;
}

// Approach 4: Recursive with Memoization
// Detailed Reasoning: Use the recursive definition Pascal(n,k) = Pascal(n-1,k-1) + Pascal(n-1,k)
// with base cases Pascal(n,0) = Pascal(n,n) = 1. Memoization avoids redundant calculations.
// This provides an elegant top-down solution with good performance.
std::vector<int> PascalsTriangleII::getRowRecursive(int rowIndex) {
    std::vector<std::vector<int>> memo(rowIndex + 1, std::vector<int>(rowIndex + 1, -1));
    std::vector<int> result(rowIndex + 1);
    
    for (int k = 0; k <= rowIndex; ++k) {
        result[k] = getPascalValue(rowIndex, k, memo);
    }
    
    return result;
}

// Approach 5: Iterative Row Generation
// Detailed Reasoning: Generate each row one by one using the relationship that each
// element is the sum of the two elements above it. This is similar to approach 1
// but focuses on generating only the required row iteratively.
std::vector<int> PascalsTriangleII::getRowIterative(int rowIndex) {
    std::vector<int> current = {1};
    
    for (int row = 1; row <= rowIndex; ++row) {
        std::vector<int> next(row + 1, 1);
        
        // Fill middle elements
        for (int j = 1; j < row; ++j) {
            next[j] = current[j - 1] + current[j];
        }
        
        current = std::move(next);
    }
    
    return current;
}

// Approach 6: Binomial Coefficient Calculation
// Detailed Reasoning: Use the iterative formula for binomial coefficients:
// C(n,k) = C(n,k-1) * (n-k+1) / k. This avoids factorial calculations and
// reduces the risk of overflow while maintaining O(n) time complexity.
std::vector<int> PascalsTriangleII::getRowBinomial(int rowIndex) {
    std::vector<int> result(rowIndex + 1);
    result[0] = 1;
    
    // Use iterative formula: C(n,k) = C(n,k-1) * (n-k+1) / k
    for (int k = 1; k <= rowIndex; ++k) {
        // Use long long to prevent overflow during multiplication
        long long coeff = static_cast<long long>(result[k - 1]) * (rowIndex - k + 1) / k;
        result[k] = static_cast<int>(coeff);
    }
    
    return result;
}

// Helper function for recursive approach
int PascalsTriangleII::getPascalValue(int row, int col, std::vector<std::vector<int>>& memo) {
    // Base cases
    if (col == 0 || col == row) {
        return memo[row][col] = 1;
    }
    
    // Check if already computed
    if (memo[row][col] != -1) {
        return memo[row][col];
    }
    
    // Recursive case with memoization
    memo[row][col] = getPascalValue(row - 1, col - 1, memo) + 
                     getPascalValue(row - 1, col, memo);
    
    return memo[row][col];
}

// Helper function to calculate binomial coefficient C(n,k)
long long PascalsTriangleII::binomialCoeff(int n, int k) {
    if (k > n - k) k = n - k; // Take advantage of symmetry
    
    long long result = 1;
    for (int i = 0; i < k; ++i) {
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

// Helper function for safe multiplication
int PascalsTriangleII::safeMult(long long a, long long b, long long c) {
    return static_cast<int>((a * b) / c);
}

} // namespace easy
} // namespace leetcode