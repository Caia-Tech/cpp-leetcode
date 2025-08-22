#pragma once

#include <cmath>
#include <string>
#include <unordered_set>
#include <cstdint>

namespace leetcode {
namespace easy {

/**
 * Problem 326: Power of Three
 *
 * Given an integer n, return true if it is a power of three. Otherwise,
 * return false. An integer n is a power of three if there exists an integer x
 * such that n == 3^x.
 */

/**
 * Approach 1: Iterative Division
 *
 * Repeatedly divide n by 3 while it is divisible. If the result is 1, n is a
 * power of three.
 *
 * Time Complexity: O(log_3 n)
 * Space Complexity: O(1)
 */
class PowerOfThreeIterative {
public:
    bool isPowerOfThree(int n);
};

/**
 * Approach 2: Recursive Division
 *
 * Recursively divide n by 3. Base case when n == 1. If n is not divisible by 3
 * at any step, return false.
 *
 * Time Complexity: O(log_3 n)
 * Space Complexity: O(log_3 n) due to recursion stack
 */
class PowerOfThreeRecursive {
public:
    bool isPowerOfThree(int n);
};

/**
 * Approach 3: Logarithmic Check
 *
 * Use logarithms to compute the potential exponent x = log_3(n) and verify if
 * 3^x equals n.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
class PowerOfThreeLogarithm {
public:
    bool isPowerOfThree(int n);
};

/**
 * Approach 4: Base-3 Representation
 *
 * Convert n to its base-3 string. A power of three has form "10*" in base 3.
 *
 * Time Complexity: O(log_3 n)
 * Space Complexity: O(log_3 n)
 */
class PowerOfThreeBase3 {
public:
    bool isPowerOfThree(int n);
};

/**
 * Approach 5: Maximum Power of Three
 *
 * The largest power of three within 32-bit signed int is 3^19 = 1162261467.
 * n is a power of three iff it divides this constant.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
class PowerOfThreeMaxPower {
public:
    bool isPowerOfThree(int n);
};

/**
 * Approach 6: Precomputed Set
 *
 * Precompute all powers of three within 32-bit range and check membership.
 *
 * Time Complexity: O(log_3 n) to build set once, O(1) per query
 * Space Complexity: O(log_3 INT_MAX)
 */
class PowerOfThreePrecompute {
public:
    PowerOfThreePrecompute();
    bool isPowerOfThree(int n);

private:
    std::unordered_set<int> powers;
};

} // namespace easy
} // namespace leetcode

