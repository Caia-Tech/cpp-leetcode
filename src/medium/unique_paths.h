#pragma once

#include <vector>
#include <unordered_map>

namespace leetcode {
namespace medium {

/**
 * Problem 62: Unique Paths
 * 
 * There is a robot on an m x n grid. The robot is initially located at the 
 * top-left corner (i.e., grid[0][0]). The robot tries to move to the 
 * bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move 
 * either down or right at any point in time.
 * 
 * Given the two integers m and n, return the number of possible unique paths 
 * that the robot can take to reach the bottom-right corner.
 * 
 * Constraints:
 * - 1 <= m, n <= 100
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class UniquePaths {
public:
    /**
     * Approach 1: Dynamic Programming 2D (Classic)
     * 
     * Build solution bottom-up using 2D DP table.
     * 
     * Reasoning: This is the standard textbook DP solution. Create a 2D table
     * where dp[i][j] represents the number of unique paths to reach cell (i,j).
     * The robot can only come from above or left, so dp[i][j] = dp[i-1][j] + dp[i][j-1].
     * Initialize first row and column to 1 (only one way to reach any cell in
     * first row or column). This approach clearly shows the overlapping subproblems
     * and optimal substructure of the problem.
     * 
     * Time Complexity: O(m*n) - fill entire DP table
     * Space Complexity: O(m*n) - 2D DP table storage
     * 
     * Best when: Learning DP concepts, need to visualize the problem structure
     * Worst when: Space optimization needed, memory constraints
     */
    int uniquePathsDP2D(int m, int n);

    /**
     * Approach 2: Dynamic Programming 1D (Space Optimized)
     * 
     * Optimize space by using only one row of DP table.
     * 
     * Reasoning: Since we only need the previous row and current position in
     * current row to compute dp[i][j], we can optimize space by using a 1D array.
     * At each step, dp[j] represents paths to current row position j, and we
     * update it using dp[j] (from above) + dp[j-1] (from left). This maintains
     * the same time complexity while reducing space from O(m*n) to O(n).
     * 
     * Time Complexity: O(m*n) - same computation as 2D approach
     * Space Complexity: O(n) - only need one row of DP table
     * 
     * Best when: Want space optimization, understand DP space reduction techniques
     * Worst when: 2D visualization helpful, memory not a concern
     */
    int uniquePathsDP1D(int m, int n);

    /**
     * Approach 3: Recursive with Memoization (Top-Down DP)
     * 
     * Use recursion with memoization to solve subproblems.
     * 
     * Reasoning: Start from destination (m-1, n-1) and recursively compute paths
     * by considering moves from (i-1, j) and (i, j-1). Use memoization to cache
     * results for each position to avoid recomputation. This approach naturally
     * follows the problem definition and shows how recursive solutions can be
     * optimized with memoization to achieve DP efficiency.
     * 
     * Time Complexity: O(m*n) - each subproblem solved once with memoization
     * Space Complexity: O(m*n) - memoization table plus recursion stack
     * 
     * Best when: Prefer recursive thinking, understand top-down DP approach
     * Worst when: Deep recursion concerns, prefer iterative solutions
     */
    int uniquePathsMemo(int m, int n);

    /**
     * Approach 4: Mathematical Combination (Optimal)
     * 
     * Use combinatorial mathematics to directly compute the answer.
     * 
     * Reasoning: The robot needs to make exactly (m-1) down moves and (n-1) right
     * moves, for a total of (m+n-2) moves. The problem reduces to choosing which
     * (m-1) positions out of (m+n-2) total positions are down moves. This is
     * C(m+n-2, m-1) = (m+n-2)! / ((m-1)! * (n-1)!). Use careful calculation
     * to avoid integer overflow and achieve O(min(m,n)) time complexity.
     * 
     * Time Complexity: O(min(m,n)) - calculate combination using minimal multiplications
     * Space Complexity: O(1) - only calculation variables
     * 
     * Best when: Want optimal solution, understand combinatorial mathematics
     * Worst when: Mathematical approach less intuitive, overflow concerns
     */
    int uniquePathsMath(int m, int n);

    /**
     * Approach 5: Pure Recursion (Baseline/Educational)
     * 
     * Use plain recursion without memoization to show exponential complexity.
     * 
     * Reasoning: Simple recursive implementation where each cell's paths equal
     * the sum of paths from cell above and cell to the left. While this approach
     * has exponential time complexity due to repeated subproblems, it clearly
     * demonstrates the recursive structure and serves as a baseline to show
     * the importance of memoization or DP optimization.
     * 
     * Time Complexity: O(2^(m+n)) - exponential due to repeated subproblems
     * Space Complexity: O(m+n) - recursion depth
     * 
     * Best when: Understanding problem structure, demonstrating need for optimization
     * Worst when: Performance critical, large inputs
     */
    int uniquePathsRecursive(int m, int n);

    /**
     * Approach 6: BFS Path Counting (Alternative Perspective)
     * 
     * Use breadth-first search to count all possible paths.
     * 
     * Reasoning: While not optimal for this problem, BFS provides an alternative
     * perspective. Explore all possible positions level by level, maintaining
     * count of ways to reach each position. This approach demonstrates how
     * graph traversal algorithms can be adapted for counting problems, though
     * it's less efficient than DP approaches for this specific problem.
     * 
     * Time Complexity: O(m*n) - visit each cell, but with higher constants
     * Space Complexity: O(m*n) - queue storage for BFS
     * 
     * Best when: Graph algorithm perspective preferred, exploring alternative approaches
     * Worst when: Efficiency important, DP approach more natural
     */
    int uniquePathsBFS(int m, int n);

private:
    // Helper functions
    int memoHelper(int i, int j, int m, int n, std::unordered_map<int, int>& memo);
    int recursiveHelper(int i, int j, int m, int n);
    int getKey(int i, int j, int n);
    
    // Mathematical helper
    long long binomialCoefficient(int n, int k);
    long long gcd(long long a, long long b);
};

}
}