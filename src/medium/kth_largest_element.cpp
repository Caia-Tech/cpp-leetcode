#include "kth_largest_element.h"
#include <algorithm>
#include <unordered_map>

namespace leetcode {
namespace medium {

// Approach 1: Min-Heap (Priority Queue)
int KthLargestElement::findKthLargest(std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // Min-heap
    
    for (int num : nums) {
        if (minHeap.size() < k) {
            minHeap.push(num);
        } else if (num > minHeap.top()) {
            minHeap.pop();
            minHeap.push(num);
        }
    }
    
    return minHeap.top();
}

// Approach 2: QuickSelect (Randomized)
int KthLargestElement::findKthLargestQuickSelect(std::vector<int>& nums, int k) {
    int n = nums.size();
    return quickSelect(nums, 0, n - 1, k);
}

int KthLargestElement::quickSelect(std::vector<int>& nums, int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }
    
    // Choose random pivot and partition
    int pivotIndex = randomPartition(nums, left, right);
    
    // After partitioning, elements at indices [left, pivotIndex-1] are >= pivot
    // Element at pivotIndex is the pivot
    // Elements at indices [pivotIndex+1, right] are < pivot
    
    // Number of elements >= pivot (including pivot itself)
    int numLargerOrEqual = pivotIndex - left + 1;
    
    if (numLargerOrEqual == k) {
        return nums[pivotIndex];
    } else if (numLargerOrEqual > k) {
        // kth largest is among elements >= pivot (to the left of pivot)
        return quickSelect(nums, left, pivotIndex - 1, k);
    } else {
        // kth largest is among elements < pivot (to the right of pivot)
        return quickSelect(nums, pivotIndex + 1, right, k - numLargerOrEqual);
    }
}

int KthLargestElement::randomPartition(std::vector<int>& nums, int left, int right) {
    int randomIdx = getRandomIndex(left, right);
    swap(nums, randomIdx, right);
    return partition(nums, left, right, right);
}

int KthLargestElement::partition(std::vector<int>& nums, int left, int right, int pivotIndex) {
    int pivotValue = nums[pivotIndex];
    
    // Move pivot to end
    swap(nums, pivotIndex, right);
    
    int storeIndex = left;
    
    // Partition: elements >= pivot go to left side
    for (int i = left; i < right; i++) {
        if (nums[i] >= pivotValue) {
            swap(nums, i, storeIndex);
            storeIndex++;
        }
    }
    
    // Move pivot to its final position
    swap(nums, storeIndex, right);
    return storeIndex;
}

// Approach 3: Median-of-Medians QuickSelect
int KthLargestElement::findKthLargestMedianOfMedians(std::vector<int>& nums, int k) {
    int n = nums.size();
    return medianOfMedians(nums, 0, n - 1, k);
}

int KthLargestElement::medianOfMedians(std::vector<int>& nums, int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }
    
    // Find median-of-medians as pivot
    int pivotValue = findMedianOfMedians(nums, left, right);
    
    // Find pivot index
    int pivotIndex = left;
    for (int i = left; i <= right; i++) {
        if (nums[i] == pivotValue) {
            pivotIndex = i;
            break;
        }
    }
    
    // Partition around median-of-medians
    pivotIndex = partition(nums, left, right, pivotIndex);
    
    // Number of elements >= pivot (including pivot itself)
    int numLargerOrEqual = pivotIndex - left + 1;
    
    if (numLargerOrEqual == k) {
        return nums[pivotIndex];
    } else if (numLargerOrEqual > k) {
        return medianOfMedians(nums, left, pivotIndex - 1, k);
    } else {
        return medianOfMedians(nums, pivotIndex + 1, right, k - numLargerOrEqual);
    }
}

int KthLargestElement::findMedianOfMedians(std::vector<int>& nums, int left, int right) {
    int n = right - left + 1;
    
    if (n <= 5) {
        return findMedian(nums, left, right);
    }
    
    // Divide into groups of 5 and find medians
    std::vector<int> medians;
    for (int i = left; i <= right; i += 5) {
        int groupRight = std::min(i + 4, right);
        int median = findMedian(nums, i, groupRight);
        medians.push_back(median);
    }
    
    // Recursively find median of medians
    int k = (medians.size() + 1) / 2;
    return medianOfMedians(medians, 0, medians.size() - 1, k);
}

int KthLargestElement::findMedian(std::vector<int>& nums, int left, int right) {
    std::sort(nums.begin() + left, nums.begin() + right + 1);
    return nums[left + (right - left) / 2];
}

// Approach 4: Counting Sort
int KthLargestElement::findKthLargestCountingSort(std::vector<int>& nums, int k) {
    // Find range of values
    int minVal = *std::min_element(nums.begin(), nums.end());
    int maxVal = *std::max_element(nums.begin(), nums.end());
    int range = maxVal - minVal + 1;
    
    // Count frequencies
    std::vector<int> count(range, 0);
    for (int num : nums) {
        count[num - minVal]++;
    }
    
    // Find kth largest by iterating from largest to smallest
    int seen = 0;
    for (int i = range - 1; i >= 0; i--) {
        seen += count[i];
        if (seen >= k) {
            return i + minVal;
        }
    }
    
    return -1; // Should never reach here
}

// Approach 5: Max-Heap (Full Heapify)
int KthLargestElement::findKthLargestMaxHeap(std::vector<int>& nums, int k) {
    int n = nums.size();
    
    // Build max heap
    buildMaxHeap(nums);
    
    // Extract k-1 maximum elements
    int heapSize = n;
    for (int i = 0; i < k - 1; i++) {
        extractMax(nums, heapSize);
        heapSize--;
    }
    
    // The root is now the kth largest element
    return nums[0];
}

void KthLargestElement::buildMaxHeap(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(nums, n, i);
    }
}

void KthLargestElement::heapify(std::vector<int>& nums, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && nums[left] > nums[largest]) {
        largest = left;
    }
    
    if (right < n && nums[right] > nums[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(nums, i, largest);
        heapify(nums, n, largest);
    }
}

int KthLargestElement::extractMax(std::vector<int>& nums, int heapSize) {
    if (heapSize <= 0) return -1;
    
    int max = nums[0];
    nums[0] = nums[heapSize - 1];
    heapify(nums, heapSize - 1, 0);
    
    return max;
}

// Approach 6: Partial Sort (STL nth_element)
int KthLargestElement::findKthLargestSTL(std::vector<int>& nums, int k) {
    int n = nums.size();
    
    // nth_element places the (n-k)th element (0-indexed) in its correct position
    // Elements after this position are larger than or equal to it
    std::nth_element(nums.begin(), nums.begin() + n - k, nums.end());
    
    return nums[n - k];
}

// Utility function implementations
void KthLargestElement::swap(std::vector<int>& nums, int i, int j) {
    std::swap(nums[i], nums[j]);
}

int KthLargestElement::getRandomIndex(int left, int right) {
    std::uniform_int_distribution<int> dist(left, right);
    return dist(rng);
}

}
}