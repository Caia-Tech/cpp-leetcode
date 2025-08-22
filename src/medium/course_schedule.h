#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>

namespace leetcode {
namespace medium {

/**
 * Problem 207: Course Schedule
 * 
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
 * You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you
 * must take course bi first if you want to take course ai.
 * 
 * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
 * 
 * Return true if you can finish all courses. Otherwise, return false.
 * 
 * Constraints:
 * - 1 <= numCourses <= 2000
 * - 0 <= prerequisites.length <= 5000
 * - prerequisites[i].length == 2
 * - 0 <= ai, bi < numCourses
 * - All the pairs prerequisites[i] are unique.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class CourseSchedule {
public:
    /**
     * Approach 1: DFS with Cycle Detection (Optimal)
     * 
     * Use DFS with three-color marking to detect cycles in the directed graph.
     * 
     * Reasoning: This is a classic cycle detection problem in a directed graph.
     * Courses are nodes, prerequisites are directed edges. We can finish all courses
     * if and only if there's no cycle in the graph. Use DFS with three colors:
     * WHITE (0) = unvisited, GRAY (1) = visiting (in current DFS path), BLACK (2) = visited.
     * If we encounter a GRAY node during DFS, we've found a cycle. This approach is
     * intuitive, efficient, and widely used for topological sorting problems.
     * 
     * Time Complexity: O(V + E) where V = numCourses, E = prerequisites.length
     * Space Complexity: O(V + E) for adjacency list and color array
     * 
     * Best when: Standard solution needed, good balance of simplicity and efficiency
     * Worst when: Need to find actual course order (use topological sort instead)
     */
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites);

    /**
     * Approach 2: BFS with Kahn's Algorithm (Topological Sort)
     * 
     * Use BFS to process nodes with no incoming edges, removing them layer by layer.
     * 
     * Reasoning: Kahn's algorithm is a BFS-based approach for topological sorting.
     * Calculate in-degree for each node (number of prerequisites). Start with nodes
     * having in-degree 0 (no prerequisites). Process these nodes, reducing in-degree
     * of their neighbors. If we process all nodes, no cycle exists. This approach
     * naturally produces a valid course order and is intuitive for understanding
     * dependency resolution. It's particularly good for finding one valid ordering.
     * 
     * Time Complexity: O(V + E) where V = numCourses, E = prerequisites.length
     * Space Complexity: O(V + E) for adjacency list and in-degree array
     * 
     * Best when: Need actual topological order, BFS preferred over DFS, clear layer-by-layer processing
     * Worst when: Only need cycle detection without ordering
     */
    bool canFinishKahn(int numCourses, std::vector<std::vector<int>>& prerequisites);

    /**
     * Approach 3: DFS with Stack-based Topological Sort
     * 
     * Use DFS to build topological order using a stack, detecting cycles along the way.
     * 
     * Reasoning: Classic DFS-based topological sort. During DFS, after visiting all
     * dependencies of a node, push it to a stack. If we complete DFS without finding
     * cycles, the stack contains nodes in reverse topological order. This approach
     * combines cycle detection with ordering computation. The stack naturally captures
     * the "finish time" ordering needed for topological sort. Educational for
     * understanding the relationship between DFS and topological ordering.
     * 
     * Time Complexity: O(V + E) where V = numCourses, E = prerequisites.length
     * Space Complexity: O(V + E) for adjacency list, recursion stack, and result stack
     * 
     * Best when: Need both cycle detection and topological order, educational purposes
     * Worst when: Stack space concerns with deep recursion
     */
    bool canFinishDFSStack(int numCourses, std::vector<std::vector<int>>& prerequisites);

    /**
     * Approach 4: Union-Find (Disjoint Set Union)
     * 
     * Use Union-Find to detect cycles by checking if edges connect nodes in same component.
     * 
     * Reasoning: While not the standard approach for directed graphs, Union-Find can
     * detect cycles with modifications. For each edge, if both nodes are already in
     * the same component when we try to union them, we have a cycle. This requires
     * careful handling of directed edges and is more complex than necessary for this
     * problem. However, it demonstrates the versatility of Union-Find and provides
     * an alternative perspective on cycle detection. Educational value in showing
     * different algorithmic approaches to the same problem.
     * 
     * Time Complexity: O(E * α(V)) where α is inverse Ackermann function (nearly constant)
     * Space Complexity: O(V) for parent and rank arrays
     * 
     * Best when: Learning Union-Find applications, already have Union-Find infrastructure
     * Worst when: Need standard solution, directed graph cycle detection
     */
    bool canFinishUnionFind(int numCourses, std::vector<std::vector<int>>& prerequisites);

