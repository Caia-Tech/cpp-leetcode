#include "remove_element.h"

namespace leetcode {
namespace easy {

int RemoveElement::removeElementTwoPointers(std::vector<int>& nums, int val) {
    int slow = 0;
    
    for (int fast = 0; fast < nums.size(); ++fast) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            ++slow;
        }
    }
    
    return slow;
}

int RemoveElement::removeElementStartEnd(std::vector<int>& nums, int val) {
    int start = 0;
    int end = nums.size();
    
    while (start < end) {
        if (nums[start] == val) {
            // Swap with element at end and shrink array
            nums[start] = nums[end - 1];
            --end;
        } else {
            ++start;
        }
    }
    
    return end;
}

int RemoveElement::removeElementOverwrite(std::vector<int>& nums, int val) {
    int writeIndex = 0;
    
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != val) {
            nums[writeIndex] = nums[i];
            ++writeIndex;
        }
    }
    
    return writeIndex;
}

int RemoveElement::removeElementSTL(std::vector<int>& nums, int val) {
    auto newEnd = std::remove(nums.begin(), nums.end(), val);
    return std::distance(nums.begin(), newEnd);
}

int RemoveElement::removeElementErase(std::vector<int>& nums, int val) {
    for (int i = nums.size() - 1; i >= 0; --i) {
        if (nums[i] == val) {
            nums.erase(nums.begin() + i);
        }
    }
    
    return nums.size();
}

int RemoveElement::removeElementCounting(std::vector<int>& nums, int val) {
    // First pass: count valid elements
    int validCount = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != val) {
            ++validCount;
        }
    }
    
    // Second pass: copy valid elements to front
    int writePos = 0;
    for (int i = 0; i < nums.size() && writePos < validCount; ++i) {
        if (nums[i] != val) {
            nums[writePos] = nums[i];
            ++writePos;
        }
    }
    
    return validCount;
}

}
}