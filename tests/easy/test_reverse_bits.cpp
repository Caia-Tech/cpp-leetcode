#include <gtest/gtest.h>
#include "../../src/easy/reverse_bits.h"
#include <cstdint>

namespace leetcode {
namespace easy {
namespace test {

class ReverseBitsTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(uint32_t n, uint32_t expected) {
        ReverseBits solution;
        
        EXPECT_EQ(solution.reverseBitsBitByBit(n), expected) 
            << "Bit-by-bit failed for input: " << n;
        
        EXPECT_EQ(solution.reverseBitsDivideConquer(n), expected)
            << "Divide and conquer failed for input: " << n;
        
        EXPECT_EQ(solution.reverseBitsLookupTable(n), expected)
            << "Lookup table failed for input: " << n;
        
        EXPECT_EQ(solution.reverseBitsString(n), expected)
            << "String manipulation failed for input: " << n;
        
        EXPECT_EQ(solution.reverseBitsRecursive(n), expected)
            << "Recursive failed for input: " << n;
        
        EXPECT_EQ(solution.reverseBitsOptimized(n), expected)
            << "Optimized failed for input: " << n;
    }
};

// LeetCode Example Test Cases

TEST_F(ReverseBitsTest, LeetCodeExample1) {
    // Input: n = 00000010100101000001111010011100
    // Output:    964176192 (00111001011110000010100101000000)
    uint32_t input = 0b00000010100101000001111010011100;
    uint32_t expected = 964176192;
    testAllApproaches(input, expected);
}

TEST_F(ReverseBitsTest, LeetCodeExample2) {
    // Input: n = 11111111111111111111111111111101
    // Output:   3221225471 (10111111111111111111111111111111)
    uint32_t input = 0b11111111111111111111111111111101;
    uint32_t expected = 3221225471;
    testAllApproaches(input, expected);
}

// Edge Cases

TEST_F(ReverseBitsTest, AllZeros) {
    // All zeros should remain all zeros
    testAllApproaches(0, 0);
}

TEST_F(ReverseBitsTest, AllOnes) {
    // All ones should remain all ones
    testAllApproaches(0xFFFFFFFF, 0xFFFFFFFF);
}

TEST_F(ReverseBitsTest, SingleBitAtStart) {
    // 10000000000000000000000000000000 -> 00000000000000000000000000000001
    testAllApproaches(0x80000000, 1);
}

TEST_F(ReverseBitsTest, SingleBitAtEnd) {
    // 00000000000000000000000000000001 -> 10000000000000000000000000000000
    testAllApproaches(1, 0x80000000);
}

// Power of 2 Tests

TEST_F(ReverseBitsTest, PowerOfTwo_2) {
    // 00000000000000000000000000000010 -> 01000000000000000000000000000000
    testAllApproaches(2, 0x40000000);
}

TEST_F(ReverseBitsTest, PowerOfTwo_4) {
    // 00000000000000000000000000000100 -> 00100000000000000000000000000000
    testAllApproaches(4, 0x20000000);
}

TEST_F(ReverseBitsTest, PowerOfTwo_256) {
    // 00000000000000000000000100000000 -> 00000000100000000000000000000000
    testAllApproaches(256, 0x00800000);
}

TEST_F(ReverseBitsTest, PowerOfTwo_65536) {
    // 00000000000000010000000000000000 -> 00000000000000001000000000000000
    testAllApproaches(65536, 0x00008000);
}

// Alternating Pattern Tests

TEST_F(ReverseBitsTest, AlternatingBits_0x55555555) {
    // 01010101010101010101010101010101 -> 10101010101010101010101010101010
    testAllApproaches(0x55555555, 0xAAAAAAAA);
}

TEST_F(ReverseBitsTest, AlternatingBits_0xAAAAAAAA) {
    // 10101010101010101010101010101010 -> 01010101010101010101010101010101
    testAllApproaches(0xAAAAAAAA, 0x55555555);
}

TEST_F(ReverseBitsTest, AlternatingNibbles_0x0F0F0F0F) {
    // 00001111000011110000111100001111 -> 11110000111100001111000011110000
    testAllApproaches(0x0F0F0F0F, 0xF0F0F0F0);
}

TEST_F(ReverseBitsTest, AlternatingBytes_0x00FF00FF) {
    // 00000000111111110000000011111111 -> 11111111000000001111111100000000
    testAllApproaches(0x00FF00FF, 0xFF00FF00);
}

// Symmetric Pattern Tests

TEST_F(ReverseBitsTest, Palindrome_0x81818181) {
    // 10000001100000011000000110000001 -> 10000001100000011000000110000001
    testAllApproaches(0x81818181, 0x81818181);
}

TEST_F(ReverseBitsTest, SymmetricPattern_0x00FF00) {
    // 00000000000011111111000000000000 -> 00000000000011111111000000000000
    uint32_t input = 0x00FF00;
    uint32_t expected = 0x00FF0000;
    testAllApproaches(input, expected);
}

// Byte Boundary Tests

TEST_F(ReverseBitsTest, SingleByteFirst) {
    // 11111111000000000000000000000000 -> 00000000000000000000000011111111
    testAllApproaches(0xFF000000, 0x000000FF);
}

TEST_F(ReverseBitsTest, SingleByteSecond) {
    // 00000000111111110000000000000000 -> 00000000000000001111111100000000
    testAllApproaches(0x00FF0000, 0x0000FF00);
}

TEST_F(ReverseBitsTest, SingleByteThird) {
    // 00000000000000001111111100000000 -> 00000000111111110000000000000000
    testAllApproaches(0x0000FF00, 0x00FF0000);
}

TEST_F(ReverseBitsTest, SingleByteFourth) {
    // 00000000000000000000000011111111 -> 11111111000000000000000000000000
    testAllApproaches(0x000000FF, 0xFF000000);
}

// Sequential Pattern Tests

TEST_F(ReverseBitsTest, SequentialBits_0x12345678) {
    // 00010010001101000101011001111000 -> 00011110011010100010110001001000
    testAllApproaches(0x12345678, 0x1E6A2C48);
}

TEST_F(ReverseBitsTest, SequentialBits_0x87654321) {
    // 10000111011001010100001100100001 -> 10000100110000101010011011100001
    testAllApproaches(0x87654321, 0x84C2A6E1);
}

TEST_F(ReverseBitsTest, SequentialBits_0xABCDEF01) {
    // 10101011110011011110111100000001 -> 10000000111101111011001111010101
    testAllApproaches(0xABCDEF01, 0x80F7B3D5);
}

// Random Pattern Tests

TEST_F(ReverseBitsTest, RandomPattern1) {
    // Custom pattern
    testAllApproaches(0xDEADBEEF, 0xF77DB57B);
}

TEST_F(ReverseBitsTest, RandomPattern2) {
    // Custom pattern
    testAllApproaches(0xCAFEBABE, 0x7D5D7F53);
}

TEST_F(ReverseBitsTest, RandomPattern3) {
    // Custom pattern
    testAllApproaches(0x1337C0DE, 0x7B03ECC8);
}

// Maximum and Minimum Values

TEST_F(ReverseBitsTest, MaxValue) {
    // Maximum unsigned 32-bit value
    testAllApproaches(UINT32_MAX, UINT32_MAX);
}

TEST_F(ReverseBitsTest, MinValue) {
    // Minimum unsigned 32-bit value
    testAllApproaches(0, 0);
}

// Specific Bit Patterns

TEST_F(ReverseBitsTest, FirstHalfSet) {
    // First 16 bits set
    testAllApproaches(0xFFFF0000, 0x0000FFFF);
}

TEST_F(ReverseBitsTest, SecondHalfSet) {
    // Second 16 bits set
    testAllApproaches(0x0000FFFF, 0xFFFF0000);
}

TEST_F(ReverseBitsTest, MiddleBitsSet) {
    // Middle 16 bits set
    testAllApproaches(0x00FFFF00, 0x00FFFF00);
}

TEST_F(ReverseBitsTest, OuterBitsSet) {
    // Outer 16 bits set
    testAllApproaches(0xFF0000FF, 0xFF0000FF);
}

// Incremental Tests

TEST_F(ReverseBitsTest, SmallNumbers) {
    // Test small numbers
    testAllApproaches(1, 0x80000000);
    testAllApproaches(2, 0x40000000);
    testAllApproaches(3, 0xC0000000);
    testAllApproaches(4, 0x20000000);
    testAllApproaches(5, 0xA0000000);
}

// Special Patterns

TEST_F(ReverseBitsTest, CheckerboardPattern) {
    // Checkerboard pattern
    testAllApproaches(0x33333333, 0xCCCCCCCC);
    testAllApproaches(0xCCCCCCCC, 0x33333333);
}

TEST_F(ReverseBitsTest, DiagonalPattern) {
    // Diagonal-like pattern
    testAllApproaches(0x08040201, 0x80402010);
    testAllApproaches(0x80402010, 0x08040201);
}

TEST_F(ReverseBitsTest, PrimePattern) {
    // Using prime numbers as bit patterns
    testAllApproaches(0x00000007, 0xE0000000);  // 7 in binary: 111
    testAllApproaches(0x0000001F, 0xF8000000);  // 31 in binary: 11111
}

// Stress Tests

TEST_F(ReverseBitsTest, ReverseTwice) {
    // Reversing twice should give original number
    ReverseBits solution;
    uint32_t original = 0x12345678;
    uint32_t reversed = solution.reverseBitsBitByBit(original);
    uint32_t doubleReversed = solution.reverseBitsBitByBit(reversed);
    EXPECT_EQ(original, doubleReversed);
}

TEST_F(ReverseBitsTest, ConsistencyCheck) {
    // All methods should give same result for various inputs
    ReverseBits solution;
    for (uint32_t test : {0x12345678u, 0xDEADBEEFu, 0xCAFEBABEu, 0x1337C0DEu}) {
        uint32_t result1 = solution.reverseBitsBitByBit(test);
        uint32_t result2 = solution.reverseBitsDivideConquer(test);
        uint32_t result3 = solution.reverseBitsLookupTable(test);
        uint32_t result4 = solution.reverseBitsString(test);
        uint32_t result5 = solution.reverseBitsRecursive(test);
        uint32_t result6 = solution.reverseBitsOptimized(test);
        
        EXPECT_EQ(result1, result2);
        EXPECT_EQ(result1, result3);
        EXPECT_EQ(result1, result4);
        EXPECT_EQ(result1, result5);
        EXPECT_EQ(result1, result6);
    }
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode