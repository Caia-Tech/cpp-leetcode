#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace leetcode {
namespace medium {

/**
 * Problem 12: Integer to Roman
 * 
 * Seven different symbols represent Roman numerals with the following values:
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * 
 * Roman numerals are formed by combining symbols and adding the values. However, 
 * in a few specific cases, subtraction is used instead of addition, and the smaller 
 * symbol is written in front of the larger one.
 * 
 * Given an integer, convert it to a roman numeral.
 * 
 * Constraints:
 * - 1 <= num <= 3999
 */
class IntegerToRoman {
public:
    /**
     * Approach 1: Greedy with Value-Symbol Mapping (Optimal)
     * 
     * Use greedy approach with predefined value-symbol pairs including subtractive cases.
     * 
     * Reasoning: This is the optimal approach. Create a mapping of values to Roman symbols
     * in descending order, including the subtractive cases (IV=4, IX=9, XL=40, etc.).
     * Greedily use the largest possible value at each step. This naturally handles
     * both additive and subtractive cases without special logic. The greedy choice
     * is always optimal because Roman numerals follow strict precedence rules.
     * 
     * Time Complexity: O(1) - at most 13 symbol pairs to process
     * Space Complexity: O(1) - constant size mapping array
     * 
     * Best when: Need optimal performance, clean implementation
     * Worst when: Want to understand individual digit processing
     */
    std::string intToRomanGreedy(int num);

    /**
     * Approach 2: Digit-by-Digit Processing
     * 
     * Process each digit (thousands, hundreds, tens, ones) separately.
     * 
     * Reasoning: Break down the number into individual digits and convert each
     * digit to its Roman representation based on its place value. For each place
     * (thousands, hundreds, tens, ones), have specific conversion rules. This
     * approach makes the digit-wise conversion logic very explicit and easy to
     * understand, though it requires more code for each digit position.
     * 
     * Time Complexity: O(1) - fixed number of digits to process
     * Space Complexity: O(1) - constant space for digit conversion tables
     * 
     * Best when: Want explicit digit handling, educational purposes
     * Worst when: Concise code is preferred over explicit digit logic
     */
    std::string intToRomanDigitByDigit(int num);

    /**
     * Approach 3: Lookup Table with Modular Arithmetic
     * 
     * Use lookup tables for each decimal place with modular arithmetic.
     * 
     * Reasoning: Create lookup tables for ones, tens, hundreds, and thousands
     * place values. Use modular arithmetic to extract each digit and index
     * into the appropriate lookup table. This approach separates the Roman
     * numeral patterns from the number decomposition logic, making it very
     * systematic and expandable.
     * 
     * Time Complexity: O(1) - constant number of operations
     * Space Complexity: O(1) - fixed size lookup tables
     * 
     * Best when: Want systematic table-driven approach, easy to extend
     * Worst when: Memory usage needs to be absolutely minimized
     */
    std::string intToRomanLookupTable(int num);

    /**
     * Approach 4: Recursive Decomposition
     * 
     * Recursively break down number using largest possible Roman values.
     * 
     * Reasoning: Recursively find the largest Roman value that fits into the
     * current number, append its symbol, and recursively process the remainder.
     * Base case is when number becomes 0. This approach demonstrates recursive
     * thinking and naturally follows the greedy strategy, but has function call
     * overhead that's unnecessary for this problem.
     * 
     * Time Complexity: O(1) - bounded by maximum Roman numeral length
     * Space Complexity: O(1) - recursion depth is bounded by ~13 calls
     * 
     * Best when: Recursive approach is preferred, educational recursion
     * Worst when: Iterative solution is simpler and more efficient
     */
    std::string intToRomanRecursive(int num);

    /**
     * Approach 5: String Building with Repetition
     * 
     * Build Roman numeral by repeating symbols based on quotient and remainder.
     * 
     * Reasoning: For each Roman value (M, CM, D, CD, C, XC, L, XL, X, IX, V, IV, I),
     * calculate how many times it fits into the remaining number and append that
     * many symbols. Use division to get count and modulo to get remainder. This
     * approach makes the repetition aspect very explicit and is easy to understand.
     * 
     * Time Complexity: O(1) - bounded by total Roman numeral length
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Want explicit repetition counting, clear mathematical approach
     * Worst when: Direct greedy approach is more concise
     */
    std::string intToRomanStringBuilding(int num);

    /**
     * Approach 6: Mathematical Pattern Recognition
     * 
     * Use mathematical patterns to determine Roman numeral construction.
     * 
     * Reasoning: Recognize that Roman numerals follow mathematical patterns based
     * on digit values and positions. For each decimal place, analyze the digit
     * value and apply specific Roman numeral construction rules. This approach
     * focuses on the underlying mathematical structure rather than lookup tables,
     * making the pattern recognition explicit.
     * 
     * Time Complexity: O(1) - constant number of pattern applications
     * Space Complexity: O(1) - minimal extra space for pattern logic
     * 
     * Best when: Want to understand mathematical patterns, educational purposes
     * Worst when: Lookup table approach is more straightforward
     */
    std::string intToRomanPatternBased(int num);

private:
    // Helper functions
    std::string intToRomanHelper(int num, const std::vector<std::pair<int, std::string>>& values);
    std::string processDigit(int digit, const std::string& one, const std::string& five, const std::string& ten);
    std::string repeatString(const std::string& str, int count);
    
    // Lookup tables
    static const std::vector<std::string> thousands;
    static const std::vector<std::string> hundreds;
    static const std::vector<std::string> tens;
    static const std::vector<std::string> ones;
    
    // Value-symbol pairs
    static const std::vector<std::pair<int, std::string>> valueSymbolPairs;
};

}
}