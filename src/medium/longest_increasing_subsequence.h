#pragma once

#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 300: Longest Increasing Subsequence
 * 
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * A subsequence is a sequence that can be derived from an array by deleting some or no elements
 * without changing the order of the remaining elements.
 * 
 * Constraints:
 * - 1 <= nums.length <= 2500
 * - -10^4 <= nums[i] <= 10^4
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class LongestIncreasingSubsequence {
public:
    /**
     * Approach 1: Dynamic Programming (Classic O(n²))
     * 
     * Use DP where dp[i] represents length of longest increasing subsequence ending at index i.
     * 
     * Reasoning: This is the fundamental DP solution. For each position i, we check all
     * previous positions j where nums[j] < nums[i] and extend the longest subsequence
     * ending at j. dp[i] = max(dp[j] + 1) for all valid j. The answer is max of all dp[i].
     * This approach builds the solution incrementally by considering all valid extensions
     * of existing subsequences. While O(n²), it's intuitive and demonstrates core DP principles.
     * 
     * Time Complexity: O(n²) - nested loops checking all pairs
     * Space Complexity: O(n) - DP array storage
     * 
     * Best when: Learning DP concepts, need to track actual subsequence, moderate input sizes
     * Worst when: Large inputs, need optimal performance, space constraints
     */
    int lengthOfLISDP(std::vector<int>& nums);

    /**
     * Approach 2: Binary Search with Patience Sorting (Optimal O(n log n))
     * 
     * Use binary search to maintain sorted array of smallest tail elements.
     * 
     * Reasoning: This is the optimal solution using patience sorting algorithm. Maintain
     * array `tails` where tails[i] is the smallest ending element of increasing subsequence
     * of length i+1. For each number, use binary search to find position where it should
     * be placed: if larger than all elements, extend array; otherwise, replace first
     * element >= current number. This maintains the invariant and gives correct LIS length.
     * 
     * Time Complexity: O(n log n) - binary search for each element
     * Space Complexity: O(n) - tails array in worst case
     * 
     * Best when: Large inputs, optimal performance required, standard interview solution
     * Worst when: Need actual subsequence (only gives length), learning DP concepts
     */
    int lengthOfLISBinarySearch(std::vector<int>& nums);

    /**
     * Approach 3: Segment Tree with Coordinate Compression
     * 
     * Use segment tree to efficiently query maximum LIS length for ranges.
     * 
     * Reasoning: Transform problem to range maximum queries. Coordinate compression
     * maps values to smaller range [1, unique_count]. Segment tree maintains maximum
     * LIS length ending with values in each range. For each element, query maximum
     * length for values less than current, add 1, and update tree. This approach
     * demonstrates how advanced data structures can solve DP problems efficiently.
     * 
     * Time Complexity: O(n log k) - where k is number of unique elements
     * Space Complexity: O(k) - coordinate compression + segment tree
     * 
     * Best when: Learning segment trees, need range queries, competitive programming
     * Worst when: Simple inputs, standard interviews, implementation complexity unwanted
     */
    int lengthOfLISSegmentTree(std::vector<int>& nums);

    /**
     * Approach 4: Fenwick Tree (Binary Indexed Tree)
     * 
     * Use Fenwick tree to maintain prefix maximum of LIS lengths.
     * 
     * Reasoning: Similar to segment tree but with simpler implementation. After coordinate
     * compression, use Fenwick tree to maintain maximum LIS length for prefixes. For each
     * element with compressed coordinate c, query maximum for range [1, c-1], add 1,
     * and update position c. Fenwick tree provides efficient range maximum queries
     * and point updates, making this approach elegant for the LIS problem.
     * 
     * Time Complexity: O(n log k) - where k is number of unique elements
     * Space Complexity: O(k) - coordinate compression + Fenwick tree
     * 
     * Best when: Prefer simpler tree structure than segment tree, competitive programming
     * Worst when: Standard interviews, need to understand tree operations, simple cases
     */
    int lengthOfLISFenwickTree(std::vector<int>& nums);

    /**
     * Approach 5: Stack-Based with Reconstruction
     * 
     * Use stack to track current increasing subsequence and reconstruct optimal solution.
     * 
     * Reasoning: Maintain stack of elements forming current increasing subsequence.
     * For each new element, if it extends current subsequence, push it. Otherwise,
     * find position where it should replace existing element to maintain increasing
     * property. This approach allows reconstruction of actual subsequence and provides
     * intuitive understanding of how LIS evolves. Stack operations naturally handle
     * the "patience sorting" concept in a more explicit way.
     * 
     * Time Complexity: O(n log n) - binary search operations on stack
     * Space Complexity: O(n) - stack storage
     * 
     * Best when: Need actual subsequence, intuitive stack-based thinking, educational
     * Worst when: Only need length, prefer standard solutions, minimal space required
     */
    int lengthOfLISStack(std::vector<int>& nums);

    /**
     * Approach 6: Divide and Conquer with Merge
     * 
     * Recursively divide array and merge LIS information from subarrays.
     * 
     * Reasoning: Divide array into two halves, recursively find LIS information for each half,
     * then merge results. The challenge is combining LIS information across the split point:
     * consider all elements from left half with all elements from right half to find
     * cross-boundary increasing subsequences. While this approach has higher complexity,
     * it demonstrates how divide-and-conquer can be applied to DP problems.
     * 
     * Time Complexity: O(n² log n) - merge step requires checking cross-boundary pairs
     * Space Complexity: O(n log n) - recursion stack + temporary storage
     * 
     * Best when: Learning divide-and-conquer variations, academic interest, parallel potential
     * Worst when: Performance matters, standard solutions preferred, space constrained
     */
    int lengthOfLISDivideConquer(std::vector<int>& nums);

private:
    // Helper functions for coordinate compression
    std::vector<int> coordinateCompress(const std::vector<int>& nums);
    
    // Segment Tree operations
    struct SegmentTree {
        std::vector<int> tree;
        int n;
        
        SegmentTree(int size);
        void update(int pos, int val);
        int query(int l, int r);
        void updateHelper(int node, int start, int end, int pos, int val);
        int queryHelper(int node, int start, int end, int l, int r);
    };
    
    // Fenwick Tree operations
    struct FenwickTree {
        std::vector<int> tree;
        int n;
        
        FenwickTree(int size);
        void update(int pos, int val);
        int query(int pos);
        int rangeQuery(int l, int r);
    };
    
    // Stack-based helper
    int binarySearchPosition(const std::vector<int>& arr, int target);
    
    // Divide and conquer helper
    struct LISInfo {
        int length;
        int minStart;
        int maxEnd;
        std::vector<int> prefix;  // LIS ending at each position
        std::vector<int> suffix;  // LIS starting at each position
    };
    
    LISInfo divideConquerHelper(std::vector<int>& nums, int left, int right);
    LISInfo mergeLISInfo(const LISInfo& leftInfo, const LISInfo& rightInfo, 
                         std::vector<int>& nums, int left, int mid, int right);
};

}
}