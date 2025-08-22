#include "median_of_two_sorted_arrays.h"
#include <algorithm>
#include <queue>

namespace leetcode {
namespace hard {

double MedianOfTwoSortedArrays::findMedianMerge(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> merged;
    merged.reserve(nums1.size() + nums2.size());
    
    int i = 0, j = 0;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] <= nums2[j]) {
            merged.push_back(nums1[i++]);
        } else {
            merged.push_back(nums2[j++]);
        }
    }
    
    while (i < nums1.size()) {
        merged.push_back(nums1[i++]);
    }
    
    while (j < nums2.size()) {
        merged.push_back(nums2[j++]);
    }
    
    int n = merged.size();
    if (n % 2 == 0) {
        return (merged[n/2 - 1] + merged[n/2]) / 2.0;
    } else {
        return merged[n/2];
    }
}

double MedianOfTwoSortedArrays::findMedianBinarySearch(std::vector<int>& nums1, std::vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return findMedianBinarySearch(nums2, nums1);
    }
    
    int m = nums1.size();
    int n = nums2.size();
    int low = 0, high = m;
    
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;
        
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
        
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];
        
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((m + n) % 2 == 0) {
                return (std::max(maxLeftX, maxLeftY) + std::min(minRightX, minRightY)) / 2.0;
            } else {
                return std::max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    
    return 0.0;
}

double MedianOfTwoSortedArrays::findMedianTwoPointers(std::vector<int>& nums1, std::vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    int total = m + n;
    int mid1 = (total - 1) / 2;
    int mid2 = total / 2;
    
    int i = 0, j = 0, count = 0;
    int median1 = 0, median2 = 0;
    
    while (count <= mid2) {
        int current;
        
        if (i < m && (j >= n || nums1[i] <= nums2[j])) {
            current = nums1[i++];
        } else {
            current = nums2[j++];
        }
        
        if (count == mid1) median1 = current;
        if (count == mid2) median2 = current;
        
        count++;
    }
    
    if (total % 2 == 0) {
        return (median1 + median2) / 2.0;
    } else {
        return median2;
    }
}

double MedianOfTwoSortedArrays::findMedianDivideConquer(std::vector<int>& nums1, std::vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    
    if (m == 0) {
        if (n % 2 == 0) {
            return (nums2[n/2 - 1] + nums2[n/2]) / 2.0;
        } else {
            return nums2[n/2];
        }
    }
    
    if (n == 0) {
        if (m % 2 == 0) {
            return (nums1[m/2 - 1] + nums1[m/2]) / 2.0;
        } else {
            return nums1[m/2];
        }
    }
    
    return findMedianUtil(nums1, 0, m - 1, nums2, 0, n - 1);
}

double MedianOfTwoSortedArrays::findMedianUtil(std::vector<int>& nums1, int start1, int end1,
                                              std::vector<int>& nums2, int start2, int end2) {
    int len1 = end1 - start1 + 1;
    int len2 = end2 - start2 + 1;
    
    if (len1 == 0) {
        if (len2 % 2 == 0) {
            return (nums2[start2 + len2/2 - 1] + nums2[start2 + len2/2]) / 2.0;
        } else {
            return nums2[start2 + len2/2];
        }
    }
    
    if (len2 == 0) {
        if (len1 % 2 == 0) {
            return (nums1[start1 + len1/2 - 1] + nums1[start1 + len1/2]) / 2.0;
        } else {
            return nums1[start1 + len1/2];
        }
    }
    
    if (len1 == 1 && len2 == 1) {
        return (nums1[start1] + nums2[start2]) / 2.0;
    }
    
    int mid1 = start1 + (len1 - 1) / 2;
    int mid2 = start2 + (len2 - 1) / 2;
    
    if (nums1[mid1] <= nums2[mid2]) {
        if ((len1 + len2) % 2 == 0) {
            return findMedianUtil(nums1, mid1, end1, nums2, start2, mid2);
        } else {
            return findMedianUtil(nums1, mid1, end1, nums2, start2, mid2);
        }
    } else {
        if ((len1 + len2) % 2 == 0) {
            return findMedianUtil(nums1, start1, mid1, nums2, mid2, end2);
        } else {
            return findMedianUtil(nums1, start1, mid1, nums2, mid2, end2);
        }
    }
}

double MedianOfTwoSortedArrays::findMedianKthElement(std::vector<int>& nums1, std::vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    int total = m + n;
    
    if (total % 2 == 1) {
        return findKthElement(nums1, 0, nums2, 0, total / 2 + 1);
    } else {
        double left = findKthElement(nums1, 0, nums2, 0, total / 2);
        double right = findKthElement(nums1, 0, nums2, 0, total / 2 + 1);
        return (left + right) / 2.0;
    }
}

int MedianOfTwoSortedArrays::findKthElement(std::vector<int>& nums1, int start1,
                                           std::vector<int>& nums2, int start2, int k) {
    if (start1 >= nums1.size()) {
        return nums2[start2 + k - 1];
    }
    if (start2 >= nums2.size()) {
        return nums1[start1 + k - 1];
    }
    if (k == 1) {
        return std::min(nums1[start1], nums2[start2]);
    }
    
    int mid1 = INT_MAX, mid2 = INT_MAX;
    if (start1 + k/2 - 1 < nums1.size()) {
        mid1 = nums1[start1 + k/2 - 1];
    }
    if (start2 + k/2 - 1 < nums2.size()) {
        mid2 = nums2[start2 + k/2 - 1];
    }
    
    if (mid1 < mid2) {
        return findKthElement(nums1, start1 + k/2, nums2, start2, k - k/2);
    } else {
        return findKthElement(nums1, start1, nums2, start2 + k/2, k - k/2);
    }
}

double MedianOfTwoSortedArrays::findMedianHeap(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
    auto addNum = [&](int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    };
    
    for (int num : nums1) {
        addNum(num);
    }
    for (int num : nums2) {
        addNum(num);
    }
    
    if (maxHeap.size() == minHeap.size()) {
        return (maxHeap.top() + minHeap.top()) / 2.0;
    } else {
        return maxHeap.top();
    }
}

}
}