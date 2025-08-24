#include <gtest/gtest.h>
#include "../../src/easy/minimum_depth_binary_tree.h"
#include "../../src/utils/test_utils.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

using utils::TreeNode;

class MinimumDepthBinaryTreeTest : public ::testing::Test {
protected:
    // Helper to create tree from vector (level order)
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
        MinimumDepthBinaryTree solution;
        
        EXPECT_EQ(solution.minDepthRecursive(root), expected) 
            << "Recursive approach failed";
        EXPECT_EQ(solution.minDepthBFS(root), expected) 
            << "BFS approach failed";
        EXPECT_EQ(solution.minDepthDFS(root), expected) 
            << "DFS iterative approach failed";
        EXPECT_EQ(solution.minDepthMorris(root), expected) 
            << "Morris traversal approach failed";
        EXPECT_EQ(solution.minDepthLevelOrder(root), expected) 
            << "Level order approach failed";
        EXPECT_EQ(solution.minDepthFunctional(root), expected) 
            << "Functional approach failed";
    }
};

// LeetCode Example Test Cases

TEST_F(MinimumDepthBinaryTreeTest, LeetCodeExample1) {
    // root = [3,9,20,null,null,15,7]
    // Output: 2 (path 3->9)
    int v3 = 3, v9 = 9, v20 = 20, v15 = 15, v7 = 7;
    TreeNode* root = createTree({&v3, &v9, &v20, nullptr, nullptr, &v15, &v7});
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, LeetCodeExample2) {
    // root = [2,null,3,null,4,null,5,null,6]
    // Output: 5 (only one path: 2->3->4->5->6)
    int v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6;
    TreeNode* root = createTree({&v2, nullptr, &v3, nullptr, &v4, nullptr, &v5, nullptr, &v6});
    testAllApproaches(root, 5);
    deleteTree(root);
}

// Edge Cases

TEST_F(MinimumDepthBinaryTreeTest, EmptyTree) {
    testAllApproaches(nullptr, 0);
}

TEST_F(MinimumDepthBinaryTreeTest, SingleNode) {
    TreeNode* root = new TreeNode(1);
    testAllApproaches(root, 1);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, TwoNodesLeft) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, TwoNodesRight) {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, TwoNodesBoth) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    testAllApproaches(root, 2);
    deleteTree(root);
}

// Balanced Trees

TEST_F(MinimumDepthBinaryTreeTest, PerfectBinaryTree) {
    // Perfect binary tree of depth 3
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7;
    TreeNode* root = createTree({&v1, &v2, &v3, &v4, &v5, &v6, &v7});
    testAllApproaches(root, 3);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, CompleteBinaryTree) {
    // Complete binary tree with missing right leaf
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6;
    TreeNode* root = createTree({&v1, &v2, &v3, &v4, &v5, &v6});
    testAllApproaches(root, 3);
    deleteTree(root);
}

// Unbalanced Trees

TEST_F(MinimumDepthBinaryTreeTest, LeftSkewedTree) {
    TreeNode* root = new TreeNode(1);
    TreeNode* current = root;
    
    // Create left-skewed tree: 1->2->3->4->5
    for (int i = 2; i <= 5; ++i) {
        current->left = new TreeNode(i);
        current = current->left;
    }
    
    testAllApproaches(root, 5);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, RightSkewedTree) {
    TreeNode* root = new TreeNode(1);
    TreeNode* current = root;
    
    // Create right-skewed tree: 1->2->3->4->5
    for (int i = 2; i <= 5; ++i) {
        current->right = new TreeNode(i);
        current = current->right;
    }
    
    testAllApproaches(root, 5);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, UnbalancedWithEarlyLeaf) {
    // Tree where left side has early leaf, right side is deep
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(4);
    root->right->right->right = new TreeNode(5);
    
    testAllApproaches(root, 2); // Left leaf at depth 2
    deleteTree(root);
}

// Complex Structure Tests

TEST_F(MinimumDepthBinaryTreeTest, MultipleMinDepthPaths) {
    // Tree with multiple paths at minimum depth
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    TreeNode* root = createTree({&v1, &v2, &v3, &v4, &v5});
    testAllApproaches(root, 2); // Right leaf at depth 2
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, DeepTreeWithShallowBranch) {
    TreeNode* root = new TreeNode(1);
    
    // Left side: shallow
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    
    // Right side: deep
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->right->left->left = new TreeNode(7);
    root->right->left->right = new TreeNode(8);
    
    testAllApproaches(root, 3); // Left side leaf at depth 3
    deleteTree(root);
}

// Value Variation Tests

TEST_F(MinimumDepthBinaryTreeTest, NegativeValues) {
    int v_neg5 = -5, v_neg10 = -10, v_neg1 = -1;
    TreeNode* root = createTree({&v_neg5, &v_neg10, &v_neg1});
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, ZeroValues) {
    int v0 = 0, v1 = 1, v2 = 2;
    TreeNode* root = createTree({&v0, &v1, &v2});
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, MixedValues) {
    int v100 = 100, v_neg50 = -50, v0 = 0, v999 = 999;
    TreeNode* root = createTree({&v100, &v_neg50, &v0, &v999});
    testAllApproaches(root, 2);
    deleteTree(root);
}

