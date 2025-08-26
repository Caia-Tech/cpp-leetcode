#include <gtest/gtest.h>
#include "../../src/easy/binary_tree_preorder_traversal.h"
#include "../../src/utils/test_utils.h"
#include <vector>

using namespace leetcode::easy;

// Test fixture for Binary Tree Preorder Traversal
class BinaryTreePreorderTraversalTest : public ::testing::Test {
protected:
    void testAllApproaches(leetcode::utils::TreeNode* root, const std::vector<int>& expected) {
        EXPECT_EQ(BinaryTreePreorderTraversal::preorderTraversalRecursive(root), expected) 
            << "Recursive approach failed";
        EXPECT_EQ(BinaryTreePreorderTraversal::preorderTraversalIterative(root), expected) 
            << "Iterative approach failed";
        EXPECT_EQ(BinaryTreePreorderTraversal::preorderTraversalMorris(root), expected) 
            << "Morris traversal failed";
        EXPECT_EQ(BinaryTreePreorderTraversal::preorderTraversalStack(root), expected) 
            << "Stack approach failed";
        EXPECT_EQ(BinaryTreePreorderTraversal::preorderTraversalTemplate(root), expected) 
            << "Template approach failed";
        EXPECT_EQ(BinaryTreePreorderTraversal::preorderTraversalOptimized(root), expected) 
            << "Optimized approach failed";
    }
    
    void TearDown() override {
        // Clean up any allocated trees
        // Note: In real implementation, we'd need proper cleanup
    }
};

// Test Case 1: Empty tree
TEST_F(BinaryTreePreorderTraversalTest, EmptyTree) {
    testAllApproaches(nullptr, {});
}

// Test Case 2: Single node tree
TEST_F(BinaryTreePreorderTraversalTest, SingleNode) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    testAllApproaches(root, {1});
}

// Test Case 3: LeetCode example 1 - [1,null,2,3]
TEST_F(BinaryTreePreorderTraversalTest, LeetCodeExample1) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->right = new leetcode::utils::TreeNode(2);
    root->right->left = new leetcode::utils::TreeNode(3);
    
    testAllApproaches(root, {1, 2, 3});
}

// Test Case 4: Complete binary tree
TEST_F(BinaryTreePreorderTraversalTest, CompleteBinaryTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(3);
    root->left->left = new leetcode::utils::TreeNode(4);
    root->left->right = new leetcode::utils::TreeNode(5);
    root->right->left = new leetcode::utils::TreeNode(6);
    root->right->right = new leetcode::utils::TreeNode(7);
    
    testAllApproaches(root, {1, 2, 4, 5, 3, 6, 7});
}

// Test Case 5: Left-heavy tree (worst case for recursion)
TEST_F(BinaryTreePreorderTraversalTest, LeftHeavyTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->left->left = new leetcode::utils::TreeNode(3);
    root->left->left->left = new leetcode::utils::TreeNode(4);
    root->left->left->left->left = new leetcode::utils::TreeNode(5);
    
    testAllApproaches(root, {1, 2, 3, 4, 5});
}

// Test Case 6: Right-heavy tree
TEST_F(BinaryTreePreorderTraversalTest, RightHeavyTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->right = new leetcode::utils::TreeNode(2);
    root->right->right = new leetcode::utils::TreeNode(3);
    root->right->right->right = new leetcode::utils::TreeNode(4);
    root->right->right->right->right = new leetcode::utils::TreeNode(5);
    
    testAllApproaches(root, {1, 2, 3, 4, 5});
}

// Test Case 7: Balanced tree with negative values
TEST_F(BinaryTreePreorderTraversalTest, NegativeValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(-10);
    root->left = new leetcode::utils::TreeNode(-20);
    root->right = new leetcode::utils::TreeNode(-30);
    root->left->left = new leetcode::utils::TreeNode(-40);
    root->left->right = new leetcode::utils::TreeNode(-50);
    
    testAllApproaches(root, {-10, -20, -40, -50, -30});
}

// Test Case 8: Mixed positive and negative values
TEST_F(BinaryTreePreorderTraversalTest, MixedValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(0);
    root->left = new leetcode::utils::TreeNode(-1);
    root->right = new leetcode::utils::TreeNode(1);
    root->left->left = new leetcode::utils::TreeNode(-100);
    root->right->right = new leetcode::utils::TreeNode(100);
    
    testAllApproaches(root, {0, -1, -100, 1, 100});
}

// Test Case 9: Large balanced tree
TEST_F(BinaryTreePreorderTraversalTest, LargeBalancedTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(50);
    root->left = new leetcode::utils::TreeNode(25);
    root->right = new leetcode::utils::TreeNode(75);
    root->left->left = new leetcode::utils::TreeNode(12);
    root->left->right = new leetcode::utils::TreeNode(37);
    root->right->left = new leetcode::utils::TreeNode(62);
    root->right->right = new leetcode::utils::TreeNode(87);
    root->left->left->left = new leetcode::utils::TreeNode(6);
    root->left->left->right = new leetcode::utils::TreeNode(18);
    root->left->right->left = new leetcode::utils::TreeNode(31);
    root->left->right->right = new leetcode::utils::TreeNode(43);
    
    testAllApproaches(root, {50, 25, 12, 6, 18, 37, 31, 43, 75, 62, 87});
}

