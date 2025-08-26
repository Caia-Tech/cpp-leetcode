#include <gtest/gtest.h>
#include "../../src/easy/power_of_two.h"
#include <vector>

using namespace leetcode::easy;

// Test fixture for Power of Two
class PowerOfTwoTest : public ::testing::Test {
protected:
    void testAllApproaches(int n, bool expected) {
        EXPECT_EQ(PowerOfTwo::isPowerOfTwoBitManipulation(n), expected) 
            << "Bit manipulation approach failed for " << n;
        EXPECT_EQ(PowerOfTwo::isPowerOfTwoPopCount(n), expected) 
            << "PopCount approach failed for " << n;
        EXPECT_EQ(PowerOfTwo::isPowerOfTwoMath(n), expected) 
            << "Math approach failed for " << n;
        EXPECT_EQ(PowerOfTwo::isPowerOfTwoDivision(n), expected) 
            << "Division approach failed for " << n;
        EXPECT_EQ(PowerOfTwo::isPowerOfTwoLookup(n), expected) 
            << "Lookup approach failed for " << n;
        EXPECT_EQ(PowerOfTwo::isPowerOfTwoRecursive(n), expected) 
            << "Recursive approach failed for " << n;
    }
};

// Test Case 1: LeetCode examples
TEST_F(PowerOfTwoTest, LeetCodeExamples) {
    testAllApproaches(1, true);   // 2^0 = 1
    testAllApproaches(16, true);  // 2^4 = 16
    testAllApproaches(3, false);  // Not a power of 2
}

// Test Case 2: Small powers of 2
TEST_F(PowerOfTwoTest, SmallPowersOfTwo) {
    testAllApproaches(1, true);   // 2^0
    testAllApproaches(2, true);   // 2^1
    testAllApproaches(4, true);   // 2^2
    testAllApproaches(8, true);   // 2^3
    testAllApproaches(16, true);  // 2^4
    testAllApproaches(32, true);  // 2^5
    testAllApproaches(64, true);  // 2^6
    testAllApproaches(128, true); // 2^7
    testAllApproaches(256, true); // 2^8
    testAllApproaches(512, true); // 2^9
    testAllApproaches(1024, true); // 2^10
}

// Test Case 3: Non-powers of 2 (small numbers)
TEST_F(PowerOfTwoTest, SmallNonPowersOfTwo) {
    testAllApproaches(0, false);   // Not positive
    testAllApproaches(3, false);   // Odd, not 1
    testAllApproaches(5, false);   // Odd
    testAllApproaches(6, false);   // Even but not power of 2
    testAllApproaches(7, false);   // Odd
    testAllApproaches(9, false);   // Odd
    testAllApproaches(10, false);  // Even but not power of 2
    testAllApproaches(12, false);  // Even but not power of 2
    testAllApproaches(15, false);  // Odd
    testAllApproaches(17, false);  // Odd
    testAllApproaches(18, false);  // Even but not power of 2
}

// Test Case 4: Negative numbers
TEST_F(PowerOfTwoTest, NegativeNumbers) {
    testAllApproaches(-1, false);
    testAllApproaches(-2, false);
    testAllApproaches(-4, false);
    testAllApproaches(-8, false);
    testAllApproaches(-16, false);
    testAllApproaches(-100, false);
    testAllApproaches(-2147483648, false); // Minimum int value
}

// Test Case 5: Large powers of 2
TEST_F(PowerOfTwoTest, LargePowersOfTwo) {
    testAllApproaches(2048, true);     // 2^11
    testAllApproaches(4096, true);     // 2^12
    testAllApproaches(8192, true);     // 2^13
    testAllApproaches(16384, true);    // 2^14
    testAllApproaches(32768, true);    // 2^15
    testAllApproaches(65536, true);    // 2^16
    testAllApproaches(131072, true);   // 2^17
    testAllApproaches(262144, true);   // 2^18
    testAllApproaches(524288, true);   // 2^19
    testAllApproaches(1048576, true);  // 2^20
}

// Test Case 6: Very large powers of 2 (approaching 2^31)
TEST_F(PowerOfTwoTest, VeryLargePowersOfTwo) {
    testAllApproaches(2097152, true);    // 2^21
    testAllApproaches(4194304, true);    // 2^22
    testAllApproaches(8388608, true);    // 2^23
    testAllApproaches(16777216, true);   // 2^24
    testAllApproaches(33554432, true);   // 2^25
    testAllApproaches(67108864, true);   // 2^26
    testAllApproaches(134217728, true);  // 2^27
    testAllApproaches(268435456, true);  // 2^28
    testAllApproaches(536870912, true);  // 2^29
    testAllApproaches(1073741824, true); // 2^30 (largest power of 2 in 32-bit signed int)
}

