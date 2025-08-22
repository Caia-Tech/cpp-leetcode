#include "serialize_deserialize_binary_tree.h"
#include <iostream>
#include <algorithm>

namespace leetcode {
namespace hard {

// Constants
const std::string SerializeDeserializeBinaryTree::NULL_MARKER = "null";
const char SerializeDeserializeBinaryTree::DELIMITER = ',';

// Approach 1: Preorder DFS
std::string SerializeDeserializeBinaryTree::serializePreorder(TreeNode* root) {
    std::string result;
    preorderSerialize(root, result);
    if (!result.empty() && result.back() == DELIMITER) {
        result.pop_back(); // Remove trailing delimiter
    }
    return result;
}

void SerializeDeserializeBinaryTree::preorderSerialize(TreeNode* node, std::string& result) {
    if (!node) {
        result += NULL_MARKER + DELIMITER;
        return;
    }
    
    result += toString(node->val) + DELIMITER;
    preorderSerialize(node->left, result);
    preorderSerialize(node->right, result);
}

TreeNode* SerializeDeserializeBinaryTree::deserializePreorder(std::string data) {
    if (data.empty()) return nullptr;
    
    std::vector<std::string> tokens = split(data, DELIMITER);
    int index = 0;
    return preorderDeserialize(tokens, index);
}

TreeNode* SerializeDeserializeBinaryTree::preorderDeserialize(std::vector<std::string>& tokens, int& index) {
    if (index >= tokens.size() || tokens[index] == NULL_MARKER) {
        ++index;
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(parseInt(tokens[index++]));
    node->left = preorderDeserialize(tokens, index);
    node->right = preorderDeserialize(tokens, index);
    
    return node;
}

// Approach 2: Level Order BFS
std::string SerializeDeserializeBinaryTree::serializeLevelOrder(TreeNode* root) {
    if (!root) return "";
    
    std::vector<std::string> result;
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.pop();
        
        if (node) {
            result.push_back(toString(node->val));
            queue.push(node->left);
            queue.push(node->right);
        } else {
            result.push_back(NULL_MARKER);
        }
    }
    
    // Remove trailing nulls
    while (!result.empty() && result.back() == NULL_MARKER) {
        result.pop_back();
    }
    
    return join(result, DELIMITER);
}

TreeNode* SerializeDeserializeBinaryTree::deserializeLevelOrder(std::string data) {
    if (data.empty()) return nullptr;
    
    std::vector<std::string> tokens = split(data, DELIMITER);
    if (tokens.empty() || tokens[0] == NULL_MARKER) return nullptr;
    
    TreeNode* root = new TreeNode(parseInt(tokens[0]));
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    for (int i = 1; i < tokens.size(); i += 2) {
        TreeNode* parent = queue.front();
        queue.pop();
        
        // Process left child
        if (i < tokens.size() && tokens[i] != NULL_MARKER) {
            parent->left = new TreeNode(parseInt(tokens[i]));
            queue.push(parent->left);
        }
        
        // Process right child
        if (i + 1 < tokens.size() && tokens[i + 1] != NULL_MARKER) {
            parent->right = new TreeNode(parseInt(tokens[i + 1]));
            queue.push(parent->right);
        }
    }
    
    return root;
}

// Approach 3: Postorder DFS
std::string SerializeDeserializeBinaryTree::serializePostorder(TreeNode* root) {
    std::string result;
    postorderSerialize(root, result);
    if (!result.empty() && result.back() == DELIMITER) {
        result.pop_back();
    }
    return result;
}

void SerializeDeserializeBinaryTree::postorderSerialize(TreeNode* node, std::string& result) {
    if (!node) {
        result += NULL_MARKER + DELIMITER;
        return;
    }
    
    postorderSerialize(node->left, result);
    postorderSerialize(node->right, result);
    result += toString(node->val) + DELIMITER;
}

TreeNode* SerializeDeserializeBinaryTree::deserializePostorder(std::string data) {
    if (data.empty()) return nullptr;
    
    std::vector<std::string> tokens = split(data, DELIMITER);
    int index = tokens.size() - 1;
    return postorderDeserialize(tokens, index);
}

TreeNode* SerializeDeserializeBinaryTree::postorderDeserialize(std::vector<std::string>& tokens, int& index) {
    if (index < 0 || tokens[index] == NULL_MARKER) {
        --index;
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(parseInt(tokens[index--]));
    node->right = postorderDeserialize(tokens, index);
    node->left = postorderDeserialize(tokens, index);
    
    return node;
}

// Approach 4: Inorder with Structure Information
std::string SerializeDeserializeBinaryTree::serializeInorder(TreeNode* root) {
    std::vector<int> values;
    std::string structure;
    inorderSerialize(root, values, structure);
    
    // Combine values and structure
    std::string result = "VALUES:";
    for (int i = 0; i < values.size(); ++i) {
        result += toString(values[i]);
        if (i < values.size() - 1) result += DELIMITER;
    }
    result += ";STRUCTURE:" + structure;
    
    return result;
}

void SerializeDeserializeBinaryTree::inorderSerialize(TreeNode* node, std::vector<int>& values, std::string& structure) {
    if (!node) {
        structure += "0"; // 0 for null
        return;
    }
    
    structure += "1"; // 1 for node
    inorderSerialize(node->left, values, structure);
    values.push_back(node->val);
    inorderSerialize(node->right, values, structure);
}

TreeNode* SerializeDeserializeBinaryTree::deserializeInorder(std::string data) {
    if (data.empty()) return nullptr;
    
    // Parse values and structure
    size_t valuesPos = data.find("VALUES:");
    size_t structPos = data.find(";STRUCTURE:");
    
    if (valuesPos == std::string::npos || structPos == std::string::npos) {
        return nullptr;
    }
    
    std::string valuesStr = data.substr(valuesPos + 7, structPos - valuesPos - 7);
    std::string structStr = data.substr(structPos + 11);
    
    std::vector<int> values;
    if (!valuesStr.empty()) {
        std::vector<std::string> valueTokens = split(valuesStr, DELIMITER);
        for (const std::string& token : valueTokens) {
            values.push_back(parseInt(token));
        }
    }
    
    int valueIndex = 0, structIndex = 0;
    return inorderDeserialize(values, structStr, valueIndex, structIndex);
}

TreeNode* SerializeDeserializeBinaryTree::inorderDeserialize(std::vector<int>& values, std::string& structure, 
                                                           int& valueIndex, int& structIndex) {
    if (structIndex >= structure.length() || structure[structIndex] == '0') {
        ++structIndex;
        return nullptr;
    }
    
    ++structIndex; // consume '1'
    TreeNode* node = new TreeNode(0); // temporary value
    
    node->left = inorderDeserialize(values, structure, valueIndex, structIndex);
    node->val = values[valueIndex++];
    node->right = inorderDeserialize(values, structure, valueIndex, structIndex);
    
    return node;
}

// Approach 5: Compact Binary Encoding
std::string SerializeDeserializeBinaryTree::serializeBinary(TreeNode* root) {
    std::string structure;
    std::vector<int> values;
    serializeBinaryHelper(root, structure, values);
    
    // Encode structure as bits and values as binary
    std::string result = "STRUCT:" + structure + ";VALUES:";
    for (int value : values) {
        result += encodeInteger(value);
    }
    
    return result;
}

void SerializeDeserializeBinaryTree::serializeBinaryHelper(TreeNode* node, std::string& structure, std::vector<int>& values) {
    if (!node) {
        appendBit(structure, false);
        return;
    }
    
    appendBit(structure, true);
    values.push_back(node->val);
    serializeBinaryHelper(node->left, structure, values);
    serializeBinaryHelper(node->right, structure, values);
}

TreeNode* SerializeDeserializeBinaryTree::deserializeBinary(std::string data) {
    if (data.empty()) return nullptr;
    
    // Parse structure and values
    size_t structPos = data.find("STRUCT:");
    size_t valuesPos = data.find(";VALUES:");
    
    if (structPos == std::string::npos || valuesPos == std::string::npos) {
        return nullptr;
    }
    
    std::string structStr = data.substr(structPos + 7, valuesPos - structPos - 7);
    std::string valuesStr = data.substr(valuesPos + 8);
    
    // Decode values
    std::vector<int> values;
    int valueIndex = 0;
    for (int i = 0; i < valuesStr.length(); ) {
        values.push_back(decodeInteger(valuesStr, i));
    }
    
    int structIndex = 0;
    valueIndex = 0;
    return deserializeBinaryHelper(structStr, values, structIndex, valueIndex);
}

TreeNode* SerializeDeserializeBinaryTree::deserializeBinaryHelper(const std::string& structure, const std::vector<int>& values,
                                                                 int& structIndex, int& valueIndex) {
    if (structIndex >= structure.length() || !readBit(structure, structIndex)) {
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(values[valueIndex++]);
    node->left = deserializeBinaryHelper(structure, values, structIndex, valueIndex);
    node->right = deserializeBinaryHelper(structure, values, structIndex, valueIndex);
    
    return node;
}

// Approach 6: Parentheses Notation
std::string SerializeDeserializeBinaryTree::serializeParentheses(TreeNode* root) {
    return serializeParenthesesHelper(root);
}

std::string SerializeDeserializeBinaryTree::serializeParenthesesHelper(TreeNode* node) {
    if (!node) return "()";
    
    std::string result = toString(node->val);
    result += "(" + serializeParenthesesHelper(node->left) + ")";
    result += "(" + serializeParenthesesHelper(node->right) + ")";
    
    return result;
}

TreeNode* SerializeDeserializeBinaryTree::deserializeParentheses(std::string data) {
    if (data.empty() || data == "()") return nullptr;
    
    int index = 0;
    return deserializeParenthesesHelper(data, index);
}

TreeNode* SerializeDeserializeBinaryTree::deserializeParenthesesHelper(const std::string& data, int& index) {
    if (index >= data.length() || data.substr(index, 2) == "()") {
        index += 2; // skip "()"
        return nullptr;
    }
    
    // Parse node value
    int start = index;
    while (index < data.length() && data[index] != '(') {
        ++index;
    }
    
    TreeNode* node = new TreeNode(parseInt(data.substr(start, index - start)));
    
    // Parse left subtree
    ++index; // skip '('
    node->left = deserializeParenthesesHelper(data, index);
    ++index; // skip ')'
    
    // Parse right subtree
    ++index; // skip '('
    node->right = deserializeParenthesesHelper(data, index);
    ++index; // skip ')'
    
    return node;
}

// Utility function implementations
std::vector<std::string> SerializeDeserializeBinaryTree::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(str);
    
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string SerializeDeserializeBinaryTree::join(const std::vector<std::string>& tokens, char delimiter) {
    std::string result;
    for (int i = 0; i < tokens.size(); ++i) {
        result += tokens[i];
        if (i < tokens.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

int SerializeDeserializeBinaryTree::parseInt(const std::string& str) {
    return std::stoi(str);
}

std::string SerializeDeserializeBinaryTree::toString(int value) {
    return std::to_string(value);
}

std::string SerializeDeserializeBinaryTree::encodeInteger(int value) {
    // Simple encoding: convert to 4-byte string
    std::string result(4, '\0');
    result[0] = (value >> 24) & 0xFF;
    result[1] = (value >> 16) & 0xFF;
    result[2] = (value >> 8) & 0xFF;
    result[3] = value & 0xFF;
    return result;
}

int SerializeDeserializeBinaryTree::decodeInteger(const std::string& data, int& index) {
    if (index + 4 > data.length()) return 0;
    
    int value = 0;
    value |= (static_cast<unsigned char>(data[index++]) << 24);
    value |= (static_cast<unsigned char>(data[index++]) << 16);
    value |= (static_cast<unsigned char>(data[index++]) << 8);
    value |= static_cast<unsigned char>(data[index++]);
    
    return value;
}

void SerializeDeserializeBinaryTree::appendBit(std::string& data, bool bit) {
    data += (bit ? '1' : '0');
}

bool SerializeDeserializeBinaryTree::readBit(const std::string& data, int& index) {
    return data[index++] == '1';
}

}
}