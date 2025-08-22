#include "house_robber.h"
#include <algorithm>

namespace leetcode {
namespace easy {

int HouseRobber::rob(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    // dp[i] represents max money robbing houses 0 to i
    std::vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);
    
    // Build up solution
    for (int i = 2; i < n; ++i) {
        // Either rob current house + money from i-2, or skip current and take i-1
        dp[i] = std::max(dp[i-1], nums[i] + dp[i-2]);
    }
    
    return dp[n-1];
}

int HouseRobber::robOptimized(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    // Only need to track previous two values
    int prev2 = nums[0];  // dp[i-2]
    int prev1 = std::max(nums[0], nums[1]);  // dp[i-1]
    
    for (int i = 2; i < n; ++i) {
        int current = std::max(prev1, nums[i] + prev2);
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

int HouseRobber::robRecursive(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    std::unordered_map<int, int> memo;
    return robRecursiveHelper(nums, 0, memo);
}

int HouseRobber::robRecursiveHelper(std::vector<int>& nums, int index, 
                                   std::unordered_map<int, int>& memo) {
    // Base cases
    if (index >= nums.size()) return 0;
    
    // Check memoization
    if (memo.find(index) != memo.end()) {
        return memo[index];
    }
    
    // Choice: rob current house or skip it
    int robCurrent = nums[index] + robRecursiveHelper(nums, index + 2, memo);
    int skipCurrent = robRecursiveHelper(nums, index + 1, memo);
    
    memo[index] = std::max(robCurrent, skipCurrent);
    return memo[index];
}

int HouseRobber::robEvenOdd(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return std::max(nums[0], nums[1]);
    
    // Consider two scenarios as starting points for DP
    // Scenario 1: Can start from house 0
    int dp0_prev2 = nums[0];
    int dp0_prev1 = std::max(nums[0], nums[1]);
    
    for (int i = 2; i < n; ++i) {
        int current = std::max(dp0_prev1, nums[i] + dp0_prev2);
        dp0_prev2 = dp0_prev1;
        dp0_prev1 = current;
    }
    
    // The result is the same as standard DP
    // This approach mainly demonstrates alternative thinking
    return dp0_prev1;
}

int HouseRobber::robStateMachine(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    // State: just robbed previous house
    int robbed = nums[0];
    // State: didn't rob previous house
    int notRobbed = 0;
    
    for (int i = 1; i < n; ++i) {
        int newRobbed = nums[i] + notRobbed;  // Rob current, must not have robbed previous
        int newNotRobbed = std::max(robbed, notRobbed);  // Don't rob current
        
        robbed = newRobbed;
        notRobbed = newNotRobbed;
    }
    
    return std::max(robbed, notRobbed);
}

int HouseRobber::robMathPattern(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    // Check for special patterns that allow optimization
    if (hasUniformValues(nums)) {
        // All houses have same value - rob every other house
        int evenSum = calculateAlternatingSum(nums, 0);
        int oddSum = calculateAlternatingSum(nums, 1);
        return std::max(evenSum, oddSum);
    }
    
    if (isStrictlyIncreasing(nums)) {
        // For strictly increasing values, there's often a pattern
        // where we transition from skipping to taking at some point
        // But we still need DP to find optimal solution
    }
    
    // For general case, use space-optimized DP
    int prev2 = nums[0];
    int prev1 = std::max(nums[0], nums[1]);
    
    for (int i = 2; i < n; ++i) {
        int current = std::max(prev1, nums[i] + prev2);
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

// Helper function implementations
bool HouseRobber::hasUniformValues(const std::vector<int>& nums) {
    if (nums.size() <= 1) return true;
    
    int firstValue = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != firstValue) return false;
    }
    return true;
}

bool HouseRobber::isStrictlyIncreasing(const std::vector<int>& nums) {
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] <= nums[i-1]) return false;
    }
    return true;
}

int HouseRobber::calculateAlternatingSum(const std::vector<int>& nums, int start) {
    int sum = 0;
    for (int i = start; i < nums.size(); i += 2) {
        sum += nums[i];
    }
    return sum;
}

}
}