#include <gtest/gtest.h>
#include "../../src/easy/binary_tree_postorder_traversal.h"
#include "../../src/utils/data_structures.h"

using namespace leetcode::easy;
using namespace leetcode::utils;

// Test fixture for Binary Tree Postorder Traversal
class BinaryTreePostorderTraversalTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test cases will set up individual trees
    }
    
    void TearDown() override {
        // Clean up any dynamically allocated trees
    }
    
    // Helper function to test all approaches
    void testAllApproaches(leetcode::utils::TreeNode* root, const std::vector<int>& expected) {
        EXPECT_EQ(BinaryTreePostorderTraversal::postorderTraversalRecursive(root), expected)
            << "Recursive approach failed";
        EXPECT_EQ(BinaryTreePostorderTraversal::postorderTraversalTwoStacks(root), expected)
            << "Two stacks approach failed";
        EXPECT_EQ(BinaryTreePostorderTraversal::postorderTraversalSingleStack(root), expected)
            << "Single stack approach failed";
        EXPECT_EQ(BinaryTreePostorderTraversal::postorderTraversalMorris(root), expected)
            << "Morris traversal approach failed";
        EXPECT_EQ(BinaryTreePostorderTraversal::postorderTraversalReversePreorder(root), expected)
            << "Reverse preorder approach failed";
        EXPECT_EQ(BinaryTreePostorderTraversal::postorderTraversalWithState(root), expected)
            << "State tracking approach failed";
    }
};

// Test Case 1: Empty tree
TEST_F(BinaryTreePostorderTraversalTest, EmptyTree) {
    leetcode::utils::TreeNode* root = nullptr;
    std::vector<int> expected = {};
    testAllApproaches(root, expected);
}

// Test Case 2: Single node
TEST_F(BinaryTreePostorderTraversalTest, SingleNode) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    std::vector<int> expected = {1};
    testAllApproaches(root, expected);
    delete root;
}

