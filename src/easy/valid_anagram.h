#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <bitset>

namespace leetcode {
namespace easy {

/**
 * Problem 242: Valid Anagram
 * 
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * 
 * An Anagram is a word or phrase formed by rearranging the letters of a different word 
 * or phrase, typically using all the original letters exactly once.
 * 
 * Constraints:
 * - 1 <= s.length, t.length <= 5 * 10^4
 * - s and t consist of lowercase English letters only
 * 
 * Follow up: What if the inputs contain Unicode characters? How would you adapt your 
 * solution to such a case?
 */
class ValidAnagram {
public:
    /**
     * Approach 1: Sorting (Classic)
     * 
     * Sort both strings and compare if they are equal.
     * 
     * Reasoning: The most intuitive approach - anagrams contain the same characters
     * in different order. After sorting, anagrams become identical strings. This
     * approach is simple, handles Unicode naturally, and requires minimal code.
     * The sorting step dominates the time complexity. While not optimal for time,
     * it's often preferred for its simplicity and reliability.
     * 
     * Time Complexity: O(n log n) - sorting dominates
     * Space Complexity: O(1) or O(n) depending on sort implementation
     * 
     * Best when: Simplicity preferred, Unicode support needed, small inputs
     * Worst when: Large inputs where O(n) solution is significantly faster
     */
    bool isAnagramSorting(std::string s, std::string t);

    /**
     * Approach 2: Character Count Array (Optimal for lowercase)
     * 
     * Use fixed-size array to count character frequencies.
     * 
     * Reasoning: Since input is limited to lowercase English letters, we can
     * use a fixed array of size 26. Count characters in first string (increment),
     * then count characters in second string (decrement). If strings are anagrams,
     * all counts will be zero. This is the most efficient approach for the given
     * constraints, with both time and space being linear and optimal.
     * 
     * Time Complexity: O(n) - single pass through both strings
     * Space Complexity: O(1) - fixed size array of 26
     * 
     * Best when: Lowercase English only, optimal performance needed
     * Worst when: Unicode or mixed case characters
     */
    bool isAnagramCharArray(std::string s, std::string t);

    /**
     * Approach 3: Hash Map Counting
     * 
     * Use hash map to count character frequencies.
     * 
     * Reasoning: More flexible than character array, works with any character set.
     * First pass: count all characters in string s. Second pass: decrement counts
     * for characters in string t. If any count becomes negative or doesn't reach
     * zero, strings aren't anagrams. This approach easily extends to Unicode and
     * mixed case scenarios mentioned in the follow-up.
     * 
     * Time Complexity: O(n) - two passes through strings
     * Space Complexity: O(k) - where k is number of unique characters
     * 
     * Best when: Unicode support needed, flexible character sets
     * Worst when: Only lowercase English (array approach is faster)
     */
    bool isAnagramHashMap(std::string s, std::string t);

    /**
     * Approach 4: Single Hash Map Pass
     * 
     * Count characters from both strings in single pass.
     * 
     * Reasoning: Optimize hash map approach by processing both strings
     * simultaneously. For each position, increment count for character from s
     * and decrement for character from t. After processing, all counts should
     * be zero. This reduces the number of hash map operations and can be faster
     * in practice, especially when strings are similar lengths.
     * 
     * Time Complexity: O(n) - single pass through both strings
     * Space Complexity: O(k) - where k is number of unique characters
     * 
     * Best when: Want to minimize hash map operations, similar string lengths
     * Worst when: Very different string lengths (need to handle remainder)
     */
    bool isAnagramSinglePass(std::string s, std::string t);

    /**
     * Approach 5: Bit Manipulation (XOR)
     * 
     * Use XOR properties to detect character differences.
     * 
     * Reasoning: XOR each character's ASCII value from both strings. If strings
     * are anagrams, the XOR result will be 0 (since a XOR a = 0). However, this
     * approach has a critical flaw: it only checks if XOR values are equal, not
     * if character frequencies match. For example, "ab" and "ba" work, but "aab" 
     * and "abb" would incorrectly pass. Included for educational purposes only.
     * 
     * Time Complexity: O(n) - single pass through both strings
     * Space Complexity: O(1) - only storing XOR result
     * 
     * Best when: Educational demonstration of XOR properties
     * Worst when: Correctness is important (this approach is flawed)
     */
    bool isAnagramXOR(std::string s, std::string t);

    /**
     * Approach 6: Prime Number Multiplication
     * 
     * Assign prime numbers to characters and multiply.
     * 
     * Reasoning: Assign each character a unique prime number, then multiply
     * all primes for characters in each string. By fundamental theorem of
     * arithmetic, products are equal only if same prime factors appear same
     * number of times (i.e., strings are anagrams). Creative mathematical
     * approach but has overflow risks for long strings and requires careful
     * prime selection.
     * 
     * Time Complexity: O(n) - single pass through both strings
     * Space Complexity: O(1) - only storing products
     * 
     * Best when: Mathematical elegance desired, short strings
     * Worst when: Long strings (overflow risk), production code
     */
    bool isAnagramPrime(std::string s, std::string t);

private:
    // Prime numbers for characters 'a' to 'z'
    static const long long primes[26];
    
    // Helper to get prime for character
    long long getPrime(char c) const {
        return primes[c - 'a'];
    }
};

}  // namespace easy
}  // namespace leetcode