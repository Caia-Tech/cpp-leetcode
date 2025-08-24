#include "balanced_binary_tree.h"
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace leetcode {
namespace easy {

// Approach 1: Top-Down Recursive (Naive)
bool BalancedBinaryTree::isBalancedTopDown(TreeNode* root) {
    if (!root) return true;
    
    // Calculate heights of left and right subtrees
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    
    // Check if current node is balanced
    if (std::abs(leftHeight - rightHeight) > 1) {
        return false;
    }
    
    // Recursively check if subtrees are balanced
    return isBalancedTopDown(root->left) && isBalancedTopDown(root->right);
}

int BalancedBinaryTree::calculateHeight(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(calculateHeight(root->left), calculateHeight(root->right));
}

// Approach 2: Bottom-Up Recursive (Optimal)
bool BalancedBinaryTree::isBalancedBottomUp(TreeNode* root) {
    return calculateHeightAndCheckBalance(root) != UNBALANCED;
}

int BalancedBinaryTree::calculateHeightAndCheckBalance(TreeNode* root) {
    if (!root) return 0;
    
    // Calculate height of left subtree
    int leftHeight = calculateHeightAndCheckBalance(root->left);
    if (leftHeight == UNBALANCED) return UNBALANCED;
    
    // Calculate height of right subtree
    int rightHeight = calculateHeightAndCheckBalance(root->right);
    if (rightHeight == UNBALANCED) return UNBALANCED;
    
    // Check if current node is balanced
    if (std::abs(leftHeight - rightHeight) > 1) {
        return UNBALANCED;
    }
    
    // Return height of current subtree
    return 1 + std::max(leftHeight, rightHeight);
}

// Approach 3: Iterative BFS with Height Caching
bool BalancedBinaryTree::isBalancedBFS(TreeNode* root) {
    if (!root) return true;
    
    std::unordered_map<TreeNode*, int> heightCache;
    std::queue<TreeNode*> queue;
    
    // Process tree level by level
    queue.push(root);
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = queue.front();
            queue.pop();
            
            // Calculate heights of children
            int leftHeight = getHeight(current->left, heightCache);
            int rightHeight = getHeight(current->right, heightCache);
            
            // Check balance condition
            if (std::abs(leftHeight - rightHeight) > 1) {
                return false;
            }
            
            // Cache height of current node
            heightCache[current] = 1 + std::max(leftHeight, rightHeight);
            
            // Add children to queue
            if (current->left) queue.push(current->left);
            if (current->right) queue.push(current->right);
        }
    }
    
    return true;
}

int BalancedBinaryTree::getHeight(TreeNode* node, std::unordered_map<TreeNode*, int>& heightCache) {
    if (!node) return 0;
    
    auto it = heightCache.find(node);
    if (it != heightCache.end()) {
        return it->second;
    }
    
    // Calculate and cache height
    int height = 1 + std::max(getHeight(node->left, heightCache), 
                              getHeight(node->right, heightCache));
    heightCache[node] = height;
    return height;
}

// Approach 4: Iterative DFS with Stack
bool BalancedBinaryTree::isBalancedDFS(TreeNode* root) {
    if (!root) return true;
    
    std::stack<NodeState> stack;
    std::unordered_map<TreeNode*, int> heights;
    
    stack.push(NodeState(root));
    
    while (!stack.empty()) {
        NodeState& current = stack.top();
        
        if (current.processed) {
            // Post-order processing: children have been processed
            int leftHeight = current.node->left ? heights[current.node->left] : 0;
            int rightHeight = current.node->right ? heights[current.node->right] : 0;
            
            // Check balance condition
            if (std::abs(leftHeight - rightHeight) > 1) {
                return false;
            }
            
            // Store height of current node
            heights[current.node] = 1 + std::max(leftHeight, rightHeight);
            stack.pop();
        } else {
            // Pre-order processing: push children first
            current.processed = true;
            
            if (current.node->right) {
                stack.push(NodeState(current.node->right));
            }
            if (current.node->left) {
                stack.push(NodeState(current.node->left));
            }
        }
    }
    
    return true;
}

// Approach 5: Morris Traversal with Height Tracking
bool BalancedBinaryTree::isBalancedMorris(TreeNode* root) {
    if (!root) return true;
    
    // Morris traversal is complex for this problem because we need height information
    // This is a simplified approach that demonstrates the concept
    // In practice, the bottom-up recursive approach is preferred
    
    std::unordered_map<TreeNode*, int> heights;
    TreeNode* current = root;
    
    while (current) {
        if (!current->left) {
            // Process current node
            int leftHeight = 0;
            int rightHeight = current->right ? heights[current->right] : 0;
            
            heights[current] = 1 + std::max(leftHeight, rightHeight);
            current = current->right;
        } else {
            TreeNode* predecessor = findPredecessor(current);
            
            if (!predecessor->right) {
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                
                // Process current node
                int leftHeight = heights[current->left];
                int rightHeight = current->right ? heights[current->right] : 0;
                
                if (std::abs(leftHeight - rightHeight) > 1) {
                    return false;
                }
                
                heights[current] = 1 + std::max(leftHeight, rightHeight);
                current = current->right;
            }
        }
    }
    
    return true;
}

TreeNode* BalancedBinaryTree::findPredecessor(TreeNode* current) {
    TreeNode* pred = current->left;
    while (pred->right && pred->right != current) {
        pred = pred->right;
    }
    return pred;
}

// Approach 6: Parallel Height Calculation
bool BalancedBinaryTree::isBalancedParallel(TreeNode* root) {
    auto result = calculateHeightAndBalance(root);
    return result.second; // second element is balance flag
}

std::pair<int, bool> BalancedBinaryTree::calculateHeightAndBalance(TreeNode* root) {
    if (!root) return {0, true};
    
    // Calculate left subtree height and balance
    auto leftResult = calculateHeightAndBalance(root->left);
    if (!leftResult.second) return {0, false}; // Left subtree unbalanced
    
    // Calculate right subtree height and balance
    auto rightResult = calculateHeightAndBalance(root->right);
    if (!rightResult.second) return {0, false}; // Right subtree unbalanced
    
    // Check current node balance
    int heightDiff = std::abs(leftResult.first - rightResult.first);
    if (heightDiff > 1) return {0, false};
    
    // Return height and balance status
    int currentHeight = 1 + std::max(leftResult.first, rightResult.first);
    return {currentHeight, true};
}

}  // namespace easy
}  // namespace leetcode