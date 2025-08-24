#pragma once

#include <vector>
#include <functional>
#include <unordered_set>

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
 * Problem 237: Delete Node in a Linked List
 * 
 * There is a singly-linked list head and we want to delete a node in it.
 * You are given the node to be deleted. You will not be given access to 
 * the first node of head. All the values of the linked list are unique, 
 * and it is guaranteed that the given node to delete is not the last node 
 * in the linked list.
 * 
 * Delete the given node.
 * 
 * Constraints:
 * - The number of the nodes in the given list is in the range [2, 1000].
 * - -1000 <= Node.val <= 1000
 * - The value of each node in the list is unique.
 * - The node to be deleted is in the list and is not a tail node.
 */
class DeleteNodeInLinkedList {
public:
    /**
     * Approach 1: Copy Next Node Value (Optimal)
     * 
     * Copy the next node's value to current node, then delete the next node.
     * 
     * Reasoning: Since we can't access the previous node to update its next
     * pointer, we can't actually "delete" the current node in the traditional
     * sense. Instead, we copy the next node's value to the current node, then
     * delete the next node. This effectively removes the target value from
     * the list by overwriting it and removing the duplicate.
     * 
     * Time Complexity: O(1) - constant time operation
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Always - this is the standard and most efficient solution
     * Worst when: Never - this is the expected approach for this problem
     */
    void deleteNodeCopyNext(ListNode* node);

    /**
     * Approach 2: Shift All Values Left
     * 
     * Shift all values from the next node leftward, then delete the last node.
     * 
     * Reasoning: Instead of just copying one value, traverse the remaining
     * list and shift each value one position to the left. This approach
     * demonstrates a more comprehensive value shifting strategy, though less
     * efficient than the copy-next approach. Each node gets the value from
     * its next node, until we reach the second-to-last node.
     * 
     * Time Complexity: O(n) - traverse remaining part of the list
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Educational purposes, demonstrating alternative approaches
     * Worst when: Efficiency is critical, simple copy operation preferred
     */
    void deleteNodeShiftValues(ListNode* node);

    /**
     * Approach 3: Mark and Compact
     * 
     * Mark node as deleted, then compact the list by copying valid values.
     * 
     * Reasoning: Mark the node to be deleted with a special value, then
     * traverse the list copying all non-marked values leftward. This
     * approach simulates deletion by creating a compacted version of the
     * list without the deleted element. Uses a sentinel value to mark
     * deleted nodes, then compacts during a second pass.
     * 
     * Time Complexity: O(n) - two passes through remaining list
     * Space Complexity: O(1) - only use constant extra variables
     * 
     * Best when: Multiple deletions needed, mark-and-compact pattern useful
     * Worst when: Simple single deletion, extra complexity not justified
     */
    void deleteNodeMarkAndCompact(ListNode* node);

    /**
     * Approach 4: Recursive Value Propagation
     * 
     * Use recursion to propagate values backward through the list.
     * 
     * Reasoning: Use recursion to reach the end of the list, then on the
     * return path, propagate values backward. Each recursive call returns
     * the value that should be assigned to the current node. The deletion
     * happens implicitly by not propagating the target node's value.
     * This creates a cascade of value updates throughout the remaining list.
     * 
     * Time Complexity: O(n) - recursive calls for remaining nodes
     * Space Complexity: O(n) - recursion call stack
     * 
     * Best when: Recursive solutions preferred, educational demonstration
     * Worst when: Stack overflow concerns, iterative solutions preferred
     */
    void deleteNodeRecursive(ListNode* node);

    /**
     * Approach 5: Two-Pointer Technique
     * 
     * Use two pointers to manage value copying and node deletion.
     * 
     * Reasoning: Maintain two pointers - one for writing values and one for
     * reading values. The write pointer stays at the node to be deleted,
     * while the read pointer advances through subsequent nodes. Copy values
     * from read pointer to write pointer, effectively overwriting the
     * deleted value and shifting all subsequent values left by one position.
     * 
     * Time Complexity: O(n) - traverse remaining part of list
     * Space Complexity: O(1) - only use two pointer variables
     * 
     * Best when: Two-pointer technique practice, clear separation of concerns
     * Worst when: Simple operations preferred, minimal code complexity desired
     */
    void deleteNodeTwoPointers(ListNode* node);

    /**
     * Approach 6: Functional Style with Lambda
     * 
     * Use functional programming concepts to handle node deletion.
     * 
     * Reasoning: Create a lambda function that encapsulates the deletion
     * logic, demonstrating how functional programming concepts can be
     * applied to linked list manipulation. The lambda function takes a
     * node and applies the appropriate deletion strategy, making the
     * operation more modular and reusable for different deletion scenarios.
     * 
     * Time Complexity: O(1) - delegates to efficient copy-next strategy
     * Space Complexity: O(1) - lambda overhead is constant
     * 
     * Best when: Functional programming style preferred, modular design
     * Worst when: Simple direct function calls preferred, minimal abstraction
     */
    void deleteNodeFunctional(ListNode* node);

private:
    // Helper function for recursive approach
    int deleteNodeRecursiveHelper(ListNode* node, ListNode* target);
    
    // Functional approach helper
    std::function<void(ListNode*)> createNodeDeleter();

public:
    // Helper functions for testing
    static ListNode* createList(const std::vector<int>& values);
    static std::vector<int> listToVector(ListNode* head);
    static void deleteList(ListNode* head);
    static ListNode* findNode(ListNode* head, int value);
};

}  // namespace easy
}  // namespace leetcode