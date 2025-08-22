#include "edit_distance.h"
#include <queue>
#include <unordered_set>
#include <climits>

namespace leetcode {
namespace hard {

int EditDistance::minDistanceDP2D(std::string word1, std::string word2) {
    int m = word1.length();
    int n = word2.length();
    
    // dp[i][j] = minimum edits to transform word1[0...i-1] to word2[0...j-1]
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    
    // Base cases: transforming empty string
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i; // Delete all characters from word1
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j; // Insert all characters to form word2
    }
    
    // Fill DP table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i-1] == word2[j-1]) {
                // Characters match, no operation needed
                dp[i][j] = dp[i-1][j-1];
            } else {
                // Take minimum of three operations
                dp[i][j] = 1 + std::min({
                    dp[i-1][j-1],  // Replace
                    dp[i][j-1],    // Insert
                    dp[i-1][j]     // Delete
                });
            }
        }
    }
    
    return dp[m][n];
}

int EditDistance::minDistanceDP1D(std::string word1, std::string word2) {
    int m = word1.length();
    int n = word2.length();
    
    // Optimize space by using the shorter string for the columns
    if (m < n) {
        std::swap(word1, word2);
        std::swap(m, n);
    }
    
    // Use two 1D arrays: previous and current row
    std::vector<int> prev(n + 1), curr(n + 1);
    
    // Initialize first row
    for (int j = 0; j <= n; ++j) {
        prev[j] = j;
    }
    
    for (int i = 1; i <= m; ++i) {
        curr[0] = i; // First column
        
        for (int j = 1; j <= n; ++j) {
            if (word1[i-1] == word2[j-1]) {
                curr[j] = prev[j-1];
            } else {
                curr[j] = 1 + std::min({
                    prev[j-1],  // Replace
                    curr[j-1],  // Insert
                    prev[j]     // Delete
                });
            }
        }
        
        // Swap arrays for next iteration
        prev = curr;
    }
    
    return prev[n];
}

int EditDistance::minDistanceMemo(std::string word1, std::string word2) {
    int m = word1.length();
    int n = word2.length();
    
    std::vector<std::vector<int>> memo(m + 1, std::vector<int>(n + 1, -1));
    return memoHelper(word1, word2, 0, 0, memo);
}

int EditDistance::minDistanceBFS(std::string word1, std::string word2) {
    if (word1 == word2) return 0;
    
    std::queue<BFSState> queue;
    std::unordered_set<std::string> visited;
    
    queue.push(BFSState(word1, 0));
    visited.insert(word1);
    
    while (!queue.empty()) {
        BFSState current = queue.front();
        queue.pop();
        
        std::string& str = current.current;
        int ops = current.operations;
        
        // Generate all possible next states
        
        // Try all possible insertions
        for (int i = 0; i <= str.length(); ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                std::string next = str.substr(0, i) + c + str.substr(i);
                if (next == word2) return ops + 1;
                
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    queue.push(BFSState(next, ops + 1));
                }
            }
        }
        
        // Try all possible deletions
        for (int i = 0; i < str.length(); ++i) {
            std::string next = str.substr(0, i) + str.substr(i + 1);
            if (next == word2) return ops + 1;
            
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                queue.push(BFSState(next, ops + 1));
            }
        }
        
        // Try all possible replacements
        for (int i = 0; i < str.length(); ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c != str[i]) {
                    std::string next = str;
                    next[i] = c;
                    if (next == word2) return ops + 1;
                    
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        queue.push(BFSState(next, ops + 1));
                    }
                }
            }
        }
    }
    
    return -1; // Should not reach here for valid inputs
}

int EditDistance::minDistanceIterativeDeepening(std::string word1, std::string word2) {
    if (word1 == word2) return 0;
    
    // Try increasing edit distance limits
    for (int limit = 1; limit <= word1.length() + word2.length(); ++limit) {
        if (canTransformWithLimit(word1, word2, 0, 0, limit)) {
            return limit;
        }
    }
    
    return word1.length() + word2.length(); // Worst case
}

