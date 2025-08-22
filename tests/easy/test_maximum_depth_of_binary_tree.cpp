#include <gtest/gtest.h>
#include "easy/maximum_depth_of_binary_tree.h"
#include "utils/data_structures.h"

using namespace leetcode::easy;
using namespace leetcode::utils;

class MaxDepthTest : public ::testing::Test {
protected:
    void verifyAll(TreeNode* root, int expected) {
        MaxDepthRecursive a1; MaxDepthTopDown a2; MaxDepthIterativeDFS a3;
        MaxDepthBFSQueue a4; MaxDepthBFSSentinel a5; MaxDepthLevelCount a6;
        EXPECT_EQ(a1.maxDepth(root), expected);
        EXPECT_EQ(a2.maxDepth(root), expected);
        EXPECT_EQ(a3.maxDepth(root), expected);
        EXPECT_EQ(a4.maxDepth(root), expected);
        EXPECT_EQ(a5.maxDepth(root), expected);
        EXPECT_EQ(a6.maxDepth(root), expected);
    }
};

TEST_F(MaxDepthTest, EmptyTree) {
    verifyAll(nullptr, 0);
}

TEST_F(MaxDepthTest, SingleNode) {
    TreeNode* root = new TreeNode(1);
    verifyAll(root, 1);
    deleteTree(root);
}

TEST_F(MaxDepthTest, BalancedTree) {
    TreeNode* root = buildTree({3,9,20,std::nullopt,std::nullopt,15,7});
    verifyAll(root, 3);
    deleteTree(root);
}

TEST_F(MaxDepthTest, LeftSkewed) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    verifyAll(root, 4);
    deleteTree(root);
}

TEST_F(MaxDepthTest, RightSkewed) {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    verifyAll(root, 3);
    deleteTree(root);
}

