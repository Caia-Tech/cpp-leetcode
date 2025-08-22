#include "top_k_frequent_elements.h"
#include <algorithm>
#include <climits>

namespace leetcode {
namespace medium {

// Approach 1: Min-Heap (Priority Queue) - Optimal Space
std::vector<int> TopKFrequentElements::topKFrequent(std::vector<int>& nums, int k) {
    // Count frequencies
    std::unordered_map<int, int> frequencies = countFrequencies(nums);
    
    // Min-heap to maintain k most frequent elements
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, FrequencyComparator> minHeap;
    
    for (const auto& pair : frequencies) {
        if (minHeap.size() < k) {
            minHeap.push({pair.first, pair.second});
        } else if (pair.second > minHeap.top().second) {
            minHeap.pop();
            minHeap.push({pair.first, pair.second});
        }
    }
    
    // Extract elements from heap
    std::vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }
    
    return result;
}

// Approach 2: QuickSelect on Frequencies - Average O(n)
std::vector<int> TopKFrequentElements::topKFrequentQuickSelect(std::vector<int>& nums, int k) {
    // Count frequencies
    std::unordered_map<int, int> frequencies = countFrequencies(nums);
    
    // Create frequency pairs for QuickSelect
    std::vector<std::pair<int, int>> freqPairs = createFrequencyPairs(frequencies);
    
    int n = freqPairs.size();
    
    // Use QuickSelect to find the kth largest frequency boundary
    // We want elements at indices [0, k-1] to be the k most frequent
    quickSelect(freqPairs, 0, n - 1, k);
    
    // Extract the top k elements
    std::vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(freqPairs[i].first);
    }
    
    return result;
}

// Approach 3: Bucket Sort by Frequency - Guaranteed O(n)
std::vector<int> TopKFrequentElements::topKFrequentBucketSort(std::vector<int>& nums, int k) {
    // Count frequencies
    std::unordered_map<int, int> frequencies = countFrequencies(nums);
    
    // Find maximum frequency for bucket creation
    int maxFreq = 0;
    for (const auto& pair : frequencies) {
        maxFreq = std::max(maxFreq, pair.second);
    }
    
    // Create buckets for each frequency
    std::vector<std::vector<int>> buckets = createFrequencyBuckets(frequencies, maxFreq);
    
    // Collect top k elements from highest frequency buckets
    return collectTopKFromBuckets(buckets, k);
}

// Approach 4: Max-Heap (Extract K Elements) - Intuitive Approach
std::vector<int> TopKFrequentElements::topKFrequentMaxHeap(std::vector<int>& nums, int k) {
    // Count frequencies
    std::unordered_map<int, int> frequencies = countFrequencies(nums);
    
    // Create frequency pairs and build max-heap
    std::vector<std::pair<int, int>> freqPairs = createFrequencyPairs(frequencies);
    buildMaxHeap(freqPairs);
    
    // Extract k most frequent elements
    std::vector<int> result;
    int heapSize = freqPairs.size();
    
    for (int i = 0; i < k; i++) {
        std::pair<int, int> maxElement = extractMax(freqPairs, heapSize);
        result.push_back(maxElement.first);
    }
    
    return result;
}

// Approach 5: Sorting by Frequency - Baseline Implementation
std::vector<int> TopKFrequentElements::topKFrequentSort(std::vector<int>& nums, int k) {
    // Count frequencies
    std::unordered_map<int, int> frequencies = countFrequencies(nums);
    
    // Create frequency pairs and sort by frequency (descending)
    std::vector<std::pair<int, int>> freqPairs = createFrequencyPairs(frequencies);
    
    std::sort(freqPairs.begin(), freqPairs.end(), 
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second; // Higher frequency first
              });
    
    // Extract top k elements
    std::vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(freqPairs[i].first);
    }
    
    return result;
}

// Approach 6: Counting Sort + Linear Scan - Constrained Optimal
std::vector<int> TopKFrequentElements::topKFrequentCountingSort(std::vector<int>& nums, int k) {
    if (nums.empty()) return {};
    
    // Find range for counting sort
    int minVal = *std::min_element(nums.begin(), nums.end());
    int maxVal = *std::max_element(nums.begin(), nums.end());
    int range = maxVal - minVal + 1;
    
    // Use counting sort to count frequencies
    std::vector<int> counts(range, 0);
    for (int num : nums) {
        counts[num - minVal]++;
    }
    
    // Create frequency pairs from counts
    std::vector<std::pair<int, int>> freqPairs = getFrequencyPairsFromCounting(counts, minVal);
    
    // Sort by frequency and take top k
    std::sort(freqPairs.begin(), freqPairs.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second; // Higher frequency first
              });
    
    std::vector<int> result;
    for (int i = 0; i < k && i < freqPairs.size(); i++) {
        result.push_back(freqPairs[i].first);
    }
    
    return result;
}

// Helper function implementations

