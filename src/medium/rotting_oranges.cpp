#include "rotting_oranges.h"
#include <algorithm>

namespace leetcode {
namespace medium {

// ============================================================================
// Approach 1: Multi-source BFS (Optimal)
// ============================================================================

int RottingOranges::orangesRotting(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    std::queue<std::pair<int, int>> q;
    int freshCount = 0;
    
    // Find all initially rotten oranges and count fresh ones
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }
    
    // If no fresh oranges, return 0
    if (freshCount == 0) return 0;
    
    int minutes = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // BFS level by level
    while (!q.empty() && freshCount > 0) {
        int size = q.size();
        minutes++;
        
        // Process all oranges that rot at this minute
        for (int i = 0; i < size; i++) {
            auto [row, col] = q.front();
            q.pop();
            
            // Check all 4 directions
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                // Check bounds and if it's a fresh orange
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 1) {
                    
                    grid[newRow][newCol] = 2;  // Rot the orange
                    freshCount--;
                    q.push({newRow, newCol});
                }
            }
        }
    }
    
    return freshCount == 0 ? minutes : -1;
}

// ============================================================================
// Approach 2: DFS with Time Simulation (Recursive)
// ============================================================================

int RottingOrangesDFS::orangesRotting(std::vector<std::vector<int>>& grid) {
    return dfsSimulate(grid, 0);
}

int RottingOrangesDFS::dfsSimulate(std::vector<std::vector<int>> grid, int minute) {
    // Check if there are any fresh oranges left
    bool hasFresh = false;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == 1) {
                hasFresh = true;
                break;
            }
        }
        if (hasFresh) break;
    }
    
    if (!hasFresh) return minute;
    
    // Create next state
    std::vector<std::vector<int>> nextGrid = grid;
    bool rotOccurred = false;
    
    int m = grid.size();
    int n = grid[0].size();
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // Find fresh oranges adjacent to rotten ones
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {  // Fresh orange
                // Check if adjacent to any rotten orange
                for (auto& dir : directions) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
                        grid[ni][nj] == 2) {
                        nextGrid[i][j] = 2;
                        rotOccurred = true;
                        break;
                    }
                }
            }
        }
    }
    
    if (!rotOccurred) return -1;  // No more rotting possible
    
    return dfsSimulate(nextGrid, minute + 1);
}

bool RottingOrangesDFS::hasRottingOccurred(const std::vector<std::vector<int>>& before, 
                                          const std::vector<std::vector<int>>& after) {
    for (int i = 0; i < before.size(); i++) {
        for (int j = 0; j < before[0].size(); j++) {
            if (before[i][j] != after[i][j]) {
                return true;
            }
        }
    }
    return false;
}

// ============================================================================
// Approach 3: Iterative Simulation (Level-by-level)
// ============================================================================

int RottingOrangesIterative::orangesRotting(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int minutes = 0;
    
    while (true) {
        auto newlyRotten = findNewlyRotten(grid);
        
        if (newlyRotten.empty()) {
            // No more oranges can rot
            break;
        }
        
        // Rot all the newly identified oranges
        for (auto& pos : newlyRotten) {
            grid[pos.first][pos.second] = 2;
        }
        
        minutes++;
    }
    
    // Check if any fresh oranges remain
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == 1) {
                return -1;
            }
        }
    }
    
    return minutes;
}

std::vector<std::pair<int, int>> RottingOrangesIterative::findNewlyRotten(
    const std::vector<std::vector<int>>& grid) {
    
    std::vector<std::pair<int, int>> result;
    int m = grid.size();
    int n = grid[0].size();
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {  // Fresh orange
                // Check if adjacent to any rotten orange
                for (auto& dir : directions) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
                        grid[ni][nj] == 2) {
                        result.push_back({i, j});
                        break;
                    }
                }
            }
        }
    }
    
    return result;
}

// ============================================================================
// Approach 4: Union-Find with Time Tracking (Graph Connectivity)
// ============================================================================

int RottingOrangesUnionFind::orangesRotting(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    UnionFind uf(m * n);
    std::vector<std::pair<int, int>> freshOranges;
    std::vector<std::pair<int, int>> rottenOranges;
    
    // Find all oranges and initialize rot times for rotten ones
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                freshOranges.push_back({i, j});
            } else if (grid[i][j] == 2) {
                rottenOranges.push_back({i, j});
                uf.setRotTime(encode(i, j, n), 0);
            }
        }
    }
    
    if (freshOranges.empty()) return 0;
    
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maxTime = 0;
    
    // Simulate time progression
    for (int time = 1; time <= m * n; time++) {
        bool changed = false;
        
        for (auto& fresh : freshOranges) {
            int row = fresh.first, col = fresh.second;
            int encoded = encode(row, col, n);
            
            if (uf.getRotTime(encoded) != -1) continue;  // Already rotten
            
            // Check if adjacent to any rotten orange
            for (auto& dir : directions) {
                int nr = row + dir[0];
                int nc = col + dir[1];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int neighborEncoded = encode(nr, nc, n);
                    int neighborRotTime = uf.getRotTime(neighborEncoded);
                    
                    if (neighborRotTime != -1 && neighborRotTime < time) {
                        uf.setRotTime(encoded, time);
                        maxTime = std::max(maxTime, time);
                        changed = true;
                        break;
                    }
                }
            }
        }
        
        if (!changed) break;
    }
    
    // Check if all fresh oranges got rotten
    for (auto& fresh : freshOranges) {
        int encoded = encode(fresh.first, fresh.second, n);
        if (uf.getRotTime(encoded) == -1) {
            return -1;
        }
    }
    
    return maxTime;
}

