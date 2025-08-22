#include <gtest/gtest.h>
#include "hard/serialize_deserialize_binary_tree.h"
#include "utils/data_structures.h"
#include <vector>
#include <algorithm>
#include <queue>

using namespace leetcode::utils;

namespace leetcode {
namespace hard {
namespace test {

class SerializeDeserializeBinaryTreeTest : public ::testing::Test {
protected:
    SerializeDeserializeBinaryTree solution;
    
    // Helper to compare trees for structural and value equality
    bool treesEqual(TreeNode* a, TreeNode* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return a->val == b->val && 
               treesEqual(a->left, b->left) && 
               treesEqual(a->right, b->right);
    }
    
    void testAllApproaches(TreeNode* root) {
        // Test Preorder approach
        std::string serialized1 = solution.serializePreorder(root);
        TreeNode* deserialized1 = solution.deserializePreorder(serialized1);
        EXPECT_TRUE(treesEqual(root, deserialized1)) 
            << "Preorder approach failed";
        
        // Test Level Order approach
        std::string serialized2 = solution.serializeLevelOrder(root);
        TreeNode* deserialized2 = solution.deserializeLevelOrder(serialized2);
        EXPECT_TRUE(treesEqual(root, deserialized2)) 
            << "Level Order approach failed";
        
        // Test Postorder approach
        std::string serialized3 = solution.serializePostorder(root);
        TreeNode* deserialized3 = solution.deserializePostorder(serialized3);
        EXPECT_TRUE(treesEqual(root, deserialized3)) 
            << "Postorder approach failed";
        
        // Test Inorder approach
        std::string serialized4 = solution.serializeInorder(root);
        TreeNode* deserialized4 = solution.deserializeInorder(serialized4);
        EXPECT_TRUE(treesEqual(root, deserialized4)) 
            << "Inorder approach failed";
        
        // Test Binary encoding approach
        std::string serialized5 = solution.serializeBinary(root);
        TreeNode* deserialized5 = solution.deserializeBinary(serialized5);
        EXPECT_TRUE(treesEqual(root, deserialized5)) 
            << "Binary encoding approach failed";
        
        // Test Parentheses approach
        std::string serialized6 = solution.serializeParentheses(root);
        TreeNode* deserialized6 = solution.deserializeParentheses(serialized6);
        EXPECT_TRUE(treesEqual(root, deserialized6)) 
            << "Parentheses approach failed";
    }
    
