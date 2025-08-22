#include "search_insert_position.h"

namespace leetcode {
namespace easy {

int SearchInsertPosition::searchInsertBinarySearch(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
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
    
    // At this point, left is the insertion position
    return left;
}

int SearchInsertPosition::searchInsertLinear(const std::vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] >= target) {
            return i;
        }
    }
    
    // Target is larger than all elements
    return nums.size();
}

int SearchInsertPosition::searchInsertSTL(const std::vector<int>& nums, int target) {
    auto it = std::lower_bound(nums.begin(), nums.end(), target);
    return std::distance(nums.begin(), it);
}

int SearchInsertPosition::searchInsertRecursive(const std::vector<int>& nums, int target) {
    return binarySearchRecursive(nums, target, 0, nums.size() - 1);
}

int SearchInsertPosition::binarySearchRecursive(const std::vector<int>& nums, int target, int left, int right) {
    if (left > right) {
        return left;  // Insertion position
    }
    
    int mid = left + (right - left) / 2;
    
    if (nums[mid] == target) {
        return mid;
    } else if (nums[mid] < target) {
        return binarySearchRecursive(nums, target, mid + 1, right);
    } else {
        return binarySearchRecursive(nums, target, left, mid - 1);
    }
}

int SearchInsertPosition::searchInsertOptimized(const std::vector<int>& nums, int target) {
    // Early termination checks
    if (target <= nums[0]) return 0;
    if (target > nums.back()) return nums.size();
    
    int left = 0;
    int right = nums.size() - 1;
    
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
    
    return left;
}

int SearchInsertPosition::searchInsertInterpolation(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right && target >= nums[left] && target <= nums[right]) {
        // If array has only one element
        if (left == right) {
            if (nums[left] >= target) return left;
            return left + 1;
        }
        
        // Interpolation formula
        int pos = left + ((target - nums[left]) * (right - left)) / (nums[right] - nums[left]);
        
        // Bounds checking for safety
        pos = std::max(left, std::min(pos, right));
        
        if (nums[pos] == target) {
            return pos;
        } else if (nums[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    
    // Fallback to ensure correct insertion position
    if (target <= nums[left]) return left;
    return left + 1;
}

}
}