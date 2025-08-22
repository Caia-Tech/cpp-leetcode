#include <gtest/gtest.h>
#include "medium/clone_graph.h"
#include <vector>
#include <unordered_set>
#include <queue>

namespace leetcode {
namespace medium {
namespace test {

class CloneGraphTest : public ::testing::Test {
protected:
    // Helper function to create a graph from adjacency list
    Node* createGraph(const std::vector<std::vector<int>>& adjList) {
        if (adjList.empty()) return nullptr;
        
        int n = adjList.size();
        std::vector<Node*> nodes(n + 1);
        
        // Create all nodes
        for (int i = 1; i <= n; i++) {
            nodes[i] = new Node(i);
        }
        
        // Create edges
        for (int i = 0; i < n; i++) {
            for (int neighbor : adjList[i]) {
                nodes[i + 1]->neighbors.push_back(nodes[neighbor]);
            }
        }
        
        return nodes[1];
    }
    
    // Helper function to delete a graph
    void deleteGraph(Node* node) {
        if (!node) return;
        
        std::unordered_set<Node*> visited;
        std::queue<Node*> queue;
        queue.push(node);
        visited.insert(node);
        
        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();
            
            for (Node* neighbor : current->neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }
        
        // Delete all visited nodes
        for (Node* n : visited) {
            delete n;
        }
    }
    
    // Helper function to verify if two graphs are identical
    bool areGraphsIdentical(Node* original, Node* cloned) {
        if (!original && !cloned) return true;
        if (!original || !cloned) return false;
        
        std::unordered_map<Node*, Node*> mapping;
        std::unordered_set<Node*> visitedOriginal;
        std::unordered_set<Node*> visitedCloned;
        
        return dfsVerify(original, cloned, mapping, visitedOriginal, visitedCloned);
    }
    
