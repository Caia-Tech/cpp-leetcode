#include "number_of_1_bits.h"
#include <array>

namespace leetcode {
namespace easy {

// Static member initialization
uint8_t NumberOf1Bits::byteCountTable[256];
bool NumberOf1Bits::tableInitialized = false;

// Approach 1: Clear Lowest Bit (Brian Kernighan)
int NumberOf1Bits::hammingWeightBitClear(uint32_t n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // Clear the lowest set bit
        ++count;
    }
    return count;
}

// Approach 2: Brian Kernighan's Algorithm (Alternative Implementation)
int NumberOf1Bits::hammingWeightBrianKernighan(uint32_t n) {
    int count = 0;
    for (; n; ++count) {
        n &= (n - 1);  // Clear the lowest set bit
    }
    return count;
}

// Approach 3: Built-in Popcount
int NumberOf1Bits::hammingWeightBuiltIn(uint32_t n) {
    return __builtin_popcount(n);
}

// Approach 4: Lookup Table
int NumberOf1Bits::hammingWeightLookupTable(uint32_t n) {
    if (!tableInitialized) {
        initializeLookupTable();
    }
    
    return byteCountTable[n         & 0xFF] +
           byteCountTable[(n >>  8) & 0xFF] +
           byteCountTable[(n >> 16) & 0xFF] +
           byteCountTable[(n >> 24) & 0xFF];
}

// Approach 5: Divide and Conquer (SWAR)
int NumberOf1Bits::hammingWeightDivideConquer(uint32_t n) {
    // Count bits in pairs
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    
    // Count bits in groups of 4
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    
    // Count bits in groups of 8
    n = (n + (n >> 4)) & 0x0F0F0F0F;
    
    // Sum all bytes by multiplying and shifting
    return (n * 0x01010101) >> 24;
}

// Approach 6: Bit Shifting
int NumberOf1Bits::hammingWeightBitShift(uint32_t n) {
    int count = 0;
    for (int i = 0; i < 32; ++i) {
        count += (n >> i) & 1;
    }
    return count;
}

// Helper function to initialize lookup table
void NumberOf1Bits::initializeLookupTable() {
    for (int i = 0; i < 256; ++i) {
        byteCountTable[i] = (i & 1) + byteCountTable[i >> 1];
    }
    tableInitialized = true;
}

}  // namespace easy
}  // namespace leetcode