#include "binary_tree_level_order_traversal.h"
#include <algorithm>

namespace leetcode {
namespace medium {

// Approach 1: Standard BFS with Queue
std::vector<std::vector<int>> BinaryTreeLevelOrderTraversal::levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (!root) return result;
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        std::vector<int> currentLevel;
        
        // Process all nodes at current level
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = queue.front();
            queue.pop();
            
            currentLevel.push_back(node->val);
            
            // Add children for next level
            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }
        
        result.push_back(currentLevel);
    }
    
    return result;
}

// Approach 2: DFS with Level Parameter
std::vector<std::vector<int>> BinaryTreeLevelOrderTraversal::levelOrderDFS(TreeNode* root) {
    std::vector<std::vector<int>> result;
    dfsHelper(root, 0, result);
    return result;
}

void BinaryTreeLevelOrderTraversal::dfsHelper(TreeNode* node, int level, std::vector<std::vector<int>>& result) {
    if (!node) return;
    
    // Ensure result has vector for current level
    if (level >= result.size()) {
        result.push_back(std::vector<int>());
    }
    
    // Add current node to its level
    result[level].push_back(node->val);
    
    // Recurse on children with incremented level
    dfsHelper(node->left, level + 1, result);
    dfsHelper(node->right, level + 1, result);
}

// Approach 3: Two-Queue Approach
std::vector<std::vector<int>> BinaryTreeLevelOrderTraversal::levelOrderTwoQueues(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (!root) return result;
    
    std::queue<TreeNode*> currentLevel;
    std::queue<TreeNode*> nextLevel;
    
    currentLevel.push(root);
    
    while (!currentLevel.empty()) {
        std::vector<int> levelValues;
        
        // Process entire current level
        while (!currentLevel.empty()) {
            TreeNode* node = currentLevel.front();
            currentLevel.pop();
            
            levelValues.push_back(node->val);
            
            // Add children to next level queue
            if (node->left) nextLevel.push(node->left);
            if (node->right) nextLevel.push(node->right);
        }
        
        result.push_back(levelValues);
        
        // Swap queues for next iteration
        std::swap(currentLevel, nextLevel);
    }
    
    return result;
}

// Approach 4: Level-by-Level with HashMap
std::vector<std::vector<int>> BinaryTreeLevelOrderTraversal::levelOrderHashMap(TreeNode* root) {
    std::unordered_map<int, std::vector<int>> levelMap;
    dfsWithMap(root, 0, levelMap);
    
    std::vector<std::vector<int>> result;
    
    // Extract levels in order
    for (int level = 0; level < levelMap.size(); ++level) {
        if (levelMap.find(level) != levelMap.end()) {
            result.push_back(levelMap[level]);
        }
    }
    
    return result;
}

void BinaryTreeLevelOrderTraversal::dfsWithMap(TreeNode* node, int level, 
                                               std::unordered_map<int, std::vector<int>>& levelMap) {
    if (!node) return;
    
    levelMap[level].push_back(node->val);
    
    dfsWithMap(node->left, level + 1, levelMap);
    dfsWithMap(node->right, level + 1, levelMap);
}

// Approach 5: Iterative DFS with Stack and Level Tracking
std::vector<std::vector<int>> BinaryTreeLevelOrderTraversal::levelOrderIterativeDFS(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (!root) return result;
    
    std::stack<NodeLevel> stack;
    stack.push(NodeLevel(root, 0));
    
    while (!stack.empty()) {
        NodeLevel current = stack.top();
        stack.pop();
        
        TreeNode* node = current.node;
        int level = current.level;
        
        // Ensure result has vector for current level
        if (level >= result.size()) {
            result.resize(level + 1);
        }
        
        result[level].push_back(node->val);
        
        // Push children (right first for left-to-right order)
        if (node->right) stack.push(NodeLevel(node->right, level + 1));
        if (node->left) stack.push(NodeLevel(node->left, level + 1));
    }
    
    return result;
}

// Approach 6: BFS with Level Markers (Null Sentinel)
std::vector<std::vector<int>> BinaryTreeLevelOrderTraversal::levelOrderNullMarkers(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if (!root) return result;
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    queue.push(nullptr); // Level marker
    
    std::vector<int> currentLevel;
    
    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.pop();
        
        if (node == nullptr) {
            // End of current level
            result.push_back(currentLevel);
            currentLevel.clear();
            
            // Add marker for next level if there are more nodes
            if (!queue.empty()) {
                queue.push(nullptr);
            }
        } else {
            // Process current node
            currentLevel.push_back(node->val);
            
            // Add children
            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }
    }
    
    return result;
}

}
}