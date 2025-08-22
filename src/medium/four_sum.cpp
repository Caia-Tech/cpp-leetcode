#include "four_sum.h"
#include <set>

namespace leetcode {
namespace medium {

std::vector<std::vector<int>> FourSum::fourSumTwoPointers(std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    if (n < 4) return result;
    
    std::sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 3; ++i) {
        // Skip duplicate for first element
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        for (int j = i + 1; j < n - 2; ++j) {
            // Skip duplicate for second element
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            
            int left = j + 1;
            int right = n - 1;
            long long twoSum = (long long)target - nums[i] - nums[j];
            
            while (left < right) {
                long long currentSum = (long long)nums[left] + nums[right];
                
                if (currentSum == twoSum) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    
                    // Skip duplicates for third element
                    while (left < right && nums[left] == nums[left + 1]) ++left;
                    // Skip duplicates for fourth element
                    while (left < right && nums[right] == nums[right - 1]) --right;
                    
                    ++left;
                    --right;
                } else if (currentSum < twoSum) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
    }
    
    return result;
}

std::vector<std::vector<int>> FourSum::fourSumHashMap(std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    if (n < 4) return result;
    
    std::set<std::vector<int>> uniqueQuadruplets;
    std::unordered_map<long long, std::vector<PairSum>> pairSums;
    
    // Generate all pair sums
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long sum = (long long)nums[i] + nums[j];
            pairSums[sum].emplace_back(sum, i, j);
        }
    }
    
    // Find complementary pairs
    for (const auto& entry : pairSums) {
        long long sum1 = entry.first;
        long long sum2 = (long long)target - sum1;
        
        if (pairSums.find(sum2) != pairSums.end()) {
            for (const PairSum& pair1 : entry.second) {
                for (const PairSum& pair2 : pairSums[sum2]) {
                    // Check that all indices are distinct
                    std::set<int> indices = {pair1.i, pair1.j, pair2.i, pair2.j};
                    if (indices.size() == 4) {
                        std::vector<int> quad = {nums[pair1.i], nums[pair1.j], nums[pair2.i], nums[pair2.j]};
                        std::sort(quad.begin(), quad.end());
                        uniqueQuadruplets.insert(quad);
                    }
                }
            }
        }
    }
    
    return std::vector<std::vector<int>>(uniqueQuadruplets.begin(), uniqueQuadruplets.end());
}

std::vector<std::vector<int>> FourSum::fourSumBruteForce(std::vector<int>& nums, int target) {
    std::set<std::vector<int>> uniqueQuadruplets;
    int n = nums.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                for (int l = k + 1; l < n; ++l) {
                    if ((long long)nums[i] + nums[j] + nums[k] + nums[l] == target) {
                        std::vector<int> quad = {nums[i], nums[j], nums[k], nums[l]};
                        std::sort(quad.begin(), quad.end());
                        uniqueQuadruplets.insert(quad);
                    }
                }
            }
        }
    }
    
    return std::vector<std::vector<int>>(uniqueQuadruplets.begin(), uniqueQuadruplets.end());
}

std::vector<std::vector<int>> FourSum::fourSumRecursive(std::vector<int>& nums, int target) {
    if (nums.size() < 4) return {};
    std::sort(nums.begin(), nums.end());
    return kSum(nums, target, 4, 0);
}

std::vector<std::vector<int>> FourSum::kSum(std::vector<int>& nums, int target, int k, int startIndex) {
    std::vector<std::vector<int>> result;
    
    if (startIndex >= nums.size()) return result;
    
    // Base case: 2Sum
    if (k == 2) {
        return twoSum(nums, target, startIndex);
    }
    
    for (int i = startIndex; i <= (int)nums.size() - k; ++i) {
        // Skip duplicates
        if (i > startIndex && nums[i] == nums[i - 1]) continue;
        
        // Recursive call for (k-1)Sum
        auto subResults = kSum(nums, target - nums[i], k - 1, i + 1);
        
        // Add current element to each sub-result
        for (auto& subResult : subResults) {
            subResult.insert(subResult.begin(), nums[i]);
            result.push_back(subResult);
        }
    }
    
    return result;
}

