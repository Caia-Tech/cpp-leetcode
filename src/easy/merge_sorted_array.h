#pragma once

#include <vector>
#include <algorithm>
#include <queue>

namespace leetcode {
namespace easy {

/**
 * Problem 88: Merge Sorted Array
 * 
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, 
 * and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
 * 
 * Merge nums1 and nums2 into a single array sorted in non-decreasing order.
 * 
 * The final sorted array should not be returned by the function, but instead be stored 
 * inside the array nums1. To accommodate this, nums1 has a length of m + n, where the 
 * first m elements denote the elements that should be merged, and the last n elements 
 * are set to 0 and should be ignored. nums2 has a length of n.
 * 
 * Constraints:
 * - nums1.length == m + n
 * - nums2.length == n
 * - 0 <= m, n <= 200
 * - 1 <= m + n <= 200
 * - -10^9 <= nums1[i], nums2[j] <= 10^9
 * 
 * Follow up: Can you come up with an algorithm that runs in O(m + n) time?
 */
class MergeSortedArray {
public:
    /**
     * Approach 1: Three Pointers (Backward) - Optimal
     * 
     * Merge arrays from the end to avoid overwriting.
     * 
     * Reasoning: This is the optimal in-place solution. Since nums1 has extra
     * space at the end, we can merge from right to left. Use three pointers:
     * i for nums1's last valid element, j for nums2's last element, and k for
     * current position to fill. Compare nums1[i] and nums2[j], place larger
     * element at nums1[k], and decrement corresponding pointers. This avoids
     * overwriting unprocessed elements.
     * 
     * Time Complexity: O(m + n) - single pass through both arrays
     * Space Complexity: O(1) - only using pointer variables
     * 
     * Best when: In-place solution required, optimal performance
     * Worst when: Never - this is the standard optimal solution
     */
    void mergeThreePointers(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

    /**
     * Approach 2: Merge and Sort
     * 
     * Copy nums2 to nums1 and sort the entire array.
     * 
     * Reasoning: Simplest approach - copy all elements from nums2 to the end
     * of nums1, then sort the entire array. While this doesn't leverage the
     * fact that inputs are already sorted, it's straightforward and reliable.
     * Uses standard library sort which is highly optimized. Good baseline
     * for correctness checking.
     * 
     * Time Complexity: O((m + n) log(m + n)) - sorting dominates
     * Space Complexity: O(1) - in-place sort
     * 
     * Best when: Simplicity over efficiency, small arrays
     * Worst when: Need to leverage sorted property for efficiency
     */
    void mergeSortThenMerge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

    /**
     * Approach 3: Extra Array with Two Pointers
     * 
     * Use extra array to merge, then copy back.
     * 
     * Reasoning: Classic merge algorithm from merge sort. Create temporary
     * array, use two pointers to merge nums1 and nums2 into temp array,
     * then copy back to nums1. This is easier to understand than backward
     * merging and follows standard merge pattern. Uses extra space but
     * achieves optimal time complexity.
     * 
     * Time Complexity: O(m + n) - single pass through both arrays
     * Space Complexity: O(m + n) - temporary array
     * 
     * Best when: Clarity over space efficiency, teaching merge algorithm
     * Worst when: Space is constrained, need in-place solution
     */
    void mergeExtraArray(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

    /**
     * Approach 4: Insertion Sort Style
     * 
     * Insert each element from nums2 into correct position in nums1.
     * 
     * Reasoning: For each element in nums2, find its correct position in
     * nums1 and insert it by shifting elements. This is like insertion sort
     * but inserting from one array into another. While O(mn) worst case,
     * it can be efficient when nums2 is small or elements are already
     * mostly in order. Demonstrates insertion-based merging.
     * 
     * Time Complexity: O(m * n) - for each nums2 element, scan nums1
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: nums2 is very small, educational purposes
     * Worst when: Arrays are large, optimal performance needed
     */
    void mergeInsertionStyle(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

    /**
     * Approach 5: Priority Queue (Heap)
     * 
     * Use min-heap to merge arrays in sorted order.
     * 
     * Reasoning: Push all elements into min-heap, then pop in sorted order.
     * This is overkill for two sorted arrays but demonstrates heap usage
     * and generalizes to k-way merge problems. The heap maintains the
     * ordering property, ensuring we always get the next smallest element.
     * More complex than needed but educationally valuable.
     * 
     * Time Complexity: O((m + n) log(m + n)) - heap operations
     * Space Complexity: O(m + n) - heap storage
     * 
     * Best when: Generalizing to k-way merge, demonstrating heap usage
     * Worst when: Two-array merge is all that's needed
     */
    void mergePriorityQueue(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

    /**
     * Approach 6: Two-Pass with Separate Arrays
     * 
     * Separate arrays, merge using standard merge, copy back.
     * 
     * Reasoning: Create separate copies of the valid portions of nums1 and
     * nums2, then use standard two-pointer merge algorithm to combine them
     * back into nums1. This clearly separates the "extraction" phase from
     * the "merge" phase, making the algorithm easier to understand and debug.
     * Uses more space but provides clear algorithmic structure.
     * 
     * Time Complexity: O(m + n) - linear passes for copy and merge
     * Space Complexity: O(m + n) - copies of both arrays
     * 
     * Best when: Clarity and modularity important, debugging
     * Worst when: Space efficiency critical
     */
    void mergeTwoPass(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

private:
    // Helper for insertion style approach
    void insertAt(std::vector<int>& arr, int pos, int value, int& size);
    
    // Helper for finding insertion position
    int findInsertionPos(const std::vector<int>& arr, int value, int size);
};

}  // namespace easy
}  // namespace leetcode