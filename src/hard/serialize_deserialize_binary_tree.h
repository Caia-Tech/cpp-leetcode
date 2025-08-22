#pragma once

#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <stack>
#include "../utils/data_structures.h"

using namespace leetcode::utils;

namespace leetcode {
namespace hard {

/**
 * Problem 297: Serialize and Deserialize Binary Tree
 * 
 * Serialization is the process of converting a data structure or object into a sequence 
 * of bits so that it can be stored in a file or memory buffer, or transmitted across 
 * a network connection link to be reconstructed later in the same or another computer 
 * environment.
 * 
 * Design an algorithm to serialize and deserialize a binary tree. There is no restriction 
 * on how your serialization/deserialization algorithm should work. You just need to ensure 
 * that a binary tree can be serialized to a string and this string can be deserialized 
 * to the original tree structure.
 * 
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 10^4].
 * - -1000 <= Node.val <= 1000
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class SerializeDeserializeBinaryTree {
public:
    /**
     * Approach 1: Preorder DFS with Null Markers (Classic)
     * 
     * Use preorder traversal with explicit null markers for serialization.
     * 
     * Reasoning: Preorder traversal naturally captures tree structure by visiting
     * root first, then left subtree, then right subtree. Include explicit null markers
     * to represent missing children, enabling unambiguous reconstruction. Serialization:
     * recursively append "root,left_subtree,right_subtree" with "null" for empty nodes.
     * Deserialization: recursively build tree by consuming tokens in preorder sequence.
     * This approach is intuitive, matches human tree reading, and ensures unique encoding.
     * 
     * Time Complexity: O(n) - visit each node once for both operations
     * Space Complexity: O(n) - recursion stack + result string storage
     * 
     * Best when: Learning tree serialization, recursive thinking natural, human-readable format
     * Worst when: Stack overflow risk, very deep trees, iterative solutions preferred
     */
    std::string serializePreorder(TreeNode* root);
    TreeNode* deserializePreorder(std::string data);

    /**
     * Approach 2: Level Order BFS with Queue
     * 
     * Use level-order traversal to serialize tree level by level.
     * 
     * Reasoning: Level-order (breadth-first) serialization produces intuitive format
     * where tree is encoded level by level, left to right. Use queue for BFS traversal,
     * including null markers for missing nodes. Deserialization reverses process:
     * build tree level by level using queue to track parent nodes. This format is
     * often used in LeetCode problems and provides natural tree visualization.
     * Handles wide trees better than deep recursive approaches.
     * 
     * Time Complexity: O(n) - each node processed once
     * Space Complexity: O(w) - queue size proportional to maximum width
     * 
     * Best when: Wide trees, avoiding recursion, LeetCode format compatibility
     * Worst when: Deep narrow trees, prefer recursive solutions, compact encoding needed
     */
    std::string serializeLevelOrder(TreeNode* root);
    TreeNode* deserializeLevelOrder(std::string data);

    /**
     * Approach 3: Postorder DFS for Minimal Encoding
     * 
     * Use postorder traversal to create compact representation.
     * 
     * Reasoning: Postorder visits children before parent, enabling compact encoding
     * for certain tree structures. In postorder, we can sometimes omit null markers
     * if we encode tree structure information differently (e.g., using parentheses
     * or length prefixes). This approach demonstrates how traversal order affects
     * serialization efficiency. While more complex, it can produce shorter strings
     * for specific tree patterns and provides educational value about tree encoding.
     * 
     * Time Complexity: O(n) - visit each node once
     * Space Complexity: O(h) - recursion stack depth
     * 
     * Best when: Compact encoding important, educational purposes, specific tree structures
     * Worst when: Simplicity preferred, general-purpose solution needed, debugging required
     */
    std::string serializePostorder(TreeNode* root);
    TreeNode* deserializePostorder(std::string data);

