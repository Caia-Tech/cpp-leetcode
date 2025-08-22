#include <gtest/gtest.h>
#include "easy/binary_tree_inorder_traversal.h"
#include <chrono>
#include <queue>

using namespace leetcode::easy;

class BinaryTreeInorderTraversalTest : public ::testing::Test {
protected:
    BinaryTreeInorderTraversal solution;
    
    // Helper function to create a tree node
    TreeNode* createNode(int val) {
        return new TreeNode(val);
    }
    
    // Helper function to create a tree from values (level order, -1 for null)
    TreeNode* createTree(const std::vector<int>& values) {
        if (values.empty() || values[0] == -1) return nullptr;
        
        TreeNode* root = new TreeNode(values[0]);
        std::queue<TreeNode*> queue;
        queue.push(root);
        
        int i = 1;
        while (!queue.empty() && i < values.size()) {
            TreeNode* node = queue.front();
            queue.pop();
            
            // Left child
            if (i < values.size() && values[i] != -1) {
                node->left = new TreeNode(values[i]);
                queue.push(node->left);
            }
            i++;
            
            // Right child
            if (i < values.size() && values[i] != -1) {
                node->right = new TreeNode(values[i]);
                queue.push(node->right);
            }
            i++;
        }
        
        return root;
    }
    
