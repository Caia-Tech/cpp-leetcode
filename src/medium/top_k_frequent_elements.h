#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <random>

namespace leetcode {
namespace medium {

/**
 * Problem 347: Top K Frequent Elements
 * 
 * Given an integer array nums and an integer k, return the k most frequent elements.
 * You may return the answer in any order.
 * 
 * Follow up: Your algorithm's time complexity must be better than O(n log n), 
 * where n is the array's size.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 * - k is in the range [1, the number of unique elements in the array]
 * - It is guaranteed that the answer is unique.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class TopKFrequentElements {
public:
    /**
     * Approach 1: Min-Heap (Priority Queue) - Optimal Space
     * 
     * Use frequency map + min-heap of size k to track the k most frequent elements.
     * 
     * Reasoning: This is the most space-efficient approach. First count frequencies
     * in O(n) time using hash map. Then maintain a min-heap of size k containing
     * the k most frequent elements seen so far. For each element, if heap size < k,
     * add element. If element frequency > heap top frequency, remove top and add
     * element. This keeps exactly k elements in heap with the kth most frequent
     * at the top. Optimal when k << n, uses only O(k) extra space for heap.
     * 
     * Time Complexity: O(n log k) - count frequencies O(n), heap operations O(log k) for n elements
     * Space Complexity: O(n + k) - hash map O(n), heap O(k)
     * 
     * Best when: k is small relative to n, need space efficiency, follow-up requirement
     * Worst when: k approaches n, simple sorting would be faster
     */
    std::vector<int> topKFrequent(std::vector<int>& nums, int k);

    /**
     * Approach 2: QuickSelect on Frequencies - Average O(n)
     * 
     * Count frequencies, then use QuickSelect on unique elements by frequency to find kth boundary.
     * 
     * Reasoning: After counting frequencies, we have a selection problem: find the
     * k elements with highest frequencies. This is perfect for QuickSelect, the
     * same algorithm used for kth largest element. Create array of unique elements,
     * use frequencies for comparison, and partition until we find the k most frequent.
     * Expected O(n) time complexity makes this theoretically optimal and satisfies
     * the follow-up requirement. Randomization ensures good average case performance.
     * 
     * Time Complexity: O(n) average case, O(n²) worst case
     * Space Complexity: O(n) - frequency map and unique elements array
     * 
     * Best when: Need guaranteed better than O(n log n), k varies widely, optimal average time
     * Worst when: Worst-case guarantees needed, prefer predictable performance
     */
    std::vector<int> topKFrequentQuickSelect(std::vector<int>& nums, int k);

    /**
     * Approach 3: Bucket Sort by Frequency - Guaranteed O(n)
     * 
     * Create buckets for each possible frequency (1 to n), then collect k most frequent.
     * 
     * Reasoning: Since frequency can only range from 1 to n, we can use bucket sort
     * for guaranteed linear time. After counting frequencies, create n+1 buckets
     * where bucket[i] contains all elements with frequency i. Then iterate from
     * highest frequency (n) down to 1, collecting elements until we have k elements.
     * This guarantees O(n) time complexity and is deterministic, satisfying the
     * follow-up requirement without randomization dependency.
     * 
     * Time Complexity: O(n) - guaranteed linear time
     * Space Complexity: O(n) - frequency map and buckets
     * 
     * Best when: Need guaranteed linear time, deterministic algorithm, educational bucket sort
     * Worst when: Space usage concerns with sparse frequencies, simple cases
     */
    std::vector<int> topKFrequentBucketSort(std::vector<int>& nums, int k);

    /**
     * Approach 4: Max-Heap (Extract K Elements) - Intuitive Approach
     * 
     * Build max-heap from all elements by frequency, then extract k most frequent.
     * 
     * Reasoning: Straightforward approach using max-heap. After counting frequencies,
     * create max-heap containing all unique elements ordered by frequency. Extract
     * k elements from heap to get result. While not optimal (O(n log n) for heap
     * construction), it's intuitive and demonstrates heap usage. Could be optimized
     * to heapify in O(n) then extract k elements in O(k log n). Simple to understand
     * and implement correctly.
     * 
     * Time Complexity: O(n log n) - heap construction dominates
     * Space Complexity: O(n) - frequency map and heap
     * 
     * Best when: Simplicity preferred, small to medium inputs, educational purposes
     * Worst when: Need to satisfy follow-up requirement, very large inputs
     */
    std::vector<int> topKFrequentMaxHeap(std::vector<int>& nums, int k);

