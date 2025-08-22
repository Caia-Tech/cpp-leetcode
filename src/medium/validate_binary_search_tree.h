#pragma once

#include <vector>
#include <algorithm>
#include <stack>
#include <limits>
#include "../utils/data_structures.h"

using namespace leetcode::utils;

namespace leetcode {
namespace medium {

/**
 * Problem 98: Validate Binary Search Tree
 * 
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * 
 * A valid BST is defined as follows:
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [1, 10^4].
 * - -2^31 <= Node.val <= 2^31 - 1
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class ValidateBinarySearchTree {
public:
    /**
     * Approach 1: Inorder Traversal with Array (Classic)
     * 
     * Perform inorder traversal to get values in sorted order if BST is valid.
     * 
     * Reasoning: In a valid BST, inorder traversal produces values in strictly increasing
     * order. Collect all values during traversal, then check if array is sorted and
     * contains no duplicates. This approach directly leverages the fundamental BST property
     * that inorder traversal yields sorted sequence. Simple to understand and implement,
     * making it ideal for interviews. The explicit array makes verification straightforward
     * and allows for easy debugging of edge cases.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(n) - array storage + recursion stack
     * 
     * Best when: Learning BST properties, need explicit sorted sequence, debugging
     * Worst when: Space constraints, large trees, need optimal space efficiency
     */
    bool isValidBST(TreeNode* root);

    /**
     * Approach 2: Inorder Traversal with Previous Value (Space Optimized)
     * 
     * Track only previous value during inorder traversal for immediate validation.
     * 
     * Reasoning: Instead of storing entire inorder sequence, maintain only the previous
     * value seen during traversal. At each node, verify current value > previous value.
     * This optimizes space to O(1) auxiliary (excluding recursion) while maintaining
     * the same core logic. Early termination possible when violation detected.
     * Demonstrates how to optimize classic algorithms by removing unnecessary storage
     * when only recent state matters.
     * 
     * Time Complexity: O(n) - visit each node once, early termination possible
     * Space Complexity: O(h) - recursion stack only, where h is tree height
     * 
     * Best when: Space efficiency important, large trees, standard interview solution
     * Worst when: Need full traversal data, debugging complex cases, teaching BST properties
     */
    bool isValidBSTInorderOptimized(TreeNode* root);

    /**
     * Approach 3: Recursive with Min/Max Bounds
     * 
     * Recursively validate each subtree with tightening min/max constraints.
     * 
     * Reasoning: For each node, maintain valid range [min, max] that its value must satisfy.
     * Root can have any value, left subtree must have values < root.val, right subtree
     * must have values > root.val. Recursively tighten bounds: left child gets range
     * [min, root.val), right child gets range (root.val, max]. This approach directly
     * models BST definition and makes constraint propagation explicit. Very intuitive
     * and handles edge cases naturally.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - recursion stack depth
     * 
     * Best when: Intuitive recursive thinking, constraint modeling, teaching BST definition
     * Worst when: Iterative preferred, integer overflow concerns, stack space limited
     */
    bool isValidBSTBounds(TreeNode* root);

    /**
     * Approach 4: Iterative Inorder with Stack
     * 
     * Implement inorder traversal iteratively using explicit stack.
     * 
     * Reasoning: Convert recursive inorder to iterative using stack to manage traversal
     * state. Push all left nodes, process current, move to right. Track previous value
     * to validate BST property without recursion overhead. This approach demonstrates
     * how to eliminate recursion when stack space is constrained or when iterative
     * solutions are preferred. Maintains same logic as recursive inorder but with
     * explicit control over execution.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - explicit stack storage
     * 
     * Best when: Recursion not allowed, stack space controlled, iterative preference
     * Worst when: Recursive solutions simpler, teaching tree traversal concepts
     */
    bool isValidBSTIterative(TreeNode* root);

    /**
     * Approach 5: Morris Inorder Traversal (O(1) Space)
     * 
     * Use threading technique for inorder traversal without recursion or stack.
     * 
     * Reasoning: Morris traversal temporarily modifies tree structure by creating
     * threads (links) to enable O(1) space inorder traversal. For each node, find
     * inorder predecessor and create temporary link. After processing, restore
     * original structure. This advanced technique achieves true O(1) space complexity
     * while maintaining O(n) time. Demonstrates sophisticated tree manipulation
     * and optimal space utilization.
     * 
     * Time Complexity: O(n) - each edge traversed at most twice
     * Space Complexity: O(1) - no extra space except variables
     * 
     * Best when: Extreme space constraints, demonstrating advanced techniques, research
     * Worst when: Tree modification not allowed, simpler approaches sufficient, readability important
     */
    bool isValidBSTMorris(TreeNode* root);

    /**
     * Approach 6: Level Order with Range Validation
     * 
     * Use BFS to validate BST properties level by level with range constraints.
     * 
     * Reasoning: Combine level-order traversal (BFS) with min/max range validation.
     * For each node, verify its value is within valid range, then add children to
     * queue with updated ranges. This approach provides different perspective on
     * BST validation using breadth-first exploration rather than depth-first.
     * Can be useful for debugging or when level-wise processing is beneficial.
     * Demonstrates how BFS can solve problems typically handled by DFS.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(w) - queue storage, where w is maximum width
     * 
     * Best when: Level-order processing preferred, BFS perspective useful, debugging by levels
     * Worst when: DFS more natural, queue overhead unnecessary, simple validation sufficient
     */
    bool isValidBSTLevelOrder(TreeNode* root);

private:
    // Helper functions for recursive approaches
    void inorderTraversal(TreeNode* node, std::vector<int>& values);
    bool inorderWithPrev(TreeNode* node, TreeNode*& prev);
    bool validateWithBounds(TreeNode* node, long long minVal, long long maxVal);
    
    // Morris traversal helpers
    TreeNode* getInorderPredecessor(TreeNode* node);
    
    // Level order helper structure
    struct NodeWithRange {
        TreeNode* node;
        long long minVal;
        long long maxVal;
        
        NodeWithRange(TreeNode* n, long long min_val, long long max_val)
            : node(n), minVal(min_val), maxVal(max_val) {}
    };
};

}
}