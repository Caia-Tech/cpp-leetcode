#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 125: Valid Palindrome
 * 
 * A phrase is a palindrome if, after converting all uppercase letters into 
 * lowercase letters and removing all non-alphanumeric characters, it reads 
 * the same forward and backward.
 * 
 * Given a string s, return true if it is a palindrome, or false otherwise.
 * 
 * Constraints:
 * - 1 <= s.length <= 2 * 10^5
 * - s consists only of printable ASCII characters.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class ValidPalindrome {
public:
    /**
     * Approach 1: Two Pointers (Optimal)
     * 
     * Use two pointers from start and end, comparing alphanumeric characters.
     * 
     * Reasoning: This is the most efficient approach with O(n) time and O(1) space.
     * Use two pointers starting from opposite ends, skip non-alphanumeric characters,
     * and compare characters after converting to lowercase. Move pointers inward
     * until they meet. This avoids creating a cleaned string and processes
     * characters on-the-fly. The key insight is that we only need to compare
     * valid characters and can skip invalid ones during traversal.
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(1) - only pointer variables
     * 
     * Best when: Want optimal space/time complexity, large strings
     * Worst when: Need to preserve processed string, multiple validations
     */
    bool isPalindromeOptimal(std::string s);

    /**
     * Approach 2: Clean and Compare (Intuitive)
     * 
     * Create cleaned string with only alphanumeric characters, then check palindrome.
     * 
     * Reasoning: This approach separates concerns: first clean the string by
     * removing non-alphanumeric characters and converting to lowercase, then
     * check if the cleaned string is a palindrome. While this uses extra space,
     * it's more intuitive and easier to understand. The logic is straightforward:
     * create a new string with only valid characters, then compare with its reverse.
     * 
     * Time Complexity: O(n) - pass to clean + pass to check palindrome
     * Space Complexity: O(n) - storage for cleaned string
     * 
     * Best when: Code clarity preferred, need cleaned string for other purposes
     * Worst when: Memory constrained, want optimal space complexity
     */
    bool isPalindromeCleanFirst(std::string s);

    /**
     * Approach 3: Recursive Validation (Educational)
     * 
     * Use recursion to check palindrome property with character filtering.
     * 
     * Reasoning: Implement palindrome check recursively where each call handles
     * one pair of characters from opposite ends. Skip non-alphanumeric characters
     * and compare valid characters after normalization. This approach demonstrates
     * the recursive nature of palindrome definition: a string is palindromic if
     * its first and last characters match and the inner substring is also palindromic.
     * 
     * Time Complexity: O(n) - each character examined once
     * Space Complexity: O(n) - recursion stack depth
     * 
     * Best when: Learning recursion, understand palindrome structure
     * Worst when: Deep recursion concerns, want iterative approach
     */
    bool isPalindromeRecursive(std::string s);

    /**
     * Approach 4: STL Algorithm Based (Concise)
     * 
     * Use STL algorithms for string cleaning and palindrome checking.
     * 
     * Reasoning: Leverage STL algorithms like std::remove_copy_if, std::transform,
     * and std::equal to create a concise solution. First clean the string using
     * algorithm functions, then use std::equal with reverse iterator to check
     * palindrome property. This approach showcases C++ STL proficiency and
     * can be very readable once familiar with the algorithms.
     * 
     * Time Complexity: O(n) - STL algorithms are optimized
     * Space Complexity: O(n) - cleaned string storage
     * 
     * Best when: STL proficiency, concise code preferred, functional style
     * Worst when: STL overhead concerns, need explicit control
     */
    bool isPalindromeSTL(std::string s);

    /**
     * Approach 5: Index-Based Validation (Systematic)
     * 
     * Use explicit indices to systematically check palindrome property.
     * 
     * Reasoning: Instead of pointers, use indices to traverse the string.
     * Maintain explicit left and right indices, advance them while skipping
     * invalid characters, and compare valid characters. This approach provides
     * clear control over traversal and can be easier to debug. It's similar
     * to two-pointer approach but uses array indexing instead of pointers.
     * 
     * Time Complexity: O(n) - single pass with index management
     * Space Complexity: O(1) - only index variables
     * 
     * Best when: Prefer array indexing over pointers, explicit control needed
     * Worst when: Pointer approach is more natural, want minimal code
     */
    bool isPalindromeIndexBased(std::string s);

    /**
     * Approach 6: Character Frequency Analysis (Alternative)
     * 
     * Analyze character frequencies to determine palindrome possibility.
     * 
     * Reasoning: For a string to be palindromic, at most one character can
     * have an odd frequency (the middle character in odd-length palindromes).
     * Count frequency of each normalized alphanumeric character and check
     * if at most one has odd count. While this doesn't verify the actual
     * arrangement, it's a necessary condition. This approach provides different
     * algorithmic perspective on palindrome properties.
     * 
     * Time Complexity: O(n) - single pass to count frequencies
     * Space Complexity: O(1) - fixed size frequency array (36 for alphanumeric)
     * 
     * Best when: Frequency analysis insight interesting, different algorithm perspective
     * Worst when: Doesn't verify actual palindrome structure, over-engineering
     */
    bool isPalindromeFrequency(std::string s);

private:
    // Helper functions
    bool isAlphanumeric(char c);
    char normalize(char c);
    bool isValidChar(char c);
    std::string cleanString(const std::string& s);
    bool recursiveHelper(const std::string& s, int left, int right);
    
    // Character classification helpers
    bool isAlphanumericSTL(char c);
    char toLowerSTL(char c);
};

}
}