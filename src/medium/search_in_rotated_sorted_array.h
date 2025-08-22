#pragma once

#include <vector>

namespace leetcode {
namespace medium {

/**
 * Problem 33: Search in Rotated Sorted Array
 * 
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at some pivot index k 
 * (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
 * 
 * Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Constraints:
 * - 1 <= nums.length <= 5000
 * - -10^4 <= nums[i] <= 10^4
 * - All values of nums are unique.
 * - nums is an ascending array that is possibly rotated.
 * - -10^4 <= target <= 10^4
 */
class SearchInRotatedSortedArray {
public:
    /**
     * Approach 1: Modified Binary Search (Optimal)
     * 
     * Use binary search with rotation-aware comparison logic.
     * 
     * Reasoning: This is the optimal O(log n) solution. Key insight: in a rotated
     * sorted array, at least one half is always properly sorted. Use binary search
     * but modify the comparison logic: determine which half is sorted, then check
     * if target lies in the sorted half. If yes, search that half; otherwise,
     * search the other half. This maintains binary search efficiency while handling rotation.
     * 
     * Time Complexity: O(log n) - binary search with constant-time comparisons
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal logarithmic time, understand binary search variations
     * Worst when: Array is not rotated (though algorithm still works correctly)
     */
    int searchModifiedBinarySearch(const std::vector<int>& nums, int target);

    /**
     * Approach 2: Find Pivot then Binary Search
     * 
     * First find rotation pivot, then perform standard binary search on appropriate half.
     * 
     * Reasoning: Two-phase approach: first find the rotation point using binary search
     * (smallest element), then determine which half contains target and perform
     * standard binary search on that half. While conceptually clear, this requires
     * two binary search passes instead of one integrated pass.
     * 
     * Time Complexity: O(log n) - two binary search passes
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Want clear separation of concerns, easier to understand and debug
     * Worst when: Single-pass solution is preferred for efficiency
     */
    int searchFindPivotFirst(const std::vector<int>& nums, int target);

    /**
     * Approach 3: Recursive Binary Search
     * 
     * Recursively apply modified binary search with rotation handling.
     * 
     * Reasoning: Recursive version of approach 1. At each recursive call, determine
     * which half is sorted and recurse accordingly. Base cases handle target found
     * or search space exhausted. While elegant, it uses call stack space that the
     * iterative version avoids.
     * 
     * Time Complexity: O(log n) - recursive binary search
     * Space Complexity: O(log n) - recursion call stack
     * 
     * Best when: Recursive approach is preferred, educational recursion understanding
     * Worst when: Stack space is limited or iterative approach is simpler
     */
    int searchRecursive(const std::vector<int>& nums, int target);

    /**
     * Approach 4: Linear Search (Baseline)
     * 
     * Simple linear scan through array to find target.
     * 
     * Reasoning: Straightforward O(n) approach that ignores the sorted property.
     * While this doesn't meet the O(log n) requirement, it's useful as a baseline
     * for correctness testing and comparison. Demonstrates the performance difference
     * between linear and logarithmic approaches.
     * 
     * Time Complexity: O(n) - linear scan through array
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Very small arrays, need simple baseline implementation
     * Worst when: Need to meet O(log n) requirement or array is large
     */
    int searchLinear(const std::vector<int>& nums, int target);

    /**
     * Approach 5: Unrotate then Binary Search
     * 
     * Restore original order by finding pivot and conceptually unrotate for search.
     * 
     * Reasoning: Find rotation pivot, then map indices to simulate searching in
     * the unrotated array using standard binary search. This approach doesn't
     * actually modify the array but maps indices during comparison. Demonstrates
     * how to work with rotated data without physical transformation.
     * 
     * Time Complexity: O(log n) - binary search after O(log n) pivot finding
     * Space Complexity: O(1) - constant extra space for index mapping
     * 
     * Best when: Want to understand index mapping, conceptual unrotation
     * Worst when: Direct rotation-aware search is more straightforward
     */
    int searchUnrotate(const std::vector<int>& nums, int target);

    /**
     * Approach 6: Three-Way Partitioning Analysis
     * 
     * Analyze array as three potential sections and search accordingly.
     * 
     * Reasoning: Consider rotated array as having up to three sections: elements
     * greater than rotation point, rotation point area, elements less than rotation
     * point. Analyze target's relationship to these sections to determine search
     * strategy. While this provides deep insight into rotation structure, it's
     * more complex than needed.
     * 
     * Time Complexity: O(log n) - binary search with enhanced analysis
     * Space Complexity: O(1) - constant space for section analysis
     * 
     * Best when: Want deep understanding of rotation structure, educational analysis
     * Worst when: Simpler rotation-aware binary search is sufficient
     */
    int searchThreeWayPartition(const std::vector<int>& nums, int target);

private:
    // Helper functions
    int findPivot(const std::vector<int>& nums);
    int binarySearch(const std::vector<int>& nums, int left, int right, int target);
    int searchRecursiveHelper(const std::vector<int>& nums, int left, int right, int target);
    int mapIndex(int index, int pivot, int n);
    bool isInSortedRange(int target, int start, int end);
    void analyzeRotationStructure(const std::vector<int>& nums, int& section1, int& section2, int& section3);
};

}
}