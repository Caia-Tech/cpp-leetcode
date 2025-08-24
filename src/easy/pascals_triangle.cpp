#include "pascals_triangle.h"
#include <cmath>

namespace leetcode {
namespace easy {

// Approach 1: Iterative Row-by-Row Construction (Optimal)
std::vector<std::vector<int>> PascalsTriangle::generateIterative(int numRows) {
    std::vector<std::vector<int>> triangle;
    triangle.reserve(numRows);
    
    for (int row = 0; row < numRows; ++row) {
        std::vector<int> currentRow(row + 1, 1);
        
        // Fill interior elements
        for (int col = 1; col < row; ++col) {
            currentRow[col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
        }
        
        triangle.push_back(std::move(currentRow));
    }
    
    return triangle;
}

// Approach 2: Mathematical Formula with Combinations
std::vector<std::vector<int>> PascalsTriangle::generateCombinatorial(int numRows) {
    std::vector<std::vector<int>> triangle;
    triangle.reserve(numRows);
    
    for (int row = 0; row < numRows; ++row) {
        std::vector<int> currentRow(row + 1);
        
        for (int col = 0; col <= row; ++col) {
            currentRow[col] = static_cast<int>(binomialCoeff(row, col));
        }
        
        triangle.push_back(std::move(currentRow));
    }
    
    return triangle;
}

long long PascalsTriangle::binomialCoeff(int n, int k) {
    if (k > n - k) k = n - k; // Take advantage of symmetry
    
    long long result = 1;
    for (int i = 0; i < k; ++i) {
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

// Approach 3: Recursive with Memoization
std::vector<std::vector<int>> PascalsTriangle::generateRecursive(int numRows) {
    std::vector<std::vector<int>> triangle;
    triangle.reserve(numRows);
    
    // Initialize memoization table
    memoTable.assign(numRows, std::vector<int>(numRows, -1));
    
    for (int row = 0; row < numRows; ++row) {
        std::vector<int> currentRow(row + 1);
        
        for (int col = 0; col <= row; ++col) {
            currentRow[col] = pascalElement(row, col, memoTable);
        }
        
        triangle.push_back(std::move(currentRow));
    }
    
    return triangle;
}

int PascalsTriangle::pascalElement(int row, int col, std::vector<std::vector<int>>& memo) {
    // Base cases
    if (col == 0 || col == row) return 1;
    
    // Check memoization table
    if (memo[row][col] != -1) return memo[row][col];
    
    // Recursive case
    memo[row][col] = pascalElement(row - 1, col - 1, memo) + 
                     pascalElement(row - 1, col, memo);
    
    return memo[row][col];
}

// Approach 4: Space-Optimized Single Array
std::vector<std::vector<int>> PascalsTriangle::generateSpaceOptimized(int numRows) {
    std::vector<std::vector<int>> triangle;
    triangle.reserve(numRows);
    
    if (numRows == 0) return triangle;
    
    // Start with first row
    std::vector<int> currentRow = {1};
    triangle.push_back(currentRow);
    
    for (int row = 1; row < numRows; ++row) {
        std::vector<int> nextRow(row + 1, 1);
        
        // Update from right to left to avoid overwriting needed values
        for (int col = 1; col < row; ++col) {
            nextRow[col] = currentRow[col - 1] + currentRow[col];
        }
        
        triangle.push_back(nextRow);
        currentRow = std::move(nextRow);
    }
    
    return triangle;
}

// Approach 5: Bitwise Generation using Powers of 11
std::vector<std::vector<int>> PascalsTriangle::generateBitwise(int numRows) {
    std::vector<std::vector<int>> triangle;
    triangle.reserve(numRows);
    
    for (int row = 0; row < numRows; ++row) {
        if (row <= 4) { // Powers of 11 pattern works for first 5 rows
            std::vector<int> currentRow;
            long long power11 = static_cast<long long>(std::pow(11, row));
            
            // Extract digits from power of 11
            if (power11 == 1) {
                currentRow = {1};
            } else {
                // Convert number to vector of digits
                long long temp = power11;
                std::vector<int> digits;
                while (temp > 0) {
                    digits.push_back(temp % 10);
                    temp /= 10;
                }
                
                // Reverse to get correct order
                currentRow.assign(digits.rbegin(), digits.rend());
            }
            
            triangle.push_back(std::move(currentRow));
        } else {
            // Fall back to standard method for rows where pattern breaks
            std::vector<int> currentRow(row + 1, 1);
            
            for (int col = 1; col < row; ++col) {
                currentRow[col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
            
            triangle.push_back(std::move(currentRow));
        }
    }
    
    return triangle;
}

// Approach 6: Functional Programming with Lambda
std::vector<std::vector<int>> PascalsTriangle::generateFunctional(int numRows) {
    auto rowGenerator = createRowGenerator();
    
    std::vector<std::vector<int>> triangle;
    triangle.reserve(numRows);
    
    for (int row = 0; row < numRows; ++row) {
        triangle.push_back(rowGenerator(row));
    }
    
    return triangle;
}

std::function<std::vector<int>(int)> PascalsTriangle::createRowGenerator() {
    auto elementCalculator = createElementCalculator();
    
    return [elementCalculator](int rowIndex) -> std::vector<int> {
        std::vector<int> row(rowIndex + 1);
        
        for (int col = 0; col <= rowIndex; ++col) {
            row[col] = elementCalculator(rowIndex, col);
        }
        
        return row;
    };
}

std::function<int(int, int)> PascalsTriangle::createElementCalculator() {
    return [this](int row, int col) -> int {
        // Base case lambda
        if (col == 0 || col == row) return 1;
        
        // Recursive calculator with memoization
        static std::vector<std::vector<int>> memo;
        
        // Ensure memo table is large enough
        if (memo.size() <= row) {
            memo.resize(row + 1);
            for (auto& memoRow : memo) {
                if (memoRow.size() <= row) {
                    memoRow.resize(row + 1, -1);
                }
            }
        }
        
        // Check memoization
        if (memo[row][col] != -1) {
            return memo[row][col];
        }
        
        // Recursive calculation
        auto calculator = createElementCalculator();
        memo[row][col] = calculator(row - 1, col - 1) + calculator(row - 1, col);
        
        return memo[row][col];
    };
}

}  // namespace easy
}  // namespace leetcode