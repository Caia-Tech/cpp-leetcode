#include "reverse_bits.h"
#include <string>
#include <algorithm>

namespace leetcode {
namespace easy {

// Static member initialization
uint8_t ReverseBits::reverseByteTable[256];
bool ReverseBits::tableInitialized = false;

// Approach 1: Bit-by-Bit Reversal (Standard)
uint32_t ReverseBits::reverseBitsBitByBit(uint32_t n) {
    uint32_t result = 0;
    
    for (int i = 0; i < 32; i++) {
        // Extract the rightmost bit
        result = (result << 1) | (n & 1);
        // Move to the next bit
        n >>= 1;
    }
    
    return result;
}

// Approach 2: Divide and Conquer (Bit Swapping)
uint32_t ReverseBits::reverseBitsDivideConquer(uint32_t n) {
    // Swap odd and even bits
    n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
    // Swap consecutive pairs
    n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
    // Swap nibbles
    n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
    // Swap bytes
    n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
    // Swap 2-byte pairs
    n = (n >> 16) | (n << 16);
    
    return n;
}

// Approach 3: Lookup Table (Cache Optimization)
uint32_t ReverseBits::reverseBitsLookupTable(uint32_t n) {
    if (!tableInitialized) {
        initializeLookupTable();
    }
    
    uint32_t result = 0;
    
    // Reverse each byte using the lookup table
    result |= ((uint32_t)reverseByteTable[n & 0xFF]) << 24;
    result |= ((uint32_t)reverseByteTable[(n >> 8) & 0xFF]) << 16;
    result |= ((uint32_t)reverseByteTable[(n >> 16) & 0xFF]) << 8;
    result |= ((uint32_t)reverseByteTable[(n >> 24) & 0xFF]);
    
    return result;
}

// Approach 4: String Manipulation
uint32_t ReverseBits::reverseBitsString(uint32_t n) {
    std::string binary = "";
    
    // Convert to binary string
    for (int i = 0; i < 32; i++) {
        binary += (n & 1) ? '1' : '0';
        n >>= 1;
    }
    
    // String is already reversed due to how we built it
    // Convert back to integer
    uint32_t result = 0;
    for (char bit : binary) {
        result = (result << 1) | (bit - '0');
    }
    
    return result;
}

// Approach 5: Recursive Solution
uint32_t ReverseBits::reverseBitsRecursive(uint32_t n) {
    return reverseBitsRecursiveHelper(n, 32);
}

uint32_t ReverseBits::reverseBitsRecursiveHelper(uint32_t n, int remaining) {
    if (remaining == 1) {
        return n;
    }
    
    int half = remaining / 2;
    uint32_t mask = (1ULL << half) - 1;
    
    // Extract left and right halves
    uint32_t right = n & mask;
    uint32_t left = (n >> half) & mask;
    
    // Recursively reverse each half and swap them
    uint32_t reversedRight = reverseBitsRecursiveHelper(right, half);
    uint32_t reversedLeft = reverseBitsRecursiveHelper(left, half);
    
    // Combine with swapped positions
    return (reversedRight << half) | reversedLeft;
}

// Approach 6: Optimized with Built-in Functions
uint32_t ReverseBits::reverseBitsOptimized(uint32_t n) {
    // For GCC/Clang, we could use __builtin_bitreverse32 if available
    // For now, we'll use an optimized manual approach
    
    // This is similar to divide and conquer but with potential compiler optimizations
    n = ((n & 0xFFFF0000) >> 16) | ((n & 0x0000FFFF) << 16);
    n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
    n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
    n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
    
    return n;
}

// Helper functions
void ReverseBits::initializeLookupTable() {
    for (int i = 0; i < 256; i++) {
        reverseByteTable[i] = reverseByte(i);
    }
    tableInitialized = true;
}

uint8_t ReverseBits::reverseByte(uint8_t byte) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result = (result << 1) | (byte & 1);
        byte >>= 1;
    }
    return result;
}

}  // namespace easy
}  // namespace leetcode