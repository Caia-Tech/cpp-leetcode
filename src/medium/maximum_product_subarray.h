#pragma once

#include <vector>
#include <algorithm>
#include <climits>

namespace leetcode {
namespace medium {

/**
 * Problem 152: Maximum Product Subarray
 * 
 * Given an integer array nums, find a contiguous subarray that has the 
 * largest product, and return the product.
 * 
 * The test cases are generated so that the answer will fit in a 32-bit integer.
 * 
 * Constraints:
 * - 1 <= nums.length <= 2 * 10^4
 * - -10 <= nums[i] <= 10
 * - The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class MaximumProductSubarray {
public:
    /**
     * Approach 1: Dynamic Programming with Min/Max Tracking (Optimal)
     * 
     * Track both maximum and minimum products at each position for negative handling.
     * 
     * Reasoning: Unlike maximum sum subarray, negative numbers complicate the problem
     * because a negative number can turn the smallest (most negative) product into
     * the largest positive product. At each position, we need to track both the
     * maximum and minimum product ending at that position. When we encounter a
     * negative number, the previous minimum becomes the new maximum candidate.
     * This is the classic optimal solution with O(n) time and O(1) space.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only track current min/max values
     * 
     * Best when: Want optimal solution, understand negative number impact
     * Worst when: Logic with min/max swapping seems complex
     */
    int maxProductDP(std::vector<int>& nums);

    /**
     * Approach 2: Brute Force with All Subarrays (Baseline)
     * 
     * Check all possible subarrays and find maximum product.
     * 
     * Reasoning: Generate all contiguous subarrays and calculate their products.
     * This approach is straightforward to understand and implement but has
     * quadratic time complexity. Useful for small inputs or as a baseline
     * to verify other approaches. Handles all edge cases naturally since
     * it explicitly checks every possibility.
     * 
     * Time Complexity: O(n²) - nested loops for all subarrays
     * Space Complexity: O(1) - only variables for tracking maximum
     * 
     * Best when: Need simple baseline implementation, small input sizes
     * Worst when: Large inputs, performance requirements
     */
    int maxProductBruteForce(std::vector<int>& nums);

    /**
     * Approach 3: Two-Pass Left-Right Scanning (Clever)
     * 
     * Scan from left and right separately to handle zeros and negative numbers.
     * 
     * Reasoning: Key insight is that the maximum product subarray either doesn't
     * contain any zeros, or starts/ends at a zero boundary. Scan left-to-right
     * building products until hitting zero (reset), then scan right-to-left.
     * The maximum of all products found is the answer. This elegantly handles
     * zeros as natural breakpoints and negative numbers through the bidirectional scan.
     * 
     * Time Complexity: O(n) - two passes through array
     * Space Complexity: O(1) - only tracking variables
     * 
     * Best when: Elegant solution preferred, good intuition for zeros handling
     * Worst when: Two passes seem unnecessary, prefer single-pass algorithms
     */
    int maxProductTwoPass(std::vector<int>& nums);

    /**
     * Approach 4: Kadane's Algorithm Modified (Adapted Classic)
     * 
     * Adapt Kadane's algorithm for products instead of sums.
     * 
     * Reasoning: Traditional Kadane's algorithm finds maximum sum subarray by
     * deciding at each position whether to extend current subarray or start new.
     * For products, we modify this by tracking maximum product ending at current
     * position. However, negative numbers complicate this since we need both
     * max and min tracking. This approach shows how classic algorithms can be
     * adapted for related problems.
     * 
     * Time Complexity: O(n) - single pass with constant work per element
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Want to see Kadane's adaptation, familiar with maximum sum problem
     * Worst when: Min/max tracking adds complexity over original Kadane's
     */
    int maxProductKadane(std::vector<int>& nums);

    /**
     * Approach 5: Prefix/Suffix Product Analysis (Mathematical)
     * 
     * Build prefix and suffix products, handling zeros as reset points.
     * 
     * Reasoning: The maximum product subarray must be either a prefix ending
     * at some position, or a suffix starting at some position, with zeros
     * acting as natural boundaries. Compute cumulative products from left
     * and right, resetting at zeros. The maximum value encountered is the
     * answer. This approach has strong mathematical foundation and handles
     * edge cases elegantly.
     * 
     * Time Complexity: O(n) - single pass with prefix/suffix calculation
     * Space Complexity: O(1) - only tracking current products
     * 
     * Best when: Mathematical approach preferred, understand prefix/suffix concepts
     * Worst when: Conceptually more complex than direct DP approach
     */
    int maxProductPrefixSuffix(std::vector<int>& nums);

    /**
     * Approach 6: Divide and Conquer with Zero Handling (Recursive)
     * 
     * Divide array at zeros and recursively find maximum in each segment.
     * 
     * Reasoning: Zeros naturally divide the problem into independent subproblems.
     * Split array at zeros and recursively solve for each segment. Within each
     * zero-free segment, the maximum product is either the entire segment (if
     * even number of negatives) or the segment with one negative removed from
     * either end. This approach provides good insights into problem structure
     * but has higher complexity than needed.
     * 
     * Time Complexity: O(n log n) - divide and conquer with linear work per level
     * Space Complexity: O(log n) - recursion depth for divide and conquer
     * 
     * Best when: Recursive approach preferred, want to understand problem structure
     * Worst when: Higher complexity than needed, recursion overhead
     */
    int maxProductDivideConquer(std::vector<int>& nums);

private:
    // Helper functions
    int maxProductInSegment(const std::vector<int>& nums, int start, int end);
    int maxProductDCHelper(const std::vector<int>& nums, int start, int end);
    
    // Utility functions
    bool hasZero(const std::vector<int>& nums, int start, int end);
    int findZeroIndex(const std::vector<int>& nums, int start, int end);
};

}
}