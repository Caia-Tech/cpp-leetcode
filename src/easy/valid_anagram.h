#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>

namespace leetcode {
namespace easy {

/**
 * Problem 242: Valid Anagram
 *
 * Given two strings s and t, return true if t is an anagram of s,
 * and false otherwise.
 *
 * Constraints:
 * - 1 <= s.length, t.length <= 5 * 10^4
 * - s and t consist of lowercase English letters
 */

// Approach 1: Sort both strings and compare
class ValidAnagramSort {
public:
    bool isAnagram(std::string s, std::string t);
};

// Approach 2: Count using fixed-size array
class ValidAnagramCountArray {
public:
    bool isAnagram(std::string s, std::string t);
};

// Approach 3: Count using unordered_map
class ValidAnagramHashMap {
public:
    bool isAnagram(std::string s, std::string t);
};

// Approach 4: Counting sort comparison
class ValidAnagramCountingSort {
public:
    bool isAnagram(std::string s, std::string t);
};

// Approach 5: Prime product hashing
class ValidAnagramPrimeProduct {
public:
    bool isAnagram(std::string s, std::string t);
};

// Approach 6: Single pass count increment/decrement
class ValidAnagramSinglePass {
public:
    bool isAnagram(std::string s, std::string t);
};

} // namespace easy
} // namespace leetcode
