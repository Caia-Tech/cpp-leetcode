#pragma once

#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::TreeNode;

/**
 * Problem 104: Maximum Depth of Binary Tree
 * 
 * Given the root of a binary tree, return its maximum depth.
 * 
 * A binary tree's maximum depth is the number of nodes along the longest path 
 * from the root node down to the farthest leaf node.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 10^4]
 * - -100 <= Node.val <= 100
 */
class MaximumDepthBinaryTree {
public:
    /**
     * Approach 1: Recursive DFS (Optimal)
     * 
     * Recursively find depth of left and right subtrees.
     * 
     * Reasoning: This is the most elegant and intuitive solution. The depth
     * of a tree is 1 + maximum depth of its subtrees. Base case: null tree
     * has depth 0. For each node, recursively calculate depth of left and
     * right subtrees, take maximum, and add 1. This naturally follows the
     * tree structure and is very efficient with minimal code.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion stack, where h is tree height
     * 
     * Best when: Clean recursive solution preferred, balanced trees
     * Worst when: Very deep trees might cause stack overflow
     */
    int maxDepthRecursive(TreeNode* root);

    /**
     * Approach 2: Iterative BFS (Level Order)
     * 
     * Use BFS to traverse level by level, counting levels.
     * 
     * Reasoning: BFS naturally processes trees level by level. Use a queue
     * to store nodes at current level, process entire level at once, then
     * move to next level. Count the number of levels processed. This approach
     * is iterative (no recursion) and gives clear understanding of tree depth
     * as the number of levels.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(w) - where w is maximum width of tree
     * 
     * Best when: Avoiding recursion, wide trees, need level information
     * Worst when: Deep narrow trees (queue overhead without benefit)
     */
    int maxDepthBFS(TreeNode* root);

    /**
     * Approach 3: Iterative DFS with Stack
     * 
     * Use explicit stack to simulate recursive DFS.
     * 
     * Reasoning: Simulate recursive approach using explicit stack to track
     * nodes and their depths. Push root with depth 1, then for each node,
     * push its children with depth+1. Track maximum depth seen. This avoids
     * recursion limits and gives more control over the traversal process.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - stack can hold up to tree height
     * 
     * Best when: Need DFS pattern without recursion, very deep trees
     * Worst when: Recursive solution is cleaner and sufficient
     */
    int maxDepthDFS(TreeNode* root);

    /**
     * Approach 4: Morris Traversal with Depth Tracking
     * 
     * Use Morris traversal to achieve O(1) space complexity.
     * 
     * Reasoning: Morris traversal modifies tree temporarily to create threads,
     * allowing traversal without stack or recursion. We track depth as we
     * traverse and maintain maximum depth seen. This achieves optimal space
     * complexity but is complex to implement and modifies tree structure
     * temporarily. Demonstrates advanced tree traversal techniques.
     * 
     * Time Complexity: O(n) - each edge traversed at most twice
     * Space Complexity: O(1) - no extra space besides variables
     * 
     * Best when: Space is extremely constrained, demonstrating advanced techniques
     * Worst when: Simplicity preferred, temporary tree modification concerns
     */
    int maxDepthMorris(TreeNode* root);

    /**
     * Approach 5: Two-Stack DFS (Explicit Depth Tracking)
     * 
     * Use two stacks to track nodes and their corresponding depths.
     * 
     * Reasoning: More explicit version of stack-based DFS. One stack holds
     * nodes, another holds corresponding depths. This separates node tracking
     * from depth tracking, making the algorithm clearer. While using two stacks
     * instead of one, it can be easier to understand and debug than the
     * combined approach.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - two stacks each of size up to tree height
     * 
     * Best when: Clearer separation of concerns needed, debugging
     * Worst when: Memory usage should be minimized
     */
    int maxDepthTwoStack(TreeNode* root);

    /**
     * Approach 6: Level-by-Level BFS with Size Tracking
     * 
     * Process each level completely before moving to next.
     * 
     * Reasoning: Enhanced BFS that processes complete levels at once by
     * tracking queue size at each level. For each level, dequeue all nodes
     * currently in queue (one complete level), enqueue their children,
     * then increment depth. This approach clearly separates level processing
     * and can be extended to solve level-specific problems.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(w) - queue holds at most one level (width w)
     * 
     * Best when: Need to process complete levels, level-aware algorithms
     * Worst when: Simple depth calculation is all that's needed
     */
    int maxDepthLevelBFS(TreeNode* root);

private:
    // Helper for two-stack approach
    struct NodeDepthPair {
        TreeNode* node;
        int depth;
        NodeDepthPair(TreeNode* n, int d) : node(n), depth(d) {}
    };
};

}  // namespace easy
}  // namespace leetcode