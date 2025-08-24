#pragma once

#include <cstdint>

namespace leetcode {
namespace easy {

/**
 * Problem 190: Reverse Bits
 * 
 * Reverse bits of a given 32 bits unsigned integer.
 * 
 * Note:
 * - In some languages, such as Java, there is no unsigned integer type. In this case,
 *   both input and output will be given as a signed integer type. They should not affect
 *   your implementation, as the integer's internal binary representation is the same,
 *   whether it is signed or unsigned.
 * - In Java, the compiler represents the signed integers using 2's complement notation.
 *   Therefore, in Example 2 below, the input represents the signed integer -3 and the
 *   output represents the signed integer -1073741825.
 * 
 * Example 1:
 * Input: n = 00000010100101000001111010011100
 * Output:    964176192 (00111001011110000010100101000000)
 * 
 * Example 2:
 * Input: n = 11111111111111111111111111111101
 * Output:   3221225471 (10111111111111111111111111111111)
 * 
 * Constraints:
 * - The input must be a binary string of length 32
 * 
 * Follow up:
 * If this function is called many times, how would you optimize it?
 */
class ReverseBits {
public:
    /**
     * Approach 1: Bit-by-Bit Reversal (Standard)
     * 
     * Extract each bit from the right and place it in the reversed position.
     * 
     * Reasoning: This is the most straightforward approach. We process each bit
     * from the input number, extracting it using bitwise AND with 1, then placing
     * it in the correct position in the result using left shift. We shift the input
     * right after each extraction to process the next bit.
     * 
     * Time Complexity: O(32) = O(1) - always process 32 bits
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Clear, readable solution is needed
     * Worst when: Maximum performance is critical
     */
    uint32_t reverseBitsBitByBit(uint32_t n);

    /**
     * Approach 2: Divide and Conquer (Bit Swapping)
     * 
     * Swap bits in groups, progressively from pairs to halves.
     * 
     * Reasoning: Instead of processing bits one by one, we can swap groups of bits
     * using masks. We start by swapping adjacent bits, then 2-bit groups, then 4-bit
     * groups, and so on. This approach uses bit manipulation patterns that can be
     * optimized by modern processors.
     * 
     * Time Complexity: O(log 32) = O(1) - constant number of swaps
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Performance is important, parallel operations available
     * Worst when: Code clarity is more important than optimization
     */
    uint32_t reverseBitsDivideConquer(uint32_t n);

    /**
     * Approach 3: Lookup Table (Cache Optimization)
     * 
     * Use precomputed lookup tables for byte reversal.
     * 
     * Reasoning: For frequent calls, we can precompute the reversal of all possible
     * byte values (256 entries) and use this table to reverse 4 bytes independently.
     * This trades memory for speed and is especially effective when the function
     * is called many times.
     * 
     * Time Complexity: O(1) - four table lookups
     * Space Complexity: O(256) = O(1) - fixed size lookup table
     * 
     * Best when: Function is called frequently, cache-friendly
     * Worst when: Memory is extremely limited, called rarely
     */
    uint32_t reverseBitsLookupTable(uint32_t n);

    /**
     * Approach 4: String Manipulation
     * 
     * Convert to string, reverse, and convert back.
     * 
     * Reasoning: Although not the most efficient, this approach clearly demonstrates
     * the reversal operation. We convert the number to a binary string representation,
     * reverse the string, and convert back to an integer. This is educational and
     * shows the problem from a different perspective.
     * 
     * Time Complexity: O(32) = O(1) - string operations on fixed size
     * Space Complexity: O(32) = O(1) - string storage
     * 
     * Best when: Clarity and understanding are priorities
     * Worst when: Performance is critical
     */
    uint32_t reverseBitsString(uint32_t n);

    /**
     * Approach 5: Recursive Solution
     * 
     * Recursively reverse bits by dividing the problem.
     * 
     * Reasoning: We can solve this recursively by reversing the left and right
     * halves of the bits separately, then swapping them. The base case is when
     * we have a single bit. This demonstrates the divide-and-conquer nature of
     * the problem in a recursive manner.
     * 
     * Time Complexity: O(log 32) = O(1) - recursion depth is constant
     * Space Complexity: O(log 32) = O(1) - recursion stack
     * 
     * Best when: Demonstrating recursive approaches
     * Worst when: Stack space is limited, iterative is clearer
     */
    uint32_t reverseBitsRecursive(uint32_t n);

    /**
     * Approach 6: Optimized with Built-in Functions
     * 
     * Use compiler intrinsics or built-in functions when available.
     * 
     * Reasoning: Modern compilers provide built-in functions for bit manipulation
     * that may use processor-specific instructions for optimal performance. While
     * not portable across all systems, this shows how to leverage platform-specific
     * optimizations when available.
     * 
     * Time Complexity: O(1) - hardware optimized
     * Space Complexity: O(1) - no extra space
     * 
     * Best when: Maximum performance on supported platforms
     * Worst when: Portability across platforms is required
     */
    uint32_t reverseBitsOptimized(uint32_t n);

private:
    // Helper for recursive approach
    uint32_t reverseBitsRecursiveHelper(uint32_t n, int remaining);
    
    // Lookup table for byte reversal (lazy initialization)
    static uint8_t reverseByteTable[256];
    static bool tableInitialized;
    
    // Initialize the lookup table
    void initializeLookupTable();
    
    // Helper to reverse a single byte
    uint8_t reverseByte(uint8_t byte);
};

}  // namespace easy
}  // namespace leetcode