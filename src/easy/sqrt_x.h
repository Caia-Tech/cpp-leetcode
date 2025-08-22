#pragma once

#include <cmath>

namespace leetcode {
namespace easy {

/**
 * Problem 69: Sqrt(x)
 * 
 * Given a non-negative integer x, return the square root of x rounded down to the nearest integer. 
 * The returned integer should be non-negative as well.
 * 
 * You must not use any built-in exponent function or operator.
 * 
 * Constraints:
 * - 0 <= x <= 2^31 - 1
 */
class SqrtX {
public:
    /**
     * Approach 1: Binary Search (Optimal)
     * 
     * Use binary search to find the largest integer whose square <= x.
     * 
     * Reasoning: This is the optimal approach. The square root lies between 0 and x,
     * but we can optimize the upper bound to x/2 + 1 for x >= 2. Use binary search
     * to find the largest integer mid such that mid^2 <= x. When mid^2 <= x, the
     * answer might be mid or larger, so search right. When mid^2 > x, the answer
     * is smaller, so search left. Handle integer overflow carefully when computing mid^2.
     * 
     * Time Complexity: O(log x) - binary search through possible values
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal logarithmic time, avoiding built-in sqrt
     * Worst when: Simple linear search is acceptable for small inputs
     */
    int mySqrtBinarySearch(int x);

    /**
     * Approach 2: Newton's Method (Babylonian Method)
     * 
     * Use Newton's iterative method to approximate square root.
     * 
     * Reasoning: Newton's method for finding square root uses the iteration:
     * next = (current + x/current) / 2. Start with initial guess (often x/2 or x)
     * and iterate until convergence. This method has quadratic convergence rate,
     * making it very fast in practice. However, requires careful handling of
     * integer arithmetic and convergence criteria.
     * 
     * Time Complexity: O(log log x) - quadratic convergence
     * Space Complexity: O(1) - only using constant variables
     * 
     * Best when: Need fast convergence, understand numerical methods
     * Worst when: Integer overflow handling becomes complex
     */
    int mySqrtNewton(int x);

    /**
     * Approach 3: Linear Search (Brute Force)
     * 
     * Search linearly from 0 until i^2 > x, return i-1.
     * 
     * Reasoning: Simple brute force approach. Start from 0 and increment until
     * we find the first number whose square exceeds x. The answer is the previous
     * number. While conceptually simple, this is inefficient for large x values.
     * Useful as baseline for testing other approaches.
     * 
     * Time Complexity: O(√x) - linear search up to square root
     * Space Complexity: O(1) - only using counter variable
     * 
     * Best when: Very small inputs, need simple implementation
     * Worst when: Large inputs where √x is significant
     */
    int mySqrtLinear(int x);

    /**
     * Approach 4: Bit Manipulation
     * 
     * Build the square root bit by bit using bit manipulation.
     * 
     * Reasoning: Construct the square root by trying to set each bit from most
     * significant to least significant. For each bit position, check if setting
     * that bit in the result would make the square <= x. This approach leverages
     * the binary representation and can be efficient. Similar to binary search
     * but works at bit level.
     * 
     * Time Complexity: O(log x) - check each bit position (at most 16 for 32-bit int)
     * Space Complexity: O(1) - only using bit manipulation variables
     * 
     * Best when: Want to understand bit-level computation, educational purposes
     * Worst when: Binary search is more intuitive and equally efficient
     */
    int mySqrtBitManipulation(int x);

    /**
     * Approach 5: Mathematical Formula (Exponential and Logarithm)
     * 
     * Use the identity: sqrt(x) = e^(ln(x)/2), then truncate.
     * 
     * Reasoning: Transform square root to exponential and logarithm operations.
     * Since sqrt(x) = x^(1/2) = e^(ln(x) * 1/2), we can compute this using
     * math library functions. However, this violates the constraint of not using
     * built-in exponent functions and may have precision issues with floating point.
     * Included for mathematical completeness.
     * 
     * Time Complexity: O(1) - assuming constant time math functions
     * Space Complexity: O(1) - only using constant variables
     * 
     * Best when: Educational purposes, understanding mathematical relationships
     * Worst when: Constraint forbids built-in functions, precision is critical
     */
    int mySqrtExponential(int x);

    /**
     * Approach 6: Digit-by-Digit Calculation
     * 
     * Calculate square root digit by digit like manual calculation.
     * 
     * Reasoning: Implement the manual square root calculation method taught in
     * schools. Process digits in pairs from left to right, find the largest digit
     * d such that (20*result + d) * d <= remainder. This method directly simulates
     * the pencil-and-paper algorithm. While educational, it's complex to implement
     * correctly and not more efficient than binary search.
     * 
     * Time Complexity: O(log x) - process each digit pair
     * Space Complexity: O(1) - only using calculation variables
     * 
     * Best when: Educational purposes, understanding manual calculation
     * Worst when: Simpler methods available, implementation complexity is high
     */
    int mySqrtDigitByDigit(int x);

private:
    // Helper functions
    bool canSquare(long long mid, int x);
    int digitByDigitHelper(int x);
};

}
}