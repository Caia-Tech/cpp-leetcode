#include "merge_sorted_array.h"
#include <algorithm>
#include <queue>

namespace leetcode {
namespace easy {

// Approach 1: Three Pointers (Backward) - Optimal
void MergeSortedArray::mergeThreePointers(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    int i = m - 1;      // Last element in nums1's valid part
    int j = n - 1;      // Last element in nums2
    int k = m + n - 1;  // Last position in nums1
    
    // Merge from the end to avoid overwriting
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
    
    // Copy remaining elements from nums2 (if any)
    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
    
    // Note: if i >= 0, those elements are already in correct position
}

// Approach 2: Merge and Sort
void MergeSortedArray::mergeSortThenMerge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    // Copy all elements from nums2 to end of nums1
    for (int i = 0; i < n; ++i) {
        nums1[m + i] = nums2[i];
    }
    
    // Sort the entire array
    std::sort(nums1.begin(), nums1.end());
}

// Approach 3: Extra Array with Two Pointers
void MergeSortedArray::mergeExtraArray(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    std::vector<int> temp(m + n);
    int i = 0, j = 0, k = 0;
    
    // Merge into temporary array
    while (i < m && j < n) {
        if (nums1[i] <= nums2[j]) {
            temp[k] = nums1[i];
            i++;
        } else {
            temp[k] = nums2[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements from nums1
    while (i < m) {
        temp[k] = nums1[i];
        i++;
        k++;
    }
    
    // Copy remaining elements from nums2
    while (j < n) {
        temp[k] = nums2[j];
        j++;
        k++;
    }
    
    // Copy back to nums1
    for (int idx = 0; idx < m + n; ++idx) {
        nums1[idx] = temp[idx];
    }
}

// Approach 4: Insertion Sort Style
void MergeSortedArray::mergeInsertionStyle(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    int currentSize = m;
    
    // Insert each element from nums2 into nums1
    for (int i = 0; i < n; ++i) {
        int pos = findInsertionPos(nums1, nums2[i], currentSize);
        insertAt(nums1, pos, nums2[i], currentSize);
    }
}

int MergeSortedArray::findInsertionPos(const std::vector<int>& arr, int value, int size) {
    // Binary search for insertion position
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

void MergeSortedArray::insertAt(std::vector<int>& arr, int pos, int value, int& size) {
    // Shift elements to the right
    for (int i = size; i > pos; --i) {
        arr[i] = arr[i - 1];
    }
    // Insert the value
    arr[pos] = value;
    size++;
}

// Approach 5: Priority Queue (Heap)
void MergeSortedArray::mergePriorityQueue(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
    // Push all elements into min-heap
    for (int i = 0; i < m; ++i) {
        minHeap.push(nums1[i]);
    }
    for (int i = 0; i < n; ++i) {
        minHeap.push(nums2[i]);
    }
    
    // Pop elements in sorted order
    for (int i = 0; i < m + n; ++i) {
        nums1[i] = minHeap.top();
        minHeap.pop();
    }
}

// Approach 6: Two-Pass with Separate Arrays
void MergeSortedArray::mergeTwoPass(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    // Create copies of the arrays
    std::vector<int> arr1(nums1.begin(), nums1.begin() + m);
    std::vector<int> arr2(nums2.begin(), nums2.begin() + n);
    
    int i = 0, j = 0, k = 0;
    
    // Merge the copied arrays back into nums1
    while (i < m && j < n) {
        if (arr1[i] <= arr2[j]) {
            nums1[k] = arr1[i];
            i++;
        } else {
            nums1[k] = arr2[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < m) {
        nums1[k] = arr1[i];
        i++;
        k++;
    }
    
    while (j < n) {
        nums1[k] = arr2[j];
        j++;
        k++;
    }
}

}  // namespace easy
}  // namespace leetcode