#pragma once

#include <vector>
#include <unordered_set>
#include <functional>

namespace leetcode {
namespace easy {

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Problem 160: Intersection of Two Linked Lists
 * 
 * Given the heads of two singly linked-lists headA and headB, return the node 
 * at which the two lists intersect. If the two linked lists have no intersection 
 * at all, return null.
 * 
 * For example, the following two linked lists begin to intersect at node c1:
 * A:          a1 → a2 ↘
 *                      c1 → c2 → c3
 * B:     b1 → b2 → b3 ↗
 * 
 * The test cases are generated such that there are no cycles anywhere in the entire linked structure.
 * 
 * Note that the linked lists must retain their original structure after the function returns.
 * 
 * Constraints:
 * - The number of nodes of listA is in the m.
 * - The number of nodes of listB is in the n.
 * - 1 <= m, n <= 3 * 10^4
 * - 1 <= Node.val <= 10^5
 * - 0 <= skipA < m
 * - 0 <= skipB < n
 * - intersectVal is 0 if the two lists do not intersect.
 * - intersectVal == listA[skipA] == listB[skipB] if the two lists intersect.
 * 
 * Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?
 */
class IntersectionOfTwoLinkedLists {
public:
    /**
     * Approach 1: Two Pointers with Length Alignment (Optimal)
     * 
     * Calculate lengths, align the longer list, then traverse both lists together.
     * 
     * Reasoning: Find the lengths of both lists, then advance the longer list
     * by the difference in lengths. This ensures both pointers start at positions
     * that are equidistant from the potential intersection. Then traverse both
     * lists simultaneously until we find the intersection or reach the end.
     * This approach is optimal with O(m+n) time and O(1) space.
     * 
     * Time Complexity: O(m + n) - traverse both lists completely
     * Space Complexity: O(1) - only use constant extra space
     * 
     * Best when: Always optimal, especially when lists have very different lengths
     * Worst when: Never - this approach is consistently efficient
     */
    ListNode* getIntersectionNodeTwoPointers(ListNode* headA, ListNode* headB);

    /**
     * Approach 2: Hash Set for Node Tracking
     * 
     * Use a hash set to store nodes from one list and check intersection with the other.
     * 
     * Reasoning: Traverse the first list and store all node addresses in a hash set.
     * Then traverse the second list and check if any node exists in the hash set.
     * The first node found in the set is the intersection point. This approach
     * is straightforward but uses extra space to store node references.
     * 
     * Time Complexity: O(m + n) - traverse both lists once
     * Space Complexity: O(m) or O(n) - store nodes from one list
     * 
     * Best when: Simplicity preferred, memory not a constraint
     * Worst when: Memory constraints, large lists
     */
    ListNode* getIntersectionNodeHashSet(ListNode* headA, ListNode* headB);

    /**
     * Approach 3: Clever Two Pointers (Mathematical)
     * 
     * Use two pointers that switch lists when reaching the end, guaranteeing meeting point.
     * 
     * Reasoning: Two pointers traverse their respective lists. When a pointer reaches
     * the end, it switches to the other list's head. If there's an intersection,
     * both pointers will meet at the intersection after traversing a total distance
     * of (m + n). If no intersection, both will become null simultaneously.
     * This elegant solution automatically handles length differences.
     * 
     * Time Complexity: O(m + n) - each pointer traverses at most m + n nodes
     * Space Complexity: O(1) - only use pointer variables
     * 
     * Best when: Elegant solution preferred, mathematical insight appreciated
     * Worst when: Code clarity more important than cleverness
     */
    ListNode* getIntersectionNodeCleverTwoPointers(ListNode* headA, ListNode* headB);

    /**
     * Approach 4: Stack-Based Comparison
     * 
     * Use stacks to traverse both lists backwards and find the last common node.
     * 
     * Reasoning: Push all nodes from both lists onto separate stacks, then pop
     * from both stacks simultaneously. The last pair of identical nodes popped
     * represents the intersection point. This approach leverages the fact that
     * intersection creates a Y-shape, so traversing backwards will find the
     * junction point where paths diverge.
     * 
     * Time Complexity: O(m + n) - traverse both lists and process stacks
     * Space Complexity: O(m + n) - store all nodes in stacks
     * 
     * Best when: Backward traversal logic is intuitive, don't mind extra space
     * Worst when: Memory constraints, prefer forward-only traversal
     */
    ListNode* getIntersectionNodeStack(ListNode* headA, ListNode* headB);

    /**
     * Approach 5: Mark and Restore Technique
     * 
     * Temporarily modify one list to create a cycle, then detect cycle in combined structure.
     * 
     * Reasoning: Connect the tail of one list to its head, creating a cycle.
     * Then use cycle detection on the other list. If a cycle is detected,
     * the cycle start point is the intersection. Restore the original structure
     * afterward. This approach leverages cycle detection algorithms but requires
     * careful restoration of the original list structure.
     * 
     * Time Complexity: O(m + n) - traverse lists and detect cycle
     * Space Complexity: O(1) - only use pointer variables
     * 
     * Best when: Educational purposes, demonstrating cycle detection applications
     * Worst when: List modification not allowed, complexity over clarity
     */
    ListNode* getIntersectionNodeMarkAndRestore(ListNode* headA, ListNode* headB);

    /**
     * Approach 6: Functional Programming with Lambda
     * 
     * Use functional programming concepts to create parameterizable intersection finders.
     * 
     * Reasoning: Create higher-order functions that encapsulate different intersection
     * finding strategies. Use lambdas to create customizable intersection detectors
     * that can be parameterized for different approaches. This demonstrates how
     * functional programming concepts can be applied to linked list problems,
     * though it may have performance overhead.
     * 
     * Time Complexity: O(m + n) - depends on underlying strategy chosen
     * Space Complexity: O(1) - constant space plus lambda overhead
     * 
     * Best when: Functional programming style preferred, strategy pattern needed
     * Worst when: Performance critical, simple pointer manipulation sufficient
     */
    ListNode* getIntersectionNodeFunctional(ListNode* headA, ListNode* headB);

private:
    // Helper functions
    int getListLength(ListNode* head);
    ListNode* advanceList(ListNode* head, int steps);
    ListNode* detectCycleStart(ListNode* head);
    
    // Functional approach helpers
    std::function<ListNode*(ListNode*, ListNode*)> createIntersectionFinder();
    
    // Helper functions for testing
public:
    static ListNode* createIntersectedLists(const std::vector<int>& listA, 
                                          const std::vector<int>& listB,
                                          const std::vector<int>& intersection,
                                          ListNode*& headA, ListNode*& headB);
    static void deleteIntersectedLists(ListNode* headA, ListNode* headB, ListNode* intersection);
    static std::vector<int> listToVector(ListNode* head);
    static void deleteList(ListNode* head);
};

}  // namespace easy
}  // namespace leetcode