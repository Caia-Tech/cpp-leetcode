#pragma once

#include <string>
#include <vector>
#include <unordered_set>

namespace leetcode {
namespace medium {

/**
 * Problem 647: Palindromic Substrings
 * 
 * Given a string s, return the number of palindromic substrings in it.
 * A string is a palindrome when it reads the same backward as forward.
 * A substring is a contiguous sequence of characters within the string.
 * 
 * Constraints:
 * - 1 <= s.length <= 1000
 * - s consists of lowercase English letters.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class PalindromicSubstrings {
public:
    /**
     * Approach 1: Brute Force - Check All Substrings
     * 
     * Generate all possible substrings and check if each is palindrome.
     * 
     * Reasoning: Most straightforward approach - examine every possible substring
     * and verify palindrome property by comparing characters from both ends.
     * While inefficient, it's easy to understand and implement correctly.
     * Serves as baseline for testing and demonstrates the problem constraints.
     * Good for small inputs where simplicity matters more than performance.
     * 
     * Time Complexity: O(n³) - O(n²) substrings × O(n) palindrome check
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Small strings, need simple implementation, educational purposes
     * Worst when: Large strings where O(n³) becomes prohibitive
     */
    int countSubstringsBruteForce(std::string s);

    /**
     * Approach 2: Expand Around Centers (Optimal)
     * 
     * For each possible center, expand outward while characters match.
     * 
     * Reasoning: Key insight is that palindromes have symmetric structure.
     * For each position, treat it as potential palindrome center and expand
     * outward while characters match. Handle both odd-length palindromes
     * (single center) and even-length palindromes (center between two chars).
     * This avoids redundant work by building on palindrome structure rather
     * than checking each substring independently. Most efficient approach.
     * 
     * Time Complexity: O(n²) - n centers × O(n) expansion in worst case
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal performance, standard palindrome problems
     * Worst when: Need to track actual palindromes, not just count
     */
    int countSubstringsExpandCenters(std::string s);

    /**
     * Approach 3: Dynamic Programming - Bottom Up
     * 
     * Build palindrome table using previously computed results.
     * 
     * Reasoning: Use DP table where dp[i][j] indicates if substring s[i...j]
     * is palindrome. Base cases: single characters and two-character substrings.
     * For longer substrings, s[i...j] is palindrome if s[i] == s[j] and
     * s[i+1...j-1] is palindrome. This systematic approach ensures all
     * substrings are checked exactly once and builds solutions incrementally.
     * Useful when need to track which substrings are palindromes.
     * 
     * Time Complexity: O(n²) - fill n×n DP table
     * Space Complexity: O(n²) - DP table storage
     * 
     * Best when: Need to track palindrome locations, extending to other palindrome problems
     * Worst when: Only need count and want to minimize space usage
     */
    int countSubstringsDP(std::string s);

    /**
     * Approach 4: Manacher's Algorithm (Advanced)
     * 
     * Preprocess string and use previously computed information to avoid redundant checks.
     * 
     * Reasoning: Manacher's algorithm is specialized for palindrome problems.
     * Transform string by inserting special characters between each pair to
     * handle odd/even length uniformly. Maintain array tracking palindrome
     * radius at each position. Use symmetry property: if we know palindromes
     * around center C, we can infer information about palindromes around
     * positions symmetric to C. This eliminates redundant character comparisons.
     * 
     * Time Complexity: O(n) - each character processed at most twice
     * Space Complexity: O(n) - transformed string and radius array
     * 
     * Best when: Very large strings, multiple palindrome queries, educational
     * Worst when: Simple problems where O(n²) is acceptable, implementation complexity
     */
    int countSubstringsManachers(std::string s);

    /**
     * Approach 5: Rolling Hash with Collision Detection
     * 
     * Use polynomial rolling hash to quickly compare substrings.
     * 
     * Reasoning: Compute rolling hash for each substring and its reverse.
     * If hashes match, potential palindrome (verify to handle collisions).
     * Rolling hash allows O(1) hash computation for each substring after
     * O(n) preprocessing. This approach demonstrates how hashing can optimize
     * string problems. Handle hash collisions by explicit verification.
     * Useful pattern for other string matching problems.
     * 
     * Time Complexity: O(n²) - O(n²) substrings × O(1) hash comparison
     * Space Complexity: O(n) - precomputed hash values and powers
     * 
     * Best when: Educational hashing examples, extending to pattern matching
     * Worst when: Simple palindrome count sufficient, avoid hash complexity
     */
    int countSubstringsRollingHash(std::string s);

    /**
     * Approach 6: Suffix Array with LCP (Longest Common Prefix)
     * 
     * Build suffix array and use LCP to find palindromic patterns.
     * 
     * Reasoning: Advanced string algorithm demonstrating suffix array applications.
     * Create combined string of original + reverse with separator. Build suffix
     * array and LCP array. Palindromes correspond to common prefixes between
     * suffixes from original string and suffixes from reversed string at
     * appropriate positions. While overkill for this problem, demonstrates
     * powerful string processing techniques used in bioinformatics and text
     * processing. Educational value in understanding suffix-based algorithms.
     * 
     * Time Complexity: O(n²) - suffix array construction and LCP computation
     * Space Complexity: O(n) - suffix array, LCP array, and combined string
     * 
     * Best when: Educational purposes, part of larger string processing system
     * Worst when: Simple palindrome counting, avoid algorithmic complexity
     */
    int countSubstringsSuffixArray(std::string s);

private:
    // Helper functions for brute force approach
    bool isPalindrome(const std::string& s, int start, int end);
    
    // Helper functions for expand centers approach
    int expandAroundCenter(const std::string& s, int left, int right);
    
    // Helper functions for Manacher's algorithm
    std::string preprocess(const std::string& s);
    std::vector<int> computePalindromeRadii(const std::string& processed);
    
    // Helper functions for rolling hash approach
    static const int MOD = 1000000007;
    static const int BASE = 31;
    long long computeHash(const std::string& s, int start, int end);
    long long computeReverseHash(const std::string& s, int start, int end);
    std::vector<long long> computePowers(int n);
    std::vector<long long> computePrefixHashes(const std::string& s);
    std::vector<long long> computeSuffixHashes(const std::string& s);
    
    // Helper functions for suffix array approach
    std::vector<int> buildSuffixArray(const std::string& s);
    std::vector<int> computeLCP(const std::string& s, const std::vector<int>& suffixArray);
    int countPalindromesFromSuffixArray(const std::string& s, const std::vector<int>& sa, const std::vector<int>& lcp);
};

}
}