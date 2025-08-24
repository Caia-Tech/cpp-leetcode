#include <gtest/gtest.h>
#include "../../src/easy/path_sum.h"
#include "../../src/utils/test_utils.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

using utils::TreeNode;

class PathSumTest : public ::testing::Test {
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
    void testAllApproaches(TreeNode* root, int targetSum, bool expected) {
        PathSum solution;
        
        EXPECT_EQ(solution.hasPathSumRecursive(root, targetSum), expected) 
            << "Recursive approach failed for target: " << targetSum;
        EXPECT_EQ(solution.hasPathSumDFS(root, targetSum), expected) 
            << "DFS iterative approach failed for target: " << targetSum;
        EXPECT_EQ(solution.hasPathSumBFS(root, targetSum), expected) 
            << "BFS approach failed for target: " << targetSum;
        EXPECT_EQ(solution.hasPathSumMorris(root, targetSum), expected) 
            << "Morris traversal approach failed for target: " << targetSum;
        EXPECT_EQ(solution.hasPathSumTwoPass(root, targetSum), expected) 
            << "Two-pass approach failed for target: " << targetSum;
        EXPECT_EQ(solution.hasPathSumFunctional(root, targetSum), expected) 
            << "Functional approach failed for target: " << targetSum;
    }
};

// LeetCode Example Test Cases

TEST_F(PathSumTest, LeetCodeExample1) {
    // root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
    // Path: 5 -> 4 -> 11 -> 2 = 22, Output: true
    int v5 = 5, v4 = 4, v8 = 8, v11 = 11, v13 = 13, v7 = 7, v2 = 2, v1 = 1;
    TreeNode* root = createTree({&v5, &v4, &v8, &v11, nullptr, &v13, &v4, &v7, &v2, nullptr, nullptr, nullptr, &v1});
    testAllApproaches(root, 22, true);
    deleteTree(root);
}

TEST_F(PathSumTest, LeetCodeExample2) {
    // root = [1,2,3], targetSum = 5
    // No root-to-leaf path sums to 5, Output: false
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v3});
    testAllApproaches(root, 5, false);
    deleteTree(root);
}

TEST_F(PathSumTest, LeetCodeExample3) {
    // root = [], targetSum = 0
    // Empty tree, Output: false
    testAllApproaches(nullptr, 0, false);
}

// Edge Cases

TEST_F(PathSumTest, SingleNodeMatching) {
    TreeNode* root = new TreeNode(5);
    testAllApproaches(root, 5, true);
    deleteTree(root);
}

TEST_F(PathSumTest, SingleNodeNotMatching) {
    TreeNode* root = new TreeNode(5);
    testAllApproaches(root, 3, false);
    deleteTree(root);
}

TEST_F(PathSumTest, SingleNodeZero) {
    TreeNode* root = new TreeNode(0);
    testAllApproaches(root, 0, true);
    deleteTree(root);
}

TEST_F(PathSumTest, TwoNodesLeftPath) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    testAllApproaches(root, 3, true);  // 1 + 2 = 3
    testAllApproaches(root, 1, false); // No path sums to 1
    deleteTree(root);
}

TEST_F(PathSumTest, TwoNodesRightPath) {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    testAllApproaches(root, 3, true);  // 1 + 2 = 3
    testAllApproaches(root, 2, false); // No path sums to 2
    deleteTree(root);
}

// Negative Values

TEST_F(PathSumTest, NegativeValues) {
    int v1 = 1, v_neg2 = -2, v_neg3 = -3, v1_pos = 1, v3 = 3;
    TreeNode* root = createTree({&v1, &v_neg2, &v_neg3, &v1_pos, &v3});
    testAllApproaches(root, 0, true);   // 1 + (-2) + 1 = 0
    testAllApproaches(root, -2, true);  // 1 + (-3) = -2  
    testAllApproaches(root, 2, true);   // 1 + (-2) + 3 = 2
    deleteTree(root);
}

TEST_F(PathSumTest, AllNegativeValues) {
    int v_neg1 = -1, v_neg2 = -2, v_neg3 = -3;
    TreeNode* root = createTree({&v_neg1, &v_neg2, &v_neg3});
    testAllApproaches(root, -3, true);  // -1 + (-2) = -3
    testAllApproaches(root, -4, true);  // -1 + (-3) = -4
    testAllApproaches(root, -1, false);
    deleteTree(root);
}

