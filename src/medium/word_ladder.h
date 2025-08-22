#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <deque>
#include <climits>

namespace leetcode {
namespace medium {

/**
 * Problem 127: Word Ladder
 * 
 * A transformation sequence from word beginWord to word endWord using a dictionary wordList
 * is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
 * - Every adjacent pair of words differs by exactly one letter.
 * - Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
 * - sk == endWord
 * 
 * Given two words, beginWord and endWord, and a dictionary wordList, return the number of
 * words in the shortest transformation sequence from beginWord to endWord, or 0 if no such
 * sequence exists.
 * 
 * Constraints:
 * - 1 <= beginWord.length <= 10
 * - endWord.length == beginWord.length
 * - 1 <= wordList.size() <= 5000
 * - wordList[i].length == beginWord.length
 * - beginWord, endWord, and wordList[i] consist of lowercase English letters.
 * - beginWord != endWord
 * - All the words in wordList are unique.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class WordLadder {
public:
    /**
     * Approach 1: Standard BFS with Queue (Classic)
     * 
     * Use breadth-first search to find shortest transformation path.
     * 
     * Reasoning: Since we need the shortest path, BFS is natural choice as it explores
     * all nodes at distance k before exploring nodes at distance k+1. Start from
     * beginWord, for each word try all possible single-character changes, check if
     * resulting word exists in dictionary. If it's endWord, return current level + 1.
     * If it's in dictionary and not visited, add to queue for next level exploration.
     * This guarantees finding shortest path due to BFS's level-by-level exploration.
     * Use visited set to avoid cycles and redundant processing.
     * 
     * Time Complexity: O(M²×N) - M=word length, N=wordList size, M² for generating neighbors
     * Space Complexity: O(M×N) - queue and visited set storage
     * 
     * Best when: Standard shortest path problem, moderate dataset size, clear implementation
     * Worst when: Very large datasets, memory constraints, need bidirectional optimization
     */
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);

    /**
     * Approach 2: Bidirectional BFS (Optimized)
     * 
     * Search simultaneously from both ends to reduce search space.
     * 
     * Reasoning: Standard BFS explores exponentially growing search space. Bidirectional
     * BFS starts from both beginWord and endWord, alternating between forward and backward
     * search. When searches meet, we've found shortest path. This reduces time complexity
     * from O(b^d) to O(b^(d/2)) where b=branching factor, d=depth. Always expand smaller
     * frontier to maintain efficiency. Use two separate visited sets to track which words
     * have been reached from each direction. Critical optimization for large search spaces.
     * 
     * Time Complexity: O(M²×N/2) - effectively halves search space
     * Space Complexity: O(M×N) - two visited sets and queues
     * 
     * Best when: Large search spaces, deep transformation chains, performance critical
     * Worst when: Short paths, small datasets, implementation simplicity preferred
     */
    int ladderLengthBidirectional(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);

    /**
     * Approach 3: BFS with Precomputed Adjacent Words
     * 
     * Precompute all adjacent word relationships to optimize neighbor finding.
     * 
     * Reasoning: Standard BFS spends O(M²) time generating neighbors for each word by
     * trying all character substitutions. Instead, precompute adjacency list where
     * each word maps to its directly reachable neighbors. This trades space for time:
     * preprocessing takes O(M²×N) but each BFS step only needs O(degree) time to find
     * neighbors. Particularly beneficial when running multiple queries on same wordList
     * or when words have many neighbors. Use unordered_map for O(1) neighbor lookup.
     * 
     * Time Complexity: O(M²×N + breadth×levels) - preprocessing + optimized BFS
     * Space Complexity: O(M²×N) - adjacency list storage
     * 
     * Best when: Multiple queries, dense word connectivity, repeated operations
     * Worst when: Single query, sparse connections, memory constraints
     */
    int ladderLengthPrecomputed(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);

