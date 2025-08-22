#pragma once

#include <cmath>
#include <cstdint>

namespace leetcode {
namespace easy {

/**
 * Problem 367: Valid Perfect Square
 *
 * Given a positive integer num, return true if num is a perfect square or
 * false otherwise. You must not use any built-in library function, such as
 * std::sqrt, unless specifically stated in an approach.
 *
 * Each class below demonstrates a different strategy with detailed reasoning
 * and complexity analysis.
 */

/**
 * Approach 1: Brute Force Iteration
 *
 * Linearly try all integers i with i * i <= num.
 *
 * Time Complexity: O(\sqrt{n})
 * Space Complexity: O(1)
 */
class ValidPerfectSquareBruteForce {
public:
    bool isPerfectSquare(int num);
};

/**
 * Approach 2: Binary Search
 *
 * Perform binary search on the range [1, num] to find integer square root.
 *
 * Time Complexity: O(\log n)
 * Space Complexity: O(1)
 */
class ValidPerfectSquareBinarySearch {
public:
    bool isPerfectSquare(int num);
};

/**
 * Approach 3: Newton's Method
 *
 * Iteratively improve an initial guess using Newton-Raphson until convergence.
 *
 * Time Complexity: O(\log n) iterations
 * Space Complexity: O(1)
 */
class ValidPerfectSquareNewton {
public:
    bool isPerfectSquare(int num);
};

/**
 * Approach 4: Sum of Odd Numbers
 *
 * A number is a perfect square if it can be expressed as the sum of the first
 * k odd numbers. Repeatedly subtract odd numbers until zero or negative.
 *
 * Time Complexity: O(\sqrt{n})
 * Space Complexity: O(1)
 */
class ValidPerfectSquareSumOdd {
public:
    bool isPerfectSquare(int num);
};

/**
 * Approach 5: Bitwise Square Root
 *
 * Compute integer square root using bit manipulation and compare square.
 *
 * Time Complexity: O(\log n)
 * Space Complexity: O(1)
 */
class ValidPerfectSquareBit {
public:
    bool isPerfectSquare(int num);
};

/**
 * Approach 6: Standard Library sqrt
 *
 * Use std::sqrt and verify the square. Provided for completeness.
 *
 * Time Complexity: O(1) practical
 * Space Complexity: O(1)
 */
class ValidPerfectSquareSqrt {
public:
    bool isPerfectSquare(int num);
};

} // namespace easy
} // namespace leetcode

