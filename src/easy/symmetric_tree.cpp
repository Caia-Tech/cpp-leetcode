#include "symmetric_tree.h"
#include <queue>
#include <stack>
#include <algorithm>

namespace leetcode {
namespace easy {

// Define the static constant
const int SymmetricTree::NULL_MARKER;

// Approach 1: Recursive Comparison (Optimal)
bool SymmetricTree::isSymmetricRecursive(TreeNode* root) {
    if (!root) return true;
    return isMirror(root->left, root->right);
}

bool SymmetricTree::isMirror(TreeNode* left, TreeNode* right) {
    // Both null - symmetric
    if (!left && !right) return true;
    
    // One null, one not - not symmetric
    if (!left || !right) return false;
    
    // Values must match and subtrees must be mirrors
    return (left->val == right->val) &&
           isMirror(left->left, right->right) &&
           isMirror(left->right, right->left);
}

// Approach 2: Iterative BFS with Queue
bool SymmetricTree::isSymmetricBFS(TreeNode* root) {
    if (!root) return true;
    
    std::queue<TreeNode*> queue;
    queue.push(root->left);
    queue.push(root->right);
    
    while (!queue.empty()) {
        TreeNode* left = queue.front(); queue.pop();
        TreeNode* right = queue.front(); queue.pop();
        
        // Both null - continue
        if (!left && !right) continue;
        
        // One null or different values - not symmetric
        if (!left || !right || left->val != right->val) {
            return false;
        }
        
        // Add mirror pairs to queue
        queue.push(left->left);
        queue.push(right->right);
        queue.push(left->right);
        queue.push(right->left);
    }
    
    return true;
}

// Approach 3: Iterative DFS with Stack
bool SymmetricTree::isSymmetricDFS(TreeNode* root) {
    if (!root) return true;
    
    std::stack<TreeNode*> stack;
    stack.push(root->left);
    stack.push(root->right);
    
    while (!stack.empty()) {
        TreeNode* right = stack.top(); stack.pop();
        TreeNode* left = stack.top(); stack.pop();
        
        // Both null - continue
        if (!left && !right) continue;
        
        // One null or different values - not symmetric
        if (!left || !right || left->val != right->val) {
            return false;
        }
        
        // Push mirror pairs
        stack.push(left->left);
        stack.push(right->right);
        stack.push(left->right);
        stack.push(right->left);
    }
    
    return true;
}

// Approach 4: In-order Traversal Comparison
bool SymmetricTree::isSymmetricInOrder(TreeNode* root) {
    if (!root) return true;
    
    std::vector<int> leftTraversal, rightTraversal;
    inOrderLeft(root->left, leftTraversal);
    inOrderRight(root->right, rightTraversal);
    
    return leftTraversal == rightTraversal;
}

void SymmetricTree::inOrderLeft(TreeNode* root, std::vector<int>& result) {
    if (!root) {
        result.push_back(NULL_MARKER);
        return;
    }
    
    inOrderLeft(root->left, result);
    result.push_back(root->val);
    inOrderLeft(root->right, result);
}

void SymmetricTree::inOrderRight(TreeNode* root, std::vector<int>& result) {
    if (!root) {
        result.push_back(NULL_MARKER);
        return;
    }
    
    inOrderRight(root->right, result);
    result.push_back(root->val);
    inOrderRight(root->left, result);
}

// Approach 5: String Serialization
bool SymmetricTree::isSymmetricSerialization(TreeNode* root) {
    if (!root) return true;
    
    std::stringstream ss;
    serialize(root, ss);
    std::string serialized = ss.str();
    
    return isPalindrome(serialized);
}

void SymmetricTree::serialize(TreeNode* root, std::stringstream& ss) {
    if (!root) {
        ss << "null,";
        return;
    }
    
    ss << root->val << ",";
    serialize(root->left, ss);
    serialize(root->right, ss);
}

bool SymmetricTree::isPalindrome(const std::string& s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// Approach 6: Pre-order and Post-order Combination
bool SymmetricTree::isSymmetricTraversal(TreeNode* root) {
    if (!root) return true;
    
    std::vector<int> leftPreOrder, rightMirrorPreOrder;
    preOrder(root->left, leftPreOrder);
    mirrorPreOrder(root->right, rightMirrorPreOrder);
    
    return leftPreOrder == rightMirrorPreOrder;
}

void SymmetricTree::preOrder(TreeNode* root, std::vector<int>& result) {
    if (!root) {
        result.push_back(NULL_MARKER);
        return;
    }
    
    result.push_back(root->val);
    preOrder(root->left, result);
    preOrder(root->right, result);
}

void SymmetricTree::mirrorPreOrder(TreeNode* root, std::vector<int>& result) {
    if (!root) {
        result.push_back(NULL_MARKER);
        return;
    }
    
    result.push_back(root->val);
    mirrorPreOrder(root->right, result);
    mirrorPreOrder(root->left, result);
}

}  // namespace easy
}  // namespace leetcode