#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace leetcode {
namespace medium {

/**
 * Problem 3: Longest Substring Without Repeating Characters
 * 
 * Given a string s, find the length of the longest substring without repeating characters.
 * 
 * Constraints:
 * - 0 <= s.length <= 5 * 10^4
 * - s consists of English letters, digits, symbols and spaces.
 */
class LongestSubstringWithoutRepeating {
public:
    /**
     * Approach 1: Brute Force
     * 
     * Check all possible substrings for uniqueness.
     * 
     * Reasoning: The most straightforward approach - enumerate all possible
     * substrings and check each one for unique characters. For each starting position,
     * check all ending positions, and for each substring, verify all characters are
     * unique. While this guarantees finding the optimal solution, it's highly
     * inefficient due to triple nested operations.
     * 
     * Time Complexity: O(n^3) - n^2 substrings, each takes O(n) to check uniqueness
     * Space Complexity: O(min(n, m)) - set to store characters for uniqueness check
     * 
     * Best when: Very small strings, need baseline for testing
     * Worst when: Any practical use case, strings longer than ~10 characters
     */
    int lengthOfLongestSubstringBruteForce(const std::string& s);

    /**
     * Approach 2: Sliding Window with Hash Set
     * 
     * Use sliding window with set to track unique characters.
     * 
     * Reasoning: This introduces the sliding window technique. Maintain a window
     * [left, right] and a set of characters in current window. Expand right pointer
     * until duplicate found, then shrink left pointer until duplicate removed.
     * The set provides O(1) lookup for duplicates. In worst case, each character
     * is visited twice (once by right, once by left pointer).
     * 
     * Time Complexity: O(2n) = O(n) - each character visited at most twice
     * Space Complexity: O(min(n, m)) - set stores at most min(string length, charset size)
     * 
     * Best when: Learning sliding window technique, straightforward implementation
     * Worst when: Need maximum optimization (can be improved further)
     */
    int lengthOfLongestSubstringHashSet(const std::string& s);

    /**
     * Approach 3: Sliding Window Optimized with Hash Map
     * 
     * Track character indices to skip directly.
     * 
     * Reasoning: This optimizes approach 2 by eliminating the gradual left pointer
     * movement. Instead of removing characters one by one when duplicate found,
     * jump the left pointer directly to the position after the duplicate character.
     * Hash map stores character -> index mapping, allowing direct jumps. This
     * ensures each character is visited at most once.
     * 
     * Time Complexity: O(n) - each character visited exactly once
     * Space Complexity: O(min(n, m)) - hash map storage
     * 
     * Best when: Need optimal sliding window solution, standard interview answer
     * Worst when: Memory usage must be minimized for specific character sets
     */
    int lengthOfLongestSubstringHashMap(const std::string& s);

    /**
     * Approach 4: ASCII Array (Optimized for ASCII)
     * 
     * Use fixed array for ASCII characters.
     * 
     * Reasoning: When character set is limited (e.g., ASCII), replace hash map with
     * fixed-size array indexed by character code. This provides faster access than
     * hash operations and predictable memory usage. Array[128] covers all ASCII
     * characters. Same sliding window logic as approach 3 but with array lookup
     * instead of hash map.
     * 
     * Time Complexity: O(n) - single pass with O(1) array access
     * Space Complexity: O(128) = O(1) - fixed array size regardless of input
     * 
     * Best when: ASCII-only strings, need maximum performance
     * Worst when: Unicode characters or very large character sets
     */
    int lengthOfLongestSubstringASCII(const std::string& s);

    /**
     * Approach 5: Dynamic Programming
     * 
     * Track longest substring ending at each position.
     * 
     * Reasoning: Frame as DP problem where dp[i] = length of longest substring
     * without repeating characters ending at position i. For each position,
     * either extend the previous substring or start fresh if current character
     * creates a duplicate. This approach makes the optimal substructure explicit
     * and can be useful when you need intermediate results.
     * 
     * Time Complexity: O(n) - single pass to fill DP array
     * Space Complexity: O(n) - DP array storage
     * 
     * Best when: Need all intermediate results, DP approach is more intuitive
     * Worst when: Memory usage is critical and sliding window suffices
     */
    int lengthOfLongestSubstringDP(const std::string& s);

    /**
     * Approach 6: Two Pointers with Character Count
     * 
     * Use two pointers with character frequency tracking.
     * 
     * Reasoning: Alternative implementation of sliding window that uses character
     * frequency counts instead of indices. Maintain counts of characters in current
     * window. When a character count exceeds 1, shrink window from left until
     * that character count becomes 1. This approach is more explicit about the
     * "no repeating characters" constraint through frequency tracking.
     * 
     * Time Complexity: O(n) - each character processed at most twice
     * Space Complexity: O(min(n, m)) - frequency map storage
     * 
     * Best when: Frequency-based thinking is more intuitive
     * Worst when: Index-based jumping (approach 3) is more efficient
     */
    int lengthOfLongestSubstringTwoPointers(const std::string& s);

private:
    bool hasUniqueCharacters(const std::string& s, int start, int end);
};

}
}