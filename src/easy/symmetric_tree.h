#pragma once

#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::TreeNode;

/**
 * Problem 101: Symmetric Tree
 * 
 * Given the root of a binary tree, check whether it is a mirror of itself 
 * (i.e., symmetric around its center).
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [1, 1000]
 * - -100 <= Node.val <= 100
 * 
 * Follow up: Could you solve it both recursively and iteratively?
 */
class SymmetricTree {
public:
    /**
     * Approach 1: Recursive Comparison (Optimal)
     * 
     * Recursively check if left and right subtrees are mirrors.
     * 
     * Reasoning: A tree is symmetric if left and right subtrees are mirrors
     * of each other. Two trees are mirrors if:
     * 1. Both roots have same value
     * 2. Left subtree of first is mirror of right subtree of second
     * 3. Right subtree of first is mirror of left subtree of second
     * This recursive definition naturally captures the symmetry property.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - recursion stack, h is tree height
     * 
     * Best when: Clean recursive solution preferred, most intuitive
     * Worst when: Very deep trees might cause stack overflow
     */
    bool isSymmetricRecursive(TreeNode* root);

    /**
     * Approach 2: Iterative BFS with Queue
     * 
     * Use BFS to compare nodes level by level.
     * 
     * Reasoning: Process tree level by level, ensuring symmetric properties.
     * For each level, nodes should appear in mirror order. Use queue to
     * store pairs of nodes that should be mirrors of each other. This
     * avoids recursion and provides level-by-level verification of symmetry.
     * Easier to debug and visualize than recursive approach.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(w) - queue size, w is maximum tree width
     * 
     * Best when: Avoiding recursion, wide trees, level-order processing
     * Worst when: Deep narrow trees (queue overhead)
     */
    bool isSymmetricBFS(TreeNode* root);

    /**
     * Approach 3: Iterative DFS with Stack
     * 
     * Use stack to simulate recursive comparison.
     * 
     * Reasoning: Simulate recursive approach using explicit stack. Push
     * pairs of nodes that should be mirrors onto stack. Pop and compare,
     * pushing children in mirror order. This gives same traversal pattern
     * as recursion but with explicit stack control. Useful for very deep
     * trees where recursion might overflow.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - stack size proportional to tree height
     * 
     * Best when: Need DFS pattern without recursion, deep trees
     * Worst when: Recursive solution is simpler and adequate
     */
    bool isSymmetricDFS(TreeNode* root);

    /**
     * Approach 4: In-order Traversal Comparison
     * 
     * Compare in-order traversals of left and right subtrees.
     * 
     * Reasoning: For symmetric tree, in-order traversal of left subtree
     * should be reverse of right subtree's in-order traversal. However,
     * this approach has flaws - trees with same in-order traversal aren't
     * necessarily symmetric. Need to include null nodes and structure info.
     * Demonstrates traversal-based comparison but requires careful handling.
     * 
     * Time Complexity: O(n) - traverse tree to build sequences
     * Space Complexity: O(n) - store traversal sequences
     * 
     * Best when: Educational purposes, understanding traversal properties
     * Worst when: Simple symmetric check is needed (more complex than needed)
     */
    bool isSymmetricInOrder(TreeNode* root);

    /**
     * Approach 5: String Serialization
     * 
     * Serialize tree and check if it reads same forwards and backwards.
     * 
     * Reasoning: Serialize tree in a way that captures structure, then check
     * if resulting string is palindromic. Must include null markers and
     * position information. While creative, this is inefficient as it
     * processes entire tree and doesn't take advantage of early termination.
     * Demonstrates string-based tree analysis.
     * 
     * Time Complexity: O(n) - serialize entire tree
     * Space Complexity: O(n) - store serialized string
     * 
     * Best when: Need string representation anyway, creative solutions
     * Worst when: Efficiency important, early termination desired
     */
    bool isSymmetricSerialization(TreeNode* root);

    /**
     * Approach 6: Pre-order and Post-order Combination
     * 
     * Use pre-order and mirror pre-order traversals.
     * 
     * Reasoning: Perform pre-order traversal on left subtree and mirror
     * pre-order (root-right-left) on right subtree. For symmetric tree,
     * these should produce identical sequences. This approach separates
     * the traversal from comparison and can be extended to other tree
     * analysis problems. Include null markers to capture structure.
     * 
     * Time Complexity: O(n) - traverse tree twice
     * Space Complexity: O(n) - store traversal results
     * 
     * Best when: Need traversal sequences, separating concerns
     * Worst when: Direct comparison is more efficient
     */
    bool isSymmetricTraversal(TreeNode* root);

private:
    // Helper for recursive approach
    bool isMirror(TreeNode* left, TreeNode* right);
    
    // Helpers for traversal approaches
    void inOrderLeft(TreeNode* root, std::vector<int>& result);
    void inOrderRight(TreeNode* root, std::vector<int>& result);
    void preOrder(TreeNode* root, std::vector<int>& result);
    void mirrorPreOrder(TreeNode* root, std::vector<int>& result);
    
    // Helper for serialization
    void serialize(TreeNode* root, std::stringstream& ss);
    
    // Helper to check if string is palindrome
    bool isPalindrome(const std::string& s);
    
    // Null marker for traversals
    static const int NULL_MARKER = INT_MIN;
};

}  // namespace easy
}  // namespace leetcode