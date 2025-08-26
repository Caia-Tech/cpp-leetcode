#include <gtest/gtest.h>
#include "../../src/easy/happy_number.h"

using namespace leetcode::easy;

// Test fixture for Happy Number
class HappyNumberTest : public ::testing::Test {
protected:
    void testAllApproaches(int n, bool expected) {
        EXPECT_EQ(HappyNumber::isHappySet(n), expected) 
            << "Set approach failed for " << n;
        EXPECT_EQ(HappyNumber::isHappyFloyd(n), expected) 
            << "Floyd approach failed for " << n;
        EXPECT_EQ(HappyNumber::isHappyMathematical(n), expected) 
            << "Mathematical approach failed for " << n;
        EXPECT_EQ(HappyNumber::isHappyMemoized(n), expected) 
            << "Memoized approach failed for " << n;
        EXPECT_EQ(HappyNumber::isHappyLimited(n), expected) 
            << "Limited approach failed for " << n;
        EXPECT_EQ(HappyNumber::isHappyBrent(n), expected) 
            << "Brent approach failed for " << n;
    }
};

// Test Case 1: LeetCode examples
TEST_F(HappyNumberTest, LeetCodeExamples) {
    // Example 1: n = 19 → 82 → 68 → 100 → 1
    testAllApproaches(19, true);
    
    // Example 2: n = 2 (eventually cycles)
    testAllApproaches(2, false);
}

// Test Case 2: Single digit happy numbers
TEST_F(HappyNumberTest, SingleDigitHappyNumbers) {
    testAllApproaches(1, true);   // 1 is trivially happy
    testAllApproaches(7, true);   // 7 → 49 → 97 → 130 → 10 → 1
}

// Test Case 3: Single digit unhappy numbers
TEST_F(HappyNumberTest, SingleDigitUnhappyNumbers) {
    testAllApproaches(2, false);  // Eventually cycles
    testAllApproaches(3, false);  // Eventually cycles
    testAllApproaches(4, false);  // Part of the main cycle
    testAllApproaches(5, false);  // Eventually cycles
    testAllApproaches(6, false);  // Eventually cycles
    testAllApproaches(8, false);  // Eventually cycles
    testAllApproaches(9, false);  // Eventually cycles
}

// Test Case 4: Two digit happy numbers
TEST_F(HappyNumberTest, TwoDigitHappyNumbers) {
    testAllApproaches(10, true);  // 10 → 1 → 1
    testAllApproaches(13, true);  // 13 → 10 → 1
    testAllApproaches(19, true);  // Classic example
    testAllApproaches(23, true);  // 23 → 13 → 10 → 1
    testAllApproaches(28, true);  // 28 → 68 → 100 → 1
    testAllApproaches(44, true);  // 44 → 32 → 13 → 10 → 1
    testAllApproaches(49, true);  // 49 → 97 → 130 → 10 → 1
    testAllApproaches(68, true);  // 68 → 100 → 1
    testAllApproaches(70, true);  // 70 → 49 → 97 → 130 → 10 → 1
    testAllApproaches(79, true);  // 79 → 130 → 10 → 1
    testAllApproaches(82, true);  // 82 → 68 → 100 → 1
    testAllApproaches(86, true);  // 86 → 100 → 1
    testAllApproaches(91, true);  // 91 → 82 → 68 → 100 → 1
    testAllApproaches(94, true);  // 94 → 97 → 130 → 10 → 1
    testAllApproaches(97, true);  // 97 → 130 → 10 → 1
}

// Test Case 5: Two digit unhappy numbers
TEST_F(HappyNumberTest, TwoDigitUnhappyNumbers) {
    testAllApproaches(11, false); // Eventually cycles
    testAllApproaches(12, false); // Eventually cycles  
    testAllApproaches(14, false); // Eventually cycles
    testAllApproaches(15, false); // Eventually cycles
    testAllApproaches(16, false); // Part of main cycle
    testAllApproaches(17, false); // Eventually cycles
    testAllApproaches(18, false); // Eventually cycles
    testAllApproaches(20, false); // Part of main cycle
    testAllApproaches(21, false); // Eventually cycles
    testAllApproaches(22, false); // Eventually cycles
}

