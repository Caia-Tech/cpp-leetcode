#pragma once

#include <cstdint>

namespace leetcode {
namespace easy {

/**
 * Problem 191: Number of 1 Bits
 * 
 * Write a function that takes an unsigned integer and returns the number of '1' bits it has.
 * (This function is sometimes called the Hamming weight.)
 * 
 * Example 1:
 * Input: n = 00000000000000000000000000001011
 * Output: 3
 * Explanation: The input binary string has three '1' bits.
 * 
 * Example 2:
 * Input: n = 00000000000000000000000010000000
 * Output: 1
 * Explanation: The input binary string has one '1' bit.
 * 
 * Constraints:
 * - The input must be a binary string of length 32
 */
class NumberOf1Bits {
public:
    /**
     * Approach 1: Clear Lowest Bit (Brian Kernighan)
     * 
     * Use the trick n & (n-1) to clear the lowest set bit.
     * 
     * Reasoning: n & (n-1) always clears the lowest set bit of n.
     * This is because (n-1) flips all the trailing zeros and the lowest set bit.
     * 
     * Time Complexity: O(k) - where k is the number of set bits
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Sparse bit patterns (few set bits)
     * Worst when: Dense bit patterns (many set bits)
     */
    int hammingWeightBitClear(uint32_t n);

    /**
     * Approach 2: Brian Kernighan's Algorithm (Alternative Implementation)
     * 
     * Same algorithm as above but with different loop structure.
     * 
     * Reasoning: Identical to approach 1 but shows different coding style.
     * Demonstrates the flexibility of the core algorithm.
     * 
     * Time Complexity: O(k) - where k is the number of set bits
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Alternative implementation preference
     * Worst when: Need maximum performance (slight overhead vs approach 1)
     */
    int hammingWeightBrianKernighan(uint32_t n);

    /**
     * Approach 3: Built-in Popcount
     * 
     * Use compiler built-in function for population count.
     * 
     * Reasoning: Modern processors have dedicated instructions for bit counting.
     * The compiler can generate optimal machine code using these instructions.
     * This leverages hardware optimization when available.
     * 
     * Time Complexity: O(1) - single instruction on modern hardware
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Maximum performance on supported hardware
     * Worst when: Portability across different compilers/platforms
     */
    int hammingWeightBuiltIn(uint32_t n);

    /**
     * Approach 4: Lookup Table
     * 
     * Pre-compute bit counts for all possible byte values.
     * 
     * Reasoning: Trade memory for speed by pre-computing results.
     * Process the 32-bit number as four 8-bit chunks and sum their counts.
     * This approach is cache-friendly and very fast for multiple calls.
     * 
     * Time Complexity: O(1) - four table lookups
     * Space Complexity: O(256) = O(1) - fixed size lookup table
     * 
     * Best when: Many repeated calls, cache-friendly access patterns
     * Worst when: Memory is extremely limited, single call scenarios
     */
    int hammingWeightLookupTable(uint32_t n);

    /**
     * Approach 5: Divide and Conquer (SWAR)
     * 
     * Use bit manipulation to count bits in parallel.
     * 
     * Reasoning: SWAR (SIMD Within A Register) technique processes multiple
     * bits simultaneously. It uses bit masks to count bits in parallel,
     * progressively combining results from smaller to larger groups.
     * 
     * Time Complexity: O(log w) = O(1) - where w=32 is word size
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Demonstrating parallel algorithms, educational purposes
     * Worst when: Code clarity is more important than showing technique
     */
    int hammingWeightDivideConquer(uint32_t n);

    /**
     * Approach 6: Bit Shifting
     * 
     * Check each bit position by shifting and masking.
     * 
     * Reasoning: Most straightforward approach that examines each bit
     * position individually. Easy to understand and implement, though
     * not the most efficient for sparse bit patterns.
     * 
     * Time Complexity: O(32) = O(1) - always check all 32 bits
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Code clarity is important, educational purposes
     * Worst when: Performance is critical for sparse patterns
     */
    int hammingWeightBitShift(uint32_t n);

private:
    // Static lookup table for byte bit counts (lazy initialization)
    static uint8_t byteCountTable[256];
    static bool tableInitialized;
    
    // Initialize the lookup table
    void initializeLookupTable();
};

}  // namespace easy
}  // namespace leetcode