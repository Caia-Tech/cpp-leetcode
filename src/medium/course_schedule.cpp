#include "course_schedule.h"
#include <algorithm>

namespace leetcode {
namespace medium {

// Approach 1: DFS with Cycle Detection (Optimal)
bool CourseSchedule::canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    // Build adjacency list representation
    std::vector<std::vector<int>> adj = buildAdjacencyList(numCourses, prerequisites);
    
    // Initialize colors for all nodes
    std::vector<Color> colors(numCourses, WHITE);
    
    // Check for cycles starting from each unvisited node
    for (int i = 0; i < numCourses; i++) {
        if (colors[i] == WHITE) {
            if (hasCycleDFS(i, adj, colors)) {
                return false; // Cycle detected
            }
        }
    }
    
    return true; // No cycles found
}

// Approach 2: BFS with Kahn's Algorithm (Topological Sort)
bool CourseSchedule::canFinishKahn(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    // Build adjacency list and calculate in-degrees
    std::vector<std::vector<int>> adj = buildAdjacencyList(numCourses, prerequisites);
    std::vector<int> inDegree = calculateInDegrees(numCourses, prerequisites);
    
    // Queue for BFS - start with nodes having no prerequisites
    std::queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    
    int processedCourses = 0;
    
    // Process nodes in topological order
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        processedCourses++;
        
        // Reduce in-degree for all neighbors
        for (int neighbor : adj[course]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    // If we processed all courses, no cycle exists
    return processedCourses == numCourses;
}

// Approach 3: DFS with Stack-based Topological Sort
bool CourseSchedule::canFinishDFSStack(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    // Build adjacency list
    std::vector<std::vector<int>> adj = buildAdjacencyList(numCourses, prerequisites);
    
    std::vector<bool> visited(numCourses, false);
    std::vector<bool> recStack(numCourses, false);
    std::stack<int> topoStack;
    
    // Try DFS from each unvisited node
    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            if (dfsWithStack(i, adj, visited, recStack, topoStack)) {
                return false; // Cycle detected
            }
        }
    }
    
    // Successfully built topological order (in topoStack)
    return true;
}

// Approach 4: Union-Find (Disjoint Set Union)
bool CourseSchedule::canFinishUnionFind(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    // Note: Union-Find is not ideal for directed cycle detection
    // This is a modified approach for educational purposes
    
    // Build adjacency list for DFS validation
    std::vector<std::vector<int>> adj = buildAdjacencyList(numCourses, prerequisites);
    
    // We'll still use DFS for directed cycle detection
    // Union-Find would work better for undirected graphs
    std::vector<Color> colors(numCourses, WHITE);
    
    for (int i = 0; i < numCourses; i++) {
        if (colors[i] == WHITE) {
            if (hasCycleDFS(i, adj, colors)) {
                return false;
            }
        }
    }
    
    return true;
}

// Approach 5: Matrix-based DFS (Alternative Representation)
bool CourseSchedule::canFinishMatrix(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    // Build adjacency matrix
    std::vector<std::vector<bool>> matrix = buildAdjacencyMatrix(numCourses, prerequisites);
    
    // Initialize colors for all nodes
    std::vector<Color> colors(numCourses, WHITE);
    
    // Check for cycles starting from each unvisited node
    for (int i = 0; i < numCourses; i++) {
        if (colors[i] == WHITE) {
            if (hasCycleMatrix(i, matrix, colors, numCourses)) {
                return false; // Cycle detected
            }
        }
    }
    
    return true; // No cycles found
}

// Approach 6: Iterative DFS with Explicit Stack
bool CourseSchedule::canFinishIterative(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    // Build adjacency list
    std::vector<std::vector<int>> adj = buildAdjacencyList(numCourses, prerequisites);
    
    // Initialize colors for all nodes
    std::vector<Color> colors(numCourses, WHITE);
    
    // Check for cycles starting from each unvisited node
    for (int i = 0; i < numCourses; i++) {
        if (colors[i] == WHITE) {
            if (hasCycleIterative(i, adj, colors)) {
                return false; // Cycle detected
            }
        }
    }
    
    return true; // No cycles found
}

// Helper function implementations

bool CourseSchedule::hasCycleDFS(int node, std::vector<std::vector<int>>& adj, std::vector<Color>& colors) {
    colors[node] = GRAY; // Mark as visiting
    
    // Check all neighbors
    for (int neighbor : adj[node]) {
        if (colors[neighbor] == GRAY) {
            return true; // Back edge found - cycle detected
        }
        if (colors[neighbor] == WHITE) {
            if (hasCycleDFS(neighbor, adj, colors)) {
                return true;
            }
        }
    }
    
    colors[node] = BLACK; // Mark as visited
    return false;
}

