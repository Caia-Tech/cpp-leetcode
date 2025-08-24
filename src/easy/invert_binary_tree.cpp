#include "invert_binary_tree.h"
#include <queue>
#include <stack>
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: Recursive DFS (Optimal)
TreeNode* InvertBinaryTree::invertTreeRecursive(TreeNode* root) {
    // Base case: null node
    if (!root) return root;
    
    // Swap left and right children
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recursively invert subtrees
    invertTreeRecursive(root->left);
    invertTreeRecursive(root->right);
    
    return root;
}

// Approach 2: Iterative BFS (Level Order)
TreeNode* InvertBinaryTree::invertTreeBFS(TreeNode* root) {
    if (!root) return root;
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    while (!queue.empty()) {
        TreeNode* current = queue.front();
        queue.pop();
        
        // Swap left and right children
        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;
        
        // Add children to queue for next level processing
        if (current->left) queue.push(current->left);
        if (current->right) queue.push(current->right);
    }
    
    return root;
}

// Approach 3: Iterative DFS with Stack
TreeNode* InvertBinaryTree::invertTreeDFS(TreeNode* root) {
    if (!root) return root;
    
    std::stack<TreeNode*> stack;
    stack.push(root);
    
    while (!stack.empty()) {
        TreeNode* current = stack.top();
        stack.pop();
        
        // Swap left and right children
        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;
        
        // Push children onto stack
        if (current->left) stack.push(current->left);
        if (current->right) stack.push(current->right);
    }
    
    return root;
}

// Approach 4: Morris Traversal (Space Optimized)
TreeNode* InvertBinaryTree::invertTreeMorris(TreeNode* root) {
    if (!root) return root;
    
    TreeNode* current = root;
    
    while (current) {
        if (!current->left) {
            // Swap children for current node
            TreeNode* temp = current->left;
            current->left = current->right;
            current->right = temp;
            
            // Move to right child (which was originally left)
            current = current->left;
        } else {
            // Find inorder predecessor
            TreeNode* predecessor = findPredecessor(current);
            
            if (!predecessor->right) {
                // Create thread
                predecessor->right = current;
                current = current->left;
            } else {
                // Remove thread and process current node
                predecessor->right = nullptr;
                
                // Swap children for current node
                TreeNode* temp = current->left;
                current->left = current->right;
                current->right = temp;
                
                current = current->left; // which was originally right
            }
        }
    }
    
    return root;
}

TreeNode* InvertBinaryTree::findPredecessor(TreeNode* node) {
    TreeNode* pred = node->left;
    while (pred->right && pred->right != node) {
        pred = pred->right;
    }
    return pred;
}

// Approach 5: Post-order Recursive
TreeNode* InvertBinaryTree::invertTreePostOrder(TreeNode* root) {
    if (!root) return root;
    
    // First recursively invert subtrees
    invertTreePostOrder(root->left);
    invertTreePostOrder(root->right);
    
    // Then swap children of current node
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    return root;
}

// Approach 6: Functional Programming Style
TreeNode* InvertBinaryTree::invertTreeFunctional(TreeNode* root) {
    auto inverter = createInverter();
    return inverter(root);
}

std::function<TreeNode*(TreeNode*)> InvertBinaryTree::createInverter() {
    return [this](TreeNode* node) -> TreeNode* {
        if (!node) return nullptr;
        
        // Create swap operation
        auto swapChildren = [](TreeNode* n) {
            if (n) {
                std::swap(n->left, n->right);
            }
        };
        
        // Apply swap to current node
        swapChildren(node);
        
        // Create recursive inverter
        auto inverter = createInverter();
        
        // Apply to children
        if (node->left) inverter(node->left);
        if (node->right) inverter(node->right);
        
        return node;
    };
}

void InvertBinaryTree::applyToTree(TreeNode* root, std::function<void(TreeNode*)> fn) {
    if (!root) return;
    
    fn(root);
    applyToTree(root->left, fn);
    applyToTree(root->right, fn);
}

}  // namespace easy
}  // namespace leetcode