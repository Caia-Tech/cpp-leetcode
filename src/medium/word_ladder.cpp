#include "word_ladder.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

namespace leetcode {
namespace medium {

// Approach 1: Standard BFS with Queue
int WordLadder::ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    // Convert wordList to set for O(1) lookup
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    
    // If endWord not in dictionary, no transformation possible
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;
    
    queue.push(beginWord);
    visited.insert(beginWord);
    
    int level = 1;
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        
        // Process all words at current level
        for (int i = 0; i < levelSize; ++i) {
            std::string currentWord = queue.front();
            queue.pop();
            
            // Check if we reached the target
            if (currentWord == endWord) {
                return level;
            }
            
            // Try all possible single character changes
            for (int pos = 0; pos < currentWord.length(); ++pos) {
                char originalChar = currentWord[pos];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == originalChar) continue;
                    
                    currentWord[pos] = c;
                    
                    // If this word exists in dictionary and not visited
                    if (wordSet.find(currentWord) != wordSet.end() &&
                        visited.find(currentWord) == visited.end()) {
                        visited.insert(currentWord);
                        queue.push(currentWord);
                    }
                }
                // Restore original character
                currentWord[pos] = originalChar;
            }
        }
        ++level;
    }
    
    return 0; // No path found
}

// Approach 2: Bidirectional BFS
int WordLadder::ladderLengthBidirectional(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    // Special case: if begin and end are the same
    if (beginWord == endWord) {
        return 1; // Already at target
    }
    
    std::unordered_set<std::string> beginSet, endSet;
    std::unordered_set<std::string> visited;
    
    beginSet.insert(beginWord);
    endSet.insert(endWord);
    
    int level = 1;
    
    while (!beginSet.empty() && !endSet.empty()) {
        // Always expand the smaller set for efficiency
        if (beginSet.size() > endSet.size()) {
            std::swap(beginSet, endSet);
        }
        
        std::unordered_set<std::string> nextSet;
        
        for (const std::string& word : beginSet) {
            for (int pos = 0; pos < word.length(); ++pos) {
                std::string newWord = word;
                for (char c = 'a'; c <= 'z'; ++c) {
                    newWord[pos] = c;
                    
                    // If we found intersection between two searches
                    if (endSet.find(newWord) != endSet.end()) {
                        return level + 1;
                    }
                    
                    // If valid word and not visited, add to next level
                    if (wordSet.find(newWord) != wordSet.end() &&
                        visited.find(newWord) == visited.end()) {
                        visited.insert(newWord);
                        nextSet.insert(newWord);
                    }
                }
            }
        }
        
        beginSet = nextSet;
        ++level;
    }
    
    return 0;
}

// Approach 3: BFS with Precomputed Adjacent Words
int WordLadder::ladderLengthPrecomputed(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    // Build adjacency list
    std::unordered_map<std::string, std::vector<std::string>> adjList;
    buildAdjacencyList(wordList, adjList);
    
    // Add beginWord to adjacency list if not present
    if (adjList.find(beginWord) == adjList.end()) {
        std::vector<std::string> allWords = wordList;
        allWords.push_back(beginWord);
        adjList.clear();
        buildAdjacencyList(allWords, adjList);
    }
    
    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;
    
    queue.push(beginWord);
    visited.insert(beginWord);
    
    int level = 1;
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        
        for (int i = 0; i < levelSize; ++i) {
            std::string currentWord = queue.front();
            queue.pop();
            
            if (currentWord == endWord) {
                return level;
            }
            
            // Use precomputed neighbors
            if (adjList.find(currentWord) != adjList.end()) {
                for (const std::string& neighbor : adjList[currentWord]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        queue.push(neighbor);
                    }
                }
            }
        }
        ++level;
    }
    
    return 0;
}

// Approach 4: BFS with Pattern Matching
int WordLadder::ladderLengthPatternMatching(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    // Build pattern map
    std::unordered_map<std::string, std::vector<std::string>> patternMap;
    buildPatternMap(wordList, patternMap);
    
    // Add beginWord patterns if not in wordList
    if (wordSet.find(beginWord) == wordSet.end()) {
        std::vector<std::string> patterns = getPatterns(beginWord);
        for (const std::string& pattern : patterns) {
            patternMap[pattern].push_back(beginWord);
        }
    }
    
    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;
    
    queue.push(beginWord);
    visited.insert(beginWord);
    
    int level = 1;
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        
        for (int i = 0; i < levelSize; ++i) {
            std::string currentWord = queue.front();
            queue.pop();
            
            if (currentWord == endWord) {
                return level;
            }
            
            // Get all patterns for current word
            std::vector<std::string> patterns = getPatterns(currentWord);
            for (const std::string& pattern : patterns) {
                if (patternMap.find(pattern) != patternMap.end()) {
                    for (const std::string& neighbor : patternMap[pattern]) {
                        if (neighbor != currentWord && visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            queue.push(neighbor);
                        }
                    }
                }
            }
        }
        ++level;
    }
    
    return 0;
}

