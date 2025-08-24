#include <gtest/gtest.h>
#include "../../src/easy/best_time_to_buy_and_sell_stock_ii.h"
#include <vector>
#include <algorithm>

namespace leetcode {
namespace easy {
namespace test {

class BestTimeToBuyAndSellStockIITest : public ::testing::Test {
protected:
    // Test all approaches
    void testAllApproaches(std::vector<int> prices, int expected) {
        BestTimeToBuyAndSellStockII solution;
        
        // Make copies for each approach since some might modify the input
        auto prices1 = prices;
        auto prices2 = prices;
        auto prices3 = prices;
        auto prices4 = prices;
        auto prices5 = prices;
        auto prices6 = prices;
        
        EXPECT_EQ(solution.maxProfitGreedy(prices1), expected) 
            << "Greedy approach failed for prices: " << vectorToString(prices);
        EXPECT_EQ(solution.maxProfitDP(prices2), expected) 
            << "DP approach failed for prices: " << vectorToString(prices);
        EXPECT_EQ(solution.maxProfitPeakValley(prices3), expected) 
            << "Peak-Valley approach failed for prices: " << vectorToString(prices);
        EXPECT_EQ(solution.maxProfitRecursive(prices4), expected) 
            << "Recursive approach failed for prices: " << vectorToString(prices);
        EXPECT_EQ(solution.maxProfitTwoPointer(prices5), expected) 
            << "Two-pointer approach failed for prices: " << vectorToString(prices);
        EXPECT_EQ(solution.maxProfitFunctional(prices6), expected) 
            << "Functional approach failed for prices: " << vectorToString(prices);
    }
    
