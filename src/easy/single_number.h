#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

namespace leetcode {
namespace easy {

/**
 * Problem 136: Single Number
 * 
 * Given a non-empty array of integers nums, every element appears twice except for one. 
 * Find that single one.
 * 
 * You must implement a solution with a linear runtime complexity and use only constant 
 * extra space.
 * 
 * Constraints:
 * - 1 <= nums.length <= 3 * 10^4
 * - -3 * 10^4 <= nums[i] <= 3 * 10^4
 * - Each element in the array appears twice except for one element which appears only once.
 */
class SingleNumber {
public:
    /**
     * Approach 1: XOR Bit Manipulation (Optimal)
     * 
     * Use XOR operation to find the single number.
     * 
     * Reasoning: This is the optimal solution leveraging XOR properties:
     * 1) a XOR 0 = a (identity)
     * 2) a XOR a = 0 (self-inverse)
     * 3) XOR is commutative and associative
     * 
     * When we XOR all numbers, pairs cancel out (a XOR a = 0), leaving
     * only the single number. For example: [2,1,2,3,3] -> 2^1^2^3^3 = 
     * (2^2)^(3^3)^1 = 0^0^1 = 1. This elegant solution uses constant space
     * and linear time.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only one variable for result
     * 
     * Best when: Always the best approach for this specific problem
     * Worst when: Need to find multiple single numbers or track counts
     */
    int singleNumberXOR(std::vector<int>& nums);

    /**
     * Approach 2: Hash Map Counting
     * 
     * Count occurrences of each number using hash map.
     * 
     * Reasoning: Store count of each number in a hash map, then find
     * the number with count 1. While this uses extra space, it's more
     * general and can handle variations like finding numbers that appear
     * odd times, or finding multiple single numbers. The approach is
     * intuitive and extends to more complex counting problems.
     * 
     * Time Complexity: O(n) - two passes through array
     * Space Complexity: O(n) - hash map stores at most n/2 + 1 unique numbers
     * 
     * Best when: Need to track counts, problem variations with different counts
     * Worst when: Space is constrained, only need single number
     */
    int singleNumberHashMap(std::vector<int>& nums);

    /**
     * Approach 3: Hash Set Toggle
     * 
     * Add/remove numbers from set, single number remains.
     * 
     * Reasoning: Add numbers to set on first encounter, remove on second.
     * The single number will be the only one left in the set. This is
     * more space-efficient than hash map (no counts stored) but still
     * uses O(n) space. The toggle mechanism is elegant: seen once -> add,
     * seen twice -> remove, leaving only the single occurrence.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(n) - set stores at most n/2 + 1 numbers
     * 
     * Best when: Simple implementation needed, moderate space available
     * Worst when: Need constant space solution
     */
    int singleNumberHashSet(std::vector<int>& nums);

    /**
     * Approach 4: Sorting
     * 
     * Sort array and find the element without a pair.
     * 
     * Reasoning: After sorting, duplicates are adjacent. Scan through
     * sorted array in steps of 2 - if current doesn't equal next, it's
     * the single number. Special handling needed for last element.
     * While this modifies the array and has higher time complexity,
     * it demonstrates a different algorithmic approach using ordering.
     * 
     * Time Complexity: O(n log n) - dominated by sorting
     * Space Complexity: O(1) or O(n) depending on sort implementation
     * 
     * Best when: Array needs to be sorted anyway, in-place modification OK
     * Worst when: Original order must be preserved, need O(n) time
     */
    int singleNumberSort(std::vector<int>& nums);

    /**
     * Approach 5: Mathematical Sum
     * 
     * Use mathematical formula: 2 * sum(unique) - sum(all) = single.
     * 
     * Reasoning: If we sum all unique elements and multiply by 2, we get
     * the sum as if all elements appeared twice. Subtracting the actual
     * sum gives us the single number. For example: [1,2,2,3,3]
     * unique sum = 1+2+3 = 6, actual sum = 1+2+2+3+3 = 11
     * single = 2*6 - 11 = 1. Creative mathematical approach.
     * 
     * Time Complexity: O(n) - need to find unique elements
     * Space Complexity: O(n) - set to store unique elements
     * 
     * Best when: Teaching mathematical problem-solving approaches
     * Worst when: Integer overflow is a concern, need constant space
     */
    int singleNumberMath(std::vector<int>& nums);

    /**
     * Approach 6: Bit Counting
     * 
     * Count set bits at each position across all numbers.
     * 
     * Reasoning: For each bit position (0-31 for 32-bit integers),
     * count how many numbers have that bit set. Since pairs contribute
     * even counts, positions with odd counts belong to the single number.
     * This generalizes to finding numbers that appear odd times and
     * demonstrates bit-level analysis. More complex than XOR but
     * educational for understanding bit patterns.
     * 
     * Time Complexity: O(32n) = O(n) - check 32 bit positions
     * Space Complexity: O(1) - only bit counters needed
     * 
     * Best when: Learning bit manipulation, generalizing to "appears k times"
     * Worst when: Simple XOR solution is sufficient
     */
    int singleNumberBitCount(std::vector<int>& nums);

private:
    // Helper for bit counting approach
    static constexpr int INT_BITS = 32;
};

}  // namespace easy
}  // namespace leetcode