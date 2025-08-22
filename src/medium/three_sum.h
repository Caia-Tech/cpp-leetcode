#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 15: 3Sum
 * 
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] 
 * such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * 
 * Notice that the solution set must not contain duplicate triplets.
 * 
 * Constraints:
 * - 3 <= nums.length <= 3000
 * - -10^5 <= nums[i] <= 10^5
 */
class ThreeSum {
public:
    /**
     * Approach 1: Brute Force with Set
     * 
     * Check all triplets and use set to avoid duplicates.
     * 
     * Reasoning: The most straightforward approach - check every possible triplet
     * using three nested loops. Use a set to store triplets and automatically
     * handle duplicates. While this guarantees correctness, it's highly inefficient
     * with cubic time complexity. Useful as a baseline for correctness testing
     * but not practical for large inputs.
     * 
     * Time Complexity: O(n^3) - three nested loops through array
     * Space Complexity: O(n) - set storage for result triplets
     * 
     * Best when: Small arrays (<50 elements), need simple baseline implementation
     * Worst when: Large arrays, performance is important
     */
    std::vector<std::vector<int>> threeSumBruteForce(std::vector<int>& nums);

    /**
     * Approach 2: Sort + Two Pointers
     * 
     * Fix one element and use two pointers for the rest.
     * 
     * Reasoning: This is the optimal and most elegant solution. Sort the array first,
     * then for each element, use two pointers to find pairs that sum to the negative
     * of current element. Sorting enables duplicate skipping and efficient two-pointer
     * technique. The two pointers converge based on sum comparison, avoiding the need
     * for hash lookups. This is the standard interview solution.
     * 
     * Time Complexity: O(n^2) - O(n log n) sort + O(n^2) two-pointer search
     * Space Complexity: O(1) - only using pointers, excluding output array
     * 
     * Best when: Standard interview solution, need optimal time complexity
     * Worst when: Cannot modify input array (sorting required)
     */
    std::vector<std::vector<int>> threeSumTwoPointers(std::vector<int>& nums);

    /**
     * Approach 3: Hash Set
     * 
     * Use hash set to find the third element.
     * 
     * Reasoning: Fix two elements with nested loops, then use hash set to check
     * if the required third element (-(first + second)) exists. This reduces the
     * third loop to O(1) hash lookup. Still requires sorting for duplicate handling
     * or careful duplicate management. While achieving O(n^2) time, it uses more
     * space than the two-pointer approach.
     * 
     * Time Complexity: O(n^2) - two nested loops with O(1) hash lookups
     * Space Complexity: O(n) - hash set storage
     * 
     * Best when: Two-pointer technique is less intuitive
     * Worst when: Memory usage is critical and two-pointer approach available
     */
    std::vector<std::vector<int>> threeSumHashSet(std::vector<int>& nums);

    /**
     * Approach 4: No-Sort Hash Map
     * 
     * Use hash map without sorting.
     * 
     * Reasoning: Attempt to solve without sorting by using hash map for lookups.
     * For each pair of elements, check if the complement exists. The main challenge
     * is handling duplicates without sorting - requires careful index management
     * and additional logic to avoid using the same element twice and prevent
     * duplicate triplets. More complex than sorted approaches.
     * 
     * Time Complexity: O(n^2) - nested loops with hash operations
     * Space Complexity: O(n) - hash map storage
     * 
     * Best when: Input cannot be modified (no sorting allowed)
     * Worst when: Duplicate handling complexity outweighs benefits
     */
    std::vector<std::vector<int>> threeSumHashMap(std::vector<int>& nums);

    /**
     * Approach 5: Binary Search
     * 
     * Fix two elements and binary search for third.
     * 
     * Reasoning: After sorting, fix two elements and binary search for the complement
     * in the remaining portion of array. While this achieves the goal, it's less
     * efficient than two-pointers due to the logarithmic factor from binary search.
     * Each binary search operation takes O(log n), making overall complexity worse
     * than the O(n^2) two-pointer approach.
     * 
     * Time Complexity: O(n^2 log n) - n^2 pairs, each with O(log n) binary search
     * Space Complexity: O(1) - excluding output, only using constant extra space
     * 
     * Best when: Educational purposes, demonstrating binary search application
     * Worst when: Optimal performance needed (two-pointers is better)
     */
    std::vector<std::vector<int>> threeSumBinarySearch(std::vector<int>& nums);

    /**
     * Approach 6: Early Termination Optimization
     * 
     * Two pointers with early termination conditions.
     * 
     * Reasoning: Enhanced version of the two-pointer approach with optimizations:
     * early termination when current element is positive (since array is sorted,
     * no negative sum possible), skip when current element would create impossible
     * sums, and other pruning conditions. These optimizations reduce the average
     * case runtime significantly while maintaining worst-case O(n^2).
     * 
     * Time Complexity: O(n^2) - same worst case, but much better average case
     * Space Complexity: O(1) - excluding output array
     * 
     * Best when: Need maximum performance, large arrays with many edge cases
     * Worst when: Code simplicity is more important than micro-optimizations
     */
    std::vector<std::vector<int>> threeSumOptimized(std::vector<int>& nums);

private:
    std::string tripletToString(int a, int b, int c);
};

}
}