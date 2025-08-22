#pragma once

#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <memory>
#include <chrono>

namespace leetcode {
namespace medium {

/**
 * Problem 146: LRU Cache
 * 
 * Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
 * 
 * Implement the LRUCache class:
 * - LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
 * - int get(int key) Return the value of the key if the key exists, otherwise return -1.
 * - void put(int key, int value) Update the value of the key if the key exists. Otherwise,
 *   add the key-value pair to the cache. If the number of keys exceeds the capacity from
 *   this operation, evict the least recently used key.
 * 
 * The functions get and put must each run in O(1) average time complexity.
 * 
 * Constraints:
 * - 1 <= capacity <= 3000
 * - 0 <= key <= 10^4
 * - 0 <= value <= 10^5
 * - At most 2 * 10^5 calls will be made to get and put.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */

/**
 * Approach 1: Doubly Linked List + HashMap (Optimal)
 * 
 * Use doubly linked list for ordering and hashmap for O(1) access.
 * 
 * Reasoning: This is the classic LRU cache implementation. The doubly linked list
 * maintains the usage order (most recent at head, least recent at tail). HashMap
 * provides O(1) access to any node. On get: move node to head. On put: add/move
 * to head, evict from tail if at capacity. The dummy head and tail nodes simplify
 * edge cases. This achieves O(1) for both operations and is the industry standard.
 * 
 * Time Complexity: O(1) for both get and put
 * Space Complexity: O(capacity) for storing cache entries
 * 
 * Best when: Standard implementation needed, true O(1) operations required
 * Worst when: Memory overhead of pointers is a concern
 */
class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k = 0, int v = 0) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    
    int capacity;
    int size;
    Node* head;  // Dummy head
    Node* tail;  // Dummy tail
    std::unordered_map<int, Node*> cache;
    
    void addToHead(Node* node);
    void removeNode(Node* node);
    Node* removeTail();
    void moveToHead(Node* node);

public:
    LRUCache(int capacity);
    ~LRUCache();
    int get(int key);
    void put(int key, int value);
};

/**
 * Approach 2: STL list + unordered_map (Clean Implementation)
 * 
 * Use STL list and map with iterators for cleaner code.
 * 
 * Reasoning: Leverages STL containers for cleaner implementation. std::list provides
 * doubly linked list functionality, and we store iterators in the hashmap. On access,
 * we splice the element to the front of the list (O(1) operation). This approach
 * reduces manual memory management and potential bugs while maintaining O(1) complexity.
 * The splice operation is key - it moves elements without copying.
 * 
 * Time Complexity: O(1) for both get and put
 * Space Complexity: O(capacity) for storing cache entries
 * 
 * Best when: Clean, maintainable code preferred, STL usage encouraged
 * Worst when: Need full control over memory layout
 */
class LRUCacheSTL {
private:
    int capacity;
    std::list<std::pair<int, int>> cacheList;  // pair<key, value>
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap;
    
public:
    LRUCacheSTL(int capacity);
    int get(int key);
    void put(int key, int value);
};

/**
 * Approach 3: Circular Buffer with Time Stamps (Alternative Design)
 * 
 * Use circular buffer with timestamps for different perspective.
 * 
 * Reasoning: Alternative approach using a fixed-size array as circular buffer.
 * Each entry has a timestamp indicating last access time. On cache miss, we
 * scan for the oldest timestamp (O(capacity) worst case). While not O(1) for
 * eviction, this approach has better cache locality and can be faster for
 * small capacities. It also demonstrates time-based eviction strategies.
 * 
 * Time Complexity: O(1) for get, O(capacity) for put with eviction
 * Space Complexity: O(capacity) fixed array
 * 
 * Best when: Small capacity, cache locality important, educational purposes
 * Worst when: Large capacity, strict O(1) requirement for all operations
 */
class LRUCacheCircular {
private:
    struct Entry {
        int key;
        int value;
        int timestamp;
        bool valid;
        Entry() : key(0), value(0), timestamp(0), valid(false) {}
    };
    
    int capacity;
    int currentTime;
    std::vector<Entry> buffer;
    std::unordered_map<int, int> keyToIndex;  // key -> buffer index
    
