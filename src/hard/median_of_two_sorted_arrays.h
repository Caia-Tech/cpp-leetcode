#pragma once

#include <vector>
#include <algorithm>
#include <climits>

namespace leetcode {
namespace hard {

/**
 * Problem 4: Median of Two Sorted Arrays
 * 
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, 
 * return the median of the two sorted arrays.
 * 
 * The overall run time complexity should be O(log (m+n)).
 * 
 * Constraints:
 * - nums1.length == m
 * - nums2.length == n
 * - 0 <= m <= 1000
 * - 0 <= n <= 1000
 * - 1 <= m + n <= 2000
 * - -10^6 <= nums1[i], nums2[i] <= 10^6
 */
class MedianOfTwoSortedArrays {
public:
    /**
     * Approach 1: Merge and Find Median
     * 
     * Merge both arrays and find the median.
     * 
     * Reasoning: The most straightforward approach - merge both sorted arrays into
     * one sorted array, then find the median at position (m+n)/2. Uses standard
     * merge technique from merge sort. While this doesn't meet the O(log(m+n))
     * requirement, it's simple to understand and implement correctly. Good baseline
     * for testing other approaches.
     * 
     * Time Complexity: O(m + n) - must process all elements for merging
     * Space Complexity: O(m + n) - storing the merged array
     * 
     * Best when: Simple implementation needed, arrays are small
     * Worst when: Need to meet O(log(m+n)) requirement or memory is constrained
     */
    double findMedianMerge(std::vector<int>& nums1, std::vector<int>& nums2);

    /**
     * Approach 2: Binary Search (Optimal)
     * 
     * Use binary search on the smaller array to find partition.
     * 
     * Reasoning: This is the optimal solution that meets the O(log(m+n)) requirement.
     * Key insight: find a partition in both arrays such that left partitions contain
     * the smaller half of all elements. Binary search on the smaller array to find
     * the correct partition point. The median is then derived from the max of left
     * partitions and min of right partitions. Extremely efficient but complex.
     * 
     * Time Complexity: O(log min(m, n)) - binary search on smaller array
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal time complexity, large arrays
     * Worst when: Implementation complexity outweighs performance gains
     */
    double findMedianBinarySearch(std::vector<int>& nums1, std::vector<int>& nums2);

    /**
     * Approach 3: Two Pointers Without Full Merge
     * 
     * Use two pointers to find median without full merge.
     * 
     * Reasoning: Optimize the merge approach by not storing the merged array.
     * Instead, use two pointers to traverse both arrays simultaneously, counting
     * elements until reaching the median position(s). Only track the elements
     * needed for median calculation. This saves space while maintaining the
     * same time complexity as full merge.
     * 
     * Time Complexity: O(m + n) - still need to traverse to median position
     * Space Complexity: O(1) - no additional array storage
     * 
     * Best when: Want space optimization over merge approach
     * Worst when: Need to meet logarithmic time requirement
     */
    double findMedianTwoPointers(std::vector<int>& nums1, std::vector<int>& nums2);

    /**
     * Approach 4: Divide and Conquer
     * 
     * Recursively find the median using divide and conquer.
     * 
     * Reasoning: Apply divide-and-conquer by eliminating half of the search space
     * in each recursive call. Compare medians of both arrays and eliminate the
     * half that cannot contain the overall median. This approach meets the
     * logarithmic time requirement and is often easier to understand than the
     * binary search partition approach, though it uses recursion stack.
     * 
     * Time Complexity: O(log(m + n)) - eliminate half elements each recursion
     * Space Complexity: O(log(m + n)) - recursion call stack
     * 
     * Best when: Recursive thinking is more intuitive than binary search
     * Worst when: Stack space is limited or iterative approach preferred
     */
    double findMedianDivideConquer(std::vector<int>& nums1, std::vector<int>& nums2);

    /**
     * Approach 5: Kth Element Method
     * 
     * Find kth smallest element where k is the median position.
     * 
     * Reasoning: Reduce the problem to finding the kth smallest element in two
     * sorted arrays, where k corresponds to median position(s). For even total
     * length, find both middle elements. This approach generalizes to any kth
     * element problem and uses binary elimination similar to divide-and-conquer
     * but with explicit k-based logic.
     * 
     * Time Complexity: O(log(m + n)) - binary elimination based on k
     * Space Complexity: O(log(m + n)) - recursion for kth element finding
     * 
     * Best when: Need to solve general kth element problem, not just median
     * Worst when: Only median is needed and simpler approaches suffice
     */
    double findMedianKthElement(std::vector<int>& nums1, std::vector<int>& nums2);

    /**
     * Approach 6: Priority Queue (Heap)
     * 
     * Use min-heap to track median elements.
     * 
     * Reasoning: This approach demonstrates heap usage but is not optimal for this
     * problem. Insert all elements into a min-heap, then extract the median element(s).
     * While conceptually simple and generalizable to unsorted arrays, it's inefficient
     * for sorted inputs since we're not leveraging the sorted property.
     * Included for completeness and comparison.
     * 
     * Time Complexity: O((m + n) log(m + n)) - heap operations for all elements
     * Space Complexity: O(m + n) - heap storage for all elements
     * 
     * Best when: Arrays are not sorted, educational heap usage
     * Worst when: Arrays are sorted (doesn't leverage this property)
     */
    double findMedianHeap(std::vector<int>& nums1, std::vector<int>& nums2);

private:
    int findKthElement(std::vector<int>& nums1, int start1, 
                       std::vector<int>& nums2, int start2, int k);
    double findMedianUtil(std::vector<int>& nums1, int start1, int end1,
                         std::vector<int>& nums2, int start2, int end2);
};

}
}