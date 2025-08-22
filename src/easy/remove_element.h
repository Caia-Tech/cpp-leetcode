#pragma once

#include <vector>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 27: Remove Element
 * 
 * Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. 
 * The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.
 * 
 * Consider the number of elements in nums which are not equal to val be k, to get accepted, you need to do the following things:
 * - Change the array nums such that the first k elements of nums contain the elements which are not equal to val. 
 *   The remaining elements of nums are not important as well as the size of nums.
 * - Return k.
 * 
 * Constraints:
 * - 0 <= nums.length <= 100
 * - 0 <= nums[i] <= 50
 * - 0 <= val <= 100
 */
class RemoveElement {
public:
    /**
     * Approach 1: Two Pointers (Fast-Slow)
     * 
     * Use two pointers to track write position and read position.
     * 
     * Reasoning: This is the standard two-pointer approach. Fast pointer scans
     * through the array, slow pointer tracks where to write the next valid element.
     * When fast pointer finds an element != val, copy it to slow pointer position
     * and advance both pointers. When fast pointer finds val, only advance fast
     * pointer. This maintains all non-val elements at the beginning of array.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only using two pointers
     * 
     * Best when: Standard interview solution, maintains relative order
     * Worst when: Many elements equal val (unnecessary copying)
     */
    int removeElementTwoPointers(std::vector<int>& nums, int val);

    /**
     * Approach 2: Two Pointers (Start-End)
     * 
     * Use pointers from both ends, swap with end when target found.
     * 
     * Reasoning: Optimize for cases where many elements equal val. When we find
     * an element equal to val, instead of skipping it, swap it with the element
     * at the end and shrink the array size. This avoids copying many elements
     * when val is frequent. However, this doesn't preserve relative order of
     * remaining elements.
     * 
     * Time Complexity: O(n) - each element processed at most once
     * Space Complexity: O(1) - only using two pointers
     * 
     * Best when: Many occurrences of val, order preservation not required
     * Worst when: Need to maintain relative order of remaining elements
     */
    int removeElementStartEnd(std::vector<int>& nums, int val);

    /**
     * Approach 3: Overwrite in Place
     * 
     * Overwrite array by shifting valid elements forward.
     * 
     * Reasoning: Maintain a write index for the next valid element position.
     * Scan through array and when we find a valid element (not equal to val),
     * write it to the current write position and increment write index.
     * This is conceptually similar to two-pointers but focuses on the write
     * operation rather than pointer movement.
     * 
     * Time Complexity: O(n) - single pass through array
     * Space Complexity: O(1) - only using write index variable
     * 
     * Best when: Write-index concept is more intuitive
     * Worst when: Two-pointer abstraction is clearer
     */
    int removeElementOverwrite(std::vector<int>& nums, int val);

    /**
     * Approach 4: STL remove() Function
     * 
     * Use STL's remove function to eliminate target elements.
     * 
     * Reasoning: C++ STL provides std::remove() which moves all elements not
     * equal to val to the front and returns iterator to new end. This is
     * essentially the same algorithm as two-pointers but implemented in STL.
     * While concise, it may not be allowed in interviews where manual
     * implementation is expected.
     * 
     * Time Complexity: O(n) - STL remove implementation
     * Space Complexity: O(1) - in-place operation
     * 
     * Best when: STL usage is allowed, need concise implementation
     * Worst when: Need to implement logic manually, interview restrictions
     */
    int removeElementSTL(std::vector<int>& nums, int val);

    /**
     * Approach 5: Backward Iteration with Erase
     * 
     * Iterate backwards and erase elements equal to val.
     * 
     * Reasoning: Iterate from end to beginning and use vector's erase() function
     * to remove elements equal to val. Backward iteration avoids index shifting
     * issues when erasing. However, vector::erase() is O(n) for each operation,
     * making this approach O(n²) in worst case. Not efficient but demonstrates
     * erase usage.
     * 
     * Time Complexity: O(n²) - O(n) iterations × O(n) erase operations
     * Space Complexity: O(1) - no additional space besides iterator
     * 
     * Best when: Educational purposes, understanding vector::erase behavior
     * Worst when: Performance is important due to quadratic complexity
     */
    int removeElementErase(std::vector<int>& nums, int val);

    /**
     * Approach 6: Counting and Reconstruction
     * 
     * Count valid elements, then reconstruct array.
     * 
     * Reasoning: First pass counts how many elements are not equal to val.
     * Second pass copies only the valid elements to the beginning of array.
     * While this requires two passes, it makes the counting explicit and
     * separates concerns. Less efficient than single-pass solutions but
     * easier to understand and debug.
     * 
     * Time Complexity: O(n) - two passes through array
     * Space Complexity: O(1) - only using counter variables
     * 
     * Best when: Two-pass approach is more intuitive, need explicit counting
     * Worst when: Single-pass efficiency is preferred
     */
    int removeElementCounting(std::vector<int>& nums, int val);

private:
    // No private helper methods needed for this problem
};

}
}