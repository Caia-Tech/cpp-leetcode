#pragma once

#include <vector>
#include <unordered_set>
#include <numeric>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 268: Missing Number
 *
 * Given an array nums containing n distinct numbers taken from 0..n,
 * return the one number missing from the range.
 */

// Approach 1: Sort and scan for mismatch
class MissingNumberSort {
public:
    int missingNumber(std::vector<int> nums);
};

// Approach 2: Hash set lookup
class MissingNumberHashSet {
public:
    int missingNumber(const std::vector<int>& nums);
};

// Approach 3: Sum formula n(n+1)/2 minus actual sum
class MissingNumberSum {
public:
    int missingNumber(const std::vector<int>& nums);
};

// Approach 4: XOR all indices and values
class MissingNumberXor {
public:
    int missingNumber(const std::vector<int>& nums);
};

// Approach 5: Boolean marker array (bitset-like)
class MissingNumberBitset {
public:
    int missingNumber(const std::vector<int>& nums);
};

// Approach 6: Cyclic sort (swap into place)
class MissingNumberCyclicSort {
public:
    int missingNumber(std::vector<int>& nums);
};

} // namespace easy
} // namespace leetcode

