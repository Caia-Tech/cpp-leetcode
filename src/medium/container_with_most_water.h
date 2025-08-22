#pragma once

#include <vector>
#include <algorithm>
#include <stack>

namespace leetcode {
namespace medium {

/**
 * Problem 11: Container With Most Water
 * 
 * You are given an integer array height of length n. There are n vertical lines drawn such that 
 * the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * 
 * Find two lines that together with the x-axis form a container such that the container contains the most water.
 * 
 * Return the maximum amount of water a container can store.
 * 
 * Note: You may not slant the container.
 * 
 * Constraints:
 * - n == height.length
 * - 2 <= n <= 10^5
 * - 0 <= height[i] <= 10^4
 */
class ContainerWithMostWater {
public:
    /**
     * Approach 1: Two Pointers (Optimal)
     * 
     * Use two pointers from both ends, move the pointer with smaller height.
     * 
     * Reasoning: This is the optimal O(n) solution. Start with widest possible
     * container (left=0, right=n-1). The water level is determined by the shorter
     * line. Moving the taller line inward won't increase area (width decreases,
     * height limited by shorter line). Moving the shorter line might find a taller
     * line, potentially increasing area. This ensures we don't miss the optimal solution.
     * 
     * Time Complexity: O(n) - single pass with two pointers
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal time complexity, understand two-pointer technique
     * Worst when: Brute force approach is acceptable for small inputs
     */
    int maxAreaTwoPointers(const std::vector<int>& height);

    /**
     * Approach 2: Brute Force
     * 
     * Check all possible pairs of lines and find maximum area.
     * 
     * Reasoning: Straightforward approach that checks every possible container
     * formed by pairs of lines. For each pair (i, j), calculate area as
     * min(height[i], height[j]) * (j - i). Keep track of maximum area found.
     * While this guarantees finding the optimal solution, it's inefficient for
     * large inputs due to quadratic time complexity.
     * 
     * Time Complexity: O(n²) - nested loops checking all pairs
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Small inputs, need simple baseline implementation
     * Worst when: Large inputs where quadratic time is prohibitive
     */
    int maxAreaBruteForce(const std::vector<int>& height);

    /**
     * Approach 3: Divide and Conquer
     * 
     * Recursively find maximum area in left, right, and crossing sections.
     * 
     * Reasoning: Divide array into two halves and consider three cases: maximum
     * area entirely in left half, entirely in right half, or formed by one line
     * from each half. For crossing case, find the tallest lines in each half
     * and compute their area. While this demonstrates divide-and-conquer thinking,
     * it's not more efficient than the two-pointer approach.
     * 
     * Time Complexity: O(n log n) - T(n) = 2T(n/2) + O(n)
     * Space Complexity: O(log n) - recursion call stack
     * 
     * Best when: Educational purposes, demonstrating divide-and-conquer
     * Worst when: Two-pointer O(n) solution is available
     */
    int maxAreaDivideConquer(const std::vector<int>& height);

    /**
     * Approach 4: Stack-Based Approach
     * 
     * Use stack to track potential container boundaries.
     * 
     * Reasoning: Use a stack to maintain lines in decreasing height order.
     * When we find a line taller than stack top, it can form containers with
     * previous lines. Pop from stack and calculate areas with current line.
     * This approach is more complex than needed for this problem but demonstrates
     * stack usage for geometric problems.
     * 
     * Time Complexity: O(n) - each element pushed and popped at most once
     * Space Complexity: O(n) - stack storage in worst case
     * 
     * Best when: Educational purposes, understanding stack applications
     * Worst when: Two-pointer approach is simpler and more direct
     */
    int maxAreaStack(const std::vector<int>& height);

    /**
     * Approach 5: Optimized Brute Force with Early Termination
     * 
     * Brute force with pruning based on maximum possible area.
     * 
     * Reasoning: Enhanced brute force that includes early termination conditions.
     * When checking pairs, if the maximum possible area with remaining elements
     * is less than current best, skip to next iteration. Also skip pairs where
     * one line is much shorter and can't possibly improve the result. Still
     * O(n²) worst case but better average case performance.
     * 
     * Time Complexity: O(n²) worst case, often better in practice
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Brute force is acceptable but want some optimization
     * Worst when: Optimal O(n) solution is required
     */
    int maxAreaOptimizedBruteForce(const std::vector<int>& height);

    /**
     * Approach 6: Binary Search on Height
     * 
     * For each height, use binary search to find optimal partner.
     * 
     * Reasoning: For each line, try to find the farthest line of at least the
     * same height (to maximize both width and effective height). Use binary search
     * or scanning techniques to find optimal partners. While creative, this
     * approach is more complex and not more efficient than two-pointers for
     * this specific problem structure.
     * 
     * Time Complexity: O(n²) in worst case, varies with height distribution
     * Space Complexity: O(n) - for sorting or preprocessing
     * 
     * Best when: Educational purposes, exploring different search strategies
     * Worst when: Two-pointer solution is simpler and more efficient
     */
    int maxAreaBinarySearch(const std::vector<int>& height);

private:
    int maxAreaHelper(const std::vector<int>& height, int left, int right);
    int findMaxCrossingArea(const std::vector<int>& height, int left, int mid, int right);
};

}
}