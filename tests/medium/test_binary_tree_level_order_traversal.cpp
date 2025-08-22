#include <gtest/gtest.h>
#include "medium/binary_tree_level_order_traversal.h"
#include "utils/data_structures.h"
#include <vector>
#include <queue>

using namespace leetcode::utils;

namespace leetcode {
namespace medium {
namespace test {

class BinaryTreeLevelOrderTraversalTest : public ::testing::Test {
protected:
    BinaryTreeLevelOrderTraversal solution;
    
    void testAllApproaches(TreeNode* root, const std::vector<std::vector<int>>& expected) {
        EXPECT_EQ(solution.levelOrder(root), expected) 
            << "Standard BFS approach failed";
        EXPECT_EQ(solution.levelOrderDFS(root), expected) 
            << "DFS with Level Parameter approach failed";
        EXPECT_EQ(solution.levelOrderTwoQueues(root), expected) 
            << "Two-Queue approach failed";
        EXPECT_EQ(solution.levelOrderHashMap(root), expected) 
            << "HashMap approach failed";
        EXPECT_EQ(solution.levelOrderIterativeDFS(root), expected) 
            << "Iterative DFS approach failed";
        EXPECT_EQ(solution.levelOrderNullMarkers(root), expected) 
            << "Null Markers approach failed";
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
TEST_F(BinaryTreeLevelOrderTraversalTest, EmptyTree) {
    testAllApproaches(nullptr, {});
}

TEST_F(BinaryTreeLevelOrderTraversalTest, SingleNode) {
    TreeNode* root = new TreeNode(1);
    testAllApproaches(root, {{1}});
}

TEST_F(BinaryTreeLevelOrderTraversalTest, LeetCodeExample1) {
    // Example 1: [3,9,20,null,null,15,7]
    // Output: [[3],[9,20],[15,7]]
    TreeNode* root = createTree({val(3), val(9), val(20), null(), null(), val(15), val(7)});
    std::vector<std::vector<int>> expected = {{3}, {9, 20}, {15, 7}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, LeetCodeExample2) {
    // Example 2: [1]
    // Output: [[1]]
    TreeNode* root = new TreeNode(1);
    testAllApproaches(root, {{1}});
}

// Tree structure variations
TEST_F(BinaryTreeLevelOrderTraversalTest, TwoNodes) {
    // Left child only
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    testAllApproaches(root, {{1}, {2}});
    
    // Right child only
    root = new TreeNode(1);
    root->right = new TreeNode(3);
    testAllApproaches(root, {{1}, {3}});
}

TEST_F(BinaryTreeLevelOrderTraversalTest, LeftSkewed) {
    // Left-skewed tree: 1->2->3->4
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    
    std::vector<std::vector<int>> expected = {{1}, {2}, {3}, {4}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, RightSkewed) {
    // Right-skewed tree: 1->2->3->4
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    
    std::vector<std::vector<int>> expected = {{1}, {2}, {3}, {4}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, CompleteBinaryTree) {
    // Complete binary tree: [1,2,3,4,5,6,7]
    TreeNode* root = createTree({val(1), val(2), val(3), val(4), val(5), val(6), val(7)});
    std::vector<std::vector<int>> expected = {{1}, {2, 3}, {4, 5, 6, 7}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, PerfectBinaryTree) {
    // Perfect binary tree height 3: [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
    TreeNode* root = new TreeNode(1);
    
    // Level 1
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    // Level 2
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    // Level 3
    root->left->left->left = new TreeNode(8);
    root->left->left->right = new TreeNode(9);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(11);
    root->right->left->left = new TreeNode(12);
    root->right->left->right = new TreeNode(13);
    root->right->right->left = new TreeNode(14);
    root->right->right->right = new TreeNode(15);
    
    std::vector<std::vector<int>> expected = {
        {1}, 
        {2, 3}, 
        {4, 5, 6, 7}, 
        {8, 9, 10, 11, 12, 13, 14, 15}
    };
    testAllApproaches(root, expected);
}

// Incomplete trees
TEST_F(BinaryTreeLevelOrderTraversalTest, IncompleteTree1) {
    // [1,2,3,4,null,null,7]
    TreeNode* root = createTree({val(1), val(2), val(3), val(4), null(), null(), val(7)});
    std::vector<std::vector<int>> expected = {{1}, {2, 3}, {4, 7}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, IncompleteTree2) {
    // [1,2,3,null,5,6,null]
    TreeNode* root = createTree({val(1), val(2), val(3), null(), val(5), val(6), null()});
    std::vector<std::vector<int>> expected = {{1}, {2, 3}, {5, 6}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, SparseTree) {
    // Tree with many missing nodes
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->left->right->left = new TreeNode(9);
    root->right->left->right = new TreeNode(10);
    
    std::vector<std::vector<int>> expected = {{1}, {2, 3}, {5, 6}, {9, 10}};
    testAllApproaches(root, expected);
}

// Value variation tests
TEST_F(BinaryTreeLevelOrderTraversalTest, NegativeValues) {
    // Tree with negative values
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(-5);
    root->right = new TreeNode(-15);
    root->left->left = new TreeNode(-3);
    root->left->right = new TreeNode(-7);
    root->right->right = new TreeNode(-18);
    
    std::vector<std::vector<int>> expected = {{-10}, {-5, -15}, {-3, -7, -18}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, MixedValues) {
    // Tree with mixed positive/negative/zero values
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(-1);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(-100);
    root->left->right = new TreeNode(100);
    root->right->left = new TreeNode(-999);
    root->right->right = new TreeNode(999);
    
    std::vector<std::vector<int>> expected = {{0}, {-1, 1}, {-100, 100, -999, 999}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, DuplicateValues) {
    // Tree with duplicate values
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(1);
    
    std::vector<std::vector<int>> expected = {{1}, {1, 1}, {1, 2, 2, 1}};
    testAllApproaches(root, expected);
}

// Extreme values
TEST_F(BinaryTreeLevelOrderTraversalTest, ExtremeValues) {
    // Tree with constraint boundary values
    TreeNode* root = new TreeNode(1000);
    root->left = new TreeNode(-1000);
    root->right = new TreeNode(0);
    
    std::vector<std::vector<int>> expected = {{1000}, {-1000, 0}};
    testAllApproaches(root, expected);
}

// Large tree tests
TEST_F(BinaryTreeLevelOrderTraversalTest, DeepTree) {
    // Create a deep tree (height 10)
    TreeNode* root = new TreeNode(0);
    TreeNode* current = root;
    
    std::vector<std::vector<int>> expected;
    for (int level = 0; level < 10; ++level) {
        expected.push_back({level});
        if (level < 9) {
            current->left = new TreeNode(level + 1);
            current = current->left;
        }
    }
    
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, WideTree) {
    // Create a wide tree (all nodes at level 1)
    TreeNode* root = new TreeNode(0);
    std::vector<int> level1;
    
    // Create a binary tree where root has many "grandchildren"
    root->left = new TreeNode(1);
    root->right = new TreeNode(2);
    
    // Level 2 - create wide level
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    
    std::vector<std::vector<int>> expected = {{0}, {1, 2}, {3, 4, 5, 6}};
    testAllApproaches(root, expected);
}

// Edge cases and special patterns
TEST_F(BinaryTreeLevelOrderTraversalTest, ZigzagStructure) {
    // Tree that goes left-right-left-right
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(4);
    root->left->right->left->right = new TreeNode(5);
    
    std::vector<std::vector<int>> expected = {{1}, {2}, {3}, {4}, {5}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, AlternatingMissing) {
    // Tree where alternate nodes are missing at each level
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    // Skip level 2 left positions
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    // Skip level 3 alternating
    root->left->right->left = new TreeNode(10);
    root->right->left->right = new TreeNode(11);
    
    std::vector<std::vector<int>> expected = {{1}, {2, 3}, {5, 6}, {10, 11}};
    testAllApproaches(root, expected);
}

// Algorithm-specific edge cases
TEST_F(BinaryTreeLevelOrderTraversalTest, SinglePath) {
    // Tree that forms a single path (tests DFS approaches)
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(4);
    
    std::vector<std::vector<int>> expected = {{1}, {2}, {3}, {4}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, OnlyLeftChildren) {
    // Tree with only left children
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(2);
    root->left->left->left->left = new TreeNode(1);
    
    std::vector<std::vector<int>> expected = {{5}, {4}, {3}, {2}, {1}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, OnlyRightChildren) {
    // Tree with only right children
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    root->right->right->right->right = new TreeNode(5);
    
    std::vector<std::vector<int>> expected = {{1}, {2}, {3}, {4}, {5}};
    testAllApproaches(root, expected);
}

// Stress test
TEST_F(BinaryTreeLevelOrderTraversalTest, BalancedMediumTree) {
    // Balanced tree with height 4
    TreeNode* root = new TreeNode(1);
    
    // Level 1
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    // Level 2
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    // Level 3 (partial)
    root->left->left->left = new TreeNode(8);
    root->left->left->right = new TreeNode(9);
    root->left->right->left = new TreeNode(10);
    root->right->left->right = new TreeNode(11);
    root->right->right->left = new TreeNode(12);
    
    std::vector<std::vector<int>> expected = {
        {1}, 
        {2, 3}, 
        {4, 5, 6, 7}, 
        {8, 9, 10, 11, 12}
    };
    testAllApproaches(root, expected);
}

// Numeric sequence tests
TEST_F(BinaryTreeLevelOrderTraversalTest, IncreasingValues) {
    // Tree with increasing values level by level
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    std::vector<std::vector<int>> expected = {{1}, {2, 3}, {4, 5, 6, 7}};
    testAllApproaches(root, expected);
}

TEST_F(BinaryTreeLevelOrderTraversalTest, DecreasingValues) {
    // Tree with decreasing values
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(6);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(1);
    
    std::vector<std::vector<int>> expected = {{7}, {6, 5}, {4, 3, 2, 1}};
    testAllApproaches(root, expected);
}

}
}
}