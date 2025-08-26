#pragma once

#ifndef LEETCODE_EASY_EXCEL_SHEET_COLUMN_TITLE_H
#define LEETCODE_EASY_EXCEL_SHEET_COLUMN_TITLE_H

#include <string>
#include <vector>

namespace leetcode {
namespace easy {

// Problem 168: Excel Sheet Column Title
// Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.
//
// For example:
// A -> 1, B -> 2, C -> 3, ..., Z -> 26, AA -> 27, AB -> 28, ...
//
// Example 1:
// Input: columnNumber = 1
// Output: "A"
//
// Example 2:
// Input: columnNumber = 28
// Output: "AB"
//
// Example 3:
// Input: columnNumber = 701
// Output: "ZY"
//
// Constraints: 1 <= columnNumber <= 2^31 - 1
//
// This class implements 6 different algorithmic approaches:
// 1. Iterative Division: Standard base-26-like conversion with adjustment
// 2. Recursive Approach: Recursive divide-and-conquer method
// 3. Mathematical Formula: Direct calculation using position values
// 4. String Building: Build string character by character
// 5. Reverse and Build: Build in reverse order then reverse the result
// 6. Bijective Base-26: Treat as bijective numeration system

class ExcelSheetColumnTitle {
public:
    // Approach 1: Iterative Division (Standard)
    // Time: O(log₂₆(n)), Space: O(1) excluding output
    // Convert number to base-26 like system with 1-based indexing
    static std::string convertToTitle(int columnNumber);
    
    // Approach 2: Recursive Approach
    // Time: O(log₂₆(n)), Space: O(log₂₆(n)) for recursion stack
    // Use recursion to break down the problem into smaller subproblems
    static std::string convertToTitleRecursive(int columnNumber);
    
    // Approach 3: Mathematical Formula
    // Time: O(log₂₆(n)), Space: O(1) excluding output
    // Use mathematical properties to directly compute each character
    static std::string convertToTitleMath(int columnNumber);
    
    // Approach 4: String Building
    // Time: O(log₂₆(n)), Space: O(log₂₆(n))
    // Build the string character by character from right to left
    static std::string convertToTitleStringBuilder(int columnNumber);
    
    // Approach 5: Reverse and Build
    // Time: O(log₂₆(n)), Space: O(log₂₆(n))
    // Build string in reverse order then reverse the final result
    static std::string convertToTitleReverseBuild(int columnNumber);
    
    // Approach 6: Bijective Base-26 Conversion
    // Time: O(log₂₆(n)), Space: O(1) excluding output
    // Treat Excel columns as bijective base-26 numeration system
    static std::string convertToTitleBijective(int columnNumber);

private:
    // Helper function for recursive approach
    static std::string convertRecursiveHelper(int num);
    
    // Helper function to get character for a given position (0-based)
    static char getCharAt(int position);
    
    // Helper function to calculate power of 26
    static long long power26(int exponent);
    
    // Helper function for bijective base conversion
    static char bijectiveDigit(int num);
};

} // namespace easy
} // namespace leetcode

#endif // LEETCODE_EASY_EXCEL_SHEET_COLUMN_TITLE_H