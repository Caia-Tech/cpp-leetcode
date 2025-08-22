#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 217: Contains Duplicate
 *
 * Given an integer array nums, return true if any value appears at least twice
 * in the array, and return false if every element is distinct.
 */

// Approach 1: Sort and check adjacent elements
class ContainsDuplicateSort {
public:
    bool containsDuplicate(std::vector<int> nums);
};

// Approach 2: Hash set lookup
class ContainsDuplicateHashSet {
public:
    bool containsDuplicate(const std::vector<int>& nums);
};

// Approach 3: Hash map counting
class ContainsDuplicateHashMap {
public:
    bool containsDuplicate(const std::vector<int>& nums);
};

// Approach 4: Bit vector using offset (only practical for small ranges)
class ContainsDuplicateBitVector {
public:
    bool containsDuplicate(const std::vector<int>& nums);
};

// Approach 5: Sort and binary search each element's tail
class ContainsDuplicateBinarySearch {
public:
    bool containsDuplicate(std::vector<int> nums);
};

// Approach 6: Compare size of std::set with original array
class ContainsDuplicateSetSize {
public:
    bool containsDuplicate(const std::vector<int>& nums);
};

} // namespace easy
} // namespace leetcode

