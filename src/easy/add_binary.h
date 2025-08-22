#pragma once

#include <string>
#include <algorithm>
#include <bitset>

namespace leetcode {
namespace easy {

/**
 * Problem 67: Add Binary
 * 
 * Given two binary strings a and b, return their sum as a binary string.
 * 
 * Constraints:
 * - 1 <= a.length, b.length <= 10^4
 * - a and b consist only of '0' and '1' characters.
 * - Each string does not contain leading zeros except for the zero itself.
 */
class AddBinary {
public:
    /**
     * Approach 1: Two Pointers with Carry (Optimal)
     * 
     * Use two pointers from end of strings, simulate binary addition with carry.
     * 
     * Reasoning: This is the optimal approach that mimics manual binary addition.
     * Start from the least significant bits (rightmost), add corresponding bits
     * plus any carry from previous position. Handle carry propagation properly:
     * sum of two bits plus carry can be 0, 1, or 2 (which becomes 0 with carry 1)
     * or 3 (which becomes 1 with carry 1). Continue until both strings exhausted
     * and no carry remains.
     * 
     * Time Complexity: O(max(m, n)) - where m, n are lengths of input strings
     * Space Complexity: O(max(m, n)) - for result string
     * 
     * Best when: Standard binary addition, handles different length strings efficiently
     * Worst when: Need to convert to integers (not applicable for large numbers)
     */
    std::string addBinaryTwoPointers(const std::string& a, const std::string& b);

    /**
     * Approach 2: Pad Shorter String
     * 
     * Pad shorter string with leading zeros, then add digit by digit.
     * 
     * Reasoning: Normalize both strings to same length by padding shorter one
     * with leading zeros. This simplifies addition logic since we don't need
     * to handle different lengths. Then perform digit-by-digit addition from
     * right to left with carry. While conceptually simpler, it uses extra
     * space for padding.
     * 
     * Time Complexity: O(max(m, n)) - padding and addition operations
     * Space Complexity: O(max(m, n)) - padded strings and result
     * 
     * Best when: Uniform length processing is preferred, simplifies loop logic
     * Worst when: Memory usage is critical (padding uses extra space)
     */
    std::string addBinaryPadding(const std::string& a, const std::string& b);

    /**
     * Approach 3: Reverse and Add
     * 
     * Reverse both strings, add from beginning, then reverse result.
     * 
     * Reasoning: Reverse both strings so we can process from least significant
     * to most significant digit using normal left-to-right iteration. After
     * addition, reverse the result back. This approach makes the addition loop
     * more natural (left-to-right) but requires extra string reversals.
     * 
     * Time Complexity: O(max(m, n)) - reverse operations and addition
     * Space Complexity: O(max(m, n)) - reversed strings and result
     * 
     * Best when: Left-to-right processing is more intuitive
     * Worst when: Extra string operations are undesirable
     */
    std::string addBinaryReverse(const std::string& a, const std::string& b);

    /**
     * Approach 4: Recursive Addition
     * 
     * Recursively add corresponding bits with carry propagation.
     * 
     * Reasoning: Recursive approach where each call processes one bit position
     * and passes carry to next recursive call. Base case is when both strings
     * are exhausted and no carry exists. While elegant, it has call stack
     * overhead and may hit stack limits for very long strings.
     * 
     * Time Complexity: O(max(m, n)) - recursive calls for each bit position
     * Space Complexity: O(max(m, n)) - recursion call stack plus result
     * 
     * Best when: Recursive thinking is preferred, educational recursion
     * Worst when: String length is large (stack overflow risk)
     */
    std::string addBinaryRecursive(const std::string& a, const std::string& b);

    /**
     * Approach 5: Bit Manipulation (Convert to Integer)
     * 
     * Convert strings to integers, add using bitwise operations, convert back.
     * 
     * Reasoning: Convert binary strings to integers, perform addition using
     * built-in arithmetic or bitwise operations, then convert result back to
     * binary string. While this leverages hardware arithmetic, it's limited
     * by integer size and doesn't work for arbitrarily large numbers that
     * exceed integer limits.
     * 
     * Time Complexity: O(n) - conversion and arithmetic operations
     * Space Complexity: O(n) - result string
     * 
     * Best when: Numbers fit in integer range, want to use hardware arithmetic
     * Worst when: Numbers are too large for standard integer types
     */
    std::string addBinaryBitwise(const std::string& a, const std::string& b);

    /**
     * Approach 6: STL bitset (Educational)
     * 
     * Use C++ bitset for binary operations.
     * 
     * Reasoning: Demonstrate usage of std::bitset for binary arithmetic.
     * Convert strings to bitset, perform addition using bitset operations,
     * convert back to string. While this shows STL usage, bitset has fixed
     * size limitations and isn't suitable for arbitrary precision arithmetic
     * that this problem might require.
     * 
     * Time Complexity: O(n) - bitset operations
     * Space Complexity: O(n) - bitset storage and result
     * 
     * Best when: Educational purposes, demonstrating STL bitset usage
     * Worst when: Need arbitrary precision or bitset size is insufficient
     */
    std::string addBinaryBitset(const std::string& a, const std::string& b);

private:
    std::string addBinaryRecHelper(const std::string& a, const std::string& b, int i, int j, int carry);
    std::string padWithZeros(const std::string& str, int targetLength);
    long long binaryStringToInt(const std::string& binary);
    std::string intToBinaryString(long long num);
};

}
}