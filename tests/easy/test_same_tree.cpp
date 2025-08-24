#include <gtest/gtest.h>
#include "../../src/easy/same_tree.h"
#include "../../src/utils/test_utils.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

using utils::TreeNode;

class SameTreeTest : public ::testing::Test {
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
    void testAllApproaches(TreeNode* p, TreeNode* q, bool expected) {
        SameTree solution;
        
        EXPECT_EQ(solution.isSameTreeRecursive(p, q), expected) 
            << "Recursive approach failed";
        EXPECT_EQ(solution.isSameTreeBFS(p, q), expected) 
            << "BFS approach failed";
        EXPECT_EQ(solution.isSameTreeDFS(p, q), expected) 
            << "DFS iterative approach failed";
        EXPECT_EQ(solution.isSameTreeSerialization(p, q), expected) 
            << "Serialization approach failed";
        EXPECT_EQ(solution.isSameTreeMorris(p, q), expected) 
            << "Morris traversal approach failed";
        EXPECT_EQ(solution.isSameTreeHash(p, q), expected) 
            << "Hash approach failed";
    }
    
    // Helper to create test values
    std::vector<int> vals(std::initializer_list<int> list) {
        return std::vector<int>(list);
    }
};

// LeetCode Example Test Cases

TEST_F(SameTreeTest, LeetCodeExample1) {
    // p = [1,2,3], q = [1,2,3]
    // Output: true
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* p = createTree({&v1, &v2, &v3});
    TreeNode* q = createTree({&v1, &v2, &v3});
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, LeetCodeExample2) {
    // p = [1,2], q = [1,null,2]
    // Output: false
    int v1 = 1, v2 = 2;
    TreeNode* p = createTree({&v1, &v2, nullptr});
    TreeNode* q = createTree({&v1, nullptr, &v2});
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, LeetCodeExample3) {
    // p = [1,2,1], q = [1,1,2]
    // Output: false
    int v1 = 1, v2 = 2;
    TreeNode* p = createTree({&v1, &v2, &v1});
    TreeNode* q = createTree({&v1, &v1, &v2});
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

// Edge Cases

TEST_F(SameTreeTest, BothEmpty) {
    testAllApproaches(nullptr, nullptr, true);
}

TEST_F(SameTreeTest, OneEmpty) {
    int v1 = 1;
    TreeNode* p = new TreeNode(v1);
    
    testAllApproaches(p, nullptr, false);
    testAllApproaches(nullptr, p, false);
    
    deleteTree(p);
}

TEST_F(SameTreeTest, SingleNodeSame) {
    int v1 = 5;
    TreeNode* p = new TreeNode(v1);
    TreeNode* q = new TreeNode(v1);
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, SingleNodeDifferent) {
    TreeNode* p = new TreeNode(5);
    TreeNode* q = new TreeNode(10);
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

// Structure Differences

TEST_F(SameTreeTest, DifferentDepth) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* p = createTree({&v1, &v2, &v3});
    TreeNode* q = createTree({&v1, &v2, &v3, &v1, nullptr});
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, MirroredStructure) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* p = createTree({&v1, &v2, &v3});
    TreeNode* q = createTree({&v1, &v3, &v2});
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, SameStructureDifferentValues) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* p = createTree({&v1, &v2, &v3});
    TreeNode* q = createTree({&v1, &v2, &v4});
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

// Special Values