// Boundary Value Tests

TEST_F(MinimumDepthBinaryTreeTest, MaxConstraintValues) {
    int vmax = 1000, vmin = -1000;
    TreeNode* root = new TreeNode(vmax);
    root->left = new TreeNode(vmin);
    root->right = new TreeNode(vmax);
    
    testAllApproaches(root, 2);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, RepeatingValues) {
    int v5 = 5;
    TreeNode* root = createTree({&v5, &v5, &v5, &v5, &v5, &v5, &v5});
    testAllApproaches(root, 3);
    deleteTree(root);
}

// Asymmetric Trees

TEST_F(MinimumDepthBinaryTreeTest, LeftHeavyTree) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6;
    TreeNode* root = createTree({&v1, &v2, &v3, &v4, &v5, nullptr, &v6});
    testAllApproaches(root, 3); // All leaves at depth 3
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, RightHeavyTree) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6;
    TreeNode* root = createTree({&v1, &v2, &v3, &v4, nullptr, &v5, &v6});
    testAllApproaches(root, 3); // All leaves at depth 3
    deleteTree(root);
}

// Performance Edge Cases

TEST_F(MinimumDepthBinaryTreeTest, WideShallowTree) {
    // Wide tree with many leaves at depth 2
    TreeNode* root = new TreeNode(1);
    
    // Create 8 children at depth 2
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    testAllApproaches(root, 3);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, VeryDeepSinglePath) {
    TreeNode* root = new TreeNode(1);
    TreeNode* current = root;
    
    // Create very deep single path
    for (int i = 2; i <= 20; ++i) {
        current->left = new TreeNode(i);
        current = current->left;
    }
    
    testAllApproaches(root, 20);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, DeepTreeWithShortcut) {
    TreeNode* root = new TreeNode(1);
    
    // Short path on left
    root->left = new TreeNode(2);
    
    // Long path on right
    TreeNode* current = root;
    for (int i = 3; i <= 15; ++i) {
        current->right = new TreeNode(i);
        current = current->right;
    }
    
    testAllApproaches(root, 2); // Left leaf at depth 2
    deleteTree(root);
}

// Special Structure Tests

TEST_F(MinimumDepthBinaryTreeTest, FullBinaryTreeDepth4) {
    // Full binary tree with all leaves at same depth
    TreeNode* root = new TreeNode(1);
    
    // Level 1
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    // Level 2
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    // Level 3 (leaves)
    root->left->left->left = new TreeNode(8);
    root->left->left->right = new TreeNode(9);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(11);
    root->right->left->left = new TreeNode(12);
    root->right->left->right = new TreeNode(13);
    root->right->right->left = new TreeNode(14);
    root->right->right->right = new TreeNode(15);
    
    testAllApproaches(root, 4);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, ZigzagPattern) {
    // Tree with zigzag pattern
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(4);
    root->left->right->left->right = new TreeNode(5);
    
    testAllApproaches(root, 5);
    deleteTree(root);
}

// Incomplete Trees

TEST_F(MinimumDepthBinaryTreeTest, IncompleteLeftSide) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* root = createTree({&v1, &v2, &v3, nullptr, &v4});
    testAllApproaches(root, 2); // Right leaf at depth 2
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, IncompleteRightSide) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* root = createTree({&v1, &v2, &v3, &v4});
    testAllApproaches(root, 2); // Right leaf at depth 2
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, SparseTree) {
    int v1 = 1, v2 = 2, v5 = 5, v6 = 6;
    TreeNode* root = createTree({&v1, &v2, nullptr, nullptr, nullptr, &v5, &v6});
    testAllApproaches(root, 2); // Leaf at depth 2 (node 2 is leaf)
    deleteTree(root);
}

// Stress Tests

TEST_F(MinimumDepthBinaryTreeTest, LargeBalancedTree) {
    // Create larger balanced tree programmatically
    TreeNode* root = new TreeNode(1);
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    int nodeVal = 2;
    int levels = 6; // Create tree with 6 levels
    
    for (int level = 1; level < levels; ++level) {
        int levelSize = queue.size();
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = queue.front();
            queue.pop();
            
            current->left = new TreeNode(nodeVal++);
            current->right = new TreeNode(nodeVal++);
            
            queue.push(current->left);
            queue.push(current->right);
        }
    }
    
    testAllApproaches(root, levels);
    deleteTree(root);
}

TEST_F(MinimumDepthBinaryTreeTest, PathologicalCase) {
    // One very short path, one very long path
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2); // Short path ends here
    
    // Long right path
    TreeNode* current = root;
    for (int i = 3; i <= 50; ++i) {
        current->right = new TreeNode(i);
        current = current->right;
    }
    
    testAllApproaches(root, 2); // Left leaf wins
    deleteTree(root);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode