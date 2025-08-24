#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

namespace leetcode {
namespace easy {

/**
 * Problem 169: Majority Element
 * 
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n/2⌋ times.
 * You may assume that the majority element always exists in the array.
 * 
 * Constraints:
 * - n == nums.length
 * - 1 <= n <= 5 * 10^4
 * - -10^9 <= nums[i] <= 10^9
 */
class MajorityElement {
public:
    /**
     * Approach 1: Boyer-Moore Voting Algorithm (Optimal)
     * 
     * Maintain a candidate and counter, updating as we traverse the array.
     * 
     * Reasoning: The key insight is that if we pair up different elements
     * and remove them, the majority element will still be the majority of
     * the remaining elements. We maintain a candidate and its count. When
     * we see the same element, increment count; otherwise decrement. When
     * count reaches 0, pick a new candidate. The final candidate is guaranteed
     * to be the majority element (given that one exists).
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only use two variables
     * 
     * Best when: Always - this is the optimal solution
     * Worst when: Never - this is the most efficient approach
     */
    int majorityElementBoyerMoore(std::vector<int>& nums);

    /**
     * Approach 2: Hash Map Counting
     * 
     * Count occurrences of each element and return the one with count > n/2.
     * 
     * Reasoning: Use a hash map to count the frequency of each element in
     * the array. As soon as we find an element with count greater than n/2,
     * we can return it immediately. This approach is straightforward and
     * easy to understand, though it requires extra space for the hash map.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(n) - hash map to store counts
     * 
     * Best when: Need to know exact counts, multiple queries on same data
     * Worst when: Memory is constrained
     */
    int majorityElementHashMap(std::vector<int>& nums);

    /**
     * Approach 3: Sorting
     * 
     * Sort the array, then the element at position n/2 is the majority.
     * 
     * Reasoning: After sorting, identical elements are grouped together.
     * Since the majority element appears more than n/2 times, it must
     * occupy the middle position (n/2) of the sorted array. This is because
     * the majority element's range will span across the middle regardless
     * of where it starts in the sorted array.
     * 
     * Time Complexity: O(n log n) - sorting dominates
     * Space Complexity: O(1) or O(n) - depends on sorting algorithm
     * 
     * Best when: Array needs to be sorted anyway for other operations
     * Worst when: Time efficiency is critical
     */
    int majorityElementSorting(std::vector<int>& nums);

    /**
     * Approach 4: Divide and Conquer
     * 
     * Recursively find majority in left and right halves, then combine.
     * 
     * Reasoning: Divide the array into two halves and recursively find the
     * majority element in each half. If both halves have the same majority,
     * that's the overall majority. If they differ, count occurrences of each
     * candidate in the full range to determine the true majority. This
     * demonstrates the divide-and-conquer paradigm for this problem.
     * 
     * Time Complexity: O(n log n) - T(n) = 2T(n/2) + O(n)
     * Space Complexity: O(log n) - recursion stack depth
     * 
     * Best when: Demonstrating divide-and-conquer techniques
     * Worst when: Simple iterative solution is clearer
     */
    int majorityElementDivideConquer(std::vector<int>& nums);

    /**
     * Approach 5: Bit Manipulation
     * 
     * Build the majority element bit by bit.
     * 
     * Reasoning: For each bit position (0-31 for 32-bit integers), count
     * how many numbers have that bit set. If more than n/2 numbers have
     * the bit set, then the majority element must have that bit set.
     * Build the result by setting appropriate bits based on these counts.
     * Works for both positive and negative numbers.
     * 
     * Time Complexity: O(32n) = O(n) - check each bit position
     * Space Complexity: O(1) - only use constant variables
     * 
     * Best when: Demonstrating bit manipulation techniques
     * Worst when: Simple approaches are more readable
     */
    int majorityElementBitManipulation(std::vector<int>& nums);

    /**
     * Approach 6: Functional Programming with Reduce
     * 
     * Use functional programming concepts to find the majority element.
     * 
     * Reasoning: Apply functional programming paradigms using reduce/fold
     * operations to implement the voting algorithm. Create a stateful
     * accumulator that maintains the candidate and count, updating them
     * as we process each element. This demonstrates how imperative
     * algorithms can be expressed in functional style.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - accumulator state only
     * 
     * Best when: Functional programming style preferred
     * Worst when: Imperative approach is clearer
     */
    int majorityElementFunctional(std::vector<int>& nums);

private:
    // Helper for divide and conquer
    int majorityElementDivideConquerHelper(std::vector<int>& nums, int left, int right);
    int countInRange(std::vector<int>& nums, int target, int left, int right);
    
    // Helper for functional approach
    struct VoteState {
        int candidate;
        int count;
    };
    std::function<VoteState(VoteState, int)> createVoteReducer();
};

}  // namespace easy
}  // namespace leetcode