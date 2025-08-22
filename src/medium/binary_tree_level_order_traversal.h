#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include "../utils/data_structures.h"

using namespace leetcode::utils;

namespace leetcode {
namespace medium {

/**
 * Problem 102: Binary Tree Level Order Traversal
 * 
 * Given the root of a binary tree, return the level order traversal of its nodes' values. 
 * (i.e., from left to right, level by level).
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 2000].
 * - -1000 <= Node.val <= 1000
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class BinaryTreeLevelOrderTraversal {
public:
    /**
     * Approach 1: Standard BFS with Queue (Classic)
     * 
     * Use breadth-first search with queue to traverse level by level.
     * 
     * Reasoning: Level-order traversal is the natural application of BFS. Use queue
     * to process nodes in FIFO order. At each level, record current queue size to
     * know how many nodes to process for current level. Process exactly that many
     * nodes, adding their children to queue for next level. This guarantees
     * level-by-level processing and creates clean separation between levels.
     * Most intuitive and commonly used approach for level-order problems.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(w) - queue size proportional to maximum width of tree
     * 
     * Best when: Standard level-order traversal, intuitive implementation
     * Worst when: Memory constraints with very wide trees, need other traversal orders
     */
    std::vector<std::vector<int>> levelOrder(TreeNode* root);

    /**
     * Approach 2: DFS with Level Parameter (Recursive)
     * 
     * Use depth-first search with level tracking to build result.
     * 
     * Reasoning: Instead of BFS, use DFS but track current level. Pass level as
     * parameter in recursive calls. If result vector doesn't have vector for
     * current level yet, create it. Then add current node's value to appropriate
     * level vector. This converts the natural DFS traversal into level-order
     * output by organizing values by their level. Demonstrates how recursion
     * can solve problems typically associated with iteration.
     * 
     * Time Complexity: O(n) - visit each node once in DFS
     * Space Complexity: O(h) - recursion stack depth, plus O(n) result storage
     * 
     * Best when: Prefer recursive solutions, need to combine with other DFS logic
     * Worst when: Deep trees risk stack overflow, BFS more natural for level-order
     */
    std::vector<std::vector<int>> levelOrderDFS(TreeNode* root);

    /**
     * Approach 3: Two-Queue Approach
     * 
     * Use two queues to separate current and next level nodes.
     * 
     * Reasoning: Alternative to tracking queue size - use two queues where one
     * holds current level nodes and other collects next level nodes. Process
     * all nodes from current queue, adding children to next queue. When current
     * is empty, swap queues and repeat. This makes level boundaries very explicit
     * and can be easier to understand than size-tracking approach. Also enables
     * easy modification for level-specific processing.
     * 
     * Time Complexity: O(n) - each node processed exactly once
     * Space Complexity: O(w) - two queues, total space proportional to max width
     * 
     * Best when: Level boundaries need to be very explicit, educational clarity
     * Worst when: Memory usage concerns with two queues, standard BFS sufficient
     */
    std::vector<std::vector<int>> levelOrderTwoQueues(TreeNode* root);

    /**
     * Approach 4: Level-by-Level with HashMap
     * 
     * Use DFS with hashmap to group nodes by level.
     * 
     * Reasoning: Traverse tree using any order (preorder chosen here) while
     * tracking current level. Use hashmap where key is level and value is vector
     * of node values at that level. After traversal, extract levels in order
     * to create final result. This approach separates traversal logic from
     * level organization, making it flexible for different traversal patterns.
     * Useful when tree traversal needs to be combined with other operations.
     * 
     * Time Complexity: O(n) - single DFS traversal plus O(h) for map extraction
     * Space Complexity: O(n) - hashmap storage plus O(h) recursion stack
     * 
     * Best when: Need flexible traversal with level grouping, combining operations
     * Worst when: Simple level-order sufficient, avoid hashmap overhead
     */
    std::vector<std::vector<int>> levelOrderHashMap(TreeNode* root);

    /**
     * Approach 5: Iterative DFS with Stack and Level Tracking
     * 
     * Use iterative DFS with explicit stack storing node-level pairs.
     * 
     * Reasoning: Avoid recursion by using explicit stack for DFS traversal.
     * Store pairs of (node, level) on stack. When popping node, add its value
     * to appropriate level in result vector and push children with level+1.
     * This combines benefits of DFS approach with iterative implementation,
     * avoiding recursion stack limitations. Demonstrates how to convert recursive
     * solutions to iterative ones systematically.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - explicit stack depth plus result storage
     * 
     * Best when: Avoid recursion, need iterative DFS, very deep trees
     * Worst when: Standard BFS more natural, recursion not a concern
     */
    std::vector<std::vector<int>> levelOrderIterativeDFS(TreeNode* root);

    /**
     * Approach 6: BFS with Level Markers (Null Sentinel)
     * 
     * Use single queue with null markers to separate levels.
     * 
     * Reasoning: Classic variation where null nodes act as level separators.
     * Start by adding root and nullptr to queue. When processing queue, if
     * current node is nullptr, we've finished a level - save current level
     * values and add another nullptr (unless queue is empty). If current node
     * is real, add its value and add children. This creates clean level
     * separation without needing to track queue sizes or use multiple queues.
     * 
     * Time Complexity: O(n) - each real node processed once
     * Space Complexity: O(w + h) - queue space plus null markers
     * 
     * Best when: Clean level separation without size tracking, classic approach
     * Worst when: Prefer explicit size management, avoid null handling complexity
     */
    std::vector<std::vector<int>> levelOrderNullMarkers(TreeNode* root);

private:
    // Helper functions for DFS approach
    void dfsHelper(TreeNode* node, int level, std::vector<std::vector<int>>& result);
    
    // Helper functions for HashMap approach
    void dfsWithMap(TreeNode* node, int level, std::unordered_map<int, std::vector<int>>& levelMap);
    
    // Data structure for iterative DFS
    struct NodeLevel {
        TreeNode* node;
        int level;
        
        NodeLevel(TreeNode* n, int l) : node(n), level(l) {}
    };
};

}
}