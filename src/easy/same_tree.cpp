#include "same_tree.h"
#include <queue>
#include <stack>
#include <sstream>
#include <functional>

namespace leetcode {
namespace easy {

// Approach 1: Recursive DFS (Optimal)
bool SameTree::isSameTreeRecursive(TreeNode* p, TreeNode* q) {
    // Base case: both trees are empty
    if (!p && !q) {
        return true;
    }
    
    // One tree is empty, the other is not
    if (!p || !q) {
        return false;
    }
    
    // Check current nodes have same value
    if (p->val != q->val) {
        return false;
    }
    
    // Recursively check left and right subtrees
    return isSameTreeRecursive(p->left, q->left) && 
           isSameTreeRecursive(p->right, q->right);
}

// Approach 2: Iterative BFS with Queue
bool SameTree::isSameTreeBFS(TreeNode* p, TreeNode* q) {
    // Use queue to store pairs of nodes to compare
    std::queue<std::pair<TreeNode*, TreeNode*>> queue;
    queue.push({p, q});
    
    while (!queue.empty()) {
        auto [node1, node2] = queue.front();
        queue.pop();
        
        // Both null - continue to next pair
        if (!node1 && !node2) {
            continue;
        }
        
        // One null or values different - trees are different
        if (!node1 || !node2 || node1->val != node2->val) {
            return false;
        }
        
        // Add children pairs to queue
        queue.push({node1->left, node2->left});
        queue.push({node1->right, node2->right});
    }
    
    return true;
}

// Approach 3: Iterative DFS with Stack
bool SameTree::isSameTreeDFS(TreeNode* p, TreeNode* q) {
    // Use stack for iterative DFS
    std::stack<std::pair<TreeNode*, TreeNode*>> stack;
    stack.push({p, q});
    
    while (!stack.empty()) {
        auto [node1, node2] = stack.top();
        stack.pop();
        
        // Both null - continue
        if (!node1 && !node2) {
            continue;
        }
        
        // One null or values different
        if (!node1 || !node2 || node1->val != node2->val) {
            return false;
        }
        
        // Push children pairs to stack (right first for left-to-right DFS)
        stack.push({node1->right, node2->right});
        stack.push({node1->left, node2->left});
    }
    
    return true;
}

// Approach 4: String Serialization
bool SameTree::isSameTreeSerialization(TreeNode* p, TreeNode* q) {
    return serialize(p) == serialize(q);
}

std::string SameTree::serialize(TreeNode* root) {
    if (!root) {
        return "null";
    }
    
    std::stringstream ss;
    ss << root->val << "," 
       << serialize(root->left) << "," 
       << serialize(root->right);
    
    return ss.str();
}

// Approach 5: Morris Traversal (Space Optimized)
bool SameTree::isSameTreeMorris(TreeNode* p, TreeNode* q) {
    TreeNode* curr1 = p;
    TreeNode* curr2 = q;
    
    while (curr1 || curr2) {
        // If one is null and other isn't
        if (!curr1 || !curr2) {
            return false;
        }
        
        // If no left child in either tree
        if (!curr1->left && !curr2->left) {
            // Compare values
            if (curr1->val != curr2->val) {
                return false;
            }
            // Move to right
            curr1 = curr1->right;
            curr2 = curr2->right;
        }
        // If both have left children
        else if (curr1->left && curr2->left) {
            // Find predecessors
            TreeNode* pred1 = findPredecessor(curr1);
            TreeNode* pred2 = findPredecessor(curr2);
            
            // If right child of predecessor is null, make thread
            if (!pred1->right && !pred2->right) {
                pred1->right = curr1;
                pred2->right = curr2;
                curr1 = curr1->left;
                curr2 = curr2->left;
            }
            // Thread already exists, remove it and process current
            else if (pred1->right == curr1 && pred2->right == curr2) {
                pred1->right = nullptr;
                pred2->right = nullptr;
                
                // Compare values
                if (curr1->val != curr2->val) {
                    return false;
                }
                
                curr1 = curr1->right;
                curr2 = curr2->right;
            }
            else {
                // Structural difference
                return false;
            }
        }
        else {
            // One has left child, other doesn't
            return false;
        }
    }
    
    return true;
}

TreeNode* SameTree::findPredecessor(TreeNode* current) {
    TreeNode* pred = current->left;
    while (pred->right && pred->right != current) {
        pred = pred->right;
    }
    return pred;
}

// Approach 6: Hash-based Structural Comparison
bool SameTree::isSameTreeHash(TreeNode* p, TreeNode* q) {
    return computeTreeHash(p) == computeTreeHash(q);
}

size_t SameTree::computeTreeHash(TreeNode* root) {
    if (!root) {
        // Use a special value for null nodes
        return std::hash<int>()(INT_MIN);
    }
    
    // Combine hash of current value with hashes of subtrees
    size_t h1 = std::hash<int>()(root->val);
    size_t h2 = computeTreeHash(root->left);
    size_t h3 = computeTreeHash(root->right);
    
    // Combine hashes using prime multipliers to maintain structure
    // Different positions (left vs right) get different multipliers
    return h1 ^ (h2 << 1) ^ (h3 << 2);
}

}  // namespace easy
}  // namespace leetcode