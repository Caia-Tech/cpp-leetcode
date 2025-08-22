#include <gtest/gtest.h>
#include "medium/merge_intervals.h"
#include <chrono>
#include <algorithm>

using namespace leetcode::medium;

class MergeIntervalsTest : public ::testing::Test {
protected:
    MergeIntervals solution;
    
    // Helper function to normalize results for comparison (sort by start time)
    void normalizeResult(std::vector<std::vector<int>>& result) {
        std::sort(result.begin(), result.end());
    }
    
    bool areResultsEquivalent(std::vector<std::vector<int>> result1, std::vector<std::vector<int>> result2) {
        normalizeResult(result1);
        normalizeResult(result2);
        return result1 == result2;
    }
    
    // Helper function to test main approaches (excluding complex ones for performance)
    void testMainApproaches(std::vector<std::vector<int>> intervals, const std::vector<std::vector<int>>& expected) {
        std::vector<std::vector<int>> intervals1 = intervals, intervals2 = intervals, 
                                     intervals3 = intervals, intervals4 = intervals;
        
        auto result1 = solution.mergeIntervals(intervals1);
        auto result2 = solution.mergeIntervalsStack(intervals2);
        auto result3 = solution.mergeIntervalsSweepLine(intervals3);
        auto result4 = solution.mergeIntervalsUnionFind(intervals4);
        
        EXPECT_TRUE(areResultsEquivalent(result1, expected)) << "Standard merge failed";
        EXPECT_TRUE(areResultsEquivalent(result2, expected)) << "Stack merge failed";
        EXPECT_TRUE(areResultsEquivalent(result3, expected)) << "Sweep line merge failed";
        EXPECT_TRUE(areResultsEquivalent(result4, expected)) << "Union-Find merge failed";
    }
    
    // Test all approaches including the more complex ones
    void testAllApproaches(std::vector<std::vector<int>> intervals, const std::vector<std::vector<int>>& expected) {
        testMainApproaches(intervals, expected);
        
        std::vector<std::vector<int>> intervals5 = intervals, intervals6 = intervals;
        
        auto result5 = solution.mergeIntervalsByEndTime(intervals5);
        auto result6 = solution.mergeIntervalsIntervalTree(intervals6);
        
        EXPECT_TRUE(areResultsEquivalent(result5, expected)) << "End time sort merge failed";
        EXPECT_TRUE(areResultsEquivalent(result6, expected)) << "Interval tree merge failed";
    }
};

