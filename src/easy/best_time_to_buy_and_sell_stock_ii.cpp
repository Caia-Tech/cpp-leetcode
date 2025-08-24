#include "best_time_to_buy_and_sell_stock_ii.h"
#include <numeric>
#include <functional>

namespace leetcode {
namespace easy {

// Approach 1: Greedy Algorithm (Optimal)
int BestTimeToBuyAndSellStockII::maxProfitGreedy(std::vector<int>& prices) {
    if (prices.size() <= 1) return 0;
    
    int totalProfit = 0;
    
    // Add profit from every price increase
    for (size_t i = 1; i < prices.size(); ++i) {
        if (prices[i] > prices[i - 1]) {
            totalProfit += prices[i] - prices[i - 1];
        }
    }
    
    return totalProfit;
}

// Approach 2: Dynamic Programming with States
int BestTimeToBuyAndSellStockII::maxProfitDP(std::vector<int>& prices) {
    if (prices.empty()) return 0;
    
    // State variables: profit when holding stock vs not holding stock
    int hold = -prices[0];  // Bought stock on day 0
    int sold = 0;           // No stock, no transactions yet
    
    for (size_t i = 1; i < prices.size(); ++i) {
        int newHold = std::max(hold, sold - prices[i]); // Keep holding or buy today
        int newSold = std::max(sold, hold + prices[i]); // Keep not holding or sell today
        
        hold = newHold;
        sold = newSold;
    }
    
    // At the end, we should not be holding stock for maximum profit
    return sold;
}

// Approach 3: Peak and Valley Detection
int BestTimeToBuyAndSellStockII::maxProfitPeakValley(std::vector<int>& prices) {
    if (prices.size() <= 1) return 0;
    
    auto tradePoints = findTradePoints(prices);
    
    int totalProfit = 0;
    int buyPrice = -1;
    
    for (const auto& point : tradePoints) {
        if (!point.isPeak) {
            // Valley - buy
            buyPrice = point.price;
        } else {
            // Peak - sell
            if (buyPrice != -1) {
                totalProfit += point.price - buyPrice;
                buyPrice = -1;
            }
        }
    }
    
    return totalProfit;
}

std::vector<BestTimeToBuyAndSellStockII::TradePoint> 
BestTimeToBuyAndSellStockII::findTradePoints(std::vector<int>& prices) {
    std::vector<TradePoint> points;
    if (prices.size() <= 1) return points;
    
    int i = 0;
    int n = prices.size();
    
    while (i < n - 1) {
        // Find valley (local minimum)
        while (i < n - 1 && prices[i] >= prices[i + 1]) {
            i++;
        }
        
        if (i == n - 1) break; // No more valleys
        
        points.emplace_back(i, prices[i], false); // Valley
        
        // Find peak (local maximum)
        while (i < n - 1 && prices[i] <= prices[i + 1]) {
            i++;
        }
        
        points.emplace_back(i, prices[i], true); // Peak
    }
    
    return points;
}

// Approach 4: Recursion with Memoization
int BestTimeToBuyAndSellStockII::maxProfitRecursive(std::vector<int>& prices) {
    if (prices.empty()) return 0;
    
    // Memoization table: memo[day][holding]
    // holding: 0 = not holding, 1 = holding
    std::vector<std::vector<int>> memo(prices.size(), 
                                      std::vector<int>(2, MEMO_NOT_COMPUTED));
    
    return maxProfitHelper(prices, 0, false, memo);
}

int BestTimeToBuyAndSellStockII::maxProfitHelper(std::vector<int>& prices, int day, 
                                                bool holding, 
                                                std::vector<std::vector<int>>& memo) {
    // Base case: no more days
    if (day >= static_cast<int>(prices.size())) {
        return 0;
    }
    
    // Check memoization
    int holdingIndex = holding ? 1 : 0;
    if (memo[day][holdingIndex] != MEMO_NOT_COMPUTED) {
        return memo[day][holdingIndex];
    }
    
    int profit = 0;
    
    if (holding) {
        // We're holding stock: can sell or do nothing
        int sellProfit = prices[day] + maxProfitHelper(prices, day + 1, false, memo);
        int holdProfit = maxProfitHelper(prices, day + 1, true, memo);
        profit = std::max(sellProfit, holdProfit);
    } else {
        // We're not holding stock: can buy or do nothing
        int buyProfit = -prices[day] + maxProfitHelper(prices, day + 1, true, memo);
        int waitProfit = maxProfitHelper(prices, day + 1, false, memo);
        profit = std::max(buyProfit, waitProfit);
    }
    
    memo[day][holdingIndex] = profit;
    return profit;
}

// Approach 5: Two-Pointer Technique
int BestTimeToBuyAndSellStockII::maxProfitTwoPointer(std::vector<int>& prices) {
    if (prices.size() <= 1) return 0;
    
    int totalProfit = 0;
    int buyPrice = prices[0];
    
    for (size_t i = 1; i < prices.size(); ++i) {
        if (prices[i] > buyPrice) {
            // Price went up, sell and capture profit
            totalProfit += prices[i] - buyPrice;
        }
        // Always update buy price to current price (ready for next opportunity)
        buyPrice = prices[i];
    }
    
    return totalProfit;
}

// Approach 6: Functional Programming with Transform
int BestTimeToBuyAndSellStockII::maxProfitFunctional(std::vector<int>& prices) {
    auto profitCalculator = createProfitCalculator();
    return profitCalculator(prices);
}

std::function<int(const std::vector<int>&)> 
BestTimeToBuyAndSellStockII::createProfitCalculator() {
    return [](const std::vector<int>& prices) -> int {
        if (prices.size() <= 1) return 0;
        
        // Transform prices to daily differences
        std::vector<int> differences;
        differences.reserve(prices.size() - 1);
        
        std::transform(prices.begin() + 1, prices.end(), prices.begin(),
                      std::back_inserter(differences),
                      [](int today, int yesterday) { return today - yesterday; });
        
        // Filter positive differences and sum them
        return std::accumulate(differences.begin(), differences.end(), 0,
                              [](int sum, int diff) { return sum + std::max(0, diff); });
    };
}

// Define static constant
const int BestTimeToBuyAndSellStockII::MEMO_NOT_COMPUTED;

}  // namespace easy
}  // namespace leetcode