int EditDistance::minDistanceAStar(std::string word1, std::string word2) {
    if (word1 == word2) return 0;
    
    int m = word1.length();
    int n = word2.length();
    
    std::priority_queue<AStarState, std::vector<AStarState>, std::greater<AStarState>> pq;
    std::vector<std::vector<bool>> visited(m + 1, std::vector<bool>(n + 1, false));
    
    // Start state
    int heuristic = manhattanDistanceHeuristic(0, 0, m, n);
    pq.push(AStarState(0, 0, 0, heuristic));
    
    while (!pq.empty()) {
        AStarState current = pq.top();
        pq.pop();
        
        int i = current.i;
        int j = current.j;
        int cost = current.gCost;
        
        // Goal state
        if (i == m && j == n) {
            return cost;
        }
        
        if (visited[i][j]) continue;
        visited[i][j] = true;
        
        // Possible moves
        
        // Match/Replace: move both pointers
        if (i < m && j < n) {
            int newCost = cost + (word1[i] == word2[j] ? 0 : 1);
            int h = manhattanDistanceHeuristic(i + 1, j + 1, m, n);
            pq.push(AStarState(i + 1, j + 1, newCost, newCost + h));
        }
        
        // Delete from word1: move i pointer
        if (i < m) {
            int newCost = cost + 1;
            int h = manhattanDistanceHeuristic(i + 1, j, m, n);
            pq.push(AStarState(i + 1, j, newCost, newCost + h));
        }
        
        // Insert into word1: move j pointer
        if (j < n) {
            int newCost = cost + 1;
            int h = manhattanDistanceHeuristic(i, j + 1, m, n);
            pq.push(AStarState(i, j + 1, newCost, newCost + h));
        }
    }
    
    return -1; // Should not reach here
}

// Helper function implementations
int EditDistance::memoHelper(const std::string& word1, const std::string& word2, int i, int j,
                            std::vector<std::vector<int>>& memo) {
    // Base cases
    if (i == word1.length()) return word2.length() - j; // Insert remaining chars
    if (j == word2.length()) return word1.length() - i; // Delete remaining chars
    
    // Check memo
    if (memo[i][j] != -1) return memo[i][j];
    
    int result;
    if (word1[i] == word2[j]) {
        // Characters match, no operation needed
        result = memoHelper(word1, word2, i + 1, j + 1, memo);
    } else {
        // Try all three operations
        int replace = memoHelper(word1, word2, i + 1, j + 1, memo);
        int insert = memoHelper(word1, word2, i, j + 1, memo);
        int delete_op = memoHelper(word1, word2, i + 1, j, memo);
        
        result = 1 + std::min({replace, insert, delete_op});
    }
    
    memo[i][j] = result;
    return result;
}

bool EditDistance::canTransformWithLimit(const std::string& word1, const std::string& word2,
                                        int i, int j, int limit) {
    // Base cases
    if (limit < 0) return false;
    if (i == word1.length()) return j == word2.length() || limit >= word2.length() - j;
    if (j == word2.length()) return limit >= word1.length() - i;
    
    // Pruning: if remaining characters differ more than limit allows
    int remaining1 = word1.length() - i;
    int remaining2 = word2.length() - j;
    if (abs(remaining1 - remaining2) > limit) return false;
    
    if (word1[i] == word2[j]) {
        // Characters match
        return canTransformWithLimit(word1, word2, i + 1, j + 1, limit);
    } else {
        // Try all three operations
        return canTransformWithLimit(word1, word2, i + 1, j + 1, limit - 1) ||  // Replace
               canTransformWithLimit(word1, word2, i, j + 1, limit - 1) ||      // Insert
               canTransformWithLimit(word1, word2, i + 1, j, limit - 1);       // Delete
    }
}

int EditDistance::manhattanDistanceHeuristic(int i, int j, int m, int n) {
    // Simple heuristic: difference in remaining characters
    return abs((m - i) - (n - j));
}

}
}