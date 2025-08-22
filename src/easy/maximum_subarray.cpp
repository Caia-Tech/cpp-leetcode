#include "maximum_subarray.h"
#include <algorithm>
#include <climits>

namespace leetcode {
namespace easy {

int MaximumSubarray::maxSubArrayBruteForce(std::vector<int>& nums) {
    int maxSum = INT_MIN;
    int n = nums.size();
    
    for (int i = 0; i < n; ++i) {
        int currentSum = 0;
        for (int j = i; j < n; ++j) {
            currentSum += nums[j];
            maxSum = std::max(maxSum, currentSum);
        }
    }
    
    return maxSum;
}

int MaximumSubarray::maxSubArrayKadane(std::vector<int>& nums) {
    int maxSoFar = nums[0];
    int maxEndingHere = nums[0];
    
    for (int i = 1; i < nums.size(); ++i) {
        maxEndingHere = std::max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = std::max(maxSoFar, maxEndingHere);
    }
    
    return maxSoFar;
}

int MaximumSubarray::maxSubArrayDivideConquer(std::vector<int>& nums) {
    return divideConquerHelper(nums, 0, nums.size() - 1);
}

int MaximumSubarray::divideConquerHelper(std::vector<int>& nums, int left, int right) {
    if (left == right) {
        return nums[left];
    }
    
    int mid = left + (right - left) / 2;
    
    int leftSum = divideConquerHelper(nums, left, mid);
    int rightSum = divideConquerHelper(nums, mid + 1, right);
    int crossSum = maxCrossingSum(nums, left, mid, right);
    
    return std::max({leftSum, rightSum, crossSum});
}

int MaximumSubarray::maxCrossingSum(std::vector<int>& nums, int left, int mid, int right) {
    int leftSum = INT_MIN;
    int sum = 0;
    
    for (int i = mid; i >= left; --i) {
        sum += nums[i];
        leftSum = std::max(leftSum, sum);
    }
    
    int rightSum = INT_MIN;
    sum = 0;
    
    for (int i = mid + 1; i <= right; ++i) {
        sum += nums[i];
        rightSum = std::max(rightSum, sum);
    }
    
    return leftSum + rightSum;
}

int MaximumSubarray::maxSubArrayDP(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> dp(n);
    dp[0] = nums[0];
    int maxSum = dp[0];
    
    for (int i = 1; i < n; ++i) {
        dp[i] = std::max(nums[i], dp[i - 1] + nums[i]);
        maxSum = std::max(maxSum, dp[i]);
    }
    
    return maxSum;
}

int MaximumSubarray::maxSubArrayPrefixSum(std::vector<int>& nums) {
    int maxSum = INT_MIN;
    int minPrefixSum = 0;
    int prefixSum = 0;
    
    for (int num : nums) {
        prefixSum += num;
        maxSum = std::max(maxSum, prefixSum - minPrefixSum);
        minPrefixSum = std::min(minPrefixSum, prefixSum);
    }
    
    return maxSum;
}

int MaximumSubarray::maxSubArrayWithIndices(std::vector<int>& nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    int start = 0, end = 0;
    int tempStart = 0;
    
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > currentSum + nums[i]) {
            currentSum = nums[i];
            tempStart = i;
        } else {
            currentSum += nums[i];
        }
        
        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            end = i;
        }
    }
    
    return maxSum;
}

}
}