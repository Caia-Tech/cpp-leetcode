#include "word_search.h"
#include <algorithm>
#include <unordered_map>

namespace leetcode {
namespace medium {

// ============================================================================
// Approach 1: DFS with Backtracking (Classic Solution)
// ============================================================================

bool WordSearch::exist(std::vector<std::vector<char>>& board, std::string word) {
    if (board.empty() || board[0].empty() || word.empty()) {
        return false;
    }
    
    int m = board.size();
    int n = board[0].size();
    
    // Try starting from each cell
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dfs(board, word, i, j, 0)) {
                return true;
            }
        }
    }
    
    return false;
}

bool WordSearch::dfs(std::vector<std::vector<char>>& board, const std::string& word,
                    int row, int col, int index) {
    // Base case: found the complete word
    if (index == word.length()) {
        return true;
    }
    
    // Boundary check and character match
    if (!isValid(row, col, board.size(), board[0].size()) || 
        board[row][col] != word[index]) {
        return false;
    }
    
    // Mark current cell as visited
    char temp = board[row][col];
    board[row][col] = '#';  // Use special character to mark visited
    
    // Explore all 4 directions
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto& dir : dirs) {
        if (dfs(board, word, row + dir[0], col + dir[1], index + 1)) {
            board[row][col] = temp;  // Restore before returning
            return true;
        }
    }
    
    // Backtrack: restore the cell
    board[row][col] = temp;
    return false;
}

bool WordSearch::isValid(int row, int col, int m, int n) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

// ============================================================================
// Approach 2: BFS with State Tracking (Level-by-level Search)
// ============================================================================

bool WordSearchBFS::exist(std::vector<std::vector<char>>& board, std::string word) {
    if (board.empty() || board[0].empty() || word.empty()) {
        return false;
    }
    
    int m = board.size();
    int n = board[0].size();
    std::queue<State> q;
    
    // Initialize queue with all possible starting positions
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0]) {
                State state(i, j, 0);
                state.visited.insert(encode(i, j, n));
                q.push(state);
            }
        }
    }
    
    // BFS exploration
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        // Check if we've found the complete word
        if (curr.index == word.length() - 1) {
            return true;
        }
        
        // Explore neighbors
        for (auto& dir : dirs) {
            int newRow = curr.row + dir[0];
            int newCol = curr.col + dir[1];
            int encoded = encode(newRow, newCol, n);
            
            if (isValid(newRow, newCol, m, n) &&
                curr.visited.find(encoded) == curr.visited.end() &&
                board[newRow][newCol] == word[curr.index + 1]) {
                
                State newState(newRow, newCol, curr.index + 1);
                newState.visited = curr.visited;  // Copy visited set
                newState.visited.insert(encoded);
                q.push(newState);
            }
        }
    }
    
    return false;
}

int WordSearchBFS::encode(int row, int col, int n) {
    return row * n + col;
}

bool WordSearchBFS::isValid(int row, int col, int m, int n) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

// ============================================================================
// Approach 3: Iterative DFS with Stack (Non-recursive)
// ============================================================================

bool WordSearchIterative::exist(std::vector<std::vector<char>>& board, std::string word) {
    if (board.empty() || board[0].empty() || word.empty()) {
        return false;
    }
    
    int m = board.size();
    int n = board[0].size();
    
    // Try each starting position
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] != word[0]) continue;
            
            std::stack<DFSState> stack;
            stack.push(DFSState(i, j, 0));
            
            // Mark starting cell
            char original = board[i][j];
            board[i][j] = '#';
            
            while (!stack.empty()) {
                DFSState& state = stack.top();
                
                // Check if we found the word
                if (state.index == word.length() - 1) {
                    // Restore board and return
                    board[i][j] = original;
                    // Clean up any other marked cells
                    while (!stack.empty()) {
                        DFSState s = stack.top();
                        stack.pop();
                        if (s.index > 0) {
                            board[s.row][s.col] = word[s.index];
                        }
                    }
                    return true;
                }
                
                // Try next direction
                int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                bool found = false;
                
                while (state.direction < 4) {
                    int newRow = state.row + dirs[state.direction][0];
                    int newCol = state.col + dirs[state.direction][1];
                    state.direction++;
                    
                    if (isValid(newRow, newCol, m, n) &&
                        board[newRow][newCol] == word[state.index + 1]) {
                        
                        // Found next character
                        board[newRow][newCol] = '#';
                        stack.push(DFSState(newRow, newCol, state.index + 1));
                        found = true;
                        break;
                    }
                }
                
                // Backtrack if no valid direction found
                if (!found) {
                    stack.pop();
                    if (state.index > 0) {
                        board[state.row][state.col] = word[state.index];
                    }
                }
            }
            
            // Restore starting cell
            board[i][j] = original;
        }
    }
    
    return false;
}

bool WordSearchIterative::isValid(int row, int col, int m, int n) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

// ============================================================================
// Approach 4: Optimized with Pruning (Enhanced DFS)
// ============================================================================

bool WordSearchOptimized::exist(std::vector<std::vector<char>>& board, std::string word) {
    if (board.empty() || board[0].empty() || word.empty()) {
        return false;
    }
    
    // Optimization 1: Check if board has enough characters
    if (!canFormWord(board, word)) {
        return false;
    }
    
    // Optimization 2: Reverse word if last char is rarer
    std::unordered_map<char, int> boardFreq;
    for (const auto& row : board) {
        for (char c : row) {
            boardFreq[c]++;
        }
    }
    
    if (boardFreq[word.back()] < boardFreq[word[0]]) {
        std::reverse(word.begin(), word.end());
    }
    
    int m = board.size();
    int n = board[0].size();
    
    // Try starting from each cell
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dfsOptimized(board, word, i, j, 0)) {
                return true;
            }
        }
    }
    
    return false;
}

