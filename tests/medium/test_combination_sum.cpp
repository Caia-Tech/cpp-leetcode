#include <gtest/gtest.h>
#include "medium/combination_sum.h"
#include <algorithm>
#include <set>

using namespace leetcode::medium;

class CombinationSumTest : public ::testing::Test {
protected:
    CombinationSum solution;
    
    // Helper function to normalize and compare results (order-independent)
    void normalizeResult(std::vector<std::vector<int>>& result) {
        for (auto& combination : result) {
            std::sort(combination.begin(), combination.end());
        }
        std::sort(result.begin(), result.end());
    }
    
    bool areResultsEquivalent(std::vector<std::vector<int>> result1, std::vector<std::vector<int>> result2) {
        normalizeResult(result1);
        normalizeResult(result2);
        return result1 == result2;
    }
    
    // Helper function to test all approaches
    void testAllApproaches(std::vector<int> candidates, int target, const std::vector<std::vector<int>>& expected) {
        std::vector<int> candidates1 = candidates, candidates2 = candidates, 
                        candidates3 = candidates, candidates4 = candidates,
                        candidates5 = candidates, candidates6 = candidates;
        
        auto result1 = solution.combinationSumBacktracking(candidates1, target);
        auto result2 = solution.combinationSumDP(candidates2, target);
        auto result3 = solution.combinationSumBFS(candidates3, target);
        auto result4 = solution.combinationSumMemoization(candidates4, target);
        auto result5 = solution.combinationSumIterative(candidates5, target);
        auto result6 = solution.combinationSumMathematical(candidates6, target);
        
        EXPECT_TRUE(areResultsEquivalent(result1, expected)) << "Backtracking approach failed";
        EXPECT_TRUE(areResultsEquivalent(result2, expected)) << "DP approach failed";
        EXPECT_TRUE(areResultsEquivalent(result3, expected)) << "BFS approach failed";
        EXPECT_TRUE(areResultsEquivalent(result4, expected)) << "Memoization approach failed";
        EXPECT_TRUE(areResultsEquivalent(result5, expected)) << "Iterative approach failed";
        EXPECT_TRUE(areResultsEquivalent(result6, expected)) << "Mathematical approach failed";
    }
};

TEST_F(CombinationSumTest, BasicExample1) {
    // Input: candidates = [2,3,6,7], target = 7
    // Output: [[2,2,3],[7]]
    std::vector<int> candidates = {2, 3, 6, 7};
    std::vector<std::vector<int>> expected = {{2, 2, 3}, {7}};
    testAllApproaches(candidates, 7, expected);
}

TEST_F(CombinationSumTest, BasicExample2) {
    // Input: candidates = [2,3,5], target = 8
    // Output: [[2,2,2,2],[2,3,3],[3,5]]
    std::vector<int> candidates = {2, 3, 5};
    std::vector<std::vector<int>> expected = {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}};
    testAllApproaches(candidates, 8, expected);
}

TEST_F(CombinationSumTest, NoSolution) {
    // Input: candidates = [2], target = 1
    // Output: []
    std::vector<int> candidates = {2};
    std::vector<std::vector<int>> expected = {};
    testAllApproaches(candidates, 1, expected);
}

TEST_F(CombinationSumTest, SingleCandidate) {
    // Input: candidates = [1], target = 1
    // Output: [[1]]
    std::vector<int> candidates = {1};
    std::vector<std::vector<int>> expected = {{1}};
    testAllApproaches(candidates, 1, expected);
}

TEST_F(CombinationSumTest, SingleCandidateMultipleUses) {
    // Input: candidates = [2], target = 6
    // Output: [[2,2,2]]
    std::vector<int> candidates = {2};
    std::vector<std::vector<int>> expected = {{2, 2, 2}};
    testAllApproaches(candidates, 6, expected);
}

