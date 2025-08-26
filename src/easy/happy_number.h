#pragma once
#include <vector>
#include <unordered_set>
#include <string>

namespace leetcode {
namespace easy {

/**
 * Problem 202: Happy Number
 * 
 * Write an algorithm to determine if a number n is happy.
 * A happy number is a number defined by the following process:
 * - Starting with any positive integer, replace the number by the sum of the squares of its digits.
 * - Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
 * - Those numbers for which this process ends in 1 are happy.
 * 
 * Return true if n is a happy number, and false if not.
 * 
 * Example 1:
 * Input: n = 19
 * Output: true
 * Explanation:
 * 1² + 9² = 82
 * 8² + 2² = 68  
 * 6² + 8² = 100
 * 1² + 0² + 0² = 1
 * 
 * Example 2:
 * Input: n = 2
 * Output: false
 * 
 * Constraints:
 * 1 <= n <= 2³¹ - 1
 */
class HappyNumber {
public:
    // Approach 1: Set-based cycle detection
    // Time: O(log n), Space: O(log n)
    // Intuition: Track seen numbers to detect cycles
    static bool isHappySet(int n);
    
    // Approach 2: Floyd's cycle detection (two pointers)
    // Time: O(log n), Space: O(1)
    // Intuition: Use slow/fast pointers like in linked list cycle detection
    static bool isHappyFloyd(int n);
    
    // Approach 3: Mathematical hardcoded cycle detection
    // Time: O(log n), Space: O(1)
    // Intuition: There are only a few known cycles, check against them
    static bool isHappyMathematical(int n);
    
    // Approach 4: Recursive with memoization
    // Time: O(log n), Space: O(log n)
    // Intuition: Cache results to avoid recalculation
    static bool isHappyMemoized(int n);
    
    // Approach 5: Iterative with limit
    // Time: O(log n), Space: O(1)
    // Intuition: Happy numbers reach 1 quickly, set reasonable limit
    static bool isHappyLimited(int n);
    
    // Approach 6: Brent's cycle detection algorithm
    // Time: O(log n), Space: O(1)
    // Intuition: Alternative cycle detection with better average performance
    static bool isHappyBrent(int n);

private:
    // Helper function to get sum of squares of digits
    static int getSumOfSquares(int n);
    
    // Helper for memoized approach
    static bool isHappyMemoizedHelper(int n, std::unordered_set<int>& memo);
};

} // namespace easy
} // namespace leetcode