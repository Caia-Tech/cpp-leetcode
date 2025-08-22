#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <array>

namespace leetcode {
namespace medium {

/**
 * Problem 49: Group Anagrams
 * 
 * Given an array of strings strs, group the anagrams together. 
 * You can return the answer in any order.
 * 
 * An anagram is a word or phrase formed by rearranging the letters 
 * of a different word or phrase, typically using all the original 
 * letters exactly once.
 * 
 * Constraints:
 * - 1 <= strs.length <= 10^4
 * - 0 <= strs[i].length <= 100
 * - strs[i] consists of lowercase English letters only.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class GroupAnagrams {
public:
    /**
     * Approach 1: Sorting-Based Grouping (Classic)
     * 
     * Group strings by their sorted character representation.
     * 
     * Reasoning: Two strings are anagrams if and only if they contain
     * the same characters with the same frequencies. When we sort both
     * strings, anagrams will have identical sorted representations.
     * Use this sorted string as a key in hash map to group anagrams together.
     * This is the most intuitive and commonly used approach for anagram problems.
     * 
     * Time Complexity: O(n * k log k) - n strings, each of length k, sorting each takes O(k log k)
     * Space Complexity: O(n * k) - hash map storage for all strings
     * 
     * Best when: Simple implementation needed, string lengths are moderate
     * Worst when: String lengths are very large (sorting becomes expensive)
     */
    std::vector<std::vector<std::string>> groupAnagramsSorting(std::vector<std::string>& strs);

    /**
     * Approach 2: Character Frequency Counting (Optimal)
     * 
     * Group strings by their character frequency signature.
     * 
     * Reasoning: Instead of sorting, count frequency of each character (a-z)
     * and use this frequency array as the grouping key. Since we only have
     * 26 lowercase letters, we can represent the frequency as a string like
     * "a2b1c3..." or as an array. This avoids the O(k log k) sorting cost
     * and reduces time complexity to O(n * k).
     * 
     * Time Complexity: O(n * k) - n strings, each requiring O(k) to count characters
     * Space Complexity: O(n * k) - hash map storage
     * 
     * Best when: Want optimal time complexity, many strings with long length
     * Worst when: Need simple implementation, character counting seems complex
     */
    std::vector<std::vector<std::string>> groupAnagramsFrequency(std::vector<std::string>& strs);

    /**
     * Approach 3: Prime Number Multiplication (Mathematical)
     * 
     * Assign prime numbers to each character and use product as key.
     * 
     * Reasoning: Assign unique prime numbers to each letter (a=2, b=3, c=5, etc.).
     * For each string, multiply the primes corresponding to its characters.
     * Since prime factorization is unique, two strings will have the same
     * product if and only if they are anagrams. This creates a unique
     * mathematical signature for each anagram group.
     * 
     * Time Complexity: O(n * k) - n strings, each requiring O(k) multiplication
     * Space Complexity: O(n * k) - hash map storage
     * 
     * Best when: Want mathematical elegance, avoid string operations
     * Worst when: Risk of integer overflow with long strings, less intuitive
     */
    std::vector<std::vector<std::string>> groupAnagramsPrime(std::vector<std::string>& strs);

    /**
     * Approach 4: Radix/Bucket Sort Based (Character Distribution)
     * 
     * Use character count array directly as hash map key.
     * 
     * Reasoning: Instead of converting character frequencies to string,
     * use the raw frequency array (size 26 for a-z) as the key directly.
     * This requires implementing custom hash function for arrays but can
     * be more efficient than string-based frequency representations.
     * Uses the fact that we have a limited character set (26 letters).
     * 
     * Time Complexity: O(n * k) - n strings, O(k) to count characters
     * Space Complexity: O(n * k) - hash map with array keys
     * 
     * Best when: Want to avoid string concatenation overhead
     * Worst when: Custom hash function complexity, less standard implementation
     */
    std::vector<std::vector<std::string>> groupAnagramsArray(std::vector<std::string>& strs);

    /**
     * Approach 5: Trie-Based Grouping (Advanced Data Structure)
     * 
     * Build trie where each path represents sorted character sequence.
     * 
     * Reasoning: Build a trie where each node represents a character and
     * paths from root to leaves represent sorted anagram signatures.
     * All anagrams will follow the same path in the trie. At each leaf,
     * store the list of strings that follow this path. This approach
     * can be memory efficient and allows for prefix-based optimizations.
     * 
     * Time Complexity: O(n * k) - insert each string into trie
     * Space Complexity: O(n * k) - trie storage plus string lists
     * 
     * Best when: Need prefix-based operations, advanced data structure practice
     * Worst when: Over-engineering for simple grouping, implementation complexity
     */
    std::vector<std::vector<std::string>> groupAnagramsTrie(std::vector<std::string>& strs);

    /**
     * Approach 6: Rolling Hash (String Hashing)
     * 
     * Use rolling hash function to create signature for each anagram group.
     * 
     * Reasoning: Implement a custom hash function that produces the same
     * hash value for anagrams regardless of character order. One approach
     * is to sum character values raised to the same power, or use polynomial
     * rolling hash with commutative operations. This avoids sorting or
     * explicit frequency counting but requires careful hash function design
     * to minimize collisions.
     * 
     * Time Complexity: O(n * k) - n strings, O(k) to compute hash
     * Space Complexity: O(n * k) - hash map storage
     * 
     * Best when: Want custom hashing approach, avoid sorting/counting
     * Worst when: Hash collision risk, complex hash function design
     */
    std::vector<std::vector<std::string>> groupAnagramsRollingHash(std::vector<std::string>& strs);

private:
    // Helper functions
    std::string getFrequencyString(const std::string& str);
    long long getPrimeProduct(const std::string& str);
    std::vector<int> getFrequencyArray(const std::string& str);
    long long getRollingHash(const std::string& str);
    
    // Trie node structure
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        std::vector<std::string> words;
        
        TrieNode() = default;
        ~TrieNode() {
            for (auto& pair : children) {
                delete pair.second;
            }
        }
    };
    
    void insertIntoTrie(TrieNode* root, const std::string& str);
    void collectAnagramGroups(TrieNode* root, std::vector<std::vector<std::string>>& result);
    
    // Prime numbers for first 26 letters
    static const std::vector<long long> PRIMES;
    
    // Array hash function
    struct ArrayHash {
        std::size_t operator()(const std::array<int, 26>& arr) const {
            std::size_t hash = 0;
            for (int i = 0; i < 26; ++i) {
                hash ^= std::hash<int>()(arr[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
            return hash;
        }
    };
};

}
}