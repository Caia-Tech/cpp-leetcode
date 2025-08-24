#pragma once

#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <climits>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::TreeNode;

/**
 * Problem 111: Minimum Depth of Binary Tree
 * 
 * Given a binary tree, find its minimum depth.
 * 
 * The minimum depth is the number of nodes along the shortest path from the root node 
 * down to the nearest leaf node.
 * 
 * Note: A leaf is a node with no children.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 10^5]
 * - -1000 <= Node.val <= 1000
 */
class MinimumDepthBinaryTree {
public:
    /**
     * Approach 1: Recursive DFS (Optimal for Most Cases)
     * 
     * Calculate minimum depth recursively by exploring all paths to leaves.
     * 
     * Reasoning: This is the intuitive recursive approach. The minimum depth is
     * 1 + minimum of left and right subtree depths. However, we must handle the
     * case where one subtree is empty - in that case, we cannot take the minimum
     * of 0 and some depth, we must take the non-zero depth. Only when both
     * subtrees exist do we take the true minimum. Base case: null node has depth 0.
     * 
     * Time Complexity: O(n) - visit each node exactly once in worst case
     * Space Complexity: O(h) - recursion stack depth equals tree height
     * 
     * Best when: Balanced trees, when minimum depth is not much smaller than average depth
     * Worst when: Very unbalanced trees where BFS would find answer faster
     */
    int minDepthRecursive(TreeNode* root);

    /**
     * Approach 2: Breadth-First Search (Optimal for Unbalanced Trees)
     * 
     * Use BFS to find the first leaf node encountered, which gives minimum depth.
     * 
     * Reasoning: BFS explores nodes level by level, so the first leaf we encounter
     * will be at the minimum depth. This is more efficient than DFS when the
     * minimum depth is much smaller than the maximum depth, as we can stop early.
     * For each level, process all nodes and check if any is a leaf. Return depth
     * when first leaf is found.
     * 
     * Time Complexity: O(n) - worst case visit all nodes, best case visit few levels
     * Space Complexity: O(w) - queue size proportional to maximum tree width
     * 
     * Best when: Very unbalanced trees, minimum depth much smaller than maximum depth
     * Worst when: Balanced trees where we need to visit most nodes anyway
     */
    int minDepthBFS(TreeNode* root);

    /**
     * Approach 3: Iterative DFS with Stack
     * 
     * Use explicit stack to simulate recursive DFS approach.
     * 
     * Reasoning: Implement the recursive logic using explicit stack to avoid
     * recursion stack overflow in very deep trees. Track (node, depth) pairs
     * and maintain running minimum. Process nodes in DFS order but track
     * minimum depth to all leaves found so far. More complex than recursive
     * but handles deeper trees.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - stack size proportional to tree height
     * 
     * Best when: Very deep trees, avoiding recursion stack limits
     * Worst when: Shallow trees where recursive solution is simpler
     */
    int minDepthDFS(TreeNode* root);

    /**
     * Approach 4: Morris Traversal with Depth Tracking
     * 
     * Use Morris traversal to achieve O(1) auxiliary space complexity.
     * 
     * Reasoning: Morris traversal allows tree traversal without recursion or
     * stack by temporarily modifying tree structure. However, tracking minimum
     * depth is challenging because we need to know when we reach leaves and
     * their depths. This approach demonstrates advanced traversal techniques
     * but is complex to implement correctly for this specific problem.
     * 
     * Time Complexity: O(n) - each edge traversed at most twice
     * Space Complexity: O(1) - only using pointer variables
     * 
     * Best when: Extreme space constraints, demonstrating advanced techniques
     * Worst when: Simplicity preferred, other solutions adequate
     */
    int minDepthMorris(TreeNode* root);

    /**
     * Approach 5: Level Order with Early Termination
     * 
     * Enhanced BFS that processes complete levels and terminates early.
     * 
     * Reasoning: Similar to basic BFS but processes nodes level by level
     * in batches. For each level, count all nodes and process them all
     * before moving to next level. This provides clear level boundaries
     * and allows for early termination as soon as any leaf is found at
     * current level. More structured than basic BFS approach.
     * 
     * Time Complexity: O(n) - worst case, but often better due to early termination
     * Space Complexity: O(w) - queue size equals maximum level width
     * 
     * Best when: Want clear level-by-level processing, early termination benefits
     * Worst when: All leaves are at maximum depth
     */
    int minDepthLevelOrder(TreeNode* root);

    /**
     * Approach 6: Functional Programming with Min Tracking
     * 
     * Use functional programming paradigms with lambda expressions.
     * 
     * Reasoning: Demonstrate functional approach by creating composable
     * functions for depth calculation. Use lambda expressions and higher-order
     * functions to build minimum depth calculator. Shows how tree problems
     * can be approached using functional programming concepts, though may
     * have overhead from function calls and closures.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - function call stack depth
     * 
     * Best when: Functional programming environment, code reusability needed
     * Worst when: Performance critical, simple imperative solutions preferred
     */
    int minDepthFunctional(TreeNode* root);

private:
    // Helper for Morris traversal
    TreeNode* findPredecessor(TreeNode* current);
    
    // Helper for functional approach
    std::function<int(TreeNode*)> createMinDepthCalculator();
    
    // Helper for recursive approach with proper null handling
    int minDepthHelper(TreeNode* root);
    
    // Node state for iterative approaches
    struct NodeDepthPair {
        TreeNode* node;
        int depth;
        NodeDepthPair(TreeNode* n, int d) : node(n), depth(d) {}
    };
};

}  // namespace easy
}  // namespace leetcode