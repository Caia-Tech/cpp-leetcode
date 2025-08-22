#pragma once

#include <vector>
#include <stack>
#include <memory>

namespace leetcode {
namespace easy {

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Problem 94: Binary Tree Inorder Traversal
 * 
 * Given the root of a binary tree, return the inorder traversal of its nodes' values.
 * 
 * Inorder traversal visits nodes in the order: Left subtree, Root, Right subtree.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 100].
 * - -100 <= Node.val <= 100
 * 
 * Follow-up: Recursive solution is trivial, could you do it iteratively?
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class BinaryTreeInorderTraversal {
public:
    /**
     * Approach 1: Recursive Inorder (Classic)
     * 
     * Use recursion to naturally follow the inorder traversal pattern.
     * 
     * Reasoning: This is the most intuitive and standard approach for tree traversal.
     * Recursively traverse left subtree, visit current node, then traverse right
     * subtree. The recursive call stack naturally handles the traversal order.
     * This approach directly mirrors the definition of inorder traversal and is
     * the easiest to understand and implement correctly.
     * 
     * Time Complexity: O(n) - visit each node exactly once
     * Space Complexity: O(h) - recursion depth equals tree height, O(n) worst case
     * 
     * Best when: Natural recursive thinking, clear and concise code needed
     * Worst when: Deep trees risk stack overflow, iterative solution required
     */
    std::vector<int> inorderTraversalRecursive(TreeNode* root);

    /**
     * Approach 2: Iterative with Explicit Stack (Standard Iterative)
     * 
     * Use explicit stack to simulate recursive call behavior.
     * 
     * Reasoning: Convert the recursive approach to iterative using explicit stack.
     * The key insight is to go as far left as possible, pushing nodes onto stack,
     * then process the leftmost unprocessed node, and move to its right subtree.
     * This approach eliminates recursion depth limitations and gives explicit
     * control over the traversal process.
     * 
     * Time Complexity: O(n) - each node pushed and popped once
     * Space Complexity: O(h) - stack size equals maximum path length
     * 
     * Best when: Avoid recursion, need explicit control over traversal
     * Worst when: Code complexity higher than recursive, stack management overhead
     */
    std::vector<int> inorderTraversalIterative(TreeNode* root);

    /**
     * Approach 3: Morris Traversal (Optimal Space)
     * 
     * Achieve O(1) space complexity using threaded binary tree technique.
     * 
     * Reasoning: Morris traversal modifies tree structure temporarily by creating
     * threads (links) to enable constant space traversal. For each node, find its
     * inorder predecessor and create a temporary link back to current node. This
     * allows navigation without stack or recursion. After processing, remove the
     * temporary links to restore original tree structure. This is the optimal
     * solution for space complexity.
     * 
     * Time Complexity: O(n) - each node visited at most 3 times
     * Space Complexity: O(1) - no additional space except result array
     * 
     * Best when: Memory constraints critical, want theoretical optimal space
     * Worst when: Tree modification complexity, temporary structure changes
     */
    std::vector<int> inorderTraversalMorris(TreeNode* root);

    /**
     * Approach 4: State Machine Iterative (Educational)
     * 
     * Use state machine to track traversal progress for each node.
     * 
     * Reasoning: Instead of implicit recursion state, explicitly track what stage
     * each node is in: processing left subtree, visiting node, or processing right
     * subtree. Use a stack of node-state pairs to manage traversal. This approach
     * provides clear insight into the traversal process and can be extended to
     * handle more complex tree algorithms.
     * 
     * Time Complexity: O(n) - each node processed with its states
     * Space Complexity: O(h) - stack stores node-state pairs
     * 
     * Best when: Understanding traversal mechanics, extensible to complex algorithms
     * Worst when: Overkill for simple traversal, additional state complexity
     */
    std::vector<int> inorderTraversalStateMachine(TreeNode* root);

    /**
     * Approach 5: Reverse Postorder Simulation (Creative)
     * 
     * Simulate inorder by modifying preorder/postorder traversal patterns.
     * 
     * Reasoning: Inorder can be seen as reverse of a modified postorder traversal.
     * Use creative stack manipulation to achieve inorder result through different
     * traversal pattern. While not the most intuitive, this approach demonstrates
     * the relationship between different traversal methods and provides algorithmic
     * flexibility for converting between traversal types.
     * 
     * Time Complexity: O(n) - standard traversal with reverse operations
     * Space Complexity: O(h) - stack space plus result reversal
     * 
     * Best when: Understanding traversal relationships, algorithmic creativity
     * Worst when: Unnecessarily complex for straightforward inorder traversal
     */
    std::vector<int> inorderTraversalReverse(TreeNode* root);

    /**
     * Approach 6: Parent Pointer Simulation (Alternative)
     * 
     * Simulate parent pointers to enable upward navigation without stack.
     * 
     * Reasoning: In traditional tree traversal, we need to remember where we came
     * from to backtrack. Simulate parent pointers by maintaining additional
     * information during traversal. This approach explores different ways to
     * handle the backtracking aspect of tree traversal without explicit recursion
     * or large stacks, though it may use additional data structures.
     * 
     * Time Complexity: O(n) - visit each node, additional parent tracking
     * Space Complexity: O(h) - parent information storage
     * 
     * Best when: Exploring parent-based tree algorithms, different navigation perspective
     * Worst when: Added complexity over standard approaches, no significant benefit
     */
    std::vector<int> inorderTraversalParentTracking(TreeNode* root);

private:
    // Helper functions
    void inorderHelper(TreeNode* root, std::vector<int>& result);
    
    // State machine enumeration
    enum class TraversalState {
        PROCESSING_LEFT,
        VISITING_NODE,
        PROCESSING_RIGHT
    };
    
    struct NodeState {
        TreeNode* node;
        TraversalState state;
        
        NodeState(TreeNode* n, TraversalState s) : node(n), state(s) {}
    };
    
    // Parent tracking structure
    struct NodeWithParent {
        TreeNode* node;
        TreeNode* parent;
        bool fromLeft;
        
        NodeWithParent(TreeNode* n, TreeNode* p, bool left) 
            : node(n), parent(p), fromLeft(left) {}
    };
};

}
}