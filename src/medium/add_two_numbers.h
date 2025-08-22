#pragma once

#include <vector>
#include <string>
#include <stack>
#include "utils/data_structures.h"

namespace leetcode {
namespace medium {

using ListNode = utils::ListNode;

/**
 * Problem 2: Add Two Numbers
 * 
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * 
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 * 
 * Constraints:
 * - The number of nodes in each linked list is in the range [1, 100].
 * - 0 <= Node.val <= 9
 * - It is guaranteed that the list represents a number that does not have leading zeros.
 * 
 * Example:
 * Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807.
 */
class AddTwoNumbers {
public:
    /**
     * Approach 1: Elementary Math Simulation
     * 
     * Simulate elementary math addition with carry propagation.
     * Process digits from least significant to most significant.
     * 
     * Reasoning: This mimics how we add numbers on paper. Since digits are already
     * in reverse order (LSB first), we can directly simulate the process.
     * Handle carry at each step and continue until both lists are exhausted.
     * 
     * Time Complexity: O(max(n, m)) where n, m are lengths of the lists
     * Space Complexity: O(max(n, m)) for the result list
     */
    ListNode* addTwoNumbersElementary(ListNode* l1, ListNode* l2);

    /**
     * Approach 2: Recursive with Carry
     * 
     * Recursively add corresponding digits with carry propagation.
     * 
     * Reasoning: The problem has recursive structure - adding two numbers is
     * equivalent to adding current digits plus carry, then recursively adding
     * the rest. Base case is when both lists are null and carry is 0.
     * 
     * Time Complexity: O(max(n, m))
     * Space Complexity: O(max(n, m)) for recursion stack + result
     */
    ListNode* addTwoNumbersRecursive(ListNode* l1, ListNode* l2);

    /**
     * Approach 3: Convert to Integers, Add, Convert Back
     * 
     * Convert linked lists to integers, add them, convert result back to list.
     * 
     * Reasoning: This approach treats the problem as integer arithmetic.
     * However, it has limitations with very large numbers that exceed integer limits.
     * Works well for numbers within standard integer range.
     * 
     * Time Complexity: O(max(n, m))
     * Space Complexity: O(max(n, m)) for result
     */
    ListNode* addTwoNumbersInteger(ListNode* l1, ListNode* l2);

    /**
     * Approach 4: String-based Arithmetic
     * 
     * Convert to strings, perform string addition, convert back to list.
     * 
     * Reasoning: String arithmetic can handle arbitrarily large numbers without
     * integer overflow. This approach is more robust for very large inputs.
     * 
     * Time Complexity: O(max(n, m))
     * Space Complexity: O(max(n, m)) for strings and result
     */
    ListNode* addTwoNumbersString(ListNode* l1, ListNode* l2);

    /**
     * Approach 5: Stack-based (for forward order)
     * 
     * Use stacks to reverse the process, useful if digits were in forward order.
     * 
     * Reasoning: Although the problem gives digits in reverse order, this approach
     * demonstrates how to handle the case where digits are in normal order.
     * We reverse, add, then reverse again.
     * 
     * Time Complexity: O(max(n, m))
     * Space Complexity: O(max(n, m)) for stacks
     */
    ListNode* addTwoNumbersStack(ListNode* l1, ListNode* l2);

    /**
     * Approach 6: In-place Modification (Reuse l1)
     * 
     * Modify the first list in-place to store the result.
     * 
     * Reasoning: To save space, we can reuse one of the input lists to store
     * the result. This requires careful handling when lists have different lengths.
     * 
     * Time Complexity: O(max(n, m))
     * Space Complexity: O(1) additional space (reuses input)
     */
    ListNode* addTwoNumbersInPlace(ListNode* l1, ListNode* l2);

private:
    // Helper functions
    ListNode* addRecursive(ListNode* l1, ListNode* l2, int carry);
    long long listToInteger(ListNode* head);
    ListNode* integerToList(long long num);
    std::string listToString(ListNode* head);
    ListNode* stringToList(const std::string& str);
    std::string addStrings(const std::string& num1, const std::string& num2);
    ListNode* reverseList(ListNode* head);
};

}
}