// Test Case 7: Numbers just above and below powers of 2
TEST_F(PowerOfTwoTest, NumbersAroundPowersOfTwo) {
    // Around 2^4 = 16
    testAllApproaches(15, false);
    testAllApproaches(16, true);
    testAllApproaches(17, false);
    
    // Around 2^6 = 64  
    testAllApproaches(63, false);
    testAllApproaches(64, true);
    testAllApproaches(65, false);
    
    // Around 2^8 = 256
    testAllApproaches(255, false);
    testAllApproaches(256, true);
    testAllApproaches(257, false);
    
    // Around 2^10 = 1024
    testAllApproaches(1023, false);
    testAllApproaches(1024, true);
    testAllApproaches(1025, false);
}

// Test Case 8: Large non-powers of 2
TEST_F(PowerOfTwoTest, LargeNonPowersOfTwo) {
    testAllApproaches(1000, false);
    testAllApproaches(2000, false);
    testAllApproaches(3000, false);
    testAllApproaches(5000, false);
    testAllApproaches(10000, false);
    testAllApproaches(100000, false);
    testAllApproaches(1000000, false);
    testAllApproaches(2000000, false);
}

// Test Case 9: Edge cases at constraint boundaries
TEST_F(PowerOfTwoTest, ConstraintBoundaries) {
    testAllApproaches(1, true);           // Minimum valid power of 2
    testAllApproaches(1073741824, true);  // 2^30, largest power of 2 in range
    testAllApproaches(2147483647, false); // 2^31 - 1, maximum constraint but not power of 2
    testAllApproaches(-2147483648, false); // Minimum constraint
}

// Test Case 10: Common programming numbers that aren't powers of 2
TEST_F(PowerOfTwoTest, CommonNonPowerNumbers) {
    testAllApproaches(100, false);  // Common round number
    testAllApproaches(1000, false); // Common round number
    testAllApproaches(255, false);  // 2^8 - 1, common in byte operations
    testAllApproaches(511, false);  // 2^9 - 1
    testAllApproaches(1023, false); // 2^10 - 1
    testAllApproaches(10, false);   // Decimal base
    testAllApproaches(20, false);   // 2 * 10
    testAllApproaches(50, false);   // 2 * 25
}

// Test Case 11: Numbers that are multiples of powers of 2 but not powers of 2
TEST_F(PowerOfTwoTest, MultiplesOfPowersOfTwo) {
    testAllApproaches(6, false);    // 2 * 3
    testAllApproaches(12, false);   // 4 * 3
    testAllApproaches(24, false);   // 8 * 3
    testAllApproaches(48, false);   // 16 * 3
    testAllApproaches(96, false);   // 32 * 3
    testAllApproaches(192, false);  // 64 * 3
    testAllApproaches(384, false);  // 128 * 3
    testAllApproaches(768, false);  // 256 * 3
}

// Test Case 12: Sequential power checks
TEST_F(PowerOfTwoTest, SequentialPowerChecks) {
    // Check all powers from 2^0 to 2^10
    for (int i = 0; i <= 10; ++i) {
        int power = 1 << i;  // 2^i
        testAllApproaches(power, true);
    }
    
    // Check numbers between consecutive powers
    testAllApproaches(3, false);   // Between 2^1 and 2^2
    testAllApproaches(5, false);   // Between 2^2 and 2^3
    testAllApproaches(6, false);   // Between 2^2 and 2^3
    testAllApproaches(7, false);   // Between 2^2 and 2^3
    testAllApproaches(9, false);   // Between 2^3 and 2^4
    testAllApproaches(15, false);  // Between 2^3 and 2^4
}

// Test Case 13: Bit pattern analysis
TEST_F(PowerOfTwoTest, BitPatternAnalysis) {
    // Powers of 2 have exactly one bit set
    testAllApproaches(1, true);    // 0001
    testAllApproaches(2, true);    // 0010
    testAllApproaches(4, true);    // 0100
    testAllApproaches(8, true);    // 1000
    
    // Non-powers have multiple bits set
    testAllApproaches(3, false);   // 0011 (two bits)
    testAllApproaches(5, false);   // 0101 (two bits)
    testAllApproaches(7, false);   // 0111 (three bits)
    testAllApproaches(15, false);  // 1111 (four bits)
}

