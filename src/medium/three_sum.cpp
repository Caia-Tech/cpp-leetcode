#include "three_sum.h"
#include <algorithm>
#include <unordered_set>
#include <set>

namespace leetcode {
namespace medium {

std::string ThreeSum::tripletToString(int a, int b, int c) {
    std::vector<int> triplet = {a, b, c};
    std::sort(triplet.begin(), triplet.end());
    return std::to_string(triplet[0]) + "," + 
           std::to_string(triplet[1]) + "," + 
           std::to_string(triplet[2]);
}

std::vector<std::vector<int>> ThreeSum::threeSumBruteForce(std::vector<int>& nums) {
    int n = nums.size();
    std::set<std::vector<int>> resultSet;
    
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    std::vector<int> triplet = {nums[i], nums[j], nums[k]};
                    std::sort(triplet.begin(), triplet.end());
                    resultSet.insert(triplet);
                }
            }
        }
    }
    
    return std::vector<std::vector<int>>(resultSet.begin(), resultSet.end());
}

std::vector<std::vector<int>> ThreeSum::threeSumTwoPointers(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;
    
    std::sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}

std::vector<std::vector<int>> ThreeSum::threeSumHashSet(std::vector<int>& nums) {
    std::set<std::vector<int>> resultSet;
    int n = nums.size();
    
    for (int i = 0; i < n - 2; ++i) {
        std::unordered_set<int> seen;
        for (int j = i + 1; j < n; ++j) {
            int complement = -(nums[i] + nums[j]);
            if (seen.find(complement) != seen.end()) {
                std::vector<int> triplet = {nums[i], nums[j], complement};
                std::sort(triplet.begin(), triplet.end());
                resultSet.insert(triplet);
            }
            seen.insert(nums[j]);
        }
    }
    
    return std::vector<std::vector<int>>(resultSet.begin(), resultSet.end());
}

std::vector<std::vector<int>> ThreeSum::threeSumHashMap(std::vector<int>& nums) {
    std::unordered_set<std::string> usedTriplets;
    std::vector<std::vector<int>> result;
    int n = nums.size();
    
    std::unordered_map<int, std::vector<std::pair<int, int>>> twoSum;
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = nums[i] + nums[j];
            twoSum[sum].push_back({i, j});
        }
    }
    
    for (int i = 0; i < n; ++i) {
        int target = -nums[i];
        if (twoSum.find(target) != twoSum.end()) {
            for (auto& pair : twoSum[target]) {
                if (pair.first != i && pair.second != i) {
                    std::string key = tripletToString(nums[i], nums[pair.first], nums[pair.second]);
                    if (usedTriplets.find(key) == usedTriplets.end()) {
                        usedTriplets.insert(key);
                        result.push_back({nums[i], nums[pair.first], nums[pair.second]});
                    }
                }
            }
        }
    }
    
    return result;
}

std::vector<std::vector<int>> ThreeSum::threeSumBinarySearch(std::vector<int>& nums) {
    std::set<std::vector<int>> resultSet;
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            int target = -(nums[i] + nums[j]);
            
            auto it = std::lower_bound(nums.begin() + j + 1, nums.end(), target);
            if (it != nums.end() && *it == target) {
                std::vector<int> triplet = {nums[i], nums[j], target};
                resultSet.insert(triplet);
            }
        }
    }
    
    return std::vector<std::vector<int>>(resultSet.begin(), resultSet.end());
}

std::vector<std::vector<int>> ThreeSum::threeSumOptimized(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;
    
    std::sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; ++i) {
        if (nums[i] > 0) break;
        
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        if (nums[i] + nums[n - 2] + nums[n - 1] < 0) continue;
        
        if (nums[i] + nums[i + 1] + nums[i + 2] > 0) break;
        
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                
                int leftVal = nums[left];
                int rightVal = nums[right];
                
                while (left < right && nums[left] == leftVal) left++;
                while (left < right && nums[right] == rightVal) right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}

}
}