#pragma once

#include <vector>
#include <unordered_set>
#include <algorithm>

namespace leetcode {
namespace hard {

/**
 * Problem 41: First Missing Positive
 * 
 * Given an unsorted integer array nums, return the smallest missing positive integer.
 * You must implement an algorithm that runs in O(n) time and uses O(1) extra space.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -2^31 <= nums[i] <= 2^31 - 1
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class FirstMissingPositive {
public:
    /**
     * Approach 1: Cyclic Sort / Index as Hash (Optimal)
     * 
     * Use array indices as hash table to mark presence of positive integers.
     * 
     * Reasoning: This is the optimal O(n) time, O(1) space solution. Key insight:
     * the first missing positive must be in range [1, n+1] where n is array length.
     * Use the array itself as a hash table: place each number x at index x-1.
     * After placement, scan array to find first index i where nums[i] != i+1.
     * This gives the first missing positive as i+1.
     * 
     * Time Complexity: O(n) - each element placed at most once
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal O(n) time and O(1) space, understand cyclic sort
     * Worst when: Array modification not allowed, need to preserve original array
     */
    int firstMissingPositiveCyclicSort(std::vector<int>& nums);

    /**
     * Approach 2: Mark Negatives as Presence Indicators
     * 
     * Use sign of numbers to indicate presence without extra space.
     * 
     * Reasoning: Modify the sign of nums[abs(nums[i])-1] to indicate that positive
     * integer abs(nums[i]) exists. First, handle negatives and zeros by replacing
     * with a sentinel value. Then use signs to mark presence. Finally, scan to
     * find first positive index, which indicates missing positive integer.
     * 
     * Time Complexity: O(n) - multiple passes through array
     * Space Complexity: O(1) - in-place sign modifications
     * 
     * Best when: Clever sign-based marking is preferred, avoid element swapping
     * Worst when: Sign manipulation logic is less intuitive than direct placement
     */
    int firstMissingPositiveSignMarking(std::vector<int>& nums);

    /**
     * Approach 3: Hash Set (Not Optimal - Space)
     * 
     * Use hash set to store all positive numbers, then find first missing.
     * 
     * Reasoning: Store all positive numbers in hash set, then check integers
     * 1, 2, 3, ... until finding one not in set. While conceptually simple
     * and easy to implement, this uses O(n) extra space which violates the
     * constraint. Included for comparison and as baseline solution.
     * 
     * Time Complexity: O(n) - single pass plus O(n) lookups in worst case
     * Space Complexity: O(n) - hash set storage (violates constraint)
     * 
     * Best when: Space constraint relaxed, need simple baseline implementation
     * Worst when: Must satisfy O(1) space requirement
     */
    int firstMissingPositiveHashSet(std::vector<int>& nums);

    /**
     * Approach 4: Sort and Scan (Not Optimal - Time)
     * 
     * Sort array then scan for first gap in positive integers.
     * 
     * Reasoning: Sort array and scan from beginning, looking for first positive
     * integer sequence gap. Skip negatives and zeros, then check if sequence
     * 1,2,3,... has any gaps. While straightforward, sorting takes O(n log n)
     * time which violates the time constraint. Useful for understanding problem.
     * 
     * Time Complexity: O(n log n) - dominated by sorting (violates constraint)
     * Space Complexity: O(1) - in-place sorting
     * 
     * Best when: Time constraint relaxed, sorting approach is intuitive
     * Worst when: Must satisfy O(n) time requirement
     */
    int firstMissingPositiveSort(std::vector<int>& nums);

    /**
     * Approach 5: Binary Search on Answer (Complex)
     * 
     * Binary search on possible answer with counting verification.
     * 
     * Reasoning: Binary search on range [1, n+1] for the answer. For each
     * candidate answer x, count how many numbers in [1, x] exist in array.
     * If count < x, then x or some smaller positive is missing. While this
     * achieves correct complexity, it's more complex than needed and has
     * higher constant factors than cyclic sort.
     * 
     * Time Complexity: O(n log n) - log n binary search iterations, each with O(n) counting
     * Space Complexity: O(1) - only using binary search variables
     * 
     * Best when: Binary search pattern practice, different algorithmic approach
     * Worst when: Simpler cyclic sort approach available
     */
    int firstMissingPositiveBinarySearch(std::vector<int>& nums);

    /**
     * Approach 6: Partition and Conquer
     * 
     * Partition array into positive/negative, then process positive part.
     * 
     * Reasoning: First partition array to separate positive numbers from
     * non-positive ones. Then apply cyclic sort technique to positive portion.
     * This makes the algorithm structure very clear: separate concerns of
     * filtering vs finding missing positive. While algorithmically sound,
     * it has more steps than direct cyclic sort.
     * 
     * Time Complexity: O(n) - partitioning + cyclic sort on positive portion
     * Space Complexity: O(1) - in-place partitioning and sorting
     * 
     * Best when: Want clear separation of positive filtering and missing detection
     * Worst when: Direct cyclic sort on entire array is simpler
     */
    int firstMissingPositivePartition(std::vector<int>& nums);

private:
    // Helper functions
    void cyclicSortHelper(std::vector<int>& nums);
    int partitionPositives(std::vector<int>& nums);
    int countPositivesUpTo(const std::vector<int>& nums, int x);
    bool hasNumber(const std::vector<int>& nums, int target);
    void markPresence(std::vector<int>& nums, int num);
};

}
}