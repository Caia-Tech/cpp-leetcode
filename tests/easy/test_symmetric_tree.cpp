#include <gtest/gtest.h>
#include "../../src/easy/symmetric_tree.h"
#include "../../src/utils/test_utils.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

using utils::TreeNode;

class SymmetricTreeTest : public ::testing::Test {
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
    void testAllApproaches(TreeNode* root, bool expected) {
        SymmetricTree solution;
        
        EXPECT_EQ(solution.isSymmetricRecursive(root), expected) 
            << "Recursive approach failed";
        EXPECT_EQ(solution.isSymmetricBFS(root), expected) 
            << "BFS approach failed";
        EXPECT_EQ(solution.isSymmetricDFS(root), expected) 
            << "DFS iterative approach failed";
        EXPECT_EQ(solution.isSymmetricInOrder(root), expected) 
            << "In-order traversal approach failed";
        EXPECT_EQ(solution.isSymmetricSerialization(root), expected) 
            << "Serialization approach failed";
        EXPECT_EQ(solution.isSymmetricTraversal(root), expected) 
            << "Traversal approach failed";
    }
};

// LeetCode Example Test Cases

TEST_F(SymmetricTreeTest, LeetCodeExample1) {
    // root = [1,2,2,3,4,4,3]
    // Output: true
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* root = createTree({&v1, &v2, &v2, &v3, &v4, &v4, &v3});
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, LeetCodeExample2) {
    // root = [1,2,2,null,3,null,3]
    // Output: false
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v2, nullptr, &v3, nullptr, &v3});
    testAllApproaches(root, false);
    deleteTree(root);
}

// Edge Cases

TEST_F(SymmetricTreeTest, EmptyTree) {
    testAllApproaches(nullptr, true);
}

TEST_F(SymmetricTreeTest, SingleNode) {
    TreeNode* root = new TreeNode(1);
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, TwoNodesSymmetric) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, TwoNodesAsymmetric) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    testAllApproaches(root, false);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, OnlyLeftChild) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    testAllApproaches(root, false);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, OnlyRightChild) {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    testAllApproaches(root, false);
    deleteTree(root);
}

// Perfect Symmetric Trees

TEST_F(SymmetricTreeTest, PerfectSymmetricDepth3) {
    // Perfect symmetric tree of depth 3
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v2, &v3, &v3, &v3, &v3});
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, PerfectAsymmetricDepth3) {
    // Perfect tree but not symmetric
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* root = createTree({&v1, &v2, &v2, &v3, &v4, &v3, &v4});
    testAllApproaches(root, false);
    deleteTree(root);
}

// Structural Asymmetry

TEST_F(SymmetricTreeTest, StructuralAsymmetryLeft) {
    // Same values but different structure
    int v1 = 1, v2 = 2;
    TreeNode* root = createTree({&v1, &v2, &v2, &v2, nullptr, nullptr, &v2});
    testAllApproaches(root, false);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, StructuralAsymmetryRight) {
    int v1 = 1, v2 = 2;
    TreeNode* root = createTree({&v1, &v2, &v2, nullptr, &v2, &v2, nullptr});
    testAllApproaches(root, false);
    deleteTree(root);
}

// Value-based Tests

TEST_F(SymmetricTreeTest, SameStructureDifferentValues) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v3, &v2, &v2, &v3, &v3});
    testAllApproaches(root, false);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, NegativeValues) {
    int v1 = 0, v_neg = -1;
    TreeNode* root = createTree({&v1, &v_neg, &v_neg, &v1, &v1, &v1, &v1});
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, MixedPositiveNegative) {
    int v_pos = 5, v_neg = -5, v_zero = 0;
    TreeNode* root = createTree({&v_zero, &v_pos, &v_neg, &v_neg, &v_pos, &v_pos, &v_neg});
    testAllApproaches(root, false);
    deleteTree(root);
}

// Complex Patterns

TEST_F(SymmetricTreeTest, NestedSymmetry) {
    // Complex nested symmetric pattern
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    TreeNode* root = createTree({&v1, &v2, &v2, &v3, &v4, &v4, &v3, &v5, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &v5});
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, AlmostSymmetric) {
    // Almost symmetric but fails at leaf level
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    TreeNode* root = createTree({&v1, &v2, &v2, &v3, &v4, &v4, &v3, &v5, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &v4});
    testAllApproaches(root, false);
    deleteTree(root);
}

// Large Trees

TEST_F(SymmetricTreeTest, LargeSymmetricTree) {
    // Create large symmetric tree
    TreeNode* root = new TreeNode(1);
    
    // Level 1
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    
    // Level 2
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    
    // Level 3
    root->left->left->left = new TreeNode(5);
    root->left->left->right = new TreeNode(6);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(8);
    root->right->left->left = new TreeNode(8);
    root->right->left->right = new TreeNode(7);
    root->right->right->left = new TreeNode(6);
    root->right->right->right = new TreeNode(5);
    
    testAllApproaches(root, true);
    deleteTree(root);
}

// Special Cases

TEST_F(SymmetricTreeTest, AllSameValues) {
    int v1 = 5;
    TreeNode* root = createTree({&v1, &v1, &v1, &v1, &v1, &v1, &v1});
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, ZeroValues) {
    int v0 = 0, v1 = 1;
    TreeNode* root = createTree({&v1, &v0, &v0, &v1, &v1, &v1, &v1});
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, BoundaryValues) {
    int vmin = -100, vmax = 100, v0 = 0;
    TreeNode* root = createTree({&v0, &vmin, &vmax, &vmax, &vmin, &vmin, &vmax});
    testAllApproaches(root, false);
    deleteTree(root);
}

// Incomplete Trees

TEST_F(SymmetricTreeTest, IncompleteButSymmetric) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v2, nullptr, &v3, &v3, nullptr});
    testAllApproaches(root, true);
    deleteTree(root);
}

TEST_F(SymmetricTreeTest, IncompleteAsymmetric) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* root = createTree({&v1, &v2, &v2, &v3, nullptr, &v3, nullptr});
    testAllApproaches(root, false);
    deleteTree(root);
}

// Performance Tests

TEST_F(SymmetricTreeTest, MaximumDepthSymmetric) {
    // Build maximum depth tree within constraints
    TreeNode* root = new TreeNode(1);
    TreeNode* leftCurrent = root;
    TreeNode* rightCurrent = root;
    
    for (int i = 0; i < 10; ++i) {
        leftCurrent->left = new TreeNode(i);
        leftCurrent->right = new TreeNode(10-i);
        rightCurrent->right = new TreeNode(i);
        rightCurrent->left = new TreeNode(10-i);
        
        leftCurrent = leftCurrent->left;
        rightCurrent = rightCurrent->right;
    }
    
    testAllApproaches(root, true);
    deleteTree(root);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode