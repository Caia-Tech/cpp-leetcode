#include <gtest/gtest.h>
#include "../../src/easy/maximum_depth_binary_tree.h"
#include "../../src/utils/test_utils.h"
#include <vector>
#include <queue>

namespace leetcode {
namespace easy {
namespace test {

using utils::TreeNode;

class MaximumDepthBinaryTreeTest : public ::testing::Test {
protected:
    // Helper to create tree from vector (level order, null represented by nullptr)
    TreeNode* createTree(const std::vector<int*>& values) {
        if (values.empty() || !values[0]) return nullptr;
        
        TreeNode* root = new TreeNode(*values[0]);
        std::queue<TreeNode*> queue;
        queue.push(root);
        
        size_t i = 1;
        while (!queue.empty() && i < values.size()) {
            TreeNode* current = queue.front();
            queue.pop();
            
            // Left child
            if (i < values.size() && values[i]) {
                current->left = new TreeNode(*values[i]);
                queue.push(current->left);
            }
            i++;
            
            // Right child
            if (i < values.size() && values[i]) {
                current->right = new TreeNode(*values[i]);
                queue.push(current->right);
            }
            i++;
        }
        
        return root;
    }
    
    // Helper to delete tree
    void deleteTree(TreeNode* root) {
        if (!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
    
    // Test all approaches
    void testAllApproaches(TreeNode* root, int expected) {
        MaximumDepthBinaryTree solution;
        
        EXPECT_EQ(solution.maxDepthRecursive(root), expected) 
            << "Recursive approach failed";
        EXPECT_EQ(solution.maxDepthBFS(root), expected) 
            << "BFS approach failed";
        EXPECT_EQ(solution.maxDepthDFS(root), expected) 
            << "DFS iterative approach failed";
        EXPECT_EQ(solution.maxDepthMorris(root), expected) 
            << "Morris traversal approach failed";
        EXPECT_EQ(solution.maxDepthTwoStack(root), expected) 
            << "Two-stack approach failed";
        EXPECT_EQ(solution.maxDepthLevelBFS(root), expected) 
            << "Level BFS approach failed";
    }
    
    // Helper to create a perfect binary tree of given depth
    TreeNode* createPerfectTree(int depth) {
        if (depth == 0) return nullptr;
        
        TreeNode* root = new TreeNode(1);
        std::queue<TreeNode*> queue;
        queue.push(root);
        
        int currentLevel = 1;
        int nodeValue = 2;
        
        while (currentLevel < depth) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = queue.front();
                queue.pop();
                
                node->left = new TreeNode(nodeValue++);
                node->right = new TreeNode(nodeValue++);
                
                queue.push(node->left);
                queue.push(node->right);
            }
            currentLevel++;
        }
        
        return root;
    }
    
    // Helper to create a left-skewed tree
    TreeNode* createLeftSkewedTree(int depth) {
        if (depth == 0) return nullptr;
        
        TreeNode* root = new TreeNode(1);
        TreeNode* current = root;
        
        for (int i = 2; i <= depth; ++i) {
            current->left = new TreeNode(i);
            current = current->left;
        }
        
        return root;
    }
    
