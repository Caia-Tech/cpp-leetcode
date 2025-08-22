#include "easy/intersection_of_two_arrays_ii.h"

namespace leetcode {
namespace easy {

// -----------------------------------------------------------------------------
// Approach 1: Hash Map Counting
// -----------------------------------------------------------------------------

std::vector<int> IntersectionHashMap::intersect(std::vector<int> nums1, std::vector<int> nums2) {
    std::unordered_map<int, int> counts;
    for (int n : nums1) counts[n]++;
    std::vector<int> result;
    for (int n : nums2) {
        auto it = counts.find(n);
        if (it != counts.end() && it->second > 0) {
            result.push_back(n);
            it->second--;
        }
    }
    return result;
}

// -----------------------------------------------------------------------------
// Approach 2: Sorting with Two Pointers
// -----------------------------------------------------------------------------

std::vector<int> IntersectionSortTwoPointers::intersect(std::vector<int> nums1, std::vector<int> nums2) {
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    size_t i = 0, j = 0;
    std::vector<int> result;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] == nums2[j]) {
            result.push_back(nums1[i]);
            i++; j++;
        } else if (nums1[i] < nums2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return result;
}

// -----------------------------------------------------------------------------
// Approach 3: Sorting with Binary Search
// -----------------------------------------------------------------------------

std::vector<int> IntersectionSortBinarySearch::intersect(std::vector<int> nums1, std::vector<int> nums2) {
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    std::vector<int> result;
    size_t start = 0;
    for (int n : nums1) {
        auto it = std::lower_bound(nums2.begin() + start, nums2.end(), n);
        if (it != nums2.end() && *it == n) {
            result.push_back(n);
            start = (it - nums2.begin()) + 1; // move past used element
        }
    }
    return result;
}

// -----------------------------------------------------------------------------
// Approach 4: Multiset Intersection
// -----------------------------------------------------------------------------

std::vector<int> IntersectionMultiset::intersect(std::vector<int> nums1, std::vector<int> nums2) {
    std::multiset<int> ms(nums1.begin(), nums1.end());
    std::vector<int> result;
    for (int n : nums2) {
        auto it = ms.find(n);
        if (it != ms.end()) {
            result.push_back(n);
            ms.erase(it);
        }
    }
    return result;
}

// -----------------------------------------------------------------------------
// Approach 5: Optimized Hash Map (use smaller array for map)
// -----------------------------------------------------------------------------

std::vector<int> IntersectionHashMapOptimized::intersect(std::vector<int> nums1, std::vector<int> nums2) {
    if (nums1.size() > nums2.size()) std::swap(nums1, nums2);
    std::unordered_map<int, int> counts;
    for (int n : nums1) counts[n]++;
    std::vector<int> result;
    for (int n : nums2) {
        auto it = counts.find(n);
        if (it != counts.end() && it->second > 0) {
            result.push_back(n);
            it->second--;
        }
    }
    return result;
}

// -----------------------------------------------------------------------------
// Approach 6: Frequency Array (0..1000 constraint)
// -----------------------------------------------------------------------------

std::vector<int> IntersectionFrequencyArray::intersect(std::vector<int> nums1, std::vector<int> nums2) {
    std::vector<int> freq(1001, 0);
    for (int n : nums1) freq[n]++;
    std::vector<int> result;
    for (int n : nums2) {
        if (freq[n] > 0) {
            result.push_back(n);
            freq[n]--;
        }
    }
    return result;
}

} // namespace easy
} // namespace leetcode