    // Helper to convert vector to string for error messages
    std::string vectorToString(const std::vector<int>& vec) {
        std::string result = "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) result += ", ";
            result += std::to_string(vec[i]);
        }
        result += "]";
        return result;
    }
};

// LeetCode Example Test Cases

TEST_F(BestTimeToBuyAndSellStockIITest, LeetCodeExample1) {
    // Input: prices = [7,1,5,3,6,4]
    // Output: 7
    // Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
    // Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
    // Total profit is 4 + 3 = 7.
    testAllApproaches({7, 1, 5, 3, 6, 4}, 7);
}

TEST_F(BestTimeToBuyAndSellStockIITest, LeetCodeExample2) {
    // Input: prices = [1,2,3,4,5]
    // Output: 4
    // Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    // Total profit is 4.
    testAllApproaches({1, 2, 3, 4, 5}, 4);
}

TEST_F(BestTimeToBuyAndSellStockIITest, LeetCodeExample3) {
    // Input: prices = [7,6,4,3,1]
    // Output: 0
    // Explanation: There is no way to make a positive profit, so we never buy the stock.
    testAllApproaches({7, 6, 4, 3, 1}, 0);
}

// Edge Cases

TEST_F(BestTimeToBuyAndSellStockIITest, SingleDay) {
    // Only one day, no transactions possible
    testAllApproaches({5}, 0);
}

TEST_F(BestTimeToBuyAndSellStockIITest, TwoDaysProfit) {
    // Two days with profit opportunity
    testAllApproaches({1, 5}, 4);
}

TEST_F(BestTimeToBuyAndSellStockIITest, TwoDaysLoss) {
    // Two days with no profit opportunity
    testAllApproaches({5, 1}, 0);
}

TEST_F(BestTimeToBuyAndSellStockIITest, AllSamePrices) {
    // All prices are the same
    testAllApproaches({3, 3, 3, 3, 3}, 0);
}

TEST_F(BestTimeToBuyAndSellStockIITest, EmptyArray) {
    // Empty price array
    testAllApproaches({}, 0);
}

// Pattern-Based Tests

TEST_F(BestTimeToBuyAndSellStockIITest, StrictlyIncreasing) {
    // Continuously increasing prices
    testAllApproaches({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 9);
}

TEST_F(BestTimeToBuyAndSellStockIITest, StrictlyDecreasing) {
    // Continuously decreasing prices
    testAllApproaches({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 0);
}

TEST_F(BestTimeToBuyAndSellStockIITest, AlternatingUpDown) {
    // Alternating up and down pattern
    testAllApproaches({1, 3, 2, 4, 1, 5}, 8); // (3-1) + (4-2) + (5-1) = 2 + 2 + 4 = 8
}

TEST_F(BestTimeToBuyAndSellStockIITest, VPattern) {
    // V-shaped pattern (down then up)
    testAllApproaches({5, 3, 1, 4, 6}, 5); // Buy at 1, sell at 6
}

TEST_F(BestTimeToBuyAndSellStockIITest, InvertedVPattern) {
    // Inverted V pattern (up then down)
    testAllApproaches({1, 4, 6, 3, 2}, 5); // Sell at peak before decline
}

// Multiple Peak-Valley Scenarios

TEST_F(BestTimeToBuyAndSellStockIITest, MultiplePeaksValleys) {
    // Multiple clear buy/sell opportunities
    testAllApproaches({2, 1, 4, 5, 2, 9, 7}, 11); // (4-1) + (5-4) + (9-2) = 3 + 1 + 7 = 11
}

TEST_F(BestTimeToBuyAndSellStockIITest, FlatThenRise) {
    // Flat prices then rise
    testAllApproaches({3, 3, 3, 3, 3, 5, 7}, 4); // (5-3) + (7-5) = 2 + 2 = 4
}

TEST_F(BestTimeToBuyAndSellStockIITest, RiseThenFlat) {
    // Rise then flat prices
    testAllApproaches({1, 3, 5, 5, 5, 5}, 4); // Buy at 1, sell at 5
}

// Boundary Value Tests

TEST_F(BestTimeToBuyAndSellStockIITest, MinimumPrices) {
    // Minimum constraint values
    testAllApproaches({0, 0, 0}, 0);
}

TEST_F(BestTimeToBuyAndSellStockIITest, MaximumPrices) {
    // Maximum constraint values
    testAllApproaches({10000, 10000, 10000}, 0);
}

TEST_F(BestTimeToBuyAndSellStockIITest, MinToMaxProfit) {
    // Maximum possible profit scenario
    testAllApproaches({0, 10000}, 10000);
}

TEST_F(BestTimeToBuyAndSellStockIITest, LargeVolatility) {
    // High volatility scenario
    testAllApproaches({0, 10000, 0, 10000, 0}, 20000);
}

// Real-World Scenarios

TEST_F(BestTimeToBuyAndSellStockIITest, StockCrashRecovery) {
    // Crash followed by recovery
    testAllApproaches({100, 50, 25, 30, 40, 60, 80}, 55); // Buy at 25, sell at 80
}

TEST_F(BestTimeToBuyAndSellStockIITest, BubbleBurst) {
    // Bubble formation and burst
    testAllApproaches({10, 20, 40, 80, 160, 80, 40, 20}, 150); // Sell at peak before crash
}

TEST_F(BestTimeToBuyAndSellStockIITest, SidewaysMarket) {
    // Market with small fluctuations
    testAllApproaches({50, 52, 48, 51, 49, 53, 47}, 9); // (52-50) + (51-48) + (53-49) = 2 + 3 + 4 = 9
}

// Complex Patterns

TEST_F(BestTimeToBuyAndSellStockIITest, DoubleBottom) {
    // Double bottom pattern
    testAllApproaches({5, 3, 4, 3, 6}, 4); // (4-3) + (6-3) = 1 + 3 = 4
}

TEST_F(BestTimeToBuyAndSellStockIITest, DoubleTop) {
    // Double top pattern
    testAllApproaches({1, 5, 3, 5, 2}, 6); // (5-1) + (5-3) = 4 + 2 = 6
}

TEST_F(BestTimeToBuyAndSellStockIITest, Sawtooth) {
    // Sawtooth pattern
    testAllApproaches({1, 5, 2, 6, 3, 7, 4}, 12); // (5-1)+(6-2)+(7-3) = 4+4+4 = 12
}

// Performance and Stress Tests

TEST_F(BestTimeToBuyAndSellStockIITest, LargeIncreasingArray) {
    // Large array with increasing trend
    std::vector<int> prices;
    for (int i = 0; i < 1000; ++i) {
        prices.push_back(i);
    }
    testAllApproaches(prices, 999); // Buy at 0, sell at 999
}

TEST_F(BestTimeToBuyAndSellStockIITest, LargeDecreasingArray) {
    // Large array with decreasing trend
    std::vector<int> prices;
    for (int i = 1000; i > 0; --i) {
        prices.push_back(i);
    }
    testAllApproaches(prices, 0); // No profit possible
}

TEST_F(BestTimeToBuyAndSellStockIITest, LargeRandomPattern) {
    // Large array with alternating pattern
    std::vector<int> prices;
    for (int i = 0; i < 500; ++i) {
        prices.push_back(i % 2 == 0 ? 10 : 20);
    }
    // Should capture profit on every up move
    int expected = 250 * 10; // 250 moves from 10 to 20
    testAllApproaches(prices, expected);
}

// Specific Algorithm Tests

TEST_F(BestTimeToBuyAndSellStockIITest, PeakValleyDetection) {
    // Test peak-valley detection specifically
    BestTimeToBuyAndSellStockII solution;
    std::vector<int> prices = {1, 7, 4, 3, 6, 2, 8};
    
    // All approaches should give same result
    std::vector<int> copies(6, 0);
    for (int i = 0; i < 6; ++i) {
        auto copy = prices;
        switch (i) {
            case 0: copies[i] = solution.maxProfitGreedy(copy); break;
            case 1: copies[i] = solution.maxProfitDP(copy); break;
            case 2: copies[i] = solution.maxProfitPeakValley(copy); break;
            case 3: copies[i] = solution.maxProfitRecursive(copy); break;
            case 4: copies[i] = solution.maxProfitTwoPointer(copy); break;
            case 5: copies[i] = solution.maxProfitFunctional(copy); break;
        }
    }
    
    // All should give same result
    for (int i = 1; i < 6; ++i) {
        EXPECT_EQ(copies[0], copies[i]) << "Approach " << i << " differs from greedy";
    }
}

// Mathematical Property Tests

TEST_F(BestTimeToBuyAndSellStockIITest, SumOfPositiveDifferences) {
    // Verify that result equals sum of positive differences
    std::vector<int> prices = {3, 1, 4, 1, 5, 9, 2, 6};
    
    BestTimeToBuyAndSellStockII solution;
    auto copy = prices;
    int result = solution.maxProfitGreedy(copy);
    
    // Calculate expected: sum of positive consecutive differences
    int expected = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i-1]) {
            expected += prices[i] - prices[i-1];
        }
    }
    
    EXPECT_EQ(result, expected);
}

// Edge Case Stress Tests

TEST_F(BestTimeToBuyAndSellStockIITest, AllZeroPrices) {
    testAllApproaches({0, 0, 0, 0, 0, 0}, 0);
}

TEST_F(BestTimeToBuyAndSellStockIITest, SinglePriceFluctuation) {
    // Tiny fluctuation
    testAllApproaches({1000, 1001, 1000, 1001}, 2);
}

TEST_F(BestTimeToBuyAndSellStockIITest, MaximumConstraintSize) {
    // Test at constraint boundary (simplified for test speed)
    std::vector<int> prices(100, 5);
    prices[50] = 10; // One price spike
    testAllApproaches(prices, 5); // Buy before spike, sell at spike
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode