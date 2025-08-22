#pragma once

#include <string>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <map>
#include <set>

namespace leetcode {
namespace easy {

/**
 * Problem 383: Ransom Note
 *
 * Given two strings ransomNote and magazine, return true if ransomNote can be
 * constructed from magazine and false otherwise. Each letter in magazine can only
 * be used once in ransomNote.
 *
 * Constraints:
 * - 1 <= ransomNote.length, magazine.length <= 10^5
 * - ransomNote and magazine consist of lowercase English letters
 */
class RansomNote {
public:
    /**
     * Approach 1: Frequency Array
     *
     * Build a count of magazine letters using a fixed-size array and decrement
     * for each letter in the ransom note. If any count becomes negative, the note
     * cannot be constructed.
     *
     * Time Complexity: O(n + m) where n and m are lengths of ransomNote and magazine
     * Space Complexity: O(1) - fixed array of size 26
     */
    bool canConstructCountArray(const std::string& ransomNote, const std::string& magazine);

    /**
     * Approach 2: Hash Map Counting
     *
     * Use unordered_map to count magazine characters then decrement for ransom
     * characters. Works for full ASCII range.
     *
     * Time Complexity: O(n + m)
     * Space Complexity: O(k) where k is number of distinct characters
     */
    bool canConstructHashMap(const std::string& ransomNote, const std::string& magazine);

    /**
     * Approach 3: Sorting with Two Pointers
     *
     * Sort both strings and walk them using two pointers, consuming magazine
     * characters when they match ransom characters.
     *
     * Time Complexity: O(n log n + m log m)
     * Space Complexity: O(1) or O(log n) depending on sort implementation
     */
    bool canConstructSorting(std::string ransomNote, std::string magazine);

    /**
     * Approach 4: Single Pass Difference Array
     *
     * Iterate through magazine incrementing counts and through ransom note
     * decrementing counts on the fly with early exit when any count goes negative.
     *
     * Time Complexity: O(n + m)
     * Space Complexity: O(1)
     */
    bool canConstructSinglePass(const std::string& ransomNote, const std::string& magazine);

    /**
     * Approach 5: Multiset Erasure
     *
     * Insert magazine letters into a multiset then attempt to erase each ransom
     * character. If any erase fails, construction is impossible.
     *
     * Time Complexity: O((n + m) log m)
     * Space Complexity: O(m)
     */
    bool canConstructMultiset(const std::string& ransomNote, const std::string& magazine);

    /**
     * Approach 6: Ordered Map Comparison
     *
     * Use std::map to count letters for both strings and ensure magazine has at
     * least as many of each letter as required by ransom note.
     *
     * Time Complexity: O((n + m) log k)
     * Space Complexity: O(k)
     */
    bool canConstructMap(const std::string& ransomNote, const std::string& magazine);
};

} // namespace easy
} // namespace leetcode

