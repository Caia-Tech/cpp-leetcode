#pragma once

#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 31: Next Permutation
 * 
 * A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
 * The next permutation of an array of integers is the next lexicographically greater permutation of its integer.
 * More formally, if all the permutations of the array are sorted in one container according to their 
 * lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container.
 * 
 * If such an arrangement is not possible, the array must be rearranged as the lowest possible order 
 * (i.e., sorted in ascending order).
 * 
 * The replacement must be in place and use only constant extra memory.
 * 
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 0 <= nums[i] <= 100
 */
class NextPermutation {
public:
    /**
     * Approach 1: Standard Algorithm (Optimal)
     * 
     * Find rightmost ascending pair, find next larger element, swap, reverse suffix.
     * 
     * Reasoning: This is the optimal O(n) algorithm. The next lexicographical permutation
     * can be found by: 1) Find the rightmost character that is smaller than its next
     * character (pivot), 2) Find the smallest character to the right of pivot that's
     * larger than pivot, 3) Swap them, 4) Reverse the suffix after original pivot position.
     * If no pivot exists, array is in descending order (largest permutation), so reverse entire array.
     * 
     * Time Complexity: O(n) - single pass to find pivot, single pass to find successor, O(n) reverse
     * Space Complexity: O(1) - only using constant extra space for swaps
     * 
     * Best when: Need optimal in-place solution, understand lexicographical ordering
     * Worst when: Want to understand all permutations generation (this gives only next one)
     */
    void nextPermutationStandard(std::vector<int>& nums);

    /**
     * Approach 2: STL next_permutation
     * 
     * Use built-in STL next_permutation function.
     * 
     * Reasoning: C++ STL provides std::next_permutation which implements the same
     * algorithm as approach 1 but is highly optimized and tested. While this gives
     * the correct result, it may not be allowed in interviews where manual
     * implementation is expected. Useful for comparison and understanding STL.
     * 
     * Time Complexity: O(n) - STL implementation of the standard algorithm
     * Space Complexity: O(1) - in-place operation
     * 
     * Best when: STL usage allowed, need production-ready solution
     * Worst when: Need to implement algorithm manually, interview restrictions
     */
    void nextPermutationSTL(std::vector<int>& nums);

    /**
     * Approach 3: Recursive Generation with Position Tracking
     * 
     * Generate next permutation using recursive position-based approach.
     * 
     * Reasoning: Recursively determine what the next permutation should be by
     * analyzing position by position from right to left. At each position, try to
     * increment the current digit to next available value, carrying over when needed.
     * While this demonstrates recursive thinking, it's more complex than the standard
     * algorithm and doesn't improve efficiency.
     * 
     * Time Complexity: O(n²) worst case - recursive calls with linear work each
     * Space Complexity: O(n) - recursion call stack depth
     * 
     * Best when: Want recursive approach, educational understanding of permutation structure
     * Worst when: Optimal O(n) iterative solution is preferred
     */
    void nextPermutationRecursive(std::vector<int>& nums);

    /**
     * Approach 4: Digit-by-Digit Increment with Carry
     * 
     * Treat array like a number and increment with carry propagation.
     * 
     * Reasoning: Think of the array as a variable-base number system where each
     * position has constraints based on available values. Start from rightmost
     * position and try to increment, carrying over to next position when current
     * position reaches maximum. This approach makes the "increment" operation
     * very explicit but is more complex than standard algorithm.
     * 
     * Time Complexity: O(n²) worst case - may need to scan available values at each position
     * Space Complexity: O(n) - tracking available values at each position
     * 
     * Best when: Want to understand permutation as number increment, educational purposes
     * Worst when: Standard algorithm is more efficient and clearer
     */
    void nextPermutationDigitIncrement(std::vector<int>& nums);

    /**
     * Approach 5: Two-Pointer with Optimization
     * 
     * Use two pointers to find pivot and successor efficiently.
     * 
     * Reasoning: Optimized version of standard algorithm using two-pointer technique.
     * Use one pointer to find pivot from right, another to find the successor.
     * Include optimizations like early termination and efficient swapping. While
     * asymptotically the same as standard algorithm, it may have better constant factors.
     * 
     * Time Complexity: O(n) - optimized single pass operations
     * Space Complexity: O(1) - constant space with pointer variables
     * 
     * Best when: Want optimized implementation, understand two-pointer patterns
     * Worst when: Standard algorithm clarity is more important than micro-optimizations
     */
    void nextPermutationTwoPointers(std::vector<int>& nums);

    /**
     * Approach 6: Segment-Based Processing
     * 
     * Process array in segments to find and fix the permutation.
     * 
     * Reasoning: Divide array into segments and process each segment based on its
     * permutation properties. Identify ascending, descending, and mixed segments,
     * then apply appropriate transformations. While this provides insight into
     * array structure, it's more complex than needed for this specific problem.
     * 
     * Time Complexity: O(n) - segment identification and processing
     * Space Complexity: O(1) - constant extra space for segment tracking
     * 
     * Best when: Want to understand array segment properties, educational analysis
     * Worst when: Direct standard algorithm is simpler and more straightforward
     */
    void nextPermutationSegmentBased(std::vector<int>& nums);

private:
    // Helper functions
    bool nextPermutationRecursiveHelper(std::vector<int>& nums, int pos);
    int findNextLarger(const std::vector<int>& nums, int start, int target);
    void reverseRange(std::vector<int>& nums, int start, int end);
    bool canIncrementAtPosition(std::vector<int>& nums, int pos);
    void identifySegments(const std::vector<int>& nums, std::vector<int>& segmentTypes);
    
    // Constants for segment types
    static const int ASCENDING = 1;
    static const int DESCENDING = 2;
    static const int MIXED = 3;
};

}
}