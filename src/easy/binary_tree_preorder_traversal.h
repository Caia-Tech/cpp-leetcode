#pragma once

#ifndef LEETCODE_EASY_BINARY_TREE_PREORDER_TRAVERSAL_H
#define LEETCODE_EASY_BINARY_TREE_PREORDER_TRAVERSAL_H

#include <vector>
#include <stack>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

// Problem 144: Binary Tree Preorder Traversal
// Given the root of a binary tree, return the preorder traversal of its nodes' values.
// Preorder traversal visits nodes in the order: Root -> Left -> Right
//
// Example 1:
// Input: root = [1,null,2,3]
// Output: [1,2,3]
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
// 2. Iterative with Stack: Use explicit stack to simulate recursion
// 3. Morris Traversal: O(1) space using threaded binary tree technique
// 4. Iterative with Stack (Reverse): Push right first, then left
// 5. Template-based DFS: Generic approach using function templates
// 6. Tail Recursion Optimized: Optimized recursive approach

class BinaryTreePreorderTraversal {
public:
    // Approach 1: Recursive DFS (Classic)
    // Time: O(n), Space: O(h) where h is tree height
    // Most intuitive approach following the definition of preorder traversal
    static std::vector<int> preorderTraversalRecursive(utils::TreeNode* root);
    
    // Approach 2: Iterative with Stack
    // Time: O(n), Space: O(h)
    // Use explicit stack to simulate the call stack of recursion
    static std::vector<int> preorderTraversalIterative(utils::TreeNode* root);
    
    // Approach 3: Morris Traversal (Threaded Binary Tree)
    // Time: O(n), Space: O(1)
    // Modify tree structure temporarily to achieve constant space
    static std::vector<int> preorderTraversalMorris(utils::TreeNode* root);
    
    // Approach 4: Iterative Stack (Reverse Order)
    // Time: O(n), Space: O(h)
    // Push right child first, then left child for correct ordering
    static std::vector<int> preorderTraversalStack(utils::TreeNode* root);
    
    // Approach 5: Template-based DFS
    // Time: O(n), Space: O(h)
    // Generic approach using function templates for flexibility
    static std::vector<int> preorderTraversalTemplate(utils::TreeNode* root);
    
    // Approach 6: Tail Recursion Optimized
    // Time: O(n), Space: O(h)
    // Optimized recursive approach to minimize function call overhead
    static std::vector<int> preorderTraversalOptimized(utils::TreeNode* root);

private:
    // Helper functions for different approaches
    static void preorderHelper(utils::TreeNode* node, std::vector<int>& result);
    static void preorderTailRecursive(utils::TreeNode* node, std::vector<int>& result);
    
    // Template helper for generic DFS
    template<typename Func>
    static void dfsTemplate(utils::TreeNode* node, std::vector<int>& result, Func visit);
};

} // namespace easy
} // namespace leetcode

#endif // LEETCODE_EASY_BINARY_TREE_PREORDER_TRAVERSAL_H