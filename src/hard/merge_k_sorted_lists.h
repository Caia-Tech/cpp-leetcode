#pragma once

#include <vector>
#include <queue>
#include "utils/data_structures.h"

namespace leetcode {
namespace hard {

using ListNode = utils::ListNode;

/**
 * Problem 23: Merge k Sorted Lists
 * 
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 * 
 * Constraints:
 * - k == lists.length
 * - 0 <= k <= 10^4
 * - 0 <= lists[i].length <= 500
 * - -10^4 <= lists[i][j] <= 10^4
 * - lists[i] is sorted in ascending order.
 * - The sum of lists[i].length will not exceed 10^4.
 */
class MergeKSortedLists {
public:
    /**
     * Approach 1: Brute Force
     * 
     * Collect all values, sort, and create new list.
     * 
     * Reasoning: The most straightforward approach - traverse all k lists to collect
     * all values into an array, sort the array, then create a new linked list from
     * the sorted values. While this completely ignores the fact that input lists
     * are already sorted, it's simple to implement and guaranteed to work. The
     * sorting step dominates the time complexity.
     * 
     * Time Complexity: O(N log N) - where N is total number of nodes across all lists
     * Space Complexity: O(N) - array to store all values plus result list
     * 
     * Best when: Simple implementation needed, k is very large compared to list lengths
     * Worst when: Need to leverage the sorted property of input lists
     */
    ListNode* mergeKListsBruteForce(std::vector<ListNode*>& lists);

    /**
     * Approach 2: Priority Queue (Min Heap)
     * 
     * Use heap to always get minimum node.
     * 
     * Reasoning: This leverages the sorted property of input lists efficiently.
     * Maintain a min-heap containing the head nodes of all non-empty lists.
     * Repeatedly extract the minimum node from heap, add it to result, and insert
     * the next node from that list. This ensures we always process the globally
     * smallest remaining node. Very efficient when k is much smaller than N.
     * 
     * Time Complexity: O(N log k) - N heap operations, each taking O(log k)
     * Space Complexity: O(k) - heap stores at most k nodes
     * 
     * Best when: k is small compared to total nodes, need clean implementation
     * Worst when: k is large or heap operations have high constant overhead
     */
    ListNode* mergeKListsHeap(std::vector<ListNode*>& lists);

    /**
     * Approach 3: Merge Two at a Time
     * 
     * Sequentially merge lists one by one.
     * 
     * Reasoning: Use the standard "merge two sorted lists" algorithm repeatedly.
     * Start with first list, merge it with second list, then merge result with
     * third list, and so on. While conceptually simple, this approach is inefficient
     * because later merges involve much longer lists, leading to quadratic behavior.
     * The first node may be processed k times.
     * 
     * Time Complexity: O(kN) - each node processed multiple times
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Memory is extremely constrained, k is very small
     * Worst when: k is large, making the quadratic behavior expensive
     */
    ListNode* mergeKListsSequential(std::vector<ListNode*>& lists);

    /**
     * Approach 4: Divide and Conquer
     * 
     * Recursively merge pairs of lists.
     * 
     * Reasoning: This is the optimal approach that leverages merge sort's divide-and-conquer
     * strategy. Instead of merging lists sequentially, merge them in pairs recursively.
     * This ensures each node is processed exactly log k times (tree height),
     * achieving the same complexity as heap approach but without heap overhead.
     * Classic divide-and-conquer solution.
     * 
     * Time Complexity: O(N log k) - each node processed log k times
     * Space Complexity: O(log k) - recursion stack depth
     * 
     * Best when: Need optimal time complexity without heap overhead
     * Worst when: Recursive implementation adds complexity or stack limitations exist
     */
    ListNode* mergeKListsDivideConquer(std::vector<ListNode*>& lists);

    /**
     * Approach 5: Iterative Pair Merging
     * 
     * Merge lists in pairs iteratively.
     * 
     * Reasoning: This implements the same logic as divide-and-conquer but iteratively
     * to avoid recursion overhead. In each round, merge adjacent pairs of lists,
     * reducing the number of lists by half. Continue until only one list remains.
     * This achieves the optimal time complexity while using constant space and
     * avoiding recursion stack.
     * 
     * Time Complexity: O(N log k) - log k rounds, each processing N nodes
     * Space Complexity: O(1) - no recursion stack, constant extra space
     * 
     * Best when: Want optimal complexity without recursion, memory is constrained
     * Worst when: Recursive approach is more intuitive
     */
    ListNode* mergeKListsIterative(std::vector<ListNode*>& lists);

    /**
     * Approach 6: Tournament Tree
     * 
     * Build tournament tree for merging.
     * 
     * Reasoning: Model the merging process as a tournament where each "match"
     * determines the winner (smaller value) between two nodes. Build a binary tree
     * where leaves are list heads and internal nodes represent comparisons.
     * The root always contains the globally minimum node. After extracting the
     * winner, update the path from that leaf to root. More complex than heap
     * but demonstrates tournament tree concept.
     * 
     * Time Complexity: O(N log k) - N tournament operations, each O(log k) updates
     * Space Complexity: O(k) - tournament tree structure
     * 
     * Best when: Educational purposes, understanding tournament trees
     * Worst when: Simpler approaches (heap, divide-conquer) are available
     */
    ListNode* mergeKListsTournament(std::vector<ListNode*>& lists);

private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);
    ListNode* mergeHelper(std::vector<ListNode*>& lists, int left, int right);
    
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };
};

}
}