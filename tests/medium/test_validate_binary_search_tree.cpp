#include <gtest/gtest.h>
#include "../../src/medium/validate_binary_search_tree.h"
#include "../../src/utils/data_structures.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace leetcode::utils;

namespace leetcode {
namespace medium {
namespace test {

class ValidateBinarySearchTreeTest : public ::testing::Test {
protected:
    ValidateBinarySearchTree solution;
    
    void testAllApproaches(TreeNode* root, bool expected) {
        EXPECT_EQ(solution.isValidBST(root), expected) 
            << "Inorder Array approach failed";
        EXPECT_EQ(solution.isValidBSTInorderOptimized(root), expected) 
            << "Inorder Optimized approach failed";
        EXPECT_EQ(solution.isValidBSTBounds(root), expected) 
            << "Min/Max Bounds approach failed";
        EXPECT_EQ(solution.isValidBSTIterative(root), expected) 
            << "Iterative Inorder approach failed";
        EXPECT_EQ(solution.isValidBSTMorris(root), expected) 
            << "Morris Traversal approach failed";
        EXPECT_EQ(solution.isValidBSTLevelOrder(root), expected) 
            << "Level Order approach failed";
    }
    
    // Helper function to create tree from vector (level order)
    TreeNode* createTree(const std::vector<int*>& values) {
        if (values.empty() || !values[0]) return nullptr;
        
        TreeNode* root = new TreeNode(*values[0]);
        std::queue<TreeNode*> queue;
        queue.push(root);
        
        for (int i = 1; i < values.size(); i += 2) {
            TreeNode* current = queue.front();
            queue.pop();
            
            if (i < values.size() && values[i]) {
                current->left = new TreeNode(*values[i]);
                queue.push(current->left);
            }
            
            if (i + 1 < values.size() && values[i + 1]) {
                current->right = new TreeNode(*values[i + 1]);
                queue.push(current->right);
            }
        }
        
        return root;
    }
    
    // Helper to create values (for null nodes)
    int* val(int x) { return new int(x); }
    int* null() { return nullptr; }
    
