#include <gtest/gtest.h>
#include "../../src/easy/excel_sheet_column_title.h"

using namespace leetcode::easy;

// Test fixture for Excel Sheet Column Title
class ExcelSheetColumnTitleTest : public ::testing::Test {
protected:
    void testAllApproaches(int columnNumber, const std::string& expected) {
        EXPECT_EQ(ExcelSheetColumnTitle::convertToTitle(columnNumber), expected) 
            << "Standard approach failed for " << columnNumber;
        EXPECT_EQ(ExcelSheetColumnTitle::convertToTitleRecursive(columnNumber), expected) 
            << "Recursive approach failed for " << columnNumber;
        EXPECT_EQ(ExcelSheetColumnTitle::convertToTitleMath(columnNumber), expected) 
            << "Math approach failed for " << columnNumber;
        EXPECT_EQ(ExcelSheetColumnTitle::convertToTitleStringBuilder(columnNumber), expected) 
            << "String builder approach failed for " << columnNumber;
        EXPECT_EQ(ExcelSheetColumnTitle::convertToTitleReverseBuild(columnNumber), expected) 
            << "Reverse build approach failed for " << columnNumber;
        EXPECT_EQ(ExcelSheetColumnTitle::convertToTitleBijective(columnNumber), expected) 
            << "Bijective approach failed for " << columnNumber;
    }
};

// Test Case 1: Single letter columns (1-26)
TEST_F(ExcelSheetColumnTitleTest, SingleLetterColumns) {
    testAllApproaches(1, "A");
    testAllApproaches(2, "B");
    testAllApproaches(3, "C");
    testAllApproaches(26, "Z");
}

// Test Case 2: LeetCode examples
TEST_F(ExcelSheetColumnTitleTest, LeetCodeExamples) {
    testAllApproaches(1, "A");      // Example 1
    testAllApproaches(28, "AB");    // Example 2  
    testAllApproaches(701, "ZY");   // Example 3
}

// Test Case 3: Two letter columns
TEST_F(ExcelSheetColumnTitleTest, TwoLetterColumns) {
    testAllApproaches(27, "AA");
    testAllApproaches(28, "AB");
    testAllApproaches(52, "AZ");
    testAllApproaches(53, "BA");
    testAllApproaches(702, "ZZ");
}

// Test Case 4: Three letter columns
TEST_F(ExcelSheetColumnTitleTest, ThreeLetterColumns) {
    testAllApproaches(703, "AAA");
    testAllApproaches(704, "AAB");
    testAllApproaches(728, "AAZ");
    testAllApproaches(729, "ABA");
}

// Test Case 5: Boundary cases
TEST_F(ExcelSheetColumnTitleTest, BoundaryCases) {
    testAllApproaches(25, "Y");
    testAllApproaches(26, "Z");
    testAllApproaches(27, "AA");
    testAllApproaches(51, "AY");
    testAllApproaches(52, "AZ");
    testAllApproaches(53, "BA");
}

// Test Case 6: Powers of 26 and nearby values
TEST_F(ExcelSheetColumnTitleTest, PowersOf26) {
    // 26^1 = 26 -> Z
    testAllApproaches(26, "Z");
    
    // 26^1 + 1 = 27 -> AA
    testAllApproaches(27, "AA");
    
    // 26 + 26^2 = 26 + 676 = 702 -> ZZ
    testAllApproaches(702, "ZZ");
    
    // 26 + 26^2 + 1 = 703 -> AAA
    testAllApproaches(703, "AAA");
}

// Test Case 7: Sequential values to verify pattern
TEST_F(ExcelSheetColumnTitleTest, SequentialValues) {
    std::vector<std::pair<int, std::string>> testCases = {
        {1, "A"}, {2, "B"}, {3, "C"}, {4, "D"}, {5, "E"},
        {24, "X"}, {25, "Y"}, {26, "Z"}, {27, "AA"}, {28, "AB"},
        {50, "AX"}, {51, "AY"}, {52, "AZ"}, {53, "BA"}, {54, "BB"}
    };
    
    for (const auto& [num, expected] : testCases) {
        testAllApproaches(num, expected);
    }
}

// Test Case 8: Large values
TEST_F(ExcelSheetColumnTitleTest, LargeValues) {
    testAllApproaches(1000, "ALL");
    testAllApproaches(2000, "BXL");
    testAllApproaches(5000, "GKD");
    testAllApproaches(10000, "NTP");
}

