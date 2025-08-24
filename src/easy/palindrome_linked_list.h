#pragma once

#include <vector>
#include <functional>
#include <stack>

namespace leetcode {
namespace easy {

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * Problem 234: Palindrome Linked List
 * 
 * Given the head of a singly linked list, return true if it is a palindrome
 * or false otherwise.
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [1, 10^5].
 * - 0 <= Node.val <= 9
 */
class PalindromeLinkedList {
public:
    /**
     * Approach 1: Convert to Array and Two Pointers (Simplest)
     * 
     * Convert the linked list to an array, then use two pointers to check palindrome.
     * 
     * Reasoning: First traverse the linked list to copy all values into an array.
     * Then use two pointers (left and right) starting from ends of the array,
     * moving inward while comparing values. This approach is straightforward
     * and easy to understand, separating the linked list traversal from the
     * palindrome checking logic.
     * 
     * Time Complexity: O(n) - traverse list once, then array once
     * Space Complexity: O(n) - array to store all node values
     * 
     * Best when: Simplicity preferred, space not a constraint
     * Worst when: Memory usage is critical
     */
    bool isPalindromeArray(ListNode* head);

    /**
     * Approach 2: Stack-Based Comparison
     * 
     * Use a stack to store first half values, then compare with second half.
     * 
     * Reasoning: First pass to count nodes, then traverse again pushing first
     * half of values onto a stack. Continue traversal for second half, popping
     * from stack and comparing with current values. Stack naturally reverses
     * the first half order, making comparison with second half straightforward.
     * This approach uses stack's LIFO property to handle the reversal needed
     * for palindrome checking.
     * 
     * Time Complexity: O(n) - two passes through the list
     * Space Complexity: O(n/2) = O(n) - stack stores half the nodes
     * 
     * Best when: Stack-based processing preferred, moderate memory usage acceptable
     * Worst when: Constant space required
     */
    bool isPalindromeStack(ListNode* head);

    /**
     * Approach 3: Reverse Second Half and Compare (Optimal)
     * 
     * Find middle, reverse second half, compare with first half, restore list.
     * 
     * Reasoning: Use slow/fast pointers to find the middle of the list. Reverse
     * the second half of the list in-place. Compare the first half with the
     * reversed second half node by node. Finally restore the original list
     * structure. This achieves O(1) space complexity while still being efficient.
     * Most optimal approach balancing time and space complexity.
     * 
     * Time Complexity: O(n) - traverse list multiple times but still linear
     * Space Complexity: O(1) - only use constant extra variables
     * 
     * Best when: Space efficiency is critical, in-place operations preferred
     * Worst when: List modification (even temporary) is not allowed
     */
    bool isPalindromeReverseSecondHalf(ListNode* head);

    /**
     * Approach 4: Recursive with Global Variable
     * 
     * Use recursion to reach the end, then compare on the way back.
     * 
     * Reasoning: Use recursion to traverse to the end of the list while
     * maintaining a global pointer that advances from the beginning. When
     * recursion unwinds, compare the current recursive position (moving backward)
     * with the global pointer (moving forward). This creates a natural two-pointer
     * movement from both ends toward the center during the recursive unwinding.
     * 
     * Time Complexity: O(n) - visit each node once during recursion
     * Space Complexity: O(n) - recursion call stack depth
     * 
     * Best when: Recursive solutions preferred, elegant implementation desired
     * Worst when: Stack overflow risk with large lists, space constraints
     */
    bool isPalindromeRecursive(ListNode* head);

    /**
     * Approach 5: Two-Pass with Mathematical Properties
     * 
     * Calculate mathematical properties in two passes to determine palindrome.
     * 
     * Reasoning: First pass calculates the sum and product of all elements along
     * with their positions. Second pass recalculates these values in reverse
     * order and compares with mirrored expectations. While not foolproof for
     * all cases due to potential hash collisions, demonstrates mathematical
     * approaches to palindrome detection and works for many practical cases.
     * 
     * Time Complexity: O(n) - two passes through the list
     * Space Complexity: O(1) - only use constant variables
     * 
     * Best when: Mathematical approaches preferred, demonstration purposes
     * Worst when: Perfect accuracy required (hash collision possibility)
     */
    bool isPalindromeMathematical(ListNode* head);

    /**
     * Approach 6: Functional Programming with Lambdas
     * 
     * Use functional programming concepts to check palindrome property.
     * 
     * Reasoning: Create a functional pipeline that extracts values from the
     * linked list, then applies palindrome checking logic using lambda functions
     * and higher-order functions. This approach demonstrates how functional
     * programming paradigms can be applied to data structure problems, creating
     * reusable and composable checking functions.
     * 
     * Time Complexity: O(n) - linear traversal with functional transformations
     * Space Complexity: O(n) - intermediate data structures for functional operations
     * 
     * Best when: Functional programming style preferred, code reusability important
     * Worst when: Performance critical, simple imperative approach is clearer
     */
    bool isPalindromeFunctional(ListNode* head);

private:
    // Helper functions
    ListNode* reverseList(ListNode* head);
    ListNode* findMiddle(ListNode* head);
    int getListLength(ListNode* head);
    
    // Recursive helper
    bool isPalindromeRecursiveHelper(ListNode* node, ListNode*& frontPointer);
    
    // Functional approach helpers
    std::function<bool(const std::vector<int>&)> createPalindromeChecker();
    std::function<std::vector<int>(ListNode*)> createValueExtractor();

public:
    // Helper functions for testing
    static ListNode* createList(const std::vector<int>& values);
    static std::vector<int> listToVector(ListNode* head);
    static void deleteList(ListNode* head);
};

}  // namespace easy
}  // namespace leetcode