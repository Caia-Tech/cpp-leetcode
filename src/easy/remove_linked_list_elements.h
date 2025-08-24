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
 * Problem 203: Remove Linked List Elements
 * 
 * Given the head of a linked list and an integer val, remove all the nodes 
 * of the linked list that have Node.val == val, and return the new head.
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [0, 10^4].
 * - 1 <= Node.val <= 50
 * - 0 <= val <= 50
 */
class RemoveLinkedListElements {
public:
    /**
     * Approach 1: Iterative with Dummy Head (Optimal)
     * 
     * Use a dummy head to simplify edge cases and iterate through the list.
     * 
     * Reasoning: Create a dummy head node to handle the case where the first
     * nodes need to be removed. Maintain a previous pointer and current pointer.
     * When current node's value matches the target, skip it by updating the
     * previous node's next pointer. This approach handles all edge cases
     * uniformly and is the most straightforward solution.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Always - this is the optimal and most intuitive solution
     * Worst when: Never - this approach is universally preferred
     */
    ListNode* removeElementsIterativeDummy(ListNode* head, int val);

    /**
     * Approach 2: Iterative without Dummy Head
     * 
     * Handle head removal separately, then process the rest of the list.
     * 
     * Reasoning: First handle the special case where head nodes need removal
     * by advancing the head pointer while it points to nodes with target value.
     * Then process the rest of the list with two pointers. This approach
     * avoids the dummy head but requires special handling for the head case.
     * More complex but demonstrates different edge case handling strategies.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Want to avoid dummy head, explicit head handling preferred
     * Worst when: Code simplicity is prioritized
     */
    ListNode* removeElementsIterativeNoDummy(ListNode* head, int val);

    /**
     * Approach 3: Recursive Solution
     * 
     * Use recursion to process the list and build result list.
     * 
     * Reasoning: For each node, recursively process the rest of the list first.
     * Then decide whether to include the current node in the result based on
     * its value. If the node's value matches the target, return the result
     * from recursive call; otherwise, connect current node to the result.
     * This approach is elegant but uses O(n) stack space.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(n) - recursion call stack depth
     * 
     * Best when: Recursive solutions preferred, elegant code style desired
     * Worst when: Large lists (stack overflow risk), memory constraints
     */
    ListNode* removeElementsRecursive(ListNode* head, int val);

    /**
     * Approach 4: Stack-Based Processing
     * 
     * Use a stack to collect nodes that should be kept, then rebuild the list.
     * 
     * Reasoning: Traverse the list and push nodes that don't match the target
     * value onto a stack. Then pop from the stack and rebuild the list in
     * reverse order. This approach demonstrates how stack can be used for
     * list processing, though it's less efficient than direct pointer
     * manipulation due to the extra rebuilding step.
     * 
     * Time Complexity: O(n) - traverse list twice (collect and rebuild)
     * Space Complexity: O(n) - stack to store kept nodes
     * 
     * Best when: Stack-based processing preferred, educational purposes
     * Worst when: Memory efficiency important, direct pointer manipulation available
     */
    ListNode* removeElementsStack(ListNode* head, int val);

    /**
     * Approach 5: Two-Pass Solution
     * 
     * First pass counts remaining nodes, second pass builds new list.
     * 
     * Reasoning: In the first pass, count how many nodes will remain after
     * removal. In the second pass, create a new list with exactly that many
     * nodes by copying values from nodes that don't match the target. This
     * approach creates an entirely new list structure rather than modifying
     * the existing one, which might be useful when original list preservation
     * is required before the final decision.
     * 
     * Time Complexity: O(n) - two passes through the list
     * Space Complexity: O(1) - only use constant extra variables (not counting output)
     * 
     * Best when: Original list structure must be preserved initially
     * Worst when: Memory efficiency important, in-place modification preferred
     */
    ListNode* removeElementsTwoPass(ListNode* head, int val);

    /**
     * Approach 6: Functional Programming with Lambda
     * 
     * Use functional programming concepts with filters and transformations.
     * 
     * Reasoning: Apply functional programming paradigms by creating a filter
     * function that determines which nodes to keep. Use lambda expressions
     * to create a configurable node processor that can be parameterized for
     * different removal criteria. This approach demonstrates how functional
     * concepts can be applied to linked list manipulation problems.
     * 
     * Time Complexity: O(n) - process each node once
     * Space Complexity: O(1) - constant space plus lambda overhead
     * 
     * Best when: Functional programming style preferred, parameterizable filtering
     * Worst when: Performance critical, simple iterative approach is clearer
     */
    ListNode* removeElementsFunctional(ListNode* head, int val);

private:
    // Helper functions
    ListNode* removeElementsRecursiveHelper(ListNode* node, int val);
    
    // Functional approach helpers
    std::function<ListNode*(ListNode*, int)> createElementRemover();
    
    // Helper functions for testing
public:
    static ListNode* createList(const std::vector<int>& values);
    static std::vector<int> listToVector(ListNode* head);
    static void deleteList(ListNode* head);
};

}  // namespace easy
}  // namespace leetcode