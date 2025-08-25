#include <gtest/gtest.h>
#include "../../src/easy/number_of_1_bits.h"
#include <cstdint>

namespace leetcode {
namespace easy {
namespace test {

class NumberOf1BitsTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(uint32_t n, int expected) {
        NumberOf1Bits solution;
        
        EXPECT_EQ(solution.hammingWeightBitClear(n), expected) 
            << "BitClear failed for input: " << n;
        
        EXPECT_EQ(solution.hammingWeightBrianKernighan(n), expected)
            << "BrianKernighan failed for input: " << n;
        
        EXPECT_EQ(solution.hammingWeightBuiltIn(n), expected)
            << "BuiltIn failed for input: " << n;
        
        EXPECT_EQ(solution.hammingWeightLookupTable(n), expected)
            << "LookupTable failed for input: " << n;
        
        EXPECT_EQ(solution.hammingWeightDivideConquer(n), expected)
            << "DivideConquer failed for input: " << n;
        
        EXPECT_EQ(solution.hammingWeightBitShift(n), expected)
            << "BitShift failed for input: " << n;
    }
};

// LeetCode Example Test Cases

TEST_F(NumberOf1BitsTest, LeetCodeExample1) {
    // Input: n = 00000000000000000000000000001011
    // Output: 3
    testAllApproaches(0b00000000000000000000000000001011, 3);
}

TEST_F(NumberOf1BitsTest, LeetCodeExample2) {
    // Input: n = 00000000000000000000000010000000
    // Output: 1
    testAllApproaches(0b00000000000000000000000010000000, 1);
}

// Edge Cases

TEST_F(NumberOf1BitsTest, Zero) {
    // No bits set
    testAllApproaches(0, 0);
}

TEST_F(NumberOf1BitsTest, AllOnes) {
    // All 32 bits set
    testAllApproaches(0xFFFFFFFF, 32);
}

TEST_F(NumberOf1BitsTest, SingleBitFirst) {
    // Only the first bit set
    testAllApproaches(0x00000001, 1);
}

TEST_F(NumberOf1BitsTest, SingleBitLast) {
    // Only the last bit set
    testAllApproaches(0x80000000, 1);
}

// Power of 2 Tests

TEST_F(NumberOf1BitsTest, PowerOf2_1) {
    testAllApproaches(1, 1);
}

TEST_F(NumberOf1BitsTest, PowerOf2_2) {
    testAllApproaches(2, 1);
}

TEST_F(NumberOf1BitsTest, PowerOf2_4) {
    testAllApproaches(4, 1);
}

TEST_F(NumberOf1BitsTest, PowerOf2_256) {
    testAllApproaches(256, 1);
}

TEST_F(NumberOf1BitsTest, PowerOf2_65536) {
    testAllApproaches(65536, 1);
}

// Alternating Patterns

TEST_F(NumberOf1BitsTest, AlternatingBits_0x55555555) {
    // 01010101010101010101010101010101
    testAllApproaches(0x55555555, 16);
}

TEST_F(NumberOf1BitsTest, AlternatingBits_0xAAAAAAAA) {
    // 10101010101010101010101010101010
    testAllApproaches(0xAAAAAAAA, 16);
}

TEST_F(NumberOf1BitsTest, AlternatingBytes_0x00FF00FF) {
    // 00000000111111110000000011111111
    testAllApproaches(0x00FF00FF, 16);
}

TEST_F(NumberOf1BitsTest, AlternatingBytes_0xFF00FF00) {
    // 11111111000000001111111100000000
    testAllApproaches(0xFF00FF00, 16);
}

// Consecutive Bits

TEST_F(NumberOf1BitsTest, Consecutive1Bit) {
    testAllApproaches(0x00000001, 1);
}

TEST_F(NumberOf1BitsTest, Consecutive2Bits) {
    testAllApproaches(0x00000003, 2);
}

TEST_F(NumberOf1BitsTest, Consecutive3Bits) {
    testAllApproaches(0x00000007, 3);
}

TEST_F(NumberOf1BitsTest, Consecutive8Bits) {
    testAllApproaches(0x000000FF, 8);
}

TEST_F(NumberOf1BitsTest, Consecutive16Bits) {
    testAllApproaches(0x0000FFFF, 16);
}

// Specific Patterns

TEST_F(NumberOf1BitsTest, HexPattern_0x12345678) {
    // 0001001000110100010101100111000 = 13 bits
    testAllApproaches(0x12345678, 13);
}

TEST_F(NumberOf1BitsTest, HexPattern_0xDEADBEEF) {
    // 11011110101011011011111011101111 = 24 bits
    testAllApproaches(0xDEADBEEF, 24);
}

TEST_F(NumberOf1BitsTest, HexPattern_0xCAFEBABE) {
    // 11001010111111101011101010111110 = 22 bits
    testAllApproaches(0xCAFEBABE, 22);
}

// Byte Patterns

TEST_F(NumberOf1BitsTest, SingleByteFirst) {
    testAllApproaches(0xFF000000, 8);
}

TEST_F(NumberOf1BitsTest, SingleByteSecond) {
    testAllApproaches(0x00FF0000, 8);
}

TEST_F(NumberOf1BitsTest, SingleByteThird) {
    testAllApproaches(0x0000FF00, 8);
}

TEST_F(NumberOf1BitsTest, SingleByteFourth) {
    testAllApproaches(0x000000FF, 8);
}

// Sparse Patterns (few bits set)

TEST_F(NumberOf1BitsTest, SparseBits_3Bits) {
    // Bits at positions 0, 15, 31
    testAllApproaches(0x80008001, 3);
}

TEST_F(NumberOf1BitsTest, SparseBits_4Bits) {
    // Bits at positions 0, 7, 15, 31
    testAllApproaches(0x80008081, 4);
}

TEST_F(NumberOf1BitsTest, SparseBits_5Bits) {
    // Bits at positions 0, 7, 15, 23, 31
    testAllApproaches(0x80808081, 5);
}

// Dense Patterns (many bits set)

TEST_F(NumberOf1BitsTest, DenseBits_31Bits) {
    // All bits except bit 15
    testAllApproaches(0xFFFF7FFF, 31);
}

TEST_F(NumberOf1BitsTest, DenseBits_30Bits) {
    // All bits except bits 7 and 15
    testAllApproaches(0xFFFF7F7F, 30);
}

TEST_F(NumberOf1BitsTest, DenseBits_29Bits) {
    // All bits except bits 7, 15, and 23
    testAllApproaches(0xFF7F7F7F, 29);
}

// Half and Quarter Patterns

TEST_F(NumberOf1BitsTest, FirstHalf) {
    // First 16 bits set
    testAllApproaches(0x0000FFFF, 16);
}

TEST_F(NumberOf1BitsTest, SecondHalf) {
    // Last 16 bits set
    testAllApproaches(0xFFFF0000, 16);
}

TEST_F(NumberOf1BitsTest, FirstQuarter) {
    // First 8 bits set
    testAllApproaches(0x000000FF, 8);
}

TEST_F(NumberOf1BitsTest, LastQuarter) {
    // Last 8 bits set
    testAllApproaches(0xFF000000, 8);
}

// Prime Number Bit Patterns

TEST_F(NumberOf1BitsTest, Prime3) {
    testAllApproaches(3, 2);  // 11
}

TEST_F(NumberOf1BitsTest, Prime7) {
    testAllApproaches(7, 3);  // 111
}

TEST_F(NumberOf1BitsTest, Prime31) {
    testAllApproaches(31, 5); // 11111
}

// Fibonacci Patterns

TEST_F(NumberOf1BitsTest, Fibonacci21) {
    testAllApproaches(21, 3); // 10101
}

TEST_F(NumberOf1BitsTest, Fibonacci55) {
    testAllApproaches(55, 5); // 110111
}

// Maximum Values

TEST_F(NumberOf1BitsTest, MaxUInt32) {
    testAllApproaches(UINT32_MAX, 32);
}

TEST_F(NumberOf1BitsTest, MaxInt32) {
    testAllApproaches(0x7FFFFFFF, 31);
}

// Binary Progression

TEST_F(NumberOf1BitsTest, BinaryProgression1) {
    testAllApproaches(0x11111111, 8); // 1 bit per nibble
}

TEST_F(NumberOf1BitsTest, BinaryProgression2) {
    testAllApproaches(0x33333333, 16); // 2 bits per nibble
}

TEST_F(NumberOf1BitsTest, BinaryProgression3) {
    testAllApproaches(0x77777777, 24); // 3 bits per nibble
}

// Checkerboard Patterns

TEST_F(NumberOf1BitsTest, CheckerboardNibbles) {
    testAllApproaches(0x0F0F0F0F, 16);
}

TEST_F(NumberOf1BitsTest, CheckerboardBytes) {
    testAllApproaches(0x00FF00FF, 16);
}

// Special Cases

TEST_F(NumberOf1BitsTest, OneAwayFromZero) {
    testAllApproaches(1, 1);
}

TEST_F(NumberOf1BitsTest, OneAwayFromMax) {
    testAllApproaches(0xFFFFFFFE, 31);
}

TEST_F(NumberOf1BitsTest, MiddleValue) {
    testAllApproaches(0x80000000, 1);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode