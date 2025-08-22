#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>

namespace leetcode {
namespace medium {

/**
 * Problem 133: Clone Graph
 * 
 * Given a reference of a node in a connected undirected graph.
 * Return a deep copy (clone) of the graph.
 * 
 * Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
 * 
 * class Node {
 *     public int val;
 *     public List<Node> neighbors;
 * }
 * 
 * Test case format:
 * For simplicity, each node's value is the same as the node's index (1-indexed).
 * For example, the first node with val == 1, the second node with val == 2, and so on.
 * The graph is represented in the test case using an adjacency list.
 * 
 * An adjacency list is a collection of unordered lists used to represent a finite graph.
 * Each list describes the set of neighbors of a node in the graph.
 * 
 * The given node will always be the first node with val = 1. You must return the copy
 * of the given node as a reference to the cloned graph.
 * 
 * Constraints:
 * - The number of nodes in the graph is in the range [0, 100].
 * - 1 <= Node.val <= 100
 * - Node.val is unique for each node.
 * - There are no repeated edges and no self-loops in the graph.
 * - The Graph is connected and all nodes can be visited starting from the given node.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */

// Definition for a Node.
class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }
    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

/**
 * Approach 1: DFS with Hash Map (Most Common)
 * 
 * Use DFS traversal with a hash map to track visited nodes and their clones.
 * 
 * Reasoning: This is the most intuitive approach for graph cloning. We perform
 * a depth-first traversal of the original graph, creating new nodes for each
 * unvisited node. The hash map serves two purposes: tracking visited nodes to
 * avoid infinite loops, and mapping original nodes to their clones for proper
 * neighbor connections. This approach naturally handles the recursive structure
 * of graph traversal and ensures each node is cloned exactly once.
 * 
 * Time Complexity: O(N + M) where N is nodes and M is edges
 * Space Complexity: O(N) for hash map and recursion stack
 * 
 * Best when: Natural recursive thinking, standard graph cloning
 * Worst when: Deep graphs causing stack overflow
 */
class CloneGraphDFS {
public:
    Node* cloneGraph(Node* node);
    
private:
    std::unordered_map<Node*, Node*> visited;
    Node* dfs(Node* node);
};

/**
 * Approach 2: BFS with Hash Map (Level-order)
 * 
 * Use BFS traversal with queue and hash map for iterative cloning.
 * 
 * Reasoning: BFS provides an iterative alternative to DFS, avoiding potential
 * stack overflow issues with deep graphs. We use a queue to process nodes
 * level by level, creating clones and establishing neighbor relationships.
 * The hash map tracks the mapping between original and cloned nodes. This
 * approach is particularly useful when we want to avoid recursion or need
 * to process the graph in a breadth-first manner.
 * 
 * Time Complexity: O(N + M) where N is nodes and M is edges
 * Space Complexity: O(N) for hash map and queue
 * 
 * Best when: Avoiding recursion, iterative preference, wide graphs
 * Worst when: Simple recursive solution sufficient
 */
class CloneGraphBFS {
public:
    Node* cloneGraph(Node* node);
};

/**
 * Approach 3: DFS with Stack (Iterative DFS)
 * 
 * Use explicit stack to simulate DFS without recursion.
 * 
 * Reasoning: This approach combines the depth-first exploration pattern of
 * recursive DFS with the stack safety of iterative solutions. We manually
 * manage a stack to control the traversal order, pushing unvisited neighbors
 * and processing them in LIFO order. This gives us the benefits of DFS
 * (following paths to completion) while avoiding recursion depth limitations.
 * 
 * Time Complexity: O(N + M) where N is nodes and M is edges
 * Space Complexity: O(N) for hash map and explicit stack
 * 
 * Best when: DFS pattern preferred but recursion avoided
 * Worst when: BFS or recursive DFS more natural
 */
class CloneGraphIterativeDFS {
public:
    Node* cloneGraph(Node* node);
};

/**
 * Approach 4: Two-Pass Algorithm (Nodes then Edges)
 * 
 * First pass creates all nodes, second pass establishes all connections.
 * 
 * Reasoning: This approach separates the node creation from edge establishment,
 * making the algorithm conceptually clearer. In the first pass, we traverse
 * the graph to create all clone nodes and store them in a hash map. In the
 * second pass, we traverse again to establish neighbor relationships using
 * the previously created clones. This separation can be helpful for debugging
 * and understanding, and works well when we need to process nodes and edges
 * separately.
 * 
 * Time Complexity: O(N + M) where N is nodes and M is edges
 * Space Complexity: O(N) for hash map and traversal structures
 * 
 * Best when: Clear separation of concerns, debugging ease
 * Worst when: Single-pass efficiency preferred
 */
class CloneGraphTwoPass {
public:
    Node* cloneGraph(Node* node);
    
private:
    void createNodes(Node* node, std::unordered_map<Node*, Node*>& nodeMap, std::unordered_set<Node*>& visited);
    void createEdges(Node* node, std::unordered_map<Node*, Node*>& nodeMap, std::unordered_set<Node*>& visited);
};

/**
 * Approach 5: Union-Find Based Cloning (Component Analysis)
 * 
 * Use Union-Find to analyze graph structure before cloning.
 * 
 * Reasoning: While Union-Find is typically used for connectivity problems,
 * we can leverage it to analyze the graph's connected components and structure
 * before performing the actual cloning. This approach first builds a Union-Find
 * structure to understand the graph topology, then uses this information to
 * guide the cloning process. Though more complex than needed for this problem,
 * it demonstrates how different data structures can be combined for graph
 * operations.
 * 
 * Time Complexity: O(N * α(N) + M) where α is inverse Ackermann function
 * Space Complexity: O(N) for Union-Find structure and hash map
 * 
 * Best when: Learning Union-Find applications, graph analysis needed
 * Worst when: Simple cloning sufficient, performance critical
 */
class CloneGraphUnionFind {
public:
    Node* cloneGraph(Node* node);
    
private:
    class UnionFind {
    public:
        std::unordered_map<int, int> parent;
        std::unordered_map<int, int> rank;
        
        void makeSet(int x);
        int find(int x);
        void unite(int x, int y);
    };
    
    void buildUnionFind(Node* node, UnionFind& uf, std::unordered_set<Node*>& visited);
    void cloneWithStructure(Node* node, std::unordered_map<Node*, Node*>& nodeMap, 
                           std::unordered_set<Node*>& visited);
};

/**
 * Approach 6: Topological Clone (Ordering Based)
 * 
 * Use topological-like ordering for systematic cloning.
 * 
 * Reasoning: Although the graph is undirected and may contain cycles (making
 * true topological sorting impossible), we can use a topological-inspired
 * approach to order our cloning process. We perform multiple passes, each
 * time cloning nodes whose dependencies (neighbors) have been processed.
 * This methodical approach ensures systematic processing and can provide
 * insights into graph structure analysis.
 * 
 * Time Complexity: O(N² + M) in worst case due to multiple passes
 * Space Complexity: O(N) for tracking structures
 * 
 * Best when: Systematic processing preferred, learning graph ordering
 * Worst when: Performance optimization needed, simple solution sufficient
 */
class CloneGraphTopological {
public:
    Node* cloneGraph(Node* node);
    
private:
    std::vector<Node*> getTopologicalOrder(Node* start);
    void cloneInOrder(const std::vector<Node*>& order, std::unordered_map<Node*, Node*>& nodeMap);
};

}
}