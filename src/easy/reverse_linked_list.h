#pragma once

#include <stack>
#include <vector>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::ListNode;

/**
 * Problem 206: Reverse Linked List
 * 
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [0, 5000]
 * - -5000 <= Node.val <= 5000
 * 
 * Follow up: A linked list can be reversed either iteratively or recursively. 
 * Could you implement both?
 */
class ReverseLinkedList {
public:
    /**
     * Approach 1: Iterative with Three Pointers (Optimal)
     * 
     * Use three pointers to reverse links while traversing.
     * 
     * Reasoning: This is the most efficient and straightforward approach.
     * We maintain three pointers: prev (initially null), current (head),
     * and next (temporary). At each step, we reverse the current node's
     * link to point to prev, then advance all pointers. This reverses
     * the list in a single pass with constant extra space.
     * 
     * Time Complexity: O(n) - single pass through the list
     * Space Complexity: O(1) - only using three pointers
     * 
     * Best when: Need optimal performance, standard solution
     * Worst when: Need to preserve original list structure
     */
    ListNode* reverseListIterative(ListNode* head);

    /**
     * Approach 2: Recursive
     * 
     * Recursively reverse the list from the tail.
     * 
     * Reasoning: The recursive approach elegantly reverses the list by
     * recursively reversing the rest of the list, then fixing the links.
     * The base case is reaching the last node, which becomes the new head.
     * As we unwind the recursion, we reverse each link. The key insight:
     * head->next->next = head reverses the link, and head->next = nullptr
     * prevents cycles.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(n) - recursion call stack
     * 
     * Best when: Elegant solution preferred, functional programming style
     * Worst when: Stack space is limited, very long lists
     */
    ListNode* reverseListRecursive(ListNode* head);

    /**
     * Approach 3: Using Stack
     * 
     * Push all nodes to stack, then pop to build reversed list.
     * 
     * Reasoning: Stacks naturally reverse order (LIFO property).
     * We push all nodes onto a stack, then pop them to build
     * the reversed list. While this uses extra space, it clearly
     * demonstrates the reversal concept and separates the traversal
     * from the reconstruction phases.
     * 
     * Time Complexity: O(n) - two passes through the list
     * Space Complexity: O(n) - stack stores all nodes
     * 
     * Best when: Conceptual clarity needed, teaching reversal concept
     * Worst when: Memory is constrained, need optimal solution
     */
    ListNode* reverseListStack(ListNode* head);

    /**
     * Approach 4: Array-Based Reversal
     * 
     * Store nodes in array, then rebuild list in reverse order.
     * 
     * Reasoning: Arrays provide random access, making reversal straightforward.
     * We first traverse the list to store all nodes in an array, then
     * iterate through the array backwards to rebuild the connections.
     * This approach is similar to the stack approach but uses an array
     * for explicit index-based access.
     * 
     * Time Complexity: O(n) - two passes through the list
     * Space Complexity: O(n) - array stores all node pointers
     * 
     * Best when: Need to manipulate list order in complex ways
     * Worst when: Space efficiency is important
     */
    ListNode* reverseListArray(ListNode* head);

    /**
     * Approach 5: Tail Recursive with Accumulator
     * 
     * Use tail recursion with accumulator for potential optimization.
     * 
     * Reasoning: Tail recursion can be optimized by compilers to avoid
     * stack overflow. We pass an accumulator (the reversed portion so far)
     * through the recursive calls. Each call moves one node from the
     * original list to the front of the accumulator. This combines
     * the elegance of recursion with better space efficiency in
     * optimizing compilers.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(n) - recursion stack (O(1) with tail call optimization)
     * 
     * Best when: Functional programming paradigm, compiler supports TCO
     * Worst when: C++ compiler doesn't guarantee tail call optimization
     */
    ListNode* reverseListTailRecursive(ListNode* head);

    /**
     * Approach 6: Two-Pass with Node Value Swapping
     * 
     * Find middle, then swap values from ends toward center.
     * 
     * Reasoning: Instead of changing pointers, we can swap values.
     * First, we find the length and store nodes in a vector.
     * Then we swap values from both ends moving toward the center.
     * This preserves the node structure while reversing the values.
     * While not traditional for linked lists, it demonstrates an
     * alternative approach to reversal.
     * 
     * Time Complexity: O(n) - two passes through the list
     * Space Complexity: O(n) - storing nodes in vector
     * 
     * Best when: Node structure must be preserved, only values change
     * Worst when: Nodes contain complex data or references
     */
    ListNode* reverseListValueSwap(ListNode* head);

private:
    // Helper for tail recursive approach
    ListNode* reverseListTailRecursiveHelper(ListNode* current, ListNode* prev);
    
    // Helper for standard recursive approach
    ListNode* reverseListRecursiveHelper(ListNode* head);
};

}  // namespace easy
}  // namespace leetcode