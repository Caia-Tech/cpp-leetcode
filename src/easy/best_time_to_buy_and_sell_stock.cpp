#include "best_time_to_buy_and_sell_stock.h"
#include <algorithm>
#include <climits>

namespace leetcode {
namespace easy {

int BestTimeToBuyAndSellStock::maxProfitBruteForce(const std::vector<int>& prices) {
    int maxProfit = 0;
    int n = prices.size();
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int profit = prices[j] - prices[i];
            maxProfit = std::max(maxProfit, profit);
        }
    }
    
    return maxProfit;
}

int BestTimeToBuyAndSellStock::maxProfitSinglePass(const std::vector<int>& prices) {
    if (prices.empty()) return 0;
    
    int minPrice = prices[0];
    int maxProfit = 0;
    
    for (int i = 1; i < prices.size(); ++i) {
        minPrice = std::min(minPrice, prices[i]);
        maxProfit = std::max(maxProfit, prices[i] - minPrice);
    }
    
    return maxProfit;
}

int BestTimeToBuyAndSellStock::maxProfitDP(const std::vector<int>& prices) {
    if (prices.empty()) return 0;
    
    int n = prices.size();
    std::vector<int> dp(n, 0);
    int minPrice = prices[0];
    
    for (int i = 1; i < n; ++i) {
        dp[i] = std::max(dp[i - 1], prices[i] - minPrice);
        minPrice = std::min(minPrice, prices[i]);
    }
    
    return dp[n - 1];
}

int BestTimeToBuyAndSellStock::maxProfitDivideConquer(const std::vector<int>& prices) {
    if (prices.size() < 2) return 0;
    
    Result result = divideConquerHelper(prices, 0, prices.size() - 1);
    return result.maxProfit;
}

BestTimeToBuyAndSellStock::Result BestTimeToBuyAndSellStock::divideConquerHelper(
    const std::vector<int>& prices, int left, int right) {
    
    if (left == right) {
        return {0, prices[left], prices[left]};
    }
    
    int mid = left + (right - left) / 2;
    
    Result leftResult = divideConquerHelper(prices, left, mid);
    Result rightResult = divideConquerHelper(prices, mid + 1, right);
    
    int crossProfit = rightResult.maxPrice - leftResult.minPrice;
    
    Result result;
    result.maxProfit = std::max({leftResult.maxProfit, rightResult.maxProfit, crossProfit});
    result.minPrice = std::min(leftResult.minPrice, rightResult.minPrice);
    result.maxPrice = std::max(leftResult.maxPrice, rightResult.maxPrice);
    
    return result;
}

int BestTimeToBuyAndSellStock::maxProfitMaxSubarray(const std::vector<int>& prices) {
    if (prices.size() < 2) return 0;
    
    std::vector<int> diff(prices.size() - 1);
    for (int i = 0; i < prices.size() - 1; ++i) {
        diff[i] = prices[i + 1] - prices[i];
    }
    
    int maxSoFar = 0;
    int maxEndingHere = 0;
    
    for (int d : diff) {
        maxEndingHere = std::max(0, maxEndingHere + d);
        maxSoFar = std::max(maxSoFar, maxEndingHere);
    }
    
    return maxSoFar;
}

int BestTimeToBuyAndSellStock::maxProfitTwoPointers(const std::vector<int>& prices) {
    if (prices.size() < 2) return 0;
    
    int buyDay = 0;
    int sellDay = 1;
    int maxProfit = 0;
    
    while (sellDay < prices.size()) {
        int profit = prices[sellDay] - prices[buyDay];
        
        if (profit > 0) {
            maxProfit = std::max(maxProfit, profit);
        } else {
            buyDay = sellDay;
        }
        
        sellDay++;
    }
    
    return maxProfit;
}

}
}