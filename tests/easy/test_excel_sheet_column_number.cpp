#include <gtest/gtest.h>
#include "../../src/easy/excel_sheet_column_number.h"
#include <string>

namespace leetcode {
namespace easy {
namespace test {

class ExcelSheetColumnNumberTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(const std::string& columnTitle, int expected) {
        ExcelSheetColumnNumber solution;
        
        EXPECT_EQ(solution.titleToNumberIterative(columnTitle), expected) 
            << "Iterative failed for input: " << columnTitle;
        
        EXPECT_EQ(solution.titleToNumberRecursive(columnTitle), expected)
            << "Recursive failed for input: " << columnTitle;
        
        EXPECT_EQ(solution.titleToNumberPower(columnTitle), expected)
            << "Power failed for input: " << columnTitle;
        
        EXPECT_EQ(solution.titleToNumberHorner(columnTitle), expected)
            << "Horner's method failed for input: " << columnTitle;
        
        EXPECT_EQ(solution.titleToNumberBitOptimized(columnTitle), expected)
            << "Bit optimized failed for input: " << columnTitle;
        
        EXPECT_EQ(solution.titleToNumberFunctional(columnTitle), expected)
            << "Functional failed for input: " << columnTitle;
    }
};

// LeetCode Example Test Cases

TEST_F(ExcelSheetColumnNumberTest, LeetCodeExample1) {
    // Input: columnTitle = "A"
    // Output: 1
    testAllApproaches("A", 1);
}

TEST_F(ExcelSheetColumnNumberTest, LeetCodeExample2) {
    // Input: columnTitle = "AB"
    // Output: 28
    testAllApproaches("AB", 28);
}

TEST_F(ExcelSheetColumnNumberTest, LeetCodeExample3) {
    // Input: columnTitle = "ZY"
    // Output: 701
    testAllApproaches("ZY", 701);
}

// Single Character Tests

TEST_F(ExcelSheetColumnNumberTest, SingleCharacterA) {
    testAllApproaches("A", 1);
}

TEST_F(ExcelSheetColumnNumberTest, SingleCharacterB) {
    testAllApproaches("B", 2);
}

TEST_F(ExcelSheetColumnNumberTest, SingleCharacterM) {
    testAllApproaches("M", 13);
}

TEST_F(ExcelSheetColumnNumberTest, SingleCharacterZ) {
    testAllApproaches("Z", 26);
}

// Two Character Tests

TEST_F(ExcelSheetColumnNumberTest, TwoCharactersAA) {
    // AA = 1*26 + 1 = 27
    testAllApproaches("AA", 27);
}

TEST_F(ExcelSheetColumnNumberTest, TwoCharactersAZ) {
    // AZ = 1*26 + 26 = 52
    testAllApproaches("AZ", 52);
}

TEST_F(ExcelSheetColumnNumberTest, TwoCharactersBA) {
    // BA = 2*26 + 1 = 53
    testAllApproaches("BA", 53);
}

TEST_F(ExcelSheetColumnNumberTest, TwoCharactersBZ) {
    // BZ = 2*26 + 26 = 78
    testAllApproaches("BZ", 78);
}

TEST_F(ExcelSheetColumnNumberTest, TwoCharactersZA) {
    // ZA = 26*26 + 1 = 677
    testAllApproaches("ZA", 677);
}

TEST_F(ExcelSheetColumnNumberTest, TwoCharactersZZ) {
    // ZZ = 26*26 + 26 = 702
    testAllApproaches("ZZ", 702);
}

// Three Character Tests

TEST_F(ExcelSheetColumnNumberTest, ThreeCharactersAAA) {
    // AAA = 1*26^2 + 1*26 + 1 = 676 + 26 + 1 = 703
    testAllApproaches("AAA", 703);
}

TEST_F(ExcelSheetColumnNumberTest, ThreeCharactersAAZ) {
    // AAZ = 1*26^2 + 1*26 + 26 = 676 + 26 + 26 = 728
    testAllApproaches("AAZ", 728);
}

TEST_F(ExcelSheetColumnNumberTest, ThreeCharactersABA) {
    // ABA = 1*26^2 + 2*26 + 1 = 676 + 52 + 1 = 729
    testAllApproaches("ABA", 729);
}

TEST_F(ExcelSheetColumnNumberTest, ThreeCharactersAZZ) {
    // AZZ = 1*26^2 + 26*26 + 26 = 676 + 676 + 26 = 1378
    testAllApproaches("AZZ", 1378);
}

TEST_F(ExcelSheetColumnNumberTest, ThreeCharactersBAA) {
    // BAA = 2*26^2 + 1*26 + 1 = 1352 + 26 + 1 = 1379
    testAllApproaches("BAA", 1379);
}

TEST_F(ExcelSheetColumnNumberTest, ThreeCharactersZZZ) {
    // ZZZ = 26*26^2 + 26*26 + 26 = 17576 + 676 + 26 = 18278
    testAllApproaches("ZZZ", 18278);
}

// Four Character Tests

TEST_F(ExcelSheetColumnNumberTest, FourCharactersAAAA) {
    // AAAA = 1*26^3 + 1*26^2 + 1*26 + 1 = 17576 + 676 + 26 + 1 = 18279
    testAllApproaches("AAAA", 18279);
}

TEST_F(ExcelSheetColumnNumberTest, FourCharactersABCD) {
    // ABCD = 1*26^3 + 2*26^2 + 3*26 + 4 = 17576 + 1352 + 78 + 4 = 19010
    testAllApproaches("ABCD", 19010);
}

TEST_F(ExcelSheetColumnNumberTest, FourCharactersZZZZ) {
    // ZZZZ = 26*26^3 + 26*26^2 + 26*26 + 26 = 456976 + 17576 + 676 + 26 = 475254
    testAllApproaches("ZZZZ", 475254);
}

// Pattern Tests

TEST_F(ExcelSheetColumnNumberTest, SequentialPatternABC) {
    // ABC = 1*26^2 + 2*26 + 3 = 676 + 52 + 3 = 731
    testAllApproaches("ABC", 731);
}

TEST_F(ExcelSheetColumnNumberTest, SequentialPatternDEF) {
    // DEF = 4*26^2 + 5*26 + 6 = 2704 + 130 + 6 = 2840
    testAllApproaches("DEF", 2840);
}

TEST_F(ExcelSheetColumnNumberTest, SequentialPatternXYZ) {
    // XYZ = 24*26^2 + 25*26 + 26 = 16224 + 650 + 26 = 16900
    testAllApproaches("XYZ", 16900);
}

TEST_F(ExcelSheetColumnNumberTest, RepeatingPatternCCC) {
    // CCC = 3*26^2 + 3*26 + 3 = 2028 + 78 + 3 = 2109
    testAllApproaches("CCC", 2109);
}

TEST_F(ExcelSheetColumnNumberTest, AlternatingPatternABAB) {
    // ABAB = 1*26^3 + 2*26^2 + 1*26 + 2 = 17576 + 1352 + 26 + 2 = 18956
    testAllApproaches("ABAB", 18956);
}

// Five Character Tests

TEST_F(ExcelSheetColumnNumberTest, FiveCharactersAAAAA) {
    // AAAAA = 26^4 + 26^3 + 26^2 + 26 + 1 = 456976 + 17576 + 676 + 26 + 1 = 475255
    testAllApproaches("AAAAA", 475255);
}

TEST_F(ExcelSheetColumnNumberTest, FiveCharactersABCDE) {
    // ABCDE = 1*26^4 + 2*26^3 + 3*26^2 + 4*26 + 5
    // = 456976 + 35152 + 2028 + 104 + 5 = 494265
    testAllApproaches("ABCDE", 494265);
}

TEST_F(ExcelSheetColumnNumberTest, FiveCharactersZZZZZ) {
    // ZZZZZ = 26*26^4 + 26*26^3 + 26*26^2 + 26*26 + 26
    // = 11881376 + 456976 + 17576 + 676 + 26 = 12356630
    testAllApproaches("ZZZZZ", 12356630);
}

// Six Character Tests

TEST_F(ExcelSheetColumnNumberTest, SixCharactersAAAAAA) {
    // AAAAAA = 26^5 + 26^4 + 26^3 + 26^2 + 26 + 1
    // = 11881376 + 456976 + 17576 + 676 + 26 + 1 = 12356631
    testAllApproaches("AAAAAA", 12356631);
}

TEST_F(ExcelSheetColumnNumberTest, SixCharactersABCDEF) {
    // ABCDEF = 1*26^5 + 2*26^4 + 3*26^3 + 4*26^2 + 5*26 + 6
    // = 11881376 + 913952 + 52728 + 2704 + 130 + 6 = 12850896
    testAllApproaches("ABCDEF", 12850896);
}

// Seven Character Tests (Maximum Length)

TEST_F(ExcelSheetColumnNumberTest, SevenCharactersAAAAAAA) {
    // AAAAAAA = 26^6 + 26^5 + 26^4 + 26^3 + 26^2 + 26 + 1
    // = 308915776 + 11881376 + 456976 + 17576 + 676 + 26 + 1 = 321272407
    testAllApproaches("AAAAAAA", 321272407);
}

TEST_F(ExcelSheetColumnNumberTest, SevenCharactersMaximum) {
    // FXSHRXW - Maximum constraint value
    // F=6, X=24, S=19, H=8, R=18, X=24, W=23
    // = 6*26^6 + 24*26^5 + 19*26^4 + 8*26^3 + 18*26^2 + 24*26 + 23
    // = 1853494656 + 285153024 + 8682544 + 140608 + 12168 + 624 + 23
    testAllApproaches("FXSHRXW", 2147483647);
}

// Special Patterns

TEST_F(ExcelSheetColumnNumberTest, FirstLetterOfEachGroup) {
    // Test first letter after each "wrap"
    testAllApproaches("A", 1);      // First single letter
    testAllApproaches("AA", 27);     // First double letter
    testAllApproaches("AAA", 703);   // First triple letter
}

TEST_F(ExcelSheetColumnNumberTest, LastLetterOfEachGroup) {
    // Test last letter before each "wrap"
    testAllApproaches("Z", 26);      // Last single letter
    testAllApproaches("ZZ", 702);    // Last double letter
    testAllApproaches("ZZZ", 18278); // Last triple letter
}

TEST_F(ExcelSheetColumnNumberTest, MiddleValues) {
    // Test middle values in different ranges
    testAllApproaches("N", 14);      // Middle of single letters
    testAllApproaches("MN", 352);    // M=13, N=14: 13*26 + 14 = 352
    testAllApproaches("MMM", 9139);  // M=13: 13*26^2 + 13*26 + 13 = 8788 + 338 + 13 = 9139
}

// Boundary Cases

TEST_F(ExcelSheetColumnNumberTest, MinimumConstraint) {
    // Minimum valid input
    testAllApproaches("A", 1);
}

TEST_F(ExcelSheetColumnNumberTest, PowersOf26) {
    // Test exact powers of 26
    testAllApproaches("Z", 26);          // 26^1
    testAllApproaches("AZ", 52);         // 2 * 26
    testAllApproaches("YZ", 676);        // 26^2
}

// Incremental Sequences

TEST_F(ExcelSheetColumnNumberTest, IncrementalSingleLetters) {
    // Test consecutive single letters
    testAllApproaches("A", 1);
    testAllApproaches("B", 2);
    testAllApproaches("C", 3);
    testAllApproaches("D", 4);
    testAllApproaches("E", 5);
}

TEST_F(ExcelSheetColumnNumberTest, IncrementalDoubleLetters) {
    // Test transition from single to double letters
    testAllApproaches("Y", 25);
    testAllApproaches("Z", 26);
    testAllApproaches("AA", 27);
    testAllApproaches("AB", 28);
    testAllApproaches("AC", 29);
}

TEST_F(ExcelSheetColumnNumberTest, IncrementalTripleLetters) {
    // Test transition from double to triple letters
    testAllApproaches("ZX", 700);
    testAllApproaches("ZY", 701);
    testAllApproaches("ZZ", 702);
    testAllApproaches("AAA", 703);
    testAllApproaches("AAB", 704);
}

// Mathematical Properties

TEST_F(ExcelSheetColumnNumberTest, Base26Properties) {
    // Verify base-26 calculation properties
    // BA should equal B*26 + A = 2*26 + 1 = 53
    testAllApproaches("BA", 53);
    
    // CA should equal C*26 + A = 3*26 + 1 = 79
    testAllApproaches("CA", 79);
    
    // CB should equal C*26 + B = 3*26 + 2 = 80
    testAllApproaches("CB", 80);
}

TEST_F(ExcelSheetColumnNumberTest, SymmetricPatterns) {
    // Test symmetric patterns
    testAllApproaches("AZA", 1353);  // A=1, Z=26, A=1: 1*26^2 + 26*26 + 1 = 676 + 676 + 1 = 1353
    testAllApproaches("ZAZ", 17628); // Z=26, A=1, Z=26: 26*26^2 + 1*26 + 26 = 17576 + 26 + 26 = 17628
}

// Complex Cases

TEST_F(ExcelSheetColumnNumberTest, MixedPatterns) {
    // Mixed high and low letters
    // AZBY: A=1, Z=26, B=2, Y=25: 1*26^3 + 26*26^2 + 2*26 + 25 = 17576 + 17576 + 52 + 25 = 35229
    testAllApproaches("AZBY", 35229);
    // HIGH: H=8, I=9, G=7, H=8: 8*26^3 + 9*26^2 + 7*26 + 8 = 140608 + 6084 + 182 + 8 = 146882
    testAllApproaches("HIGH", 146882);
    // LOW: L=12, O=15, W=23: 12*26^2 + 15*26 + 23 = 8112 + 390 + 23 = 8525
    testAllApproaches("LOW", 8525);
}

TEST_F(ExcelSheetColumnNumberTest, RealWorldExamples) {
    // Common Excel column references
    testAllApproaches("IV", 256);    // Common last column in old Excel
    testAllApproaches("XFD", 16384); // Last column in modern Excel
}

// Stress Tests

TEST_F(ExcelSheetColumnNumberTest, LongRandomPattern) {
    // Random pattern of maximum length
    // BCDGFAE: B=2, C=3, D=4, G=7, F=6, A=1, E=5
    // = 2*26^6 + 3*26^5 + 4*26^4 + 7*26^3 + 6*26^2 + 1*26 + 5
    // = 617831552 + 35644128 + 1827904 + 123032 + 4056 + 26 + 5 = 655430703
    testAllApproaches("BCDGFAE", 655430703);
}

TEST_F(ExcelSheetColumnNumberTest, AlmostMaximum) {
    // One less than maximum
    testAllApproaches("FXSHRXV", 2147483646);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode