#pragma once

#include <string>
#include <vector>

namespace leetcode {
namespace easy {

/**
 * Problem 9: Palindrome Number
 * 
 * Given an integer x, return true if x is a palindrome, and false otherwise.
 * An integer is a palindrome when it reads the same backward as forward.
 * 
 * Constraints:
 * - -2^31 <= x <= 2^31 - 1
 * 
 * Follow up: Could you solve it without converting the integer to a string?
 */
class PalindromeNumber {
public:
    /**
     * Approach 1: Full Number Reversal
     * 
     * Reverse the entire number and compare with original.
     * 
     * Reasoning: This is the most intuitive approach - if a number is a palindrome,
     * its reverse should equal the original. We reverse the entire number and compare.
     * However, we need to handle overflow when reversing, and negative numbers are
     * never palindromes. This approach is straightforward but does unnecessary work
     * for large numbers since we only need to check half the digits.
     * 
     * Time Complexity: O(log n) - process each digit once
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Simple implementation is preferred, number size is manageable
     * Worst when: Risk of overflow exists or optimization is critical
     */
    bool isPalindromeFullReverse(int x);

    /**
     * Approach 2: Half Reversal
     * 
     * Reverse only half of the number for efficiency.
     * 
     * Reasoning: This is the optimal mathematical approach. Key insight: we only need
     * to reverse half the digits and compare with the other half. For even-length numbers,
     * we compare reversed_half == remaining_half. For odd-length numbers, we compare
     * reversed_half == remaining_half/10 (ignoring middle digit). This avoids overflow
     * issues and is more efficient than full reversal.
     * 
     * Time Complexity: O(log n) - but roughly half the iterations
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal performance, want to avoid overflow
     * Worst when: Implementation complexity is a concern
     */
    bool isPalindromeHalfReverse(int x);

    /**
     * Approach 3: String Conversion
     * 
     * Convert to string and check palindrome property.
     * 
     * Reasoning: This leverages string operations which are often highly optimized.
     * Convert the number to string, then use two pointers to check from both ends.
     * While this uses extra space, it's often the clearest and least error-prone
     * approach. String comparison avoids mathematical overflow issues entirely.
     * 
     * Time Complexity: O(log n) - string creation and comparison
     * Space Complexity: O(log n) - storing string representation
     * 
     * Best when: Code clarity is prioritized, string operations are fast
     * Worst when: Memory usage is critical or string conversion is expensive
     */
    bool isPalindromeString(int x);

    /**
     * Approach 4: Digit Array
     * 
     * Store digits in array and check from both ends.
     * 
     * Reasoning: This approach separates digit extraction from palindrome checking.
     * First extract all digits into an array, then use two pointers to check.
     * This makes the algorithm easy to understand and debug. The explicit array
     * storage makes it clear what digits we're comparing at each step.
     * 
     * Time Complexity: O(log n) - extract digits + array comparison
     * Space Complexity: O(log n) - array to store all digits
     * 
     * Best when: Need to debug digit extraction, want explicit storage
     * Worst when: Memory usage must be minimized
     */
    bool isPalindromeArray(int x);

    /**
     * Approach 5: Recursive
     * 
     * Recursively check first and last digits.
     * 
     * Reasoning: This demonstrates divide-and-conquer thinking. Extract the first
     * and last digits, compare them, then recursively check the remaining middle.
     * Base cases are single digit (always palindrome) or empty (palindrome).
     * While elegant, it requires careful digit position calculation and has
     * call stack overhead.
     * 
     * Time Complexity: O(log n) - recursive calls for each digit pair
     * Space Complexity: O(log n) - call stack depth equals half the digits
     * 
     * Best when: Recursive solutions are preferred, educational purposes
     * Worst when: Call stack is limited or iterative approach is simpler
     */
    bool isPalindromeRecursive(int x);

    /**
     * Approach 6: Mathematical Division
     * 
     * Use division to extract and compare digits.
     * 
     * Reasoning: This approach uses mathematical operations to extract first and last
     * digits without conversion. Use modulo to get last digit, use division by
     * appropriate power of 10 to get first digit. Shrink the number by removing
     * both ends until we've checked all digit pairs. More complex than other approaches
     * but demonstrates pure mathematical digit manipulation.
     * 
     * Time Complexity: O(log n) - process digit pairs from both ends
     * Space Complexity: O(1) - only using mathematical operations
     * 
     * Best when: Want pure mathematical solution, no conversions allowed
     * Worst when: Code complexity outweighs benefits of avoiding conversions
     */
    bool isPalindromeDivision(int x);

private:
    bool checkPalindromeRecursive(int x, int& original, int& divisor);
    int getNumberOfDigits(int x);
};

}
}