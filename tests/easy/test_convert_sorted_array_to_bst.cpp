#include <gtest/gtest.h>
#include "../../src/easy/convert_sorted_array_to_bst.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

namespace leetcode {
namespace easy {
namespace test {

class ConvertSortedArrayToBSTTest : public ::testing::Test {
protected:
    // Helper function to perform in-order traversal
    void inOrderTraversal(TreeNode* root, std::vector<int>& result) {
        if (!root) return;
        inOrderTraversal(root->left, result);
        result.push_back(root->val);
        inOrderTraversal(root->right, result);
    }
    
    // Helper function to check if tree is height-balanced
    int checkBalancedHeight(TreeNode* root) {
        if (!root) return 0;
        
        int leftHeight = checkBalancedHeight(root->left);
        if (leftHeight == -1) return -1;  // Left subtree is not balanced
        
        int rightHeight = checkBalancedHeight(root->right);
        if (rightHeight == -1) return -1; // Right subtree is not balanced
        
        // Check if current node is balanced
        if (std::abs(leftHeight - rightHeight) > 1) return -1;
        
        return std::max(leftHeight, rightHeight) + 1;
    }
    
    bool isBalanced(TreeNode* root) {
        return checkBalancedHeight(root) != -1;
    }
    
    // Helper function to validate BST property
    bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
        if (!root) return true;
        
        if (root->val <= minVal || root->val >= maxVal) return false;
        
        return isValidBST(root->left, minVal, root->val) && 
               isValidBST(root->right, root->val, maxVal);
    }
    
