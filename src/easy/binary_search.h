#pragma once

#include <vector>
#include <algorithm>
#include <functional>

namespace leetcode {
namespace easy {

/**
 * Problem 704: Binary Search
 * 
 * Given an array of integers nums which is sorted in ascending order, and an integer target,
 * write a function to search target in nums. If target exists, return its index. 
 * Otherwise, return -1.
 * 
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 < nums[i], target < 10^4
 * - All the integers in nums are unique
 * - nums is sorted in ascending order
 */
class BinarySearch {
public:
    /**
     * Approach 1: Classic Binary Search (Optimal)
     * 
     * Standard iterative binary search implementation.
     * 
     * Reasoning: This is the classic binary search algorithm. We maintain
     * left and right pointers and repeatedly divide the search space in half.
     * Compare middle element with target: if equal, found; if less, search
     * right half; if greater, search left half. This achieves O(log n) by
     * eliminating half of remaining elements each iteration. Using left <= right
     * ensures we check all elements including when left == right.
     * 
     * Time Complexity: O(log n) - halve search space each iteration
     * Space Complexity: O(1) - only using pointers
     * 
     * Best when: Standard solution needed, iterative approach preferred
     * Worst when: Never - this is the optimal approach
     */
    int searchClassic(std::vector<int>& nums, int target);

    /**
     * Approach 2: Recursive Binary Search
     * 
     * Recursive implementation of binary search.
     * 
     * Reasoning: Implements the same divide-and-conquer logic recursively.
     * More elegant and mirrors the mathematical definition of binary search.
     * Each recursive call handles half the remaining array. Base case is
     * when search space is empty (left > right). While elegant, uses O(log n)
     * stack space due to recursion depth.
     * 
     * Time Complexity: O(log n) - halve search space each recursion
     * Space Complexity: O(log n) - recursion stack depth
     * 
     * Best when: Recursive thinking preferred, teaching recursion
     * Worst when: Stack space is limited, very large arrays
     */
    int searchRecursive(std::vector<int>& nums, int target);

    /**
     * Approach 3: Binary Search with Bit Manipulation
     * 
     * Use bit manipulation to calculate mid point.
     * 
     * Reasoning: Instead of (left + right) / 2 which can overflow for large
     * values, we use left + ((right - left) >> 1). The bit shift >> 1 is
     * equivalent to division by 2 but potentially faster. This approach also
     * demonstrates overflow-safe midpoint calculation, important for production
     * code with large indices.
     * 
     * Time Complexity: O(log n) - same as classic binary search
     * Space Complexity: O(1) - only using pointers
     * 
     * Best when: Avoiding overflow, micro-optimization needed
     * Worst when: Readability is more important than micro-optimization
     */
    int searchBitManipulation(std::vector<int>& nums, int target);

    /**
     * Approach 4: Lower Bound Binary Search
     * 
     * Use STL-style lower bound approach.
     * 
     * Reasoning: Implements binary search using the lower_bound pattern from STL.
     * Finds the first position where target could be inserted to maintain order.
     * If element at that position equals target, we found it. This approach
     * is more general and can be adapted for finding insertion points or
     * handling duplicates (though this problem has unique elements).
     * 
     * Time Complexity: O(log n) - binary search pattern
     * Space Complexity: O(1) - only using pointers
     * 
     * Best when: Consistency with STL algorithms, need insertion point
     * Worst when: Simple search is all that's needed
     */
    int searchLowerBound(std::vector<int>& nums, int target);

    /**
     * Approach 5: Exponential Search then Binary Search
     * 
     * Find range using exponential search, then binary search.
     * 
     * Reasoning: First find a range where target might exist using exponential
     * search (doubling index: 1, 2, 4, 8...). Once we find a range [i/2, i]
     * where target might be, perform binary search in that range. This is
     * particularly efficient when target is near the beginning of a very large
     * array, as we quickly narrow down the range.
     * 
     * Time Complexity: O(log n) - exponential + binary search
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: Target likely near beginning, unbounded arrays
     * Worst when: Target near end (does extra work)
     */
    int searchExponential(std::vector<int>& nums, int target);

    /**
     * Approach 6: Interpolation Search
     * 
     * Use interpolation to guess target position.
     * 
     * Reasoning: Instead of always checking middle, estimate target's position
     * based on its value relative to range endpoints. If values are uniformly
     * distributed, this can find target in O(log log n) average case. For
     * example, searching for 25 in [0,100] would check around position 25%
     * rather than 50%. Falls back to O(n) worst case for skewed distributions.
     * 
     * Time Complexity: O(log log n) average, O(n) worst case
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: Uniformly distributed data, phone book-like searches
     * Worst when: Skewed distributions, need guaranteed O(log n)
     */
    int searchInterpolation(std::vector<int>& nums, int target);

private:
    // Helper for recursive approach
    int searchRecursiveHelper(std::vector<int>& nums, int target, int left, int right);
    
    // Helper for exponential search
    int binarySearchRange(std::vector<int>& nums, int target, int left, int right);
};

}  // namespace easy
}  // namespace leetcode