int TopKFrequentElements::quickSelect(std::vector<std::pair<int, int>>& freqPairs, int left, int right, int k) {
    if (left == right) {
        return left;
    }
    
    // Randomly choose pivot and partition
    int pivotIndex = randomPartition(freqPairs, left, right);
    
    // After partitioning, elements at [left, pivotIndex-1] have frequency >= pivot frequency
    // Element at pivotIndex has the pivot frequency
    // Elements at [pivotIndex+1, right] have frequency < pivot frequency
    
    int numLargerOrEqual = pivotIndex - left + 1;
    
    if (numLargerOrEqual == k) {
        return pivotIndex;
    } else if (numLargerOrEqual > k) {
        // kth element is among higher frequency elements (left side)
        return quickSelect(freqPairs, left, pivotIndex - 1, k);
    } else {
        // kth element is among lower frequency elements (right side)
        return quickSelect(freqPairs, pivotIndex + 1, right, k - numLargerOrEqual);
    }
}

int TopKFrequentElements::partition(std::vector<std::pair<int, int>>& freqPairs, int left, int right, int pivotIndex) {
    int pivotFreq = freqPairs[pivotIndex].second;
    
    // Move pivot to end
    swap(freqPairs, pivotIndex, right);
    
    int storeIndex = left;
    
    // Partition: elements with frequency >= pivot go to left side
    for (int i = left; i < right; i++) {
        if (freqPairs[i].second >= pivotFreq) {
            swap(freqPairs, i, storeIndex);
            storeIndex++;
        }
    }
    
    // Move pivot to its final position
    swap(freqPairs, storeIndex, right);
    return storeIndex;
}

int TopKFrequentElements::randomPartition(std::vector<std::pair<int, int>>& freqPairs, int left, int right) {
    int randomIdx = getRandomIndex(left, right);
    swap(freqPairs, randomIdx, right);
    return partition(freqPairs, left, right, right);
}

void TopKFrequentElements::swap(std::vector<std::pair<int, int>>& freqPairs, int i, int j) {
    std::swap(freqPairs[i], freqPairs[j]);
}

int TopKFrequentElements::getRandomIndex(int left, int right) {
    std::uniform_int_distribution<int> dist(left, right);
    return dist(rng);
}

std::vector<std::vector<int>> TopKFrequentElements::createFrequencyBuckets(
    const std::unordered_map<int, int>& frequencies, int maxFreq) {
    
    std::vector<std::vector<int>> buckets(maxFreq + 1);
    
    for (const auto& pair : frequencies) {
        buckets[pair.second].push_back(pair.first);
    }
    
    return buckets;
}

std::vector<int> TopKFrequentElements::collectTopKFromBuckets(
    const std::vector<std::vector<int>>& buckets, int k) {
    
    std::vector<int> result;
    
    // Iterate from highest frequency to lowest
    for (int freq = buckets.size() - 1; freq >= 0 && result.size() < k; freq--) {
        for (int element : buckets[freq]) {
            if (result.size() < k) {
                result.push_back(element);
            } else {
                break;
            }
        }
    }
    
    return result;
}

void TopKFrequentElements::buildMaxHeap(std::vector<std::pair<int, int>>& freqPairs) {
    int n = freqPairs.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(freqPairs, n, i);
    }
}

void TopKFrequentElements::heapify(std::vector<std::pair<int, int>>& freqPairs, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && freqPairs[left].second > freqPairs[largest].second) {
        largest = left;
    }
    
    if (right < n && freqPairs[right].second > freqPairs[largest].second) {
        largest = right;
    }
    
    if (largest != i) {
        swap(freqPairs, i, largest);
        heapify(freqPairs, n, largest);
    }
}

std::pair<int, int> TopKFrequentElements::extractMax(std::vector<std::pair<int, int>>& freqPairs, int& heapSize) {
    if (heapSize <= 0) return {0, 0};
    
    std::pair<int, int> max = freqPairs[0];
    freqPairs[0] = freqPairs[heapSize - 1];
    heapSize--;
    heapify(freqPairs, heapSize, 0);
    
    return max;
}

std::unordered_map<int, int> TopKFrequentElements::countFrequencies(const std::vector<int>& nums) {
    std::unordered_map<int, int> frequencies;
    for (int num : nums) {
        frequencies[num]++;
    }
    return frequencies;
}

std::vector<std::pair<int, int>> TopKFrequentElements::createFrequencyPairs(
    const std::unordered_map<int, int>& frequencies) {
    
    std::vector<std::pair<int, int>> pairs;
    for (const auto& pair : frequencies) {
        pairs.push_back({pair.first, pair.second});
    }
    return pairs;
}

std::vector<int> TopKFrequentElements::countingSort(const std::vector<int>& nums, int minVal, int maxVal) {
    int range = maxVal - minVal + 1;
    std::vector<int> counts(range, 0);
    
    for (int num : nums) {
        counts[num - minVal]++;
    }
    
    return counts;
}

std::vector<std::pair<int, int>> TopKFrequentElements::getFrequencyPairsFromCounting(
    const std::vector<int>& counts, int minVal) {
    
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] > 0) {
            pairs.push_back({i + minVal, counts[i]});
        }
    }
    return pairs;
}

void TopKFrequentElements::reverseVector(std::vector<int>& vec) {
    std::reverse(vec.begin(), vec.end());
}

}
}