#pragma once

#include <vector>
#include <unordered_set>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 26: Remove Duplicates from Sorted Array
 * 
 * Given an integer array nums sorted in non-decreasing order, remove the duplicates 
 * in-place such that each unique element appears only once. The relative order of the 
 * elements should be kept the same. Then return the number of unique elements in nums.
 * 
 * Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:
 * - Change the array nums such that the first k elements of nums contain the unique elements 
 *   in the order they were present in nums originally. The remaining elements of nums are not important 
 *   as well as the size of nums.
 * - Return k.
 * 
 * Constraints:
 * - 1 <= nums.length <= 3 * 10^4
 * - -100 <= nums[i] <= 100
 * - nums is sorted in non-decreasing order.
 */
class RemoveDuplicatesFromSortedArray {
public:
    /**
     * Approach 1: Two Pointers (Optimal)
     * 
     * Use two pointers to track unique elements position and current scanning position.
     * 
     * Reasoning: This is the optimal solution that leverages the sorted property.
     * Since array is sorted, duplicates are adjacent. Use two pointers: slow pointer
     * tracks the position for next unique element, fast pointer scans through array.
     * When fast pointer finds a new unique element (different from previous), copy it
     * to slow pointer position and advance slow pointer. This maintains order and
     * removes duplicates in-place.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only using two pointers
     * 
     * Best when: Need optimal in-place solution, array is sorted
     * Worst when: Array is not sorted (wouldn't work correctly)
     */
    int removeDuplicatesTwoPointers(std::vector<int>& nums);

    /**
     * Approach 2: Hash Set (Not Optimal for Sorted Array)
     * 
     * Use hash set to track seen elements and rebuild array.
     * 
     * Reasoning: Use hash set to track which elements we've seen before. Scan through
     * array and only keep elements not in the set. While this works for any array
     * (sorted or unsorted), it doesn't leverage the sorted property and uses extra
     * space. Less efficient than two-pointer approach for this specific problem.
     * 
     * Time Complexity: O(n) - single pass with O(1) hash operations
     * Space Complexity: O(k) - hash set stores up to k unique elements
     * 
     * Best when: Educational purposes, need to handle unsorted arrays
     * Worst when: Array is sorted and two-pointer approach is available
     */
    int removeDuplicatesHashSet(std::vector<int>& nums);

    /**
     * Approach 3: Write Index Tracking
     * 
     * Track write position separately from read position.
     * 
     * Reasoning: Similar to two-pointer but conceptually focuses on "write index"
     * for where to place the next unique element. Read through array sequentially,
     * and whenever we find an element different from the last written element,
     * write it to the write index and increment write index. This makes the
     * "building result array" concept more explicit.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only using write index variable
     * 
     * Best when: Write/read index concept is more intuitive
     * Worst when: Two-pointer abstraction is clearer
     */
    int removeDuplicatesWriteIndex(std::vector<int>& nums);

    /**
     * Approach 4: STL unique() Function
     * 
     * Use STL's unique function to remove consecutive duplicates.
     * 
     * Reasoning: C++ STL provides std::unique() which removes consecutive duplicate
     * elements from a range. Since our array is sorted, all duplicates are consecutive.
     * Call unique() and it returns iterator to new end, then calculate the distance
     * to get count of unique elements. While concise, it may not be allowed in
     * interviews where you need to implement the logic yourself.
     * 
     * Time Complexity: O(n) - STL unique implementation
     * Space Complexity: O(1) - in-place operation
     * 
     * Best when: STL usage is allowed, need concise code
     * Worst when: Need to implement logic manually, interview restrictions
     */
    int removeDuplicatesSTL(std::vector<int>& nums);

    /**
     * Approach 5: Overwrite Duplicates
     * 
     * Scan and overwrite duplicates by shifting unique elements forward.
     * 
     * Reasoning: Instead of using two pointers, maintain a count of unique elements
     * and overwrite the array positions. When we encounter a duplicate, skip it.
     * When we encounter a unique element, place it at position determined by our
     * unique count. This approach makes the counting aspect more explicit.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only using counter variable
     * 
     * Best when: Counting approach is more intuitive
     * Worst when: Two-pointer approach is clearer
     */
    int removeDuplicatesOverwrite(std::vector<int>& nums);

    /**
     * Approach 6: Recursive Approach
     * 
     * Recursively process array sections to remove duplicates.
     * 
     * Reasoning: This demonstrates how to solve the problem recursively, though
     * it's not practical. Base case is single element (always unique). For larger
     * arrays, recursively process and merge results while removing duplicates at
     * boundaries. While educational for understanding recursion, it's inefficient
     * due to call stack overhead and doesn't improve upon iterative solutions.
     * 
     * Time Complexity: O(n) - each element processed once, but with recursion overhead
     * Space Complexity: O(log n) - recursion call stack in best case (balanced)
     * 
     * Best when: Educational purposes, demonstrating recursive thinking
     * Worst when: Performance is critical or stack space is limited
     */
    int removeDuplicatesRecursive(std::vector<int>& nums);

private:
    int removeDuplicatesHelper(std::vector<int>& nums, int start, int end);
};

}
}