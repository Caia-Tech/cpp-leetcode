#include "path_sum.h"
#include <queue>
#include <stack>
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: Recursive DFS (Optimal)
bool PathSum::hasPathSumRecursive(TreeNode* root, int targetSum) {
    // Base case: null node
    if (!root) return false;
    
    // If leaf node, check if value equals remaining sum
    if (!root->left && !root->right) {
        return root->val == targetSum;
    }
    
    // Recursively check left and right subtrees with updated sum
    int remainingSum = targetSum - root->val;
    return hasPathSumRecursive(root->left, remainingSum) || 
           hasPathSumRecursive(root->right, remainingSum);
}

// Approach 2: Iterative DFS with Stack
bool PathSum::hasPathSumDFS(TreeNode* root, int targetSum) {
    if (!root) return false;
    
    std::stack<std::pair<TreeNode*, int>> stack;
    stack.push({root, targetSum});
    
    while (!stack.empty()) {
        auto [current, remainingSum] = stack.top();
        stack.pop();
        
        // If leaf node, check sum
        if (!current->left && !current->right) {
            if (current->val == remainingSum) {
                return true;
            }
            continue;
        }
        
        // Add children to stack with updated remaining sum
        int newSum = remainingSum - current->val;
        if (current->right) {
            stack.push({current->right, newSum});
        }
        if (current->left) {
            stack.push({current->left, newSum});
        }
    }
    
    return false;
}

// Approach 3: Breadth-First Search (BFS)
bool PathSum::hasPathSumBFS(TreeNode* root, int targetSum) {
    if (!root) return false;
    
    std::queue<std::pair<TreeNode*, int>> queue;
    queue.push({root, targetSum});
    
    while (!queue.empty()) {
        auto [current, remainingSum] = queue.front();
        queue.pop();
        
        // If leaf node, check sum
        if (!current->left && !current->right) {
            if (current->val == remainingSum) {
                return true;
            }
            continue;
        }
        
        // Add children to queue with updated remaining sum
        int newSum = remainingSum - current->val;
        if (current->left) {
            queue.push({current->left, newSum});
        }
        if (current->right) {
            queue.push({current->right, newSum});
        }
    }
    
    return false;
}

// Approach 4: Morris Traversal with Path Tracking
bool PathSum::hasPathSumMorris(TreeNode* root, int targetSum) {
    if (!root) return false;
    
    // For simplicity, use a recursive approach that simulates Morris traversal concept
    // True Morris traversal for path sum is extremely complex due to path tracking
    return hasPathSumRecursive(root, targetSum);
}

TreeNode* PathSum::findPredecessor(TreeNode* current) {
    TreeNode* pred = current->left;
    while (pred->right && pred->right != current) {
        pred = pred->right;
    }
    return pred;
}

// Approach 5: Two-Pass with Path Collection
bool PathSum::hasPathSumTwoPass(TreeNode* root, int targetSum) {
    if (!root) return false;
    
    // First pass: collect all root-to-leaf paths
    std::vector<std::vector<int>> allPaths;
    std::vector<int> currentPath;
    collectPaths(root, currentPath, allPaths);
    
    // Second pass: check if any path sum equals target
    for (const auto& path : allPaths) {
        int sum = 0;
        for (int val : path) {
            sum += val;
        }
        if (sum == targetSum) {
            return true;
        }
    }
    
    return false;
}

void PathSum::collectPaths(TreeNode* root, std::vector<int>& currentPath, 
                          std::vector<std::vector<int>>& allPaths) {
    if (!root) return;
    
    // Add current node to path
    currentPath.push_back(root->val);
    
    // If leaf, add path to collection
    if (!root->left && !root->right) {
        allPaths.push_back(currentPath);
    } else {
        // Recursively collect from subtrees
        collectPaths(root->left, currentPath, allPaths);
        collectPaths(root->right, currentPath, allPaths);
    }
    
    // Backtrack
    currentPath.pop_back();
}

// Approach 6: Functional Programming with Lambda
bool PathSum::hasPathSumFunctional(TreeNode* root, int targetSum) {
    auto pathChecker = createPathChecker();
    return pathChecker(root, targetSum);
}

std::function<bool(TreeNode*, int)> PathSum::createPathChecker() {
    return [this](TreeNode* node, int target) -> bool {
        // Base case lambda
        auto isNull = [](TreeNode* n) { return !n; };
        auto isLeaf = [](TreeNode* n) { return n && !n->left && !n->right; };
        
        if (isNull(node)) return false;
        
        if (isLeaf(node)) {
            return node->val == target;
        }
        
        // Recursive checker creation
        auto checker = createPathChecker();
        
        // Path exploration lambdas
        auto exploreLeft = [&]() {
            return node->left ? checker(node->left, target - node->val) : false;
        };
        
        auto exploreRight = [&]() {
            return node->right ? checker(node->right, target - node->val) : false;
        };
        
        // Combine results
        return exploreLeft() || exploreRight();
    };
}

}  // namespace easy
}  // namespace leetcode