bool CourseSchedule::dfsWithStack(int node, std::vector<std::vector<int>>& adj, 
                                  std::vector<bool>& visited, std::vector<bool>& recStack,
                                  std::stack<int>& topoStack) {
    visited[node] = true;
    recStack[node] = true;
    
    // Check all neighbors
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfsWithStack(neighbor, adj, visited, recStack, topoStack)) {
                return true; // Cycle detected in subtree
            }
        } else if (recStack[neighbor]) {
            return true; // Back edge found - cycle detected
        }
    }
    
    recStack[node] = false;
    topoStack.push(node); // Add to topological order
    return false;
}

bool CourseSchedule::hasCycleMatrix(int node, std::vector<std::vector<bool>>& matrix, 
                                    std::vector<Color>& colors, int numCourses) {
    colors[node] = GRAY; // Mark as visiting
    
    // Check all possible neighbors
    for (int neighbor = 0; neighbor < numCourses; neighbor++) {
        if (matrix[node][neighbor]) { // Edge exists
            if (colors[neighbor] == GRAY) {
                return true; // Back edge found - cycle detected
            }
            if (colors[neighbor] == WHITE) {
                if (hasCycleMatrix(neighbor, matrix, colors, numCourses)) {
                    return true;
                }
            }
        }
    }
    
    colors[node] = BLACK; // Mark as visited
    return false;
}

bool CourseSchedule::hasCycleIterative(int start, std::vector<std::vector<int>>& adj, 
                                       std::vector<Color>& colors) {
    std::stack<DFSState> stack;
    stack.push(DFSState(start, false));
    
    while (!stack.empty()) {
        DFSState state = stack.top();
        stack.pop();
        
        if (state.isReturning) {
            // Returning from DFS subtree
            colors[state.node] = BLACK;
        } else {
            // First visit to node
            if (colors[state.node] == GRAY) {
                return true; // Already visiting - cycle detected
            }
            if (colors[state.node] == BLACK) {
                continue; // Already visited
            }
            
            colors[state.node] = GRAY;
            
            // Push return marker
            stack.push(DFSState(state.node, true));
            
            // Push all unvisited neighbors
            for (int neighbor : adj[state.node]) {
                if (colors[neighbor] == GRAY) {
                    return true; // Back edge - cycle detected
                }
                if (colors[neighbor] == WHITE) {
                    stack.push(DFSState(neighbor, false));
                }
            }
        }
    }
    
    return false;
}

std::vector<std::vector<int>> CourseSchedule::buildAdjacencyList(int numCourses, 
                                                                 const std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> adj(numCourses);
    
    for (const auto& prereq : prerequisites) {
        int course = prereq[0];
        int prerequisite = prereq[1];
        adj[prerequisite].push_back(course); // Edge from prerequisite to course
    }
    
    return adj;
}

std::vector<std::vector<bool>> CourseSchedule::buildAdjacencyMatrix(int numCourses, 
                                                                    const std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<bool>> matrix(numCourses, std::vector<bool>(numCourses, false));
    
    for (const auto& prereq : prerequisites) {
        int course = prereq[0];
        int prerequisite = prereq[1];
        matrix[prerequisite][course] = true; // Edge from prerequisite to course
    }
    
    return matrix;
}

std::vector<int> CourseSchedule::calculateInDegrees(int numCourses, 
                                                    const std::vector<std::vector<int>>& prerequisites) {
    std::vector<int> inDegree(numCourses, 0);
    
    for (const auto& prereq : prerequisites) {
        int course = prereq[0];
        inDegree[course]++; // Course has one more prerequisite
    }
    
    return inDegree;
}

bool CourseSchedule::isValidCourse(int course, int numCourses) {
    return course >= 0 && course < numCourses;
}

bool CourseSchedule::hasMultipleEdges(const std::vector<std::vector<int>>& prerequisites) {
    std::unordered_set<std::string> edges;
    
    for (const auto& prereq : prerequisites) {
        std::string edge = std::to_string(prereq[0]) + "," + std::to_string(prereq[1]);
        if (edges.count(edge)) {
            return true;
        }
        edges.insert(edge);
    }
    
    return false;
}

bool CourseSchedule::hasSelfLoop(const std::vector<std::vector<int>>& prerequisites) {
    for (const auto& prereq : prerequisites) {
        if (prereq[0] == prereq[1]) {
            return true;
        }
    }
    return false;
}

}
}