TEST_F(SameTreeTest, NegativeValues) {
    int v1 = -1, v2 = -2, v3 = -3;
    TreeNode* p = createTree({&v1, &v2, &v3});
    TreeNode* q = createTree({&v1, &v2, &v3});
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, ZeroValues) {
    int v0 = 0, v1 = 1;
    TreeNode* p = createTree({&v0, &v0, &v1});
    TreeNode* q = createTree({&v0, &v0, &v1});
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, MixedPositiveNegative) {
    int v1 = -5, v2 = 0, v3 = 5;
    TreeNode* p = createTree({&v2, &v1, &v3});
    TreeNode* q = createTree({&v2, &v1, &v3});
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

// Boundary Values

TEST_F(SameTreeTest, MinMaxValues) {
    int vmin = -10000, vmax = 10000;
    TreeNode* p = createTree({&vmax, &vmin, &vmax});
    TreeNode* q = createTree({&vmax, &vmin, &vmax});
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

// Complex Trees

TEST_F(SameTreeTest, BalancedTreeSame) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7;
    TreeNode* p = createTree({&v1, &v2, &v3, &v4, &v5, &v6, &v7});
    TreeNode* q = createTree({&v1, &v2, &v3, &v4, &v5, &v6, &v7});
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, BalancedTreeDifferent) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v7 = 7, v8 = 8;
    TreeNode* p = createTree({&v1, &v2, &v3, &v4, &v5, &v6, &v7});
    TreeNode* q = createTree({&v1, &v2, &v3, &v4, &v5, &v6, &v8});
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, SkewedLeft) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* p = new TreeNode(v1);
    p->left = new TreeNode(v2);
    p->left->left = new TreeNode(v3);
    p->left->left->left = new TreeNode(v4);
    
    TreeNode* q = new TreeNode(v1);
    q->left = new TreeNode(v2);
    q->left->left = new TreeNode(v3);
    q->left->left->left = new TreeNode(v4);
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, SkewedRight) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* p = new TreeNode(v1);
    p->right = new TreeNode(v2);
    p->right->right = new TreeNode(v3);
    p->right->right->right = new TreeNode(v4);
    
    TreeNode* q = new TreeNode(v1);
    q->right = new TreeNode(v2);
    q->right->right = new TreeNode(v3);
    q->right->right->right = new TreeNode(v4);
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, ZigZagPattern) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4;
    TreeNode* p = new TreeNode(v1);
    p->left = new TreeNode(v2);
    p->left->right = new TreeNode(v3);
    p->left->right->left = new TreeNode(v4);
    
    TreeNode* q = new TreeNode(v1);
    q->left = new TreeNode(v2);
    q->left->right = new TreeNode(v3);
    q->left->right->left = new TreeNode(v4);
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

// Subtree Differences

TEST_F(SameTreeTest, DifferentLeftSubtree) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    TreeNode* p = createTree({&v1, &v2, &v3, &v4, &v5});
    TreeNode* q = createTree({&v1, &v2, &v3, &v5, &v5});  // Different left subtree
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, DifferentRightSubtree) {
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6;
    TreeNode* p = createTree({&v1, &v2, &v3, &v4, &v5, &v6});
    TreeNode* q = createTree({&v1, &v2, &v3, &v4, &v5, &v5});  // Different right subtree
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

// Large Trees

TEST_F(SameTreeTest, LargeIdenticalTrees) {
    // Create two identical trees with many nodes
    std::vector<int*> values;
    std::vector<int> nums;
    for (int i = 0; i < 31; i++) {  // Full binary tree of depth 4
        nums.push_back(i);
    }
    for (auto& num : nums) {
        values.push_back(&num);
    }
    
    TreeNode* p = createTree(values);
    TreeNode* q = createTree(values);
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, AllSameValues) {
    int v1 = 5;
    TreeNode* p = createTree({&v1, &v1, &v1, &v1, &v1});
    TreeNode* q = createTree({&v1, &v1, &v1, &v1, &v1});
    
    testAllApproaches(p, q, true);
    
    deleteTree(p);
    deleteTree(q);
}

TEST_F(SameTreeTest, SubtleStructuralDifference) {
    int v1 = 1, v2 = 2, v3 = 3;
    TreeNode* p = createTree({&v1, &v2, &v3, nullptr, nullptr, &v2});
    TreeNode* q = createTree({&v1, &v2, &v3, &v2, nullptr, nullptr});
    
    testAllApproaches(p, q, false);
    
    deleteTree(p);
    deleteTree(q);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode