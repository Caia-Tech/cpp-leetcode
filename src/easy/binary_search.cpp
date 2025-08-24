#include "binary_search.h"
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: Classic Binary Search (Optimal)
int BinarySearch::searchClassic(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }
    
    return -1;  // Target not found
}

// Approach 2: Recursive Binary Search
int BinarySearch::searchRecursive(std::vector<int>& nums, int target) {
    return searchRecursiveHelper(nums, target, 0, nums.size() - 1);
}

int BinarySearch::searchRecursiveHelper(std::vector<int>& nums, int target, int left, int right) {
    // Base case: search space is empty
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if (nums[mid] == target) {
        return mid;
    } else if (nums[mid] < target) {
        return searchRecursiveHelper(nums, target, mid + 1, right);
    } else {
        return searchRecursiveHelper(nums, target, left, mid - 1);
    }
}

// Approach 3: Binary Search with Bit Manipulation
int BinarySearch::searchBitManipulation(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right) {
        // Use bit shift for division by 2
        int mid = left + ((right - left) >> 1);
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Approach 4: Lower Bound Binary Search
int BinarySearch::searchLowerBound(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size();
    
    // Find first position where nums[pos] >= target
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    // Check if we found the target
    if (left < nums.size() && nums[left] == target) {
        return left;
    }
    
    return -1;
}

// Approach 5: Exponential Search then Binary Search
int BinarySearch::searchExponential(std::vector<int>& nums, int target) {
    int n = nums.size();
    
    // If target is at first position
    if (nums[0] == target) {
        return 0;
    }
    
    // Find range for binary search using exponential search
    int bound = 1;
    while (bound < n && nums[bound] < target) {
        bound *= 2;
    }
    
    // Perform binary search in the found range
    return binarySearchRange(nums, target, bound / 2, std::min(bound, n - 1));
}

int BinarySearch::binarySearchRange(std::vector<int>& nums, int target, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Approach 6: Interpolation Search
int BinarySearch::searchInterpolation(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right && target >= nums[left] && target <= nums[right]) {
        // If only one element
        if (left == right) {
            return nums[left] == target ? left : -1;
        }
        
        // Estimate position using interpolation formula
        // pos = left + [(target - nums[left]) / (nums[right] - nums[left])] * (right - left)
        int pos = left + static_cast<int>(
            static_cast<double>(target - nums[left]) / 
            static_cast<double>(nums[right] - nums[left]) * 
            (right - left)
        );
        
        // Ensure pos is within bounds
        pos = std::max(left, std::min(pos, right));
        
        if (nums[pos] == target) {
            return pos;
        } else if (nums[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    
    return -1;
}

}  // namespace easy
}  // namespace leetcode