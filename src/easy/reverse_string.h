#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <deque>

namespace leetcode {
namespace easy {

/**
 * Problem 344: Reverse String
 *
 * Write a function that reverses a string. The input string is given as an
 * array of characters s.
 *
 * You must do this by modifying the input array in-place with O(1) extra
 * memory.
 *
 * Each approach below provides a different algorithmic perspective with
 * detailed reasoning and complexity analysis.
 */

/**
 * Approach 1: Two-Pointer Swap
 *
 * Maintain two indices at the beginning and end of the array and swap the
 * characters while moving the indices toward each other.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
class ReverseStringTwoPointer {
public:
    void reverseString(std::vector<char>& s);
};

/**
 * Approach 2: std::reverse
 *
 * Use the C++ standard library's std::reverse algorithm which performs the
 * reversal in-place.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
class ReverseStringStdReverse {
public:
    void reverseString(std::vector<char>& s);
};

/**
 * Approach 3: Stack-Based
 *
 * Push all characters onto a stack and pop them back into the array to obtain
 * the reversed sequence. Demonstrates use of an auxiliary data structure.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
class ReverseStringStack {
public:
    void reverseString(std::vector<char>& s);
};

/**
 * Approach 4: Recursive Swap
 *
 * Recursively swap mirrored characters moving toward the center. Illustrates a
 * divide-and-conquer style solution.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n) recursion stack
 */
class ReverseStringRecursive {
public:
    void reverseString(std::vector<char>& s);

private:
    void helper(std::vector<char>& s, int left, int right);
};

/**
 * Approach 5: XOR Swap
 *
 * Use bitwise XOR operations to swap characters without a temporary variable.
 * Provided for educational purposes.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
class ReverseStringXor {
public:
    void reverseString(std::vector<char>& s);
};

/**
 * Approach 6: Deque Rebuild
 *
 * Insert characters into a deque and reconstruct the array by popping from the
 * front. This approach highlights double-ended queue usage.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
class ReverseStringDeque {
public:
    void reverseString(std::vector<char>& s);
};

} // namespace easy
} // namespace leetcode

