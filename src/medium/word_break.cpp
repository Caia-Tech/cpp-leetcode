#include "word_break.h"

namespace leetcode {
namespace medium {

bool WordBreak::wordBreakDP(std::string s, std::vector<std::string>& wordDict) {
    int n = s.length();
    std::unordered_set<std::string> wordSet(wordDict.begin(), wordDict.end());
    
    // dp[i] represents whether s[0...i-1] can be segmented
    std::vector<bool> dp(n + 1, false);
    dp[0] = true; // Empty string can always be segmented
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            // If s[0...j-1] can be segmented and s[j...i-1] is in dictionary
            if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                dp[i] = true;
                break; // Found one valid segmentation for position i
            }
        }
    }
    
    return dp[n];
}

bool WordBreak::wordBreakMemo(std::string s, std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> wordSet(wordDict.begin(), wordDict.end());
    std::unordered_map<int, bool> memo;
    
    return memoHelper(s, 0, wordSet, memo);
}

bool WordBreak::wordBreakBFS(std::string s, std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> wordSet(wordDict.begin(), wordDict.end());
    std::queue<int> queue;
    std::vector<bool> visited(s.length(), false);
    
    queue.push(0);
    
    while (!queue.empty()) {
        int start = queue.front();
        queue.pop();
        
        if (visited[start]) {
            continue;
        }
        visited[start] = true;
        
        for (int end = start + 1; end <= s.length(); ++end) {
            if (wordSet.count(s.substr(start, end - start))) {
                if (end == s.length()) {
                    return true; // Reached the end
                }
                queue.push(end);
            }
        }
    }
    
    return false;
}

bool WordBreak::wordBreakTrie(std::string s, std::vector<std::string>& wordDict) {
    TrieNode* root = new TrieNode();
    buildTrie(root, wordDict);
    
    int n = s.length();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;
    
    for (int i = 0; i < n; ++i) {
        if (!dp[i]) continue;
        
        // Find all words starting at position i using trie
        std::vector<int> wordEnds = findWordsStartingAt(root, s, i);
        
        for (int end : wordEnds) {
            dp[end] = true;
        }
    }
    
    bool result = dp[n];
    delete root;
    return result;
}

bool WordBreak::wordBreakBacktrack(std::string s, std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> wordSet(wordDict.begin(), wordDict.end());
    std::unordered_set<int> visited; // For pruning failed positions
    
    return backtrackHelper(s, 0, wordSet, visited);
}

bool WordBreak::wordBreakSlidingWindow(std::string s, std::vector<std::string>& wordDict) {
    int n = s.length();
    std::unordered_set<std::string> wordSet(wordDict.begin(), wordDict.end());
    std::vector<bool> canBreak(n + 1, false);
    canBreak[0] = true;
    
    // Find maximum word length for optimization
    int maxWordLen = 0;
    for (const std::string& word : wordDict) {
        maxWordLen = std::max(maxWordLen, static_cast<int>(word.length()));
    }
    
    for (int i = 1; i <= n; ++i) {
        // Use sliding window of different sizes
        for (int len = 1; len <= std::min(i, maxWordLen); ++len) {
            int start = i - len;
            if (canBreak[start] && wordSet.count(s.substr(start, len))) {
                canBreak[i] = true;
                break; // Found valid segmentation for position i
            }
        }
    }
    
    return canBreak[n];
}

bool WordBreak::memoHelper(const std::string& s, int start, const std::unordered_set<std::string>& wordSet,
                          std::unordered_map<int, bool>& memo) {
    // Base case: reached end of string
    if (start == s.length()) {
        return true;
    }
    
    // Check memoization
    if (memo.count(start)) {
        return memo[start];
    }
    
    // Try all possible words starting at current position
    for (int end = start + 1; end <= s.length(); ++end) {
        std::string word = s.substr(start, end - start);
        
        if (wordSet.count(word) && memoHelper(s, end, wordSet, memo)) {
            memo[start] = true;
            return true;
        }
    }
    
    memo[start] = false;
    return false;
}

bool WordBreak::backtrackHelper(const std::string& s, int start, const std::unordered_set<std::string>& wordSet,
                               std::unordered_set<int>& visited) {
    // Base case: reached end of string
    if (start == s.length()) {
        return true;
    }
    
    // Pruning: if we've already failed from this position, skip
    if (visited.count(start)) {
        return false;
    }
    
    // Try all possible words starting at current position
    for (int end = start + 1; end <= s.length(); ++end) {
        std::string word = s.substr(start, end - start);
        
        if (wordSet.count(word)) {
            if (backtrackHelper(s, end, wordSet, visited)) {
                return true;
            }
        }
    }
    
    // Mark this position as visited (failed)
    visited.insert(start);
    return false;
}

void WordBreak::buildTrie(TrieNode* root, const std::vector<std::string>& wordDict) {
    for (const std::string& word : wordDict) {
        TrieNode* current = root;
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        
        current->isEndOfWord = true;
    }
}

std::vector<int> WordBreak::findWordsStartingAt(TrieNode* root, const std::string& s, int start) {
    std::vector<int> wordEnds;
    TrieNode* current = root;
    
    for (int i = start; i < s.length(); ++i) {
        char c = s[i];
        
        if (current->children.find(c) == current->children.end()) {
            break; // No more matching words possible
        }
        
        current = current->children[c];
        
        if (current->isEndOfWord) {
            wordEnds.push_back(i + 1); // End position (exclusive)
        }
    }
    
    return wordEnds;
}

}
}