bool WordSearchOptimized::canFormWord(std::vector<std::vector<char>>& board, const std::string& word) {
    std::unordered_map<char, int> boardFreq, wordFreq;
    
    for (const auto& row : board) {
        for (char c : row) {
            boardFreq[c]++;
        }
    }
    
    for (char c : word) {
        wordFreq[c]++;
    }
    
    for (const auto& [ch, count] : wordFreq) {
        if (boardFreq[ch] < count) {
            return false;
        }
    }
    
    return true;
}

bool WordSearchOptimized::dfsOptimized(std::vector<std::vector<char>>& board, const std::string& word,
                                       int row, int col, int index) {
    if (index == word.length()) {
        return true;
    }
    
    if (!isValid(row, col, board.size(), board[0].size()) || 
        board[row][col] != word[index]) {
        return false;
    }
    
    // Use XOR to mark visited (preserves original value)
    board[row][col] ^= 256;
    
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto& dir : dirs) {
        if (dfsOptimized(board, word, row + dir[0], col + dir[1], index + 1)) {
            board[row][col] ^= 256;  // Restore
            return true;
        }
    }
    
    board[row][col] ^= 256;  // Restore
    return false;
}

bool WordSearchOptimized::isValid(int row, int col, int m, int n) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

// ============================================================================
// Approach 5: Bidirectional Search (Search from Both Ends)
// ============================================================================

bool WordSearchBidirectional::exist(std::vector<std::vector<char>>& board, std::string word) {
    if (board.empty() || board[0].empty() || word.empty()) {
        return false;
    }
    
    if (word.length() == 1) {
        // For single character, just check if it exists
        for (const auto& row : board) {
            for (char c : row) {
                if (c == word[0]) return true;
            }
        }
        return false;
    }
    
    return searchFromBothEnds(board, word);
}

bool WordSearchBidirectional::searchFromBothEnds(std::vector<std::vector<char>>& board, const std::string& word) {
    // Bidirectional search is complex for this problem due to path tracking
    // Fall back to standard DFS for now
    WordSearch standardDFS;
    return standardDFS.exist(board, word);
}

bool WordSearchBidirectional::expandSearch(std::vector<std::vector<char>>& board, const std::string& word,
                                          std::unordered_set<int>& frontier, std::unordered_set<int>& otherFrontier,
                                          int startIdx, int endIdx, bool forward) {
    int m = board.size();
    int n = board[0].size();
    std::unordered_set<int> newFrontier;
    
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int targetIdx = forward ? startIdx + 1 : endIdx - 1;
    
    if (targetIdx < 0 || targetIdx >= word.length()) {
        return false;
    }
    
    for (int encoded : frontier) {
        auto [row, col] = decode(encoded, n);
        
        for (auto& dir : dirs) {
            int newRow = row + dir[0];
            int newCol = col + dir[1];
            
            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                board[newRow][newCol] == word[targetIdx]) {
                
                int newEncoded = encode(newRow, newCol, n);
                
                // Check if we've met the other frontier
                if (otherFrontier.count(newEncoded)) {
                    return true;
                }
                
                newFrontier.insert(newEncoded);
            }
        }
    }
    
    frontier = std::move(newFrontier);
    return false;
}

int WordSearchBidirectional::encode(int row, int col, int n) {
    return row * n + col;
}

std::pair<int, int> WordSearchBidirectional::decode(int encoded, int n) {
    return {encoded / n, encoded % n};
}

// ============================================================================
// Approach 6: Trie-based Solution (Multiple Word Search)
// ============================================================================

void WordSearchTrie::Trie::insert(const std::string& word) {
    TrieNode* curr = root;
    for (char c : word) {
        int idx = static_cast<unsigned char>(c);
        if (!curr->children[idx]) {
            curr->children[idx] = new TrieNode();
        }
        curr = curr->children[idx];
    }
    curr->isEnd = true;
}

bool WordSearchTrie::exist(std::vector<std::vector<char>>& board, std::string word) {
    if (board.empty() || board[0].empty() || word.empty()) {
        return false;
    }
    
    // Build trie with the word
    Trie trie;
    trie.insert(word);
    
    int m = board.size();
    int n = board[0].size();
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    
    // Try starting from each cell
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (searchWithTrie(board, trie.root, i, j, visited)) {
                return true;
            }
        }
    }
    
    return false;
}

bool WordSearchTrie::searchWithTrie(std::vector<std::vector<char>>& board, TrieNode* node,
                                    int row, int col, std::vector<std::vector<bool>>& visited) {
    if (!isValid(row, col, board.size(), board[0].size()) || visited[row][col]) {
        return false;
    }
    
    char c = board[row][col];
    int idx = static_cast<unsigned char>(c);
    
    if (!node->children[idx]) {
        return false;
    }
    
    node = node->children[idx];
    
    if (node->isEnd) {
        return true;
    }
    
    visited[row][col] = true;
    
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto& dir : dirs) {
        if (searchWithTrie(board, node, row + dir[0], col + dir[1], visited)) {
            visited[row][col] = false;
            return true;
        }
    }
    
    visited[row][col] = false;
    return false;
}

bool WordSearchTrie::isValid(int row, int col, int m, int n) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

}
}