    void TearDown() override {
        // Note: In practice, should implement proper tree cleanup
        // For testing purposes, relying on test framework cleanup
    }
};

// Basic functionality tests
TEST_F(ValidateBinarySearchTreeTest, SingleNode) {
    TreeNode* root = new TreeNode(1);
    testAllApproaches(root, true);
    
    root = new TreeNode(INT_MAX);
    testAllApproaches(root, true);
    
    root = new TreeNode(INT_MIN);
    testAllApproaches(root, true);
}

TEST_F(ValidateBinarySearchTreeTest, TwoNodes) {
    // Valid cases
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    testAllApproaches(root, true);
    
    root = new TreeNode(1);
    root->right = new TreeNode(2);
    testAllApproaches(root, true);
    
    // Invalid cases
    root = new TreeNode(1);
    root->left = new TreeNode(2);
    testAllApproaches(root, false);
    
    root = new TreeNode(2);
    root->right = new TreeNode(1);
    testAllApproaches(root, false);
}

TEST_F(ValidateBinarySearchTreeTest, LeetCodeExamples) {
    // Example 1: [2,1,3] - Valid BST
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    testAllApproaches(root, true);
    
    // Example 2: [5,1,4,null,null,3,6] - Invalid BST
    root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(6);
    testAllApproaches(root, false);
}

// Edge cases with duplicates
TEST_F(ValidateBinarySearchTreeTest, DuplicateValues) {
    // Root and left child same value
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(1);
    testAllApproaches(root, false);
    
    // Root and right child same value
    root = new TreeNode(1);
    root->right = new TreeNode(1);
    testAllApproaches(root, false);
    
    // Duplicate values in different subtrees
    root = new TreeNode(2);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    testAllApproaches(root, false);
}

// Empty tree
TEST_F(ValidateBinarySearchTreeTest, EmptyTree) {
    testAllApproaches(nullptr, true);
}

// Linear trees (essentially linked lists)
TEST_F(ValidateBinarySearchTreeTest, LeftSkewed) {
    // Valid left-skewed tree: 4->3->2->1
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(2);
    root->left->left->left = new TreeNode(1);
    testAllApproaches(root, true);
    
    // Invalid left-skewed tree: 1->2->3->4
    root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    testAllApproaches(root, false);
}

TEST_F(ValidateBinarySearchTreeTest, RightSkewed) {
    // Valid right-skewed tree: 1->2->3->4
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    testAllApproaches(root, true);
    
    // Invalid right-skewed tree: 4->3->2->1
    root = new TreeNode(4);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(2);
    root->right->right->right = new TreeNode(1);
    testAllApproaches(root, false);
}

// Complex valid BSTs
TEST_F(ValidateBinarySearchTreeTest, CompleteValidBST) {
    // Perfect BST: [4,2,6,1,3,5,7]
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    testAllApproaches(root, true);
}

TEST_F(ValidateBinarySearchTreeTest, LargeValidBST) {
    // [8,4,12,2,6,10,14,1,3,5,7,9,11,13,15]
    TreeNode* root = new TreeNode(8);
    
    // Level 1
    root->left = new TreeNode(4);
    root->right = new TreeNode(12);
    
    // Level 2
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(6);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(14);
    
    // Level 3
    root->left->left->left = new TreeNode(1);
    root->left->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(5);
    root->left->right->right = new TreeNode(7);
    root->right->left->left = new TreeNode(9);
    root->right->left->right = new TreeNode(11);
    root->right->right->left = new TreeNode(13);
    root->right->right->right = new TreeNode(15);
    
    testAllApproaches(root, true);
}

// Boundary violations
TEST_F(ValidateBinarySearchTreeTest, SubtreeBoundaryViolation) {
    // [5,4,6,null,null,3,7] - 3 violates BST property (should be > 5)
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(6);
    root->right->left = new TreeNode(3);  // This violates BST
    root->right->right = new TreeNode(7);
    testAllApproaches(root, false);
    
    // [10,5,15,null,null,6,20] - 6 should be < 10 but it's in right subtree
    root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(6);  // Violates BST
    root->right->right = new TreeNode(20);
    testAllApproaches(root, false);
}

// Extreme values
TEST_F(ValidateBinarySearchTreeTest, ExtremeBounds) {
    // Tree with INT_MIN and INT_MAX
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(INT_MIN);
    root->right = new TreeNode(INT_MAX);
    testAllApproaches(root, true);
    
    // Invalid case where INT_MIN is on right
    root = new TreeNode(0);
    root->right = new TreeNode(INT_MIN);
    testAllApproaches(root, false);
    
    // Invalid case where INT_MAX is on left
    root = new TreeNode(0);
    root->left = new TreeNode(INT_MAX);
    testAllApproaches(root, false);
}

// Subtle violations
TEST_F(ValidateBinarySearchTreeTest, SubtleViolations) {
    // Case where local BST property holds but global doesn't
    // [8,3,10,1,6,null,14,null,null,4,7,13]
    // The 4 and 7 are in correct positions relative to 6,
    // but 7 > 3 which violates BST property
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(3);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(6);
    root->right->right = new TreeNode(14);
    root->left->right->left = new TreeNode(4);
    root->left->right->right = new TreeNode(7);  // This should be < 8
    root->right->right->left = new TreeNode(13);
    
    // This is actually valid since 7 < 8, let me create an invalid case
    testAllApproaches(root, true);
}

TEST_F(ValidateBinarySearchTreeTest, ActualSubtleViolation) {
    // [10,5,15,null,null,6,20] where 6 > 5 but 6 should be < 10 (it's in right subtree)
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(6);  // Invalid: 6 < 10 but in right subtree
    root->right->right = new TreeNode(20);
    testAllApproaches(root, false);
    
    // Another case: [10,5,15,null,null,12,20] where right child is 15 but its left is 12
    // This is valid since 12 > 10 and 12 < 15
    root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(12);
    root->right->right = new TreeNode(20);
    testAllApproaches(root, true);
}

// Algorithm-specific tests
TEST_F(ValidateBinarySearchTreeTest, InorderSequenceValidation) {
    // Test that inorder approaches correctly identify non-increasing sequences
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(1);  // Equal values should be invalid
    testAllApproaches(root, false);
    
    // Decreasing sequence
    root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);  // 4 > 3, invalid
    testAllApproaches(root, false);
}

TEST_F(ValidateBinarySearchTreeTest, BoundsValidation) {
    // Test that bounds approaches correctly propagate constraints
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(7);  // 7 > 5, invalid for left subtree
    testAllApproaches(root, false);
}

// Performance and stress tests
TEST_F(ValidateBinarySearchTreeTest, DeepTree) {
    // Create a deep valid BST (right-skewed)
    TreeNode* root = new TreeNode(1);
    TreeNode* current = root;
    for (int i = 2; i <= 100; ++i) {
        current->right = new TreeNode(i);
        current = current->right;
    }
    testAllApproaches(root, true);
}

TEST_F(ValidateBinarySearchTreeTest, WideTree) {
    // Create a wide tree (complete binary tree)
    // Build perfect BST of height 3
    TreeNode* root = new TreeNode(8);
    
    // Level 1
    root->left = new TreeNode(4);
    root->right = new TreeNode(12);
    
    // Level 2  
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(6);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(14);
    
    // Level 3
    root->left->left->left = new TreeNode(1);
    root->left->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(5);
    root->left->right->right = new TreeNode(7);
    root->right->left->left = new TreeNode(9);
    root->right->left->right = new TreeNode(11);
    root->right->right->left = new TreeNode(13);
    root->right->right->right = new TreeNode(15);
    
    testAllApproaches(root, true);
}

// Special number patterns
TEST_F(ValidateBinarySearchTreeTest, ConsecutiveNumbers) {
    // [5,4,6,3,5,null,7] - duplicate 5 makes it invalid
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(5);  // Duplicate
    root->right->right = new TreeNode(7);
    testAllApproaches(root, false);
}

TEST_F(ValidateBinarySearchTreeTest, NegativeNumbers) {
    // Valid BST with negative numbers
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(-5);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(-10);
    root->left->right = new TreeNode(-1);
    root->right->left = new TreeNode(1);
    root->right->right = new TreeNode(10);
    testAllApproaches(root, true);
}

TEST_F(ValidateBinarySearchTreeTest, AllNegativeNumbers) {
    // Valid BST with all negative numbers
    TreeNode* root = new TreeNode(-5);
    root->left = new TreeNode(-10);
    root->right = new TreeNode(-1);
    root->left->left = new TreeNode(-15);
    root->left->right = new TreeNode(-7);
    root->right->left = new TreeNode(-3);
    testAllApproaches(root, true);
}

// Morris traversal specific test
TEST_F(ValidateBinarySearchTreeTest, MorrisTraversalIntegrity) {
    // Test that Morris traversal doesn't permanently modify the tree
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    
    // Verify tree structure before
    EXPECT_EQ(root->val, 2);
    EXPECT_EQ(root->left->val, 1);
    EXPECT_EQ(root->right->val, 3);
    EXPECT_EQ(root->left->right, nullptr);
    
    // Run Morris traversal
    bool result = solution.isValidBSTMorris(root);
    EXPECT_TRUE(result);
    
    // Verify tree structure is unchanged after Morris traversal
    EXPECT_EQ(root->val, 2);
    EXPECT_EQ(root->left->val, 1);
    EXPECT_EQ(root->right->val, 3);
    EXPECT_EQ(root->left->right, nullptr);
}

}
}
}