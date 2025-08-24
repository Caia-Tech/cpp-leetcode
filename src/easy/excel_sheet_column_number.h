#pragma once

#include <string>
#include <functional>
#include <cmath>

namespace leetcode {
namespace easy {

/**
 * Problem 171: Excel Sheet Column Number
 * 
 * Given a string columnTitle that represents the column title as appears in an Excel sheet,
 * return its corresponding column number.
 * 
 * For example:
 * A -> 1
 * B -> 2
 * C -> 3
 * ...
 * Z -> 26
 * AA -> 27
 * AB -> 28
 * ...
 * 
 * Constraints:
 * - 1 <= columnTitle.length <= 7
 * - columnTitle consists only of uppercase English letters.
 * - columnTitle is in the range ["A", "FXSHRXW"].
 */
class ExcelSheetColumnNumber {
public:
    /**
     * Approach 1: Iterative Base-26 Conversion (Optimal)
     * 
     * Treat the problem as base-26 number system conversion.
     * 
     * Reasoning: Excel column titles follow a base-26 system where A=1, B=2, ..., Z=26.
     * For multi-character titles, each position represents a power of 26. We iterate
     * through the string from left to right, multiplying the accumulated result by 26
     * and adding the current character's value. This is similar to converting any
     * base-N number to decimal.
     * 
     * Time Complexity: O(n) - where n is the length of columnTitle
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Always - this is the standard and most efficient solution
     * Worst when: Never - this is the optimal approach
     */
    int titleToNumberIterative(std::string columnTitle);

    /**
     * Approach 2: Recursive Conversion
     * 
     * Use recursion to process the string from right to left.
     * 
     * Reasoning: Break down the problem recursively by processing the rightmost
     * character and recursively handling the rest. Each recursive call handles
     * one character and its corresponding power of 26. The base case is when
     * we've processed all characters. This demonstrates the recursive nature
     * of positional number systems.
     * 
     * Time Complexity: O(n) - process each character once
     * Space Complexity: O(n) - recursion stack depth
     * 
     * Best when: Demonstrating recursive approaches, functional style preferred
     * Worst when: Stack space is limited, iterative solution is clearer
     */
    int titleToNumberRecursive(std::string columnTitle);

    /**
     * Approach 3: Mathematical Formula with Power
     * 
     * Calculate using explicit power operations for each position.
     * 
     * Reasoning: Directly apply the mathematical formula for base conversion.
     * Each character at position i (from right, 0-indexed) contributes
     * (char_value * 26^i) to the total. We iterate through the string from
     * right to left, calculating powers of 26 explicitly. This approach
     * clearly shows the mathematical foundation of the conversion.
     * 
     * Time Complexity: O(n) - process each character once
     * Space Complexity: O(1) - only use constant variables
     * 
     * Best when: Mathematical clarity is important, educational purposes
     * Worst when: Multiplication is more efficient than power operations
     */
    int titleToNumberPower(std::string columnTitle);

    /**
     * Approach 4: Horner's Method
     * 
     * Apply Horner's method for polynomial evaluation.
     * 
     * Reasoning: The column number can be viewed as evaluating a polynomial
     * where coefficients are character values and x=26. Horner's method
     * evaluates polynomials efficiently by factoring out common terms:
     * (((...(a_n * x + a_{n-1}) * x + a_{n-2}) * x + ...) + a_0).
     * This minimizes the number of multiplications needed.
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(1) - only use constant space
     * 
     * Best when: Demonstrating numerical methods, polynomial evaluation
     * Worst when: Simple iteration is more intuitive
     */
    int titleToNumberHorner(std::string columnTitle);

    /**
     * Approach 5: Bit Manipulation Optimization
     * 
     * Use bit operations where possible for optimization.
     * 
     * Reasoning: While 26 is not a power of 2, we can still optimize some
     * operations using bit manipulation. We can use bit shifts for intermediate
     * calculations and optimize the character-to-value conversion. This approach
     * demonstrates how to think about optimization even when the base isn't
     * a power of 2.
     * 
     * Time Complexity: O(n) - process each character once
     * Space Complexity: O(1) - only use constant variables
     * 
     * Best when: Demonstrating optimization techniques
     * Worst when: Readability is more important than micro-optimizations
     */
    int titleToNumberBitOptimized(std::string columnTitle);

    /**
     * Approach 6: Functional Programming with Fold
     * 
     * Use functional programming concepts with fold/reduce operations.
     * 
     * Reasoning: Apply functional programming paradigms using fold/reduce
     * to accumulate the result. Each character is processed by a lambda
     * function that updates the accumulator. This demonstrates how imperative
     * loops can be expressed as functional operations, making the code more
     * declarative and composable.
     * 
     * Time Complexity: O(n) - process each character once
     * Space Complexity: O(1) - only accumulator state
     * 
     * Best when: Functional programming style preferred, composability important
     * Worst when: Simple loops are clearer, performance critical
     */
    int titleToNumberFunctional(std::string columnTitle);

private:
    // Helper for recursive approach
    int titleToNumberRecursiveHelper(const std::string& columnTitle, int index);
    
    // Helper for functional approach
    std::function<int(int, char)> createAccumulator();
    
    // Helper to convert character to value
    inline int charToValue(char c) {
        return c - 'A' + 1;
    }
};

}  // namespace easy
}  // namespace leetcode