#pragma once

#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 56: Merge Intervals
 * 
 * Given an array of intervals where intervals[i] = [start_i, end_i], 
 * merge all overlapping intervals, and return an array of the non-overlapping 
 * intervals that cover all the intervals in the input.
 * 
 * Constraints:
 * - 1 <= intervals.length <= 10^4
 * - intervals[i].length == 2
 * - 0 <= start_i <= end_i <= 10^4
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class MergeIntervals {
public:
    /**
     * Approach 1: Sort by Start Time (Classic Optimal)
     * 
     * Sort intervals by start time and merge overlapping intervals in single pass.
     * 
     * Reasoning: This is the standard optimal solution. First sort intervals by start time
     * to ensure we process them in chronological order. Then iterate through sorted intervals,
     * maintaining the current merged interval. If next interval overlaps with current
     * (next.start <= current.end), merge them by extending current.end. Otherwise, add
     * current to result and start new interval. This approach guarantees we find all
     * overlaps with single pass after sorting.
     * 
     * Time Complexity: O(n log n) - dominated by sorting
     * Space Complexity: O(1) - excluding result array, in-place merging
     * 
     * Best when: Standard interval merging, most intuitive approach
     * Worst when: Need alternative sorting strategy, specific merge requirements
     */
    std::vector<std::vector<int>> mergeIntervals(std::vector<std::vector<int>>& intervals);

    /**
     * Approach 2: Sort by End Time (Alternative Sorting)
     * 
     * Sort intervals by end time and use different merging strategy.
     * 
     * Reasoning: While sorting by start time is more common, sorting by end time
     * provides alternative perspective on interval processing. After sorting by end time,
     * we need different logic to detect overlaps: current interval overlaps with next
     * if current.end >= next.start. This approach demonstrates that different sorting
     * strategies can work for interval problems, though may require adjusted logic.
     * 
     * Time Complexity: O(n log n) - sorting dominates
     * Space Complexity: O(1) - in-place processing
     * 
     * Best when: End time priority important, exploring alternative approaches
     * Worst when: Start time sorting is more natural, standard approach preferred
     */
    std::vector<std::vector<int>> mergeIntervalsByEndTime(std::vector<std::vector<int>>& intervals);

    /**
     * Approach 3: Stack-Based Merging (Explicit State Management)
     * 
     * Use stack to manage current interval being built during merging process.
     * 
     * Reasoning: Use stack to explicitly manage the interval merging process.
     * Sort intervals by start time, then push first interval onto stack. For each
     * subsequent interval, peek at stack top. If current interval overlaps with
     * stack top, pop stack top, merge with current interval, and push merged result.
     * Otherwise, push current interval as-is. This approach makes the merging
     * process more explicit and can be extended for complex interval operations.
     * 
     * Time Complexity: O(n log n) - sorting plus linear stack operations
     * Space Complexity: O(n) - stack storage
     * 
     * Best when: Explicit state management preferred, extensible to complex operations
     * Worst when: Extra stack overhead unnecessary, simple merging sufficient
     */
    std::vector<std::vector<int>> mergeIntervalsStack(std::vector<std::vector<int>>& intervals);

    /**
     * Approach 4: Coordinate Sweep Line (Event Processing)
     * 
     * Convert intervals to events and process using sweep line algorithm.
     * 
     * Reasoning: Transform problem into event processing: each interval creates
     * "start" and "end+1" events. Sort all events by coordinate. Sweep through
     * events maintaining active interval count. When count goes from 0 to 1,
     * start new merged interval. When count goes from 1 to 0, end current interval.
     * This approach provides different algorithmic perspective and can handle
     * more complex interval queries efficiently.
     * 
     * Time Complexity: O(n log n) - sorting events
     * Space Complexity: O(n) - event list storage
     * 
     * Best when: Event processing perspective preferred, extensible to range queries
     * Worst when: Simple merging sufficient, event overhead unnecessary
     */
    std::vector<std::vector<int>> mergeIntervalsSweepLine(std::vector<std::vector<int>>& intervals);

    /**
     * Approach 5: Union-Find (Connected Components)
     * 
     * Model overlapping intervals as connected components using Union-Find.
     * 
     * Reasoning: Treat each interval as a node in graph where overlapping intervals
     * are connected by edges. Use Union-Find to group connected components (overlapping
     * intervals). After processing all overlaps, each connected component represents
     * intervals that should be merged. Extract bounds of each component to form
     * final merged intervals. While this has higher complexity, it demonstrates
     * how graph algorithms can solve interval problems.
     * 
     * Time Complexity: O(n²α(n)) - check all pairs for overlap, Union-Find operations
     * Space Complexity: O(n) - Union-Find structure
     * 
     * Best when: Graph algorithm perspective interesting, complex interval relationships
     * Worst when: Performance critical, simpler approaches sufficient
     */
    std::vector<std::vector<int>> mergeIntervalsUnionFind(std::vector<std::vector<int>>& intervals);

    /**
     * Approach 6: Interval Tree Based (Advanced Data Structure)
     * 
     * Build interval tree and use it to find and merge overlapping intervals.
     * 
     * Reasoning: Construct interval tree data structure optimized for interval
     * queries. Insert all intervals into tree, then query for overlaps to build
     * merged result. While this approach has higher complexity for single merge
     * operation, it demonstrates advanced interval data structures and would be
     * efficient for multiple queries on same interval set. Shows how specialized
     * data structures can solve interval problems.
     * 
     * Time Complexity: O(n log n) - tree construction and queries
     * Space Complexity: O(n) - interval tree storage
     * 
     * Best when: Multiple queries expected, learning interval trees, complex queries
     * Worst when: Single merge operation, simpler approaches more efficient
     */
    std::vector<std::vector<int>> mergeIntervalsIntervalTree(std::vector<std::vector<int>>& intervals);

private:
    // Helper functions
    bool intervalsOverlap(const std::vector<int>& a, const std::vector<int>& b);
    std::vector<int> mergeTwo(const std::vector<int>& a, const std::vector<int>& b);
    
    // Event processing structures
    struct Event {
        int coordinate;
        int type; // 1 for start, -1 for end
        
        Event(int coord, int t) : coordinate(coord), type(t) {}
        
        // Sort by coordinate, then by type (end events before start events at same coordinate)
        bool operator<(const Event& other) const {
            if (coordinate != other.coordinate) {
                return coordinate < other.coordinate;
            }
            return type < other.type; // -1 (end) < 1 (start)
        }
    };
    
    // Union-Find structure
    struct UnionFind {
        std::vector<int> parent;
        std::vector<int> rank;
        
        UnionFind(int n) : parent(n), rank(n, 0) {
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]); // Path compression
            }
            return parent[x];
        }
        
        void unite(int x, int y) {
            int px = find(x), py = find(y);
            if (px == py) return;
            
            // Union by rank
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }
    };
    
    // Interval Tree Node
    struct IntervalTreeNode {
        int start, end;
        int maxEnd; // Maximum end in subtree
        IntervalTreeNode* left;
        IntervalTreeNode* right;
        
        IntervalTreeNode(int s, int e) 
            : start(s), end(e), maxEnd(e), left(nullptr), right(nullptr) {}
    };
    
    // Interval tree operations
    IntervalTreeNode* insertInterval(IntervalTreeNode* root, int start, int end);
    void findOverlapping(IntervalTreeNode* root, int start, int end, std::vector<std::vector<int>>& result);
    void deleteTree(IntervalTreeNode* root);
    void updateMaxEnd(IntervalTreeNode* node);
};

}
}