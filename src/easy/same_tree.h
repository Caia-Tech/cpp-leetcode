#pragma once

#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include "../utils/data_structures.h"

namespace leetcode {
namespace easy {

using utils::TreeNode;

/**
 * Problem 100: Same Tree
 * 
 * Given the roots of two binary trees p and q, write a function to check if they are 
 * the same or not.
 * 
 * Two binary trees are considered the same if they are structurally identical, and 
 * the nodes have the same value.
 * 
 * Constraints:
 * - The number of nodes in both trees is in the range [0, 100]
 * - -10^4 <= Node.val <= 10^4
 */
class SameTree {
public:
    /**
     * Approach 1: Recursive DFS (Optimal)
     * 
     * Recursively check if trees are identical.
     * 
     * Reasoning: This is the most elegant and intuitive solution. We check:
     * 1. Both null -> same (base case)
     * 2. One null -> different
     * 3. Different values -> different
     * 4. Recursively check left and right subtrees
     * 
     * The recursive structure naturally mirrors the tree structure, making
     * this approach both efficient and easy to understand. Each node is
     * visited exactly once.
     * 
     * Time Complexity: O(min(m, n)) where m and n are tree sizes
     * Space Complexity: O(min(m, n)) for recursion stack (worst case: skewed tree)
     * 
     * Best when: Standard solution, clean code preferred
     * Worst when: Very deep trees might cause stack overflow
     */
    bool isSameTreeRecursive(TreeNode* p, TreeNode* q);

    /**
     * Approach 2: Iterative BFS with Queue
     * 
     * Use queue to traverse both trees level by level.
     * 
     * Reasoning: BFS approach using a queue to store pairs of nodes to compare.
     * We traverse both trees simultaneously, level by level. At each step,
     * we dequeue a pair of nodes and compare them. If they match, we enqueue
     * their children. This avoids recursion stack and processes trees breadth-first,
     * which can be more cache-friendly for wide trees.
     * 
     * Time Complexity: O(min(m, n)) - visit nodes until difference found
     * Space Complexity: O(min(m, n)) - queue can hold at most one level
     * 
     * Best when: Wide trees, avoiding recursion, level-order processing preferred
     * Worst when: Deep narrow trees (queue overhead without benefit)
     */
    bool isSameTreeBFS(TreeNode* p, TreeNode* q);

    /**
     * Approach 3: Iterative DFS with Stack
     * 
     * Use stack to traverse both trees depth-first iteratively.
     * 
     * Reasoning: Similar to recursive DFS but using explicit stack instead
     * of call stack. This gives us more control over the traversal and avoids
     * potential stack overflow for very deep trees. We push pairs of nodes
     * onto the stack and process them in LIFO order, maintaining the
     * depth-first traversal pattern.
     * 
     * Time Complexity: O(min(m, n)) - visit nodes until difference found
     * Space Complexity: O(min(m, n)) - stack size in worst case
     * 
     * Best when: Deep trees, need iterative solution, want DFS pattern
     * Worst when: Recursive solution is acceptable (more complex code)
     */
    bool isSameTreeDFS(TreeNode* p, TreeNode* q);

    /**
     * Approach 4: String Serialization
     * 
     * Serialize both trees and compare strings.
     * 
     * Reasoning: Convert both trees to string representations that uniquely
     * identify their structure and values, then compare strings. We use
     * preorder traversal with special markers for null nodes. While this
     * approach is less efficient (requires full traversal), it demonstrates
     * tree serialization and can be useful when trees need to be compared
     * multiple times (serialize once, compare many).
     * 
     * Time Complexity: O(m + n) - must traverse both trees completely
     * Space Complexity: O(m + n) - store serialized strings
     * 
     * Best when: Need to compare trees multiple times, teaching serialization
     * Worst when: Efficiency is important, early termination needed
     */
    bool isSameTreeSerialization(TreeNode* p, TreeNode* q);

    /**
     * Approach 5: Morris Traversal (Space Optimized)
     * 
     * Use Morris traversal for O(1) space comparison.
     * 
     * Reasoning: Morris traversal modifies the tree temporarily to achieve
     * O(1) space complexity by using threaded binary tree concept. We create
     * temporary links from rightmost nodes of left subtrees to their inorder
     * successors. This allows traversal without stack/recursion. While complex,
     * it demonstrates advanced tree traversal techniques and achieves optimal
     * space complexity.
     * 
     * Time Complexity: O(min(m, n)) - each edge traversed at most twice
     * Space Complexity: O(1) - no extra space besides pointers
     * 
     * Best when: Space is extremely limited, demonstrating advanced techniques
     * Worst when: Simplicity is important, tree modification concerns
     */
    bool isSameTreeMorris(TreeNode* p, TreeNode* q);

    /**
     * Approach 6: Hash-based Structural Comparison
     * 
     * Compute structural hash for both trees and compare.
     * 
     * Reasoning: Calculate a hash value that uniquely represents each tree's
     * structure and values. We use a rolling hash that combines node values
     * and structural information (null nodes represented specially). This
     * approach is interesting for learning about tree hashing and can be
     * extended to find similar subtrees or detect tree isomorphism with
     * modifications.
     * 
     * Time Complexity: O(m + n) - must traverse both trees
     * Space Complexity: O(min(m, n)) - recursion stack for hash computation
     * 
     * Best when: Learning tree hashing, need hash values for other purposes
     * Worst when: Simple comparison needed, hash collision concerns
     */
    bool isSameTreeHash(TreeNode* p, TreeNode* q);

private:
    // Helper for serialization approach
    std::string serialize(TreeNode* root);
    
    // Helper for hash approach
    size_t computeTreeHash(TreeNode* root);
    
    // Helper for Morris traversal restoration
    TreeNode* findPredecessor(TreeNode* current);
};

}  // namespace easy
}  // namespace leetcode