#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace leetcode {
namespace hard {

/**
 * Problem 72: Edit Distance
 * 
 * Given two strings word1 and word2, return the minimum number of operations 
 * required to convert word1 to word2.
 * 
 * You have the following three operations permitted on a word:
 * - Insert a character
 * - Delete a character  
 * - Replace a character
 * 
 * Constraints:
 * - 0 <= word1.length, word2.length <= 500
 * - word1 and word2 consist of lowercase English letters only.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class EditDistance {
public:
    /**
     * Approach 1: Dynamic Programming 2D (Classic)
     * 
     * Build solution using 2D DP table representing edit distances for all prefixes.
     * 
     * Reasoning: This is the canonical solution to the edit distance problem (Levenshtein distance).
     * Create a 2D table where dp[i][j] represents the minimum edit distance between
     * word1[0...i-1] and word2[0...j-1]. For each cell, consider three operations:
     * 1) Replace: dp[i-1][j-1] + (word1[i-1] != word2[j-1] ? 1 : 0)
     * 2) Insert: dp[i][j-1] + 1
     * 3) Delete: dp[i-1][j] + 1
     * Take minimum of these three. This approach clearly shows the optimal substructure.
     * 
     * Time Complexity: O(m*n) - fill entire DP table
     * Space Complexity: O(m*n) - 2D DP table storage
     * 
     * Best when: Learning DP, need to trace back operations, clear problem visualization
     * Worst when: Space optimization needed, memory constraints
     */
    int minDistanceDP2D(std::string word1, std::string word2);

    /**
     * Approach 2: Dynamic Programming 1D (Space Optimized)
     * 
     * Optimize space by using only two rows of DP table.
     * 
     * Reasoning: Since we only need the previous row and current position to compute
     * dp[i][j], we can optimize space from O(m*n) to O(min(m,n)) by using rolling
     * arrays or just two 1D arrays. At each iteration, we maintain current row and
     * previous row, swapping them after each row completion. This maintains the same
     * time complexity while significantly reducing space usage.
     * 
     * Time Complexity: O(m*n) - same computation as 2D approach
     * Space Complexity: O(min(m,n)) - only need two rows
     * 
     * Best when: Memory constraints, want space optimization without complexity increase
     * Worst when: Need to trace back actual operations, 2D visualization helpful
     */
    int minDistanceDP1D(std::string word1, std::string word2);

    /**
     * Approach 3: Recursive with Memoization (Top-Down DP)
     * 
     * Use recursion with memoization to solve subproblems naturally.
     * 
     * Reasoning: Define recursive function that returns minimum edits to transform
     * word1[i...] to word2[j...]. At each step, if characters match, recurse on
     * remaining strings. If they don't match, try all three operations and take
     * minimum. Use memoization to cache results for each (i,j) pair to avoid
     * recomputation. This approach follows the problem definition naturally.
     * 
     * Time Complexity: O(m*n) - each subproblem solved once with memoization
     * Space Complexity: O(m*n) - memoization table plus recursion stack
     * 
     * Best when: Prefer recursive thinking, understand top-down approach
     * Worst when: Deep recursion concerns, iterative solution preferred
     */
    int minDistanceMemo(std::string word1, std::string word2);

    /**
     * Approach 4: BFS Shortest Path (Graph Perspective)
     * 
     * Model as shortest path problem in state space graph.
     * 
     * Reasoning: Each string state is a node in graph, edges represent operations
     * (insert, delete, replace) with weight 1. Use BFS to find shortest path from
     * word1 to word2. Each level in BFS represents one more edit operation. While
     * this approach has higher space complexity due to storing intermediate states,
     * it provides intuitive understanding of edit distance as shortest path problem.
     * 
     * Time Complexity: O(3^(m+n)) worst case, but early termination helps
     * Space Complexity: O(3^k) where k is the edit distance
     * 
     * Best when: Graph algorithm perspective, understanding state space exploration
     * Worst when: Large inputs, exponential space growth
     */
    int minDistanceBFS(std::string word1, std::string word2);

    /**
     * Approach 5: Iterative Deepening DFS (Memory Efficient Search)
     * 
     * Use iterative deepening to find minimum edit distance with controlled memory.
     * 
     * Reasoning: Instead of BFS which stores all states at each level, use iterative
     * deepening DFS. Try edit distances 0, 1, 2, ... until solution found. For each
     * limit, use DFS to explore if transformation is possible within that many edits.
     * This approach trades time for space, using O(edit_distance) space instead of
     * exponential space, while still guaranteeing optimal solution.
     * 
     * Time Complexity: O(3^d * d) where d is edit distance, with repeated work
     * Space Complexity: O(d) - DFS recursion depth equals edit distance
     * 
     * Best when: Memory extremely constrained, small edit distances expected
     * Worst when: Large edit distances, repeated computation overhead
     */
    int minDistanceIterativeDeepening(std::string word1, std::string word2);

    /**
     * Approach 6: A* Search (Heuristic-Guided)
     * 
     * Use A* search with admissible heuristic to guide exploration.
     * 
     * Reasoning: Implement A* search where each state is (position in word1, position in word2).
     * Use Manhattan distance heuristic: |remaining_chars_word1 - remaining_chars_word2|
     * as lower bound estimate. A* guarantees optimal solution while potentially
     * exploring fewer states than BFS. Priority queue orders states by f(n) = g(n) + h(n)
     * where g(n) is current cost and h(n) is heuristic estimate.
     * 
     * Time Complexity: O(b^d) where b is branching factor, d is solution depth
     * Space Complexity: O(b^d) - priority queue storage
     * 
     * Best when: Want optimal search with heuristic guidance, AI algorithm practice
     * Worst when: Heuristic overhead not worth it, simple DP more efficient
     */
    int minDistanceAStar(std::string word1, std::string word2);

private:
    // Helper functions
    int memoHelper(const std::string& word1, const std::string& word2, int i, int j,
                  std::vector<std::vector<int>>& memo);
    
    bool canTransformWithLimit(const std::string& word1, const std::string& word2,
                              int i, int j, int limit);
    
    int manhattanDistanceHeuristic(int i, int j, int m, int n);
    
    // State structures for search algorithms
    struct BFSState {
        std::string current;
        int operations;
        
        BFSState(const std::string& str, int ops) : current(str), operations(ops) {}
    };
    
    struct AStarState {
        int i, j;           // Positions in word1 and word2
        int gCost;          // Actual cost so far
        int fCost;          // gCost + heuristic
        
        AStarState(int pos1, int pos2, int g, int f) 
            : i(pos1), j(pos2), gCost(g), fCost(f) {}
        
        // For priority queue (min-heap)
        bool operator>(const AStarState& other) const {
            return fCost > other.fCost;
        }
    };
};

}
}