#pragma once

#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::TreeNode;

/**
 * Problem 110: Balanced Binary Tree
 * 
 * Given a binary tree, determine if it is height-balanced.
 * 
 * For this problem, a height-balanced binary tree is defined as:
 * a binary tree in which the left and right subtrees of every node differ in height 
 * by no more than 1.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 5000]
 * - -10^4 <= Node.val <= 10^4
 */
class BalancedBinaryTree {
public:
    /**
     * Approach 1: Top-Down Recursive (Naive)
     * 
     * Check balance for each node by calculating heights of subtrees.
     * 
     * Reasoning: For each node, calculate heights of left and right subtrees
     * and check if difference is ≤ 1. Recursively check if subtrees are balanced.
     * This approach recalculates heights multiple times for the same nodes,
     * making it inefficient but easy to understand. Each height calculation
     * visits all nodes in subtree, leading to O(n²) complexity in worst case.
     * 
     * Time Complexity: O(n²) - height calculation for each node
     * Space Complexity: O(h) - recursion stack depth
     * 
     * Best when: Understanding problem, small trees
     * Worst when: Large trees (inefficient due to repeated calculations)
     */
    bool isBalancedTopDown(TreeNode* root);

    /**
     * Approach 2: Bottom-Up Recursive (Optimal)
     * 
     * Calculate height and check balance in single traversal.
     * 
     * Reasoning: This is the optimal solution. During height calculation,
     * simultaneously check balance condition. If any subtree is unbalanced,
     * return special value (-1) to indicate imbalance. This avoids recalculation
     * and solves problem in single pass. The key insight: combine height
     * calculation with balance checking to eliminate redundant work.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion stack depth
     * 
     * Best when: Always - this is the optimal approach
     * Worst when: Never - this is the standard solution
     */
    bool isBalancedBottomUp(TreeNode* root);

    /**
     * Approach 3: Iterative BFS with Height Caching
     * 
     * Use BFS to process nodes, caching heights to avoid recalculation.
     * 
     * Reasoning: Process tree level by level, calculating and caching heights
     * for each node. Use map to store heights to avoid recalculation. For each
     * node, use cached heights of children to determine balance. While avoiding
     * recursion, this approach uses extra space for caching but provides
     * clear separation between traversal and computation.
     * 
     * Time Complexity: O(n) - visit each node once, O(1) height lookup
     * Space Complexity: O(n) - cache heights for all nodes
     * 
     * Best when: Avoiding recursion, need height information for other purposes
     * Worst when: Space is constrained, recursive solution acceptable
     */
    bool isBalancedBFS(TreeNode* root);

    /**
     * Approach 4: Iterative DFS with Stack
     * 
     * Use explicit stack to simulate recursive bottom-up approach.
     * 
     * Reasoning: Simulate optimal recursive approach using explicit stack
     * to avoid recursion limits. Use post-order traversal pattern to process
     * children before parent. Maintain state about processed nodes and their
     * heights. More complex than recursive version but handles very deep trees.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - stack size proportional to tree height
     * 
     * Best when: Very deep trees, avoiding recursion stack overflow
     * Worst when: Recursive solution is cleaner and sufficient
     */
    bool isBalancedDFS(TreeNode* root);

    /**
     * Approach 5: Morris Traversal with Height Tracking
     * 
     * Use Morris traversal to achieve O(1) space complexity.
     * 
     * Reasoning: Morris traversal can traverse tree without recursion or stack
     * by temporarily modifying tree structure. However, checking balance requires
     * height information, which is challenging to maintain in O(1) space during
     * Morris traversal. This approach demonstrates advanced tree traversal but
     * is complex and less practical than other solutions.
     * 
     * Time Complexity: O(n) - each edge traversed at most twice
     * Space Complexity: O(1) - only using pointer variables
     * 
     * Best when: Extreme space constraints, demonstrating advanced techniques
     * Worst when: Simplicity preferred, standard solutions adequate
     */
    bool isBalancedMorris(TreeNode* root);

    /**
     * Approach 6: Parallel Height Calculation
     * 
     * Calculate heights of left and right subtrees independently.
     * 
     * Reasoning: For educational purposes, demonstrate how balance checking
     * can be thought of as independent height calculations. While this doesn't
     * improve algorithmic complexity, it shows how the problem can be
     * decomposed and could potentially benefit from parallel processing
     * in multi-threaded environments. Maintains clarity of logic separation.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - recursion depth
     * 
     * Best when: Educational purposes, potential parallel processing
     * Worst when: Single-threaded optimization needed
     */
    bool isBalancedParallel(TreeNode* root);

private:
    // Helper for top-down approach
    int calculateHeight(TreeNode* root);
    
    // Helper for bottom-up approach (returns -1 if unbalanced)
    int calculateHeightAndCheckBalance(TreeNode* root);
    
    // Helper for BFS approach
    int getHeight(TreeNode* node, std::unordered_map<TreeNode*, int>& heightCache);
    
    // Helper for DFS approach
    struct NodeState {
        TreeNode* node;
        bool processed;
        int height;
        
        NodeState(TreeNode* n) : node(n), processed(false), height(0) {}
    };
    
    // Helper for Morris traversal
    TreeNode* findPredecessor(TreeNode* current);
    
    // Helper for parallel approach
    std::pair<int, bool> calculateHeightAndBalance(TreeNode* root);
    
    // Constants
    static constexpr int UNBALANCED = -1;
};

}  // namespace easy
}  // namespace leetcode