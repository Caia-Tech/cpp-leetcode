#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <bitset>

namespace leetcode {
namespace easy {

/**
 * Problem 350: Intersection of Two Arrays II
 *
 * Given two integer arrays nums1 and nums2, return an array of their
 * intersection. Each element in the result must appear as many times as it
 * shows in both arrays and you may return the result in any order.
 *
 * Constraints:
 * - 1 <= nums1.length, nums2.length <= 1000
 * - 0 <= nums1[i], nums2[i] <= 1000
 *
 * This header declares six different approaches with detailed reasoning.
 */

// Approach 1: Hash Map Counting
class IntersectionHashMap {
public:
    std::vector<int> intersect(std::vector<int> nums1, std::vector<int> nums2);
};

// Approach 2: Sorting with Two Pointers
class IntersectionSortTwoPointers {
public:
    std::vector<int> intersect(std::vector<int> nums1, std::vector<int> nums2);
};

// Approach 3: Sorting with Binary Search
class IntersectionSortBinarySearch {
public:
    std::vector<int> intersect(std::vector<int> nums1, std::vector<int> nums2);
};

// Approach 4: Multiset Intersection
class IntersectionMultiset {
public:
    std::vector<int> intersect(std::vector<int> nums1, std::vector<int> nums2);
};

// Approach 5: Optimized Hash Map (use smaller array for map)
class IntersectionHashMapOptimized {
public:
    std::vector<int> intersect(std::vector<int> nums1, std::vector<int> nums2);
};

// Approach 6: Frequency Array (using value constraints 0..1000)
class IntersectionFrequencyArray {
public:
    std::vector<int> intersect(std::vector<int> nums1, std::vector<int> nums2);
};

} // namespace easy
} // namespace leetcode

