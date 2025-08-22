#include "binary_tree_inorder_traversal.h"
#include <algorithm>
#include <unordered_map>

namespace leetcode {
namespace easy {

std::vector<int> BinaryTreeInorderTraversal::inorderTraversalRecursive(TreeNode* root) {
    std::vector<int> result;
    inorderHelper(root, result);
    return result;
}

std::vector<int> BinaryTreeInorderTraversal::inorderTraversalIterative(TreeNode* root) {
    std::vector<int> result;
    std::stack<TreeNode*> stack;
    TreeNode* current = root;
    
    while (current != nullptr || !stack.empty()) {
        // Go to the leftmost node of current
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        
        // Current must be nullptr at this point
        current = stack.top();
        stack.pop();
        
        // Visit the node
        result.push_back(current->val);
        
        // Move to right subtree
        current = current->right;
    }
    
    return result;
}

std::vector<int> BinaryTreeInorderTraversal::inorderTraversalMorris(TreeNode* root) {
    std::vector<int> result;
    TreeNode* current = root;
    
    while (current != nullptr) {
        if (current->left == nullptr) {
            // No left subtree, visit current and go right
            result.push_back(current->val);
            current = current->right;
        } else {
            // Find inorder predecessor
            TreeNode* predecessor = current->left;
            
            // Find rightmost node in left subtree or thread back to current
            while (predecessor->right != nullptr && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            
            if (predecessor->right == nullptr) {
                // Make current as right child of predecessor (create thread)
                predecessor->right = current;
                current = current->left;
            } else {
                // Thread already exists, remove it and process current
                predecessor->right = nullptr;
                result.push_back(current->val);
                current = current->right;
            }
        }
    }
    
    return result;
}

std::vector<int> BinaryTreeInorderTraversal::inorderTraversalStateMachine(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) return result;
    
    std::stack<NodeState> stack;
    stack.push(NodeState(root, TraversalState::PROCESSING_LEFT));
    
    while (!stack.empty()) {
        NodeState current = stack.top();
        stack.pop();
        
        switch (current.state) {
            case TraversalState::PROCESSING_LEFT:
                // Add right processing, node visiting, and left processing (in reverse order)
                stack.push(NodeState(current.node, TraversalState::PROCESSING_RIGHT));
                stack.push(NodeState(current.node, TraversalState::VISITING_NODE));
                
                if (current.node->left != nullptr) {
                    stack.push(NodeState(current.node->left, TraversalState::PROCESSING_LEFT));
                }
                break;
                
            case TraversalState::VISITING_NODE:
                result.push_back(current.node->val);
                break;
                
            case TraversalState::PROCESSING_RIGHT:
                if (current.node->right != nullptr) {
                    stack.push(NodeState(current.node->right, TraversalState::PROCESSING_LEFT));
                }
                break;
        }
    }
    
    return result;
}

std::vector<int> BinaryTreeInorderTraversal::inorderTraversalReverse(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) return result;
    
    std::stack<TreeNode*> stack;
    std::vector<int> temp;
    
    // Modified postorder-like traversal
    stack.push(root);
    
    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();
        
        temp.push_back(node->val);
        
        // Push left first, then right (opposite of preorder)
        if (node->left) stack.push(node->left);
        if (node->right) stack.push(node->right);
    }
    
    // This gives us a modified traversal that needs to be processed
    // to get inorder. For this implementation, we'll use a different approach:
    
    // Actually, let's implement using two stacks for correct inorder
    result.clear();
    temp.clear();
    
    std::stack<TreeNode*> stack1;
    TreeNode* current = root;
    
    // Go to leftmost
    while (current != nullptr) {
        stack1.push(current);
        current = current->left;
    }
    
    while (!stack1.empty()) {
        current = stack1.top();
        stack1.pop();
        
        result.push_back(current->val);
        
        // Process right subtree
        current = current->right;
        while (current != nullptr) {
            stack1.push(current);
            current = current->left;
        }
    }
    
    return result;
}

std::vector<int> BinaryTreeInorderTraversal::inorderTraversalParentTracking(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) return result;
    
    std::stack<NodeWithParent> stack;
    std::unordered_map<TreeNode*, TreeNode*> parentMap;
    
    // Build parent map and start traversal
    stack.push(NodeWithParent(root, nullptr, true));
    
    while (!stack.empty()) {
        NodeWithParent current = stack.top();
        stack.pop();
        
        if (current.node == nullptr) continue;
        
        // If we haven't processed left subtree yet
        if (current.fromLeft && current.node->left != nullptr) {
            // Push current node back for later processing
            stack.push(NodeWithParent(current.node, current.parent, false));
            // Process left subtree
            stack.push(NodeWithParent(current.node->left, current.node, true));
        } else {
            // Process current node
            result.push_back(current.node->val);
            
            // Process right subtree if exists
            if (current.node->right != nullptr) {
                stack.push(NodeWithParent(current.node->right, current.node, true));
            }
        }
    }
    
    return result;
}

// Helper function implementation
void BinaryTreeInorderTraversal::inorderHelper(TreeNode* root, std::vector<int>& result) {
    if (root == nullptr) {
        return;
    }
    
    // Traverse left subtree
    inorderHelper(root->left, result);
    
    // Visit root
    result.push_back(root->val);
    
    // Traverse right subtree
    inorderHelper(root->right, result);
}

}
}