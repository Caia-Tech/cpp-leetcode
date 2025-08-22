#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>

namespace leetcode {
namespace medium {

/**
 * Problem 18: 4Sum
 * 
 * Given an array nums of n integers, return an array of all the unique quadruplets 
 * [nums[a], nums[b], nums[c], nums[d]] such that:
 * - 0 <= a, b, c, d < n
 * - a, b, c, d are all distinct.
 * - nums[a] + nums[b] + nums[c] + nums[d] == target
 * 
 * You may return the answer in any order.
 * 
 * Constraints:
 * - 1 <= nums.length <= 200
 * - -10^9 <= nums[i] <= 10^9
 * - -10^9 <= target <= 10^9
 */
class FourSum {
public:
    /**
     * Approach 1: Two Pointers with Two Fixed Elements (Optimal)
     * 
     * Fix first two elements, then use two pointers for remaining two.
     * 
     * Reasoning: This is the optimal approach, extending 3Sum technique. Sort array first,
     * then fix two elements with nested loops. For remaining elements, use two pointers
     * from both ends to find pairs that sum to (target - fixed_sum). Skip duplicates
     * at all levels to avoid duplicate quadruplets. This approach has the best time
     * complexity while being relatively straightforward to implement.
     * 
     * Time Complexity: O(n³) - two nested loops + two pointers
     * Space Complexity: O(1) - excluding result storage, only using pointers
     * 
     * Best when: Need optimal time complexity, extending 3Sum knowledge
     * Worst when: Hash-based approach is preferred for different constant factors
     */
    std::vector<std::vector<int>> fourSumTwoPointers(std::vector<int>& nums, int target);

    /**
     * Approach 2: Hash Map for Pair Sums
     * 
     * Use hash map to store all possible pair sums and their indices.
     * 
     * Reasoning: Generate all possible pairs and store their sums with indices in
     * a hash map. For each pair (i,j), look for complement pairs (k,l) such that
     * pair_sum + complement_sum = target and all indices are distinct. This approach
     * trades space for potential time improvements in average case, though worst
     * case is still O(n³) due to duplicate handling.
     * 
     * Time Complexity: O(n²) average case, O(n³) worst case with many duplicates
     * Space Complexity: O(n²) - hash map storing all pair sums
     * 
     * Best when: Want hash-based approach, average case optimization
     * Worst when: Memory usage is critical or many duplicate sums exist
     */
    std::vector<std::vector<int>> fourSumHashMap(std::vector<int>& nums, int target);

    /**
     * Approach 3: Brute Force with Set for Deduplication
     * 
     * Check all possible quadruplets and use set to handle duplicates.
     * 
     * Reasoning: Four nested loops to check all possible quadruplets. Use set to
     * automatically handle duplicate removal by storing sorted quadruplets. While
     * this is the most straightforward approach and guarantees correctness, it's
     * inefficient with O(n⁴) time complexity. Useful as baseline for testing.
     * 
     * Time Complexity: O(n⁴) - four nested loops
     * Space Complexity: O(k) - set storage for unique quadruplets
     * 
     * Best when: Small arrays, need simple baseline implementation
     * Worst when: Array size is large, performance is important
     */
    std::vector<std::vector<int>> fourSumBruteForce(std::vector<int>& nums, int target);

    /**
     * Approach 4: Recursive Decomposition
     * 
     * Recursively reduce 4Sum to 3Sum, 3Sum to 2Sum, etc.
     * 
     * Reasoning: Generic recursive approach that reduces kSum to (k-1)Sum problem.
     * Base case is 2Sum solved with two pointers. This demonstrates how to solve
     * the general kSum problem systematically. While elegant, it has recursion
     * overhead and doesn't improve asymptotic complexity for 4Sum specifically.
     * 
     * Time Complexity: O(n³) - same as two-pointer approach but with recursion
     * Space Complexity: O(k) - recursion stack depth for k levels
     * 
     * Best when: Need general kSum solution, recursive approach preferred
     * Worst when: Direct 4Sum implementation is simpler for fixed k=4
     */
    std::vector<std::vector<int>> fourSumRecursive(std::vector<int>& nums, int target);

    /**
     * Approach 5: Early Termination with Optimizations
     * 
     * Two pointers approach with aggressive pruning and early termination.
     * 
     * Reasoning: Enhanced two-pointer approach with multiple optimizations:
     * skip when minimum possible sum > target, skip when maximum possible sum < target,
     * break early when conditions can't be satisfied. These optimizations significantly
     * improve average case performance while maintaining O(n³) worst case complexity.
     * 
     * Time Complexity: O(n³) worst case, much better average case
     * Space Complexity: O(1) - excluding result storage
     * 
     * Best when: Want maximum practical performance, willing to add complexity
     * Worst when: Code simplicity is more important than optimization
     */
    std::vector<std::vector<int>> fourSumOptimized(std::vector<int>& nums, int target);

    /**
     * Approach 6: Divide and Conquer with Merge
     * 
     * Divide array and find quadruplets crossing the divide point.
     * 
     * Reasoning: Divide array in half and consider quadruplets formed by:
     * all from left half, all from right half, or crossing the midpoint.
     * For crossing case, enumerate pairs from each half and find matching pairs.
     * While this demonstrates divide-and-conquer thinking, it's not more efficient
     * than direct approaches for this problem.
     * 
     * Time Complexity: O(n³ log n) - recursion with O(n²) merge work
     * Space Complexity: O(n² log n) - recursion stack and temporary storage
     * 
     * Best when: Educational purposes, understanding divide-and-conquer
     * Worst when: Direct approaches are more efficient and simpler
     */
    std::vector<std::vector<int>> fourSumDivideConquer(std::vector<int>& nums, int target);

private:
    // Helper functions
    std::vector<std::vector<int>> kSum(std::vector<int>& nums, int target, int k, int startIndex);
    std::vector<std::vector<int>> twoSum(std::vector<int>& nums, int target, int startIndex);
    void divideFourSum(std::vector<int>& nums, int target, int left, int right, 
                       std::vector<std::vector<int>>& result);
    std::string vectorToString(const std::vector<int>& vec);
    
    struct PairSum {
        long long sum;
        int i, j;
        PairSum(long long s, int idx1, int idx2) : sum(s), i(idx1), j(idx2) {}
    };
};

}
}