#pragma once

#include <vector>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 704: Binary Search
 *
 * Given an array of integers nums which is sorted in ascending order, and an integer target,
 * write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
 * You must write an algorithm with O(log n) runtime complexity.
 */

/** Approach 1: Iterative binary search with inclusive bounds. */
class BinarySearchIterative {
public:
    int search(const std::vector<int>& nums, int target);
};

/** Approach 2: Recursive binary search. */
class BinarySearchRecursive {
public:
    int search(const std::vector<int>& nums, int target);
private:
    int helper(const std::vector<int>& nums, int left, int right, int target);
};

/** Approach 3: std::lower_bound to locate insertion point. */
class BinarySearchLowerBound {
public:
    int search(const std::vector<int>& nums, int target);
};

/** Approach 4: std::binary_search followed by std::lower_bound. */
class BinarySearchStdBinarySearch {
public:
    int search(const std::vector<int>& nums, int target);
};

/** Approach 5: Half-open interval [left, right) binary search. */
class BinarySearchHalfOpen {
public:
    int search(const std::vector<int>& nums, int target);
};

/** Approach 6: Iterative search using bitwise mid computation. */
class BinarySearchBitwiseMid {
public:
    int search(const std::vector<int>& nums, int target);
};

} // namespace easy
} // namespace leetcode