    /**
     * Approach 5: Matrix-based DFS (Alternative Representation)
     * 
     * Use adjacency matrix representation with DFS cycle detection.
     * 
     * Reasoning: Instead of adjacency list, use adjacency matrix for graph representation.
     * While less space-efficient for sparse graphs, matrix representation provides O(1)
     * edge lookup and can be more cache-friendly for dense graphs. The DFS logic remains
     * similar but demonstrates how graph representation affects implementation details.
     * This approach is educational for understanding trade-offs between different graph
     * representations and their impact on algorithm implementation.
     * 
     * Time Complexity: O(V²) for matrix initialization, O(V + E) for DFS
     * Space Complexity: O(V²) for adjacency matrix
     * 
     * Best when: Dense graphs, need O(1) edge queries, educational comparison
     * Worst when: Sparse graphs (most prerequisite graphs), memory constraints
     */
    bool canFinishMatrix(int numCourses, std::vector<std::vector<int>>& prerequisites);

    /**
     * Approach 6: Iterative DFS with Explicit Stack
     * 
     * Use iterative DFS with explicit stack to avoid recursion stack overflow.
     * 
     * Reasoning: Converts recursive DFS to iterative using explicit stack. This avoids
     * potential stack overflow for deep recursion and provides more control over the
     * traversal process. While more complex than recursive DFS, it's important for
     * production systems where recursion depth might be a concern. The explicit stack
     * stores state information including the current node and processing phase,
     * allowing proper cycle detection without recursion.
     * 
     * Time Complexity: O(V + E) where V = numCourses, E = prerequisites.length
     * Space Complexity: O(V + E) for adjacency list and explicit stack
     * 
     * Best when: Large graphs with deep paths, production systems, avoiding recursion
     * Worst when: Simplicity preferred, small graphs where recursion depth not a concern
     */
    bool canFinishIterative(int numCourses, std::vector<std::vector<int>>& prerequisites);

private:
    // Helper structures and enums
    enum Color { WHITE = 0, GRAY = 1, BLACK = 2 };
    
    struct UnionFind {
        std::vector<int> parent;
        std::vector<int> rank;
        
        UnionFind(int n);
        int find(int x);
        bool unionSets(int x, int y);
        bool connected(int x, int y);
    };
    
    // Helper functions for DFS with Cycle Detection
    bool hasCycleDFS(int node, std::vector<std::vector<int>>& adj, std::vector<Color>& colors);
    
    // Helper functions for DFS with Stack
    bool dfsWithStack(int node, std::vector<std::vector<int>>& adj, 
                     std::vector<bool>& visited, std::vector<bool>& recStack,
                     std::stack<int>& topoStack);
    
    // Helper functions for Matrix DFS
    bool hasCycleMatrix(int node, std::vector<std::vector<bool>>& matrix, 
                       std::vector<Color>& colors, int numCourses);
    
    // Helper functions for Iterative DFS
    struct DFSState {
        int node;
        bool isReturning;  // false = first visit, true = returning from child
        DFSState(int n, bool r) : node(n), isReturning(r) {}
    };
    
    bool hasCycleIterative(int start, std::vector<std::vector<int>>& adj, 
                          std::vector<Color>& colors);
    
    // Utility functions
    std::vector<std::vector<int>> buildAdjacencyList(int numCourses, 
                                                     const std::vector<std::vector<int>>& prerequisites);
    std::vector<std::vector<bool>> buildAdjacencyMatrix(int numCourses, 
                                                        const std::vector<std::vector<int>>& prerequisites);
    std::vector<int> calculateInDegrees(int numCourses, 
                                        const std::vector<std::vector<int>>& prerequisites);
    
    // Validation functions
    bool isValidCourse(int course, int numCourses);
    bool hasMultipleEdges(const std::vector<std::vector<int>>& prerequisites);
    bool hasSelfLoop(const std::vector<std::vector<int>>& prerequisites);
};

// Implementation of UnionFind
inline CourseSchedule::UnionFind::UnionFind(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

inline int CourseSchedule::UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

inline bool CourseSchedule::UnionFind::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) {
        return false; // Already in same set, would create cycle
    }
    
    // Union by rank
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    
    return true;
}

inline bool CourseSchedule::UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}

}
}