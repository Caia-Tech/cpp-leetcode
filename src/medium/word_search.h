#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <stack>

namespace leetcode {
namespace medium {

/**
 * Problem 79: Word Search
 * 
 * Given an m x n grid of characters board and a string word, return true if word
 * exists in the grid.
 * 
 * The word can be constructed from letters of sequentially adjacent cells, where
 * adjacent cells are horizontally or vertically neighboring. The same letter cell
 * may not be used more than once.
 * 
 * Constraints:
 * - m == board.length
 * - n = board[i].length
 * - 1 <= m, n <= 6
 * - 1 <= word.length <= 15
 * - board and word consists of only lowercase and uppercase English letters.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */

/**
 * Approach 1: DFS with Backtracking (Classic Solution)
 * 
 * Use depth-first search with backtracking to explore all possible paths.
 * 
 * Reasoning: This is the classic approach for word search problems. We try each
 * cell as a starting point and use DFS to explore paths. Mark cells as visited
 * during the path and unmark them when backtracking. This ensures we don't reuse
 * cells and explore all possibilities. The key optimization is early termination
 * when a path can't lead to the word. This approach is intuitive and efficient
 * for the given constraints.
 * 
 * Time Complexity: O(m*n*4^L) where L is word length (worst case explores all paths)
 * Space Complexity: O(L) for recursion stack
 * 
 * Best when: Standard solution needed, clear and maintainable code
 * Worst when: Very long words or large grids (though constraints are small)
 */
class WordSearch {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word);
    
private:
    bool dfs(std::vector<std::vector<char>>& board, const std::string& word,
             int row, int col, int index);
    bool isValid(int row, int col, int m, int n);
};

/**
 * Approach 2: BFS with State Tracking (Level-by-level Search)
 * 
 * Use breadth-first search with state to find the word.
 * 
 * Reasoning: While DFS is more natural for this problem, BFS can also work.
 * We maintain states (row, col, index, visited_set) in the queue. This explores
 * all paths of the same length before moving to longer paths. The challenge is
 * managing the visited state for each path, which requires storing it explicitly.
 * This approach uses more memory but provides a different perspective on the problem.
 * 
 * Time Complexity: O(m*n*4^L) similar to DFS
 * Space Complexity: O(m*n*4^L) for queue and state storage
 * 
 * Best when: Want to find shortest path (though all valid paths have same length)
 * Worst when: Memory is limited (uses much more memory than DFS)
 */
class WordSearchBFS {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word);
    
private:
    struct State {
        int row;
        int col;
        int index;
        std::unordered_set<int> visited;
        
        State(int r, int c, int i) : row(r), col(c), index(i) {}
    };
    
    int encode(int row, int col, int n);
    bool isValid(int row, int col, int m, int n);
};

/**
 * Approach 3: Iterative DFS with Stack (Non-recursive)
 * 
 * Use explicit stack to implement DFS iteratively.
 * 
 * Reasoning: Converts the recursive DFS to iterative using an explicit stack.
 * This avoids potential stack overflow for deep recursion and gives more control
 * over the search process. We push states onto the stack and process them in
 * LIFO order, mimicking recursion. The challenge is properly managing the visited
 * state and backtracking, which requires careful state tracking.
 * 
 * Time Complexity: O(m*n*4^L) same as recursive DFS
 * Space Complexity: O(L) for stack, better than BFS
 * 
 * Best when: Want to avoid recursion, need explicit control over search
 * Worst when: Simplicity is preferred (more complex than recursive)
 */
class WordSearchIterative {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word);
    
private:
    struct DFSState {
        int row;
        int col;
        int index;
        int direction;  // Which direction to try next (0-3)
        
        DFSState(int r, int c, int i) : row(r), col(c), index(i), direction(0) {}
    };
    
    bool isValid(int row, int col, int m, int n);
};

/**
 * Approach 4: Optimized with Pruning (Enhanced DFS)
 * 
 * DFS with additional optimizations and pruning strategies.
 * 
 * Reasoning: Enhances the basic DFS with several optimizations:
 * 1. Character frequency check: If word has more of a character than board, return false
 * 2. Reverse word if last char is less frequent (start from rarer character)
 * 3. In-place marking using bit manipulation instead of separate visited array
 * 4. Early termination based on remaining cells vs remaining word length
 * These optimizations can significantly speed up the search in practice.
 * 
 * Time Complexity: O(m*n*4^L) worst case, but often much faster
 * Space Complexity: O(L) for recursion
 * 
 * Best when: Performance is critical, working with typical inputs
 * Worst when: Need simple, readable code
 */
class WordSearchOptimized {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word);
    
private:
    bool canFormWord(std::vector<std::vector<char>>& board, const std::string& word);
    bool dfsOptimized(std::vector<std::vector<char>>& board, const std::string& word,
                      int row, int col, int index);
    bool isValid(int row, int col, int m, int n);
};

/**
 * Approach 5: Bidirectional Search (Search from Both Ends)
 * 
 * Search from both start and end of the word simultaneously.
 * 
 * Reasoning: Instead of searching for the entire word from start to end, we can
 * search from both ends and meet in the middle. This can reduce the search space
 * significantly, especially for longer words. We maintain two search frontiers
 * and check if they meet. This approach is more complex but can be faster for
 * certain inputs, particularly when the word has unique characters at both ends.
 * 
 * Time Complexity: O(m*n*4^(L/2)) theoretical improvement
 * Space Complexity: O(m*n) for tracking both searches
 * 
 * Best when: Long words with unique endpoints
 * Worst when: Short words or simple cases (overhead not worth it)
 */
class WordSearchBidirectional {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word);
    
private:
    bool searchFromBothEnds(std::vector<std::vector<char>>& board, const std::string& word);
    bool expandSearch(std::vector<std::vector<char>>& board, const std::string& word,
                     std::unordered_set<int>& frontier, std::unordered_set<int>& otherFrontier,
                     int startIdx, int endIdx, bool forward);
    int encode(int row, int col, int n);
    std::pair<int, int> decode(int encoded, int n);
};

/**
 * Approach 6: Trie-based Solution (Multiple Word Search)
 * 
 * Build a trie and use it for searching (extensible to multiple words).
 * 
 * Reasoning: While overkill for a single word, this approach showcases how to
 * handle multiple word searches efficiently. We build a trie of the word(s) and
 * traverse the board while following trie paths. This is the foundation for
 * problems like Word Search II. For a single word, it adds overhead, but the
 * approach is educational and shows how to scale the solution.
 * 
 * Time Complexity: O(m*n*4^L) for single word
 * Space Complexity: O(L) for trie
 * 
 * Best when: Multiple words to search, educational purposes
 * Worst when: Single word search (unnecessary complexity)
 */
class WordSearchTrie {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word);
    
private:
    struct TrieNode {
        TrieNode* children[256];  // Support both uppercase and lowercase
        bool isEnd;
        
        TrieNode() : isEnd(false) {
            for (int i = 0; i < 256; i++) {
                children[i] = nullptr;
            }
        }
        
        ~TrieNode() {
            for (int i = 0; i < 256; i++) {
                delete children[i];
            }
        }
    };
    
    class Trie {
    public:
        TrieNode* root;
        
        Trie() : root(new TrieNode()) {}
        ~Trie() { delete root; }
        
        void insert(const std::string& word);
    };
    
    bool searchWithTrie(std::vector<std::vector<char>>& board, TrieNode* node,
                       int row, int col, std::vector<std::vector<bool>>& visited);
    bool isValid(int row, int col, int m, int n);
};

}
}