// Test Case 10: Only left children (degenerate tree)
TEST_F(BinaryTreePreorderTraversalTest, OnlyLeftChildren) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(10);
    root->left = new leetcode::utils::TreeNode(20);
    root->left->left = new leetcode::utils::TreeNode(30);
    root->left->left->left = new leetcode::utils::TreeNode(40);
    
    testAllApproaches(root, {10, 20, 30, 40});
}

// Test Case 11: Only right children (degenerate tree)
TEST_F(BinaryTreePreorderTraversalTest, OnlyRightChildren) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(10);
    root->right = new leetcode::utils::TreeNode(20);
    root->right->right = new leetcode::utils::TreeNode(30);
    root->right->right->right = new leetcode::utils::TreeNode(40);
    
    testAllApproaches(root, {10, 20, 30, 40});
}

// Test Case 12: Duplicate values
TEST_F(BinaryTreePreorderTraversalTest, DuplicateValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(1);
    root->right = new leetcode::utils::TreeNode(1);
    root->left->left = new leetcode::utils::TreeNode(1);
    root->left->right = new leetcode::utils::TreeNode(1);
    
    testAllApproaches(root, {1, 1, 1, 1, 1});
}

// Test Case 13: Maximum constraint values
TEST_F(BinaryTreePreorderTraversalTest, MaximumValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(100);
    root->left = new leetcode::utils::TreeNode(-100);
    root->right = new leetcode::utils::TreeNode(99);
    root->left->left = new leetcode::utils::TreeNode(-99);
    
    testAllApproaches(root, {100, -100, -99, 99});
}

// Test Case 14: Asymmetric tree
TEST_F(BinaryTreePreorderTraversalTest, AsymmetricTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(3);
    root->left->right = new leetcode::utils::TreeNode(4);
    root->right->left = new leetcode::utils::TreeNode(5);
    root->right->right = new leetcode::utils::TreeNode(6);
    root->right->left->left = new leetcode::utils::TreeNode(7);
    
    testAllApproaches(root, {1, 2, 4, 3, 5, 7, 6});
}

// Test Case 15: Binary search tree property (not required but good test)
TEST_F(BinaryTreePreorderTraversalTest, BinarySearchTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(8);
    root->left = new leetcode::utils::TreeNode(3);
    root->right = new leetcode::utils::TreeNode(10);
    root->left->left = new leetcode::utils::TreeNode(1);
    root->left->right = new leetcode::utils::TreeNode(6);
    root->right->right = new leetcode::utils::TreeNode(14);
    root->left->right->left = new leetcode::utils::TreeNode(4);
    root->left->right->right = new leetcode::utils::TreeNode(7);
    root->right->right->left = new leetcode::utils::TreeNode(13);
    
    testAllApproaches(root, {8, 3, 1, 6, 4, 7, 10, 14, 13});
}

// Test Case 16: Full binary tree (all nodes have 0 or 2 children)
TEST_F(BinaryTreePreorderTraversalTest, FullBinaryTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(3);
    root->left->left = new leetcode::utils::TreeNode(4);
    root->left->right = new leetcode::utils::TreeNode(5);
    root->right->left = new leetcode::utils::TreeNode(6);
    root->right->right = new leetcode::utils::TreeNode(7);
    
    testAllApproaches(root, {1, 2, 4, 5, 3, 6, 7});
}

// Test Case 17: Tree with alternating structure
TEST_F(BinaryTreePreorderTraversalTest, AlternatingStructure) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->left->right = new leetcode::utils::TreeNode(3);
    root->left->right->left = new leetcode::utils::TreeNode(4);
    root->left->right->left->right = new leetcode::utils::TreeNode(5);
    
    testAllApproaches(root, {1, 2, 3, 4, 5});
}

// Test Case 18: Large depth tree (stress test)
TEST_F(BinaryTreePreorderTraversalTest, LargeDepthTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    leetcode::utils::TreeNode* current = root;
    
    // Create a deep left-leaning tree
    for (int i = 2; i <= 20; ++i) {
        current->left = new leetcode::utils::TreeNode(i);
        current = current->left;
    }
    
    std::vector<int> expected;
    for (int i = 1; i <= 20; ++i) {
        expected.push_back(i);
    }
    
    testAllApproaches(root, expected);
}

// Test Case 19: Random structure tree
TEST_F(BinaryTreePreorderTraversalTest, RandomStructure) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(15);
    root->left = new leetcode::utils::TreeNode(10);
    root->right = new leetcode::utils::TreeNode(20);
    root->left->left = new leetcode::utils::TreeNode(8);
    root->left->right = new leetcode::utils::TreeNode(12);
    root->right->left = new leetcode::utils::TreeNode(16);
    root->right->right = new leetcode::utils::TreeNode(25);
    root->left->left->left = new leetcode::utils::TreeNode(5);
    root->right->right->right = new leetcode::utils::TreeNode(30);
    
    testAllApproaches(root, {15, 10, 8, 5, 12, 20, 16, 25, 30});
}

// Test Case 20: Edge case - minimum and maximum node values
TEST_F(BinaryTreePreorderTraversalTest, MinMaxValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(0);
    root->left = new leetcode::utils::TreeNode(-100);
    root->right = new leetcode::utils::TreeNode(100);
    
    testAllApproaches(root, {0, -100, 100});
}