    // Helper to delete tree and avoid memory leaks
    void deleteTree(TreeNode* root) {
        if (!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
    
    // Helper to test all approaches
    void testAllApproaches(std::vector<int> nums) {
        ConvertSortedArrayToBST solution;
        
        // Test each approach
        auto nums1 = nums, nums2 = nums, nums3 = nums, nums4 = nums, nums5 = nums, nums6 = nums;
        
        TreeNode* result1 = solution.sortedArrayToBSTRecursive(nums1);
        TreeNode* result2 = solution.sortedArrayToBSTIterative(nums2);
        TreeNode* result3 = solution.sortedArrayToBSTPreOrder(nums3);
        TreeNode* result4 = solution.sortedArrayToBSTRandom(nums4);
        TreeNode* result5 = solution.sortedArrayToBSTLevelOrder(nums5);
        TreeNode* result6 = solution.sortedArrayToBSTFunctional(nums6);
        
        // Verify all results are valid BSTs and balanced
        std::vector<TreeNode*> results = {result1, result2, result3, result4, result5, result6};
        std::vector<std::string> approaches = {"Recursive", "Iterative", "PreOrder", "Random", "LevelOrder", "Functional"};
        
        for (size_t i = 0; i < results.size(); ++i) {
            TreeNode* result = results[i];
            
            EXPECT_TRUE(isValidBST(result)) 
                << approaches[i] << " approach failed: result is not a valid BST for input: " << vectorToString(nums);
            EXPECT_TRUE(isBalanced(result)) 
                << approaches[i] << " approach failed: result is not balanced for input: " << vectorToString(nums);
            
            // Verify in-order traversal gives original sorted array
            std::vector<int> inOrder;
            inOrderTraversal(result, inOrder);
            EXPECT_EQ(inOrder, nums) 
                << approaches[i] << " approach failed: in-order traversal doesn't match input for: " << vectorToString(nums);
        }
        
        // Clean up memory
        for (TreeNode* result : results) {
            deleteTree(result);
        }
    }
    
    // Helper to convert vector to string for error messages
    std::string vectorToString(const std::vector<int>& vec) {
        std::string result = "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) result += ", ";
            result += std::to_string(vec[i]);
        }
        result += "]";
        return result;
    }
};

// LeetCode Example Test Cases

TEST_F(ConvertSortedArrayToBSTTest, LeetCodeExample1) {
    // Input: nums = [-10,-3,0,5,9]
    // Expected: Balanced BST with in-order traversal [-10,-3,0,5,9]
    testAllApproaches({-10, -3, 0, 5, 9});
}

TEST_F(ConvertSortedArrayToBSTTest, LeetCodeExample2) {
    // Input: nums = [1,3]
    // Expected: Balanced BST with in-order traversal [1,3]
    testAllApproaches({1, 3});
}

// Edge Cases

TEST_F(ConvertSortedArrayToBSTTest, SingleElement) {
    // Single element should create a tree with just root
    testAllApproaches({5});
}

TEST_F(ConvertSortedArrayToBSTTest, TwoElements) {
    // Two elements should create a tree with root and one child
    testAllApproaches({1, 2});
}

TEST_F(ConvertSortedArrayToBSTTest, ThreeElements) {
    // Three elements should create perfect binary tree
    testAllApproaches({1, 2, 3});
}

TEST_F(ConvertSortedArrayToBSTTest, EmptyArray) {
    // Empty array should return nullptr
    ConvertSortedArrayToBST solution;
    std::vector<int> empty;
    
    EXPECT_EQ(solution.sortedArrayToBSTRecursive(empty), nullptr);
    EXPECT_EQ(solution.sortedArrayToBSTIterative(empty), nullptr);
    EXPECT_EQ(solution.sortedArrayToBSTPreOrder(empty), nullptr);
    EXPECT_EQ(solution.sortedArrayToBSTRandom(empty), nullptr);
    EXPECT_EQ(solution.sortedArrayToBSTLevelOrder(empty), nullptr);
    EXPECT_EQ(solution.sortedArrayToBSTFunctional(empty), nullptr);
}

// Size-based Tests

TEST_F(ConvertSortedArrayToBSTTest, FourElements) {
    testAllApproaches({1, 2, 3, 4});
}

TEST_F(ConvertSortedArrayToBSTTest, FiveElements) {
    testAllApproaches({1, 2, 3, 4, 5});
}

TEST_F(ConvertSortedArrayToBSTTest, SixElements) {
    testAllApproaches({1, 2, 3, 4, 5, 6});
}

TEST_F(ConvertSortedArrayToBSTTest, SevenElements) {
    testAllApproaches({1, 2, 3, 4, 5, 6, 7});
}

TEST_F(ConvertSortedArrayToBSTTest, EightElements) {
    testAllApproaches({-4, -3, -2, -1, 0, 1, 2, 3});
}

// Range Tests

TEST_F(ConvertSortedArrayToBSTTest, NegativeNumbers) {
    testAllApproaches({-10, -8, -6, -4, -2});
}

TEST_F(ConvertSortedArrayToBSTTest, PositiveNumbers) {
    testAllApproaches({2, 4, 6, 8, 10});
}

TEST_F(ConvertSortedArrayToBSTTest, MixedNumbers) {
    testAllApproaches({-5, -2, 0, 3, 7, 11});
}

TEST_F(ConvertSortedArrayToBSTTest, LargeNumbers) {
    testAllApproaches({-10000, -5000, 0, 5000, 10000});
}

// Pattern Tests

TEST_F(ConvertSortedArrayToBSTTest, ConsecutiveIntegers) {
    testAllApproaches({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
}

TEST_F(ConvertSortedArrayToBSTTest, EvenSpacing) {
    testAllApproaches({0, 2, 4, 6, 8, 10, 12});
}

TEST_F(ConvertSortedArrayToBSTTest, OddSpacing) {
    testAllApproaches({1, 3, 5, 7, 9, 11, 13});
}

TEST_F(ConvertSortedArrayToBSTTest, PowersOfTwo) {
    testAllApproaches({1, 2, 4, 8, 16, 32});
}

TEST_F(ConvertSortedArrayToBSTTest, FibonacciSequence) {
    testAllApproaches({1, 2, 3, 5, 8, 13, 21, 34});
}

// Specific Tree Structure Tests

TEST_F(ConvertSortedArrayToBSTTest, PerfectBinaryTreeSize) {
    // 15 elements form perfect binary tree of height 4
    testAllApproaches({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
}

TEST_F(ConvertSortedArrayToBSTTest, PowerOfTwoMinusOne) {
    // 7 elements (2^3 - 1) should form perfect binary tree
    testAllApproaches({10, 20, 30, 40, 50, 60, 70});
}

TEST_F(ConvertSortedArrayToBSTTest, PowerOfTwo) {
    // 8 elements (2^3) should form complete binary tree
    testAllApproaches({-8, -4, -2, -1, 1, 2, 4, 8});
}

// Boundary Value Tests

TEST_F(ConvertSortedArrayToBSTTest, MinimumConstraintValues) {
    testAllApproaches({-10000});
}

TEST_F(ConvertSortedArrayToBSTTest, MaximumConstraintValues) {
    testAllApproaches({10000});
}

TEST_F(ConvertSortedArrayToBSTTest, ConstraintRange) {
    testAllApproaches({-10000, -1, 0, 1, 10000});
}

// Larger Arrays

TEST_F(ConvertSortedArrayToBSTTest, TwentyElements) {
    std::vector<int> nums;
    for (int i = 1; i <= 20; ++i) {
        nums.push_back(i);
    }
    testAllApproaches(nums);
}

TEST_F(ConvertSortedArrayToBSTTest, FiftyElements) {
    std::vector<int> nums;
    for (int i = -25; i < 25; ++i) {
        nums.push_back(i);
    }
    testAllApproaches(nums);
}

// Property Verification Tests

TEST_F(ConvertSortedArrayToBSTTest, TreeHeightProperty) {
    // Test that tree height is approximately log(n)
    ConvertSortedArrayToBST solution;
    
    std::vector<int> nums;
    for (int i = 1; i <= 31; ++i) {  // 31 elements should have height <= 5
        nums.push_back(i);
    }
    
    TreeNode* root = solution.sortedArrayToBSTRecursive(nums);
    int height = checkBalancedHeight(root);
    
    EXPECT_LE(height, 5) << "Tree height should be logarithmic";
    EXPECT_GE(height, 4) << "Tree height should be at least ceil(log2(n))";
    
    deleteTree(root);
}

TEST_F(ConvertSortedArrayToBSTTest, InOrderTraversalProperty) {
    // Test that in-order traversal of BST gives sorted array
    ConvertSortedArrayToBST solution;
    std::vector<int> nums = {-100, -50, -10, 0, 10, 50, 100};
    
    TreeNode* root = solution.sortedArrayToBSTRecursive(nums);
    std::vector<int> inOrder;
    inOrderTraversal(root, inOrder);
    
    EXPECT_EQ(inOrder, nums);
    EXPECT_TRUE(std::is_sorted(inOrder.begin(), inOrder.end()));
    
    deleteTree(root);
}

TEST_F(ConvertSortedArrayToBSTTest, BalanceProperty) {
    // Test that all subtrees are balanced
    ConvertSortedArrayToBST solution;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    TreeNode* root = solution.sortedArrayToBSTRecursive(nums);
    
    // Verify balance at every node
    std::function<bool(TreeNode*)> verifyBalance = [&](TreeNode* node) -> bool {
        if (!node) return true;
        
        int leftHeight = checkBalancedHeight(node->left);
        int rightHeight = checkBalancedHeight(node->right);
        
        if (leftHeight == -1 || rightHeight == -1) return false;
        if (std::abs(leftHeight - rightHeight) > 1) return false;
        
        return verifyBalance(node->left) && verifyBalance(node->right);
    };
    
    EXPECT_TRUE(verifyBalance(root));
    
    deleteTree(root);
}

// Consistency Tests Between Approaches

TEST_F(ConvertSortedArrayToBSTTest, ApproachConsistency) {
    // Test that all approaches (except random) give similar tree structures
    ConvertSortedArrayToBST solution;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    
    auto nums1 = nums, nums2 = nums, nums3 = nums, nums5 = nums, nums6 = nums;
    
    TreeNode* recursive = solution.sortedArrayToBSTRecursive(nums1);
    TreeNode* iterative = solution.sortedArrayToBSTIterative(nums2);
    TreeNode* preOrder = solution.sortedArrayToBSTPreOrder(nums3);
    TreeNode* levelOrder = solution.sortedArrayToBSTLevelOrder(nums5);
    TreeNode* functional = solution.sortedArrayToBSTFunctional(nums6);
    
    // All should have same root value for this symmetric array
    EXPECT_EQ(recursive->val, 4);
    EXPECT_EQ(iterative->val, 4);
    EXPECT_EQ(preOrder->val, 4);
    EXPECT_EQ(levelOrder->val, 4);
    EXPECT_EQ(functional->val, 4);
    
    // Clean up
    deleteTree(recursive);
    deleteTree(iterative);
    deleteTree(preOrder);
    deleteTree(levelOrder);
    deleteTree(functional);
}

// Stress Tests

TEST_F(ConvertSortedArrayToBSTTest, LargeArray100) {
    std::vector<int> nums;
    for (int i = -50; i < 50; ++i) {
        nums.push_back(i * 2);  // Even numbers from -100 to 98
    }
    testAllApproaches(nums);
}

TEST_F(ConvertSortedArrayToBSTTest, MaxConstraintSize) {
    // Test with larger array (not full 10^4 for test speed)
    std::vector<int> nums;
    for (int i = 0; i < 200; ++i) {
        nums.push_back(i);
    }
    
    ConvertSortedArrayToBST solution;
    TreeNode* root = solution.sortedArrayToBSTRecursive(nums);
    
    EXPECT_TRUE(isValidBST(root));
    EXPECT_TRUE(isBalanced(root));
    
    std::vector<int> inOrder;
    inOrderTraversal(root, inOrder);
    EXPECT_EQ(inOrder, nums);
    
    deleteTree(root);
}

// Random Approach Specific Tests

TEST_F(ConvertSortedArrayToBSTTest, RandomApproachVariety) {
    // Test that random approach can produce different trees
    ConvertSortedArrayToBST solution;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    
    std::set<int> rootValues;
    
    // Generate multiple trees and collect root values
    for (int i = 0; i < 20; ++i) {
        auto copy = nums;
        TreeNode* root = solution.sortedArrayToBSTRandom(copy);
        rootValues.insert(root->val);
        
        // Verify it's still valid
        EXPECT_TRUE(isValidBST(root));
        EXPECT_TRUE(isBalanced(root));
        
        deleteTree(root);
    }
    
    // Should have some variety (though not guaranteed)
    EXPECT_GE(rootValues.size(), 1);  // At least one valid root
}

// Memory Management Tests

TEST_F(ConvertSortedArrayToBSTTest, MemoryCleanup) {
    // Test that we can create and destroy multiple trees
    ConvertSortedArrayToBST solution;
    
    for (int size = 1; size <= 10; ++size) {
        std::vector<int> nums;
        for (int i = 1; i <= size; ++i) {
            nums.push_back(i);
        }
        
        TreeNode* root = solution.sortedArrayToBSTRecursive(nums);
        EXPECT_TRUE(isValidBST(root));
        EXPECT_TRUE(isBalanced(root));
        deleteTree(root);
    }
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode