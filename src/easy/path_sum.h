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
 * Problem 112: Path Sum
 * 
 * Given the root of a binary tree and an integer targetSum, return true if the tree 
 * has a root-to-leaf path such that adding up all the values along the path equals targetSum.
 * 
 * A leaf is a node with no children.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 5000]
 * - -1000 <= Node.val <= 1000
 * - -1000 <= targetSum <= 1000
 */
class PathSum {
public:
    /**
     * Approach 1: Recursive DFS (Optimal)
     * 
     * Check path sum by recursively subtracting current node value from target.
     * 
     * Reasoning: This is the most intuitive and efficient approach. At each node,
     * subtract its value from the remaining target sum. When we reach a leaf,
     * check if the remaining sum equals the leaf's value. The recursion naturally
     * handles backtracking as we explore all possible root-to-leaf paths.
     * Base cases: null node returns false, leaf node checks if value equals target.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion stack depth equals tree height
     * 
     * Best when: Always - this is the standard optimal solution
     * Worst when: Never - this approach is preferred in most scenarios
     */
    bool hasPathSumRecursive(TreeNode* root, int targetSum);

    /**
     * Approach 2: Iterative DFS with Stack
     * 
     * Use explicit stack to track nodes and their accumulated sums.
     * 
     * Reasoning: Simulate recursive approach using explicit stack to avoid
     * recursion stack overflow in very deep trees. Store pairs of (node, remaining_sum)
     * to track the path sum as we traverse. When we reach a leaf, check if
     * remaining sum equals leaf value. This approach provides same logic as
     * recursive but with explicit control over stack memory usage.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - stack size proportional to tree height
     * 
     * Best when: Deep trees where recursion stack might overflow
     * Worst when: Shallow trees where recursive solution is cleaner
     */
    bool hasPathSumDFS(TreeNode* root, int targetSum);

    /**
     * Approach 3: Breadth-First Search (BFS)
     * 
     * Use level-order traversal with queue to find path sum.
     * 
     * Reasoning: Process tree level by level, maintaining accumulated sums
     * at each level. Use queue to store (node, accumulated_sum) pairs.
     * BFS explores all paths systematically and can find shorter paths first
     * if they exist. While not naturally suited for path problems, BFS
     * demonstrates alternative traversal approach and might be preferred
     * when exploring paths by depth priority.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(w) - queue size proportional to maximum tree width
     * 
     * Best when: Want to find paths by depth, tree is very deep vs wide
     * Worst when: Tree is wider than deep, memory usage for queue is high
     */
    bool hasPathSumBFS(TreeNode* root, int targetSum);

    /**
     * Approach 4: Morris Traversal with Path Tracking
     * 
     * Use Morris traversal to achieve O(1) space complexity.
     * 
     * Reasoning: Morris traversal allows tree traversal without recursion
     * or stack by temporarily modifying tree structure. However, tracking
     * path sums during Morris traversal is complex because we need to
     * maintain path state. This approach demonstrates advanced traversal
     * technique but is more complex than practical for this problem.
     * Requires careful handling of path sum calculations during threading.
     * 
     * Time Complexity: O(n) - each edge traversed at most twice
     * Space Complexity: O(1) - only using pointer variables
     * 
     * Best when: Extreme space constraints, demonstrating advanced techniques
     * Worst when: Simplicity preferred, standard solutions adequate
     */
    bool hasPathSumMorris(TreeNode* root, int targetSum);

    /**
     * Approach 5: Two-Pass with Path Collection
     * 
     * First collect all root-to-leaf paths, then check sums.
     * 
     * Reasoning: This educational approach separates path collection from
     * sum verification. First pass collects all root-to-leaf paths using
     * DFS with backtracking. Second pass calculates sum for each path and
     * checks against target. While less efficient than single-pass solutions,
     * this approach clearly demonstrates path collection logic and could be
     * useful when paths themselves are needed for other purposes.
     * 
     * Time Complexity: O(n*h) - visit each node, potentially store h paths
     * Space Complexity: O(n*h) - store all paths explicitly
     * 
     * Best when: Need all paths for additional processing, educational purposes
     * Worst when: Memory constrained, only need yes/no answer
     */
    bool hasPathSumTwoPass(TreeNode* root, int targetSum);

    /**
     * Approach 6: Functional Programming with Lambda
     * 
     * Use functional programming paradigms with lambda expressions.
     * 
     * Reasoning: Demonstrate functional programming approach by creating
     * composable functions for path sum checking. Use lambda expressions
     * to create reusable path checkers and sum calculators. This approach
     * shows how tree problems can be solved using functional programming
     * concepts, though it may have overhead from function calls and closures.
     * Educational value in showing different programming paradigms.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion/function call stack
     * 
     * Best when: Functional programming environment, composability needed
     * Worst when: Performance critical, simple solutions preferred
     */
    bool hasPathSumFunctional(TreeNode* root, int targetSum);

private:
    // Helper for Morris traversal
    TreeNode* findPredecessor(TreeNode* current);
    
    // Helper for two-pass approach
    void collectPaths(TreeNode* root, std::vector<int>& currentPath, 
                     std::vector<std::vector<int>>& allPaths);
    
    // Helper for functional approach
    std::function<bool(TreeNode*, int)> createPathChecker();
    
    // Path state for Morris traversal
    struct PathState {
        TreeNode* node;
        int sum;
        PathState(TreeNode* n, int s) : node(n), sum(s) {}
    };
};

}  // namespace easy
}  // namespace leetcode