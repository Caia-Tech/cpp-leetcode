#pragma once

#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <stack>
#include <deque>

namespace leetcode {
namespace medium {

/**
 * Problem 994: Rotting Oranges
 * 
 * You are given an m x n grid where each cell can have one of three values:
 * - 0 representing an empty cell,
 * - 1 representing a fresh orange, or
 * - 2 representing a rotten orange.
 * 
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten
 * orange becomes rotten.
 * 
 * Return the minimum number of minutes that must elapse until no cell has a
 * fresh orange. If this is impossible, return -1.
 * 
 * Constraints:
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 10
 * - grid[i][j] is 0, 1, or 2.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */

/**
 * Approach 1: Multi-source BFS (Optimal)
 * 
 * Use BFS from all initially rotten oranges simultaneously to simulate rot spreading.
 * 
 * Reasoning: This is the classic approach for multi-source shortest path problems.
 * We start BFS from all initially rotten oranges at the same time, treating them
 * as sources at distance 0. Each minute, rot spreads to adjacent fresh oranges.
 * We continue until no more fresh oranges can be infected. The key insight is
 * that all rotten oranges at the same "generation" rot fresh oranges simultaneously,
 * making this a perfect application of level-order BFS traversal.
 * 
 * Time Complexity: O(m*n) - visit each cell at most once
 * Space Complexity: O(m*n) - queue can contain all cells in worst case
 * 
 * Best when: Standard solution needed, optimal time complexity
 * Worst when: Want to explore alternative approaches for learning
 */
class RottingOranges {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid);
};

/**
 * Approach 2: DFS with Time Simulation (Recursive)
 * 
 * Use DFS to recursively simulate the rotting process at each time step.
 * 
 * Reasoning: Alternative approach using DFS to simulate time progression.
 * At each minute, we find all fresh oranges adjacent to rotten ones and mark
 * them for rotting. Then we recursively continue to the next minute. While
 * less efficient than BFS, this approach demonstrates how DFS can be adapted
 * for time-based simulations and provides insight into recursive state exploration.
 * 
 * Time Complexity: O(m*n*t) where t is the time to rot all oranges
 * Space Complexity: O(m*n) for recursion stack and copies
 * 
 * Best when: Recursive thinking preferred, exploring DFS applications
 * Worst when: Performance critical, large grids
 */
class RottingOrangesDFS {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid);
    
private:
    int dfsSimulate(std::vector<std::vector<int>> grid, int minute);
    bool hasRottingOccurred(const std::vector<std::vector<int>>& before, 
                           const std::vector<std::vector<int>>& after);
};

/**
 * Approach 3: Iterative Simulation (Level-by-level)
 * 
 * Simulate minute-by-minute progression without using BFS queue.
 * 
 * Reasoning: Simulates the rotting process by iteratively finding all fresh
 * oranges that should rot in the current minute, marking them, and advancing
 * to the next minute. This approach is more intuitive to understand as it
 * directly models the problem description. We maintain the grid state and
 * update it level by level, making it easy to visualize the progression.
 * 
 * Time Complexity: O(m*n*t) where t is time to complete
 * Space Complexity: O(m*n) for storing positions to update
 * 
 * Best when: Intuitive simulation preferred, educational purposes
 * Worst when: Performance optimization needed
 */
class RottingOrangesIterative {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid);
    
private:
    std::vector<std::pair<int, int>> findNewlyRotten(const std::vector<std::vector<int>>& grid);
};

/**
 * Approach 4: Union-Find with Time Tracking (Graph Connectivity)
 * 
 * Model the problem as graph connectivity with time-based union operations.
 * 
 * Reasoning: Novel approach treating orange rotting as a connectivity problem.
 * We model each orange as a node and rot spreading as edges in a graph. Using
 * Union-Find, we track when each fresh orange gets connected to a rotten source.
 * While more complex than needed, this demonstrates how graph algorithms can
 * model time-based propagation and provides insight into advanced problem modeling.
 * 
 * Time Complexity: O(m*n*α(m*n)*t) where α is inverse Ackermann function
 * Space Complexity: O(m*n) for Union-Find structure
 * 
 * Best when: Graph theory perspective interesting, learning Union-Find applications
 * Worst when: Simple solution preferred
 */
class RottingOrangesUnionFind {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid);
    
private:
    class UnionFind {
    public:
        std::vector<int> parent, rank, rotTime;
        
        UnionFind(int n) : parent(n), rank(n, 0), rotTime(n, -1) {
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        void unite(int x, int y, int time) {
            int px = find(x), py = find(y);
            if (px == py) return;
            
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
            
            // Update rot time for the newly connected component
            int root = find(x);
            if (rotTime[root] == -1) {
                rotTime[root] = time;
            }
        }
        
        void setRotTime(int x, int time) {
            int root = find(x);
            if (rotTime[root] == -1) {
                rotTime[root] = time;
            }
        }
        
        int getRotTime(int x) {
            int root = find(x);
            return rotTime[root];
        }
    };
    
    int encode(int row, int col, int n) { return row * n + col; }
    std::pair<int, int> decode(int encoded, int n) { return {encoded / n, encoded % n}; }
};

/**
 * Approach 5: Priority Queue with Time Stamps (Event-driven)
 * 
 * Use priority queue to process rotting events in chronological order.
 * 
 * Reasoning: Models the problem as an event-driven simulation. Each orange
 * rotting is an event with a timestamp. We use a priority queue to process
 * events in chronological order. When an orange rots, it schedules rot events
 * for its adjacent fresh oranges. This approach mimics discrete event simulation
 * and provides insight into event-driven programming patterns.
 * 
 * Time Complexity: O(m*n*log(m*n)) due to priority queue operations
 * Space Complexity: O(m*n) for priority queue and tracking
 * 
 * Best when: Event-driven thinking preferred, learning priority queue applications
 * Worst when: Simple BFS sufficient, avoid complexity
 */
class RottingOrangesPriorityQueue {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid);
    
private:
    struct RotEvent {
        int row, col, time;
        
        RotEvent(int r, int c, int t) : row(r), col(c), time(t) {}
        
        bool operator>(const RotEvent& other) const {
            return time > other.time;
        }
    };
};

/**
 * Approach 6: Bidirectional BFS (Optimization Exploration)
 * 
 * Attempt bidirectional BFS between rotten and fresh oranges (conceptual).
 * 
 * Reasoning: While bidirectional BFS doesn't directly apply to this problem
 * (since we need all fresh oranges, not just reaching one), we can explore
 * the concept by simultaneously tracking the "infection frontier" and the
 * "safe zone boundary." This approach demonstrates advanced BFS techniques
 * and shows how classical algorithms can be adapted to novel scenarios.
 * 
 * Time Complexity: O(m*n) similar to standard BFS
 * Space Complexity: O(m*n) for multiple queues
 * 
 * Best when: Exploring advanced BFS techniques, algorithmic learning
 * Worst when: Standard approach sufficient, simplicity preferred
 */
class RottingOrangesBidirectional {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid);
    
private:
    bool hasPath(const std::vector<std::vector<int>>& grid, int startRow, int startCol);
    std::vector<std::pair<int, int>> getNeighbors(int row, int col, int m, int n);
};

}
}