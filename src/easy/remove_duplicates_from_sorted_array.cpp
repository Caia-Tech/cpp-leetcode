#include "remove_duplicates_from_sorted_array.h"

namespace leetcode {
namespace easy {

int RemoveDuplicatesFromSortedArray::removeDuplicatesTwoPointers(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 1; // Position for next unique element
    
    for (int fast = 1; fast < nums.size(); ++fast) {
        // Found a new unique element
        if (nums[fast] != nums[fast - 1]) {
            nums[slow] = nums[fast];
            ++slow;
        }
    }
    
    return slow;
}

int RemoveDuplicatesFromSortedArray::removeDuplicatesHashSet(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    std::unordered_set<int> seen;
    int writeIndex = 0;
    
    for (int i = 0; i < nums.size(); ++i) {
        if (seen.find(nums[i]) == seen.end()) {
            seen.insert(nums[i]);
            nums[writeIndex] = nums[i];
            ++writeIndex;
        }
    }
    
    return writeIndex;
}

int RemoveDuplicatesFromSortedArray::removeDuplicatesWriteIndex(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int writeIndex = 1;
    
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[i - 1]) {
            nums[writeIndex] = nums[i];
            ++writeIndex;
        }
    }
    
    return writeIndex;
}

int RemoveDuplicatesFromSortedArray::removeDuplicatesSTL(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    auto newEnd = std::unique(nums.begin(), nums.end());
    return std::distance(nums.begin(), newEnd);
}

int RemoveDuplicatesFromSortedArray::removeDuplicatesOverwrite(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int uniqueCount = 1;
    
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] != nums[uniqueCount - 1]) {
            nums[uniqueCount] = nums[i];
            ++uniqueCount;
        }
    }
    
    return uniqueCount;
}

int RemoveDuplicatesFromSortedArray::removeDuplicatesRecursive(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    return removeDuplicatesHelper(nums, 0, nums.size() - 1);
}

int RemoveDuplicatesFromSortedArray::removeDuplicatesHelper(std::vector<int>& nums, int start, int end) {
    if (start >= end) return 1;
    
    int mid = start + (end - start) / 2;
    
    // Process left and right halves
    int leftCount = removeDuplicatesHelper(nums, start, mid);
    int rightCount = removeDuplicatesHelper(nums, mid + 1, end);
    
    // Merge the results - remove duplicates at boundary
    int writePos = start + leftCount;
    bool lastElementFromLeft = (leftCount > 0);
    
    // Copy right half, skipping duplicates
    for (int i = mid + 1; i <= end; ++i) {
        if (!lastElementFromLeft || nums[i] != nums[start + leftCount - 1]) {
            nums[writePos] = nums[i];
            ++writePos;
            lastElementFromLeft = false;
        }
    }
    
    return writePos - start;
}

}
}