    /**
     * Approach 5: Sorting by Frequency - Baseline Implementation
     * 
     * Count frequencies, sort all unique elements by frequency, take top k.
     * 
     * Reasoning: Simplest conceptual approach. Count frequencies, create pairs of
     * (element, frequency), sort by frequency in descending order, take first k
     * elements. While this violates the follow-up requirement (O(n log n) time),
     * it serves as a clear baseline for correctness verification. Easy to understand
     * and implement, useful for small inputs or when simplicity is prioritized
     * over optimal complexity.
     * 
     * Time Complexity: O(n log n) - sorting dominates
     * Space Complexity: O(n) - frequency pairs
     * 
     * Best when: Simplicity over optimization, baseline implementation, small inputs
     * Worst when: Need to satisfy follow-up requirement, performance critical
     */
    std::vector<int> topKFrequentSort(std::vector<int>& nums, int k);

    /**
     * Approach 6: Counting Sort + Linear Scan - Constrained Optimal
     * 
     * Use counting sort when element range is small, then find k most frequent.
     * 
     * Reasoning: When element values have limited range (as in constraints:
     * -10^4 to 10^4), counting sort can be used for O(n + range) performance.
     * Instead of using hash map for frequencies, use array indexing for direct
     * access. After counting, create frequency-element pairs and use bucket sort
     * or simple iteration to find top k. This approach showcases when problem
     * constraints can enable better algorithms than general solutions.
     * 
     * Time Complexity: O(n + range) where range = 2×10^4 + 1
     * Space Complexity: O(range) - counting array
     * 
     * Best when: Element range is small and bounded, constraint-specific optimization
     * Worst when: Large or unbounded element ranges, general-purpose solution needed
     */
    std::vector<int> topKFrequentCountingSort(std::vector<int>& nums, int k);

private:
    // Helper functions for QuickSelect approach
    int quickSelect(std::vector<std::pair<int, int>>& freqPairs, int left, int right, int k);
    int partition(std::vector<std::pair<int, int>>& freqPairs, int left, int right, int pivotIndex);
    int randomPartition(std::vector<std::pair<int, int>>& freqPairs, int left, int right);
    void swap(std::vector<std::pair<int, int>>& freqPairs, int i, int j);
    int getRandomIndex(int left, int right);
    
    // Helper functions for Bucket Sort approach
    std::vector<std::vector<int>> createFrequencyBuckets(const std::unordered_map<int, int>& frequencies, int maxFreq);
    std::vector<int> collectTopKFromBuckets(const std::vector<std::vector<int>>& buckets, int k);
    
    // Helper functions for Max-Heap approach
    void buildMaxHeap(std::vector<std::pair<int, int>>& freqPairs);
    void heapify(std::vector<std::pair<int, int>>& freqPairs, int n, int i);
    std::pair<int, int> extractMax(std::vector<std::pair<int, int>>& freqPairs, int& heapSize);
    
    // Helper functions for general use
    std::unordered_map<int, int> countFrequencies(const std::vector<int>& nums);
    std::vector<std::pair<int, int>> createFrequencyPairs(const std::unordered_map<int, int>& frequencies);
    
    // Helper functions for Counting Sort approach
    std::vector<int> countingSort(const std::vector<int>& nums, int minVal, int maxVal);
    std::vector<std::pair<int, int>> getFrequencyPairsFromCounting(const std::vector<int>& counts, int minVal);
    
    // Utility functions
    void reverseVector(std::vector<int>& vec);
    
    // Random number generator for randomized algorithms
    std::mt19937 rng{std::random_device{}()};
    
    // Comparator for frequency-based sorting/heaping
    struct FrequencyComparator {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second; // Min-heap: larger frequencies have lower priority (smaller freqs stay at top)
        }
    };
    
    struct MaxFrequencyComparator {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second; // Max-heap: larger frequencies have higher priority (smaller freqs have lower priority)
        }
    };
};

}
}