#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace leetcode {
namespace easy {

/**
 * Problem 136: Single Number
 *
 * Given a non-empty array of integers nums, every element appears twice except for one. 
 * Find that single one.
 *
 * All approaches below run in O(n) time unless otherwise noted and provide
 * different perspectives on solving the problem without using extra memory
 * beyond what each strategy requires.
 */

/**
 * Approach 1: Sorting
 *
 * Sort the array and check neighboring elements to find the unique value.
 *
 * - Time Complexity: O(n log n) due to sorting
 * - Space Complexity: O(1) or O(n) depending on sorting algorithm
 */
class SingleNumberSort {
public:
    int singleNumber(std::vector<int>& nums);
};

/**
 * Approach 2: Hash Map Counting
 *
 * Count occurrences using an unordered_map and return the key with count 1.
 *
 * - Time Complexity: O(n)
 * - Space Complexity: O(n)
 */
class SingleNumberHashMap {
public:
    int singleNumber(std::vector<int>& nums);
};

/**
 * Approach 3: Bitwise XOR
 *
 * XOR all elements; pairs cancel out leaving the unique number.
 *
 * - Time Complexity: O(n)
 * - Space Complexity: O(1)
 */
class SingleNumberXOR {
public:
    int singleNumber(std::vector<int>& nums);
};

/**
 * Approach 4: Bit Counting
 *
 * Count set bits at each position. Since pairs contribute even counts, the
 * remaining bits compose the unique number.
 *
 * - Time Complexity: O(n * k) where k is number of bits (32)
 * - Space Complexity: O(1)
 */
class SingleNumberBitCount {
public:
    int singleNumber(std::vector<int>& nums);
};

/**
 * Approach 5: Mathematical Set Difference
 *
 * Use the identity `2 * sum(set(nums)) - sum(nums)` to compute the unique value.
 *
 * - Time Complexity: O(n)
 * - Space Complexity: O(n)
 */
class SingleNumberMath {
public:
    int singleNumber(std::vector<int>& nums);
};

/**
 * Approach 6: Hash Set Toggle
 *
 * Insert numbers into an unordered_set; remove when seen again. Remaining
 * element is the answer.
 *
 * - Time Complexity: O(n)
 * - Space Complexity: O(n)
 */
class SingleNumberSetToggle {
public:
    int singleNumber(std::vector<int>& nums);
};

} // namespace easy
} // namespace leetcode

