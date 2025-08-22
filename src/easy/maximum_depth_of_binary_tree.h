#pragma once

#include <algorithm>
#include <queue>
#include <stack>

#include "utils/data_structures.h"

namespace leetcode {
namespace easy {

/**
 * Problem 104: Maximum Depth of Binary Tree
 *
 * Given the root of a binary tree, return its maximum depth.
 * A binary tree's maximum depth is the number of nodes along the longest
 * path from the root node down to the farthest leaf node.
 *
 * Each class below demonstrates a unique strategy with detailed reasoning
 * and complexity analysis.
 */

/**
 * Approach 1: Bottom-Up Recursion
 *
 * Recursively compute the depth of left and right subtrees and return the
 * maximum plus one for the current node.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(h) recursion stack
 */
class MaxDepthRecursive {
public:
    int maxDepth(utils::TreeNode* root);
};

/**
 * Approach 2: Top-Down Recursion with Accumulator
 *
 * Traverse the tree carrying the current depth, updating a shared maximum.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(h) recursion stack
 */
class MaxDepthTopDown {
public:
    int maxDepth(utils::TreeNode* root);

private:
    void dfs(utils::TreeNode* node, int depth, int& best);
};

/**
 * Approach 3: Iterative DFS Using Stack
 *
 * Simulate recursion with an explicit stack of {node, depth} pairs.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(h)
 */
class MaxDepthIterativeDFS {
public:
    int maxDepth(utils::TreeNode* root);
};

/**
 * Approach 4: BFS with Depth Tracking
 *
 * Perform level-order traversal storing depth alongside each node.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(w) where w is max width
 */
class MaxDepthBFSQueue {
public:
    int maxDepth(utils::TreeNode* root);
};

/**
 * Approach 5: BFS with Sentinel Marker
 *
 * Use a queue with nullptr markers to separate levels.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(w)
 */
class MaxDepthBFSSentinel {
public:
    int maxDepth(utils::TreeNode* root);
};

/**
 * Approach 6: BFS Using Level Size
 *
 * Count nodes per level using queue size to determine depth increments.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(w)
 */
class MaxDepthLevelCount {
public:
    int maxDepth(utils::TreeNode* root);
};

}  // namespace easy
}  // namespace leetcode