    bool dfsVerify(Node* original, Node* cloned, std::unordered_map<Node*, Node*>& mapping,
                   std::unordered_set<Node*>& visitedOriginal, std::unordered_set<Node*>& visitedCloned) {
        if (!original && !cloned) return true;
        if (!original || !cloned) return false;
        if (original->val != cloned->val) return false;
        
        // Check if we've seen this mapping before
        if (mapping.find(original) != mapping.end()) {
            return mapping[original] == cloned;
        }
        
        mapping[original] = cloned;
        visitedOriginal.insert(original);
        visitedCloned.insert(cloned);
        
        // Check neighbor count
        if (original->neighbors.size() != cloned->neighbors.size()) {
            return false;
        }
        
        // Check each neighbor
        for (size_t i = 0; i < original->neighbors.size(); i++) {
            Node* origNeighbor = original->neighbors[i];
            Node* clonedNeighbor = cloned->neighbors[i];
            
            if (origNeighbor->val != clonedNeighbor->val) {
                return false;
            }
            
            if (visitedOriginal.find(origNeighbor) == visitedOriginal.end()) {
                if (!dfsVerify(origNeighbor, clonedNeighbor, mapping, visitedOriginal, visitedCloned)) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    // Helper to check if clone is truly independent (different memory addresses)
    bool areGraphsIndependent(Node* original, Node* cloned) {
        if (!original && !cloned) return true;
        if (!original || !cloned) return false;
        
        std::unordered_set<Node*> visited;
        std::queue<std::pair<Node*, Node*>> queue;
        queue.push({original, cloned});
        
        while (!queue.empty()) {
            auto [orig, clone] = queue.front();
            queue.pop();
            
            if (orig == clone) return false;  // Same memory address
            if (visited.find(orig) != visited.end()) continue;
            visited.insert(orig);
            
            if (orig->val != clone->val) return false;
            if (orig->neighbors.size() != clone->neighbors.size()) return false;
            
            for (size_t i = 0; i < orig->neighbors.size(); i++) {
                queue.push({orig->neighbors[i], clone->neighbors[i]});
            }
        }
        
        return true;
    }
    
    // Helper function to test all approaches
    void testAllApproaches(const std::vector<std::vector<int>>& adjList) {
        Node* original = createGraph(adjList);
        
        CloneGraphDFS solution1;
        CloneGraphBFS solution2;
        CloneGraphIterativeDFS solution3;
        CloneGraphTwoPass solution4;
        CloneGraphUnionFind solution5;
        CloneGraphTopological solution6;
        
        Node* clone1 = solution1.cloneGraph(original);
        Node* clone2 = solution2.cloneGraph(original);
        Node* clone3 = solution3.cloneGraph(original);
        Node* clone4 = solution4.cloneGraph(original);
        Node* clone5 = solution5.cloneGraph(original);
        Node* clone6 = solution6.cloneGraph(original);
        
        EXPECT_TRUE(areGraphsIdentical(original, clone1)) << "DFS clone failed";
        EXPECT_TRUE(areGraphsIdentical(original, clone2)) << "BFS clone failed";
        EXPECT_TRUE(areGraphsIdentical(original, clone3)) << "Iterative DFS clone failed";
        EXPECT_TRUE(areGraphsIdentical(original, clone4)) << "Two-Pass clone failed";
        EXPECT_TRUE(areGraphsIdentical(original, clone5)) << "Union-Find clone failed";
        EXPECT_TRUE(areGraphsIdentical(original, clone6)) << "Topological clone failed";
        
        EXPECT_TRUE(areGraphsIndependent(original, clone1)) << "DFS clone not independent";
        EXPECT_TRUE(areGraphsIndependent(original, clone2)) << "BFS clone not independent";
        EXPECT_TRUE(areGraphsIndependent(original, clone3)) << "Iterative DFS clone not independent";
        EXPECT_TRUE(areGraphsIndependent(original, clone4)) << "Two-Pass clone not independent";
        EXPECT_TRUE(areGraphsIndependent(original, clone5)) << "Union-Find clone not independent";
        EXPECT_TRUE(areGraphsIndependent(original, clone6)) << "Topological clone not independent";
        
        // Clean up
        deleteGraph(original);
        deleteGraph(clone1);
        deleteGraph(clone2);
        deleteGraph(clone3);
        deleteGraph(clone4);
        deleteGraph(clone5);
        deleteGraph(clone6);
    }
    
    void testNullCase() {
        CloneGraphDFS solution1;
        CloneGraphBFS solution2;
        CloneGraphIterativeDFS solution3;
        CloneGraphTwoPass solution4;
        CloneGraphUnionFind solution5;
        CloneGraphTopological solution6;
        
        EXPECT_EQ(solution1.cloneGraph(nullptr), nullptr);
        EXPECT_EQ(solution2.cloneGraph(nullptr), nullptr);
        EXPECT_EQ(solution3.cloneGraph(nullptr), nullptr);
        EXPECT_EQ(solution4.cloneGraph(nullptr), nullptr);
        EXPECT_EQ(solution5.cloneGraph(nullptr), nullptr);
        EXPECT_EQ(solution6.cloneGraph(nullptr), nullptr);
    }
};

// LeetCode examples
TEST_F(CloneGraphTest, LeetCodeExample1) {
    // adjList = [[2,4],[1,3],[2,4],[1,3]]
    // Graph: 1-2-3-4 with 1-4 and 2-3 connections
    std::vector<std::vector<int>> adjList = {{2,4},{1,3},{2,4},{1,3}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, LeetCodeExample2) {
    // adjList = [[]]
    // Single node with no neighbors
    std::vector<std::vector<int>> adjList = {{}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, LeetCodeExample3) {
    // adjList = []
    // Empty graph
    testNullCase();
}

// Edge cases
TEST_F(CloneGraphTest, SingleNode) {
    // Single node with no connections
    std::vector<std::vector<int>> adjList = {{}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, TwoNodesConnected) {
    // Two nodes connected to each other
    std::vector<std::vector<int>> adjList = {{2},{1}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, LinearPath) {
    // Linear path: 1-2-3-4-5
    std::vector<std::vector<int>> adjList = {{2},{1,3},{2,4},{3,5},{4}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, CompleteCycle) {
    // Complete cycle: 1-2-3-1
    std::vector<std::vector<int>> adjList = {{2,3},{1,3},{1,2}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, Star) {
    // Star pattern: central node connected to all others
    std::vector<std::vector<int>> adjList = {{2,3,4,5},{1},{1},{1},{1}};
    testAllApproaches(adjList);
}

// Complex structures
TEST_F(CloneGraphTest, CompleteGraph4) {
    // Complete graph with 4 nodes (every node connected to every other)
    std::vector<std::vector<int>> adjList = {
        {2,3,4},{1,3,4},{1,2,4},{1,2,3}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, GridGraph) {
    // 2x2 grid graph
    // 1-2
    // | |
    // 3-4
    std::vector<std::vector<int>> adjList = {{2,3},{1,4},{1,4},{2,3}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, TreeStructure) {
    // Binary tree-like structure
    //     1
    //   /   \
    //  2     3
    // / \   / \
    //4   5 6   7
    std::vector<std::vector<int>> adjList = {
        {2,3},{1,4,5},{1,6,7},{2},{2},{3},{3}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, DiamondShape) {
    // Diamond shape: 1-2-4-3-1
    //   1
    //  / \
    // 2   3
    //  \ /
    //   4
    std::vector<std::vector<int>> adjList = {{2,3},{1,4},{1,4},{2,3}};
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, LongPath) {
    // Long linear path to test stack depth
    std::vector<std::vector<int>> adjList;
    int n = 20;
    for (int i = 0; i < n; i++) {
        std::vector<int> neighbors;
        if (i > 0) neighbors.push_back(i);
        if (i < n - 1) neighbors.push_back(i + 2);
        adjList.push_back(neighbors);
    }
    testAllApproaches(adjList);
}

// Complex connectivity patterns
TEST_F(CloneGraphTest, MultipleTriangles) {
    // Multiple connected triangles
    // Triangle 1: 1-2-3-1
    // Triangle 2: 3-4-5-3
    std::vector<std::vector<int>> adjList = {
        {2,3},{1,3},{1,2,4,5},{3,5},{3,4}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, ButterflyPattern) {
    // Butterfly pattern: two triangles sharing a vertex
    //   1     5
    //  / \   / \
    // 2---3---4
    std::vector<std::vector<int>> adjList = {
        {2,3},{1,3},{1,2,4,5},{3,5},{3,4}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, Wheel) {
    // Wheel pattern: central hub with outer cycle
    //     2
    //   /   \
    //  1-----3
    //  |  6  |
    //  5-----4
    std::vector<std::vector<int>> adjList = {
        {2,5,6},{1,3,6},{2,4,6},{3,5,6},{1,4,6},{1,2,3,4,5}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, DoubleStar) {
    // Two star patterns connected
    // Star 1: 1 connected to 2,3,4
    // Star 2: 5 connected to 6,7,8
    // Connection: 1-5
    std::vector<std::vector<int>> adjList = {
        {2,3,4,5},{1},{1},{1},{1,6,7,8},{5},{5},{5}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, ComplexCycle) {
    // Complex cycle with internal connections
    // Outer cycle: 1-2-3-4-5-6-1
    // Internal connections: 1-4, 2-5, 3-6
    std::vector<std::vector<int>> adjList = {
        {2,6,4},{1,3,5},{2,4,6},{1,3,5},{2,4,6},{1,3,5}
    };
    testAllApproaches(adjList);
}

// Stress tests
TEST_F(CloneGraphTest, DenseConnections) {
    // Almost complete graph with 8 nodes
    std::vector<std::vector<int>> adjList = {
        {2,3,4,5,6},{1,3,4,7,8},{1,2,5,6,7},{1,2,6,7,8},
        {1,3,6,7,8},{1,2,3,4,8},{2,3,4,5,8},{2,4,5,6,7}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, SparseLargeGraph) {
    // Large graph with sparse connections
    int n = 15;
    std::vector<std::vector<int>> adjList(n);
    // Create a path with some random extra connections
    for (int i = 0; i < n; i++) {
        if (i > 0) adjList[i].push_back(i);
        if (i < n - 1) adjList[i].push_back(i + 2);
        // Add some random connections
        if (i % 3 == 0 && i + 5 < n) {
            adjList[i].push_back(i + 6);
            adjList[i + 5].push_back(i + 1);
        }
    }
    testAllApproaches(adjList);
}

// Self-loop and multi-edge cases (according to constraints these don't exist)
TEST_F(CloneGraphTest, RegularPentagon) {
    // Regular pentagon with all vertices connected in a cycle
    std::vector<std::vector<int>> adjList = {
        {2,5},{1,3},{2,4},{3,5},{1,4}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, BipartiteGraph) {
    // Bipartite graph: set {1,3,5} and set {2,4,6}
    std::vector<std::vector<int>> adjList = {
        {2,4,6},{1,3,5},{2,4,6},{1,3,5},{2,4,6},{1,3,5}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, ThreeLevels) {
    // Three-level structure
    //       1
    //     / | \
    //    2  3  4
    //   /|  |  |\
    //  5 6  7  8 9
    std::vector<std::vector<int>> adjList = {
        {2,3,4},{1,5,6},{1,7},{1,8,9},{2},{2},{3},{4},{4}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, CrossConnections) {
    // Cross connections pattern
    //  1---2
    //  |\ /|
    //  | X |
    //  |/ \|
    //  3---4
    std::vector<std::vector<int>> adjList = {
        {2,3,4},{1,3,4},{1,2,4},{1,2,3}
    };
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, MaximumNodes) {
    // Test with maximum constraint (100 nodes) - simplified structure
    int n = 50;  // Use 50 for reasonable test time
    std::vector<std::vector<int>> adjList(n);
    
    // Create a cycle with every 5th node connected to center
    for (int i = 0; i < n; i++) {
        adjList[i].push_back(((i + 1) % n) + 1);  // Next in cycle
        adjList[i].push_back(((i - 1 + n) % n) + 1);  // Previous in cycle
        
        if (i % 5 == 0 && i != 0) {
            adjList[i].push_back(1);  // Connect to node 1
            adjList[0].push_back(i + 1);
        }
    }
    
    testAllApproaches(adjList);
}

TEST_F(CloneGraphTest, SpecialStructures) {
    // Test multiple special graph structures
    
    // Petersen graph subset (simplified)
    std::vector<std::vector<int>> adjList = {
        {2,5,6},{1,3,7},{2,4,8},{3,5,9},{1,4,10},
        {1,8,9},{2,7,10},{3,6,10},{5,6,9},{5,7,8}
    };
    testAllApproaches(adjList);
}

}
}
}