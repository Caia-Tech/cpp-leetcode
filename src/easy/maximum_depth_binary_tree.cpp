#include "maximum_depth_binary_tree.h"
#include <queue>
#include <stack>
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: Recursive DFS (Optimal)
int MaximumDepthBinaryTree::maxDepthRecursive(TreeNode* root) {
    // Base case: empty tree has depth 0
    if (!root) {
        return 0;
    }
    
    // Recursively find depth of left and right subtrees
    int leftDepth = maxDepthRecursive(root->left);
    int rightDepth = maxDepthRecursive(root->right);
    
    // Depth is 1 (current node) + max depth of subtrees
    return 1 + std::max(leftDepth, rightDepth);
}

// Approach 2: Iterative BFS (Level Order)
int MaximumDepthBinaryTree::maxDepthBFS(TreeNode* root) {
    if (!root) {
        return 0;
    }
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    int depth = 0;
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        depth++;
        
        // Process all nodes at current level
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = queue.front();
            queue.pop();
            
            // Add children to queue for next level
            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
        }
    }
    
    return depth;
}

// Approach 3: Iterative DFS with Stack
int MaximumDepthBinaryTree::maxDepthDFS(TreeNode* root) {
    if (!root) {
        return 0;
    }
    
    std::stack<std::pair<TreeNode*, int>> stack;
    stack.push({root, 1});
    int maxDepth = 0;
    
    while (!stack.empty()) {
        auto [node, depth] = stack.top();
        stack.pop();
        
        // Update maximum depth
        maxDepth = std::max(maxDepth, depth);
        
        // Push children with incremented depth
        if (node->left) {
            stack.push({node->left, depth + 1});
        }
        if (node->right) {
            stack.push({node->right, depth + 1});
        }
    }
    
    return maxDepth;
}

// Approach 4: Morris Traversal with Depth Tracking
int MaximumDepthBinaryTree::maxDepthMorris(TreeNode* root) {
    if (!root) {
        return 0;
    }
    
    int maxDepth = 0;
    int currentDepth = 0;
    TreeNode* current = root;
    
    while (current) {
        if (!current->left) {
            // No left child, move to right
            currentDepth++;
            maxDepth = std::max(maxDepth, currentDepth);
            current = current->right;
        } else {
            // Find inorder predecessor
            TreeNode* predecessor = current->left;
            int steps = 1;
            
            while (predecessor->right && predecessor->right != current) {
                predecessor = predecessor->right;
                steps++;
            }
            
            if (!predecessor->right) {
                // First visit, create thread
                predecessor->right = current;
                currentDepth++;
                current = current->left;
            } else {
                // Second visit, remove thread
                predecessor->right = nullptr;
                currentDepth -= steps;
                current = current->right;
            }
        }
    }
    
    return maxDepth;
}

// Approach 5: Two-Stack DFS (Explicit Depth Tracking)
int MaximumDepthBinaryTree::maxDepthTwoStack(TreeNode* root) {
    if (!root) {
        return 0;
    }
    
    std::stack<TreeNode*> nodeStack;
    std::stack<int> depthStack;
    
    nodeStack.push(root);
    depthStack.push(1);
    int maxDepth = 0;
    
    while (!nodeStack.empty()) {
        TreeNode* node = nodeStack.top();
        int depth = depthStack.top();
        nodeStack.pop();
        depthStack.pop();
        
        // Update maximum depth
        maxDepth = std::max(maxDepth, depth);
        
        // Push children with incremented depth
        if (node->left) {
            nodeStack.push(node->left);
            depthStack.push(depth + 1);
        }
        if (node->right) {
            nodeStack.push(node->right);
            depthStack.push(depth + 1);
        }
    }
    
    return maxDepth;
}

// Approach 6: Level-by-Level BFS with Size Tracking
int MaximumDepthBinaryTree::maxDepthLevelBFS(TreeNode* root) {
    if (!root) {
        return 0;
    }
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    int depth = 0;
    
    while (!queue.empty()) {
        int currentLevelSize = queue.size();
        depth++;
        
        // Process entire current level
        for (int i = 0; i < currentLevelSize; ++i) {
            TreeNode* node = queue.front();
            queue.pop();
            
            // Enqueue children for next level
            if (node->left) {
                queue.push(node->left);
            }
            if (node->right) {
                queue.push(node->right);
            }
        }
    }
    
    return depth;
}

}  // namespace easy
}  // namespace leetcode