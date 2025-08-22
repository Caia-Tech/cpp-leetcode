#include "longest_common_prefix.h"
#include <algorithm>

namespace leetcode {
namespace easy {

std::string LongestCommonPrefix::longestCommonPrefixVertical(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    
    // Find the minimum length to avoid out-of-bounds access
    int minLen = strs[0].length();
    for (const std::string& str : strs) {
        minLen = std::min(minLen, static_cast<int>(str.length()));
    }
    
    // Compare character by character at each position
    for (int i = 0; i < minLen; ++i) {
        char currentChar = strs[0][i];
        
        // Check if all strings have the same character at position i
        for (int j = 1; j < strs.size(); ++j) {
            if (strs[j][i] != currentChar) {
                // Mismatch found, return prefix up to this point
                return strs[0].substr(0, i);
            }
        }
    }
    
    // All characters matched up to minimum length
    return strs[0].substr(0, minLen);
}

std::string LongestCommonPrefix::longestCommonPrefixHorizontal(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    
    std::string prefix = strs[0];
    
    // Compare prefix with each subsequent string
    for (int i = 1; i < strs.size(); ++i) {
        int j = 0;
        
        // Find the common prefix between current prefix and strs[i]
        while (j < prefix.length() && j < strs[i].length() && 
               prefix[j] == strs[i][j]) {
            j++;
        }
        
        // Update prefix to the common part
        prefix = prefix.substr(0, j);
        
        // Early termination: if prefix becomes empty, no need to continue
        if (prefix.empty()) {
            return "";
        }
    }
    
    return prefix;
}

std::string LongestCommonPrefix::longestCommonPrefixDivideConquer(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    return divideConquerHelper(strs, 0, strs.size() - 1);
}

std::string LongestCommonPrefix::divideConquerHelper(std::vector<std::string>& strs, int left, int right) {
    if (left == right) {
        // Base case: single string
        return strs[left];
    }
    
    int mid = left + (right - left) / 2;
    
    // Recursively find LCP of left and right halves
    std::string leftLCP = divideConquerHelper(strs, left, mid);
    std::string rightLCP = divideConquerHelper(strs, mid + 1, right);
    
    // Find LCP of the two results
    return findLCP(leftLCP, rightLCP);
}

std::string LongestCommonPrefix::findLCP(const std::string& left, const std::string& right) {
    int minLen = std::min(left.length(), right.length());
    
    for (int i = 0; i < minLen; ++i) {
        if (left[i] != right[i]) {
            return left.substr(0, i);
        }
    }
    
    return left.substr(0, minLen);
}

std::string LongestCommonPrefix::longestCommonPrefixBinarySearch(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    
    // Find the length of the shortest string
    int minLen = strs[0].length();
    for (const std::string& str : strs) {
        minLen = std::min(minLen, static_cast<int>(str.length()));
    }
    
    // Binary search on the length
    int low = 0, high = minLen;
    
    while (low < high) {
        int mid = low + (high - low + 1) / 2;  // Use upper mid to avoid infinite loop
        
        if (isCommonPrefix(strs, mid)) {
            low = mid;  // mid length is valid, try longer
        } else {
            high = mid - 1;  // mid length is invalid, try shorter
        }
    }
    
    return strs[0].substr(0, low);
}

bool LongestCommonPrefix::isCommonPrefix(std::vector<std::string>& strs, int length) {
    std::string prefix = strs[0].substr(0, length);
    
    for (int i = 1; i < strs.size(); ++i) {
        // Check if strs[i] starts with prefix
        if (strs[i].length() < length || strs[i].substr(0, length) != prefix) {
            return false;
        }
    }
    
    return true;
}

std::string LongestCommonPrefix::longestCommonPrefixTrie(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    
    TrieNode* root = new TrieNode();
    
    // Build trie with all strings
    for (const std::string& str : strs) {
        insertTrie(root, str);
    }
    
    // Find longest common prefix in trie
    std::string result = searchLCPInTrie(root, strs[0]);
    
    // Clean up memory
    deleteTrie(root);
    
    return result;
}

void LongestCommonPrefix::insertTrie(TrieNode* root, const std::string& str) {
    TrieNode* current = root;
    
    for (char c : str) {
        int index = c - 'a';
        
        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
            current->childCount++;
        }
        
        current = current->children[index];
    }
    
    current->isEndOfWord = true;
}

std::string LongestCommonPrefix::searchLCPInTrie(TrieNode* root, const std::string& firstStr) {
    TrieNode* current = root;
    std::string prefix = "";
    
    for (char c : firstStr) {
        int index = c - 'a';
        
        // Check if this node has only one child and it's not end of any string
        if (current->childCount != 1 || current->isEndOfWord) {
            break;
        }
        
        current = current->children[index];
        prefix += c;
    }
    
    return prefix;
}

void LongestCommonPrefix::deleteTrie(TrieNode* root) {
    if (root == nullptr) return;
    
    for (int i = 0; i < TrieNode::ALPHABET_SIZE; i++) {
        deleteTrie(root->children[i]);
    }
    
    delete root;
}

std::string LongestCommonPrefix::longestCommonPrefixSort(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    
    // Create a copy to avoid modifying input (unless we want to modify in place)
    std::vector<std::string> sortedStrs = strs;
    
    // Sort the strings lexicographically
    std::sort(sortedStrs.begin(), sortedStrs.end());
    
    // After sorting, we only need to compare first and last strings
    // The common prefix of these two is the common prefix of all strings
    std::string first = sortedStrs.front();
    std::string last = sortedStrs.back();
    
    int i = 0;
    while (i < first.length() && i < last.length() && first[i] == last[i]) {
        i++;
    }
    
    return first.substr(0, i);
}

}
}