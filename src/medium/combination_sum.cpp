#include "combination_sum.h"
#include <queue>
#include <stack>
#include <functional>

namespace leetcode {
namespace medium {

std::vector<std::vector<int>> CombinationSum::combinationSumBacktracking(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    
    // Sort for early termination optimization
    std::sort(candidates.begin(), candidates.end());
    
    backtrackHelper(candidates, target, 0, current, result);
    return result;
}

void CombinationSum::backtrackHelper(std::vector<int>& candidates, int target, int start, 
                                    std::vector<int>& current, std::vector<std::vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    
    for (int i = start; i < candidates.size(); ++i) {
        // Early termination: if current candidate > target, all subsequent candidates will also be > target
        if (candidates[i] > target) break;
        
        current.push_back(candidates[i]);
        // Allow reusing the same candidate by passing 'i' instead of 'i+1'
        backtrackHelper(candidates, target - candidates[i], i, current, result);
        current.pop_back(); // Backtrack
    }
}

std::vector<std::vector<int>> CombinationSum::combinationSumDP(std::vector<int>& candidates, int target) {
    // dp[i] contains all combinations that sum to i
    std::vector<std::vector<std::vector<int>>> dp(target + 1);
    dp[0] = {{}};  // Empty combination sums to 0
    
    for (int i = 1; i <= target; ++i) {
        for (int candidate : candidates) {
            if (candidate <= i && !dp[i - candidate].empty()) {
                for (const auto& combination : dp[i - candidate]) {
                    std::vector<int> newCombination = combination;
                    newCombination.push_back(candidate);
                    // Sort to ensure consistent order and avoid duplicates
                    std::sort(newCombination.begin(), newCombination.end());
                    dp[i].push_back(newCombination);
                }
            }
        }
        
        // Remove duplicates from dp[i]
        std::sort(dp[i].begin(), dp[i].end());
        dp[i].erase(std::unique(dp[i].begin(), dp[i].end()), dp[i].end());
    }
    
    return dp[target];
}

std::vector<std::vector<int>> CombinationSum::combinationSumBFS(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::queue<BFSState> queue;
    
    // Start with empty combination
    queue.push(BFSState({}, target, -1));
    
    while (!queue.empty()) {
        BFSState current = queue.front();
        queue.pop();
        
        if (current.remainingTarget == 0) {
            result.push_back(current.combination);
            continue;
        }
        
        // Try each candidate starting from lastUsedIndex to avoid duplicates
        for (int i = current.lastUsedIndex + 1; i < candidates.size(); ++i) {
            if (candidates[i] <= current.remainingTarget) {
                std::vector<int> newCombination = current.combination;
                newCombination.push_back(candidates[i]);
                queue.push(BFSState(newCombination, current.remainingTarget - candidates[i], i - 1));
            }
        }
    }
    
    return result;
}

std::vector<std::vector<int>> CombinationSum::combinationSumMemoization(std::vector<int>& candidates, int target) {
    // memo[target][start] = all combinations for remaining target starting from index start
    std::vector<std::vector<std::vector<std::vector<int>>>> memo(
        target + 1, std::vector<std::vector<std::vector<int>>>(candidates.size() + 1));
    
    std::sort(candidates.begin(), candidates.end());
    return memoHelper(candidates, target, 0, memo);
}

std::vector<std::vector<int>> CombinationSum::memoHelper(std::vector<int>& candidates, int target, int start,
                                                       std::vector<std::vector<std::vector<std::vector<int>>>>& memo) {
    if (target == 0) {
        return {{}};
    }
    
    if (start >= candidates.size() || target < 0) {
        return {};
    }
    
    if (!memo[target][start].empty() || (target >= 0 && start < memo[target].size())) {
        // Check if already computed (empty vector means computed but no solutions)
        static std::vector<std::vector<int>> computed_empty;
        if (memo[target][start].empty() && target > 0) {
            // Not computed yet, compute now
        } else {
            return memo[target][start];
        }
    }
    
    std::vector<std::vector<int>> result;
    
    // Option 1: Don't use current candidate
    auto without = memoHelper(candidates, target, start + 1, memo);
    result.insert(result.end(), without.begin(), without.end());
    
    // Option 2: Use current candidate (can use it again)
    if (candidates[start] <= target) {
        auto with = memoHelper(candidates, target - candidates[start], start, memo);
        for (auto& combination : with) {
            combination.push_back(candidates[start]);
            result.push_back(combination);
        }
    }
    
    memo[target][start] = result;
    return result;
}

std::vector<std::vector<int>> CombinationSum::combinationSumIterative(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::stack<DFSState> stack;
    
    std::sort(candidates.begin(), candidates.end());
    
    // Start with empty combination
    stack.push(DFSState({}, target, 0));
    
    while (!stack.empty()) {
        DFSState current = stack.top();
        stack.pop();
        
        if (current.remainingTarget == 0) {
            result.push_back(current.combination);
            continue;
        }
        
        // Try candidates starting from startIndex
        for (int i = current.startIndex; i < candidates.size(); ++i) {
            if (candidates[i] > current.remainingTarget) break; // Early termination
            
            std::vector<int> newCombination = current.combination;
            newCombination.push_back(candidates[i]);
            
            // Push new state (can reuse same candidate, so startIndex remains i)
            stack.push(DFSState(newCombination, current.remainingTarget - candidates[i], i));
        }
    }
    
    return result;
}

std::vector<std::vector<int>> CombinationSum::combinationSumMathematical(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> maxUsage(candidates.size());
    
    // Calculate maximum times each candidate can be used
    for (int i = 0; i < candidates.size(); ++i) {
        maxUsage[i] = target / candidates[i];
    }
    
    // Generate all combinations using nested loops approach
    std::function<void(int, std::vector<int>&, int)> generate = 
        [&](int candidateIndex, std::vector<int>& currentCombination, int currentSum) {
        if (candidateIndex == candidates.size()) {
            if (currentSum == target) {
                result.push_back(currentCombination);
            }
            return;
        }
        
        // Try using current candidate 0 to maxUsage[candidateIndex] times
        for (int usage = 0; usage <= maxUsage[candidateIndex] && currentSum + usage * candidates[candidateIndex] <= target; ++usage) {
            // Add 'usage' copies of current candidate
            for (int j = 0; j < usage; ++j) {
                currentCombination.push_back(candidates[candidateIndex]);
            }
            
            generate(candidateIndex + 1, currentCombination, currentSum + usage * candidates[candidateIndex]);
            
            // Remove added candidates (backtrack)
            for (int j = 0; j < usage; ++j) {
                currentCombination.pop_back();
            }
        }
    };
    
    std::vector<int> currentCombination;
    generate(0, currentCombination, 0);
    
    return result;
}

}
}