#pragma once

#include <vector>
#include <unordered_set>
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
 * Problem 83: Remove Duplicates from Sorted List
 * 
 * Given the head of a sorted linked list, delete all duplicates such that each element 
 * appears only once. Return the linked list sorted as well.
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [0, 300].
 * - -100 <= Node.val <= 100
 * - The list is guaranteed to be sorted in ascending order.
 */
class RemoveDuplicatesFromSortedList {
public:
    /**
     * Approach 1: Single Pass Iteration (Optimal)
     * 
     * Iterate through the list and remove duplicates by skipping nodes with same values.
     * 
     * Reasoning: Since the list is sorted, all duplicates are adjacent. We can iterate
     * through the list once and whenever we find a node whose value equals its next
     * node's value, we skip the next node by updating the current node's next pointer.
     * This approach is optimal because it requires only one pass and constant extra space.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Always - this is the optimal solution
     * Worst when: Never - this approach is universally preferred
     */
    ListNode* deleteDuplicatesIterative(ListNode* head);

    /**
     * Approach 2: Recursive Solution
     * 
     * Use recursion to process the list and remove duplicates recursively.
     * 
     * Reasoning: For each node, recursively process the rest of the list first,
     * then decide whether to keep or skip the current node based on comparison
     * with the next node. This approach naturally handles the duplicate removal
     * by leveraging the call stack to maintain state. While elegant, it uses
     * O(n) space due to recursion stack.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(n) - recursion call stack depth
     * 
     * Best when: Recursive solutions preferred, small to medium lists
     * Worst when: Large lists (stack overflow risk), memory constraints
     */
    ListNode* deleteDuplicatesRecursive(ListNode* head);

    /**
     * Approach 3: Two-Pointer Technique
     * 
     * Use two pointers to track previous unique node and current node being examined.
     * 
     * Reasoning: Maintain two pointers - one for the last unique node encountered
     * and another for the current node being processed. This approach gives explicit
     * control over which nodes to keep and provides clear separation between the
     * "clean" part of the list and the part being processed. Useful when we need
     * to maintain references to multiple positions.
     * 
     * Time Complexity: O(n) - single pass through the list
     * Space Complexity: O(1) - only use pointer variables
     * 
     * Best when: Need explicit control over multiple positions, educational clarity
     * Worst when: Simple single pointer approach is sufficient
     */
    ListNode* deleteDuplicatesTwoPointer(ListNode* head);

    /**
     * Approach 4: Hash Set Tracking (Educational)
     * 
     * Use a hash set to track seen values and remove duplicates accordingly.
     * 
     * Reasoning: While overkill for sorted lists, this approach demonstrates how
     * duplicate removal would work for unsorted lists. Track seen values in a
     * hash set and remove nodes whose values have been encountered before.
     * This approach is more general but uses extra space unnecessarily for
     * sorted input since we can leverage the sorted property.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(k) where k is number of unique values
     * 
     * Best when: Educational purposes, extending to unsorted lists
     * Worst when: Memory constraints, sorted input (better approaches exist)
     */
    ListNode* deleteDuplicatesHashSet(ListNode* head);

    /**
     * Approach 5: Dummy Head with Trailing Pointer
     * 
     * Use a dummy head node to simplify edge cases and maintain a trailing pointer.
     * 
     * Reasoning: Create a dummy head to avoid special handling of the first node.
     * Maintain a trailing pointer to the last node in the result list. This
     * approach simplifies the logic by eliminating edge cases related to empty
     * lists or removing the head node. The dummy head technique is commonly
     * used in linked list problems to provide a consistent starting point.
     * 
     * Time Complexity: O(n) - single pass through the list
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Edge case handling complexity, consistent list processing pattern
     * Worst when: Simple cases where dummy head adds unnecessary overhead
     */
    ListNode* deleteDuplicatesDummyHead(ListNode* head);

    /**
     * Approach 6: Functional Programming with Lambda
     * 
     * Use functional programming concepts with lambda functions for list processing.
     * 
     * Reasoning: Implement the duplicate removal using functional programming
     * paradigms with lambda expressions. Create a processor function that
     * encapsulates the duplicate removal logic and can be parameterized.
     * This approach demonstrates how functional concepts can be applied to
     * linked list manipulation problems, though it may have overhead.
     * 
     * Time Complexity: O(n) - process each node once
     * Space Complexity: O(1) - constant space plus lambda overhead
     * 
     * Best when: Functional programming style preferred, parameterizable processing
     * Worst when: Performance critical, simple iterative approach is clearer
     */
    ListNode* deleteDuplicatesFunctional(ListNode* head);

    // Helper functions for testing
    static ListNode* createList(const std::vector<int>& values);
    static std::vector<int> listToVector(ListNode* head);
    static void deleteList(ListNode* head);

private:
    // Internal helper functions
    ListNode* removeDuplicatesRecursive(ListNode* node);
    std::function<ListNode*(ListNode*)> createDuplicateRemover();
};

}  // namespace easy
}  // namespace leetcode