// ============================================================================
// Approach 5: Priority Queue with Time Stamps (Event-driven)
// ============================================================================

int RottingOrangesPriorityQueue::orangesRotting(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    std::priority_queue<RotEvent, std::vector<RotEvent>, std::greater<RotEvent>> pq;
    std::vector<std::vector<bool>> processed(m, std::vector<bool>(n, false));
    int freshCount = 0;
    
    // Initialize with all initially rotten oranges
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                pq.push(RotEvent(i, j, 0));
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }
    
    if (freshCount == 0) return 0;
    
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int maxTime = 0;
    
    while (!pq.empty()) {
        RotEvent event = pq.top();
        pq.pop();
        
        if (processed[event.row][event.col]) continue;
        processed[event.row][event.col] = true;
        
        maxTime = std::max(maxTime, event.time);
        
        // Schedule rot events for adjacent fresh oranges
        for (auto& dir : directions) {
            int nr = event.row + dir[0];
            int nc = event.col + dir[1];
            
            if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                grid[nr][nc] == 1 && !processed[nr][nc]) {
                
                grid[nr][nc] = 2;
                freshCount--;
                pq.push(RotEvent(nr, nc, event.time + 1));
            }
        }
    }
    
    return freshCount == 0 ? maxTime : -1;
}

// ============================================================================
// Approach 6: Bidirectional BFS (Optimization Exploration)
// ============================================================================

int RottingOrangesBidirectional::orangesRotting(std::vector<std::vector<int>>& grid) {
    // For this problem, bidirectional BFS doesn't provide the traditional advantage
    // since we need to reach ALL fresh oranges, not just find a path to one.
    // However, we can use it conceptually by tracking infection spread from both
    // "sides" - from rotten oranges and checking reachability
    
    int m = grid.size();
    int n = grid[0].size();
    
    std::queue<std::pair<int, int>> rottenQueue;
    int freshCount = 0;
    
    // Find initial state
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                rottenQueue.push({i, j});
            } else if (grid[i][j] == 1) {
                freshCount++;
                // Check if this fresh orange is reachable from any rotten orange
                if (!hasPath(grid, i, j)) {
                    return -1;  // Unreachable fresh orange
                }
            }
        }
    }
    
    if (freshCount == 0) return 0;
    
    // Standard BFS from all rotten oranges
    int minutes = 0;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    while (!rottenQueue.empty() && freshCount > 0) {
        int size = rottenQueue.size();
        minutes++;
        
        for (int i = 0; i < size; i++) {
            auto [row, col] = rottenQueue.front();
            rottenQueue.pop();
            
            for (auto& dir : directions) {
                int nr = row + dir[0];
                int nc = col + dir[1];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                    grid[nr][nc] == 1) {
                    
                    grid[nr][nc] = 2;
                    freshCount--;
                    rottenQueue.push({nr, nc});
                }
            }
        }
    }
    
    return freshCount == 0 ? minutes : -1;
}

bool RottingOrangesBidirectional::hasPath(const std::vector<std::vector<int>>& grid, 
                                          int startRow, int startCol) {
    // Check if there's a path from any rotten orange to this position
    int m = grid.size();
    int n = grid[0].size();
    
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    std::queue<std::pair<int, int>> q;
    
    // Start BFS from all rotten oranges
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
                visited[i][j] = true;
            }
        }
    }
    
    auto neighbors = getNeighbors(startRow, startCol, m, n);
    
    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        
        if (row == startRow && col == startCol) {
            return true;
        }
        
        for (auto& neighbor : getNeighbors(row, col, m, n)) {
            int nr = neighbor.first;
            int nc = neighbor.second;
            
            if (!visited[nr][nc] && grid[nr][nc] != 0) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    
    return false;
}

std::vector<std::pair<int, int>> RottingOrangesBidirectional::getNeighbors(int row, int col, int m, int n) {
    std::vector<std::pair<int, int>> neighbors;
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (auto& dir : directions) {
        int nr = row + dir[0];
        int nc = col + dir[1];
        
        if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
            neighbors.push_back({nr, nc});
        }
    }
    
    return neighbors;
}

}
}