    // Helper to create tree from level-order array with nulls
    TreeNode* createTree(const std::vector<int*>& values) {
        if (values.empty() || !values[0]) return nullptr;
        
        TreeNode* root = new TreeNode(*values[0]);
        std::queue<TreeNode*> queue;
        queue.push(root);
        
        for (int i = 1; i < values.size(); i += 2) {
            if (queue.empty()) break;
            
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
    
    int* val(int x) { return new int(x); }
    int* null() { return nullptr; }
    
    void TearDown() override {
        // Note: In practice, should implement proper tree cleanup
        // For testing purposes, relying on test framework cleanup
    }
};

// Basic functionality tests
TEST_F(SerializeDeserializeBinaryTreeTest, EmptyTree) {
    testAllApproaches(nullptr);
}

TEST_F(SerializeDeserializeBinaryTreeTest, SingleNode) {
    TreeNode* root = new TreeNode(1);
    testAllApproaches(root);
    
    root = new TreeNode(0);
    testAllApproaches(root);
    
    root = new TreeNode(-1);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, TwoNodes) {
    // Left child only
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    testAllApproaches(root);
    
    // Right child only
    root = new TreeNode(1);
    root->right = new TreeNode(3);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, ThreeNodes) {
    // Complete binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, LeetCodeExample) {
    // [1,2,3,null,null,4,5]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    testAllApproaches(root);
}

// Linear trees (essentially linked lists)
TEST_F(SerializeDeserializeBinaryTreeTest, LeftSkewed) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, RightSkewed) {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    testAllApproaches(root);
}

// Complete and perfect trees
TEST_F(SerializeDeserializeBinaryTreeTest, CompleteBinaryTree) {
    // [1,2,3,4,5,6,7]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, PerfectBinaryTree) {
    // [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
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
    
    testAllApproaches(root);
}

// Trees with missing internal nodes
TEST_F(SerializeDeserializeBinaryTreeTest, SparseTree) {
    // [1,2,3,null,null,null,4,null,null,null,5]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(4);
    root->right->right->right = new TreeNode(5);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, MissingLeftSubtree) {
    // [1,null,2,null,3,null,4]
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    testAllApproaches(root);
}

// Negative values
TEST_F(SerializeDeserializeBinaryTreeTest, NegativeValues) {
    TreeNode* root = new TreeNode(-1);
    root->left = new TreeNode(-2);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(-4);
    root->left->right = new TreeNode(-5);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, MixedValues) {
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(-100);
    root->right = new TreeNode(100);
    root->left->left = new TreeNode(-50);
    root->right->right = new TreeNode(200);
    testAllApproaches(root);
}

// Extreme values
TEST_F(SerializeDeserializeBinaryTreeTest, ExtremeValues) {
    TreeNode* root = new TreeNode(1000);
    root->left = new TreeNode(-1000);
    root->right = new TreeNode(999);
    root->left->left = new TreeNode(-999);
    testAllApproaches(root);
}

// Large trees for stress testing
TEST_F(SerializeDeserializeBinaryTreeTest, DeepTree) {
    // Create a deep right-skewed tree
    TreeNode* root = new TreeNode(1);
    TreeNode* current = root;
    for (int i = 2; i <= 20; ++i) {
        current->right = new TreeNode(i);
        current = current->right;
    }
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, WideTree) {
    // Create a wide but shallow tree
    TreeNode* root = new TreeNode(0);
    
    // Level 1
    root->left = new TreeNode(-1);
    root->right = new TreeNode(1);
    
    // Level 2 - create many nodes
    root->left->left = new TreeNode(-2);
    root->left->right = new TreeNode(-3);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(3);
    
    // Level 3
    root->left->left->left = new TreeNode(-4);
    root->left->left->right = new TreeNode(-5);
    root->left->right->left = new TreeNode(-6);
    root->left->right->right = new TreeNode(-7);
    root->right->left->left = new TreeNode(4);
    root->right->left->right = new TreeNode(5);
    root->right->right->left = new TreeNode(6);
    root->right->right->right = new TreeNode(7);
    
    testAllApproaches(root);
}

// Special patterns
TEST_F(SerializeDeserializeBinaryTreeTest, ZigzagPattern) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(3);
    root->left->right->left = new TreeNode(4);
    root->left->right->left->right = new TreeNode(5);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, BalancedButIncomplete) {
    // [1,2,3,4,5,null,6]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    testAllApproaches(root);
}

// Duplicate values
TEST_F(SerializeDeserializeBinaryTreeTest, DuplicateValues) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(1);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    testAllApproaches(root);
}

TEST_F(SerializeDeserializeBinaryTreeTest, AllSameValues) {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(5);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(5);
    testAllApproaches(root);
}

// Algorithm-specific tests
TEST_F(SerializeDeserializeBinaryTreeTest, PreorderFormatValidation) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    std::string serialized = solution.serializePreorder(root);
    // Should be something like "1,2,null,null,3,null,null"
    EXPECT_FALSE(serialized.empty());
    
    TreeNode* deserialized = solution.deserializePreorder(serialized);
    EXPECT_TRUE(treesEqual(root, deserialized));
}

TEST_F(SerializeDeserializeBinaryTreeTest, LevelOrderFormatValidation) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    std::string serialized = solution.serializeLevelOrder(root);
    // Should be something like "1,2,3"
    EXPECT_FALSE(serialized.empty());
    
