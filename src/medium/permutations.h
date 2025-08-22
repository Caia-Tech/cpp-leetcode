#pragma once

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <numeric>

namespace leetcode {
namespace medium {

/**
 * Problem 46: Permutations
 * 
 * Given an array nums of distinct integers, return all the possible permutations.
 * You can return the answer in any order.
 * 
 * Constraints:
 * - 1 <= nums.length <= 6
 * - -10 <= nums[i] <= 10
 * - All the integers of nums are unique.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class Permutations {
public:
    /**
     * Approach 1: Backtracking with Boolean Visited Array (Classic)
     * 
     * Generate permutations by exploring all possibilities with backtracking.
     * 
     * Reasoning: This is the most intuitive and widely-used approach for generating
     * permutations. Use a boolean array to track which elements are already used
     * in the current permutation. At each position, try all unused elements,
     * recursively build the rest, then backtrack by unmarking the element.
     * The key insight is that permutations are ordered arrangements, so we need
     * to consider all positions for each element.
     * 
     * Time Complexity: O(n! * n) - n! permutations, each taking O(n) to construct
     * Space Complexity: O(n) - recursion depth + visited array (excluding result storage)
     * 
     * Best when: Need intuitive, easy-to-understand solution, good for learning
     * Worst when: Want to minimize space usage or avoid extra boolean array
     */
    std::vector<std::vector<int>> permuteBacktracking(std::vector<int>& nums);

    /**
     * Approach 2: Backtracking with In-Place Swapping (Space Optimized)
     * 
     * Generate permutations by swapping elements to avoid extra visited array.
     * 
     * Reasoning: Instead of maintaining a separate visited array, use swapping
     * to bring unused elements to the front. For each recursive call at position i,
     * swap nums[i] with each element from position i to end, recurse, then swap back.
     * This approach modifies the input array in-place, making it more space-efficient.
     * The swap-recurse-swap pattern ensures all permutations are generated.
     * 
     * Time Complexity: O(n! * n) - n! permutations, each taking O(n) to construct
     * Space Complexity: O(n) - only recursion depth (excluding result storage)
     * 
     * Best when: Want to minimize extra space usage, prefer in-place algorithms
     * Worst when: Input array modification is not allowed, swapping logic seems complex
     */
    std::vector<std::vector<int>> permuteSwapping(std::vector<int>& nums);

    /**
     * Approach 3: Iterative using Next Permutation (STL-based)
     * 
     * Generate all permutations using std::next_permutation algorithm.
     * 
     * Reasoning: Start with sorted array and use std::next_permutation to generate
     * all permutations in lexicographic order. This approach leverages the STL's
     * optimized implementation of the next permutation algorithm, which works by
     * finding the rightmost character that is smaller than its next character,
     * then rearranging the suffix. Simple to implement but requires understanding
     * of lexicographic ordering.
     * 
     * Time Complexity: O(n! * n) - n! calls to next_permutation, each O(n) on average
     * Space Complexity: O(1) - no extra space beyond input modification
     * 
     * Best when: Want simple, STL-based solution, need lexicographic order
     * Worst when: Don't want to modify input array, avoid STL algorithms
     */
    std::vector<std::vector<int>> permuteNextPermutation(std::vector<int>& nums);

    /**
     * Approach 4: Heap's Algorithm (Minimal Swaps)
     * 
     * Generate permutations using Heap's algorithm with minimal changes.
     * 
     * Reasoning: Heap's algorithm generates all permutations by making the minimum
     * number of swaps between consecutive permutations. For each level of recursion,
     * it systematically swaps elements to generate all permutations. The algorithm
     * is particularly elegant because it generates each permutation from the previous
     * one with exactly one swap, making it very efficient for applications that
     * process permutations incrementally.
     * 
     * Time Complexity: O(n!) - exactly n! swaps, optimal for permutation generation
     * Space Complexity: O(n) - recursion depth (excluding result storage)
     * 
     * Best when: Need minimal number of swaps, optimal permutation generation
     * Worst when: Algorithm logic is less intuitive than standard backtracking
     */
    std::vector<std::vector<int>> permuteHeaps(std::vector<int>& nums);

    /**
     * Approach 5: Iterative with Stack (Non-Recursive)
     * 
     * Generate permutations iteratively using explicit stack to simulate recursion.
     * 
     * Reasoning: Convert the recursive backtracking approach into an iterative one
     * using a stack to store the state (current permutation, used elements).
     * This approach is useful when recursion depth might be a concern or when
     * you prefer explicit control over the execution stack. Each stack frame
     * contains the current permutation and a set of available choices.
     * 
     * Time Complexity: O(n! * n) - same as recursive backtracking
     * Space Complexity: O(n! * n) - stack can grow large with multiple partial permutations
     * 
     * Best when: Want to avoid recursion, need explicit control over execution
     * Worst when: Stack space usage can be higher than recursive approach
     */
    std::vector<std::vector<int>> permuteIterative(std::vector<int>& nums);

    /**
     * Approach 6: Factorial Number System (Lehmer Code)
     * 
     * Generate permutations using mathematical factorial number system.
     * 
     * Reasoning: Each permutation can be uniquely represented by a sequence of
     * numbers in factorial base (Lehmer code). For n elements, generate integers
     * from 0 to n!-1, convert each to factorial base, then use these digits as
     * indices to build permutations. This approach provides a direct mapping
     * between integers and permutations, allowing generation of specific
     * permutations by index or all permutations systematically.
     * 
     * Time Complexity: O(n! * n²) - n! permutations, each requiring O(n²) to construct
     * Space Complexity: O(n) - for factorial base conversion and available elements
     * 
     * Best when: Need mathematical approach, want to generate specific permutation by index
     * Worst when: Higher time complexity due to list operations, complex to understand
     */
    std::vector<std::vector<int>> permuteFactorialSystem(std::vector<int>& nums);

private:
    // Helper functions
    void backtrackHelper(std::vector<int>& nums, std::vector<int>& current, 
                        std::vector<bool>& used, std::vector<std::vector<int>>& result);
    
    void swapHelper(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result);
    
    void heapsHelper(std::vector<int>& nums, int n, std::vector<std::vector<int>>& result);
    
    std::vector<int> factorialToPermutation(const std::vector<int>& nums, 
                                          const std::vector<int>& factorialBase);
    
    std::vector<int> intToFactorialBase(int num, int base);
    
    // Stack state for iterative approach
    struct IterativeState {
        std::vector<int> current;
        std::unordered_set<int> used;
        
        IterativeState(const std::vector<int>& curr, const std::unordered_set<int>& u)
            : current(curr), used(u) {}
    };
};

}
}