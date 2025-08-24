#pragma once

#include <queue>
#include <stack>
#include <vector>
#include <functional>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::TreeNode;

/**
 * Problem 226: Invert Binary Tree
 * 
 * Given the root of a binary tree, invert the tree, and return its root.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 100]
 * - -100 <= Node.val <= 100
 * 
 * Note: This is the famous problem that a Google candidate was asked and couldn't solve,
 * leading to the rejection despite creating Homebrew. The problem demonstrates basic
 * tree manipulation and has become iconic in tech interviews.
 */
class InvertBinaryTree {
public:
    /**
     * Approach 1: Recursive DFS (Optimal)
     * 
     * Recursively swap left and right children for each node.
     * 
     * Reasoning: The most elegant and intuitive solution. For each node,
     * swap its left and right children, then recursively invert both
     * subtrees. The recursion naturally handles the tree structure,
     * and the solution is just a few lines of code. This demonstrates
     * how recursion can make tree problems very clean and readable.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion stack, h is tree height
     * 
     * Best when: Clean recursive solution preferred, most readable
     * Worst when: Very deep trees might cause stack overflow
     */
    TreeNode* invertTreeRecursive(TreeNode* root);

    /**
     * Approach 2: Iterative BFS (Level Order)
     * 
     * Use BFS to process nodes level by level, swapping children.
     * 
     * Reasoning: Process tree level by level using a queue. For each node,
     * swap its left and right children, then add children to queue for
     * next level processing. This avoids recursion and processes tree
     * in breadth-first manner. Good for wide trees and when avoiding
     * recursion stack limitations.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(w) - queue size, w is maximum tree width
     * 
     * Best when: Avoiding recursion, wide trees, level-order processing
     * Worst when: Deep narrow trees (queue overhead without benefit)
     */
    TreeNode* invertTreeBFS(TreeNode* root);

    /**
     * Approach 3: Iterative DFS with Stack
     * 
     * Use explicit stack to simulate recursive DFS.
     * 
     * Reasoning: Simulate recursive approach using explicit stack to avoid
     * recursion limits. Push root onto stack, then for each node, swap
     * children and push non-null children onto stack. This gives same
     * traversal pattern as recursion but with explicit memory management.
     * Useful for very deep trees.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - stack size proportional to tree height
     * 
     * Best when: Need DFS pattern without recursion, deep trees
     * Worst when: Recursive solution is cleaner and stack limits aren't a concern
     */
    TreeNode* invertTreeDFS(TreeNode* root);

    /**
     * Approach 4: Morris Traversal (Space Optimized)
     * 
     * Use Morris traversal for O(1) space tree inversion.
     * 
     * Reasoning: Morris traversal creates temporary links (threads) to achieve
     * O(1) space complexity. We traverse tree without recursion or stack by
     * temporarily modifying tree structure. For each node, we swap children
     * and use threading to navigate. Complex to implement but demonstrates
     * advanced tree traversal techniques and achieves optimal space complexity.
     * 
     * Time Complexity: O(n) - each edge traversed at most twice
     * Space Complexity: O(1) - only using pointer variables
     * 
     * Best when: Space is extremely constrained, demonstrating advanced techniques
     * Worst when: Simplicity preferred, temporary tree modification concerns
     */
    TreeNode* invertTreeMorris(TreeNode* root);

    /**
     * Approach 5: Post-order Recursive
     * 
     * Use post-order traversal to invert tree bottom-up.
     * 
     * Reasoning: Process children first, then swap them. This ensures that
     * when we swap children of a node, those children's subtrees are already
     * inverted. While functionally equivalent to pre-order approach, it
     * demonstrates different recursive patterns and might be clearer for
     * some to understand the "process children first" logic.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion stack depth
     * 
     * Best when: Post-order processing pattern preferred
     * Worst when: Pre-order approach is simpler for this problem
     */
    TreeNode* invertTreePostOrder(TreeNode* root);

    /**
     * Approach 6: Functional Programming Style
     * 
     * Use higher-order functions and immutable-style operations.
     * 
     * Reasoning: Demonstrate functional programming concepts applied to tree
     * manipulation. Use std::function and lambda expressions to create
     * composable tree operations. While more complex than needed for this
     * simple problem, it shows how functional programming paradigms can
     * be applied to tree algorithms and creates reusable components.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion through function calls
     * 
     * Best when: Functional programming paradigm, reusable components
     * Worst when: Simple direct solution preferred
     */
    TreeNode* invertTreeFunctional(TreeNode* root);

private:
    // Helper for Morris traversal
    TreeNode* findPredecessor(TreeNode* node);
    
    // Helper for functional approach
    std::function<TreeNode*(TreeNode*)> createInverter();
    
    // Helper to apply function to tree nodes
    void applyToTree(TreeNode* root, std::function<void(TreeNode*)> fn);
};

}  // namespace easy
}  // namespace leetcode