TEST_F(PathSumTest, MixedSignsComplex) {
    int v5 = 5, v_neg8 = -8, v9 = 9, v2 = 2, v_neg3 = -3, v7 = 7;
    TreeNode* root = createTree({&v5, &v_neg8, &v9, &v2, &v_neg3, nullptr, &v7});
    testAllApproaches(root, -1, true);  // 5 + (-8) + 2 = -1
    testAllApproaches(root, -6, true);  // 5 + (-8) + (-3) = -6  
    testAllApproaches(root, 21, true);  // 5 + 9 + 7 = 21
    deleteTree(root);
}

// Zero Values

TEST_F(PathSumTest, ZeroTargetSum) {
    int v1 = 1, v_neg1 = -1, v0 = 0;
    TreeNode* root = createTree({&v0, &v1, &v_neg1});
    testAllApproaches(root, 1, true);   // 0 + 1 = 1
    testAllApproaches(root, -1, true);  // 0 + (-1) = -1
    testAllApproaches(root, 0, false);  // No leaf path sums to 0
    deleteTree(root);
}

TEST_F(PathSumTest, ZeroNodesInPath) {
    int v0 = 0, v5 = 5;
    TreeNode* root = createTree({&v5, &v0, &v0, &v0, &v5, &v0, &v5});
    testAllApproaches(root, 5, true);   // 5 + 0 + 0 = 5
    testAllApproaches(root, 10, true);  // 5 + 0 + 5 = 10
    testAllApproaches(root, 0, false);
    deleteTree(root);
}

// Complex Tree Structures

TEST_F(PathSumTest, DeepLinearTree) {
    TreeNode* root = new TreeNode(1);
    TreeNode* current = root;
    
    // Create deep linear tree: 1->2->3->4->5 (sum = 15)
    for (int i = 2; i <= 5; ++i) {
        current->left = new TreeNode(i);
        current = current->left;
    }
    
    testAllApproaches(root, 15, true);  // 1+2+3+4+5
    testAllApproaches(root, 10, false);
    testAllApproaches(root, 1, false);  // Only leaf counts
    deleteTree(root);
}

TEST_F(PathSumTest, PerfectBinaryTree) {
    // Perfect binary tree with sum paths
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7;
    TreeNode* root = createTree({&v1, &v2, &v3, &v4, &v5, &v6, &v7});
    
    testAllApproaches(root, 7, true);   // 1+2+4=7
    testAllApproaches(root, 8, true);   // 1+2+5=8
    testAllApproaches(root, 10, true);  // 1+3+6=10
    testAllApproaches(root, 11, true);  // 1+3+7=11
    testAllApproaches(root, 15, false);
    deleteTree(root);
}

TEST_F(PathSumTest, SkewedTree) {
    // Right-skewed tree
    TreeNode* root = new TreeNode(1);
    TreeNode* current = root;
    
    for (int i = 2; i <= 6; ++i) {
        current->right = new TreeNode(i);
        current = current->right;
    }
    
    testAllApproaches(root, 21, true);  // 1+2+3+4+5+6
    testAllApproaches(root, 6, false);  // Only full path to leaf
    deleteTree(root);
}

// Boundary Conditions

TEST_F(PathSumTest, MinimumValues) {
    int vmin = -1000;
    TreeNode* root = new TreeNode(vmin);
    root->left = new TreeNode(vmin);
    root->right = new TreeNode(vmin);
    
    testAllApproaches(root, -2000, true);  // -1000 + (-1000)
    testAllApproaches(root, -1000, false); // No single leaf path
    deleteTree(root);
}

TEST_F(PathSumTest, MaximumValues) {
    int vmax = 1000;
    TreeNode* root = new TreeNode(vmax);
    root->left = new TreeNode(vmax);
    root->right = new TreeNode(vmax);
    
    testAllApproaches(root, 2000, true);  // 1000 + 1000
    testAllApproaches(root, 1000, false); // No single leaf path
    deleteTree(root);
}

