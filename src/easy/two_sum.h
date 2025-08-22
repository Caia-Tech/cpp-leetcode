#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 1: Two Sum
 * 
 * Given an array of integers nums and an integer target, return indices of the two numbers 
 * such that they add up to target.
 * 
 * You may assume that each input would have exactly one solution, and you may not use the 
 * same element twice.
 * 
 * You can return the answer in any order.
 * 
 * Constraints:
 * - 2 <= nums.length <= 10^4
 * - -10^9 <= nums[i] <= 10^9
 * - -10^9 <= target <= 10^9
 * - Only one valid answer exists.
 */
class TwoSum {
public:
    /**
     * Approach 1: Brute Force
     * 
     * Check every pair of numbers to see if they sum to target.
     * 
     * Reasoning: This is the most intuitive approach - try every possible combination.
     * While inefficient, it's simple to understand and implement. Good starting point
     * for optimization. No additional space needed except for result.
     * 
     * Time Complexity: O(n^2) - nested loops through array
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Array is very small or as educational baseline
     * Worst when: Large arrays due to quadratic time complexity
     */
    std::vector<int> twoSumBruteForce(const std::vector<int>& nums, int target);

    /**
     * Approach 2: Hash Map (One Pass)
     * 
     * Use a hash map to store seen values and their indices.
     * Check if complement exists while iterating.
     * 
     * Reasoning: This is the optimal solution. As we iterate through the array,
     * we check if the complement (target - current_number) exists in our hash map.
     * If it does, we found our pair. If not, we add current number to hash map.
     * This reduces the lookup time from O(n) to O(1) average case.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(n) - hash map can store up to n elements
     * 
     * Best when: Need optimal time complexity, hash operations are fast
     * Worst when: Memory is severely constrained
     */
    std::vector<int> twoSumHashMapOnePass(const std::vector<int>& nums, int target);

    /**
     * Approach 3: Hash Map (Two Pass)
     * 
     * First pass: Build hash map of all values and indices.
     * Second pass: Look for complement in hash map.
     * 
     * Reasoning: This separates the concerns - first we build a complete lookup table,
     * then we search for complements. While less efficient than one-pass, it's
     * easier to understand and debug. Also handles edge cases more explicitly.
     * 
     * Time Complexity: O(n) - two passes through array
     * Space Complexity: O(n) - hash map stores all elements
     * 
     * Best when: Code clarity is prioritized, debugging is important
     * Worst when: Memory usage needs to be minimized
     */
    std::vector<int> twoSumHashMapTwoPass(const std::vector<int>& nums, int target);

    /**
     * Approach 4: Sorted Array with Two Pointers
     * 
     * Sort array with indices, then use two pointers from both ends.
     * 
     * Reasoning: After sorting, we can use two pointers technique. If sum is too small,
     * move left pointer right. If sum is too large, move right pointer left.
     * This works because sorted array allows us to make decisions about which
     * direction to move. We must track original indices during sorting.
     * 
     * Time Complexity: O(n log n) - dominated by sorting
     * Space Complexity: O(n) - for storing index pairs during sort
     * 
     * Best when: Array is already sorted or nearly sorted
     * Worst when: Hash operations are fast and sorting overhead is significant
     */
    std::vector<int> twoSumSortedTwoPointers(const std::vector<int>& nums, int target);

    /**
     * Approach 5: Hash Set with Second Pass
     * 
     * Use hash set to check existence, then find indices.
     * 
     * Reasoning: This approach first checks if a valid pair exists using a hash set
     * for O(1) lookups, then finds the actual indices. Less efficient than hash map
     * approaches but demonstrates separation of "existence check" vs "index finding".
     * 
     * Time Complexity: O(n) - multiple passes through array
     * Space Complexity: O(n) - hash set stores all elements
     * 
     * Best when: Need to verify existence before expensive index operations
     * Worst when: Direct hash map approach is available
     */
    std::vector<int> twoSumHashSet(const std::vector<int>& nums, int target);

    /**
     * Approach 6: Binary Search on Sorted Array
     * 
     * Sort array and use binary search to find complement.
     * 
     * Reasoning: For each element, binary search for its complement in the sorted array.
     * This combines the benefits of sorting (ordered search) with binary search
     * (logarithmic lookup). More complex than hash map but doesn't require hash operations.
     * 
     * Time Complexity: O(n log n) - sorting + n binary searches
     * Space Complexity: O(n) - for storing index pairs during sort
     * 
     * Best when: Hash operations are slow/unavailable, binary search is preferred
     * Worst when: Hash map approach is available and faster
     */
    std::vector<int> twoSumBinarySearch(const std::vector<int>& nums, int target);
};

}
}