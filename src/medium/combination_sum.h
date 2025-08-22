#pragma once

#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 39: Combination Sum
 * 
 * Given an array of distinct integers candidates and a target integer target, 
 * return a list of all unique combinations of candidates where the chosen numbers sum to target. 
 * You may choose the same number from candidates an unlimited number of times.
 * 
 * The test cases are generated such that the number of unique combinations that sum up to target 
 * is less than 150 for the given input.
 * 
 * Constraints:
 * - 1 <= candidates.length <= 30
 * - 2 <= candidates[i] <= 40
 * - All elements of candidates are distinct.
 * - 1 <= target <= 40
 */
class CombinationSum {
public:
    /**
     * Approach 1: Backtracking (Optimal)
     * 
     * Use recursive backtracking to explore all possible combinations.
     * 
     * Reasoning: This is the classic backtracking approach for combination problems.
     * For each candidate, we have two choices: include it (and possibly include it
     * again later) or exclude it. Use recursion to explore all paths, backtracking
     * when target becomes negative or we find a valid combination. Sort candidates
     * first for early termination optimization when current candidate > remaining target.
     * 
     * Time Complexity: O(N^(T/M)) where N=candidates length, T=target, M=minimal candidate
     * Space Complexity: O(T/M) - recursion depth + result storage
     * 
     * Best when: Classic backtracking understanding, optimal for most cases
     * Worst when: Target is very large relative to minimum candidate value
     */
    std::vector<std::vector<int>> combinationSumBacktracking(std::vector<int>& candidates, int target);

    /**
     * Approach 2: Dynamic Programming
     * 
     * Build combinations incrementally using DP table for each target value.
     * 
     * Reasoning: Use DP where dp[i] contains all combinations that sum to i.
     * For each target value from 1 to target, and for each candidate, if candidate <= i,
     * add candidate to all combinations in dp[i-candidate] to form new combinations for dp[i].
     * This bottom-up approach ensures we explore all possible combinations systematically.
     * 
     * Time Complexity: O(N * T^2) - for each target value, check all candidates and combinations
     * Space Complexity: O(T * number_of_combinations) - DP table storage
     * 
     * Best when: Want iterative DP approach, need all combinations for intermediate targets
     * Worst when: Large target values create memory issues, backtracking is more efficient
     */
    std::vector<std::vector<int>> combinationSumDP(std::vector<int>& candidates, int target);

    /**
     * Approach 3: BFS with Queue
     * 
     * Use BFS to explore combinations level by level.
     * 
     * Reasoning: Treat each partial combination as a state and use BFS to explore.
     * Start with empty combination, then for each state, try adding each candidate
     * (if it doesn't exceed target) to create new states. Continue until all states
     * either reach target or exceed it. This explores combinations in breadth-first order.
     * 
     * Time Complexity: O(N^(T/M)) - similar to backtracking but with queue overhead
     * Space Complexity: O(N^(T/M)) - queue can hold many partial combinations
     * 
     * Best when: Want BFS exploration pattern, iterative approach preferred
     * Worst when: Memory usage for queue becomes prohibitive
     */
    std::vector<std::vector<int>> combinationSumBFS(std::vector<int>& candidates, int target);

    /**
     * Approach 4: Memoization with Recursive Approach
     * 
     * Use memoization to cache results for repeated subproblems.
     * 
     * Reasoning: Enhanced recursive approach that memoizes results for each
     * (remaining_target, start_index) pair to avoid recomputing same subproblems.
     * This is especially effective when there are many overlapping subproblems,
     * though the combination nature of this problem has fewer overlaps than typical DP problems.
     * 
     * Time Complexity: O(N * T * number_of_combinations) - memoization reduces repeated work
     * Space Complexity: O(N * T) - memoization table + recursion stack
     * 
     * Best when: Many overlapping subproblems exist, want recursive approach with optimization
     * Worst when: Limited overlapping subproblems make memoization overhead not worth it
     */
    std::vector<std::vector<int>> combinationSumMemoization(std::vector<int>& candidates, int target);

    /**
     * Approach 5: Iterative with Stack (DFS Simulation)
     * 
     * Use explicit stack to simulate recursive DFS without recursion.
     * 
     * Reasoning: Convert recursive backtracking to iterative using explicit stack.
     * Each stack entry contains current combination, remaining target, and next
     * candidate index to try. This avoids recursion stack limits while maintaining
     * the same DFS exploration order as backtracking approach.
     * 
     * Time Complexity: O(N^(T/M)) - same as backtracking but iterative
     * Space Complexity: O(N^(T/M)) - explicit stack storage + result storage
     * 
     * Best when: Want to avoid recursion limits, iterative DFS preferred
     * Worst when: Recursive approach is cleaner and stack limits aren't an issue
     */
    std::vector<std::vector<int>> combinationSumIterative(std::vector<int>& candidates, int target);

    /**
     * Approach 6: Mathematical Enumeration
     * 
     * Systematically enumerate all possible combinations using mathematical patterns.
     * 
     * Reasoning: For each candidate, calculate maximum times it can be used (target/candidate).
     * Use nested loops to enumerate all combinations of usage counts for each candidate.
     * This approach makes the enumeration very systematic and explicit, though it
     * may explore more combinations than necessary compared to backtracking with pruning.
     * 
     * Time Complexity: O((T/candidates[0]) * (T/candidates[1]) * ... ) - product of max usage counts
     * Space Complexity: O(max_combination_size) - temporary combination storage
     * 
     * Best when: Want systematic mathematical enumeration, understand combination structure
     * Worst when: Candidates have large maximum usage counts, leading to many invalid combinations
     */
    std::vector<std::vector<int>> combinationSumMathematical(std::vector<int>& candidates, int target);

private:
    // Helper functions
    void backtrackHelper(std::vector<int>& candidates, int target, int start, 
                        std::vector<int>& current, std::vector<std::vector<int>>& result);
    
    std::vector<std::vector<int>> memoHelper(std::vector<int>& candidates, int target, int start,
                                           std::vector<std::vector<std::vector<std::vector<int>>>>& memo);
    
    // State for iterative DFS
    struct DFSState {
        std::vector<int> combination;
        int remainingTarget;
        int startIndex;
        
        DFSState(const std::vector<int>& comb, int target, int start) 
            : combination(comb), remainingTarget(target), startIndex(start) {}
    };
    
    // State for BFS
    struct BFSState {
        std::vector<int> combination;
        int remainingTarget;
        int lastUsedIndex;
        
        BFSState(const std::vector<int>& comb, int target, int lastIndex) 
            : combination(comb), remainingTarget(target), lastUsedIndex(lastIndex) {}
    };
};

}
}