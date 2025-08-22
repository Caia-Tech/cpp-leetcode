#pragma once

#include <vector>
#include <stack>
#include <algorithm>

namespace leetcode {
namespace hard {

/**
 * Problem 42: Trapping Rain Water
 * 
 * Given n non-negative integers representing an elevation map where the width of each bar is 1, 
 * compute how much water it can trap after raining.
 * 
 * Constraints:
 * - n == height.length
 * - 1 <= n <= 2 * 10^4
 * - 0 <= height[i] <= 10^5
 */
class TrappingRainWater {
public:
    /**
     * Approach 1: Brute Force
     * 
     * For each element, find max height on left and right.
     * 
     * Reasoning: The most intuitive approach - for each position, water level is
     * determined by the minimum of maximum heights on left and right sides. For
     * each element, scan left to find max height, scan right to find max height,
     * then water trapped = min(left_max, right_max) - current_height. While simple
     * to understand, it's inefficient due to repeated scanning.
     * 
     * Time Complexity: O(n^2) - for each element, scan left and right
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Small arrays, need simple baseline implementation
     * Worst when: Large arrays where repeated scanning becomes expensive
     */
    int trapBruteForce(std::vector<int>& height);

    /**
     * Approach 2: Dynamic Programming
     * 
     * Pre-compute max heights for left and right.
     * 
     * Reasoning: Optimize brute force by pre-computing maximum heights. Two passes:
     * first pass computes left_max[i] = maximum height from index 0 to i,
     * second pass computes right_max[i] = maximum height from index i to n-1.
     * Then for each position, water = min(left_max[i], right_max[i]) - height[i].
     * This eliminates repeated scanning, achieving linear time.
     * 
     * Time Complexity: O(n) - three passes through array
     * Space Complexity: O(n) - two additional arrays for max heights
     * 
     * Best when: Clear DP approach needed, intermediate results useful
     * Worst when: Memory usage is critical and space can be optimized
     */
    int trapDP(std::vector<int>& height);

    /**
     * Approach 3: Stack
     * 
     * Use stack to track bars that can trap water.
     * 
     * Reasoning: This approach calculates water horizontally (layer by layer) rather
     * than vertically. Maintain a stack of bar indices in decreasing height order.
     * When we find a taller bar, we can trap water between the current bar and
     * the bars in the stack. Pop from stack and calculate trapped water using
     * the height difference and width. This naturally handles complex elevation patterns.
     * 
     * Time Complexity: O(n) - each element pushed and popped at most once
     * Space Complexity: O(n) - stack can store up to n indices
     * 
     * Best when: Want to understand horizontal water calculation, complex patterns
     * Worst when: Vertical approach is more intuitive or memory is constrained
     */
    int trapStack(std::vector<int>& height);

    /**
     * Approach 4: Two Pointers
     * 
     * Use two pointers from both ends.
     * 
     * Reasoning: This is the optimal solution combining time and space efficiency.
     * Key insight: we only need to know if left_max < right_max (or vice versa)
     * to determine water level, not the exact values. Use two pointers moving
     * toward each other, tracking max heights seen so far from each side.
     * Move the pointer with smaller max height, ensuring water calculation is always valid.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only using pointers and max variables
     * 
     * Best when: Need optimal space complexity, standard interview solution
     * Worst when: Two-pointer logic is less intuitive than DP approach
     */
    int trapTwoPointers(std::vector<int>& height);

    /**
     * Approach 5: Horizontal Scanning
     * 
     * Calculate water level by level.
     * 
     * Reasoning: Think of filling water level by level from bottom to top.
     * For each height level from 1 to max_height, scan the array and count
     * positions that can hold water at that level (positions where surrounding
     * bars can support water at that height). While intuitive for visualization,
     * this approach is less efficient when max height is large.
     * 
     * Time Complexity: O(n * h) - scan array for each height level
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Visualizing water filling process, max height is small
     * Worst when: Max height is large, making time complexity poor
     */
    int trapHorizontal(std::vector<int>& height);

    /**
     * Approach 6: Morris Traversal Inspired
     * 
     * Single pass with optimized space usage.
     * 
     * Reasoning: This approach takes inspiration from Morris tree traversal
     * technique of avoiding extra space through clever pointer manipulation.
     * Use a single pass with minimal extra variables to track water accumulation.
     * While similar to two-pointer approach, this implementation uses different
     * logic for tracking and accumulating water, potentially with different
     * constant factors or edge case handling.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - constant space with optimized variable usage
     * 
     * Best when: Want space-optimized single-pass solution
     * Worst when: Standard two-pointer approach is clearer and sufficient
     */
    int trapOptimized(std::vector<int>& height);
};

}
}