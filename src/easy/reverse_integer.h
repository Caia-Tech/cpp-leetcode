#pragma once

#include <string>
#include <climits>

namespace leetcode {
namespace easy {

/**
 * Problem 7: Reverse Integer
 * 
 * Given a signed 32-bit integer x, return x with its digits reversed. 
 * If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], 
 * then return 0.
 * 
 * Assume the environment does not allow you to store 64-bit integers (signed or unsigned).
 * 
 * Constraints:
 * - -2^31 <= x <= 2^31 - 1
 */
class ReverseInteger {
public:
    /**
     * Approach 1: Mathematical Approach with Overflow Check
     * 
     * Build the reversed number digit by digit, checking for overflow before each operation.
     * 
     * Reasoning: This is the most direct mathematical approach. Extract digits using
     * modulo and integer division, build reversed number by multiplying by 10 and adding.
     * The key insight is checking overflow BEFORE the operation that would cause it,
     * rather than after. This satisfies the constraint of not using 64-bit integers.
     * 
     * Time Complexity: O(log n) - process each digit once
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Memory is constrained, need pure mathematical solution
     * Worst when: Overflow checking logic becomes complex
     */
    int reverseMath(int x);

    /**
     * Approach 2: String Conversion
     * 
     * Convert to string, reverse, and convert back with overflow check.
     * 
     * Reasoning: Strings are easier to manipulate and reverse. This approach separates
     * the concerns: string manipulation vs integer overflow handling. While not the most
     * efficient, it's often clearer and less error-prone. Good for prototyping.
     * 
     * Time Complexity: O(log n) - string operations scale with number of digits
     * Space Complexity: O(log n) - storing string representation
     * 
     * Best when: Code clarity is prioritized, string operations are optimized
     * Worst when: Memory usage is critical, string conversion overhead matters
     */
    int reverseString(int x);

    /**
     * Approach 3: Using Long for Overflow Detection
     * 
     * Use 64-bit integer internally to detect overflow (simulation purpose).
     * 
     * Reasoning: This approach violates the problem constraint but shows how overflow
     * detection would work if larger integers were available. Build the reversed number
     * in a long, then check if it fits in 32-bit range. Educational value for
     * understanding overflow detection patterns.
     * 
     * Time Complexity: O(log n) - process each digit once
     * Space Complexity: O(1) - using long instead of int
     * 
     * Best when: Problem constraints allow larger integers
     * Worst when: Must strictly follow 32-bit constraint
     */
    int reverseLong(int x);

    /**
     * Approach 4: Digit Array
     * 
     * Store digits in array, then reconstruct.
     * 
     * Reasoning: This approach separates digit extraction from number reconstruction.
     * First, extract all digits into an array, then build the reversed number.
     * Easier to debug and understand, but uses extra space. Good for educational
     * purposes to understand the digit manipulation process.
     * 
     * Time Complexity: O(log n) - two passes through digits
     * Space Complexity: O(log n) - array to store all digits
     * 
     * Best when: Need to process digits multiple times, debugging is important
     * Worst when: Memory usage must be minimized
     */
    int reverseArray(int x);

    /**
     * Approach 5: Recursive Approach
     * 
     * Recursively reverse the number.
     * 
     * Reasoning: This demonstrates how to think about the problem recursively.
     * Each recursive call processes one digit and delegates the rest to the recursive call.
     * While not the most efficient due to call stack overhead, it shows functional
     * programming approach and recursive thinking.
     * 
     * Time Complexity: O(log n) - recursive calls for each digit
     * Space Complexity: O(log n) - call stack depth equals number of digits
     * 
     * Best when: Functional programming style is preferred, educational purposes
     * Worst when: Call stack is limited or performance is critical
     */
    int reverseRecursive(int x);

    /**
     * Approach 6: Preemptive Overflow Check
     * 
     * Check for overflow before the operation that would cause it.
     * 
     * Reasoning: This is a more sophisticated version of approach 1 with cleaner
     * overflow detection logic. Pre-calculate the boundary conditions to make
     * overflow checks more explicit and readable. Separates overflow detection
     * logic from the main algorithm logic.
     * 
     * Time Complexity: O(log n) - process each digit once
     * Space Complexity: O(1) - constant space with precomputed boundaries
     * 
     * Best when: Code readability is important, complex overflow conditions exist
     * Worst when: Simple solutions are preferred
     */
    int reversePreemptive(int x);

private:
    int reverseRecursiveHelper(int x, int reversed);
};

}
}