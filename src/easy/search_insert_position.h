#pragma once

#include <vector>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 35: Search Insert Position
 * 
 * Given a sorted array of distinct integers and a target value, return the index if the target is found. 
 * If not, return the index where it would be if it were inserted in order.
 * 
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - nums contains distinct values sorted in ascending order.
 * - -10^4 <= target <= 10^4
 */
class SearchInsertPosition {
public:
    /**
     * Approach 1: Binary Search (Optimal)
     * 
     * Use standard binary search to find target or insertion position.
     * 
     * Reasoning: This is the optimal solution that meets the O(log n) requirement.
     * Standard binary search with a twist - when target is not found, the left
     * pointer will be at the correct insertion position. The invariant maintained
     * is that left points to the first position where target should be inserted,
     * and right points to the last position where target could be. When left > right,
     * left is the insertion position.
     * 
     * Time Complexity: O(log n) - binary search through sorted array
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal logarithmic time, array is sorted
     * Worst when: Array is not sorted (algorithm would be incorrect)
     */
    int searchInsertBinarySearch(const std::vector<int>& nums, int target);

    /**
     * Approach 2: Linear Search (Brute Force)
     * 
     * Scan array linearly to find target or insertion position.
     * 
     * Reasoning: Simple linear scan approach. Find the first element greater than
     * or equal to target - this is either the target itself (if found) or the
     * insertion position. While this doesn't meet the O(log n) requirement, it's
     * simple to understand and implement. Can be useful for very small arrays
     * where binary search overhead isn't worth it.
     * 
     * Time Complexity: O(n) - linear scan through array
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Very small arrays, simplicity is prioritized
     * Worst when: Need to meet O(log n) requirement or array is large
     */
    int searchInsertLinear(const std::vector<int>& nums, int target);

    /**
     * Approach 3: STL lower_bound
     * 
     * Use STL's lower_bound function for binary search.
     * 
     * Reasoning: STL's lower_bound() returns iterator to first element not less
     * than target, which is exactly what we need for insertion position. This
     * is highly optimized and handles all edge cases correctly. While it meets
     * the complexity requirement, it may not be allowed in interviews where
     * manual implementation is expected.
     * 
     * Time Complexity: O(log n) - STL binary search implementation
     * Space Complexity: O(1) - built-in function
     * 
     * Best when: STL usage allowed, need robust implementation
     * Worst when: Need to implement binary search logic manually
     */
    int searchInsertSTL(const std::vector<int>& nums, int target);

    /**
     * Approach 4: Recursive Binary Search
     * 
     * Implement binary search recursively.
     * 
     * Reasoning: Recursive implementation of binary search. While achieving the
     * same O(log n) time complexity, this approach uses the call stack for
     * recursion. Each recursive call reduces the search space by half. The
     * base case handles when the search space is exhausted, returning the
     * correct insertion position.
     * 
     * Time Complexity: O(log n) - binary search with recursion
     * Space Complexity: O(log n) - recursion call stack
     * 
     * Best when: Recursive approach is preferred, educational purposes
     * Worst when: Stack space is limited or iterative approach is simpler
     */
    int searchInsertRecursive(const std::vector<int>& nums, int target);

    /**
     * Approach 5: Modified Binary Search with Early Return
     * 
     * Binary search with optimized early termination conditions.
     * 
     * Reasoning: Enhanced binary search with early termination optimizations.
     * Check edge cases first (target smaller than first element, larger than
     * last element) to avoid unnecessary binary search. Also includes exact
     * match detection with immediate return. While maintaining O(log n) worst
     * case, this can improve average case performance.
     * 
     * Time Complexity: O(log n) - worst case, often better in practice
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Want optimized average case performance
     * Worst when: Code simplicity is more important than micro-optimizations
     */
    int searchInsertOptimized(const std::vector<int>& nums, int target);

    /**
     * Approach 6: Interpolation Search Inspired
     * 
     * Use interpolation search concept for better average case.
     * 
     * Reasoning: Instead of always dividing search space in half, estimate the
     * target position based on value distribution (interpolation). For uniformly
     * distributed data, this can achieve O(log log n) average case. However,
     * worst case is still O(n) when data is not uniformly distributed. Falls
     * back to binary search behavior for safety.
     * 
     * Time Complexity: O(log log n) average case, O(n) worst case
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Data is uniformly distributed, need better average case
     * Worst when: Data distribution is unknown or guarantee O(log n) needed
     */
    int searchInsertInterpolation(const std::vector<int>& nums, int target);

private:
    int binarySearchRecursive(const std::vector<int>& nums, int target, int left, int right);
};

}
}