    // Helper function to delete tree
    void deleteTree(TreeNode* root) {
        if (root == nullptr) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
    
    // Helper function to test all approaches
    void testAllApproaches(TreeNode* root, const std::vector<int>& expected) {
        auto result1 = solution.inorderTraversalRecursive(root);
        auto result2 = solution.inorderTraversalIterative(root);
        auto result3 = solution.inorderTraversalMorris(root);
        auto result4 = solution.inorderTraversalStateMachine(root);
        auto result5 = solution.inorderTraversalReverse(root);
        auto result6 = solution.inorderTraversalParentTracking(root);
        
        EXPECT_EQ(result1, expected) << "Recursive approach failed";
        EXPECT_EQ(result2, expected) << "Iterative approach failed";
        EXPECT_EQ(result3, expected) << "Morris approach failed";
        EXPECT_EQ(result4, expected) << "State machine approach failed";
        EXPECT_EQ(result5, expected) << "Reverse approach failed";
        EXPECT_EQ(result6, expected) << "Parent tracking approach failed";
    }
    
    void TearDown() override {
        // Clean up any trees created during tests
        // Note: In a real implementation, we'd track created trees and clean them up
    }
};

TEST_F(BinaryTreeInorderTraversalTest, BasicExample1) {
    // Input: root = [1,null,2,3]
    //   1
    //    \
    //     2
    //    /
    //   3
    // Output: [1,3,2]
    TreeNode* root = createTree({1, -1, 2, 3});
    testAllApproaches(root, {1, 3, 2});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, BasicExample2) {
    // Input: root = []
    // Output: []
    TreeNode* root = nullptr;
    testAllApproaches(root, {});
}

TEST_F(BinaryTreeInorderTraversalTest, BasicExample3) {
    // Input: root = [1]
    // Output: [1]
    TreeNode* root = createTree({1});
    testAllApproaches(root, {1});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, SimpleTree) {
    // Input: root = [1,2,3]
    //     1
    //    / \
    //   2   3
    // Output: [2,1,3]
    TreeNode* root = createTree({1, 2, 3});
    testAllApproaches(root, {2, 1, 3});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, LeftSkewedTree) {
    // Input: root = [4,2,null,1,3]
    //     4
    //    /
    //   2
    //  / \
    // 1   3
    // Output: [1,2,3,4]
    TreeNode* root = createTree({4, 2, -1, 1, 3});
    testAllApproaches(root, {1, 2, 3, 4});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, RightSkewedTree) {
    // Input: root = [1,null,2,null,3,null,4]
    //   1
    //    \
    //     2
    //      \
    //       3
    //        \
    //         4
    // Output: [1,2,3,4]
    TreeNode* root = createNode(1);
    root->right = createNode(2);
    root->right->right = createNode(3);
    root->right->right->right = createNode(4);
    
    testAllApproaches(root, {1, 2, 3, 4});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, LeftOnlyTree) {
    // Input: root = [4,3,null,2,null,1]
    //     4
    //    /
    //   3
    //  /
    // 2
    ///
    //1
    // Output: [1,2,3,4]
    TreeNode* root = createNode(4);
    root->left = createNode(3);
    root->left->left = createNode(2);
    root->left->left->left = createNode(1);
    
    testAllApproaches(root, {1, 2, 3, 4});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, CompleteBinaryTree) {
    // Input: root = [4,2,6,1,3,5,7]
    //       4
    //      / \
    //     2   6
    //    / \ / \
    //   1 3 5  7
    // Output: [1,2,3,4,5,6,7]
    TreeNode* root = createTree({4, 2, 6, 1, 3, 5, 7});
    testAllApproaches(root, {1, 2, 3, 4, 5, 6, 7});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, NegativeValues) {
    // Input: root = [0,-3,9,-10,null,5]
    //      0
    //     / \
    //   -3   9
    //   /   /
    // -10  5
    // Output: [-10,-3,0,5,9]
    TreeNode* root = createTree({0, -3, 9, -10, -1, 5});
    testAllApproaches(root, {-10, -3, 0, 5, 9});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, SingleLeftChild) {
    // Input: root = [1,2]
    //   1
    //  /
    // 2
    // Output: [2,1]
    TreeNode* root = createTree({1, 2});
    testAllApproaches(root, {2, 1});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, SingleRightChild) {
    // Input: root = [1,null,2]
    //   1
    //    \
    //     2
    // Output: [1,2]
    TreeNode* root = createTree({1, -1, 2});
    testAllApproaches(root, {1, 2});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, LargerTree) {
    // Input: root = [5,3,8,2,4,7,9,1]
    //         5
    //       /   \
    //      3     8
    //     / \   / \
    //    2   4 7   9
    //   /
    //  1
    // Output: [1,2,3,4,5,7,8,9]
    TreeNode* root = createTree({5, 3, 8, 2, 4, 7, 9, 1});
    testAllApproaches(root, {1, 2, 3, 4, 5, 7, 8, 9});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, DuplicateValues) {
    // Input: root = [2,2,2]
    //   2
    //  / \
    // 2   2
    // Output: [2,2,2]
    TreeNode* root = createTree({2, 2, 2});
    testAllApproaches(root, {2, 2, 2});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, MaxConstraintValues) {
    // Input: tree with constraint boundary values (-100 to 100)
    TreeNode* root = createTree({0, -100, 100});
    testAllApproaches(root, {-100, 0, 100});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, UnbalancedTree) {
    // Create an unbalanced tree
    //       1
    //      /
    //     2
    //    /
    //   3
    //  /
    // 4
    //  \
    //   5
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->left->left = createNode(3);
    root->left->left->left = createNode(4);
    root->left->left->left->right = createNode(5);
    
    testAllApproaches(root, {4, 5, 3, 2, 1});
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, MaxTreeSize) {
    // Test with maximum constraint (100 nodes)
    TreeNode* root = createNode(50);
    TreeNode* current = root;
    
    // Create left subtree
    for (int i = 49; i >= 1; --i) {
        current->left = createNode(i);
        current = current->left;
    }
    
    // Create right subtree
    current = root;
    for (int i = 51; i <= 100; ++i) {
        current->right = createNode(i);
        current = current->right;
    }
    
    // Expected: [1,2,3,...,100]
    std::vector<int> expected;
    for (int i = 1; i <= 100; ++i) {
        expected.push_back(i);
    }
    
    testAllApproaches(root, expected);
    deleteTree(root);
}

// Performance tests
TEST_F(BinaryTreeInorderTraversalTest, PerformanceComparison) {
    // Create a reasonably large balanced tree
    TreeNode* root = createTree({50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93});
    
    // Test recursive approach
    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = solution.inorderTraversalRecursive(root);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test iterative approach
    start = std::chrono::high_resolution_clock::now();
    auto result2 = solution.inorderTraversalIterative(root);
    end = std::chrono::high_resolution_clock::now();
    
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test Morris approach
    start = std::chrono::high_resolution_clock::now();
    auto result3 = solution.inorderTraversalMorris(root);
    end = std::chrono::high_resolution_clock::now();
    
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // All results should be the same
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, result3);
    
