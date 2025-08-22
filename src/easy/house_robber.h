#pragma once

#include <vector>
#include <algorithm>
#include <unordered_map>

namespace leetcode {
namespace easy {

/**
 * Problem 198: House Robber
 * 
 * You are a professional robber planning to rob houses along a street. Each house has a 
 * certain amount of money stashed, the only constraint stopping you from robbing each of 
 * them is that adjacent houses have security systems connected and it will automatically 
 * contact the police if two adjacent houses were broken into on the same night.
 * 
 * Given an integer array nums representing the amount of money of each house, return the 
 * maximum amount of money you can rob tonight without alerting the police.
 * 
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 0 <= nums[i] <= 400
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class HouseRobber {
public:
    /**
     * Approach 1: Dynamic Programming with Array (Classic)
     * 
     * Build DP array where dp[i] represents max money robbing houses 0 to i.
     * 
     * Reasoning: This is the fundamental DP solution. For each house i, we have two choices:
     * rob it (take nums[i] + dp[i-2]) or skip it (take dp[i-1]). The recurrence relation
     * dp[i] = max(dp[i-1], nums[i] + dp[i-2]) captures this decision. Base cases: dp[0] = nums[0]
     * (only one house), dp[1] = max(nums[0], nums[1]) (choose better of two houses).
     * This approach systematically builds up the optimal solution by considering all houses
     * in sequence, ensuring we find the global maximum.
     * 
     * Time Complexity: O(n) - single pass through houses
     * Space Complexity: O(n) - DP array storage
     * 
     * Best when: Learning DP, need to trace back solution, moderate input size
     * Worst when: Space optimization needed, very simple cases, constant space preferred
     */
    int rob(std::vector<int>& nums);

    /**
     * Approach 2: Space-Optimized DP (Two Variables)
     * 
     * Use only two variables to track previous two states instead of full array.
     * 
     * Reasoning: Since dp[i] only depends on dp[i-1] and dp[i-2], we don't need the entire
     * array. Use two variables: 'prev1' for dp[i-1] and 'prev2' for dp[i-2]. At each step,
     * calculate current = max(prev1, nums[i] + prev2), then update prev2 = prev1 and
     * prev1 = current. This maintains the same logic as array DP but reduces space to O(1).
     * This optimization is crucial for large inputs and demonstrates how DP space can often
     * be compressed when only recent states matter.
     * 
     * Time Complexity: O(n) - single pass through houses
     * Space Complexity: O(1) - only two variables needed
     * 
     * Best when: Standard solution needed, space efficiency matters, production code
     * Worst when: Need to reconstruct which houses were robbed, debugging DP logic
     */
    int robOptimized(std::vector<int>& nums);

    /**
     * Approach 3: Recursive with Memoization (Top-Down DP)
     * 
     * Recursively decide rob/skip for each house, caching subproblem results.
     * 
     * Reasoning: Start from the last house and work backwards. For house i, recursively
     * compute max money from robbing houses i to n-1. Choice: rob house i and recurse
     * on i+2, or skip house i and recurse on i+1. Memoization prevents recomputing
     * identical subproblems. This top-down approach is more intuitive for some - it
     * directly models the decision process and only computes needed subproblems.
     * Natural for problems where not all subproblems are needed.
     * 
     * Time Complexity: O(n) - each subproblem solved once
     * Space Complexity: O(n) - recursion stack + memoization map
     * 
     * Best when: Recursive thinking natural, sparse subproblems, early termination possible
     * Worst when: Stack overflow risk, iterative preferred, all subproblems needed anyway
     */
    int robRecursive(std::vector<int>& nums);

    /**
     * Approach 4: Even-Odd Analysis
     * 
     * Consider robbing even-indexed vs odd-indexed houses as starting points.
     * 
     * Reasoning: While we can't rob adjacent houses, we can think about the problem
     * differently: what if we consider two scenarios - starting from house 0 or house 1?
     * This doesn't mean only robbing even/odd houses, but using them as anchors for
     * our decision process. For each starting point, apply the DP logic. This approach
     * provides an alternative perspective and can be extended to circular house arrangements.
     * It demonstrates how reframing the problem can lead to different algorithmic insights.
     * 
     * Time Complexity: O(n) - two passes through houses
     * Space Complexity: O(1) - constant extra space
     * 
     * Best when: Alternative perspective helpful, teaching different approaches, circular variants
     * Worst when: Standard DP clearer, unnecessary complexity, single optimal approach needed
     */
    int robEvenOdd(std::vector<int>& nums);

    /**
     * Approach 5: State Machine
     * 
     * Model as state machine with two states: just robbed vs not just robbed.
     * 
     * Reasoning: Define two states at each position: 'robbed' (just robbed current house)
     * and 'notRobbed' (didn't rob current house). Transitions: robbed[i] = nums[i] + notRobbed[i-1]
     * (can only rob if previous wasn't robbed), notRobbed[i] = max(robbed[i-1], notRobbed[i-1])
     * (can come from either previous state). This explicitly models the constraint as state
     * transitions, making the logic very clear. Useful for more complex variants with
     * multiple constraints.
     * 
     * Time Complexity: O(n) - single pass with state updates
     * Space Complexity: O(1) - only track current states
     * 
     * Best when: Complex constraints, state-based thinking natural, extensible to variants
     * Worst when: Simple problem, standard DP sufficient, overhead unnecessary
     */
    int robStateMachine(std::vector<int>& nums);

    /**
     * Approach 6: Mathematical Pattern Recognition
     * 
     * Recognize this as a Fibonacci-like sequence with custom addition rule.
     * 
     * Reasoning: The recurrence relation dp[i] = max(dp[i-1], nums[i] + dp[i-2]) is similar
     * to Fibonacci but with max instead of sum and external values added. We can analyze
     * patterns: if all houses have same value, it becomes a pure alternating pattern.
     * For increasing values, there's often a point where we switch strategies. This approach
     * uses mathematical insights to potentially early-terminate or optimize specific cases.
     * While not always faster, it demonstrates how recognizing mathematical patterns can
     * provide algorithmic insights.
     * 
     * Time Complexity: O(n) - pattern analysis may allow early termination
     * Space Complexity: O(1) - constant space for pattern tracking
     * 
     * Best when: Uniform or patterned input, mathematical insight available, optimization needed
     * Worst when: Random input values, standard DP sufficient, premature optimization
     */
    int robMathPattern(std::vector<int>& nums);

private:
    // Helper for recursive approach
    int robRecursiveHelper(std::vector<int>& nums, int index, 
                          std::unordered_map<int, int>& memo);
    
    // Helper for pattern detection
    bool hasUniformValues(const std::vector<int>& nums);
    bool isStrictlyIncreasing(const std::vector<int>& nums);
    int calculateAlternatingSum(const std::vector<int>& nums, int start);
};

}
}