std::vector<std::vector<int>> FourSum::twoSum(std::vector<int>& nums, int target, int startIndex) {
    std::vector<std::vector<int>> result;
    int left = startIndex;
    int right = nums.size() - 1;
    
    while (left < right) {
        long long sum = (long long)nums[left] + nums[right];
        
        if (sum == target) {
            result.push_back({nums[left], nums[right]});
            
            // Skip duplicates
            while (left < right && nums[left] == nums[left + 1]) ++left;
            while (left < right && nums[right] == nums[right - 1]) --right;
            
            ++left;
            --right;
        } else if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }
    
    return result;
}

std::vector<std::vector<int>> FourSum::fourSumOptimized(std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    if (n < 4) return result;
    
    std::sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 3; ++i) {
        // Skip duplicates for first element
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        // Early termination: minimum possible sum too large
        if ((long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
        
        // Early termination: maximum possible sum too small
        if ((long long)nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) continue;
        
        for (int j = i + 1; j < n - 2; ++j) {
            // Skip duplicates for second element
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            
            // Early termination for inner loop
            if ((long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
            if ((long long)nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target) continue;
            
            int left = j + 1;
            int right = n - 1;
            long long twoSum = (long long)target - nums[i] - nums[j];
            
            while (left < right) {
                long long currentSum = (long long)nums[left] + nums[right];
                
                if (currentSum == twoSum) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    
                    // Skip duplicates
                    while (left < right && nums[left] == nums[left + 1]) ++left;
                    while (left < right && nums[right] == nums[right - 1]) --right;
                    
                    ++left;
                    --right;
                } else if (currentSum < twoSum) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
    }
    
    return result;
}

std::vector<std::vector<int>> FourSum::fourSumDivideConquer(std::vector<int>& nums, int target) {
    if (nums.size() < 4) return {};
    
    std::vector<std::vector<int>> result;
    divideFourSum(nums, target, 0, nums.size() - 1, result);
    
    // Remove duplicates
    std::set<std::vector<int>> uniqueSet;
    for (auto& quad : result) {
        std::sort(quad.begin(), quad.end());
        uniqueSet.insert(quad);
    }
    
    return std::vector<std::vector<int>>(uniqueSet.begin(), uniqueSet.end());
}

void FourSum::divideFourSum(std::vector<int>& nums, int target, int left, int right, 
                           std::vector<std::vector<int>>& result) {
    if (right - left + 1 < 4) return;
    
    // Base case: small enough to use brute force
    if (right - left + 1 <= 8) {
        for (int i = left; i <= right - 3; ++i) {
            for (int j = i + 1; j <= right - 2; ++j) {
                for (int k = j + 1; k <= right - 1; ++k) {
                    for (int l = k + 1; l <= right; ++l) {
                        if ((long long)nums[i] + nums[j] + nums[k] + nums[l] == target) {
                            result.push_back({nums[i], nums[j], nums[k], nums[l]});
                        }
                    }
                }
            }
        }
        return;
    }
    
    int mid = left + (right - left) / 2;
    
    // Recursively solve left and right halves
    divideFourSum(nums, target, left, mid, result);
    divideFourSum(nums, target, mid + 1, right, result);
    
    // Find quadruplets crossing the midpoint
    // This is a simplified version - full implementation would be more complex
    std::vector<std::pair<long long, std::pair<int, int>>> leftPairs, rightPairs;
    
    // Generate pairs from left half
    for (int i = left; i <= mid - 1; ++i) {
        for (int j = i + 1; j <= mid; ++j) {
            leftPairs.push_back({(long long)nums[i] + nums[j], {i, j}});
        }
    }
    
    // Generate pairs from right half
    for (int i = mid + 1; i <= right - 1; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            rightPairs.push_back({(long long)nums[i] + nums[j], {i, j}});
        }
    }
    
    // Find matching pairs
    for (const auto& leftPair : leftPairs) {
        long long needed = (long long)target - leftPair.first;
        for (const auto& rightPair : rightPairs) {
            if (rightPair.first == needed) {
                result.push_back({nums[leftPair.second.first], nums[leftPair.second.second],
                                nums[rightPair.second.first], nums[rightPair.second.second]});
            }
        }
    }
}

}
}