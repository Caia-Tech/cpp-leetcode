#include <gtest/gtest.h>
#include "../../src/medium/coin_change.h"
#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {
namespace test {

class CoinChangeTest : public ::testing::Test {
protected:
    CoinChange solution;
    
    void testAllApproaches(std::vector<int> coins, int amount, int expected) {
        std::vector<int> coins1 = coins, coins2 = coins, coins3 = coins;
        std::vector<int> coins4 = coins, coins5 = coins, coins6 = coins;
        
        EXPECT_EQ(solution.coinChange(coins1, amount), expected) 
            << "DP Bottom-Up approach failed for amount " << amount;
        EXPECT_EQ(solution.coinChangeBFS(coins2, amount), expected) 
            << "BFS approach failed for amount " << amount;
        EXPECT_EQ(solution.coinChangeDFS(coins3, amount), expected) 
            << "DFS with Memoization approach failed for amount " << amount;
        EXPECT_EQ(solution.coinChangeKnapsack(coins4, amount), expected) 
            << "Knapsack approach failed for amount " << amount;
        EXPECT_EQ(solution.coinChangeGreedyBacktrack(coins5, amount), expected) 
            << "Greedy Backtrack approach failed for amount " << amount;
        EXPECT_EQ(solution.coinChangeMath(coins6, amount), expected) 
            << "Mathematical approach failed for amount " << amount;
    }
};

// Basic functionality tests
TEST_F(CoinChangeTest, ZeroAmount) {
    testAllApproaches({1, 2, 5}, 0, 0);
    testAllApproaches({2}, 0, 0);
    testAllApproaches({1, 3, 4}, 0, 0);
}

TEST_F(CoinChangeTest, ExactCoinMatch) {
    testAllApproaches({1, 2, 5}, 1, 1);
    testAllApproaches({1, 2, 5}, 2, 1);
    testAllApproaches({1, 2, 5}, 5, 1);
    testAllApproaches({7, 3, 11}, 7, 1);
}

TEST_F(CoinChangeTest, StandardExamples) {
    testAllApproaches({1, 2, 5}, 11, 3);
    // 11 = 5 + 5 + 1
    
    testAllApproaches({2}, 3, -1);
    // Can't make 3 with only 2s
    
    testAllApproaches({1}, 2, 2);
    // 2 = 1 + 1
}

TEST_F(CoinChangeTest, LeetCodeExamples) {
    testAllApproaches({1, 2, 5}, 11, 3);
    testAllApproaches({2}, 3, -1);
    testAllApproaches({1}, 0, 0);
    testAllApproaches({1, 3, 4}, 6, 2);
    // 6 = 3 + 3
}

// Edge cases
TEST_F(CoinChangeTest, SingleCoin) {
    testAllApproaches({1}, 100, 100);
    testAllApproaches({5}, 15, 3);
    testAllApproaches({5}, 17, -1);
    testAllApproaches({7}, 14, 2);
    testAllApproaches({7}, 15, -1);
}

TEST_F(CoinChangeTest, ImpossibleAmount) {
    testAllApproaches({3, 5}, 1, -1);
    testAllApproaches({2, 4, 6}, 7, -1);
    testAllApproaches({5, 10}, 3, -1);
}

TEST_F(CoinChangeTest, LargeCoinValues) {
    testAllApproaches({186, 419, 83, 408}, 6249, 20);
    // Complex case requiring careful computation
    
    testAllApproaches({470, 18, 66, 301, 403, 112, 360}, 8235, 20);
}

TEST_F(CoinChangeTest, PowersOfTwo) {
    testAllApproaches({1, 2, 4, 8, 16}, 31, 5);
    // 31 = 16 + 8 + 4 + 2 + 1
    
    testAllApproaches({1, 2, 4, 8}, 15, 4);
    // 15 = 8 + 4 + 2 + 1
}

// Pattern-based tests
TEST_F(CoinChangeTest, ConsecutiveCoins) {
    testAllApproaches({1, 2, 3}, 6, 2);
    // 6 = 3 + 3
    
    testAllApproaches({1, 2, 3, 4, 5}, 11, 3);
    // 11 = 5 + 5 + 1 or 5 + 4 + 2
}

TEST_F(CoinChangeTest, FibonacciCoins) {
    testAllApproaches({1, 2, 3, 5, 8}, 12, 3);
    // 12 = 8 + 3 + 1 (3 coins) or 5 + 5 + 2 (3 coins)
    
    testAllApproaches({1, 1, 2, 3, 5}, 10, 2);
    // 10 = 5 + 5
}

TEST_F(CoinChangeTest, PrimeCoins) {
    testAllApproaches({2, 3, 5, 7}, 12, 2);
    // 12 = 7 + 5
    
    testAllApproaches({2, 3, 5, 7, 11}, 25, 3);
    // 25 = 11 + 7 + 7
}

// Greedy doesn't work cases
TEST_F(CoinChangeTest, GreedyFails) {
    testAllApproaches({1, 3, 4}, 6, 2);
    // Greedy would pick 4+1+1=3 coins, optimal is 3+3=2 coins
    
    testAllApproaches({1, 5, 6}, 9, 4);
    // Greedy would pick 6+1+1+1=4 coins, optimal is 5+4(not available) or 3*3(not available)
    // Actually 6+3(using 1+1+1) = 4 coins minimum
    // Correction: 1+1+1+6 = 4 or 1+1+1+1+5 = 5, so min is 4
    // Actually checking: 9 = 6+1+1+1 = 4 coins or 5+1+1+1+1 = 5 coins
    // So the answer should be 4, not 3. Let me recalculate...
}

TEST_F(CoinChangeTest, GreedyFailsCorrected) {
    std::vector<int> coins = {1, 5, 6};
    // For amount 9: optimal is 3+6 but we don't have 3
    // So we need 6+1+1+1 = 4 coins
    std::vector<int> coins1 = coins, coins2 = coins, coins3 = coins;
    std::vector<int> coins4 = coins, coins5 = coins, coins6 = coins;
    
    EXPECT_EQ(solution.coinChange(coins1, 9), 4);
    EXPECT_EQ(solution.coinChangeBFS(coins2, 9), 4);
    EXPECT_EQ(solution.coinChangeDFS(coins3, 9), 4);
    EXPECT_EQ(solution.coinChangeKnapsack(coins4, 9), 4);
    EXPECT_EQ(solution.coinChangeGreedyBacktrack(coins5, 9), 4);
    EXPECT_EQ(solution.coinChangeMath(coins6, 9), 4);
}

// Special patterns
TEST_F(CoinChangeTest, AllOnes) {
    std::vector<int> coins(10, 1); // 10 coins all value 1
    testAllApproaches(coins, 7, 7);
}

TEST_F(CoinChangeTest, GeometricProgression) {
    testAllApproaches({1, 3, 9, 27}, 40, 4);
    // 40 = 27 + 9 + 3 + 1
}

TEST_F(CoinChangeTest, TwoCoinTypes) {
    testAllApproaches({2, 5}, 11, 4);
    // 11 = 5 + 2 + 2 + 2
    
    testAllApproaches({3, 7}, 17, 3);
    // 17 = 7 + 7 + 3
}

// Performance edge cases
TEST_F(CoinChangeTest, MaxAmount) {
    testAllApproaches({1, 2, 5}, 100, 20);
    // 100 = 20 * 5
    
    testAllApproaches({1}, 10000, 10000);
    // Maximum amount with single penny
}

TEST_F(CoinChangeTest, ManyCoins) {
    testAllApproaches({1, 5, 10, 21, 25}, 63, 3);
    // 63 = 21 + 21 + 21
}

// Mathematical optimization tests
TEST_F(CoinChangeTest, GCDOptimization) {
    testAllApproaches({4, 6, 10}, 8, 2);
    // GCD = 2, so 8 is achievable: 8 = 4 + 4
    
    testAllApproaches({6, 9, 15}, 12, 2);
    // GCD = 3, 12 is achievable: 12 = 6 + 6
    
    testAllApproaches({4, 6, 10}, 9, -1);
    // GCD = 2, 9 is odd so not achievable
}

// Complex scenarios
TEST_F(CoinChangeTest, SubsetSumVariant) {
    testAllApproaches({1, 2, 5, 10}, 18, 4);
    // 18 = 10 + 5 + 2 + 1
    // Actually: 18 = 10 + 5 + 2 + 1 = 4 coins
    // Or: 18 = 10 + 5 + 3(1+2) = 4 coins
    // Or: 18 = 10 + 8(5+2+1) = 4 coins
    // Actually checking: 18 = 10 + 5 + 2 + 1 = 4 or 10 + 5 + 3*1 = 5
    // Optimal: 10 + 5 + 2 + 1 = 4 coins
}

TEST_F(CoinChangeTest, SubsetSumCorrected) {
    std::vector<int> coins = {1, 2, 5, 10};
    std::vector<int> coins1 = coins, coins2 = coins, coins3 = coins;
    std::vector<int> coins4 = coins, coins5 = coins, coins6 = coins;
    
    // 18 = 10 + 5 + 2 + 1 = 4 coins minimum
    EXPECT_EQ(solution.coinChange(coins1, 18), 4);
    EXPECT_EQ(solution.coinChangeBFS(coins2, 18), 4);
    EXPECT_EQ(solution.coinChangeDFS(coins3, 18), 4);
    EXPECT_EQ(solution.coinChangeKnapsack(coins4, 18), 4);
    EXPECT_EQ(solution.coinChangeGreedyBacktrack(coins5, 18), 4);
    EXPECT_EQ(solution.coinChangeMath(coins6, 18), 4);
}

// Algorithm-specific validation
TEST_F(CoinChangeTest, BFSPathLength) {
    // BFS should find shortest path (minimum coins)
    std::vector<int> coins = {1, 3, 4};
    EXPECT_EQ(solution.coinChangeBFS(coins, 10), 3);
    // 10 = 4 + 3 + 3
}

TEST_F(CoinChangeTest, MemoizationEfficiency) {
    // DFS with memoization should handle repeated subproblems efficiently
    std::vector<int> coins = {1, 2, 5, 10, 20, 50};
    EXPECT_EQ(solution.coinChangeDFS(coins, 99), 6);
    // 99 = 50 + 20 + 20 + 5 + 2 + 2
}

TEST_F(CoinChangeTest, GreedyWithBacktrackOptimal) {
    // Cases where greedy with backtrack finds optimal
    std::vector<int> coins = {1, 5, 10, 25};
    EXPECT_EQ(solution.coinChangeGreedyBacktrack(coins, 30), 2);
    // 30 = 25 + 5 (greedy works)
    
    coins = {1, 7, 10};
    EXPECT_EQ(solution.coinChangeGreedyBacktrack(coins, 14), 2);
    // 14 = 7 + 7 (needs backtrack from 10+1+1+1+1)
}

// Stress tests
TEST_F(CoinChangeTest, RandomCoinSystems) {
    testAllApproaches({83, 186, 408, 419}, 6249, 20);
    testAllApproaches({3, 7, 405, 436}, 8839, 25);
}

TEST_F(CoinChangeTest, USCoinSystem) {
    testAllApproaches({1, 5, 10, 25}, 41, 4);
    // 41 = 25 + 10 + 5 + 1
    
    testAllApproaches({1, 5, 10, 25}, 99, 9);
    // 99 = 3*25 + 2*10 + 4*1 or 3*25 + 24*1
    // Actually: 99 = 75 + 24, best is 3*25 + 2*10 + 4*1 = 9 coins
}

TEST_F(CoinChangeTest, EuroCoinSystem) {
    testAllApproaches({1, 2, 5, 10, 20, 50}, 88, 6);
    // 88 = 50 + 20 + 10 + 5 + 2 + 1 = 6 coins
    // Or: 88 = 50 + 20 + 10 + 5 + 3*1 = 7 coins
    // Or: 88 = 50 + 20 + 18 where 18 = 10 + 5 + 2 + 1 = 5 total
    // Actually checking: 88 = 50 + 20 + 10 + 5 + 2 + 1 = 6 coins minimum
}

TEST_F(CoinChangeTest, EuroCoinCorrected) {
    std::vector<int> coins = {1, 2, 5, 10, 20, 50};
    std::vector<int> coins1 = coins, coins2 = coins, coins3 = coins;
    std::vector<int> coins4 = coins, coins5 = coins, coins6 = coins;
    
    // 88 = 50 + 20 + 10 + 5 + 2 + 1 = 6 coins
    EXPECT_EQ(solution.coinChange(coins1, 88), 6);
    EXPECT_EQ(solution.coinChangeBFS(coins2, 88), 6);
    EXPECT_EQ(solution.coinChangeDFS(coins3, 88), 6);
    EXPECT_EQ(solution.coinChangeKnapsack(coins4, 88), 6);
    EXPECT_EQ(solution.coinChangeGreedyBacktrack(coins5, 88), 6);
    EXPECT_EQ(solution.coinChangeMath(coins6, 88), 6);
}

}
}
}