    // All should complete quickly
    EXPECT_LT(duration1.count(), 1000) << "Recursive should be fast";
    EXPECT_LT(duration2.count(), 1000) << "Iterative should be fast";
    EXPECT_LT(duration3.count(), 2000) << "Morris should be reasonably fast";
    
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, DeepTree) {
    // Test with deep tree (within reasonable limits)
    TreeNode* root = createNode(1);
    TreeNode* current = root;
    
    for (int i = 2; i <= 50; ++i) {
        current->left = createNode(i);
        current = current->left;
    }
    
    std::vector<int> expected;
    for (int i = 50; i >= 1; --i) {
        expected.push_back(i);
    }
    
    testAllApproaches(root, expected);
    deleteTree(root);
}

// Algorithm-specific tests
TEST_F(BinaryTreeInorderTraversalTest, MorrisSpecificTest) {
    // Morris traversal should not permanently modify the tree
    TreeNode* root = createTree({1, 2, 3});
    
    // Get original structure
    EXPECT_EQ(root->val, 1);
    EXPECT_EQ(root->left->val, 2);
    EXPECT_EQ(root->right->val, 3);
    
    // Run Morris traversal
    auto result = solution.inorderTraversalMorris(root);
    
    // Tree should be restored
    EXPECT_EQ(root->val, 1);
    EXPECT_EQ(root->left->val, 2);
    EXPECT_EQ(root->right->val, 3);
    EXPECT_EQ(root->left->right, nullptr); // Should be restored
    
    EXPECT_EQ(result, std::vector<int>({2, 1, 3}));
    deleteTree(root);
}

TEST_F(BinaryTreeInorderTraversalTest, StateMachineSpecificTest) {
    // Test state machine with complex tree
    TreeNode* root = createTree({4, 2, 6, 1, 3, 5, 7});
    auto result = solution.inorderTraversalStateMachine(root);
    EXPECT_EQ(result, std::vector<int>({1, 2, 3, 4, 5, 6, 7}));
    deleteTree(root);
}

// Edge cases
TEST_F(BinaryTreeInorderTraversalTest, EdgeCases) {
    // Test empty tree
    testAllApproaches(nullptr, {});
    
    // Test single node with negative value
    TreeNode* singleNegative = createNode(-50);
    testAllApproaches(singleNegative, {-50});
    deleteTree(singleNegative);
    
    // Test single node with zero
    TreeNode* singleZero = createNode(0);
    testAllApproaches(singleZero, {0});
    deleteTree(singleZero);
}

TEST_F(BinaryTreeInorderTraversalTest, ConsistencyCheck) {
    // Test multiple tree structures for consistency
    std::vector<std::vector<int>> treeStructures = {
        {1},
        {1, 2},
        {1, -1, 2},
        {1, 2, 3},
        {2, 1, 3},
        {3, 2, 4, 1},
        {4, 2, 6, 1, 3, 5, 7}
    };
    
    for (const auto& structure : treeStructures) {
        TreeNode* root = createTree(structure);
        
        // Get expected result from recursive approach (as ground truth)
        auto expected = solution.inorderTraversalRecursive(root);
        
        // Test all other approaches against it
        testAllApproaches(root, expected);
        
        deleteTree(root);
    }
}

TEST_F(BinaryTreeInorderTraversalTest, TreeModificationVerification) {
    // Verify that iterative and Morris approaches don't permanently modify tree
    TreeNode* root = createTree({1, 2, 3, 4, 5, 6, 7});
    
    // Store original structure
    EXPECT_TRUE(root->left != nullptr);
    EXPECT_TRUE(root->right != nullptr);
    EXPECT_EQ(root->left->val, 2);
    EXPECT_EQ(root->right->val, 3);
    
    // Run all approaches
    solution.inorderTraversalRecursive(root);
    solution.inorderTraversalIterative(root);
    solution.inorderTraversalMorris(root);
    solution.inorderTraversalStateMachine(root);
    
    // Tree should be unchanged
    EXPECT_TRUE(root->left != nullptr);
    EXPECT_TRUE(root->right != nullptr);
    EXPECT_EQ(root->left->val, 2);
    EXPECT_EQ(root->right->val, 3);
    
    deleteTree(root);
}