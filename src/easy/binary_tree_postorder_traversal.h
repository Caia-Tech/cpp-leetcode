#pragma once

#ifndef LEETCODE_EASY_BINARY_TREE_POSTORDER_TRAVERSAL_H
#define LEETCODE_EASY_BINARY_TREE_POSTORDER_TRAVERSAL_H

#include <vector>
#include <stack>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

// Problem 145: Binary Tree Postorder Traversal
// Given the root of a binary tree, return the postorder traversal of its nodes' values.
// Postorder traversal visits nodes in the order: Left -> Right -> Root
//
// Example 1:
// Input: root = [1,null,2,3]
// Output: [3,2,1]
//
// Example 2:
// Input: root = []
// Output: []
//
// Example 3:
// Input: root = [1]
// Output: [1]
//
// Constraints:
// - The number of nodes in the tree is in the range [0, 100].
// - -100 <= Node.val <= 100
//
// This class implements 6 different algorithmic approaches:
// 1. Recursive DFS: Classic recursive depth-first search
// 2. Iterative Two Stacks: Use two stacks to simulate recursion
// 3. Iterative Single Stack: Use one stack with visited tracking
// 4. Morris Traversal: O(1) space using threaded binary tree technique
// 5. Reverse Preorder: Generate reverse preorder and reverse the result
// 6. Iterative with State: Track node processing state explicitly

class BinaryTreePostorderTraversal {
public:
    // Approach 1: Recursive DFS (Classic)
    // Time: O(n), Space: O(h) where h is tree height
    // Most intuitive approach following the definition of postorder traversal
    static std::vector<int> postorderTraversalRecursive(utils::TreeNode* root);
    
    // Approach 2: Iterative Two Stacks
    // Time: O(n), Space: O(h)
    // Use two stacks: one for traversal, another for result ordering
    static std::vector<int> postorderTraversalTwoStacks(utils::TreeNode* root);
    
    // Approach 3: Iterative Single Stack with Visited Tracking
    // Time: O(n), Space: O(h)
    // Use single stack with mechanism to track visited nodes
    static std::vector<int> postorderTraversalSingleStack(utils::TreeNode* root);
    
    // Approach 4: Morris Traversal (Threaded Binary Tree)
    // Time: O(n), Space: O(1)
    // Modify tree structure temporarily to achieve constant space
    static std::vector<int> postorderTraversalMorris(utils::TreeNode* root);
    
    // Approach 5: Reverse Preorder
    // Time: O(n), Space: O(h)
    // Generate modified preorder (root-right-left) and reverse the result
    static std::vector<int> postorderTraversalReversePreorder(utils::TreeNode* root);
    
    // Approach 6: Iterative with State Tracking
    // Time: O(n), Space: O(h)
    // Explicitly track the processing state of each node
    static std::vector<int> postorderTraversalWithState(utils::TreeNode* root);

private:
    // Helper functions for different approaches
    static void postorderHelper(utils::TreeNode* node, std::vector<int>& result);
    
    // Helper for Morris traversal
    static void reverseAddRange(std::vector<int>& result, utils::TreeNode* from, utils::TreeNode* to);
    
    // State enumeration for state-based approach
    enum NodeState { UNVISITED, LEFT_VISITED, RIGHT_VISITED };
    
    struct NodeWithState {
        utils::TreeNode* node;
        NodeState state;
        
        NodeWithState(utils::TreeNode* n, NodeState s) : node(n), state(s) {}
    };
};

} // namespace easy
} // namespace leetcode

#endif // LEETCODE_EASY_BINARY_TREE_POSTORDER_TRAVERSAL_H