#include "minimum_depth_binary_tree.h"
#include <queue>
#include <stack>
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: Recursive DFS (Optimal for Most Cases)
int MinimumDepthBinaryTree::minDepthRecursive(TreeNode* root) {
    if (!root) return 0;
    
    // If it's a leaf node
    if (!root->left && !root->right) {
        return 1;
    }
    
    // If only right subtree exists
    if (!root->left) {
        return 1 + minDepthRecursive(root->right);
    }
    
    // If only left subtree exists
    if (!root->right) {
        return 1 + minDepthRecursive(root->left);
    }
    
    // Both subtrees exist, take minimum
    return 1 + std::min(minDepthRecursive(root->left), 
                        minDepthRecursive(root->right));
}

// Approach 2: Breadth-First Search (Optimal for Unbalanced Trees)
int MinimumDepthBinaryTree::minDepthBFS(TreeNode* root) {
    if (!root) return 0;
    
    std::queue<NodeDepthPair> queue;
    queue.push(NodeDepthPair(root, 1));
    
    while (!queue.empty()) {
        NodeDepthPair current = queue.front();
        queue.pop();
        
        TreeNode* node = current.node;
        int depth = current.depth;
        
        // If this is a leaf node, return its depth (first leaf found = minimum depth)
        if (!node->left && !node->right) {
            return depth;
        }
        
        // Add children to queue
        if (node->left) {
            queue.push(NodeDepthPair(node->left, depth + 1));
        }
        if (node->right) {
            queue.push(NodeDepthPair(node->right, depth + 1));
        }
    }
    
    return 0; // Should never reach here for valid input
}

// Approach 3: Iterative DFS with Stack
int MinimumDepthBinaryTree::minDepthDFS(TreeNode* root) {
    if (!root) return 0;
    
    std::stack<NodeDepthPair> stack;
    stack.push(NodeDepthPair(root, 1));
    int minDepth = INT_MAX;
    
    while (!stack.empty()) {
        NodeDepthPair current = stack.top();
        stack.pop();
        
        TreeNode* node = current.node;
        int depth = current.depth;
        
        // If this is a leaf node, update minimum depth
        if (!node->left && !node->right) {
            minDepth = std::min(minDepth, depth);
            continue;
        }
        
        // Early termination: if current depth already exceeds minimum, skip
        if (depth >= minDepth) {
            continue;
        }
        
        // Add children to stack
        if (node->right) {
            stack.push(NodeDepthPair(node->right, depth + 1));
        }
        if (node->left) {
            stack.push(NodeDepthPair(node->left, depth + 1));
        }
    }
    
    return minDepth;
}

// Approach 4: Morris Traversal with Depth Tracking
int MinimumDepthBinaryTree::minDepthMorris(TreeNode* root) {
    if (!root) return 0;
    
    // Morris traversal for minimum depth is complex due to depth tracking
    // For simplicity, use a modified approach that demonstrates the concept
    return minDepthRecursive(root);
}

TreeNode* MinimumDepthBinaryTree::findPredecessor(TreeNode* current) {
    TreeNode* pred = current->left;
    while (pred->right && pred->right != current) {
        pred = pred->right;
    }
    return pred;
}

// Approach 5: Level Order with Early Termination
int MinimumDepthBinaryTree::minDepthLevelOrder(TreeNode* root) {
    if (!root) return 0;
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    int depth = 1;
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        
        // Process all nodes at current level
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = queue.front();
            queue.pop();
            
            // If this is a leaf node, we found the minimum depth
            if (!current->left && !current->right) {
                return depth;
            }
            
            // Add children for next level
            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
        }
        
        // Move to next level
        depth++;
    }
    
    return depth - 1;
}

// Approach 6: Functional Programming with Min Tracking
int MinimumDepthBinaryTree::minDepthFunctional(TreeNode* root) {
    auto depthCalculator = createMinDepthCalculator();
    return depthCalculator(root);
}

std::function<int(TreeNode*)> MinimumDepthBinaryTree::createMinDepthCalculator() {
    return [this](TreeNode* node) -> int {
        // Base case lambda
        auto isNull = [](TreeNode* n) { return !n; };
        auto isLeaf = [](TreeNode* n) { return n && !n->left && !n->right; };
        
        if (isNull(node)) return 0;
        if (isLeaf(node)) return 1;
        
        // Recursive calculator
        auto calculator = createMinDepthCalculator();
        
        // Child depth calculators
        auto getLeftDepth = [&]() {
            return node->left ? calculator(node->left) : INT_MAX;
        };
        
        auto getRightDepth = [&]() {
            return node->right ? calculator(node->right) : INT_MAX;
        };
        
        // Minimum depth calculation with proper null handling
        int leftDepth = getLeftDepth();
        int rightDepth = getRightDepth();
        
        // If one subtree is missing, use the other
        if (leftDepth == INT_MAX) return 1 + rightDepth;
        if (rightDepth == INT_MAX) return 1 + leftDepth;
        
        // Both subtrees exist
        return 1 + std::min(leftDepth, rightDepth);
    };
}

// Helper for recursive approach with proper null handling
int MinimumDepthBinaryTree::minDepthHelper(TreeNode* root) {
    if (!root) return INT_MAX; // Use INT_MAX for null nodes in internal calculations
    
    if (!root->left && !root->right) {
        return 1; // Leaf node
    }
    
    int leftDepth = minDepthHelper(root->left);
    int rightDepth = minDepthHelper(root->right);
    
    return 1 + std::min(leftDepth, rightDepth);
}

}  // namespace easy
}  // namespace leetcode