    // Helper to create a right-skewed tree
    TreeNode* createRightSkewedTree(int depth) {
        if (depth == 0) return nullptr;
        
        TreeNode* root = new TreeNode(1);
        TreeNode* current = root;
        
        for (int i = 2; i <= depth; ++i) {
            current->right = new TreeNode(i);
            current = current->right;
        }
        
        return root;
    }
};

// LeetCode Example Test Cases

TEST_F(MaximumDepthBinaryTreeTest, LeetCodeExample1) {
    // root = [3,9,20,null,null,15,7]
    // Output: 3
    int v3 = 3, v9 = 9, v20 = 20, v15 = 15, v7 = 7;
    TreeNode* root = createTree({&v3, &v9, &v20, nullptr, nullptr, &v15, &v7});
    testAllApproaches(root, 3);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, LeetCodeExample2) {
    // root = [1,null,2]
    // Output: 2
    int v1 = 1, v2 = 2;
    TreeNode* root = createTree({&v1, nullptr, &v2});
    testAllApproaches(root, 2);
    deleteTree(root);
}

// Edge Cases

TEST_F(MaximumDepthBinaryTreeTest, EmptyTree) {
    testAllApproaches(nullptr, 0);
}

TEST_F(MaximumDepthBinaryTreeTest, SingleNode) {
    TreeNode* root = new TreeNode(42);
    testAllApproaches(root, 1);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, TwoNodesLeft) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, TwoNodesRight) {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, ThreeNodesPerfect) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    testAllApproaches(root, 2);
    deleteTree(root);
}

// Skewed Trees

TEST_F(MaximumDepthBinaryTreeTest, LeftSkewedSmall) {
    TreeNode* root = createLeftSkewedTree(5);
    testAllApproaches(root, 5);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, RightSkewedSmall) {
    TreeNode* root = createRightSkewedTree(5);
    testAllApproaches(root, 5);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, LeftSkewedMedium) {
    TreeNode* root = createLeftSkewedTree(10);
    testAllApproaches(root, 10);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, RightSkewedMedium) {
    TreeNode* root = createRightSkewedTree(10);
    testAllApproaches(root, 10);
    deleteTree(root);
}

// Perfect Trees

TEST_F(MaximumDepthBinaryTreeTest, PerfectTreeDepth3) {
    TreeNode* root = createPerfectTree(3);
    testAllApproaches(root, 3);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, PerfectTreeDepth4) {
    TreeNode* root = createPerfectTree(4);
    testAllApproaches(root, 4);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, PerfectTreeDepth5) {
    TreeNode* root = createPerfectTree(5);
    testAllApproaches(root, 5);
    deleteTree(root);
}

// Unbalanced Trees

TEST_F(MaximumDepthBinaryTreeTest, UnbalancedLeft) {
    // Tree structure:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    //  /
    // 6
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->left->left = new TreeNode(6);
    
    testAllApproaches(root, 4);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, UnbalancedRight) {
    // Tree structure:
    //   1
    //  / \
    // 2   3
    //    / \
    //   4   5
    //        \
    //         6
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->right->right->right = new TreeNode(6);
    
    testAllApproaches(root, 4);
    deleteTree(root);
}

// Special Value Tests

TEST_F(MaximumDepthBinaryTreeTest, NegativeValues) {
    TreeNode* root = new TreeNode(-1);
    root->left = new TreeNode(-100);
    root->right = new TreeNode(-50);
    root->left->left = new TreeNode(-75);
    
    testAllApproaches(root, 3);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, MixedValues) {
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(-10);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(-100);
    root->right->right = new TreeNode(100);
    
    testAllApproaches(root, 3);
    deleteTree(root);
}

// Complex Patterns

TEST_F(MaximumDepthBinaryTreeTest, ZigZagPattern) {
    // Tree with alternating left-right pattern
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(4);
    root->left->right->left->right = new TreeNode(5);
    
    testAllApproaches(root, 5);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, SpiralPattern) {
    // More complex pattern
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->left->left->left = new TreeNode(6);
    root->right->right->right = new TreeNode(7);
    
    testAllApproaches(root, 4);
    deleteTree(root);
}

// Large Trees

TEST_F(MaximumDepthBinaryTreeTest, LargeLeftSkewed) {
    TreeNode* root = createLeftSkewedTree(100);
    
    MaximumDepthBinaryTree solution;
    // Test non-recursive approaches for deep trees
    EXPECT_EQ(solution.maxDepthBFS(root), 100);
    EXPECT_EQ(solution.maxDepthDFS(root), 100);
    EXPECT_EQ(solution.maxDepthTwoStack(root), 100);
    
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, LargeRightSkewed) {
    TreeNode* root = createRightSkewedTree(100);
    
    MaximumDepthBinaryTree solution;
    // Test non-recursive approaches for deep trees
    EXPECT_EQ(solution.maxDepthBFS(root), 100);
    EXPECT_EQ(solution.maxDepthDFS(root), 100);
    EXPECT_EQ(solution.maxDepthTwoStack(root), 100);
    
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, LargePerfectTree) {
    TreeNode* root = createPerfectTree(10);  // 2^10 - 1 = 1023 nodes
    testAllApproaches(root, 10);
    deleteTree(root);
}

// Boundary Tests

TEST_F(MaximumDepthBinaryTreeTest, MaxConstraintNodes) {
    // Test with large number of nodes (but reasonable depth)
    TreeNode* root = createPerfectTree(13);  // 2^13 - 1 = 8191 nodes
    
    MaximumDepthBinaryTree solution;
    EXPECT_EQ(solution.maxDepthBFS(root), 13);
    EXPECT_EQ(solution.maxDepthDFS(root), 13);
    
    deleteTree(root);
}

// Special Tree Structures

TEST_F(MaximumDepthBinaryTreeTest, CompleteBinaryTree) {
    // Complete but not perfect binary tree
    int vals[] = {1, 2, 3, 4, 5, 6};
    std::vector<int*> values;
    for (int& val : vals) {
        values.push_back(&val);
    }
    
    TreeNode* root = createTree(values);
    testAllApproaches(root, 3);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, AlmostCompleteBinaryTree) {
    // Almost complete binary tree (missing rightmost leaf)
    int vals[] = {1, 2, 3, 4, 5};
    std::vector<int*> values;
    for (int& val : vals) {
        values.push_back(&val);
    }
    
    TreeNode* root = createTree(values);
    testAllApproaches(root, 3);
    deleteTree(root);
}

TEST_F(MaximumDepthBinaryTreeTest, FullButNotComplete) {
    // Full binary tree that's not complete
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->left->left->left = new TreeNode(8);
    root->left->left->right = new TreeNode(9);
    
    testAllApproaches(root, 4);
    deleteTree(root);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode