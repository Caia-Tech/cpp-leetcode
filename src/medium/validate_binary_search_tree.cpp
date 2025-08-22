#include "validate_binary_search_tree.h"
#include <queue>
#include <climits>

using namespace leetcode::utils;

namespace leetcode {
namespace medium {

bool ValidateBinarySearchTree::isValidBST(TreeNode* root) {
    if (!root) return true;
    
    std::vector<int> values;
    inorderTraversal(root, values);
    
    // Check if inorder traversal produces strictly increasing sequence
    for (int i = 1; i < values.size(); ++i) {
        if (values[i] <= values[i-1]) {
            return false;
        }
    }
    
    return true;
}

void ValidateBinarySearchTree::inorderTraversal(TreeNode* node, std::vector<int>& values) {
    if (!node) return;
    
    inorderTraversal(node->left, values);
    values.push_back(node->val);
    inorderTraversal(node->right, values);
}

bool ValidateBinarySearchTree::isValidBSTInorderOptimized(TreeNode* root) {
    if (!root) return true;
    
    TreeNode* prev = nullptr;
    return inorderWithPrev(root, prev);
}

bool ValidateBinarySearchTree::inorderWithPrev(TreeNode* node, TreeNode*& prev) {
    if (!node) return true;
    
    // Traverse left subtree
    if (!inorderWithPrev(node->left, prev)) {
        return false;
    }
    
    // Check current node against previous
    if (prev && node->val <= prev->val) {
        return false;
    }
    prev = node;
    
    // Traverse right subtree
    return inorderWithPrev(node->right, prev);
}

bool ValidateBinarySearchTree::isValidBSTBounds(TreeNode* root) {
    return validateWithBounds(root, LLONG_MIN, LLONG_MAX);
}

bool ValidateBinarySearchTree::validateWithBounds(TreeNode* node, long long minVal, long long maxVal) {
    if (!node) return true;
    
    // Check if current node violates bounds
    if (node->val <= minVal || node->val >= maxVal) {
        return false;
    }
    
    // Recursively validate subtrees with tightened bounds
    return validateWithBounds(node->left, minVal, node->val) &&
           validateWithBounds(node->right, node->val, maxVal);
}

bool ValidateBinarySearchTree::isValidBSTIterative(TreeNode* root) {
    if (!root) return true;
    
    std::stack<TreeNode*> stack;
    TreeNode* current = root;
    TreeNode* prev = nullptr;
    
    while (current || !stack.empty()) {
        // Go to leftmost node
        while (current) {
            stack.push(current);
            current = current->left;
        }
        
        // Process current node
        current = stack.top();
        stack.pop();
        
        // Check BST property
        if (prev && current->val <= prev->val) {
            return false;
        }
        prev = current;
        
        // Move to right subtree
        current = current->right;
    }
    
    return true;
}

bool ValidateBinarySearchTree::isValidBSTMorris(TreeNode* root) {
    if (!root) return true;
    
    TreeNode* current = root;
    TreeNode* prev = nullptr;
    
    while (current) {
        if (!current->left) {
            // Process current node
            if (prev && current->val <= prev->val) {
                return false;
            }
            prev = current;
            current = current->right;
        } else {
            // Find inorder predecessor
            TreeNode* predecessor = getInorderPredecessor(current);
            
            if (!predecessor->right) {
                // Create thread
                predecessor->right = current;
                current = current->left;
            } else {
                // Remove thread and process current node
                predecessor->right = nullptr;
                
                if (prev && current->val <= prev->val) {
                    return false;
                }
                prev = current;
                current = current->right;
            }
        }
    }
    
    return true;
}

TreeNode* ValidateBinarySearchTree::getInorderPredecessor(TreeNode* node) {
    TreeNode* predecessor = node->left;
    while (predecessor->right && predecessor->right != node) {
        predecessor = predecessor->right;
    }
    return predecessor;
}

bool ValidateBinarySearchTree::isValidBSTLevelOrder(TreeNode* root) {
    if (!root) return true;
    
    std::queue<NodeWithRange> queue;
    queue.push(NodeWithRange(root, LLONG_MIN, LLONG_MAX));
    
    while (!queue.empty()) {
        NodeWithRange current = queue.front();
        queue.pop();
        
        TreeNode* node = current.node;
        long long minVal = current.minVal;
        long long maxVal = current.maxVal;
        
        // Check if current node violates bounds
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        // Add children to queue with updated bounds
        if (node->left) {
            queue.push(NodeWithRange(node->left, minVal, node->val));
        }
        if (node->right) {
            queue.push(NodeWithRange(node->right, node->val, maxVal));
        }
    }
    
    return true;
}

}
}