    /**
     * Approach 4: BFS with Pattern Matching
     * 
     * Group words by patterns to efficiently find transformations.
     * 
     * Reasoning: Instead of checking every possible character substitution, group words
     * by their patterns (e.g., "hot" creates patterns "*ot", "h*t", "ho*"). Words sharing
     * a pattern are one transformation apart. Build pattern-to-words mapping during
     * preprocessing. During BFS, for each word generate its patterns and find all words
     * matching those patterns. This reduces neighbor finding from O(M×26) character
     * tries to O(M×neighbors_per_pattern). Especially efficient when alphabet size
     * is large or when words cluster around certain patterns.
     * 
     * Time Complexity: O(M²×N) - pattern generation dominates
     * Space Complexity: O(M²×N) - pattern mappings
     * 
     * Best when: Large alphabets, clustered word patterns, educational pattern recognition
     * Worst when: Small datasets, simple character sets, memory efficiency needed
     */
    int ladderLengthPatternMatching(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);

    /**
     * Approach 5: A* Search with Heuristic
     * 
     * Use informed search with distance heuristic for efficiency.
     * 
     * Reasoning: A* search combines BFS optimality with greedy efficiency using heuristic
     * function. Use Hamming distance (number of differing characters) as heuristic since
     * it's admissible (never overestimates true distance) and consistent. Priority queue
     * orders exploration by f(n) = g(n) + h(n) where g(n) is actual distance from start
     * and h(n) is heuristic distance to goal. This guides search toward target more
     * efficiently than blind BFS. Guarantees optimal solution while potentially reducing
     * nodes explored. Educational value in demonstrating informed search principles.
     * 
     * Time Complexity: O(M²×N×log(N)) - priority queue operations
     * Space Complexity: O(M×N) - priority queue and visited tracking
     * 
     * Best when: Educational purposes, good heuristics available, large sparse graphs
     * Worst when: Poor heuristics, small problems, implementation complexity unwanted
     */
    int ladderLengthAStar(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);

    /**
     * Approach 6: Level-Order BFS with Size Tracking
     * 
     * Process BFS level by level with explicit level counting.
     * 
     * Reasoning: Instead of storing level information with each queue element, process
     * entire levels at once. At start of each level, record current queue size and
     * process exactly that many elements before moving to next level. This eliminates
     * need for storing level data with each node, saving space and simplifying logic.
     * Clear separation between levels makes algorithm easier to understand and debug.
     * Also enables easy extraction of all words at each transformation distance.
     * Natural for problems requiring level-wise processing or analysis.
     * 
     * Time Complexity: O(M²×N) - same as standard BFS
     * Space Complexity: O(M×N) - slightly better due to no level storage per node
     * 
     * Best when: Level analysis needed, cleaner code preferred, educational clarity
     * Worst when: Standard BFS sufficient, maximum performance critical
     */
    int ladderLengthLevelOrder(std::string beginWord, std::string endWord, std::vector<std::string>& wordList);

private:
    // Helper functions for standard BFS approach
    bool isAdjacent(const std::string& word1, const std::string& word2);
    std::vector<std::string> getNeighbors(const std::string& word, const std::unordered_set<std::string>& wordSet);
    
    // Helper functions for precomputed approach
    void buildAdjacencyList(const std::vector<std::string>& wordList, 
                           std::unordered_map<std::string, std::vector<std::string>>& adjList);
    
    // Helper functions for pattern matching approach
    void buildPatternMap(const std::vector<std::string>& wordList,
                        std::unordered_map<std::string, std::vector<std::string>>& patternMap);
    std::vector<std::string> getPatterns(const std::string& word);
    
    // Helper functions for A* approach
    int hammingDistance(const std::string& word1, const std::string& word2);
    
    // Data structure for A* search
    struct AStarNode {
        std::string word;
        int g;  // Distance from start
        int f;  // g + heuristic
        
        AStarNode(std::string w, int distance, int heuristic) 
            : word(w), g(distance), f(distance + heuristic) {}
        
        bool operator>(const AStarNode& other) const {
            return f > other.f;  // For min-heap
        }
    };
};

}
}