// Test Case 6: Three digit happy numbers
TEST_F(HappyNumberTest, ThreeDigitHappyNumbers) {
    testAllApproaches(100, true); // 100 → 1
    testAllApproaches(103, true); // 103 → 10 → 1
    testAllApproaches(109, true); // 109 → 82 → 68 → 100 → 1
    testAllApproaches(129, true); // 129 → 86 → 100 → 1
    testAllApproaches(130, true); // 130 → 10 → 1
    testAllApproaches(133, true); // 133 → 19 → 82 → 68 → 100 → 1
    testAllApproaches(139, true); // 139 → 91 → 82 → 68 → 100 → 1
    testAllApproaches(167, true); // 167 → 86 → 100 → 1
    testAllApproaches(176, true); // 176 → 86 → 100 → 1
    testAllApproaches(188, true); // 188 → 129 → 86 → 100 → 1
}

// Test Case 7: Numbers that quickly enter the unhappy cycle
TEST_F(HappyNumberTest, UnhappyCycleNumbers) {
    // All numbers in the main unhappy cycle
    testAllApproaches(4, false);   // 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4
    testAllApproaches(16, false);  // 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 → 16
    testAllApproaches(37, false);  // 37 → 58 → 89 → 145 → 42 → 20 → 4 → 16 → 37
    testAllApproaches(58, false);  // And so on...
    testAllApproaches(89, false);
    testAllApproaches(145, false);
    testAllApproaches(42, false);
    testAllApproaches(20, false);
}

// Test Case 8: Large happy numbers (corrected)
TEST_F(HappyNumberTest, LargeHappyNumbers) {
    testAllApproaches(1000, true); // 1000 → 1
    testAllApproaches(1003, true); // 1003 → 10 → 1
    testAllApproaches(1300, true); // 1300 → 10 → 1
}

// Fix the above test - 1111 is actually unhappy
TEST_F(HappyNumberTest, LargeHappyNumbersCorrected) {
    testAllApproaches(1000, true); // 1000 → 1
    testAllApproaches(1003, true); // 1003 → 10 → 1
    testAllApproaches(1111, false); // 1111 → 4 → [unhappy cycle]
}

// Test Case 9: Large unhappy numbers
TEST_F(HappyNumberTest, LargeUnhappyNumbers) {
    testAllApproaches(999, false);  // Eventually cycles
    testAllApproaches(1234, false); // Eventually cycles
    testAllApproaches(5678, false); // Eventually cycles
}

// Test Case 10: Powers of 10
TEST_F(HappyNumberTest, PowersOfTen) {
    testAllApproaches(1, true);     // 10^0
    testAllApproaches(10, true);    // 10^1 → 1
    testAllApproaches(100, true);   // 10^2 → 1
    testAllApproaches(1000, true);  // 10^3 → 1
    testAllApproaches(10000, true); // 10^4 → 1
}

// Test Case 11: Numbers with repeated digits
TEST_F(HappyNumberTest, RepeatedDigits) {
    testAllApproaches(11, false);   // 11 → 2 → [unhappy]
    testAllApproaches(22, false);   // 22 → 8 → [unhappy]
    testAllApproaches(33, false);   // 33 → 18 → [unhappy]
    testAllApproaches(44, true);    // 44 → 32 → 13 → 10 → 1
    testAllApproaches(55, false);   // 55 → 50 → [unhappy]
    testAllApproaches(66, false);   // 66 → 72 → [unhappy]
    testAllApproaches(77, false);   // 77 → 98 → [unhappy]
    testAllApproaches(88, false);   // 88 → 128 → [unhappy]
    testAllApproaches(99, false);   // 99 → 162 → [unhappy]
}

// Test Case 12: Edge cases around constraint boundaries
TEST_F(HappyNumberTest, ConstraintBoundaries) {
    testAllApproaches(1, true);           // Minimum constraint
    testAllApproaches(2147483647, false); // Maximum constraint (2^31 - 1)
}

// Test Case 13: Numbers that take longer to resolve
TEST_F(HappyNumberTest, SlowConvergingNumbers) {
    testAllApproaches(9999, false);       // Takes several iterations
    testAllApproaches(99999, false);      // Takes even more iterations
    testAllApproaches(139, true);         // Takes multiple steps to reach 1
}

