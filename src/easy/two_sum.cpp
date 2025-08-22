#include "two_sum.h"
#include <algorithm>

namespace leetcode {
namespace easy {

std::vector<int> TwoSum::twoSumBruteForce(const std::vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}

std::vector<int> TwoSum::twoSumHashMapOnePass(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }
        
        seen[nums[i]] = i;
    }
    
    return {};
}

std::vector<int> TwoSum::twoSumHashMapTwoPass(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;
    
    for (int i = 0; i < nums.size(); ++i) {
        numMap[nums[i]] = i;
    }
    
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        
        if (numMap.find(complement) != numMap.end() && numMap[complement] != i) {
            return {i, numMap[complement]};
        }
    }
    
    return {};
}

std::vector<int> TwoSum::twoSumSortedTwoPointers(const std::vector<int>& nums, int target) {
    std::vector<std::pair<int, int>> indexed;
    for (int i = 0; i < nums.size(); ++i) {
        indexed.push_back({nums[i], i});
    }
    
    std::sort(indexed.begin(), indexed.end());
    
    int left = 0;
    int right = indexed.size() - 1;
    
    while (left < right) {
        int sum = indexed[left].first + indexed[right].first;
        
        if (sum == target) {
            int idx1 = indexed[left].second;
            int idx2 = indexed[right].second;
            return idx1 < idx2 ? std::vector<int>{idx1, idx2} : std::vector<int>{idx2, idx1};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {};
}

std::vector<int> TwoSum::twoSumHashSet(const std::vector<int>& nums, int target) {
    std::unordered_set<int> seen;
    
    for (int num : nums) {
        seen.insert(num);
    }
    
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        
        if (seen.find(complement) != seen.end()) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[j] == complement) {
                    return {i, j};
                }
            }
        }
    }
    
    return {};
}

std::vector<int> TwoSum::twoSumBinarySearch(const std::vector<int>& nums, int target) {
    std::vector<std::pair<int, int>> indexed;
    for (int i = 0; i < nums.size(); ++i) {
        indexed.push_back({nums[i], i});
    }
    
    std::sort(indexed.begin(), indexed.end());
    
    for (int i = 0; i < indexed.size() - 1; ++i) {
        int complement = target - indexed[i].first;
        
        auto it = std::lower_bound(
            indexed.begin() + i + 1, 
            indexed.end(), 
            std::make_pair(complement, 0)
        );
        
        if (it != indexed.end() && it->first == complement) {
            int idx1 = indexed[i].second;
            int idx2 = it->second;
            return idx1 < idx2 ? std::vector<int>{idx1, idx2} : std::vector<int>{idx2, idx1};
        }
    }
    
    return {};
}

}
}