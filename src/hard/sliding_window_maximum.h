#pragma once

#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>

namespace leetcode {
namespace hard {

/**
 * Problem 239: Sliding Window Maximum
 * 
 * You are given an array of integers nums, there is a sliding window of size k 
 * which is moving from the very left of the array to the very right. You can 
 * only see the k numbers in the window. Each time the sliding window moves 
 * right by one position.
 * 
 * Return the max sliding window.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 * - 1 <= k <= nums.length
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class SlidingWindowMaximum {
public:
    /**
     * Approach 1: Deque (Monotonic Queue) - Optimal
     * 
     * Use deque to maintain indices of elements in decreasing order of values.
     * 
     * Reasoning: This is the optimal solution using a monotonic decreasing deque.
     * The deque stores indices and maintains the property that values at these indices
     * are in decreasing order. For each new element: (1) Remove indices outside current
     * window, (2) Remove indices whose values are smaller than current element (they'll
     * never be maximum), (3) Add current index, (4) Front of deque gives maximum.
     * This ensures each element is added and removed at most once, achieving O(n) time.
     * 
     * Time Complexity: O(n) - each element processed at most twice (add and remove)
     * Space Complexity: O(k) - deque stores at most k indices
     * 
     * Best when: Want optimal solution, understand monotonic data structures
     * Worst when: Deque operations seem complex, prefer simpler approaches
     */
    std::vector<int> maxSlidingWindowDeque(std::vector<int>& nums, int k);

    /**
     * Approach 2: Priority Queue (Max Heap) - Intuitive
     * 
     * Use max heap to efficiently get maximum, with lazy removal of outdated elements.
     * 
     * Reasoning: Maintain a max heap of (value, index) pairs for current window.
     * For each position, add new element to heap. To get maximum, repeatedly pop
     * elements whose indices are outside current window until finding valid maximum.
     * While not optimal due to logarithmic operations, this approach is intuitive
     * and handles the sliding window concept naturally using heap properties.
     * 
     * Time Complexity: O(n log k) - n elements, each requiring O(log k) heap operations
     * Space Complexity: O(k) - heap stores elements in current window
     * 
     * Best when: Heap operations familiar, prefer intuitive sliding window handling
     * Worst when: Want optimal linear time, logarithmic factor is concern
     */
    std::vector<int> maxSlidingWindowHeap(std::vector<int>& nums, int k);

    /**
     * Approach 3: Multiset (Balanced BST) - Alternative Efficient
     * 
     * Use multiset to maintain sorted elements with O(log k) operations.
     * 
     * Reasoning: Multiset maintains elements in sorted order with efficient insertion,
     * deletion, and maximum access. For each window movement, remove outgoing element
     * and add incoming element. Maximum is always the last element (rbegin()).
     * This approach provides O(log k) operations with clean insertion/deletion semantics,
     * making it easier to implement correctly than deque approach.
     * 
     * Time Complexity: O(n log k) - n elements, each requiring O(log k) set operations
     * Space Complexity: O(k) - set stores exactly k elements
     * 
     * Best when: Clean insertion/deletion semantics preferred, comfortable with sets
     * Worst when: Want linear time, logarithmic operations too slow
     */
    std::vector<int> maxSlidingWindowMultiset(std::vector<int>& nums, int k);

    /**
     * Approach 4: Divide and Conquer with Sparse Table - Preprocessing
     * 
     * Preprocess array with sparse table for O(1) range maximum queries.
     * 
     * Reasoning: Build sparse table that allows O(1) range maximum queries on any
     * subarray. For sliding window, each window becomes a range query [i, i+k-1].
     * Sparse table preprocesses all power-of-2 length ranges, allowing any range
     * to be covered by at most two overlapping power-of-2 ranges. While preprocessing
     * takes O(n log n) time and space, each query is O(1), making this efficient
     * for multiple sliding window queries on same array.
     * 
     * Time Complexity: O(n log n) preprocessing + O(n) queries = O(n log n)
     * Space Complexity: O(n log n) - sparse table storage
     * 
     * Best when: Multiple sliding window queries expected, preprocessing cost amortized
     * Worst when: Single sliding window query, preprocessing overhead too high
     */
    std::vector<int> maxSlidingWindowSparseTable(std::vector<int>& nums, int k);

    /**
     * Approach 5: Brute Force - Baseline
     * 
     * For each window position, scan the window to find maximum.
     * 
     * Reasoning: Straightforward approach that examines each window independently.
     * For each of the (n-k+1) window positions, scan k elements to find maximum.
     * While inefficient with O(nk) time complexity, this approach is simple to
     * implement and understand, serving as baseline for correctness verification
     * and performance comparison with optimized approaches.
     * 
     * Time Complexity: O(n*k) - (n-k+1) windows, each requiring O(k) scan
     * Space Complexity: O(1) - only variables for tracking maximum
     * 
     * Best when: Small k, simple baseline implementation, correctness verification
     * Worst when: Large k or n, performance critical applications
     */
    std::vector<int> maxSlidingWindowBruteForce(std::vector<int>& nums, int k);

    /**
     * Approach 6: Stack-Based with Monotonic Property - Alternative
     * 
     * Use two monotonic stacks to simulate queue behavior for window sliding.
     * 
     * Reasoning: Maintain two monotonic decreasing stacks representing left and right
     * parts of current window. When window slides, move elements between stacks
     * while preserving monotonic property. Maximum is the maximum of both stack tops.
     * While more complex than deque approach, this demonstrates how stack-based
     * structures can be adapted for queue-like sliding window problems.
     * 
     * Time Complexity: O(n) - amortized, each element moved between stacks at most once
     * Space Complexity: O(k) - stacks store window elements
     * 
     * Best when: Stack operations preferred, understanding monotonic stack applications
     * Worst when: Implementation complexity outweighs benefits, deque more natural
     */
    std::vector<int> maxSlidingWindowStacks(std::vector<int>& nums, int k);

private:
    // Helper functions
    void buildSparseTable(const std::vector<int>& nums, std::vector<std::vector<int>>& st);
    int queryMax(const std::vector<std::vector<int>>& st, int left, int right);
    
    // Stack-based helper structures
    struct MonotonicStack {
        std::stack<std::pair<int, int>> stack; // (value, count)
        
        void push(int value);
        void pop(int count = 1);
        int getMax() const;
        bool empty() const;
        int size() const;
    };
    
    void rebalanceStacks(MonotonicStack& left, MonotonicStack& right);
};

}
}