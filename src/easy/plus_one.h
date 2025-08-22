#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 66: Plus One
 * 
 * You are given a large integer represented as an integer array digits, where each digits[i] 
 * is the ith digit of the integer. The digits are ordered from most significant to least significant 
 * in left-to-right order. The large integer does not contain any leading zeros.
 * 
 * Increment the large integer by one and return the resulting array of digits.
 * 
 * Constraints:
 * - 1 <= digits.length <= 100
 * - 0 <= digits[i] <= 9
 * - digits does not contain any leading zeros, except the number itself is zero.
 */
class PlusOne {
public:
    /**
     * Approach 1: Reverse Iteration with Carry (Optimal)
     * 
     * Iterate from right to left, handling carry propagation.
     * 
     * Reasoning: This is the optimal approach that mimics manual addition.
     * Start from the least significant digit (rightmost), add 1, and handle
     * carry propagation. If adding 1 to a digit results in 10, set digit to 0
     * and carry 1 to next position. Most numbers won't need carry propagation
     * beyond the first digit, making this very efficient in practice.
     * 
     * Time Complexity: O(n) worst case, O(1) average case
     * Space Complexity: O(1) if no overflow, O(n) if new digit needed
     * 
     * Best when: Standard solution, handles most cases efficiently
     * Worst when: All digits are 9 (worst case scenario)
     */
    std::vector<int> plusOneCarry(std::vector<int>& digits);

    /**
     * Approach 2: String Conversion and Back
     * 
     * Convert to string, perform string arithmetic, convert back.
     * 
     * Reasoning: Convert digits array to string representation, perform
     * string-based addition (handling carry manually), then convert back
     * to digit array. While this works, it's unnecessarily complex and
     * inefficient due to multiple conversions and string operations.
     * Demonstrates alternative thinking but not practical.
     * 
     * Time Complexity: O(n) - multiple passes for conversions
     * Space Complexity: O(n) - string storage and result array
     * 
     * Best when: Educational purposes, string arithmetic practice
     * Worst when: Efficiency is important or direct approach is available
     */
    std::vector<int> plusOneString(std::vector<int>& digits);

    /**
     * Approach 3: Recursive Carry Propagation
     * 
     * Use recursion to handle carry propagation.
     * 
     * Reasoning: Recursive approach where each call handles one digit and
     * its carry. Base case is when no carry exists or we've processed all
     * digits. Each recursive call adds 1 (or carry from previous position)
     * and returns whether a carry is needed for the next position. While
     * elegant, it uses call stack and has overhead.
     * 
     * Time Complexity: O(n) - recursive calls for each digit in worst case
     * Space Complexity: O(n) - recursion call stack
     * 
     * Best when: Recursive thinking is preferred, educational recursion
     * Worst when: Stack space is limited or iterative approach is simpler
     */
    std::vector<int> plusOneRecursive(std::vector<int>& digits);

    /**
     * Approach 4: Handle All 9s Special Case
     * 
     * Check for all 9s upfront, handle separately.
     * 
     * Reasoning: Optimize for the special case where all digits are 9.
     * First check if all digits are 9 - if so, return [1,0,0,...,0].
     * Otherwise, use standard carry propagation. This avoids unnecessary
     * carry propagation when we know the result structure upfront.
     * 
     * Time Complexity: O(n) - check for 9s + potential carry propagation
     * Space Complexity: O(1) or O(n) depending on whether overflow occurs
     * 
     * Best when: Optimizing for specific input patterns
     * Worst when: Input distribution doesn't favor this optimization
     */
    std::vector<int> plusOneSpecialCase(std::vector<int>& digits);

    /**
     * Approach 5: Two-Pass Algorithm
     * 
     * First pass determines if overflow needed, second pass performs addition.
     * 
     * Reasoning: First pass scans to determine if we need an extra digit
     * (overflow case). Second pass performs the actual addition with known
     * result size. This separates size determination from value computation,
     * potentially avoiding reallocation in overflow cases if we pre-allocate
     * the result vector.
     * 
     * Time Complexity: O(n) - two passes through digits
     * Space Complexity: O(n) - result array with known size
     * 
     * Best when: Want to avoid vector reallocation, size prediction is valuable
     * Worst when: Single-pass algorithm is simpler and sufficient
     */
    std::vector<int> plusOneTwoPass(std::vector<int>& digits);

    /**
     * Approach 6: In-Place Modification (When Allowed)
     * 
     * Modify input array in-place, handle overflow by returning new array.
     * 
     * Reasoning: When modification of input is allowed, perform addition
     * in-place to save space. Only create new array if overflow occurs
     * (all digits were 9). This minimizes memory allocation in most cases
     * but requires input modification permission, which isn't always acceptable.
     * 
     * Time Complexity: O(n) worst case, often much better
     * Space Complexity: O(1) most cases, O(n) only on overflow
     * 
     * Best when: Input modification allowed, memory optimization critical
     * Worst when: Must preserve original input, functional programming style
     */
    std::vector<int> plusOneInPlace(std::vector<int>& digits);

private:
    bool addOneRecursive(std::vector<int>& digits, int index);
    bool isAllNines(const std::vector<int>& digits);
    std::string vectorToString(const std::vector<int>& digits);
    std::vector<int> stringToVector(const std::string& str);
    std::string addOneToString(const std::string& num);
};

}
}