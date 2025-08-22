#include "search_in_rotated_sorted_array.h"

namespace leetcode {
namespace medium {

int SearchInRotatedSortedArray::searchModifiedBinarySearch(const std::vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        // Determine which half is properly sorted
        if (nums[left] <= nums[mid]) {
            // Left half is sorted
            if (target >= nums[left] && target < nums[mid]) {
                // Target is in sorted left half
                right = mid - 1;
            } else {
                // Target is in right half
                left = mid + 1;
            }
        } else {
            // Right half is sorted
            if (target > nums[mid] && target <= nums[right]) {
                // Target is in sorted right half
                left = mid + 1;
            } else {
                // Target is in left half
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

int SearchInRotatedSortedArray::searchFindPivotFirst(const std::vector<int>& nums, int target) {
    int n = nums.size();
    if (n == 1) return nums[0] == target ? 0 : -1;
    
    // Find pivot (rotation point)
    int pivot = findPivot(nums);
    
    // If array is not rotated
    if (pivot == 0) {
        return binarySearch(nums, 0, n - 1, target);
    }
    
    // Determine which half to search
    if (target >= nums[0]) {
        // Target should be in first half
        return binarySearch(nums, 0, pivot - 1, target);
    } else {
        // Target should be in second half
        return binarySearch(nums, pivot, n - 1, target);
    }
}

int SearchInRotatedSortedArray::findPivot(const std::vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    // If array is not rotated
    if (nums[left] <= nums[right]) {
        return 0;
    }
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Check if mid is the pivot
        if (mid < nums.size() - 1 && nums[mid] > nums[mid + 1]) {
            return mid + 1;
        }
        
        // Check if mid-1 is the pivot
        if (mid > 0 && nums[mid - 1] > nums[mid]) {
            return mid;
        }
        
        // Decide which half to continue searching
        if (nums[mid] >= nums[left]) {
            // Pivot is in right half
            left = mid + 1;
        } else {
            // Pivot is in left half
            right = mid - 1;
        }
    }
    
    return 0;
}

int SearchInRotatedSortedArray::binarySearch(const std::vector<int>& nums, int left, int right, int target) {
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

int SearchInRotatedSortedArray::searchRecursive(const std::vector<int>& nums, int target) {
    return searchRecursiveHelper(nums, 0, nums.size() - 1, target);
}

int SearchInRotatedSortedArray::searchRecursiveHelper(const std::vector<int>& nums, int left, int right, int target) {
    if (left > right) return -1;
    
    int mid = left + (right - left) / 2;
    
    if (nums[mid] == target) {
        return mid;
    }
    
    // Determine which half is sorted
    if (nums[left] <= nums[mid]) {
        // Left half is sorted
        if (target >= nums[left] && target < nums[mid]) {
            return searchRecursiveHelper(nums, left, mid - 1, target);
        } else {
            return searchRecursiveHelper(nums, mid + 1, right, target);
        }
    } else {
        // Right half is sorted
        if (target > nums[mid] && target <= nums[right]) {
            return searchRecursiveHelper(nums, mid + 1, right, target);
        } else {
            return searchRecursiveHelper(nums, left, mid - 1, target);
        }
    }
}

int SearchInRotatedSortedArray::searchLinear(const std::vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == target) {
            return i;
        }
    }
    return -1;
}

int SearchInRotatedSortedArray::searchUnrotate(const std::vector<int>& nums, int target) {
    int n = nums.size();
    int pivot = findPivot(nums);
    
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int realMid = mapIndex(mid, pivot, n);
        
        if (nums[realMid] == target) {
            return realMid;
        } else if (nums[realMid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int SearchInRotatedSortedArray::mapIndex(int index, int pivot, int n) {
    return (index + pivot) % n;
}

int SearchInRotatedSortedArray::searchThreeWayPartition(const std::vector<int>& nums, int target) {
    int n = nums.size();
    int section1, section2, section3;
    analyzeRotationStructure(nums, section1, section2, section3);
    
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        // Analyze which section we're in and where target should be
        if (nums[left] <= nums[mid]) {
            // We're in ascending section
            if (target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            // We're crossing rotation boundary
            if (target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

void SearchInRotatedSortedArray::analyzeRotationStructure(const std::vector<int>& nums, int& section1, int& section2, int& section3) {
    int n = nums.size();
    
    // Find boundaries of different sections
    section1 = 0; // Start of high values
    section2 = -1; // Rotation point (if exists)
    section3 = -1; // Start of low values after rotation
    
    // Find rotation point
    for (int i = 1; i < n; ++i) {
        if (nums[i] < nums[i - 1]) {
            section2 = i - 1;
            section3 = i;
            break;
        }
    }
    
    // If no rotation found, entire array is section1
    if (section2 == -1) {
        section2 = section3 = n;
    }
}

}
}