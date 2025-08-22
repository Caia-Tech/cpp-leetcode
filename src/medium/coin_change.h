#pragma once

#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

namespace leetcode {
namespace medium {

/**
 * Problem 322: Coin Change
 * 
 * You are given an integer array coins representing coins of different denominations
 * and an integer amount representing a total amount of money.
 * Return the fewest number of coins that you need to make up that amount.
 * If that amount of money cannot be made up by any combination of the coins, return -1.
 * You may assume that you have an infinite number of each kind of coin.
 * 
 * Constraints:
 * - 1 <= coins.length <= 12
 * - 1 <= coins[i] <= 2^31 - 1
 * - 0 <= amount <= 10^4
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class CoinChange {
public:
    /**
     * Approach 1: Dynamic Programming Bottom-Up (Classic Optimal)
     * 
     * Build up solutions from 0 to amount, finding minimum coins for each value.
     * 
     * Reasoning: This is the standard DP solution. Create array dp[amount+1] where
     * dp[i] represents minimum coins needed for amount i. Initialize dp[0] = 0
     * (no coins needed for 0). For each amount from 1 to target, try using each coin:
     * if coin <= amount, dp[amount] = min(dp[amount], dp[amount-coin] + 1).
     * This builds optimal solution incrementally, ensuring we find minimum coins
     * for each sub-amount before solving larger amounts.
     * 
     * Time Complexity: O(amount * coins.length) - nested loops
     * Space Complexity: O(amount) - DP array storage
     * 
     * Best when: Standard interview solution, moderate amounts, need optimal count
     * Worst when: Very large amounts, need actual coins used, space constraints
     */
    int coinChange(std::vector<int>& coins, int amount);

    /**
     * Approach 2: BFS (Breadth-First Search)
     * 
     * Treat as shortest path problem in graph where nodes are amounts.
     * 
     * Reasoning: Model as graph where each amount is a node, and edges represent
     * using a coin to reach new amount. BFS guarantees shortest path (minimum coins).
     * Start from amount 0, explore all reachable amounts using each coin type.
     * First time we reach target amount gives minimum coins. Use visited set
     * to avoid reprocessing same amounts. This approach naturally finds minimum
     * because BFS explores in level order (same number of coins used).
     * 
     * Time Complexity: O(amount * coins.length) - each amount processed once
     * Space Complexity: O(amount) - queue and visited set
     * 
     * Best when: Need path reconstruction, graph perspective useful, moderate amounts
     * Worst when: Very large amounts, simple DP sufficient, memory constraints
     */
    int coinChangeBFS(std::vector<int>& coins, int amount);

    /**
     * Approach 3: DFS with Memoization (Top-Down DP)
     * 
     * Recursively find minimum coins needed, caching results.
     * 
     * Reasoning: Start from target amount and recursively try subtracting each coin.
     * Memoization prevents recomputing same subproblems. For amount n, minimum coins
     * is 1 + min(coinChange(n - coin)) for all valid coins. Base case: amount 0
     * needs 0 coins. This top-down approach only computes needed subproblems,
     * potentially more efficient than bottom-up for sparse cases. Natural recursion
     * makes logic clear and easy to understand.
     * 
     * Time Complexity: O(amount * coins.length) - each subproblem solved once
     * Space Complexity: O(amount) - recursion stack + memoization
     * 
     * Best when: Sparse subproblems, recursive thinking natural, need early termination
     * Worst when: Stack overflow risk, iterative preferred, all subproblems needed anyway
     */
    int coinChangeDFS(std::vector<int>& coins, int amount);

    /**
     * Approach 4: Complete Knapsack Variant
     * 
     * Treat as unbounded knapsack problem with weight = value = coin.
     * 
     * Reasoning: This is essentially unbounded knapsack where we minimize items
     * (coins) used instead of maximizing value. Create 2D DP table where dp[i][j]
     * represents minimum coins using first i coin types for amount j. For each
     * coin type and amount, choose minimum between not using current coin type
     * (dp[i-1][j]) and using it (dp[i][j-coin] + 1). This approach explicitly
     * models the choice structure and can be optimized to 1D array.
     * 
     * Time Complexity: O(coins.length * amount) - fill DP table
     * Space Complexity: O(amount) - optimized to 1D array
     * 
     * Best when: Learning knapsack variations, need systematic approach, teaching
     * Worst when: Standard DP clearer, extra complexity unnecessary, performance critical
     */
    int coinChangeKnapsack(std::vector<int>& coins, int amount);

    /**
     * Approach 5: Greedy with Backtracking
     * 
     * Try greedy approach (largest coins first) with backtracking when stuck.
     * 
     * Reasoning: Sort coins descending and greedily use largest coins possible.
     * When greedy fails (can't make exact amount), backtrack and try fewer of
     * current coin. While greedy alone doesn't work for general coin systems,
     * combining with backtracking ensures correctness. Pruning: if current path
     * uses more coins than best found, abandon it. This can be very fast for
     * certain coin systems where greedy works well.
     * 
     * Time Complexity: O(amount^coins.length) worst case, often much better
     * Space Complexity: O(coins.length) - recursion stack
     * 
     * Best when: Coin system favors greedy, need quick solution for common cases
     * Worst when: Arbitrary coin values, need guaranteed optimal, worst-case matters
     */
    int coinChangeGreedyBacktrack(std::vector<int>& coins, int amount);

    /**
     * Approach 6: Mathematical Optimization (Frobenius Numbers)
     * 
     * Use mathematical properties and modular arithmetic for optimization.
     * 
     * Reasoning: For certain coin systems, mathematical properties can optimize
     * the solution. Use GCD to check if amount is achievable (must be multiple
     * of GCD of all coins). For two coins, use extended Euclidean algorithm
     * to find solutions. For general case, combine with DP but use modular
     * arithmetic to reduce state space. Pre-compute reachable amounts using
     * generating functions concept. While complex, demonstrates how number
     * theory can optimize combinatorial problems.
     * 
     * Time Complexity: O(amount * coins.length) with optimizations
     * Space Complexity: O(amount) - reduced state space
     * 
     * Best when: Special coin systems, mathematical insight available, research context
     * Worst when: General problem, simplicity needed, standard approaches sufficient
     */
    int coinChangeMath(std::vector<int>& coins, int amount);

private:
    // Helper functions for DFS approach
    int dfsHelper(std::vector<int>& coins, int amount, std::unordered_map<int, int>& memo);
    
    // Helper for greedy backtracking
    void greedyBacktrackHelper(std::vector<int>& coins, int amount, int index, 
                              int currentCoins, int& minCoins);
    
    // Mathematical helper functions
    int gcd(int a, int b);
    int gcdArray(const std::vector<int>& nums);
    bool canMakeAmount(const std::vector<int>& coins, int amount);
    
    // BFS node structure
    struct BFSNode {
        int amount;
        int coins;
        BFSNode(int a, int c) : amount(a), coins(c) {}
    };
};

}
}