TEST_F(MergeIntervalsTest, BasicExample1) {
    // Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
    // Output: [[1,6],[8,10],[15,18]]
    // Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6]
    std::vector<std::vector<int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};
    std::vector<std::vector<int>> expected = {{1,6}, {8,10}, {15,18}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, BasicExample2) {
    // Input: intervals = [[1,4],[4,5]]
    // Output: [[1,5]]
    // Explanation: Intervals [1,4] and [4,5] are considered overlapping
    std::vector<std::vector<int>> intervals = {{1,4}, {4,5}};
    std::vector<std::vector<int>> expected = {{1,5}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, SingleInterval) {
    // Input: intervals = [[1,4]]
    // Output: [[1,4]]
    std::vector<std::vector<int>> intervals = {{1,4}};
    std::vector<std::vector<int>> expected = {{1,4}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, NoOverlaps) {
    // Input: intervals = [[1,2],[3,4],[5,6]]
    // Output: [[1,2],[3,4],[5,6]]
    std::vector<std::vector<int>> intervals = {{1,2}, {3,4}, {5,6}};
    std::vector<std::vector<int>> expected = {{1,2}, {3,4}, {5,6}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, AllOverlap) {
    // Input: intervals = [[1,3],[2,4],[3,5],[4,6]]
    // Output: [[1,6]]
    std::vector<std::vector<int>> intervals = {{1,3}, {2,4}, {3,5}, {4,6}};
    std::vector<std::vector<int>> expected = {{1,6}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, TouchingIntervals) {
    // Input: intervals = [[1,2],[2,3],[3,4]]
    // Output: [[1,4]]
    std::vector<std::vector<int>> intervals = {{1,2}, {2,3}, {3,4}};
    std::vector<std::vector<int>> expected = {{1,4}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, ContainedIntervals) {
    // Input: intervals = [[1,10],[2,3],[4,5],[6,7],[8,9]]
    // Output: [[1,10]]
    // Explanation: All smaller intervals are contained within [1,10]
    std::vector<std::vector<int>> intervals = {{1,10}, {2,3}, {4,5}, {6,7}, {8,9}};
    std::vector<std::vector<int>> expected = {{1,10}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, UnsortedInput) {
    // Input: intervals = [[2,6],[1,3],[15,18],[8,10]]
    // Output: [[1,6],[8,10],[15,18]]
    // Same as BasicExample1 but unsorted input
    std::vector<std::vector<int>> intervals = {{2,6}, {1,3}, {15,18}, {8,10}};
    std::vector<std::vector<int>> expected = {{1,6}, {8,10}, {15,18}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, IdenticalIntervals) {
    // Input: intervals = [[1,3],[1,3],[1,3]]
    // Output: [[1,3]]
    std::vector<std::vector<int>> intervals = {{1,3}, {1,3}, {1,3}};
    std::vector<std::vector<int>> expected = {{1,3}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, PartialOverlaps) {
    // Input: intervals = [[1,4],[2,5],[6,8],[7,9]]
    // Output: [[1,5],[6,9]]
    std::vector<std::vector<int>> intervals = {{1,4}, {2,5}, {6,8}, {7,9}};
    std::vector<std::vector<int>> expected = {{1,5}, {6,9}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, PointIntervals) {
    // Input: intervals = [[1,1],[2,2],[3,3]]
    // Output: [[1,1],[2,2],[3,3]]
    std::vector<std::vector<int>> intervals = {{1,1}, {2,2}, {3,3}};
    std::vector<std::vector<int>> expected = {{1,1}, {2,2}, {3,3}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, TouchingPointIntervals) {
    // Input: intervals = [[1,1],[1,1],[2,2]]
    // Output: [[1,1],[2,2]]
    std::vector<std::vector<int>> intervals = {{1,1}, {1,1}, {2,2}};
    std::vector<std::vector<int>> expected = {{1,1}, {2,2}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, WideRange) {
    // Input: intervals = [[0,10000],[1,2],[3,4]]
    // Output: [[0,10000]]
    std::vector<std::vector<int>> intervals = {{0,10000}, {1,2}, {3,4}};
    std::vector<std::vector<int>> expected = {{0,10000}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, ChainedOverlaps) {
    // Input: intervals = [[1,3],[2,4],[5,7],[6,8],[9,10]]
    // Output: [[1,4],[5,8],[9,10]]
    std::vector<std::vector<int>> intervals = {{1,3}, {2,4}, {5,7}, {6,8}, {9,10}};
    std::vector<std::vector<int>> expected = {{1,4}, {5,8}, {9,10}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, BoundaryValues) {
    // Test with constraint boundaries
    std::vector<std::vector<int>> intervals = {{0,0}, {1,10000}, {5000,10000}};
    std::vector<std::vector<int>> expected = {{0,0}, {1,10000}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, ManySmallIntervals) {
    // Input: many small overlapping intervals
    std::vector<std::vector<int>> intervals = {
        {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4}
    };
    std::vector<std::vector<int>> expected = {{1,4}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, AlternatingPattern) {
    // Input: intervals = [[1,2],[3,4],[5,6],[7,8]]
    // Output: [[1,2],[3,4],[5,6],[7,8]] (no overlaps)
    std::vector<std::vector<int>> intervals = {{1,2}, {3,4}, {5,6}, {7,8}};
    std::vector<std::vector<int>> expected = {{1,2}, {3,4}, {5,6}, {7,8}};
    testAllApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, ReverseOrder) {
    // Input: intervals in reverse chronological order
    std::vector<std::vector<int>> intervals = {{15,18}, {8,10}, {2,6}, {1,3}};
    std::vector<std::vector<int>> expected = {{1,6}, {8,10}, {15,18}};
    testAllApproaches(intervals, expected);
}

// Performance tests
TEST_F(MergeIntervalsTest, PerformanceComparison) {
    // Create test data with many intervals
    std::vector<std::vector<int>> intervals;
    for (int i = 0; i < 1000; i += 2) {
        intervals.push_back({i, i + 1});
    }
    
    // Test standard approach
    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = solution.mergeIntervals(intervals);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test sweep line approach
    intervals = std::vector<std::vector<int>>();
    for (int i = 0; i < 1000; i += 2) {
        intervals.push_back({i, i + 1});
    }
    
    start = std::chrono::high_resolution_clock::now();
    auto result2 = solution.mergeIntervalsSweepLine(intervals);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Results should be equivalent
    EXPECT_TRUE(areResultsEquivalent(result1, result2));
    
    // Both should complete quickly
    EXPECT_LT(duration1.count(), 10000) << "Standard approach should be fast";
    EXPECT_LT(duration2.count(), 20000) << "Sweep line should be reasonable";
}

TEST_F(MergeIntervalsTest, LargeOverlappingSet) {
    // Test with large number of overlapping intervals
    std::vector<std::vector<int>> intervals;
    for (int i = 0; i < 100; ++i) {
        intervals.push_back({0, i + 1});
    }
    
    auto result = solution.mergeIntervals(intervals);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], std::vector<int>({0, 100}));
}

// Algorithm-specific tests
TEST_F(MergeIntervalsTest, StackSpecificTest) {
    // Test that specifically exercises stack operations
    std::vector<std::vector<int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};
    auto result = solution.mergeIntervalsStack(intervals);
    
    std::vector<std::vector<int>> expected = {{1,6}, {8,10}, {15,18}};
    EXPECT_TRUE(areResultsEquivalent(result, expected));
}

TEST_F(MergeIntervalsTest, SweepLineSpecificTest) {
    // Test sweep line with complex overlapping pattern
    std::vector<std::vector<int>> intervals = {{1,4}, {2,3}, {5,7}, {6,8}};
    auto result = solution.mergeIntervalsSweepLine(intervals);
    
    std::vector<std::vector<int>> expected = {{1,4}, {5,8}};
    EXPECT_TRUE(areResultsEquivalent(result, expected));
}

TEST_F(MergeIntervalsTest, UnionFindSpecificTest) {
    // Test Union-Find with multiple connected components
    std::vector<std::vector<int>> intervals = {{1,3}, {2,4}, {6,8}, {7,9}, {11,12}};
    auto result = solution.mergeIntervalsUnionFind(intervals);
    
    std::vector<std::vector<int>> expected = {{1,4}, {6,9}, {11,12}};
    EXPECT_TRUE(areResultsEquivalent(result, expected));
}

TEST_F(MergeIntervalsTest, EndTimeSort) {
    // Test end time sorting approach
    std::vector<std::vector<int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};
    auto result = solution.mergeIntervalsByEndTime(intervals);
    
    std::vector<std::vector<int>> expected = {{1,6}, {8,10}, {15,18}};
    EXPECT_TRUE(areResultsEquivalent(result, expected));
}

// Edge cases
TEST_F(MergeIntervalsTest, EdgeCases) {
    // Two intervals touching at one point
    testAllApproaches({{1,2}, {2,3}}, {{1,3}});
    
    // Intervals with same start time
    testAllApproaches({{1,3}, {1,5}, {1,2}}, {{1,5}});
    
    // Intervals with same end time
    testAllApproaches({{1,5}, {2,5}, {3,5}}, {{1,5}});
    
    // Single point intervals that touch
    testMainApproaches({{1,1}, {2,2}}, {{1,1}, {2,2}});
}

TEST_F(MergeIntervalsTest, ComplexOverlapPattern) {
    // Complex overlapping pattern that tests various merge scenarios
    std::vector<std::vector<int>> intervals = {
        {1,5}, {2,3}, {4,6}, {7,9}, {8,10}, {12,16}, {13,14}, {15,17}
    };
    std::vector<std::vector<int>> expected = {{1,6}, {7,10}, {12,17}};
    testMainApproaches(intervals, expected);
}

TEST_F(MergeIntervalsTest, WorstCaseScenario) {
    // All intervals overlap - should merge into one
    std::vector<std::vector<int>> intervals;
    for (int i = 0; i < 10; ++i) {
        intervals.push_back({i, i + 5});
    }
    
    auto result = solution.mergeIntervals(intervals);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[0][1], 14);
}

TEST_F(MergeIntervalsTest, ConsistencyAcrossApproaches) {
    // Test various patterns to ensure all approaches agree
    std::vector<std::vector<std::vector<int>>> testCases = {
        {{1,3}, {2,6}, {8,10}, {15,18}},
        {{1,4}, {4,5}},
        {{1,2}, {3,4}, {5,6}},
        {{1,10}, {2,3}, {4,5}},
        {{1,3}, {1,3}, {1,3}},
        {{0,0}, {1,1}, {2,2}}
    };
    
    for (const auto& intervals : testCases) {
        // Get expected result from standard approach
        std::vector<std::vector<int>> testIntervals = intervals;
        auto expected = solution.mergeIntervals(testIntervals);
        
        // Test main approaches
        testMainApproaches(intervals, expected);
    }
}

TEST_F(MergeIntervalsTest, RealWorldScenario) {
    // Meeting room scheduling scenario
    std::vector<std::vector<int>> meetings = {
        {9,10},   // 9-10 AM
        {10,11},  // 10-11 AM (back-to-back)
        {11,12},  // 11-12 PM (back-to-back)
        {14,15},  // 2-3 PM
        {15,16},  // 3-4 PM (back-to-back)
        {16,17}   // 4-5 PM (back-to-back)
    };
    
    std::vector<std::vector<int>> expected = {{9,12}, {14,17}};
    testMainApproaches(meetings, expected);
}