    TreeNode* deserialized = solution.deserializeLevelOrder(serialized);
    EXPECT_TRUE(treesEqual(root, deserialized));
}

TEST_F(SerializeDeserializeBinaryTreeTest, PostorderFormatValidation) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    std::string serialized = solution.serializePostorder(root);
    EXPECT_FALSE(serialized.empty());
    
    TreeNode* deserialized = solution.deserializePostorder(serialized);
    EXPECT_TRUE(treesEqual(root, deserialized));
}

TEST_F(SerializeDeserializeBinaryTreeTest, InorderFormatValidation) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    std::string serialized = solution.serializeInorder(root);
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find("VALUES:"), std::string::npos);
    EXPECT_NE(serialized.find("STRUCTURE:"), std::string::npos);
    
    TreeNode* deserialized = solution.deserializeInorder(serialized);
    EXPECT_TRUE(treesEqual(root, deserialized));
}

TEST_F(SerializeDeserializeBinaryTreeTest, BinaryEncodingValidation) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    std::string serialized = solution.serializeBinary(root);
    EXPECT_FALSE(serialized.empty());
    
    TreeNode* deserialized = solution.deserializeBinary(serialized);
    EXPECT_TRUE(treesEqual(root, deserialized));
}

TEST_F(SerializeDeserializeBinaryTreeTest, ParenthesesFormatValidation) {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    std::string serialized = solution.serializeParentheses(root);
    // Should be something like "1(2(()))(3(()))"
    EXPECT_FALSE(serialized.empty());
    EXPECT_NE(serialized.find('('), std::string::npos);
    EXPECT_NE(serialized.find(')'), std::string::npos);
    
    TreeNode* deserialized = solution.deserializeParentheses(serialized);
    EXPECT_TRUE(treesEqual(root, deserialized));
}

// Edge cases
TEST_F(SerializeDeserializeBinaryTreeTest, EmptyStringDeserialization) {
    // Test that empty strings properly deserialize to null
    EXPECT_EQ(solution.deserializePreorder(""), nullptr);
    EXPECT_EQ(solution.deserializeLevelOrder(""), nullptr);
    EXPECT_EQ(solution.deserializePostorder(""), nullptr);
    EXPECT_EQ(solution.deserializeInorder(""), nullptr);
    EXPECT_EQ(solution.deserializeBinary(""), nullptr);
    EXPECT_EQ(solution.deserializeParentheses(""), nullptr);
}

TEST_F(SerializeDeserializeBinaryTreeTest, RoundTripConsistency) {
    // Test multiple round trips
    TreeNode* original = new TreeNode(1);
    original->left = new TreeNode(2);
    original->right = new TreeNode(3);
    
    // Serialize -> Deserialize -> Serialize -> Deserialize
    std::string ser1 = solution.serializePreorder(original);
    TreeNode* deser1 = solution.deserializePreorder(ser1);
    std::string ser2 = solution.serializePreorder(deser1);
    TreeNode* deser2 = solution.deserializePreorder(ser2);
    
    EXPECT_TRUE(treesEqual(original, deser2));
    EXPECT_EQ(ser1, ser2);
}

// Performance validation
TEST_F(SerializeDeserializeBinaryTreeTest, LargeTreePerformance) {
    // Create a reasonably large balanced tree
    std::vector<TreeNode*> nodes;
    for (int i = 1; i <= 100; ++i) {
        nodes.push_back(new TreeNode(i));
    }
    
    // Build a complete binary tree
    for (int i = 0; i < 50; ++i) {
        if (2*i + 1 < nodes.size()) {
            nodes[i]->left = nodes[2*i + 1];
        }
        if (2*i + 2 < nodes.size()) {
            nodes[i]->right = nodes[2*i + 2];
        }
    }
    
    testAllApproaches(nodes[0]);
}

}
}
}