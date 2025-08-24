#include "number_of_islands.h"
#include <queue>
#include <stack>

namespace leetcode {
namespace medium {

// Initialize direction vectors
constexpr int NumberOfIslands::dirs[4][2];

// Approach 1: DFS (Depth-First Search) - Optimal
int NumberOfIslands::numIslandsDFS(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    
    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                islands++;
                dfs(grid, i, j);
            }
        }
    }
    
    return islands;
}

void NumberOfIslands::dfs(std::vector<std::vector<char>>& grid, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    
    // Boundary check and water check
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1') {
        return;
    }
    
    // Mark as visited by changing to '0'
    grid[i][j] = '0';
    
    // Explore all 4 directions
    dfs(grid, i + 1, j);  // down
    dfs(grid, i - 1, j);  // up
    dfs(grid, i, j + 1);  // right
    dfs(grid, i, j - 1);  // left
}

// Approach 2: BFS (Breadth-First Search)
int NumberOfIslands::numIslandsBFS(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    
    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                islands++;
                bfs(grid, i, j);
            }
        }
    }
    
    return islands;
}

void NumberOfIslands::bfs(std::vector<std::vector<char>>& grid, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    
    std::queue<std::pair<int, int>> queue;
    queue.push({i, j});
    grid[i][j] = '0';  // Mark as visited
    
    while (!queue.empty()) {
        auto [row, col] = queue.front();
        queue.pop();
        
        // Check all 4 directions
        for (const auto& dir : dirs) {
            int newRow = row + dir[0];
            int newCol = col + dir[1];
            
            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && 
                grid[newRow][newCol] == '1') {
                grid[newRow][newCol] = '0';  // Mark as visited
                queue.push({newRow, newCol});
            }
        }
    }
}

// Approach 3: Union-Find (Disjoint Set Union)
NumberOfIslands::UnionFind::UnionFind(int n) : parent(n), rank(n, 0), count(0) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int NumberOfIslands::UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // Path compression
    }
    return parent[x];
}

void NumberOfIslands::UnionFind::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) return;
    
    // Union by rank
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    count--;
}

int NumberOfIslands::numIslandsUnionFind(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    
    int m = grid.size();
    int n = grid[0].size();
    
    // Count initial land cells
    int landCount = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                landCount++;
            }
        }
    }
    
    UnionFind uf(m * n);
    uf.setCount(landCount);
    
    // Union adjacent land cells
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                // Check right and down neighbors only (to avoid double checking)
                if (j + 1 < n && grid[i][j + 1] == '1') {
                    uf.unite(i * n + j, i * n + j + 1);
                }
                if (i + 1 < m && grid[i + 1][j] == '1') {
                    uf.unite(i * n + j, (i + 1) * n + j);
                }
            }
        }
    }
    
    return uf.getCount();
}

// Approach 4: Iterative DFS with Stack
int NumberOfIslands::numIslandsIterativeDFS(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    
    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                islands++;
                
                // Use stack for iterative DFS
                std::stack<std::pair<int, int>> stack;
                stack.push({i, j});
                grid[i][j] = '0';
                
                while (!stack.empty()) {
                    auto [row, col] = stack.top();
                    stack.pop();
                    
                    // Check all 4 directions
                    for (const auto& dir : dirs) {
                        int newRow = row + dir[0];
                        int newCol = col + dir[1];
                        
                        if (newRow >= 0 && newRow < m && 
                            newCol >= 0 && newCol < n && 
                            grid[newRow][newCol] == '1') {
                            grid[newRow][newCol] = '0';
                            stack.push({newRow, newCol});
                        }
                    }
                }
            }
        }
    }
    
    return islands;
}

// Approach 5: Marking with Different Values
int NumberOfIslands::numIslandsWithMarking(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    
    int m = grid.size();
    int n = grid[0].size();
    char islandId = '2';  // Start marking from '2'
    int islands = 0;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                markIsland(grid, i, j, islandId);
                islandId++;
                islands++;
            }
        }
    }
    
    // Restore grid if needed (optional)
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] >= '2') {
                grid[i][j] = '1';  // Restore to original land
            }
        }
    }
    
    return islands;
}

void NumberOfIslands::markIsland(std::vector<std::vector<char>>& grid, int i, int j, char mark) {
    int m = grid.size();
    int n = grid[0].size();
    
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1') {
        return;
    }
    
    grid[i][j] = mark;
    
    markIsland(grid, i + 1, j, mark);
    markIsland(grid, i - 1, j, mark);
    markIsland(grid, i, j + 1, mark);
    markIsland(grid, i, j - 1, mark);
}

// Approach 6: Sink Island Approach
int NumberOfIslands::numIslandsSink(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    
    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                islands++;
                sinkIsland(grid, i, j);
            }
        }
    }
    
    return islands;
}

void NumberOfIslands::sinkIsland(std::vector<std::vector<char>>& grid, int i, int j) {
    int m = grid.size();
    int n = grid[0].size();
    
    // Boundary and water check
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {
        return;
    }
    
    // Sink the land
    grid[i][j] = '0';
    
    // Recursively sink all connected land
    sinkIsland(grid, i + 1, j);
    sinkIsland(grid, i - 1, j);
    sinkIsland(grid, i, j + 1);
    sinkIsland(grid, i, j - 1);
}

}  // namespace medium
}  // namespace leetcode