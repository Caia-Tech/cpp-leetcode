#pragma once

#include <vector>
#include "utils/data_structures.h"

namespace leetcode {
namespace easy {

using ListNode = utils::ListNode;

/**
 * Problem 21: Merge Two Sorted Lists
 * 
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists into one sorted list. The list should be made by splicing together 
 * the nodes of the first two lists.
 * 
 * Return the head of the merged linked list.
 * 
 * Constraints:
 * - The number of nodes in both lists is in the range [0, 50].
 * - -100 <= Node.val <= 100
 * - Both list1 and list2 are sorted in non-decreasing order.
 * 
 * Example:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 */
class MergeTwoSortedLists {
public:
    /**
     * Approach 1: Iterative with Dummy Head
     * 
     * Use a dummy head node to simplify edge cases. Compare nodes from both lists
     * and append the smaller one to the result.
     * 
     * Reasoning: Dummy head eliminates the need for special handling of the first node.
     * We maintain pointers to current positions in both lists and build result iteratively.
     * 
     * Time Complexity: O(n + m) where n, m are lengths of the lists
     * Space Complexity: O(1)
     */
    ListNode* mergeTwoListsIterative(ListNode* list1, ListNode* list2);

    /**
     * Approach 2: Recursive
     * 
     * If one list is empty, return the other. Otherwise, recursively merge the rest
     * based on which head is smaller.
     * 
     * Reasoning: The problem has optimal substructure. If we know which node should be
     * first, we can recursively solve the remaining problem. This naturally follows
     * the divide-and-conquer paradigm.
     * 
     * Time Complexity: O(n + m)
     * Space Complexity: O(n + m) due to recursion stack
     */
    ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2);

    /**
     * Approach 3: In-place with Two Pointers
     * 
     * Directly modify the next pointers without using extra space for dummy node.
     * 
     * Reasoning: We can save the space of a dummy node by carefully tracking the
     * head and previous node. This requires more careful handling of edge cases.
     * 
     * Time Complexity: O(n + m)
     * Space Complexity: O(1)
     */
    ListNode* mergeTwoListsInPlace(ListNode* list1, ListNode* list2);

    /**
     * Approach 4: Convert to Array, Merge, Convert Back
     * 
     * Extract all values into arrays, merge arrays, then create new linked list.
     * 
     * Reasoning: Sometimes it's easier to work with arrays for certain operations.
     * This approach leverages array merging algorithms and then reconstructs the list.
     * 
     * Time Complexity: O(n + m)
     * Space Complexity: O(n + m) for the arrays
     */
    ListNode* mergeTwoListsArray(ListNode* list1, ListNode* list2);

    /**
     * Approach 5: Priority Queue (Overkill for 2 lists)
     * 
     * Use min-heap to always get the smallest node among available heads.
     * 
     * Reasoning: This generalizes to merging k sorted lists. For 2 lists it's overkill,
     * but demonstrates how the algorithm scales. The heap maintains the smallest element
     * at the top.
     * 
     * Time Complexity: O((n + m) * log k) where k=2, so O(n + m)
     * Space Complexity: O(k) = O(1) for the heap
     */
    ListNode* mergeTwoListsPriorityQueue(ListNode* list1, ListNode* list2);

    /**
     * Approach 6: Sentinel Node with Tail Pointer
     * 
     * Use both dummy head and maintain tail pointer for O(1) append operations.
     * 
     * Reasoning: By maintaining a tail pointer, we avoid traversing to find the end
     * of the current result list. This is an optimization of the basic iterative approach.
     * 
     * Time Complexity: O(n + m)
     * Space Complexity: O(1)
     */
    ListNode* mergeTwoListsSentinel(ListNode* list1, ListNode* list2);

private:
    // Helper functions
    std::vector<int> listToArray(ListNode* head);
    ListNode* arrayToList(const std::vector<int>& arr);
    std::vector<int> mergeArrays(const std::vector<int>& arr1, const std::vector<int>& arr2);
    
    // Comparator for priority queue
    struct NodeCompare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;  // Min heap
        }
    };
};

}
}