// Test Case 9: Pattern verification for specific ranges
TEST_F(ExcelSheetColumnTitleTest, PatternVerification) {
    // Test AA through AZ (27-52)
    for (int i = 27; i <= 52; ++i) {
        std::string result = ExcelSheetColumnTitle::convertToTitle(i);
        EXPECT_TRUE(result.length() == 2 && result[0] == 'A') 
            << "Pattern failed for " << i << ", got " << result;
    }
    
    // Test BA through BZ (53-78)
    for (int i = 53; i <= 78; ++i) {
        std::string result = ExcelSheetColumnTitle::convertToTitle(i);
        EXPECT_TRUE(result.length() == 2 && result[0] == 'B') 
            << "Pattern failed for " << i << ", got " << result;
    }
}

// Test Case 10: Maximum constraint value
TEST_F(ExcelSheetColumnTitleTest, MaximumValue) {
    // Test with a very large value near the constraint limit
    int maxVal = 2147483647; // 2^31 - 1
    std::string result = ExcelSheetColumnTitle::convertToTitle(maxVal);
    EXPECT_FALSE(result.empty()) << "Failed to handle maximum constraint value";
}

// Test Case 11: Mathematical properties
TEST_F(ExcelSheetColumnTitleTest, MathematicalProperties) {
    // Test that A + 25 = Z
    testAllApproaches(1, "A");
    testAllApproaches(26, "Z");
    
    // Test that Z + 1 = AA
    testAllApproaches(27, "AA");
    
    // Test mathematical consistency
    for (int base = 1; base <= 26; ++base) {
        std::string single = ExcelSheetColumnTitle::convertToTitle(base);
        std::string double_a = ExcelSheetColumnTitle::convertToTitle(base + 26);
        EXPECT_EQ(single.length(), 1) << "Single letter expected for " << base;
        EXPECT_EQ(double_a.length(), 2) << "Double letter expected for " << (base + 26);
        EXPECT_EQ(double_a[0], 'A') << "Second position should start with A";
        EXPECT_EQ(double_a[1], single[0]) << "Pattern mismatch for " << base;
    }
}

// Test Case 12: Edge cases around transitions
TEST_F(ExcelSheetColumnTitleTest, TransitionEdgeCases) {
    // Transitions from single to double letters
    testAllApproaches(26, "Z");
    testAllApproaches(27, "AA");
    
    // Transitions from double to triple letters
    testAllApproaches(702, "ZZ");
    testAllApproaches(703, "AAA");
    
    // Other important transitions
    testAllApproaches(675, "YZ");
    testAllApproaches(676, "ZA");
    testAllApproaches(700, "ZX");
    testAllApproaches(701, "ZY");
}

// Test Case 13: Bijective numeration system properties
TEST_F(ExcelSheetColumnTitleTest, BijectiveProperties) {
    // In bijective base-26, there should be no "zero" character
    // Every valid number should produce a non-empty string
    for (int i = 1; i <= 100; ++i) {
        std::string result = ExcelSheetColumnTitle::convertToTitle(i);
        EXPECT_FALSE(result.empty()) << "Empty result for " << i;
        
        // Check that all characters are valid (A-Z)
        for (char c : result) {
            EXPECT_GE(c, 'A') << "Invalid character in result for " << i;
            EXPECT_LE(c, 'Z') << "Invalid character in result for " << i;
        }
    }
}

// Test Case 14: Consistency across approaches
TEST_F(ExcelSheetColumnTitleTest, ApproachConsistency) {
    // Test that all approaches give identical results for a range of values
    for (int i = 1; i <= 1000; i += 17) { // Test every 17th number for good coverage
        std::string standard = ExcelSheetColumnTitle::convertToTitle(i);
        std::string recursive = ExcelSheetColumnTitle::convertToTitleRecursive(i);
        std::string math = ExcelSheetColumnTitle::convertToTitleMath(i);
        std::string builder = ExcelSheetColumnTitle::convertToTitleStringBuilder(i);
        std::string reverse = ExcelSheetColumnTitle::convertToTitleReverseBuild(i);
        std::string bijective = ExcelSheetColumnTitle::convertToTitleBijective(i);
        
        EXPECT_EQ(standard, recursive) << "Consistency failed at " << i;
        EXPECT_EQ(standard, math) << "Consistency failed at " << i;
        EXPECT_EQ(standard, builder) << "Consistency failed at " << i;
        EXPECT_EQ(standard, reverse) << "Consistency failed at " << i;
        EXPECT_EQ(standard, bijective) << "Consistency failed at " << i;
    }
}

// Test Case 15: Reverse verification
TEST_F(ExcelSheetColumnTitleTest, ReverseVerification) {
    // For small values, verify that the column title makes sense
    std::vector<std::pair<int, std::string>> expected = {
        {1, "A"}, {2, "B"}, {26, "Z"}, {27, "AA"}, {28, "AB"},
        {52, "AZ"}, {53, "BA"}, {78, "BZ"}, {79, "CA"}
    };
    
    for (const auto& [num, title] : expected) {
        testAllApproaches(num, title);
    }
}

