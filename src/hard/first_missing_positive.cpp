#include "first_missing_positive.h"

namespace leetcode {
namespace hard {

int FirstMissingPositive::firstMissingPositiveCyclicSort(std::vector<int>& nums) {
    int n = nums.size();
    
    // Place each positive integer i at index i-1
    for (int i = 0; i < n; ++i) {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            std::swap(nums[i], nums[nums[i] - 1]);
        }
    }
    
    // Find first position where nums[i] != i+1
    for (int i = 0; i < n; ++i) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    
    // All positions 1 to n are filled correctly
    return n + 1;
}

int FirstMissingPositive::firstMissingPositiveSignMarking(std::vector<int>& nums) {
    int n = nums.size();
    
    // Step 1: Replace non-positive numbers with a positive number out of range
    int sentinel = n + 1;
    for (int i = 0; i < n; ++i) {
        if (nums[i] <= 0) {
            nums[i] = sentinel;
        }
    }
    
    // Step 2: Mark presence by making corresponding index negative
    for (int i = 0; i < n; ++i) {
        int num = abs(nums[i]);
        if (num <= n) {
            nums[num - 1] = -abs(nums[num - 1]);
        }
    }
    
    // Step 3: Find first positive number, its index+1 is the answer
    for (int i = 0; i < n; ++i) {
        if (nums[i] > 0) {
            return i + 1;
        }
    }
    
    // All numbers 1 to n are present
    return n + 1;
}

int FirstMissingPositive::firstMissingPositiveHashSet(std::vector<int>& nums) {
    std::unordered_set<int> numSet(nums.begin(), nums.end());
    
    for (int i = 1; i <= nums.size() + 1; ++i) {
        if (numSet.find(i) == numSet.end()) {
            return i;
        }
    }
    
    return nums.size() + 1;
}

int FirstMissingPositive::firstMissingPositiveSort(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    
    int expected = 1;
    for (int num : nums) {
        if (num == expected) {
            ++expected;
        } else if (num > expected) {
            // Found gap, return expected
            return expected;
        }
        // Skip duplicates and negatives/zeros
    }
    
    return expected;
}

int FirstMissingPositive::firstMissingPositiveBinarySearch(std::vector<int>& nums) {
    int left = 1, right = nums.size() + 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = countPositivesUpTo(nums, mid);
        
        if (count < mid) {
            // Missing positive is <= mid
            right = mid;
        } else {
            // All positives 1 to mid are present
            left = mid + 1;
        }
    }
    
    return left;
}

int FirstMissingPositive::countPositivesUpTo(const std::vector<int>& nums, int x) {
    int count = 0;
    for (int num : nums) {
        if (num >= 1 && num <= x) {
            ++count;
        }
    }
    return count;
}

int FirstMissingPositive::firstMissingPositivePartition(std::vector<int>& nums) {
    // Partition: move all positive numbers to the beginning
    int positiveEnd = partitionPositives(nums);
    
    // Apply cyclic sort to positive portion
    for (int i = 0; i < positiveEnd; ++i) {
        while (nums[i] > 0 && nums[i] <= positiveEnd && nums[nums[i] - 1] != nums[i]) {
            std::swap(nums[i], nums[nums[i] - 1]);
        }
    }
    
    // Find first missing in positive portion
    for (int i = 0; i < positiveEnd; ++i) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    
    // All positions in positive portion are correct
    return positiveEnd + 1;
}

int FirstMissingPositive::partitionPositives(std::vector<int>& nums) {
    int writeIndex = 0;
    
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            std::swap(nums[writeIndex], nums[i]);
            ++writeIndex;
        }
    }
    
    return writeIndex;
}

}
}