TEST_F(CombinationSumTest, ExactMatch) {
    // Input: candidates = [5,10,15], target = 15
    // Output: [[5,5,5],[5,10],[15]]
    std::vector<int> candidates = {5, 10, 15};
    std::vector<std::vector<int>> expected = {{5, 5, 5}, {5, 10}, {15}};
    testAllApproaches(candidates, 15, expected);
}

TEST_F(CombinationSumTest, LargerExample) {
    // Input: candidates = [2,3,4,7], target = 10
    std::vector<int> candidates = {2, 3, 4, 7};
    std::vector<std::vector<int>> expected = {
        {2, 2, 2, 2, 2}, {2, 2, 3, 3}, {2, 4, 4}, {3, 3, 4}, {3, 7}
    };
    testAllApproaches(candidates, 10, expected);
}

TEST_F(CombinationSumTest, SmallTarget) {
    // Input: candidates = [3,5,7], target = 1
    // Output: [] (no combination possible)
    std::vector<int> candidates = {3, 5, 7};
    std::vector<std::vector<int>> expected = {};
    testAllApproaches(candidates, 1, expected);
}

TEST_F(CombinationSumTest, TargetEqualsMinCandidate) {
    // Input: candidates = [2,5,8], target = 2
    // Output: [[2]]
    std::vector<int> candidates = {2, 5, 8};
    std::vector<std::vector<int>> expected = {{2}};
    testAllApproaches(candidates, 2, expected);
}

TEST_F(CombinationSumTest, OnlyLargerCandidates) {
    // Input: candidates = [10,20,30], target = 5
    // Output: [] (no combination possible)
    std::vector<int> candidates = {10, 20, 30};
    std::vector<std::vector<int>> expected = {};
    testAllApproaches(candidates, 5, expected);
}

TEST_F(CombinationSumTest, RepeatedSmallCandidate) {
    // Input: candidates = [1,2], target = 4
    // Output: [[1,1,1,1],[1,1,2],[2,2]]
    std::vector<int> candidates = {1, 2};
    std::vector<std::vector<int>> expected = {{1, 1, 1, 1}, {1, 1, 2}, {2, 2}};
    testAllApproaches(candidates, 4, expected);
}

TEST_F(CombinationSumTest, ManyCandidates) {
    // Input: candidates = [2,3,4,5,6], target = 9
    std::vector<int> candidates = {2, 3, 4, 5, 6};
    std::vector<std::vector<int>> expected = {
        {2, 2, 2, 3}, {2, 3, 4}, {3, 3, 3}, {3, 6}, {4, 5}
    };
    testAllApproaches(candidates, 9, expected);
}

TEST_F(CombinationSumTest, PrimeCandidates) {
    // Input: candidates = [2,3,5,7], target = 12
    std::vector<int> candidates = {2, 3, 5, 7};
    std::vector<std::vector<int>> expected = {
        {2, 2, 2, 2, 2, 2}, {2, 2, 2, 3, 3}, {2, 3, 7}, {2, 5, 5}, {3, 3, 3, 3}, {5, 7}
    };
    testAllApproaches(candidates, 12, expected);
}

TEST_F(CombinationSumTest, BoundaryValues) {
    // Test with boundary constraint values
    std::vector<int> candidates = {2, 40};  // Min and max candidate values
    std::vector<std::vector<int>> expected = {{2, 2}, {40}};  // Both should work for target=4 would only give [2,2]
    testAllApproaches(candidates, 4, {{2, 2}});
    testAllApproaches(candidates, 40, {{40}});
}

TEST_F(CombinationSumTest, MaxTarget) {
    // Test with maximum target value constraint
    std::vector<int> candidates = {20, 40};
    std::vector<std::vector<int>> expected = {{20, 20}};
    testAllApproaches(candidates, 40, {{20, 20}, {40}});
}

TEST_F(CombinationSumTest, DuplicateValuesInResult) {
    // Test case where multiple candidates can create same sum
    std::vector<int> candidates = {3, 4, 5};
    std::vector<std::vector<int>> expected = {{3, 4}};
    testAllApproaches(candidates, 7, expected);
}