    /**
     * Approach 4: Inorder with Structure Information
     * 
     * Combine inorder values with explicit structure encoding.
     * 
     * Reasoning: Inorder traversal alone loses structure information (multiple trees
     * can have same inorder sequence), so we must encode structure separately. Use
     * inorder for values and additional encoding for tree shape (e.g., parentheses
     * notation, preorder structure, or explicit parent-child relationships). This
     * approach demonstrates why inorder alone is insufficient and shows how to combine
     * traversal methods. Educational value in understanding traversal limitations.
     * 
     * Time Complexity: O(n) - multiple traversals needed
     * Space Complexity: O(n) - store values and structure information
     * 
     * Best when: Teaching traversal properties, specific requirements for inorder values
     * Worst when: Efficiency matters, simpler approaches available, standard serialization
     */
    std::string serializeInorder(TreeNode* root);
    TreeNode* deserializeInorder(std::string data);

    /**
     * Approach 5: Compact Binary Encoding
     * 
     * Use binary representation for space-efficient serialization.
     * 
     * Reasoning: Encode tree structure using bits (0 for null, 1 for node) and
     * store values separately in binary format. This achieves maximum space efficiency
     * by eliminating delimiter overhead and using minimal bits per structure element.
     * Serialize tree shape as bit vector and node values as binary data. While complex
     * to implement, this demonstrates advanced serialization techniques used in
     * high-performance systems where space matters.
     * 
     * Time Complexity: O(n) - single pass for each operation
     * Space Complexity: O(n) - compact binary representation
     * 
     * Best when: Space efficiency critical, binary data handling, performance optimization
     * Worst when: Human readability needed, debugging required, simple solutions preferred
     */
    std::string serializeBinary(TreeNode* root);
    TreeNode* deserializeBinary(std::string data);

    /**
     * Approach 6: Recursive Parentheses Notation
     * 
     * Use nested parentheses to represent tree structure naturally.
     * 
     * Reasoning: Encode tree using mathematical expression notation where each
     * subtree is enclosed in parentheses: "root(left_subtree)(right_subtree)".
     * Empty subtrees use empty parentheses "()". This creates human-readable
     * format that naturally represents hierarchical structure. Deserialization
     * uses recursive parsing to match parentheses and rebuild tree. Provides
     * excellent balance between readability and structural clarity.
     * 
     * Time Complexity: O(n) - parse each character/node once
     * Space Complexity: O(h) - recursion stack for parsing depth
     * 
     * Best when: Human readability important, natural tree representation, educational
     * Worst when: Parsing complexity unwanted, compact format needed, simple strings preferred
     */
    std::string serializeParentheses(TreeNode* root);
    TreeNode* deserializeParentheses(std::string data);

private:
    // Helper functions for preorder approach
    void preorderSerialize(TreeNode* node, std::string& result);
    TreeNode* preorderDeserialize(std::vector<std::string>& tokens, int& index);
    
    // Helper functions for postorder approach
    void postorderSerialize(TreeNode* node, std::string& result);
    TreeNode* postorderDeserialize(std::vector<std::string>& tokens, int& index);
    
    // Helper functions for inorder approach
    void inorderSerialize(TreeNode* node, std::vector<int>& values, std::string& structure);
    TreeNode* inorderDeserialize(std::vector<int>& values, std::string& structure, 
                                int& valueIndex, int& structIndex);
    
    // Helper functions for binary encoding
    void serializeBinaryHelper(TreeNode* node, std::string& structure, std::vector<int>& values);
    TreeNode* deserializeBinaryHelper(const std::string& structure, const std::vector<int>& values,
                                     int& structIndex, int& valueIndex);
    
    // Helper functions for parentheses approach
    std::string serializeParenthesesHelper(TreeNode* node);
    TreeNode* deserializeParenthesesHelper(const std::string& data, int& index);
    
    // Utility functions
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string join(const std::vector<std::string>& tokens, char delimiter);
    int parseInt(const std::string& str);
    std::string toString(int value);
    
    // Binary encoding utilities
    std::string encodeInteger(int value);
    int decodeInteger(const std::string& data, int& index);
    void appendBit(std::string& data, bool bit);
    bool readBit(const std::string& data, int& index);
    
    // Constants
    static const std::string NULL_MARKER;
    static const char DELIMITER;
};

}
}