// Test Case 14: Sequential ranges
TEST_F(HappyNumberTest, SequentialRange1to20) {
    // Known results for 1-20
    bool expected[21] = {
        false, // 0 (not used)
        true,  // 1
        false, // 2
        false, // 3
        false, // 4
        false, // 5
        false, // 6
        true,  // 7
        false, // 8
        false, // 9
        true,  // 10
        false, // 11
        false, // 12
        true,  // 13
        false, // 14
        false, // 15
        false, // 16
        false, // 17
        false, // 18
        true,  // 19
        false  // 20
    };
    
    for (int i = 1; i <= 20; ++i) {
        testAllApproaches(i, expected[i]);
    }
}

// Test Case 15: Pattern verification
TEST_F(HappyNumberTest, HappyNumberPatterns) {
    // Numbers ending in 0 often tend to be happy (if they have a 1)
    testAllApproaches(10, true);
    testAllApproaches(100, true);
    testAllApproaches(1000, true);
    
    // But not always
    testAllApproaches(20, false);
    testAllApproaches(30, false);
}

// Test Case 16: Mathematical properties
TEST_F(HappyNumberTest, MathematicalProperties) {
    // If a number is happy, adding leading zeros doesn't change it
    testAllApproaches(1, true);
    testAllApproaches(10, true);
    testAllApproaches(100, true);
    testAllApproaches(1000, true);
    
    // Sum of squares property: order of digits doesn't matter
    testAllApproaches(19, true);
    testAllApproaches(91, true); // Same sum of squares as 19
}

// Test Case 17: Performance stress test
TEST_F(HappyNumberTest, StressTest) {
    // Test a range of numbers to ensure all approaches work consistently
    for (int i = 1; i <= 100; i += 7) { // Test every 7th number for good coverage
        bool setResult = HappyNumber::isHappySet(i);
        bool floydResult = HappyNumber::isHappyFloyd(i);
        bool mathResult = HappyNumber::isHappyMathematical(i);
        bool memoResult = HappyNumber::isHappyMemoized(i);
        bool limitResult = HappyNumber::isHappyLimited(i);
        bool brentResult = HappyNumber::isHappyBrent(i);
        
        EXPECT_EQ(setResult, floydResult) << "Inconsistency at " << i;
        EXPECT_EQ(setResult, mathResult) << "Inconsistency at " << i;
        EXPECT_EQ(setResult, memoResult) << "Inconsistency at " << i;
        EXPECT_EQ(setResult, limitResult) << "Inconsistency at " << i;
        EXPECT_EQ(setResult, brentResult) << "Inconsistency at " << i;
    }
}

// Test Case 18: Cycle detection verification
TEST_F(HappyNumberTest, CycleDetectionVerification) {
    // Verify that all cycle detection methods work correctly
    // Test with a known unhappy number that enters cycle quickly
    testAllApproaches(4, false);  // Enters main cycle immediately
    testAllApproaches(145, false); // Also in main cycle
}

// Test Case 19: Happy number sequences  
TEST_F(HappyNumberTest, HappySequences) {
    // Some numbers that follow paths to happiness
    testAllApproaches(7, true);    // 7 → 49 → 97 → 130 → 10 → 1
    testAllApproaches(49, true);   // 49 → 97 → 130 → 10 → 1  
    testAllApproaches(97, true);   // 97 → 130 → 10 → 1
    testAllApproaches(130, true);  // 130 → 10 → 1
}

// Test Case 20: Comprehensive validation
TEST_F(HappyNumberTest, ComprehensiveValidation) {
    // Test a selection of numbers with known results
    std::vector<std::pair<int, bool>> testCases = {
        {1, true}, {7, true}, {10, true}, {13, true}, {19, true},
        {23, true}, {28, true}, {44, true}, {49, true}, {68, true},
        {70, true}, {79, true}, {82, true}, {86, true}, {91, true},
        {94, true}, {97, true}, {100, true}, {103, true}, {109, true},
        {129, true}, {130, true}, {133, true}, {139, true}, {167, true},
        {176, true}, {188, true}, {190, true}, {192, true}, {193, true},
        {2, false}, {3, false}, {4, false}, {5, false}, {6, false},
        {8, false}, {9, false}, {11, false}, {12, false}, {14, false},
        {15, false}, {16, false}, {17, false}, {18, false}, {20, false},
        {21, false}, {22, false}, {24, false}, {25, false}, {26, false}
    };
    
    for (const auto& [num, expected] : testCases) {
        testAllApproaches(num, expected);
    }
}