// Test Case 3: LeetCode Example 1 - [1,null,2,3]
TEST_F(BinaryTreePostorderTraversalTest, LeetCodeExample1) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->right = new leetcode::utils::TreeNode(2);
    root->right->left = new leetcode::utils::TreeNode(3);
    
    std::vector<int> expected = {3, 2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 4: Left skewed tree
TEST_F(BinaryTreePostorderTraversalTest, LeftSkewed) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->left->left = new leetcode::utils::TreeNode(3);
    root->left->left->left = new leetcode::utils::TreeNode(4);
    
    std::vector<int> expected = {4, 3, 2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 5: Right skewed tree
TEST_F(BinaryTreePostorderTraversalTest, RightSkewed) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->right = new leetcode::utils::TreeNode(2);
    root->right->right = new leetcode::utils::TreeNode(3);
    root->right->right->right = new leetcode::utils::TreeNode(4);
    
    std::vector<int> expected = {4, 3, 2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 6: Complete binary tree
TEST_F(BinaryTreePostorderTraversalTest, CompleteBinaryTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(3);
    root->left->left = new leetcode::utils::TreeNode(4);
    root->left->right = new leetcode::utils::TreeNode(5);
    root->right->left = new leetcode::utils::TreeNode(6);
    root->right->right = new leetcode::utils::TreeNode(7);
    
    std::vector<int> expected = {4, 5, 2, 6, 7, 3, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 7: Only left children
TEST_F(BinaryTreePostorderTraversalTest, OnlyLeftChildren) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->left->left = new leetcode::utils::TreeNode(3);
    
    std::vector<int> expected = {3, 2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 8: Only right children
TEST_F(BinaryTreePostorderTraversalTest, OnlyRightChildren) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->right = new leetcode::utils::TreeNode(2);
    root->right->right = new leetcode::utils::TreeNode(3);
    
    std::vector<int> expected = {3, 2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 9: Mixed structure
TEST_F(BinaryTreePostorderTraversalTest, MixedStructure) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(3);
    root->left->right = new leetcode::utils::TreeNode(4);
    root->right->left = new leetcode::utils::TreeNode(5);
    
    std::vector<int> expected = {4, 2, 5, 3, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 10: Two nodes (parent-left child)
TEST_F(BinaryTreePostorderTraversalTest, TwoNodesLeft) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    
    std::vector<int> expected = {2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 11: Two nodes (parent-right child)
TEST_F(BinaryTreePostorderTraversalTest, TwoNodesRight) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->right = new leetcode::utils::TreeNode(2);
    
    std::vector<int> expected = {2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 12: Negative values
TEST_F(BinaryTreePostorderTraversalTest, NegativeValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(-1);
    root->left = new leetcode::utils::TreeNode(-2);
    root->right = new leetcode::utils::TreeNode(-3);
    root->left->left = new leetcode::utils::TreeNode(-4);
    
    std::vector<int> expected = {-4, -2, -3, -1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 13: Large tree (depth 5)
TEST_F(BinaryTreePostorderTraversalTest, LargeTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    
    // Level 2
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(3);
    
    // Level 3
    root->left->left = new leetcode::utils::TreeNode(4);
    root->left->right = new leetcode::utils::TreeNode(5);
    root->right->left = new leetcode::utils::TreeNode(6);
    root->right->right = new leetcode::utils::TreeNode(7);
    
    // Level 4
    root->left->left->left = new leetcode::utils::TreeNode(8);
    root->left->left->right = new leetcode::utils::TreeNode(9);
    root->left->right->left = new leetcode::utils::TreeNode(10);
    root->right->right->left = new leetcode::utils::TreeNode(11);
    root->right->right->right = new leetcode::utils::TreeNode(12);
    
    std::vector<int> expected = {8, 9, 4, 10, 5, 2, 6, 11, 12, 7, 3, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 14: Unbalanced tree
TEST_F(BinaryTreePostorderTraversalTest, UnbalancedTree) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->left->left = new leetcode::utils::TreeNode(3);
    root->left->left->left = new leetcode::utils::TreeNode(4);
    root->right = new leetcode::utils::TreeNode(5);
    
    std::vector<int> expected = {4, 3, 2, 5, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 15: All same values
TEST_F(BinaryTreePostorderTraversalTest, AllSameValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(5);
    root->left = new leetcode::utils::TreeNode(5);
    root->right = new leetcode::utils::TreeNode(5);
    root->left->left = new leetcode::utils::TreeNode(5);
    root->left->right = new leetcode::utils::TreeNode(5);
    
    std::vector<int> expected = {5, 5, 5, 5, 5};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 16: Maximum and minimum values
TEST_F(BinaryTreePostorderTraversalTest, ExtremValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(0);
    root->left = new leetcode::utils::TreeNode(-100);
    root->right = new leetcode::utils::TreeNode(100);
    root->left->left = new leetcode::utils::TreeNode(-99);
    root->right->right = new leetcode::utils::TreeNode(99);
    
    std::vector<int> expected = {-99, -100, 99, 100, 0};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 17: Sequential values
TEST_F(BinaryTreePostorderTraversalTest, SequentialValues) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(4);
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(6);
    root->left->left = new leetcode::utils::TreeNode(1);
    root->left->right = new leetcode::utils::TreeNode(3);
    root->right->left = new leetcode::utils::TreeNode(5);
    root->right->right = new leetcode::utils::TreeNode(7);
    
    std::vector<int> expected = {1, 3, 2, 5, 7, 6, 4};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 18: Tree with gaps
TEST_F(BinaryTreePostorderTraversalTest, TreeWithGaps) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->right = new leetcode::utils::TreeNode(3);
    root->left->right = new leetcode::utils::TreeNode(4);
    root->right->left = new leetcode::utils::TreeNode(5);
    // Note: missing left->left and right->right
    
    std::vector<int> expected = {4, 2, 5, 3, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 19: Deep left branch with right leaf
TEST_F(BinaryTreePostorderTraversalTest, DeepLeftBranchRightLeaf) {
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(1);
    root->left = new leetcode::utils::TreeNode(2);
    root->left->left = new leetcode::utils::TreeNode(3);
    root->left->left->left = new leetcode::utils::TreeNode(4);
    root->left->left->left->right = new leetcode::utils::TreeNode(5);
    
    std::vector<int> expected = {5, 4, 3, 2, 1};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

// Test Case 20: Performance test (medium size tree)
TEST_F(BinaryTreePostorderTraversalTest, PerformanceTest) {
    // Create a more balanced tree for performance testing
    leetcode::utils::TreeNode* root = new leetcode::utils::TreeNode(50);
    
    // Build a tree with multiple levels
    root->left = new leetcode::utils::TreeNode(30);
    root->right = new leetcode::utils::TreeNode(70);
    root->left->left = new leetcode::utils::TreeNode(20);
    root->left->right = new leetcode::utils::TreeNode(40);
    root->right->left = new leetcode::utils::TreeNode(60);
    root->right->right = new leetcode::utils::TreeNode(80);
    
    // Add more nodes for performance testing
    root->left->left->left = new leetcode::utils::TreeNode(10);
    root->left->left->right = new leetcode::utils::TreeNode(25);
    root->left->right->left = new leetcode::utils::TreeNode(35);
    root->left->right->right = new leetcode::utils::TreeNode(45);
    
    std::vector<int> expected = {10, 25, 20, 35, 45, 40, 30, 60, 80, 70, 50};
    testAllApproaches(root, expected);
    
    deleteTree(root);
}

