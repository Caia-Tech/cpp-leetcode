#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 5: Longest Palindromic Substring
 * 
 * Given a string s, return the longest palindromic substring in s.
 * 
 * Constraints:
 * - 1 <= s.length <= 1000
 * - s consist of only digits and English letters.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class LongestPalindromicSubstring {
public:
    /**
     * Approach 1: Expand Around Centers (Optimal for Most Cases)
     * 
     * For each possible center, expand outward while characters match.
     * 
     * Reasoning: A palindrome mirrors around its center. For each position
     * (and between positions for even-length palindromes), expand outward
     * while characters match. This approach is intuitive and efficient with
     * O(n²) time complexity in worst case but often much better in practice.
     * Handle both odd-length (center at character) and even-length (center
     * between characters) palindromes by checking both cases.
     * 
     * Time Complexity: O(n²) - n centers, each expanding up to O(n)
     * Space Complexity: O(1) - only tracking indices and length
     * 
     * Best when: Practical solution needed, most palindromes are short
     * Worst when: String has many long palindromes, want guaranteed O(n) time
     */
    std::string longestPalindromeExpandCenter(std::string s);

    /**
     * Approach 2: Dynamic Programming (Educational)
     * 
     * Build solution using 2D DP table for all substring palindrome status.
     * 
     * Reasoning: Use dp[i][j] to represent whether substring s[i...j] is a
     * palindrome. A string is palindromic if its first and last characters
     * match and the inner substring is also palindromic. Build table bottom-up
     * starting with single characters (always palindromes) and 2-character
     * substrings, then expand to longer lengths. This approach clearly shows
     * the overlapping subproblem structure.
     * 
     * Time Complexity: O(n²) - fill n×n DP table
     * Space Complexity: O(n²) - DP table storage
     * 
     * Best when: Want to understand DP structure, need all palindrome info
     * Worst when: Memory usage is concern, only need longest palindrome
     */
    std::string longestPalindromeDP(std::string s);

    /**
     * Approach 3: Manacher's Algorithm (Optimal O(n))
     * 
     * Linear time algorithm using preprocessing and clever center tracking.
     * 
     * Reasoning: Manacher's algorithm achieves O(n) time by avoiding redundant
     * comparisons. Preprocess string by inserting special characters between
     * every character (handles even/odd uniformly). Maintain rightmost boundary
     * of discovered palindromes and use symmetry property: if we're inside a
     * known palindrome, we can initialize expansion based on the mirror position.
     * This is the theoretical optimal solution.
     * 
     * Time Complexity: O(n) - each character examined at most twice
     * Space Complexity: O(n) - preprocessed string and auxiliary arrays
     * 
     * Best when: Need guaranteed linear time, processing very large strings
     * Worst when: Implementation complexity outweighs benefits, smaller inputs
     */
    std::string longestPalindromeManacher(std::string s);

    /**
     * Approach 4: Brute Force (Baseline)
     * 
     * Check all possible substrings to find longest palindrome.
     * 
     * Reasoning: Generate all possible substrings and check each one for
     * palindrome property. Start with longest possible substrings and work
     * down to avoid unnecessary checks once palindrome found. While inefficient,
     * this approach is straightforward to understand and implement, making it
     * useful as a baseline for verification and small inputs.
     * 
     * Time Complexity: O(n³) - O(n²) substrings, O(n) to check each
     * Space Complexity: O(1) - only tracking variables
     * 
     * Best when: Small inputs, need simple baseline implementation
     * Worst when: Performance critical, large input sizes
     */
    std::string longestPalindromeBruteForce(std::string s);

    /**
     * Approach 5: Suffix Array Based (Advanced)
     * 
     * Use suffix array and LCP to find palindromes efficiently.
     * 
     * Reasoning: Create suffix array of both original string and its reverse.
     * Palindromes correspond to common prefixes between suffixes of original
     * string and suffixes of reversed string at complementary positions.
     * Use Longest Common Prefix (LCP) array to identify these efficiently.
     * This approach showcases advanced string processing techniques and can
     * be extended to find all palindromes.
     * 
     * Time Complexity: O(n log n) - suffix array construction dominates
     * Space Complexity: O(n) - suffix array and LCP array storage
     * 
     * Best when: Advanced string processing practice, need all palindrome info
     * Worst when: Complexity overhead not justified, simpler solutions available
     */
    std::string longestPalindromeSuffixArray(std::string s);

    /**
     * Approach 6: Rolling Hash (Probabilistic)
     * 
     * Use rolling hash to quickly verify palindrome candidates.
     * 
     * Reasoning: For each possible center, use rolling hash to quickly check
     * if expansion creates palindrome without character-by-character comparison.
     * Compute hash of substring and its reverse; if hashes match, likely palindrome
     * (verify with actual comparison to handle collisions). This can speed up
     * the expand-around-center approach when palindromes are long and hash
     * computation is faster than character comparison.
     * 
     * Time Complexity: O(n²) average case, can be faster than naive expansion
     * Space Complexity: O(1) - only hash computation variables
     * 
     * Best when: Long palindromes expected, hash computation optimized
     * Worst when: Hash collisions concern, simple character comparison sufficient
     */
    std::string longestPalindromeRollingHash(std::string s);

private:
    // Helper functions
    int expandAroundCenter(const std::string& s, int left, int right);
    bool isPalindrome(const std::string& s, int start, int end);
    std::string preprocessForManacher(const std::string& s);
    std::vector<int> computeLPSArray(const std::string& pattern);
    
    // Suffix array helpers
    std::vector<int> buildSuffixArray(const std::string& s);
    std::vector<int> computeLCPArray(const std::string& s, const std::vector<int>& suffixArray);
    
    // Rolling hash helpers
    static const long long BASE = 256;
    static const long long MOD = 1000000007;
    long long computeHash(const std::string& s, int start, int len);
    long long computeReverseHash(const std::string& s, int start, int len);
};

}
}