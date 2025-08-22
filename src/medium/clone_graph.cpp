#include "clone_graph.h"
#include <algorithm>

namespace leetcode {
namespace medium {

// ============================================================================
// Approach 1: DFS with Hash Map (Most Common)
// ============================================================================

Node* CloneGraphDFS::cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    visited.clear();
    return dfs(node);
}

Node* CloneGraphDFS::dfs(Node* node) {
    if (!node) return nullptr;
    
    // If we've already cloned this node, return the clone
    if (visited.find(node) != visited.end()) {
        return visited[node];
    }
    
    // Create a new node (clone)
    Node* clone = new Node(node->val);
    visited[node] = clone;
    
    // Clone all neighbors recursively
    for (Node* neighbor : node->neighbors) {
        clone->neighbors.push_back(dfs(neighbor));
    }
    
    return clone;
}

// ============================================================================
// Approach 2: BFS with Hash Map (Level-order)
// ============================================================================

Node* CloneGraphBFS::cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    std::unordered_map<Node*, Node*> visited;
    std::queue<Node*> queue;
    
    // Clone the starting node
    Node* clone = new Node(node->val);
    visited[node] = clone;
    queue.push(node);
    
    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();
        
        // Process all neighbors
        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                // Clone the neighbor if not already cloned
                visited[neighbor] = new Node(neighbor->val);
                queue.push(neighbor);
            }
            
            // Add the cloned neighbor to current clone's neighbors
            visited[current]->neighbors.push_back(visited[neighbor]);
        }
    }
    
    return clone;
}

// ============================================================================
// Approach 3: DFS with Stack (Iterative DFS)
// ============================================================================

Node* CloneGraphIterativeDFS::cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    std::unordered_map<Node*, Node*> visited;
    std::stack<Node*> stack;
    
    // Clone the starting node
    Node* clone = new Node(node->val);
    visited[node] = clone;
    stack.push(node);
    
    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();
        
        // Process all neighbors
        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                // Clone the neighbor if not already cloned
                visited[neighbor] = new Node(neighbor->val);
                stack.push(neighbor);
            }
            
            // Add the cloned neighbor to current clone's neighbors
            visited[current]->neighbors.push_back(visited[neighbor]);
        }
    }
    
    return clone;
}

// ============================================================================
// Approach 4: Two-Pass Algorithm (Nodes then Edges)
// ============================================================================

Node* CloneGraphTwoPass::cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    std::unordered_map<Node*, Node*> nodeMap;
    std::unordered_set<Node*> visited;
    
    // First pass: Create all nodes
    createNodes(node, nodeMap, visited);
    
    // Second pass: Create all edges
    visited.clear();
    createEdges(node, nodeMap, visited);
    
    return nodeMap[node];
}

void CloneGraphTwoPass::createNodes(Node* node, std::unordered_map<Node*, Node*>& nodeMap, 
                                   std::unordered_set<Node*>& visited) {
    if (!node || visited.find(node) != visited.end()) {
        return;
    }
    
    visited.insert(node);
    nodeMap[node] = new Node(node->val);
    
    // Recursively create nodes for all neighbors
    for (Node* neighbor : node->neighbors) {
        createNodes(neighbor, nodeMap, visited);
    }
}

void CloneGraphTwoPass::createEdges(Node* node, std::unordered_map<Node*, Node*>& nodeMap, 
                                   std::unordered_set<Node*>& visited) {
    if (!node || visited.find(node) != visited.end()) {
        return;
    }
    
    visited.insert(node);
    
    // Create edges for the cloned node
    for (Node* neighbor : node->neighbors) {
        nodeMap[node]->neighbors.push_back(nodeMap[neighbor]);
    }
    
    // Recursively create edges for all neighbors
    for (Node* neighbor : node->neighbors) {
        createEdges(neighbor, nodeMap, visited);
    }
}

// ============================================================================
// Approach 5: Union-Find Based Cloning (Component Analysis)
// ============================================================================

Node* CloneGraphUnionFind::cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    UnionFind uf;
    std::unordered_set<Node*> visited;
    std::unordered_map<Node*, Node*> nodeMap;
    
    // Build Union-Find structure to analyze graph
    buildUnionFind(node, uf, visited);
    
    // Clone the graph using the structural information
    visited.clear();
    cloneWithStructure(node, nodeMap, visited);
    
    return nodeMap[node];
}


void CloneGraphUnionFind::UnionFind::makeSet(int x) {
    if (parent.find(x) == parent.end()) {
        parent[x] = x;
        rank[x] = 0;
    }
}

int CloneGraphUnionFind::UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void CloneGraphUnionFind::UnionFind::unite(int x, int y) {
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
}

void CloneGraphUnionFind::buildUnionFind(Node* node, UnionFind& uf, std::unordered_set<Node*>& visited) {
    if (!node || visited.find(node) != visited.end()) {
        return;
    }
    
    visited.insert(node);
    uf.makeSet(node->val);
    
    // Unite with all neighbors
    for (Node* neighbor : node->neighbors) {
        uf.makeSet(neighbor->val);
        uf.unite(node->val, neighbor->val);
        buildUnionFind(neighbor, uf, visited);
    }
}

void CloneGraphUnionFind::cloneWithStructure(Node* node, std::unordered_map<Node*, Node*>& nodeMap, 
                                            std::unordered_set<Node*>& visited) {
    if (!node || visited.find(node) != visited.end()) {
        return;
    }
    
    visited.insert(node);
    
    // Create clone if not exists
    if (nodeMap.find(node) == nodeMap.end()) {
        nodeMap[node] = new Node(node->val);
    }
    
    // Process neighbors
    for (Node* neighbor : node->neighbors) {
        if (nodeMap.find(neighbor) == nodeMap.end()) {
            nodeMap[neighbor] = new Node(neighbor->val);
        }
        
        nodeMap[node]->neighbors.push_back(nodeMap[neighbor]);
        cloneWithStructure(neighbor, nodeMap, visited);
    }
}

// ============================================================================
// Approach 6: Topological Clone (Ordering Based)
// ============================================================================

Node* CloneGraphTopological::cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    std::unordered_map<Node*, Node*> nodeMap;
    
    // Get a topological-like ordering of nodes
    std::vector<Node*> order = getTopologicalOrder(node);
    
    // Clone nodes in this order
    cloneInOrder(order, nodeMap);
    
    return nodeMap[node];
}

std::vector<Node*> CloneGraphTopological::getTopologicalOrder(Node* start) {
    std::vector<Node*> order;
    std::unordered_set<Node*> visited;
    std::queue<Node*> queue;
    
    queue.push(start);
    visited.insert(start);
    
    // BFS to get an ordering (not true topological due to cycles)
    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();
        order.push_back(current);
        
        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }
    
    return order;
}

void CloneGraphTopological::cloneInOrder(const std::vector<Node*>& order, 
                                        std::unordered_map<Node*, Node*>& nodeMap) {
    // First, create all nodes
    for (Node* node : order) {
        nodeMap[node] = new Node(node->val);
    }
    
    // Then, establish all connections
    for (Node* node : order) {
        for (Node* neighbor : node->neighbors) {
            nodeMap[node]->neighbors.push_back(nodeMap[neighbor]);
        }
    }
}

}
}