TEST_F(PathSumTest, LargeNegativeTarget) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v3});
    testAllApproaches(root, -1000, false);
    deleteTree(root);
}

TEST_F(PathSumTest, LargePositiveTarget) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v3});
    testAllApproaches(root, 1000, false);
    deleteTree(root);
}

// Multiple Valid Paths

TEST_F(PathSumTest, MultipleValidPaths) {
    // Tree with multiple paths that sum to target
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* root = createTree({&v2, &v1, &v3, &v4, nullptr, nullptr, &v1});
    
    testAllApproaches(root, 7, true);   // 2+1+4=7
    testAllApproaches(root, 6, true);   // 2+3+1=6
    testAllApproaches(root, 5, false);
    deleteTree(root);
}

TEST_F(PathSumTest, SameValueNodes) {
    // All nodes have same value
    int v3 = 3;
    TreeNode* root = createTree({&v3, &v3, &v3, &v3, &v3, &v3, &v3});
    
    testAllApproaches(root, 9, true);   // 3+3+3=9 (multiple paths)
    testAllApproaches(root, 6, false);  // No path sums to 6
    testAllApproaches(root, 3, false);  // Only leaf nodes count
    deleteTree(root);
}

// Incomplete Trees

TEST_F(PathSumTest, IncompleteLeftHeavy) {
    int v5 = 5, v4 = 4, v11 = 11, v7 = 7, v2 = 2;
    TreeNode* root = createTree({&v5, &v4, nullptr, &v11, nullptr, &v7, &v2});
    
    testAllApproaches(root, 27, true);  // 5+4+11+7=27
    testAllApproaches(root, 22, true);  // 5+4+11+2=22
    testAllApproaches(root, 9, false);
    deleteTree(root);
}

TEST_F(PathSumTest, IncompleteRightHeavy) {
    int v1 = 1, v3 = 3, v6 = 6, v7 = 7;
    TreeNode* root = createTree({&v1, nullptr, &v3, &v6, &v7});
    
    testAllApproaches(root, 10, true);  // 1+3+6=10
    testAllApproaches(root, 11, true);  // 1+3+7=11
    testAllApproaches(root, 4, false);
    deleteTree(root);
}

// Performance Edge Cases

TEST_F(PathSumTest, VeryDeepTree) {
    TreeNode* root = new TreeNode(0);
    TreeNode* current = root;
    int expectedSum = 0;
    
    // Create deep tree with alternating structure
    for (int i = 1; i <= 20; ++i) {
        if (i % 2 == 1) {
            current->left = new TreeNode(i);
            current = current->left;
        } else {
            current->right = new TreeNode(i);
            current = current->right;
        }
        expectedSum += i;
    }
    
    testAllApproaches(root, expectedSum, true);
    testAllApproaches(root, expectedSum + 1, false);
    deleteTree(root);
}

TEST_F(PathSumTest, WideTree) {
    // Create wide tree at level 2
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    // Add many leaves to create width
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    testAllApproaches(root, 7, true);   // 1+2+4
    testAllApproaches(root, 8, true);   // 1+2+5
    testAllApproaches(root, 10, true);  // 1+3+6
    testAllApproaches(root, 11, true);  // 1+3+7
    deleteTree(root);
}

// Special Mathematical Cases

TEST_F(PathSumTest, IntegerOverflowPrevention) {
    // Test with values that could cause overflow if not handled properly
    int v500 = 500, v_neg500 = -500;
    TreeNode* root = createTree({&v500, &v500, &v_neg500, &v500});
    
    testAllApproaches(root, 1500, true);   // 500+500+500
    testAllApproaches(root, 0, true);      // 500+(-500)
    deleteTree(root);
}

TEST_F(PathSumTest, ZeroCancellation) {
    // Test where intermediate sums might be zero
    int v5 = 5, v_neg5 = -5, v0 = 0;
    TreeNode* root = createTree({&v5, &v_neg5, &v_neg5, &v0, &v5});
    
    testAllApproaches(root, 0, true);   // 5+(-5)+0=0
    testAllApproaches(root, 5, true);   // 5+(-5)+5=5  
    testAllApproaches(root, -10, false); // No such path
    deleteTree(root);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode