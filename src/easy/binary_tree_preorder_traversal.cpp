#include "binary_tree_preorder_traversal.h"
#include <stack>

namespace leetcode {
namespace easy {

// Approach 1: Recursive DFS (Classic)
// Detailed Reasoning: This follows the natural definition of preorder traversal.
// We visit the root first, then recursively traverse left subtree, then right subtree.
// The recursion naturally handles the call stack and maintains the correct order.
std::vector<int> BinaryTreePreorderTraversal::preorderTraversalRecursive(utils::TreeNode* root) {
    std::vector<int> result;
    preorderHelper(root, result);
    return result;
}

// Approach 2: Iterative with Stack
// Detailed Reasoning: We simulate the recursive call stack using an explicit stack.
// We push the current node, process it, then push right child (to be processed later)
// and left child (to be processed immediately). This maintains the preorder sequence.
std::vector<int> BinaryTreePreorderTraversal::preorderTraversalIterative(utils::TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    
    std::stack<utils::TreeNode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        utils::TreeNode* node = stk.top();
        stk.pop();
        
        // Visit current node (preorder: root first)
        result.push_back(node->val);
        
        // Push right child first (to be processed after left)
        if (node->right) {
            stk.push(node->right);
        }
        
        // Push left child (to be processed immediately after current)
        if (node->left) {
            stk.push(node->left);
        }
    }
    
    return result;
}

// Approach 3: Morris Traversal (Threaded Binary Tree)
// Detailed Reasoning: This achieves O(1) space by temporarily modifying the tree structure.
// We create threads (temporary links) from inorder predecessors to current nodes.
// This allows us to traverse without using recursion or an explicit stack.
std::vector<int> BinaryTreePreorderTraversal::preorderTraversalMorris(utils::TreeNode* root) {
    std::vector<int> result;
    utils::TreeNode* current = root;
    
    while (current) {
        if (!current->left) {
            // No left subtree, visit current node and go right
            result.push_back(current->val);
            current = current->right;
        } else {
            // Find the inorder predecessor (rightmost node in left subtree)
            utils::TreeNode* predecessor = current->left;
            while (predecessor->right && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            
            if (!predecessor->right) {
                // Create thread: predecessor -> current
                result.push_back(current->val);  // Visit before going to left subtree
                predecessor->right = current;
                current = current->left;
            } else {
                // Thread already exists, remove it and go right
                predecessor->right = nullptr;
                current = current->right;
            }
        }
    }
    
    return result;
}

// Approach 4: Iterative Stack (Reverse Order)
// Detailed Reasoning: Alternative iterative approach where we push nodes in
// reverse order to maintain preorder sequence. This can be more intuitive
// for some developers as it closely mirrors the recursive approach.
std::vector<int> BinaryTreePreorderTraversal::preorderTraversalStack(utils::TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    
    std::stack<utils::TreeNode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        utils::TreeNode* node = stk.top();
        stk.pop();
        
        if (node) {
            result.push_back(node->val);
            
            // Push in reverse order: right first, then left
            // This ensures left is processed before right
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
        }
    }
    
    return result;
}

// Approach 5: Template-based DFS
// Detailed Reasoning: This approach uses templates to create a generic DFS framework.
// It's more flexible and can be adapted for different traversal types by changing
// the visit function. This demonstrates good software engineering practices.
std::vector<int> BinaryTreePreorderTraversal::preorderTraversalTemplate(utils::TreeNode* root) {
    std::vector<int> result;
    
    // Lambda function for preorder visit pattern
    auto preorderVisit = [&result](utils::TreeNode* node) {
        if (node) {
            result.push_back(node->val);
        }
    };
    
    dfsTemplate(root, result, preorderVisit);
    return result;
}

// Approach 6: Tail Recursion Optimized
// Detailed Reasoning: This optimizes the recursive approach by minimizing
// the recursion depth for right-heavy trees. We handle left traversal recursively
// but iterate through right children to reduce stack usage.
std::vector<int> BinaryTreePreorderTraversal::preorderTraversalOptimized(utils::TreeNode* root) {
    std::vector<int> result;
    preorderTailRecursive(root, result);
    return result;
}

// Helper function for recursive approach
void BinaryTreePreorderTraversal::preorderHelper(utils::TreeNode* node, std::vector<int>& result) {
    if (!node) return;
    
    // Preorder: Root -> Left -> Right
    result.push_back(node->val);           // Visit root
    preorderHelper(node->left, result);   // Traverse left subtree
    preorderHelper(node->right, result);  // Traverse right subtree
}

// Helper function for tail recursion optimized approach
void BinaryTreePreorderTraversal::preorderTailRecursive(utils::TreeNode* node, std::vector<int>& result) {
    while (node) {
        result.push_back(node->val);
        
        if (node->left) {
            if (node->right) {
                // If both children exist, recurse on left and iterate on right
                preorderTailRecursive(node->left, result);
            } else {
                // Only left child exists, continue with left
                node = node->left;
                continue;
            }
        }
        
        // Move to right child (or nullptr)
        node = node->right;
    }
}

// Template helper for generic DFS
template<typename Func>
void BinaryTreePreorderTraversal::dfsTemplate(utils::TreeNode* node, std::vector<int>& result, Func visit) {
    if (!node) return;
    
    visit(node);  // Visit current node
    dfsTemplate(node->left, result, visit);   // Recurse left
    dfsTemplate(node->right, result, visit);  // Recurse right
}

} // namespace easy
} // namespace leetcode