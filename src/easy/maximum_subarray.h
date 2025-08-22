#pragma once

#include <vector>
#include <climits>

namespace leetcode {
namespace easy {

/**
 * Problem 53: Maximum Subarray
 * 
 * Given an integer array nums, find the subarray with the largest sum, and return its sum.
 * 
 * Follow up: If you have figured out the O(n) solution, try coding another solution using 
 * the divide and conquer approach, which is more subtle.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 */
class MaximumSubarray {
public:
    /**
     * Approach 1: Brute Force
     * 
     * Check all possible subarrays.
     * 
     * Reasoning: This is the most straightforward approach - examine every possible
     * contiguous subarray and track the maximum sum. While inefficient, it's easy to
     * understand and implement correctly. Useful as a baseline for testing and
     * understanding the problem constraints.
     * 
     * Time Complexity: O(n^2) - nested loops to check all subarrays
     * Space Complexity: O(1) - only tracking current and max sums
     * 
     * Best when: Array size is small (<100 elements), need simple implementation
     * Worst when: Large arrays where O(n^2) becomes prohibitive
     */
    int maxSubArrayBruteForce(std::vector<int>& nums);

    /**
     * Approach 2: Kadane's Algorithm
     * 
     * Dynamic programming approach tracking max ending at each position.
     * 
     * Reasoning: This is the optimal solution. Key insight: at each position, we decide
     * whether to extend the previous subarray or start fresh. If adding current element
     * to previous sum makes it smaller than just the current element, start fresh.
     * This maintains the maximum sum ending at each position, and global max is the answer.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only two variables needed
     * 
     * Best when: Need optimal performance, classic DP problem
     * Worst when: Need to track actual subarray indices (requires modification)
     */
    int maxSubArrayKadane(std::vector<int>& nums);

    /**
     * Approach 3: Divide and Conquer
     * 
     * Divide array and find max in left, right, and crossing subarrays.
     * 
     * Reasoning: The maximum subarray is either entirely in the left half, entirely
     * in the right half, or crosses the midpoint. Recursively solve left and right,
     * then find the maximum crossing sum. This approach demonstrates divide-and-conquer
     * thinking and can be parallelized.
     * 
     * Time Complexity: O(n log n) - T(n) = 2T(n/2) + O(n)
     * Space Complexity: O(log n) - recursion stack depth
     * 
     * Best when: Can parallelize left/right computations, educational purposes
     * Worst when: Single-threaded and O(n) solution is available
     */
    int maxSubArrayDivideConquer(std::vector<int>& nums);

    /**
     * Approach 4: Dynamic Programming with Array
     * 
     * Store max sum ending at each index.
     * 
     * Reasoning: This is the explicit DP version of Kadane's algorithm. Store the
     * maximum sum ending at each position in an array. This makes the DP state
     * transitions more visible and easier to debug. Trade space for clarity.
     * 
     * Time Complexity: O(n) - single pass to fill DP array
     * Space Complexity: O(n) - DP array storage
     * 
     * Best when: Need to debug DP transitions, want explicit state storage
     * Worst when: Memory is constrained and O(1) space solution exists
     */
    int maxSubArrayDP(std::vector<int>& nums);

    /**
     * Approach 5: Prefix Sum
     * 
     * Use prefix sum to calculate subarray sums.
     * 
     * Reasoning: Key insight: sum of subarray[i,j] = prefixSum[j] - prefixSum[i-1].
     * To maximize this, we want maximum prefixSum[j] - minimum prefixSum[k] where k < j.
     * Track minimum prefix sum seen so far and maximum difference at each position.
     * 
     * Time Complexity: O(n) - single pass computing prefix sums
     * Space Complexity: O(1) - only tracking min prefix and max difference
     * 
     * Best when: Natural to think in terms of prefix sums, generalizes to 2D
     * Worst when: Direct Kadane's algorithm is more intuitive
     */
    int maxSubArrayPrefixSum(std::vector<int>& nums);

    /**
     * Approach 6: Modified Kadane with Indices
     * 
     * Track both sum and subarray boundaries.
     * 
     * Reasoning: Extension of Kadane's algorithm that also tracks the start and end
     * indices of the maximum subarray. Useful when you need the actual subarray,
     * not just its sum. Slightly more complex but still O(n) time.
     * 
     * Time Complexity: O(n) - single pass with index tracking
     * Space Complexity: O(1) - few extra variables for index tracking
     * 
     * Best when: Need actual subarray indices, not just the sum
     * Worst when: Only sum is needed and simplicity is preferred
     */
    int maxSubArrayWithIndices(std::vector<int>& nums);

private:
    int maxCrossingSum(std::vector<int>& nums, int left, int mid, int right);
    int divideConquerHelper(std::vector<int>& nums, int left, int right);
};

}
}