    int findLRUIndex();
    
public:
    LRUCacheCircular(int capacity);
    int get(int key);
    void put(int key, int value);
};

/**
 * Approach 4: LinkedHashMap-style Implementation (Ordered Map)
 * 
 * Implement ordered map similar to Java's LinkedHashMap.
 * 
 * Reasoning: Combines hash table with linked list in a single structure.
 * Each bucket in the hash table contains nodes that are also part of a
 * doubly linked list maintaining access order. This is how Java's LinkedHashMap
 * works internally. Provides insight into how ordered maps are implemented
 * and demonstrates the relationship between different data structures.
 * 
 * Time Complexity: O(1) average for both operations
 * Space Complexity: O(capacity) for cache storage
 * 
 * Best when: Understanding ordered map internals, educational value
 * Worst when: Simplicity preferred over educational complexity
 */
class LRUCacheLinkedHashMap {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node* hashNext;  // For hash collision chaining
        Node(int k = 0, int v = 0) : key(k), value(v), 
            prev(nullptr), next(nullptr), hashNext(nullptr) {}
    };
    
    int capacity;
    int size;
    int bucketCount;
    Node* head;
    Node* tail;
    std::vector<Node*> buckets;  // Hash table buckets
    
    int hash(int key);
    void addToHead(Node* node);
    void removeNode(Node* node);
    Node* findNode(int key);
    void removeFromBucket(Node* node);
    void addToBucket(Node* node);
    
public:
    LRUCacheLinkedHashMap(int capacity);
    ~LRUCacheLinkedHashMap();
    int get(int key);
    void put(int key, int value);
};

/**
 * Approach 5: Smart Pointers Implementation (Modern C++)
 * 
 * Use shared_ptr and weak_ptr for automatic memory management.
 * 
 * Reasoning: Demonstrates modern C++ memory management with smart pointers.
 * Uses shared_ptr for nodes and weak_ptr in the map to avoid circular references.
 * This approach eliminates manual memory management and potential memory leaks,
 * showing best practices for modern C++ development. The overhead of reference
 * counting is acceptable for most use cases.
 * 
 * Time Complexity: O(1) for both operations
 * Space Complexity: O(capacity) plus smart pointer overhead
 * 
 * Best when: Modern C++ codebase, safety over micro-optimization
 * Worst when: Minimal overhead required, embedded systems
 */
class LRUCacheSmartPtr {
private:
    struct Node {
        int key;
        int value;
        std::weak_ptr<Node> prev;
        std::shared_ptr<Node> next;
        Node(int k = 0, int v = 0) : key(k), value(v) {}
    };
    
    int capacity;
    int size;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    std::unordered_map<int, std::shared_ptr<Node>> cache;
    
    void addToHead(std::shared_ptr<Node> node);
    void removeNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node> removeTail();
    void moveToHead(std::shared_ptr<Node> node);
    
public:
    LRUCacheSmartPtr(int capacity);
    int get(int key);
    void put(int key, int value);
};

/**
 * Approach 6: Deque + Hash Map (Simplified Approach)
 * 
 * Use deque for ordering with periodic cleanup for true LRU.
 * 
 * Reasoning: Simplified approach using deque (double-ended queue) for maintaining
 * order. On access, we push to front and mark old position as invalid. Periodically
 * clean up invalid entries. While not strictly O(1) due to cleanup, amortized
 * complexity is good. This approach is simpler to implement and understand,
 * making it suitable for interviews or quick prototypes.
 * 
 * Time Complexity: O(1) amortized for operations
 * Space Complexity: O(capacity) with potential temporary overhead
 * 
 * Best when: Simple implementation needed, interview setting
 * Worst when: Strict O(1) worst-case required, memory efficiency critical
 */
class LRUCacheDeque {
private:
    int capacity;
    std::deque<std::pair<int, int>> cacheDeque;  // pair<key, value>
    std::unordered_map<int, int> cacheMap;  // key -> value (for O(1) lookup)
    
    void removeKey(int key);
    void cleanupDeque();
    
public:
    LRUCacheDeque(int capacity);
    int get(int key);
    void put(int key, int value);
};

}
}