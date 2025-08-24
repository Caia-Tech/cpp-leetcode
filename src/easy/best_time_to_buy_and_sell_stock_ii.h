#pragma once

#include <vector>
#include <algorithm>
#include <functional>

namespace leetcode {
namespace easy {

/**
 * Problem 122: Best Time to Buy and Sell Stock II
 * 
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
 * 
 * On each day, you may decide to buy and/or sell the stock. You can only hold at most one share 
 * of the stock at any time. However, you can buy it then immediately sell it on the same day.
 * 
 * Find and return the maximum profit you can achieve.
 * 
 * Constraints:
 * - 1 <= prices.length <= 3 * 10^4
 * - 0 <= prices[i] <= 10^4
 */
class BestTimeToBuyAndSellStockII {
public:
    /**
     * Approach 1: Greedy Algorithm (Optimal)
     * 
     * Buy and sell whenever there's a price increase from one day to the next.
     * 
     * Reasoning: The key insight is that we can capture all upward price movements
     * by buying at every local minimum and selling at every local maximum. This
     * is equivalent to summing all positive differences between consecutive days.
     * Since we can transact on the same day, we don't need to track actual buy/sell
     * points - just accumulate profit from any price increase.
     * 
     * Time Complexity: O(n) - single pass through prices array
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Always - this is the optimal solution
     * Worst when: Never - this approach is universally preferred
     */
    int maxProfitGreedy(std::vector<int>& prices);

    /**
     * Approach 2: Dynamic Programming with States
     * 
     * Track the maximum profit for holding and not holding stock at each day.
     * 
     * Reasoning: Define two states: hold (currently own stock) and sold (don't own stock).
     * At each day, we can transition between states: buy (sold->hold), sell (hold->sold),
     * or do nothing. Use DP to track maximum profit for each state. This approach
     * clearly models the state transitions and can be extended to handle transaction
     * costs or limits easily.
     * 
     * Time Complexity: O(n) - process each day once
     * Space Complexity: O(1) - only track current state variables
     * 
     * Best when: Need to extend to handle transaction costs/limits, educational purposes
     * Worst when: Simple greedy solution is sufficient
     */
    int maxProfitDP(std::vector<int>& prices);

    /**
     * Approach 3: Peak and Valley Detection
     * 
     * Explicitly find local minima (valleys) and maxima (peaks) and buy at valleys, sell at peaks.
     * 
     * Reasoning: This approach makes the buy/sell strategy explicit by identifying
     * actual transaction points. Find consecutive valleys and peaks, then sum up
     * profit from each valley-peak pair. While conceptually clear, this requires
     * more complex logic to handle edge cases and is essentially equivalent to
     * the greedy approach but with more overhead.
     * 
     * Time Complexity: O(n) - scan for valleys and peaks
     * Space Complexity: O(1) - only track current state
     * 
     * Best when: Need explicit buy/sell points, visualization/explanation purposes
     * Worst when: Only need total profit, not transaction details
     */
    int maxProfitPeakValley(std::vector<int>& prices);

    /**
     * Approach 4: Recursion with Memoization
     * 
     * Use recursion to explore all possible buy/sell decisions with memoization.
     * 
     * Reasoning: For each day, we have choices: buy, sell, or do nothing.
     * Use recursion to explore all possibilities and memoization to avoid
     * recomputation. While this demonstrates the complete solution space,
     * it's overkill for this problem since the greedy approach gives optimal
     * solution directly. Useful for understanding the problem structure.
     * 
     * Time Complexity: O(n) - each state computed once with memoization
     * Space Complexity: O(n) - memoization table and recursion stack
     * 
     * Best when: Educational purposes, understanding decision tree structure
     * Worst when: Performance critical, simple greedy solution available
     */
    int maxProfitRecursive(std::vector<int>& prices);

    /**
     * Approach 5: Two-Pointer Technique
     * 
     * Use two pointers to track buy and sell opportunities.
     * 
     * Reasoning: Maintain two pointers - one for potential buy day and one for
     * current day. When current price is higher than buy price, add the difference
     * to profit and update buy pointer. This simulates the process of always
     * being ready to sell when price increases. Conceptually similar to greedy
     * but uses explicit pointer management.
     * 
     * Time Complexity: O(n) - single pass with two pointers
     * Space Complexity: O(1) - only pointer variables
     * 
     * Best when: Pointer manipulation preferred, clear buy/sell logic needed
     * Worst when: Simple difference calculation is clearer
     */
    int maxProfitTwoPointer(std::vector<int>& prices);

    /**
     * Approach 6: Functional Programming with Transform
     * 
     * Use functional programming paradigms to calculate profit differences.
     * 
     * Reasoning: Apply functional programming concepts by treating the problem
     * as a transformation of price array to profit differences, then filtering
     * and summing positive values. Use higher-order functions and lambda
     * expressions to create a pipeline of operations. While elegant, this
     * approach may have overhead from function calls and temporary collections.
     * 
     * Time Complexity: O(n) - transform and reduce operations
     * Space Complexity: O(n) - temporary difference array
     * 
     * Best when: Functional programming environment, pipeline operations preferred
     * Worst when: Memory efficient solution needed, performance critical
     */
    int maxProfitFunctional(std::vector<int>& prices);

private:
    // Helper for recursive approach
    int maxProfitHelper(std::vector<int>& prices, int day, bool holding, 
                       std::vector<std::vector<int>>& memo);
    
    // Helper for peak-valley approach
    struct TradePoint {
        int day;
        int price;
        bool isPeak;
        TradePoint(int d, int p, bool peak) : day(d), price(p), isPeak(peak) {}
    };
    
    std::vector<TradePoint> findTradePoints(std::vector<int>& prices);
    
    // Helper for functional approach
    std::function<int(const std::vector<int>&)> createProfitCalculator();
    
    // Constants for memoization
    static constexpr int MEMO_NOT_COMPUTED = -1;
};

}  // namespace easy
}  // namespace leetcode