TEST_F(CombinationSumTest, OnlySingleElementSolutions) {
    // Input: candidates = [7,14,21], target = 7
    // Output: [[7]]
    std::vector<int> candidates = {7, 14, 21};
    std::vector<std::vector<int>> expected = {{7}};
    testAllApproaches(candidates, 7, expected);
}

TEST_F(CombinationSumTest, MultipleRepeats) {
    // Input: candidates = [3], target = 9
    // Output: [[3,3,3]]
    std::vector<int> candidates = {3};
    std::vector<std::vector<int>> expected = {{3, 3, 3}};
    testAllApproaches(candidates, 9, expected);
}

TEST_F(CombinationSumTest, NoDivisibleSolution) {
    // Input: candidates = [4,6], target = 5
    // Output: [] (no way to make 5 from 4s and 6s)
    std::vector<int> candidates = {4, 6};
    std::vector<std::vector<int>> expected = {};
    testAllApproaches(candidates, 5, expected);
}

TEST_F(CombinationSumTest, LargeNumberOfSolutions) {
    // Input that generates many solutions
    std::vector<int> candidates = {1, 2, 3};
    // For target = 6, should have many combinations
    auto result = solution.combinationSumBacktracking(candidates, 6);
    
    // Verify some expected combinations exist
    std::set<std::vector<int>> resultSet;
    for (auto& combination : result) {
        std::sort(combination.begin(), combination.end());
        resultSet.insert(combination);
    }
    
    EXPECT_TRUE(resultSet.count({1, 1, 1, 1, 1, 1}));
    EXPECT_TRUE(resultSet.count({1, 1, 1, 1, 2}));
    EXPECT_TRUE(resultSet.count({1, 1, 2, 2}));
    EXPECT_TRUE(resultSet.count({1, 2, 3}));
    EXPECT_TRUE(resultSet.count({2, 2, 2}));
    EXPECT_TRUE(resultSet.count({3, 3}));
    
    EXPECT_EQ(resultSet.size(), 7); // Should be exactly 7 unique combinations
}

// Performance test
TEST_F(CombinationSumTest, PerformanceTest) {
    // Test with moderate complexity to ensure algorithms complete in reasonable time
    std::vector<int> candidates = {2, 3, 5, 7};
    int target = 20;
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = solution.combinationSumBacktracking(candidates, target);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    EXPECT_LT(duration.count(), 100) << "Algorithm should complete within 100ms for moderate input";
    
    // Verify we got some results
    EXPECT_GT(result.size(), 0);
}

// Test result uniqueness
TEST_F(CombinationSumTest, ResultUniqueness) {
    std::vector<int> candidates = {2, 3, 5};
    auto result = solution.combinationSumBacktracking(candidates, 8);
    
    // Convert to set to check for duplicates
    std::set<std::vector<int>> uniqueResults;
    for (auto& combination : result) {
        std::sort(combination.begin(), combination.end());
        uniqueResults.insert(combination);
    }
    
    EXPECT_EQ(result.size(), uniqueResults.size()) << "Result should not contain duplicate combinations";
}

// Test sum correctness
TEST_F(CombinationSumTest, SumCorrectness) {
    std::vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    auto result = solution.combinationSumBacktracking(candidates, target);
    
    // Verify each combination sums to target
    for (const auto& combination : result) {
        int sum = 0;
        for (int num : combination) {
            sum += num;
        }
        EXPECT_EQ(sum, target) << "Each combination should sum to target";
    }
}

// Test candidate value constraints
TEST_F(CombinationSumTest, CandidateConstraints) {
    std::vector<int> candidates = {2, 3, 6, 7};
    auto result = solution.combinationSumBacktracking(candidates, 7);
    
    // Verify each number in combinations exists in candidates
    std::set<int> candidateSet(candidates.begin(), candidates.end());
    
    for (const auto& combination : result) {
        for (int num : combination) {
            EXPECT_TRUE(candidateSet.count(num)) << "Each number in combination should be from candidates array";
        }
    }
}