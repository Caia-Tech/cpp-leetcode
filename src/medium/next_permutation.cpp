#include "next_permutation.h"
#include <climits>

namespace leetcode {
namespace medium {

void NextPermutation::nextPermutationStandard(std::vector<int>& nums) {
    int n = nums.size();
    int pivot = -1;
    
    // Step 1: Find rightmost character that is smaller than its next character
    for (int i = n - 2; i >= 0; --i) {
        if (nums[i] < nums[i + 1]) {
            pivot = i;
            break;
        }
    }
    
    // If no pivot found, array is in descending order (largest permutation)
    if (pivot == -1) {
        std::reverse(nums.begin(), nums.end());
        return;
    }
    
    // Step 2: Find the smallest character to the right of pivot that's larger than pivot
    int successor = -1;
    for (int i = n - 1; i > pivot; --i) {
        if (nums[i] > nums[pivot]) {
            successor = i;
            break;
        }
    }
    
    // Step 3: Swap pivot with successor
    std::swap(nums[pivot], nums[successor]);
    
    // Step 4: Reverse the suffix after pivot position
    std::reverse(nums.begin() + pivot + 1, nums.end());
}

void NextPermutation::nextPermutationSTL(std::vector<int>& nums) {
    std::next_permutation(nums.begin(), nums.end());
}

void NextPermutation::nextPermutationRecursive(std::vector<int>& nums) {
    if (!nextPermutationRecursiveHelper(nums, nums.size() - 1)) {
        // If no next permutation possible, reverse to get smallest
        std::reverse(nums.begin(), nums.end());
    }
}

bool NextPermutation::nextPermutationRecursiveHelper(std::vector<int>& nums, int pos) {
    if (pos <= 0) return false;
    
    // Try to increment at current position
    if (canIncrementAtPosition(nums, pos)) {
        // Find next larger element from left side to swap with
        int nextLarger = findNextLarger(nums, 0, nums[pos]);
        if (nextLarger != -1 && nextLarger < pos) {
            std::swap(nums[pos], nums[nextLarger]);
            // Sort the prefix to get next permutation
            std::sort(nums.begin(), nums.begin() + pos);
            return true;
        }
    }
    
    // If can't increment at current position, try previous position
    return nextPermutationRecursiveHelper(nums, pos - 1);
}

bool NextPermutation::canIncrementAtPosition(std::vector<int>& nums, int pos) {
    // Check if there's a larger available element to the left
    for (int i = 0; i < pos; ++i) {
        if (nums[i] > nums[pos]) {
            return true;
        }
    }
    return false;
}

int NextPermutation::findNextLarger(const std::vector<int>& nums, int start, int target) {
    int result = -1;
    int minLarger = INT_MAX;
    
    for (int i = start; i < nums.size(); ++i) {
        if (nums[i] > target && nums[i] < minLarger) {
            minLarger = nums[i];
            result = i;
        }
    }
    
    return result;
}

void NextPermutation::nextPermutationDigitIncrement(std::vector<int>& nums) {
    int n = nums.size();
    
    // Start from rightmost position
    for (int pos = n - 1; pos >= 0; --pos) {
        // Try to find next larger value for this position from remaining elements
        std::vector<bool> used(101, false); // Given constraint: 0 <= nums[i] <= 100
        
        // Mark elements to the left as used (they're fixed)
        for (int i = 0; i < pos; ++i) {
            used[nums[i]] = true;
        }
        
        // Find next available value larger than current
        for (int val = nums[pos] + 1; val <= 100; ++val) {
            if (!used[val]) {
                // Check if this value exists to the right
                bool found = false;
                int swapIndex = -1;
                for (int i = pos + 1; i < n; ++i) {
                    if (nums[i] == val) {
                        found = true;
                        swapIndex = i;
                        break;
                    }
                }
                
                if (found) {
                    // Swap and sort the suffix
                    std::swap(nums[pos], nums[swapIndex]);
                    std::sort(nums.begin() + pos + 1, nums.end());
                    return;
                }
            }
        }
    }
    
    // If no increment possible, reverse to get smallest permutation
    std::reverse(nums.begin(), nums.end());
}

void NextPermutation::nextPermutationTwoPointers(std::vector<int>& nums) {
    int n = nums.size();
    int left = n - 2;
    int right = n - 1;
    
    // Find pivot using left pointer
    while (left >= 0 && nums[left] >= nums[left + 1]) {
        --left;
    }
    
    if (left >= 0) {
        // Find successor using right pointer
        while (nums[right] <= nums[left]) {
            --right;
        }
        
        // Swap pivot with successor
        std::swap(nums[left], nums[right]);
    }
    
    // Reverse suffix after pivot
    reverseRange(nums, left + 1, n - 1);
}

void NextPermutation::reverseRange(std::vector<int>& nums, int start, int end) {
    while (start < end) {
        std::swap(nums[start], nums[end]);
        ++start;
        --end;
    }
}

void NextPermutation::nextPermutationSegmentBased(std::vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return;
    
    std::vector<int> segmentTypes(n - 1);
    identifySegments(nums, segmentTypes);
    
    // Find rightmost ascending segment
    int pivot = -1;
    for (int i = n - 2; i >= 0; --i) {
        if (segmentTypes[i] == ASCENDING) {
            pivot = i;
            break;
        }
    }
    
    if (pivot == -1) {
        // All segments are descending, reverse entire array
        std::reverse(nums.begin(), nums.end());
        return;
    }
    
    // Find successor for pivot
    int successor = -1;
    for (int i = n - 1; i > pivot; --i) {
        if (nums[i] > nums[pivot]) {
            successor = i;
            break;
        }
    }
    
    // Swap and reverse suffix
    std::swap(nums[pivot], nums[successor]);
    std::reverse(nums.begin() + pivot + 1, nums.end());
}

void NextPermutation::identifySegments(const std::vector<int>& nums, std::vector<int>& segmentTypes) {
    for (int i = 0; i < segmentTypes.size(); ++i) {
        if (nums[i] < nums[i + 1]) {
            segmentTypes[i] = ASCENDING;
        } else if (nums[i] > nums[i + 1]) {
            segmentTypes[i] = DESCENDING;
        } else {
            segmentTypes[i] = MIXED; // Equal elements
        }
    }
}

}
}