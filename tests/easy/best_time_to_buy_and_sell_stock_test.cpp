#include <gtest/gtest.h>
#include "easy/best_time_to_buy_and_sell_stock.h"

using namespace leetcode::easy;

class BestTimeToBuyAndSellStockTest : public ::testing::Test {
protected:
    BestTimeToBuyAndSellStock solution;
    
    void verifyAllApproaches(const std::vector<int>& prices, int expected) {
        EXPECT_EQ(solution.maxProfitBruteForce(prices), expected) 
            << "Brute Force failed";
        EXPECT_EQ(solution.maxProfitSinglePass(prices), expected) 
            << "Single Pass failed";
        EXPECT_EQ(solution.maxProfitDP(prices), expected) 
            << "DP failed";
        EXPECT_EQ(solution.maxProfitDivideConquer(prices), expected) 
            << "Divide and Conquer failed";
        EXPECT_EQ(solution.maxProfitMaxSubarray(prices), expected) 
            << "Max Subarray failed";
        EXPECT_EQ(solution.maxProfitTwoPointers(prices), expected) 
            << "Two Pointers failed";
    }
};

TEST_F(BestTimeToBuyAndSellStockTest, BasicProfit) {
    verifyAllApproaches({7, 1, 5, 3, 6, 4}, 5);
}

TEST_F(BestTimeToBuyAndSellStockTest, NoProfit) {
    verifyAllApproaches({7, 6, 4, 3, 1}, 0);
}

TEST_F(BestTimeToBuyAndSellStockTest, SingleElement) {
    verifyAllApproaches({5}, 0);
}

TEST_F(BestTimeToBuyAndSellStockTest, TwoElementsProfit) {
    verifyAllApproaches({1, 5}, 4);
}

TEST_F(BestTimeToBuyAndSellStockTest, TwoElementsNoProfit) {
    verifyAllApproaches({5, 1}, 0);
}

TEST_F(BestTimeToBuyAndSellStockTest, AllSamePrice) {
    verifyAllApproaches({3, 3, 3, 3, 3}, 0);
}

TEST_F(BestTimeToBuyAndSellStockTest, IncreasingPrices) {
    verifyAllApproaches({1, 2, 3, 4, 5}, 4);
}

TEST_F(BestTimeToBuyAndSellStockTest, DecreasingPrices) {
    verifyAllApproaches({5, 4, 3, 2, 1}, 0);
}

TEST_F(BestTimeToBuyAndSellStockTest, MinAtEnd) {
    verifyAllApproaches({3, 5, 4, 2, 1}, 2);
}

TEST_F(BestTimeToBuyAndSellStockTest, MaxAtEnd) {
    verifyAllApproaches({2, 1, 3, 4, 5}, 4);
}

TEST_F(BestTimeToBuyAndSellStockTest, ZigzagPattern) {
    verifyAllApproaches({3, 1, 4, 1, 5}, 4);
}

TEST_F(BestTimeToBuyAndSellStockTest, LargeProfitEarly) {
    verifyAllApproaches({1, 10, 2, 3, 4}, 9);
}

TEST_F(BestTimeToBuyAndSellStockTest, LargeProfitLate) {
    verifyAllApproaches({5, 4, 3, 1, 10}, 9);
}

TEST_F(BestTimeToBuyAndSellStockTest, MultiplePeaks) {
    verifyAllApproaches({1, 5, 2, 8, 3, 9}, 8);
}

TEST_F(BestTimeToBuyAndSellStockTest, SmallProfit) {
    verifyAllApproaches({100, 101, 99, 98}, 1);
}

TEST_F(BestTimeToBuyAndSellStockTest, AlternatingHighLow) {
    verifyAllApproaches({10, 1, 10, 1, 10}, 9);
}

TEST_F(BestTimeToBuyAndSellStockTest, SingleValley) {
    verifyAllApproaches({5, 3, 1, 3, 5}, 4);
}

TEST_F(BestTimeToBuyAndSellStockTest, SinglePeak) {
    verifyAllApproaches({1, 3, 5, 3, 1}, 4);
}

TEST_F(BestTimeToBuyAndSellStockTest, MaxValueFirst) {
    verifyAllApproaches({10, 1, 2, 3, 4}, 3);
}

TEST_F(BestTimeToBuyAndSellStockTest, MinValueLast) {
    verifyAllApproaches({5, 4, 3, 2, 1}, 0);
}

TEST_F(BestTimeToBuyAndSellStockTest, LargeRange) {
    verifyAllApproaches({1, 10000}, 9999);
}

TEST_F(BestTimeToBuyAndSellStockTest, ConsecutiveIncreases) {
    verifyAllApproaches({1, 2, 4, 8, 16}, 15);
}

TEST_F(BestTimeToBuyAndSellStockTest, FlatThenIncrease) {
    verifyAllApproaches({5, 5, 5, 5, 10}, 5);
}

TEST_F(BestTimeToBuyAndSellStockTest, DecreaseThenFlat) {
    verifyAllApproaches({10, 5, 5, 5, 5}, 0);
}

TEST_F(BestTimeToBuyAndSellStockTest, RandomPattern) {
    verifyAllApproaches({3, 7, 2, 9, 1, 5, 8}, 7);
}