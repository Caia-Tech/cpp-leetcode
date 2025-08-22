#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <random>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 215: Kth Largest Element in an Array
 * 
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * Can you solve it without sorting?
 * 
 * Constraints:
 * - 1 <= k <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class KthLargestElement {
public:
    /**
     * Approach 1: Min-Heap (Priority Queue) - Optimal Space
     * 
     * Maintain a min-heap of size k containing the k largest elements seen so far.
     * 
     * Reasoning: Key insight is we only need to track the k largest elements, not
     * sort the entire array. Use min-heap of size k where the root is the kth largest.
     * Process elements one by one: if heap size < k, add element. If element is
     * larger than heap top (current kth largest), remove top and add element.
     * This maintains exactly k largest elements with kth largest at root.
     * Optimal for cases where k << n.
     * 
     * Time Complexity: O(n log k) - process n elements, each heap operation O(log k)
     * Space Complexity: O(k) - heap stores at most k elements
     * 
     * Best when: k is small relative to n, need space efficiency
     * Worst when: k approaches n, frequent heap operations expensive
     */
    int findKthLargest(std::vector<int>& nums, int k);

    /**
     * Approach 2: QuickSelect (Randomized) - Average O(n)
     * 
     * Use randomized quickselect algorithm based on quicksort partitioning.
     * 
     * Reasoning: QuickSelect is modification of quicksort that only recurses on
     * the partition containing the target element. Choose random pivot, partition
     * array so elements >= pivot are on left. If pivot is at position k-1 from
     * right, it's our answer. Otherwise recurse on appropriate partition.
     * Randomization ensures expected O(n) performance by avoiding worst-case
     * pivot selections. This is the optimal expected time solution.
     * 
     * Time Complexity: O(n) average, O(n²) worst case
     * Space Complexity: O(1) - iterative version, O(log n) recursive
     * 
     * Best when: Need optimal average performance, k can vary widely
     * Worst when: Worst-case guarantees needed, prefer deterministic algorithms
     */
    int findKthLargestQuickSelect(std::vector<int>& nums, int k);

    /**
     * Approach 3: Median-of-Medians QuickSelect - Guaranteed O(n)
     * 
     * Use deterministic pivot selection to guarantee O(n) worst-case performance.
     * 
     * Reasoning: Standard quickselect can degrade to O(n²) with poor pivot choices.
     * Median-of-medians algorithm guarantees good pivot selection: divide array
     * into groups of 5, find median of each group, recursively find median of
     * these medians as pivot. This ensures pivot eliminates at least 30% of
     * elements, guaranteeing O(n) worst-case. While complex, demonstrates
     * theoretical computer science technique for worst-case linear selection.
     * 
     * Time Complexity: O(n) worst case - mathematically proven
     * Space Complexity: O(log n) - recursion for median finding
     * 
     * Best when: Worst-case guarantees required, educational theoretical algorithm
     * Worst when: Implementation complexity outweighs benefits, average case sufficient
     */
    int findKthLargestMedianOfMedians(std::vector<int>& nums, int k);

    /**
     * Approach 4: Counting Sort (Range-Limited)
     * 
     * Use counting sort when element range is small relative to array size.
     * 
     * Reasoning: When element values have limited range (as in constraints:
     * -10^4 to 10^4), counting sort can achieve O(n + range) performance.
     * Count frequency of each value, then iterate from largest to smallest
     * until we've seen k elements. Particularly effective when range is small
     * or when there are many duplicates. Deterministic O(n) performance when
     * range is bounded by a constant.
     * 
     * Time Complexity: O(n + range) - where range = max - min + 1
     * Space Complexity: O(range) - counting array
     * 
     * Best when: Limited value range, many duplicates, deterministic linear time needed
     * Worst when: Large value ranges, sparse distributions, memory constraints
     */
    int findKthLargestCountingSort(std::vector<int>& nums, int k);

    /**
     * Approach 5: Max-Heap (Full Heapify)
     * 
     * Build max-heap from entire array, then extract k largest elements.
     * 
     * Reasoning: Convert array to max-heap in O(n) time using heapify, then
     * extract maximum k times. Each extraction takes O(log n) time. While not
     * optimal overall, demonstrates heap applications and is straightforward
     * to implement. Useful when multiple queries for different k values are
     * expected, as heap can be reused. Also educational for understanding
     * heap operations and their applications.
     * 
     * Time Complexity: O(n + k log n) - heapify O(n), k extractions O(k log n)
     * Space Complexity: O(1) - in-place heapify
     * 
     * Best when: Multiple k queries, educational heap operations, in-place required
     * Worst when: Single query with large k, better alternatives available
     */
    int findKthLargestMaxHeap(std::vector<int>& nums, int k);

    /**
     * Approach 6: Partial Sort (STL nth_element)
     * 
     * Use standard library's nth_element for partial sorting.
     * 
     * Reasoning: STL's nth_element implements introselect (combination of
     * quickselect and heapsort) with excellent practical performance. It
     * partially sorts array so that nth element is in correct position,
     * elements before are smaller, elements after are larger. Highly optimized
     * implementation with good worst-case behavior. Demonstrates when to use
     * well-tested library functions versus custom implementations.
     * 
     * Time Complexity: O(n) average, with good worst-case behavior
     * Space Complexity: O(1) - in-place algorithm
     * 
     * Best when: Production code, proven performance needed, simplicity preferred
     * Worst when: Learning algorithms, custom requirements, avoiding STL
     */
    int findKthLargestSTL(std::vector<int>& nums, int k);

private:
    // Helper functions for QuickSelect approach
    int quickSelect(std::vector<int>& nums, int left, int right, int k);
    int partition(std::vector<int>& nums, int left, int right, int pivotIndex);
    int randomPartition(std::vector<int>& nums, int left, int right);
    
    // Helper functions for Median-of-Medians approach
    int medianOfMedians(std::vector<int>& nums, int left, int right, int k);
    int findMedianOfMedians(std::vector<int>& nums, int left, int right);
    int findMedian(std::vector<int>& nums, int left, int right);
    
    // Helper functions for Max-Heap approach
    void heapify(std::vector<int>& nums, int n, int i);
    void buildMaxHeap(std::vector<int>& nums);
    int extractMax(std::vector<int>& nums, int heapSize);
    
    // Utility functions
    void swap(std::vector<int>& nums, int i, int j);
    int getRandomIndex(int left, int right);
    
    // Random number generator for randomized algorithms
    std::mt19937 rng{std::random_device{}()};
};

}
}