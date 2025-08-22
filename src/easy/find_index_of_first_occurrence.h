#pragma once

#include <string>
#include <vector>

namespace leetcode {
namespace easy {

/**
 * Problem 28: Find the Index of the First Occurrence in a String
 * 
 * Given two strings needle and haystack, return the index of the first occurrence of needle 
 * in haystack, or -1 if needle is not part of haystack.
 * 
 * Constraints:
 * - 1 <= haystack.length, needle.length <= 10^4
 * - haystack and needle consist of only lowercase English characters.
 */
class FindIndexOfFirstOccurrence {
public:
    /**
     * Approach 1: Brute Force
     * 
     * Check every possible starting position in haystack.
     * 
     * Reasoning: The most straightforward approach - for each position in haystack,
     * check if needle matches starting from that position. Compare character by
     * character until mismatch found or needle fully matched. While simple to
     * understand and implement, it can be inefficient when there are many partial
     * matches that fail near the end of needle.
     * 
     * Time Complexity: O(nm) - n is haystack length, m is needle length
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Small strings, simple implementation needed
     * Worst when: Many partial matches, performance is critical
     */
    int strStrBruteForce(const std::string& haystack, const std::string& needle);

    /**
     * Approach 2: STL find() Function
     * 
     * Use built-in string find function.
     * 
     * Reasoning: C++ STL provides string::find() which is highly optimized for
     * substring searching. It typically uses efficient algorithms like Boyer-Moore
     * or similar. While this gives best practical performance, it may not be
     * allowed in interviews where manual implementation is expected.
     * 
     * Time Complexity: O(nm) worst case, often much better in practice
     * Space Complexity: O(1) - built-in function
     * 
     * Best when: Production code, STL usage allowed, need optimal performance
     * Worst when: Need to implement algorithm manually, interview restrictions
     */
    int strStrSTL(const std::string& haystack, const std::string& needle);

    /**
     * Approach 3: KMP (Knuth-Morris-Pratt) Algorithm
     * 
     * Use failure function to avoid redundant comparisons.
     * 
     * Reasoning: KMP preprocesses the needle to create a failure function that
     * tells us how far we can skip when a mismatch occurs. This avoids re-examining
     * characters in haystack that we've already matched. The failure function
     * captures the longest proper prefix which is also suffix for each position.
     * Guarantees linear time complexity.
     * 
     * Time Complexity: O(n + m) - linear preprocessing and search
     * Space Complexity: O(m) - failure function array
     * 
     * Best when: Need guaranteed linear time, repeated searching of same needle
     * Worst when: Implementation complexity outweighs benefits for simple cases
     */
    int strStrKMP(const std::string& haystack, const std::string& needle);

    /**
     * Approach 4: Rabin-Karp (Rolling Hash)
     * 
     * Use rolling hash to quickly compare substrings.
     * 
     * Reasoning: Compute hash of needle and rolling hash of haystack substrings.
     * When hashes match, verify with character-by-character comparison to handle
     * hash collisions. Rolling hash allows constant-time updates when sliding
     * the window. Expected linear time but worst-case can be quadratic due to
     * hash collisions.
     * 
     * Time Complexity: O(nm) worst case, O(n + m) expected
     * Space Complexity: O(1) - only hash variables
     * 
     * Best when: Expected case performance is good, understand hashing algorithms
     * Worst when: Hash collisions are frequent, guaranteed linear time needed
     */
    int strStrRabinKarp(const std::string& haystack, const std::string& needle);

    /**
     * Approach 5: Two Pointers with Reset
     * 
     * Use two pointers with intelligent reset on mismatch.
     * 
     * Reasoning: Similar to brute force but with optimized reset logic. When
     * a mismatch occurs after partial match, instead of restarting from next
     * character, try to reset more intelligently based on the matched prefix.
     * This approach is between brute force and KMP in terms of complexity
     * and implementation difficulty.
     * 
     * Time Complexity: O(nm) worst case, better than brute force on average
     * Space Complexity: O(1) - only using pointer variables
     * 
     * Best when: Want optimization over brute force without KMP complexity
     * Worst when: KMP or other advanced algorithms are available
     */
    int strStrTwoPointers(const std::string& haystack, const std::string& needle);

    /**
     * Approach 6: Boyer-Moore Inspired (Simplified)
     * 
     * Skip characters based on mismatch character analysis.
     * 
     * Reasoning: Simplified version of Boyer-Moore algorithm. When mismatch occurs,
     * skip ahead based on the mismatched character's position in needle. If the
     * mismatched character doesn't appear in needle, skip entire needle length.
     * This can be very fast for certain types of inputs but requires preprocessing
     * of needle for character positions.
     * 
     * Time Complexity: O(nm) worst case, can be sublinear for favorable inputs
     * Space Complexity: O(k) - character position map, where k is alphabet size
     * 
     * Best when: Alphabet is small, many characters in haystack don't appear in needle
     * Worst when: All characters are similar, preprocessing overhead not worth it
     */
    int strStrBoyerMooreSimple(const std::string& haystack, const std::string& needle);

private:
    // KMP helper function
    std::vector<int> computeFailureFunction(const std::string& needle);
    
    // Rabin-Karp helper functions
    static const int PRIME = 101;
    long long computeHash(const std::string& str, int len);
    long long rollingHash(long long oldHash, char oldChar, char newChar, long long pow);
    
    // Boyer-Moore helper
    std::vector<int> buildLastOccurrence(const std::string& needle);
};

}
}