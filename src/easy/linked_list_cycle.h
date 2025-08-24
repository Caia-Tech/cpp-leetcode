#pragma once

#include <unordered_set>
#include <vector>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::ListNode;

/**
 * Problem 141: Linked List Cycle
 * 
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * 
 * There is a cycle in a linked list if there is some node in the list that can be reached 
 * again by continuously following the next pointer. Internally, pos is used to denote the 
 * index of the node that tail's next pointer is connected to. Note that pos is not passed 
 * as a parameter.
 * 
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [0, 10^4]
 * - -10^5 <= Node.val <= 10^5
 * - pos is -1 or a valid index in the linked list
 * 
 * Follow up: Can you solve it using O(1) (i.e. constant) memory?
 */
class LinkedListCycle {
public:
    /**
     * Approach 1: Floyd's Cycle Detection (Two Pointers) - Optimal
     * 
     * Use slow and fast pointers (tortoise and hare algorithm).
     * 
     * Reasoning: This is the optimal solution using O(1) space. The slow pointer moves
     * one step at a time while the fast pointer moves two steps. If there's a cycle,
     * they will eventually meet. If there's no cycle, fast pointer will reach the end.
     * This works because in a cycle, the fast pointer will "lap" the slow pointer.
     * Mathematical proof: If cycle length is L, after L iterations, fast is 2L ahead,
     * which means they're at the same position in the cycle.
     * 
     * Time Complexity: O(n) - at most visit each node twice
     * Space Complexity: O(1) - only two pointers used
     * 
     * Best when: Need optimal space complexity, standard interview solution
     * Worst when: Need to find cycle start position (requires modification)
     */
    bool hasCycleFloyd(ListNode* head);

    /**
     * Approach 2: Hash Set
     * 
     * Store visited nodes in a hash set.
     * 
     * Reasoning: As we traverse the list, we store each node's address in a hash set.
     * If we encounter a node that's already in the set, we've found a cycle.
     * This is intuitive and straightforward but uses extra space. The key insight
     * is that we're storing node pointers, not values, since values can repeat
     * in a non-cyclic list.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(n) - hash set stores up to n nodes
     * 
     * Best when: Need simple, easy-to-understand solution
     * Worst when: Memory is constrained, O(1) space required
     */
    bool hasCycleHashSet(ListNode* head);

    /**
     * Approach 3: Node Marking (Destructive)
     * 
     * Temporarily modify node values to mark visited nodes.
     * 
     * Reasoning: We can mark visited nodes by setting their values to a sentinel
     * value outside the constraint range (e.g., 10^6). If we encounter a node
     * with this sentinel value, we've found a cycle. After detection, we restore
     * original values. This achieves O(1) space but modifies the list temporarily.
     * Note: This approach is generally not recommended in production code.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(1) - no extra space, but modifies input
     * 
     * Best when: Educational purposes, when modification is acceptable
     * Worst when: Concurrent access, input must remain unchanged
     */
    bool hasCycleNodeMarking(ListNode* head);

    /**
     * Approach 4: Try-Catch with Timeout
     * 
     * Use a counter with maximum iterations to detect infinite loop.
     * 
     * Reasoning: If we traverse more than n nodes (where n is a reasonable maximum),
     * we must have a cycle. This is a pragmatic approach that doesn't require
     * extra space or two pointers. We use the constraint that max nodes is 10^4,
     * so if we iterate more than that, there's definitely a cycle.
     * 
     * Time Complexity: O(n) - bounded by maximum node count
     * Space Complexity: O(1) - only a counter variable
     * 
     * Best when: Simple implementation needed, node count is known
     * Worst when: Node count is unknown or very large
     */
    bool hasCycleCounter(ListNode* head);

    /**
     * Approach 5: Reverse Detection
     * 
     * Reverse the list and check if we return to head.
     * 
     * Reasoning: If we reverse a list with a cycle, we'll eventually return to
     * the starting node. This is because reversing changes the direction of
     * pointers, and in a cycle, this creates a path back to the start.
     * This approach is destructive and complex but demonstrates an interesting
     * property of cyclic structures. We restore the list after detection.
     * 
     * Time Complexity: O(n) - traverse list for reversal
     * Space Complexity: O(1) - in-place reversal
     * 
     * Best when: Educational purposes, understanding cycle properties
     * Worst when: Need non-destructive solution, concurrent access
     */
    bool hasCycleReverse(ListNode* head);

    /**
     * Approach 6: Brent's Algorithm (Optimized Floyd)
     * 
     * Improved cycle detection that's faster than Floyd's in practice.
     * 
     * Reasoning: Brent's algorithm is an optimization of Floyd's algorithm.
     * Instead of moving both pointers continuously, we move the fast pointer
     * in increasing powers of 2. The slow pointer is moved to fast pointer's
     * position periodically. This reduces the number of iterations needed
     * to detect a cycle, making it faster in practice while maintaining
     * O(1) space complexity.
     * 
     * Time Complexity: O(n) - fewer iterations than Floyd's on average
     * Space Complexity: O(1) - only pointers and counters
     * 
     * Best when: Need fastest O(1) space solution, large lists
     * Worst when: Simplicity is more important than optimization
     */
    bool hasCycleBrent(ListNode* head);

private:
    // Helper constant for node marking approach
    static constexpr int SENTINEL = 1000001;  // Outside constraint range
    
    // Helper to restore marked nodes (for approach 3)
    void restoreNodes(ListNode* head, const std::vector<int>& original_values);
};

}  // namespace easy
}  // namespace leetcode