#include "excel_sheet_column_title.h"
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: Iterative Division (Standard)
// Detailed Reasoning: This is similar to base conversion but with a twist. Excel columns
// use 1-based indexing (A=1, B=2, ..., Z=26) rather than 0-based. We need to adjust
// for this by subtracting 1 before each division to handle the 1-based system correctly.
std::string ExcelSheetColumnTitle::convertToTitle(int columnNumber) {
    std::string result;
    
    while (columnNumber > 0) {
        // Adjust for 1-based indexing: subtract 1 to make it 0-based
        columnNumber--;
        
        // Get the character (A-Z corresponds to 0-25)
        result = char('A' + columnNumber % 26) + result;
        
        // Move to next position
        columnNumber /= 26;
    }
    
    return result;
}

// Approach 2: Recursive Approach
// Detailed Reasoning: Break down the problem recursively. For each position,
// determine what character belongs there and recursively solve for the remaining
// positions. This provides a clean, mathematical approach to the problem.
std::string ExcelSheetColumnTitle::convertToTitleRecursive(int columnNumber) {
    return convertRecursiveHelper(columnNumber);
}

// Approach 3: Mathematical Formula
// Detailed Reasoning: Calculate the exact position and value for each character
// using mathematical properties. This approach computes the result directly
// without iterative refinement, making it very efficient.
std::string ExcelSheetColumnTitle::convertToTitleMath(int columnNumber) {
    std::string result;
    int num = columnNumber;
    
    // Calculate number of digits first
    int digits = 0;
    long long temp = num;
    long long base = 26;
    
    while (temp > 0) {
        temp = (temp - 1) / base;
        digits++;
    }
    
    // Build result from most significant to least significant digit
    for (int i = digits - 1; i >= 0; i--) {
        long long position_value = power26(i);
        int char_index = ((num - 1) / position_value) % 26;
        result += char('A' + char_index);
        num -= (char_index + 1) * position_value;
    }
    
    return result;
}

// Approach 4: String Building
// Detailed Reasoning: Build the string character by character, maintaining
// the relationship between position and character value. This approach is
// intuitive and easy to understand, making it good for educational purposes.
std::string ExcelSheetColumnTitle::convertToTitleStringBuilder(int columnNumber) {
    std::string result;
    int num = columnNumber;
    
    while (num > 0) {
        // Find the rightmost character
        int remainder = (num - 1) % 26;  // Adjust for 1-based indexing
        char ch = 'A' + remainder;
        
        // Prepend to result (building from right to left)
        result = ch + result;
        
        // Update num for next iteration
        num = (num - 1) / 26;
    }
    
    return result;
}

// Approach 5: Reverse and Build
// Detailed Reasoning: Build the string in reverse order (which is more natural
// for this algorithm) and then reverse the final result. This can be more
// efficient than prepending characters and is easier to understand.
std::string ExcelSheetColumnTitle::convertToTitleReverseBuild(int columnNumber) {
    std::string result;
    int num = columnNumber;
    
    // Build string in reverse order
    while (num > 0) {
        num--;  // Adjust for 1-based indexing
        result += char('A' + num % 26);
        num /= 26;
    }
    
    // Reverse to get correct order
    std::reverse(result.begin(), result.end());
    return result;
}

// Approach 6: Bijective Base-26 Conversion
// Detailed Reasoning: Excel columns form a bijective base-26 numeration system.
// Unlike standard positional systems, there's no zero digit. This approach
// treats the problem as a direct bijective base conversion.
std::string ExcelSheetColumnTitle::convertToTitleBijective(int columnNumber) {
    std::string result;
    
    while (columnNumber > 0) {
        // In bijective base-26, digits are 1-26 (A-Z)
        char digit = bijectiveDigit(columnNumber);
        result = digit + result;
        
        // Update for next position in bijective system
        columnNumber = (columnNumber - 1) / 26;
    }
    
    return result;
}

// Helper function for recursive approach
std::string ExcelSheetColumnTitle::convertRecursiveHelper(int num) {
    if (num == 0) return "";
    
    num--;  // Adjust for 1-based indexing
    return convertRecursiveHelper(num / 26) + char('A' + num % 26);
}

// Helper function to get character at position
char ExcelSheetColumnTitle::getCharAt(int position) {
    return 'A' + position;
}

// Helper function to calculate power of 26
long long ExcelSheetColumnTitle::power26(int exponent) {
    long long result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= 26;
    }
    return result;
}

// Helper function for bijective base conversion
char ExcelSheetColumnTitle::bijectiveDigit(int num) {
    int remainder = (num - 1) % 26 + 1;  // Get digit in range [1, 26]
    return 'A' + remainder - 1;          // Convert to character
}

} // namespace easy
} // namespace leetcode