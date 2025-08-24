#pragma once

#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

namespace leetcode {
namespace easy {

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * Problem 108: Convert Sorted Array to Binary Search Tree
 * 
 * Given an integer array nums where the elements are sorted in ascending order, 
 * convert it to a height-balanced binary search tree.
 * 
 * A height-balanced binary tree is a binary tree in which the depth of the two 
 * subtrees of every node never differs by more than one.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - nums is sorted in a strictly increasing order.
 */
class ConvertSortedArrayToBST {
public:
    /**
     * Approach 1: Recursive Divide and Conquer (Optimal)
     * 
     * Choose the middle element as root and recursively build left and right subtrees.
     * 
     * Reasoning: Since the array is sorted, the middle element ensures that there are
     * equal numbers of elements on both sides (or differ by at most 1). This guarantees
     * a height-balanced BST. The recursive approach naturally handles the divide-and-conquer
     * strategy where each subproblem is solved by choosing the middle element as the root
     * of that subtree.
     * 
     * Time Complexity: O(n) - visit each element once to create a tree node
     * Space Complexity: O(log n) - recursion depth for balanced tree
     * 
     * Best when: Always - this is the optimal and most intuitive solution
     * Worst when: Never - this approach is universally preferred
     */
    TreeNode* sortedArrayToBSTRecursive(std::vector<int>& nums);

    /**
     * Approach 2: Iterative with Stack
     * 
     * Use a stack to simulate the recursive approach iteratively.
     * 
     * Reasoning: Convert the recursive solution to iterative using explicit stack
     * to avoid recursion overhead. Store range information (start, end indices)
     * along with tree nodes in the stack. This approach follows the same logic
     * as recursive but manages the call stack explicitly, which can be useful
     * for very large inputs where stack overflow might be a concern.
     * 
     * Time Complexity: O(n) - visit each element once
     * Space Complexity: O(log n) - explicit stack depth
     * 
     * Best when: Stack overflow concerns with deep recursion, iterative preference
     * Worst when: Code clarity is prioritized over stack management
     */
    TreeNode* sortedArrayToBSTIterative(std::vector<int>& nums);

    /**
     * Approach 3: Pre-order Construction
     * 
     * Build the tree in pre-order fashion by always selecting middle elements.
     * 
     * Reasoning: Instead of building the tree recursively, create nodes in pre-order
     * sequence by maintaining explicit ranges for left and right subtrees. This
     * approach gives more control over the construction order and can be optimized
     * for specific tree traversal requirements. The pre-order nature means we
     * create parent nodes before their children.
     * 
     * Time Complexity: O(n) - create each node once
     * Space Complexity: O(log n) - recursion depth
     * 
     * Best when: Need pre-order construction sequence, explicit range management
     * Worst when: Standard recursive approach is sufficient
     */
    TreeNode* sortedArrayToBSTPreOrder(std::vector<int>& nums);

    /**
     * Approach 4: Random Middle Selection
     * 
     * When there are two middle elements, randomly choose one to create different tree structures.
     * 
     * Reasoning: For arrays with even length, there are two potential middle elements.
     * Different choices lead to different but equally valid balanced BSTs. Random
     * selection can provide variety in tree structure, which might be useful for
     * testing or applications requiring different tree layouts. This approach
     * demonstrates that multiple valid solutions exist for this problem.
     * 
     * Time Complexity: O(n) - visit each element once
     * Space Complexity: O(log n) - recursion depth
     * 
     * Best when: Need variety in tree structures, testing different layouts
     * Worst when: Deterministic output is required, consistency is important
     */
    TreeNode* sortedArrayToBSTRandom(std::vector<int>& nums);

    /**
     * Approach 5: Level-Order Construction
     * 
     * Build the tree level by level using queue-based approach.
     * 
     * Reasoning: Instead of depth-first construction, build the tree breadth-first
     * by processing each level completely before moving to the next. Use a queue
     * to maintain the order of nodes to be processed along with their corresponding
     * array ranges. This approach gives explicit control over tree level construction
     * and can be useful when level-wise processing is preferred.
     * 
     * Time Complexity: O(n) - process each element once
     * Space Complexity: O(n) - queue can hold all nodes in worst case
     * 
     * Best when: Level-order construction preferred, breadth-first building needed
     * Worst when: Depth-first construction is more natural, memory usage is critical
     */
    TreeNode* sortedArrayToBSTLevelOrder(std::vector<int>& nums);

    /**
     * Approach 6: Functional Programming with Lambda
     * 
     * Use lambda functions and functional programming concepts for tree construction.
     * 
     * Reasoning: Apply functional programming paradigms by creating a tree builder
     * function that encapsulates the recursive logic. Use lambda expressions to
     * create closures that capture the array and provide a clean, functional
     * interface. This approach demonstrates how functional programming concepts
     * can be applied to tree construction problems.
     * 
     * Time Complexity: O(n) - visit each element once
     * Space Complexity: O(log n) - recursion depth plus lambda overhead
     * 
     * Best when: Functional programming style preferred, lambda expressions useful
     * Worst when: Traditional recursive approach is clearer, performance is critical
     */
    TreeNode* sortedArrayToBSTFunctional(std::vector<int>& nums);

private:
    // Helper functions for different approaches
    TreeNode* buildBSTRecursive(std::vector<int>& nums, int left, int right);
    TreeNode* buildBSTPreOrder(std::vector<int>& nums, int left, int right);
    TreeNode* buildBSTRandom(std::vector<int>& nums, int left, int right);
    
    // Structure for iterative approach
    struct TreeRange {
        TreeNode* node;
        int left;
        int right;
        TreeRange(TreeNode* n, int l, int r) : node(n), left(l), right(r) {}
    };
    
    // Structure for level-order approach
    struct NodeRange {
        TreeNode** nodeRef;
        int left;
        int right;
        NodeRange(TreeNode** ref, int l, int r) : nodeRef(ref), left(l), right(r) {}
    };
    
    // Helper for functional approach
    std::function<TreeNode*(int, int)> createBSTBuilder(std::vector<int>& nums);
    
    // Random number generator for random approach
    static int getRandomInRange(int min, int max);
};

}  // namespace easy
}  // namespace leetcode