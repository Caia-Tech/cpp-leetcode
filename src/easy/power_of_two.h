#pragma once

namespace leetcode {
namespace easy {

/**
 * Problem 231: Power of Two
 * 
 * Given an integer n, return true if it is a power of two. Otherwise, return false.
 * An integer n is a power of two, if there exists an integer x such that n == 2^x.
 * 
 * Example 1:
 * Input: n = 1
 * Output: true
 * Explanation: 2^0 = 1
 * 
 * Example 2:
 * Input: n = 16
 * Output: true
 * Explanation: 2^4 = 16
 * 
 * Example 3:
 * Input: n = 3
 * Output: false
 * 
 * Constraints:
 * -2³¹ <= n <= 2³¹ - 1
 * 
 * Follow up: Could you solve it without loops/recursion?
 */
class PowerOfTwo {
public:
    // Approach 1: Bit manipulation - Check if only one bit is set
    // Time: O(1), Space: O(1)
    // Intuition: Powers of 2 have exactly one bit set. Use n & (n-1) == 0.
    static bool isPowerOfTwoBitManipulation(int n);
    
    // Approach 2: Built-in popcount function
    // Time: O(1), Space: O(1)
    // Intuition: Powers of 2 have exactly one bit set, so popcount should be 1.
    static bool isPowerOfTwoPopCount(int n);
    
    // Approach 3: Mathematical approach using logarithms
    // Time: O(1), Space: O(1)
    // Intuition: If n is a power of 2, then log₂(n) should be an integer.
    static bool isPowerOfTwoMath(int n);
    
    // Approach 4: Iterative division by 2
    // Time: O(log n), Space: O(1)
    // Intuition: Keep dividing by 2 until we get 1 or an odd number > 1.
    static bool isPowerOfTwoDivision(int n);
    
    // Approach 5: Check against all powers of 2
    // Time: O(1), Space: O(1)
    // Intuition: Check if n is in the set of all 32-bit powers of 2.
    static bool isPowerOfTwoLookup(int n);
    
    // Approach 6: Recursive approach
    // Time: O(log n), Space: O(log n)
    // Intuition: Recursively check if n/2 is a power of 2.
    static bool isPowerOfTwoRecursive(int n);

private:
    // Helper for recursive approach
    static bool isPowerOfTwoRecursiveHelper(int n);
};

} // namespace easy
} // namespace leetcode