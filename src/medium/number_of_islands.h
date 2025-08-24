#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

namespace leetcode {
namespace medium {

/**
 * Problem 200: Number of Islands
 * 
 * Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water),
 * return the number of islands.
 * 
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally
 * or vertically. You may assume all four edges of the grid are all surrounded by water.
 * 
 * Constraints:
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 300
 * - grid[i][j] is '0' or '1'
 */
class NumberOfIslands {
public:
    /**
     * Approach 1: DFS (Depth-First Search) - Optimal
     * 
     * Use DFS to mark all connected land cells as visited.
     * 
     * Reasoning: This is the classic and most intuitive solution. When we find
     * an unvisited land cell ('1'), we increment island count and use DFS to
     * mark all connected land cells as visited (change to '0'). This ensures
     * each island is counted exactly once. DFS naturally explores the entire
     * island before moving to the next. The recursion follows the connected
     * component structure perfectly.
     * 
     * Time Complexity: O(m * n) - visit each cell at most once
     * Space Complexity: O(m * n) - recursion stack in worst case (all land)
     * 
     * Best when: Standard solution, clean recursive code preferred
     * Worst when: Very large grids might cause stack overflow
     */
    int numIslandsDFS(std::vector<std::vector<char>>& grid);

    /**
     * Approach 2: BFS (Breadth-First Search)
     * 
     * Use BFS with queue to explore islands level by level.
     * 
     * Reasoning: BFS explores islands layer by layer from starting point.
     * When we find unvisited land, we add it to queue and process all
     * connected land cells. This avoids deep recursion and gives us more
     * control over memory usage. BFS is particularly good for finding
     * shortest paths (though not needed here) and can be more cache-friendly
     * for wide islands.
     * 
     * Time Complexity: O(m * n) - visit each cell at most once
     * Space Complexity: O(min(m, n)) - queue holds at most one layer
     * 
     * Best when: Avoiding recursion, need iterative solution
     * Worst when: DFS is simpler and sufficient
     */
    int numIslandsBFS(std::vector<std::vector<char>>& grid);

    /**
     * Approach 3: Union-Find (Disjoint Set Union)
     * 
     * Use Union-Find data structure to group connected components.
     * 
     * Reasoning: Union-Find is perfect for connected component problems.
     * We treat each land cell as a node and union adjacent land cells.
     * The number of disjoint sets equals the number of islands. This
     * approach is more complex but demonstrates an important data structure
     * and can be extended to dynamic island formation problems.
     * 
     * Time Complexity: O(m * n * α(m*n)) where α is inverse Ackermann
     * Space Complexity: O(m * n) - parent and rank arrays
     * 
     * Best when: Learning Union-Find, need to track component merging
     * Worst when: Simple DFS/BFS is sufficient
     */
    int numIslandsUnionFind(std::vector<std::vector<char>>& grid);

    /**
     * Approach 4: Iterative DFS with Stack
     * 
     * Use explicit stack for iterative depth-first search.
     * 
     * Reasoning: This approach simulates recursive DFS using an explicit
     * stack, avoiding potential stack overflow for large grids. We push
     * coordinates onto stack and process them iteratively. This gives us
     * the same traversal pattern as recursive DFS but with more control
     * over memory usage and the ability to handle larger inputs.
     * 
     * Time Complexity: O(m * n) - visit each cell at most once
     * Space Complexity: O(m * n) - stack can hold all cells in worst case
     * 
     * Best when: Large grids, need DFS pattern without recursion
     * Worst when: Recursive DFS is acceptable
     */
    int numIslandsIterativeDFS(std::vector<std::vector<char>>& grid);

    /**
     * Approach 5: Marking with Different Values
     * 
     * Mark each island with a unique identifier while counting.
     * 
     * Reasoning: Instead of just marking visited cells, we assign each
     * island a unique ID (starting from '2'). This approach not only
     * counts islands but also labels them, which can be useful for
     * follow-up questions like finding the largest island or merging
     * islands. We use the grid itself to store island IDs, avoiding
     * extra space for visited tracking.
     * 
     * Time Complexity: O(m * n) - visit each cell at most once
     * Space Complexity: O(m * n) - recursion stack for marking
     * 
     * Best when: Need to identify individual islands, follow-up questions
     * Worst when: Input must remain unchanged
     */
    int numIslandsWithMarking(std::vector<std::vector<char>>& grid);

    /**
     * Approach 6: Sink Island Approach
     * 
     * "Sink" each island by converting all '1's to '0's.
     * 
     * Reasoning: This approach literally "sinks" islands by converting
     * all connected '1's to '0's when we find a new island. It's a
     * destructive but space-efficient approach that modifies the input
     * grid. We count how many times we initiate the sinking process,
     * which equals the number of islands. This is essentially DFS with
     * in-place modification.
     * 
     * Time Complexity: O(m * n) - visit each cell at most once
     * Space Complexity: O(m * n) - recursion stack in worst case
     * 
     * Best when: Input modification is acceptable, simple implementation
     * Worst when: Need to preserve original grid
     */
    int numIslandsSink(std::vector<std::vector<char>>& grid);

private:
    // Helper for DFS approach
    void dfs(std::vector<std::vector<char>>& grid, int i, int j);
    
    // Helper for BFS approach
    void bfs(std::vector<std::vector<char>>& grid, int i, int j);
    
    // Helper for marking approach
    void markIsland(std::vector<std::vector<char>>& grid, int i, int j, char mark);
    
    // Helper for sink approach
    void sinkIsland(std::vector<std::vector<char>>& grid, int i, int j);
    
    // Union-Find helper class
    class UnionFind {
    public:
        UnionFind(int n);
        int find(int x);
        void unite(int x, int y);
        int getCount() const { return count; }
        void setCount(int c) { count = c; }
        
    private:
        std::vector<int> parent;
        std::vector<int> rank;
        int count;
    };
    
    // Direction vectors for exploring neighbors
    static constexpr int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
};

}  // namespace medium
}  // namespace leetcode