// Test Case 14: Mathematical properties
TEST_F(PowerOfTwoTest, MathematicalProperties) {
    // Test that 2^n is always a power of 2
    for (int exp = 0; exp <= 20; ++exp) {
        int power = 1;
        for (int i = 0; i < exp; ++i) {
            power *= 2;
        }
        testAllApproaches(power, true);
    }
}

// Test Case 15: Special mathematical cases
TEST_F(PowerOfTwoTest, SpecialMathematicalCases) {
    // Test that products of two different powers of 2 are also powers of 2
    testAllApproaches(2 * 4, true);    // 8 = 2^3
    testAllApproaches(4 * 8, true);    // 32 = 2^5
    testAllApproaches(8 * 16, true);   // 128 = 2^7
    
    // Test that products with non-powers of 2 are not powers of 2
    testAllApproaches(2 * 3, false);   // 6
    testAllApproaches(4 * 3, false);   // 12
    testAllApproaches(8 * 3, false);   // 24
}

// Test Case 16: Zero and boundary conditions
TEST_F(PowerOfTwoTest, ZeroAndBoundaryConditions) {
    testAllApproaches(0, false);    // Zero is not a power of 2
    testAllApproaches(1, true);     // 2^0 = 1, smallest power of 2
    testAllApproaches(-1, false);   // Negative numbers are not powers of 2
}

// Test Case 17: Performance stress test
TEST_F(PowerOfTwoTest, StressTest) {
    // Test consistency across all approaches for a range of numbers
    std::vector<int> testNumbers = {
        1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 31, 32, 33,
        63, 64, 65, 127, 128, 129, 255, 256, 257, 511, 512, 513,
        1023, 1024, 1025, 2047, 2048, 2049, 100, 1000, 10000
    };
    
    for (int n : testNumbers) {
        bool bitResult = PowerOfTwo::isPowerOfTwoBitManipulation(n);
        bool popCountResult = PowerOfTwo::isPowerOfTwoPopCount(n);
        bool mathResult = PowerOfTwo::isPowerOfTwoMath(n);
        bool divisionResult = PowerOfTwo::isPowerOfTwoDivision(n);
        bool lookupResult = PowerOfTwo::isPowerOfTwoLookup(n);
        bool recursiveResult = PowerOfTwo::isPowerOfTwoRecursive(n);
        
        EXPECT_EQ(bitResult, popCountResult) << "Inconsistency at " << n;
        EXPECT_EQ(bitResult, mathResult) << "Inconsistency at " << n;
        EXPECT_EQ(bitResult, divisionResult) << "Inconsistency at " << n;
        EXPECT_EQ(bitResult, lookupResult) << "Inconsistency at " << n;
        EXPECT_EQ(bitResult, recursiveResult) << "Inconsistency at " << n;
    }
}

// Test Case 18: All powers of 2 in 32-bit range
TEST_F(PowerOfTwoTest, AllPowersOfTwoIn32BitRange) {
    // Test all possible powers of 2 that fit in a 32-bit signed integer
    for (int i = 0; i <= 30; ++i) {
        int power = 1 << i;
        testAllApproaches(power, true);
    }
}

// Test Case 19: Comprehensive non-power validation
TEST_F(PowerOfTwoTest, ComprehensiveNonPowerValidation) {
    // Test a variety of numbers that are definitely not powers of 2
    std::vector<int> nonPowers = {
        3, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23,
        25, 26, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
        50, 60, 70, 80, 90, 99, 100, 101, 110, 111, 120, 121, 130, 140, 150,
        200, 300, 400, 500, 600, 700, 800, 900, 999, 1001, 1111, 2222
    };
    
    for (int n : nonPowers) {
        testAllApproaches(n, false);
    }
}

// Test Case 20: Edge case verification
TEST_F(PowerOfTwoTest, EdgeCaseVerification) {
    // Verify behavior at interesting mathematical boundaries
    testAllApproaches(INT_MAX, false);         // 2^31 - 1
    testAllApproaches(INT_MAX / 2, false);     // Large non-power
    testAllApproaches(1073741824, true);       // 2^30, largest valid power
    testAllApproaches(1073741824 - 1, false); // Just below largest power
    testAllApproaches(1073741824 + 1, false); // Just above largest power
}