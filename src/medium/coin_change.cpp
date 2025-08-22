#include "coin_change.h"
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_set>

namespace leetcode {
namespace medium {

int CoinChange::coinChange(std::vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    
    // dp[i] = minimum coins needed for amount i
    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    
    // Build up solutions from 1 to amount
    for (int i = 1; i <= amount; ++i) {
        // Try each coin
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int CoinChange::coinChangeBFS(std::vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    
    std::queue<BFSNode> q;
    std::unordered_set<int> visited;
    
    q.push(BFSNode(0, 0));
    visited.insert(0);
    
    while (!q.empty()) {
        BFSNode current = q.front();
        q.pop();
        
        // Try adding each coin
        for (int coin : coins) {
            int newAmount = current.amount + coin;
            
            // Check if we've reached target
            if (newAmount == amount) {
                return current.coins + 1;
            }
            
            // Add to queue if valid and not visited
            if (newAmount < amount && visited.find(newAmount) == visited.end()) {
                visited.insert(newAmount);
                q.push(BFSNode(newAmount, current.coins + 1));
            }
        }
    }
    
    return -1; // Can't make the amount
}

int CoinChange::coinChangeDFS(std::vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    
    std::unordered_map<int, int> memo;
    int result = dfsHelper(coins, amount, memo);
    return result == INT_MAX ? -1 : result;
}

int CoinChange::dfsHelper(std::vector<int>& coins, int amount, 
                         std::unordered_map<int, int>& memo) {
    // Base cases
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;
    
    // Check memoization
    if (memo.find(amount) != memo.end()) {
        return memo[amount];
    }
    
    int minCoins = INT_MAX;
    
    // Try each coin
    for (int coin : coins) {
        int subResult = dfsHelper(coins, amount - coin, memo);
        if (subResult != INT_MAX) {
            minCoins = std::min(minCoins, subResult + 1);
        }
    }
    
    memo[amount] = minCoins;
    return minCoins;
}

int CoinChange::coinChangeKnapsack(std::vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    
    // dp[j] = minimum coins for amount j
    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    
    // Process each coin type
    for (int coin : coins) {
        // For each amount from coin to target
        for (int j = coin; j <= amount; ++j) {
            if (dp[j - coin] != INT_MAX) {
                dp[j] = std::min(dp[j], dp[j - coin] + 1);
            }
        }
    }
    
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int CoinChange::coinChangeGreedyBacktrack(std::vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    
    // Sort coins in descending order for greedy approach
    std::sort(coins.begin(), coins.end(), std::greater<int>());
    
    int minCoins = INT_MAX;
    greedyBacktrackHelper(coins, amount, 0, 0, minCoins);
    
    return minCoins == INT_MAX ? -1 : minCoins;
}

void CoinChange::greedyBacktrackHelper(std::vector<int>& coins, int amount, 
                                      int index, int currentCoins, int& minCoins) {
    // Base case: exact amount made
    if (amount == 0) {
        minCoins = std::min(minCoins, currentCoins);
        return;
    }
    
    // Pruning: if current path already uses too many coins
    if (index >= coins.size() || currentCoins >= minCoins - 1) {
        return;
    }
    
    // Try using maximum possible of current coin (greedy)
    int maxCount = amount / coins[index];
    
    // Try different counts of current coin (backtracking)
    for (int count = maxCount; count >= 0; --count) {
        // Early termination if this path can't be better
        if (currentCoins + count >= minCoins) break;
        
        greedyBacktrackHelper(coins, amount - count * coins[index], 
                            index + 1, currentCoins + count, minCoins);
    }
}

int CoinChange::coinChangeMath(std::vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    
    // Check if amount is achievable using GCD
    int g = gcdArray(coins);
    if (amount % g != 0) {
        return -1; // Amount not achievable
    }
    
    // Reduce problem size by dividing by GCD
    int reducedAmount = amount / g;
    std::vector<int> reducedCoins;
    for (int coin : coins) {
        reducedCoins.push_back(coin / g);
    }
    
    // Use optimized DP with reduced values
    std::vector<int> dp(reducedAmount + 1, INT_MAX);
    dp[0] = 0;
    
    // Sort coins for better cache locality
    std::sort(reducedCoins.begin(), reducedCoins.end());
    
    // DP with optimizations
    for (int i = 1; i <= reducedAmount; ++i) {
        // Only check coins that could work
        for (int coin : reducedCoins) {
            if (coin > i) break; // Coins are sorted, so we can break early
            
            if (dp[i - coin] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[reducedAmount] == INT_MAX ? -1 : dp[reducedAmount];
}

// Helper function implementations
int CoinChange::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int CoinChange::gcdArray(const std::vector<int>& nums) {
    int result = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        result = gcd(result, nums[i]);
        if (result == 1) break; // Early termination
    }
    return result;
}

bool CoinChange::canMakeAmount(const std::vector<int>& coins, int amount) {
    // Simple check using GCD
    return amount % gcdArray(coins) == 0;
}

}
}