// Approach 5: A* Search with Heuristic
int WordLadder::ladderLengthAStar(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> pq;
    std::unordered_map<std::string, int> visited; // word -> best g value seen
    
    int heuristic = hammingDistance(beginWord, endWord);
    pq.push(AStarNode(beginWord, 0, heuristic));
    visited[beginWord] = 0;
    
    while (!pq.empty()) {
        AStarNode current = pq.top();
        pq.pop();
        
        if (current.word == endWord) {
            return current.g + 1; // +1 because we count words, not edges
        }
        
        // Skip if we've found a better path to this word
        if (visited.find(current.word) != visited.end() && visited[current.word] < current.g) {
            continue;
        }
        
        // Generate neighbors
        for (int pos = 0; pos < current.word.length(); ++pos) {
            std::string newWord = current.word;
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == current.word[pos]) continue;
                
                newWord[pos] = c;
                
                if (wordSet.find(newWord) != wordSet.end()) {
                    int newG = current.g + 1;
                    
                    // Only proceed if we haven't visited or found better path
                    if (visited.find(newWord) == visited.end() || visited[newWord] > newG) {
                        visited[newWord] = newG;
                        int h = hammingDistance(newWord, endWord);
                        pq.push(AStarNode(newWord, newG, h));
                    }
                }
            }
        }
    }
    
    return 0;
}

// Approach 6: Level-Order BFS with Size Tracking
int WordLadder::ladderLengthLevelOrder(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }
    
    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;
    
    queue.push(beginWord);
    visited.insert(beginWord);
    
    int level = 1;
    
    while (!queue.empty()) {
        int currentLevelSize = queue.size();
        
        // Process entire current level
        for (int i = 0; i < currentLevelSize; ++i) {
            std::string currentWord = queue.front();
            queue.pop();
            
            // Found target
            if (currentWord == endWord) {
                return level;
            }
            
            // Add all valid neighbors to next level
            for (int pos = 0; pos < currentWord.length(); ++pos) {
                char originalChar = currentWord[pos];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == originalChar) continue;
                    
                    currentWord[pos] = c;
                    
                    if (wordSet.find(currentWord) != wordSet.end() &&
                        visited.find(currentWord) == visited.end()) {
                        visited.insert(currentWord);
                        queue.push(currentWord);
                    }
                }
                currentWord[pos] = originalChar;
            }
        }
        
        ++level; // Move to next level
    }
    
    return 0;
}

// Helper function implementations

bool WordLadder::isAdjacent(const std::string& word1, const std::string& word2) {
    if (word1.length() != word2.length()) return false;
    
    int differences = 0;
    for (int i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            differences++;
            if (differences > 1) return false;
        }
    }
    return differences == 1;
}

std::vector<std::string> WordLadder::getNeighbors(const std::string& word, const std::unordered_set<std::string>& wordSet) {
    std::vector<std::string> neighbors;
    
    for (int pos = 0; pos < word.length(); ++pos) {
        std::string newWord = word;
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c == word[pos]) continue;
            
            newWord[pos] = c;
            if (wordSet.find(newWord) != wordSet.end()) {
                neighbors.push_back(newWord);
            }
        }
    }
    
    return neighbors;
}

void WordLadder::buildAdjacencyList(const std::vector<std::string>& wordList, 
                                   std::unordered_map<std::string, std::vector<std::string>>& adjList) {
    for (int i = 0; i < wordList.size(); ++i) {
        for (int j = i + 1; j < wordList.size(); ++j) {
            if (isAdjacent(wordList[i], wordList[j])) {
                adjList[wordList[i]].push_back(wordList[j]);
                adjList[wordList[j]].push_back(wordList[i]);
            }
        }
    }
}

void WordLadder::buildPatternMap(const std::vector<std::string>& wordList,
                                std::unordered_map<std::string, std::vector<std::string>>& patternMap) {
    for (const std::string& word : wordList) {
        std::vector<std::string> patterns = getPatterns(word);
        for (const std::string& pattern : patterns) {
            patternMap[pattern].push_back(word);
        }
    }
}

std::vector<std::string> WordLadder::getPatterns(const std::string& word) {
    std::vector<std::string> patterns;
    for (int i = 0; i < word.length(); ++i) {
        std::string pattern = word;
        pattern[i] = '*';
        patterns.push_back(pattern);
    }
    return patterns;
}

int WordLadder::hammingDistance(const std::string& word1, const std::string& word2) {
    int distance = 0;
    for (int i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            distance++;
        }
    }
    return distance;
}

}
}