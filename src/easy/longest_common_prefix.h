#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 14: Longest Common Prefix
 * 
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 * 
 * Constraints:
 * - 1 <= strs.length <= 200
 * - 0 <= strs[i].length <= 200
 * - strs[i] consists of only lowercase English letters.
 * 
 * Example:
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 */
class LongestCommonPrefix {
public:
    /**
     * Approach 1: Vertical Scanning
     * 
     * Compare characters at the same index across all strings simultaneously.
     * Stop when we find a mismatch or reach the end of any string.
     * 
     * Reasoning: This approach is intuitive and stops as soon as we find the first mismatch,
     * making it efficient when the common prefix is short.
     * 
     * Time Complexity: O(S) where S is sum of all characters in all strings
     * Space Complexity: O(1)
     */
    std::string longestCommonPrefixVertical(std::vector<std::string>& strs);

    /**
     * Approach 2: Horizontal Scanning
     * 
     * Find LCP of first two strings, then find LCP of result with next string, and so on.
     * LCP(s1...sn) = LCP(LCP(LCP(s1,s2),s3),...sn)
     * 
     * Reasoning: This reduces the problem to pairwise comparisons. The prefix can only
     * get shorter or stay the same as we process more strings.
     * 
     * Time Complexity: O(S) where S is sum of all characters
     * Space Complexity: O(1)
     */
    std::string longestCommonPrefixHorizontal(std::vector<std::string>& strs);

    /**
     * Approach 3: Divide and Conquer
     * 
     * Divide strings into two halves, find LCP of each half recursively, then find LCP of results.
     * LCP(s1...sn) = LCP(LCP(s1...sk), LCP(sk+1...sn))
     * 
     * Reasoning: This approach leverages the associative property of LCP operation.
     * Good for parallelization as left and right halves can be processed independently.
     * 
     * Time Complexity: O(S) where S is sum of all characters
     * Space Complexity: O(m * log n) where m is length of shortest string, n is number of strings
     */
    std::string longestCommonPrefixDivideConquer(std::vector<std::string>& strs);

    /**
     * Approach 4: Binary Search
     * 
     * Binary search on the length of the prefix. Check if prefix of length mid is common.
     * 
     * Reasoning: The length of LCP is bounded by the shortest string. We can binary search
     * this length space to find the maximum length that forms a common prefix.
     * 
     * Time Complexity: O(S * log m) where m is length of shortest string
     * Space Complexity: O(1)
     */
    std::string longestCommonPrefixBinarySearch(std::vector<std::string>& strs);

    /**
     * Approach 5: Trie (Prefix Tree)
     * 
     * Build a trie with all strings, then find the longest path from root with single child.
     * 
     * Reasoning: Trie naturally represents common prefixes. The longest common prefix
     * is the path from root where each node has exactly one child.
     * 
     * Time Complexity: O(S) for building trie + O(m) for finding LCP
     * Space Complexity: O(S) for storing the trie
     */
    std::string longestCommonPrefixTrie(std::vector<std::string>& strs);

    /**
     * Approach 6: Sort and Compare First/Last
     * 
     * Sort the array and only compare first and last strings.
     * 
     * Reasoning: After sorting lexicographically, the first and last strings are the most
     * different. Their common prefix is the common prefix of all strings.
     * 
     * Time Complexity: O(n * m * log n) for sorting + O(m) for comparison
     * Space Complexity: O(1) if we can modify input, O(n) otherwise
     */
    std::string longestCommonPrefixSort(std::vector<std::string>& strs);

private:
    // Helper for divide and conquer
    std::string findLCP(const std::string& left, const std::string& right);
    std::string divideConquerHelper(std::vector<std::string>& strs, int left, int right);
    
    // Helper for binary search
    bool isCommonPrefix(std::vector<std::string>& strs, int length);
    
    // Trie node structure
    struct TrieNode {
        static const int ALPHABET_SIZE = 26;
        TrieNode* children[ALPHABET_SIZE];
        bool isEndOfWord;
        int childCount;
        
        TrieNode() : isEndOfWord(false), childCount(0) {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                children[i] = nullptr;
            }
        }
    };
    
    void insertTrie(TrieNode* root, const std::string& str);
    std::string searchLCPInTrie(TrieNode* root, const std::string& firstStr);
    void deleteTrie(TrieNode* root);
};

}
}