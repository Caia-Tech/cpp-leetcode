#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

namespace leetcode {
namespace medium {

/**
 * Problem 139: Word Break
 * 
 * Given a string s and a dictionary of strings wordDict, return true if s 
 * can be segmented into a space-separated sequence of one or more dictionary words.
 * 
 * Note that the same word in the dictionary may be reused multiple times 
 * in the segmentation.
 * 
 * Constraints:
 * - 1 <= s.length <= 300
 * - 1 <= wordDict.length <= 1000
 * - 1 <= wordDict[i].length <= 20
 * - s and wordDict[i] consist of only lowercase English letters.
 * - All the strings of wordDict are unique.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class WordBreak {
public:
    /**
     * Approach 1: Dynamic Programming (Bottom-Up) - Optimal
     * 
     * Build solution from smaller subproblems using tabulation.
     * 
     * Reasoning: This is the classic optimal solution. Use dp[i] to represent
     * whether s[0...i-1] can be segmented using dictionary words. For each
     * position i, check all possible previous positions j where dp[j] is true
     * and s[j...i-1] forms a valid dictionary word. This approach guarantees
     * we find the solution if it exists and has optimal time complexity.
     * 
     * Time Complexity: O(n² + m*k) - n is string length, m is dict size, k is avg word length
     * Space Complexity: O(n + m*k) - dp array plus word set storage
     * 
     * Best when: Want guaranteed optimal solution, understand DP concepts
     * Worst when: String is very long, prefer recursive approaches
     */
    bool wordBreakDP(std::string s, std::vector<std::string>& wordDict);

    /**
     * Approach 2: Memoization (Top-Down DP) - Recursive with Caching
     * 
     * Use recursion with memoization to avoid recomputing subproblems.
     * 
     * Reasoning: Start from the full string and recursively try all possible
     * first words. If first word matches dictionary, recursively check if
     * remaining string can be segmented. Use memoization to cache results
     * for each starting position to avoid redundant computation. This approach
     * is more intuitive than bottom-up DP and naturally handles the recursive
     * structure of the problem.
     * 
     * Time Complexity: O(n² + m*k) - same as DP but with recursion overhead
     * Space Complexity: O(n + m*k) - memoization cache plus recursion stack
     * 
     * Best when: Prefer recursive thinking, natural problem decomposition
     * Worst when: Deep recursion concerns, stack overflow risks
     */
    bool wordBreakMemo(std::string s, std::vector<std::string>& wordDict);

    /**
     * Approach 3: BFS (Breadth-First Search) - Level-by-Level Exploration
     * 
     * Use BFS to explore all possible segmentation paths level by level.
     * 
     * Reasoning: Model the problem as a graph where each position in the string
     * is a node, and edges exist between positions i and j if s[i...j-1] is
     * a dictionary word. Use BFS to find if there's a path from start to end.
     * This approach provides good insight into the graph structure of the problem
     * and can be useful when you want to find shortest segmentation.
     * 
     * Time Complexity: O(n² + m*k) - similar to DP but with queue operations
     * Space Complexity: O(n + m*k) - queue storage plus word set
     * 
     * Best when: Graph-based thinking preferred, want shortest segmentation path
     * Worst when: Extra queue overhead not needed, DP is more direct
     */
    bool wordBreakBFS(std::string s, std::vector<std::string>& wordDict);

    /**
     * Approach 4: Trie + DP - Optimized Dictionary Lookup
     * 
     * Build trie from dictionary for efficient prefix matching with DP.
     * 
     * Reasoning: Instead of checking every dictionary word at each position,
     * build a trie (prefix tree) from the dictionary. Then use DP where at
     * each position, traverse the trie to find all possible words starting
     * at that position. This optimizes the dictionary lookup from O(m*k) to
     * O(k) per position, making it more efficient when dictionary is large.
     * 
     * Time Complexity: O(n*k + m*k) - n positions, max k characters per lookup
     * Space Complexity: O(m*k + n) - trie storage plus DP array
     * 
     * Best when: Large dictionary, want to optimize lookup performance
     * Worst when: Dictionary is small, trie overhead not worth it
     */
    bool wordBreakTrie(std::string s, std::vector<std::string>& wordDict);

    /**
     * Approach 5: Backtracking with Pruning - Explicit Search
     * 
     * Use backtracking with intelligent pruning to explore segmentation paths.
     * 
     * Reasoning: Recursively try each possible first word and backtrack if
     * the remaining string cannot be segmented. Use pruning techniques like
     * memoizing failed positions to avoid redundant exploration. While this
     * has potentially exponential worst-case complexity, good pruning can
     * make it competitive with DP approaches in practice.
     * 
     * Time Complexity: O(2^n) worst case, but good pruning reduces this significantly
     * Space Complexity: O(n) - recursion depth plus pruning cache
     * 
     * Best when: Want explicit search control, good at pruning optimization
     * Worst when: Worst-case exponential complexity is concerning
     */
    bool wordBreakBacktrack(std::string s, std::vector<std::string>& wordDict);

    /**
     * Approach 6: Sliding Window with Set - Pattern Matching
     * 
     * Use sliding window technique with set-based dictionary lookup.
     * 
     * Reasoning: For each starting position, use a sliding window to check
     * all possible word lengths and see if any form valid dictionary words.
     * Combine this with DP-like tracking of valid positions. This approach
     * emphasizes the pattern-matching aspect of the problem and can be
     * intuitive for those familiar with sliding window techniques.
     * 
     * Time Complexity: O(n²) - nested loops for position and window size
     * Space Complexity: O(n + m*k) - position tracking plus word set
     * 
     * Best when: Familiar with sliding window patterns, want different perspective
     * Worst when: Not significantly different from standard DP approach
     */
    bool wordBreakSlidingWindow(std::string s, std::vector<std::string>& wordDict);

private:
    // Helper functions for different approaches
    bool memoHelper(const std::string& s, int start, const std::unordered_set<std::string>& wordSet,
                   std::unordered_map<int, bool>& memo);
    
    bool backtrackHelper(const std::string& s, int start, const std::unordered_set<std::string>& wordSet,
                        std::unordered_set<int>& visited);
    
    // Trie node structure
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        bool isEndOfWord;
        
        TrieNode() : isEndOfWord(false) {}
        
        ~TrieNode() {
            for (auto& pair : children) {
                delete pair.second;
            }
        }
    };
    
    void buildTrie(TrieNode* root, const std::vector<std::string>& wordDict);
    std::vector<int> findWordsStartingAt(TrieNode* root, const std::string& s, int start);
};

}
}