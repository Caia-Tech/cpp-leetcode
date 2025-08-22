#pragma once

#include <vector>
#include <climits>

namespace leetcode {
namespace easy {

/**
 * Problem 121: Best Time to Buy and Sell Stock
 * 
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a 
 * different day in the future to sell that stock.
 * 
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any 
 * profit, return 0.
 * 
 * Constraints:
 * - 1 <= prices.length <= 10^5
 * - 0 <= prices[i] <= 10^4
 */
class BestTimeToBuyAndSellStock {
public:
    /**
     * Approach 1: Brute Force
     * 
     * Check all possible buy-sell pairs.
     * 
     * Reasoning: This is the most straightforward approach - examine every possible
     * combination of buy day (earlier) and sell day (later) to find maximum profit.
     * For each potential buy day, check all subsequent days as potential sell days.
     * While inefficient, it's easy to understand and implement correctly, making it
     * a good baseline for testing and understanding the problem constraints.
     * 
     * Time Complexity: O(n^2) - nested loops through all pairs
     * Space Complexity: O(1) - only tracking maximum profit
     * 
     * Best when: Small arrays, need simple baseline implementation
     * Worst when: Large arrays where O(n^2) becomes prohibitive
     */
    int maxProfitBruteForce(const std::vector<int>& prices);

    /**
     * Approach 2: Single Pass (Kadane's Algorithm Variant)
     * 
     * Track minimum price and maximum profit in single pass.
     * 
     * Reasoning: This is the optimal solution. Key insight: to maximize profit,
     * we want to buy at the lowest price before selling at the highest price.
     * As we iterate through prices, keep track of the minimum price seen so far
     * and calculate profit if we sell at current price. This ensures we always
     * consider the best possible buy price for each potential sell price.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only two variables needed
     * 
     * Best when: Need optimal performance, standard interview solution
     * Worst when: Need to track actual buy/sell days (requires modification)
     */
    int maxProfitSinglePass(const std::vector<int>& prices);

    /**
     * Approach 3: Dynamic Programming
     * 
     * Use DP to track maximum profit at each day.
     * 
     * Reasoning: This approach explicitly stores the maximum profit achievable
     * up to each day. While conceptually clear for DP learning, it uses extra
     * space that isn't necessary. The DP state is: dp[i] = maximum profit
     * achievable from day 0 to day i. This approach helps understand the
     * overlapping subproblems structure of the problem.
     * 
     * Time Complexity: O(n) - single pass to fill DP array
     * Space Complexity: O(n) - DP array storage
     * 
     * Best when: Learning DP concepts, need to track intermediate results
     * Worst when: Memory is constrained and O(1) space solution exists
     */
    int maxProfitDP(const std::vector<int>& prices);

    /**
     * Approach 4: Divide and Conquer
     * 
     * Recursively find max profit in subarrays.
     * 
     * Reasoning: This approach demonstrates divide-and-conquer thinking. Split array
     * in half and consider three cases: maximum profit entirely in left half,
     * entirely in right half, or crossing the midpoint (buy in left, sell in right).
     * While not optimal, it shows how to decompose the problem and can potentially
     * be parallelized.
     * 
     * Time Complexity: O(n log n) - T(n) = 2T(n/2) + O(n)
     * Space Complexity: O(log n) - recursion stack depth
     * 
     * Best when: Can parallelize left/right computations, educational purposes
     * Worst when: Single-threaded and O(n) solution is available
     */
    int maxProfitDivideConquer(const std::vector<int>& prices);

    /**
     * Approach 5: Transform to Maximum Subarray Problem
     * 
     * Convert to finding maximum sum subarray of price differences.
     * 
     * Reasoning: Transform the problem by creating an array of price differences
     * (prices[i+1] - prices[i]). The maximum profit from buying and selling
     * becomes the maximum sum subarray of these differences. This demonstrates
     * how to reduce one problem to another well-known problem (Maximum Subarray).
     * Apply Kadane's algorithm to the difference array.
     * 
     * Time Complexity: O(n) - create differences + Kadane's algorithm
     * Space Complexity: O(n) - storing price differences array
     * 
     * Best when: Want to reuse Maximum Subarray solution, problem transformation
     * Worst when: Direct approach is simpler and more memory efficient
     */
    int maxProfitMaxSubarray(const std::vector<int>& prices);

    /**
     * Approach 6: Two Pointers
     * 
     * Use two pointers to track buy and sell days.
     * 
     * Reasoning: Use two pointers approach where left pointer tracks the potential
     * buy day and right pointer tracks the potential sell day. When we find a lower
     * price (better buy opportunity), move the buy pointer there. Otherwise, calculate
     * profit and update maximum. This approach makes the "buy low, sell high"
     * strategy more explicit than the single-pass approach.
     * 
     * Time Complexity: O(n) - single pass with two pointers
     * Space Complexity: O(1) - only pointer variables
     * 
     * Best when: Two-pointer pattern is preferred, want explicit buy/sell tracking
     * Worst when: Single-pass minimum tracking is simpler
     */
    int maxProfitTwoPointers(const std::vector<int>& prices);

private:
    struct Result {
        int maxProfit;
        int minPrice;
        int maxPrice;
    };
    
    Result divideConquerHelper(const std::vector<int>& prices, int left, int right);
};

}
}