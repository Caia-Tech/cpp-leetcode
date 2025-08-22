#pragma once

#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>

namespace leetcode {
namespace easy {

/**
 * Problem 977: Squares of a Sorted Array
 *
 * Given an integer array nums sorted in non-decreasing order, return an array of
 * the squares of each number sorted in non-decreasing order.
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - nums is sorted in non-decreasing order
 */
class SortedSquares {
public:
    /**
     * Approach 1: Square then Sort (Naive)
     *
     * Square each element and sort the array.
     *
     * Reasoning: The simplest method. After squaring, the order may break, so we
     * sort again. Demonstrates baseline approach using STL.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(1) extra (ignoring output vector)
     */
    std::vector<int> squareAndSort(std::vector<int> nums);

    /**
     * Approach 2: Two Pointers from Ends (Optimal)
     *
     * Use two pointers at both ends and fill result from the back.
     *
     * Reasoning: Largest square comes from extreme absolute value. Compare
     * absolute values at both ends and place larger square at the end of result.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n) for result
     */
    std::vector<int> twoPointers(std::vector<int> nums);

    /**
     * Approach 3: Split Negatives and Non-negatives then Merge
     *
     * Find first non-negative index and merge squared negatives and positives.
     *
     * Reasoning: Squared negatives become positive and monotonically decreasing
     * when traversed backwards. Merge like merge-sort.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n) for result
     */
    std::vector<int> splitAndMerge(std::vector<int> nums);

    /**
     * Approach 4: Min-Heap of Squares
     *
     * Push all squared values into a min-heap then extract.
     *
     * Reasoning: Demonstrates priority queue usage. Not optimal but easy.
     *
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    std::vector<int> heapApproach(const std::vector<int>& nums);

    /**
     * Approach 5: Deque Two-Pointer Simulation
     *
     * Load values into deque and pop larger absolute value from either end.
     *
     * Reasoning: Similar to two-pointer but using deque to show container
     * flexibility.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    std::vector<int> dequeApproach(const std::vector<int>& nums);

    /**
     * Approach 6: Counting via Ordered Map
     *
     * Count occurrences of squared values using map then output in order.
     *
     * Reasoning: Uses frequency counting with ordered map which keeps keys
     * sorted automatically.
     *
     * Time Complexity: O(n log n) due to map operations
     * Space Complexity: O(n)
     */
    std::vector<int> countingMap(const std::vector<int>& nums);
};

} // namespace easy
} // namespace leetcode

