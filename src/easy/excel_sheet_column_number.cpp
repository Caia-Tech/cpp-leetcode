#include "excel_sheet_column_number.h"
#include <numeric>

namespace leetcode {
namespace easy {

// Approach 1: Iterative Base-26 Conversion (Optimal)
int ExcelSheetColumnNumber::titleToNumberIterative(std::string columnTitle) {
    int result = 0;
    
    for (char c : columnTitle) {
        result = result * 26 + charToValue(c);
    }
    
    return result;
}

// Approach 2: Recursive Conversion
int ExcelSheetColumnNumber::titleToNumberRecursive(std::string columnTitle) {
    return titleToNumberRecursiveHelper(columnTitle, 0);
}

int ExcelSheetColumnNumber::titleToNumberRecursiveHelper(const std::string& columnTitle, int index) {
    if (index == columnTitle.length()) {
        return 0;
    }
    
    // Process current character and recurse for the rest
    int currentValue = charToValue(columnTitle[index]);
    int remainingValue = titleToNumberRecursiveHelper(columnTitle, index + 1);
    
    // Calculate the contribution of current character
    int powerOf26 = 1;
    for (int i = index + 1; i < columnTitle.length(); i++) {
        powerOf26 *= 26;
    }
    
    return currentValue * powerOf26 + remainingValue;
}

// Approach 3: Mathematical Formula with Power
int ExcelSheetColumnNumber::titleToNumberPower(std::string columnTitle) {
    int result = 0;
    int n = columnTitle.length();
    
    for (int i = 0; i < n; i++) {
        int charValue = charToValue(columnTitle[i]);
        int power = std::pow(26, n - i - 1);
        result += charValue * power;
    }
    
    return result;
}

// Approach 4: Horner's Method
int ExcelSheetColumnNumber::titleToNumberHorner(std::string columnTitle) {
    int result = 0;
    
    // Horner's method: result = (...((a_n * x + a_{n-1}) * x + a_{n-2}) * x + ...) + a_0
    for (char c : columnTitle) {
        result = result * 26 + charToValue(c);
    }
    
    return result;
}

// Approach 5: Bit Manipulation Optimization
int ExcelSheetColumnNumber::titleToNumberBitOptimized(std::string columnTitle) {
    int result = 0;
    
    for (char c : columnTitle) {
        // Optimize multiplication by 26 = 16 + 8 + 2 = 2^4 + 2^3 + 2^1
        // result * 26 = result * (16 + 8 + 2) = (result << 4) + (result << 3) + (result << 1)
        result = (result << 4) + (result << 3) + (result << 1) + charToValue(c);
    }
    
    return result;
}

// Approach 6: Functional Programming with Fold
int ExcelSheetColumnNumber::titleToNumberFunctional(std::string columnTitle) {
    auto accumulator = createAccumulator();
    
    return std::accumulate(
        columnTitle.begin(),
        columnTitle.end(),
        0,
        accumulator
    );
}

std::function<int(int, char)> ExcelSheetColumnNumber::createAccumulator() {
    return [this](int acc, char c) -> int {
        return acc * 26 + charToValue(c);
    };
}

}  // namespace easy
}  // namespace leetcode