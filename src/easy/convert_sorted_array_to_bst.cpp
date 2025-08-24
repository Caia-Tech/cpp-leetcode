#include "convert_sorted_array_to_bst.h"
#include <stack>
#include <random>

namespace leetcode {
namespace easy {

// Approach 1: Recursive Divide and Conquer (Optimal)
TreeNode* ConvertSortedArrayToBST::sortedArrayToBSTRecursive(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return buildBSTRecursive(nums, 0, nums.size() - 1);
}

TreeNode* ConvertSortedArrayToBST::buildBSTRecursive(std::vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    // Choose middle element as root
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    // Recursively build left and right subtrees
    root->left = buildBSTRecursive(nums, left, mid - 1);
    root->right = buildBSTRecursive(nums, mid + 1, right);
    
    return root;
}

// Approach 2: Iterative with Stack
TreeNode* ConvertSortedArrayToBST::sortedArrayToBSTIterative(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;
    
    // Create root node
    int mid = (nums.size() - 1) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    // Stack to manage ranges and corresponding nodes
    std::stack<TreeRange> stack;
    stack.emplace(root, 0, nums.size() - 1);
    
    while (!stack.empty()) {
        TreeRange current = stack.top();
        stack.pop();
        
        TreeNode* node = current.node;
        int left = current.left;
        int right = current.right;
        int currentMid = left + (right - left) / 2;
        
        // Build left subtree
        if (left < currentMid) {
            int leftMid = left + (currentMid - 1 - left) / 2;
            node->left = new TreeNode(nums[leftMid]);
            stack.emplace(node->left, left, currentMid - 1);
        }
        
        // Build right subtree
        if (currentMid < right) {
            int rightMid = (currentMid + 1) + (right - (currentMid + 1)) / 2;
            node->right = new TreeNode(nums[rightMid]);
            stack.emplace(node->right, currentMid + 1, right);
        }
    }
    
    return root;
}

// Approach 3: Pre-order Construction
TreeNode* ConvertSortedArrayToBST::sortedArrayToBSTPreOrder(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return buildBSTPreOrder(nums, 0, nums.size() - 1);
}

TreeNode* ConvertSortedArrayToBST::buildBSTPreOrder(std::vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    // Pre-order: process root first
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    // Then process left subtree in pre-order
    if (left < mid) {
        root->left = buildBSTPreOrder(nums, left, mid - 1);
    }
    
    // Finally process right subtree in pre-order
    if (mid < right) {
        root->right = buildBSTPreOrder(nums, mid + 1, right);
    }
    
    return root;
}

// Approach 4: Random Middle Selection
TreeNode* ConvertSortedArrayToBST::sortedArrayToBSTRandom(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return buildBSTRandom(nums, 0, nums.size() - 1);
}

TreeNode* ConvertSortedArrayToBST::buildBSTRandom(std::vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    
    // For even-length ranges, randomly choose between two middle elements
    int mid;
    if ((right - left) % 2 == 1) {
        // Even number of elements, two potential middles
        int mid1 = left + (right - left) / 2;
        int mid2 = mid1 + 1;
        mid = getRandomInRange(0, 1) ? mid1 : mid2;
    } else {
        // Odd number of elements, unique middle
        mid = left + (right - left) / 2;
    }
    
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = buildBSTRandom(nums, left, mid - 1);
    root->right = buildBSTRandom(nums, mid + 1, right);
    
    return root;
}

int ConvertSortedArrayToBST::getRandomInRange(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Approach 5: Level-Order Construction
TreeNode* ConvertSortedArrayToBST::sortedArrayToBSTLevelOrder(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;
    
    // Create root
    int mid = (nums.size() - 1) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    // Queue for level-order construction
    std::queue<NodeRange> queue;
    
    // Add left and right child ranges if they exist
    if (0 < mid) {
        queue.emplace(&(root->left), 0, mid - 1);
    }
    if (mid < static_cast<int>(nums.size()) - 1) {
        queue.emplace(&(root->right), mid + 1, nums.size() - 1);
    }
    
    while (!queue.empty()) {
        NodeRange current = queue.front();
        queue.pop();
        
        int left = current.left;
        int right = current.right;
        int currentMid = left + (right - left) / 2;
        
        // Create the node
        *(current.nodeRef) = new TreeNode(nums[currentMid]);
        TreeNode* node = *(current.nodeRef);
        
        // Add left child range to queue if it exists
        if (left < currentMid) {
            queue.emplace(&(node->left), left, currentMid - 1);
        }
        
        // Add right child range to queue if it exists
        if (currentMid < right) {
            queue.emplace(&(node->right), currentMid + 1, right);
        }
    }
    
    return root;
}

// Approach 6: Functional Programming with Lambda
TreeNode* ConvertSortedArrayToBST::sortedArrayToBSTFunctional(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;
    
    auto builder = createBSTBuilder(nums);
    return builder(0, nums.size() - 1);
}

std::function<TreeNode*(int, int)> ConvertSortedArrayToBST::createBSTBuilder(std::vector<int>& nums) {
    return [&nums](int left, int right) -> TreeNode* {
        // Capture the recursive lambda
        std::function<TreeNode*(int, int)> build = [&nums](int l, int r) -> TreeNode* {
            if (l > r) return nullptr;
            
            int mid = l + (r - l) / 2;
            TreeNode* root = new TreeNode(nums[mid]);
            
            // Use the capturing lambda recursively
            std::function<TreeNode*(int, int)> recursiveBuild;
            recursiveBuild = [&nums, &recursiveBuild](int left, int right) -> TreeNode* {
                if (left > right) return nullptr;
                
                int mid = left + (right - left) / 2;
                TreeNode* node = new TreeNode(nums[mid]);
                node->left = recursiveBuild(left, mid - 1);
                node->right = recursiveBuild(mid + 1, right);
                
                return node;
            };
            
            root->left = recursiveBuild(l, mid - 1);
            root->right = recursiveBuild(mid + 1, r);
            
            return root;
        };
        
        return build(left, right);
    };
}

}  // namespace easy
}  // namespace leetcode