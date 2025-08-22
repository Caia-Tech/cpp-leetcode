#include "lru_cache.h"
#include <algorithm>
#include <climits>

namespace leetcode {
namespace medium {

// ============================================================================
// Approach 1: Doubly Linked List + HashMap (Optimal)
// ============================================================================

LRUCache::LRUCache(int capacity) : capacity(capacity), size(0) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
}

LRUCache::~LRUCache() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LRUCache::addToHead(Node* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

LRUCache::Node* LRUCache::removeTail() {
    Node* res = tail->prev;
    removeNode(res);
    return res;
}

void LRUCache::moveToHead(Node* node) {
    removeNode(node);
    addToHead(node);
}

int LRUCache::get(int key) {
    if (cache.find(key) == cache.end()) {
        return -1;
    }
    
    Node* node = cache[key];
    moveToHead(node);
    return node->value;
}

void LRUCache::put(int key, int value) {
    if (cache.find(key) != cache.end()) {
        // Update existing key
        Node* node = cache[key];
        node->value = value;
        moveToHead(node);
    } else {
        // Add new key
        Node* newNode = new Node(key, value);
        cache[key] = newNode;
        addToHead(newNode);
        size++;
        
        if (size > capacity) {
            // Evict LRU
            Node* tail = removeTail();
            cache.erase(tail->key);
            delete tail;
            size--;
        }
    }
}

// ============================================================================
// Approach 2: STL list + unordered_map (Clean Implementation)
// ============================================================================

LRUCacheSTL::LRUCacheSTL(int capacity) : capacity(capacity) {}

int LRUCacheSTL::get(int key) {
    auto it = cacheMap.find(key);
    if (it == cacheMap.end()) {
        return -1;
    }
    
    // Move to front
    cacheList.splice(cacheList.begin(), cacheList, it->second);
    return it->second->second;
}

void LRUCacheSTL::put(int key, int value) {
    auto it = cacheMap.find(key);
    
    if (it != cacheMap.end()) {
        // Update existing key
        it->second->second = value;
        cacheList.splice(cacheList.begin(), cacheList, it->second);
    } else {
        // Add new key
        if (cacheList.size() == capacity) {
            // Evict LRU
            auto& lru = cacheList.back();
            cacheMap.erase(lru.first);
            cacheList.pop_back();
        }
        
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
}

// ============================================================================
// Approach 3: Circular Buffer with Time Stamps (Alternative Design)
// ============================================================================

LRUCacheCircular::LRUCacheCircular(int capacity) 
    : capacity(capacity), currentTime(0), buffer(capacity) {}

int LRUCacheCircular::findLRUIndex() {
    int lruIndex = 0;
    int minTime = INT_MAX;
    
    for (int i = 0; i < capacity; i++) {
        if (!buffer[i].valid) {
            return i;  // Found empty slot
        }
        if (buffer[i].timestamp < minTime) {
            minTime = buffer[i].timestamp;
            lruIndex = i;
        }
    }
    
    return lruIndex;
}

int LRUCacheCircular::get(int key) {
    auto it = keyToIndex.find(key);
    if (it == keyToIndex.end()) {
        return -1;
    }
    
    int index = it->second;
    buffer[index].timestamp = ++currentTime;
    return buffer[index].value;
}

void LRUCacheCircular::put(int key, int value) {
    auto it = keyToIndex.find(key);
    
    if (it != keyToIndex.end()) {
        // Update existing key
        int index = it->second;
        buffer[index].value = value;
        buffer[index].timestamp = ++currentTime;
    } else {
        // Add new key
        int index = findLRUIndex();
        
        // Remove old key if replacing
        if (buffer[index].valid) {
            keyToIndex.erase(buffer[index].key);
        }
        
        buffer[index].key = key;
        buffer[index].value = value;
        buffer[index].timestamp = ++currentTime;
        buffer[index].valid = true;
        keyToIndex[key] = index;
    }
}

// ============================================================================
// Approach 4: LinkedHashMap-style Implementation (Ordered Map)
// ============================================================================

LRUCacheLinkedHashMap::LRUCacheLinkedHashMap(int capacity) 
    : capacity(capacity), size(0), bucketCount(capacity) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    tail->prev = head;
    buckets.resize(bucketCount, nullptr);
}

LRUCacheLinkedHashMap::~LRUCacheLinkedHashMap() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int LRUCacheLinkedHashMap::hash(int key) {
    return key % bucketCount;
}

void LRUCacheLinkedHashMap::addToHead(Node* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

void LRUCacheLinkedHashMap::removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

LRUCacheLinkedHashMap::Node* LRUCacheLinkedHashMap::findNode(int key) {
    int index = hash(key);
    Node* current = buckets[index];
    
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->hashNext;
    }
    
    return nullptr;
}

void LRUCacheLinkedHashMap::removeFromBucket(Node* node) {
    int index = hash(node->key);
    
    if (buckets[index] == node) {
        buckets[index] = node->hashNext;
    } else {
        Node* current = buckets[index];
        while (current && current->hashNext != node) {
            current = current->hashNext;
        }
        if (current) {
            current->hashNext = node->hashNext;
        }
    }
    
    node->hashNext = nullptr;
}

void LRUCacheLinkedHashMap::addToBucket(Node* node) {
    int index = hash(node->key);
    node->hashNext = buckets[index];
    buckets[index] = node;
}

int LRUCacheLinkedHashMap::get(int key) {
    Node* node = findNode(key);
    if (!node) {
        return -1;
    }
    
    removeNode(node);
    addToHead(node);
    return node->value;
}

void LRUCacheLinkedHashMap::put(int key, int value) {
    Node* node = findNode(key);
    
    if (node) {
        // Update existing key
        node->value = value;
        removeNode(node);
        addToHead(node);
    } else {
        // Add new key
        Node* newNode = new Node(key, value);
        addToBucket(newNode);
        addToHead(newNode);
        size++;
        
        if (size > capacity) {
            // Evict LRU
            Node* lru = tail->prev;
            removeNode(lru);
            removeFromBucket(lru);
            delete lru;
            size--;
        }
    }
}

// ============================================================================
// Approach 5: Smart Pointers Implementation (Modern C++)
// ============================================================================

LRUCacheSmartPtr::LRUCacheSmartPtr(int capacity) : capacity(capacity), size(0) {
    head = std::make_shared<Node>();
    tail = std::make_shared<Node>();
    head->next = tail;
    tail->prev = head;
}

void LRUCacheSmartPtr::addToHead(std::shared_ptr<Node> node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

void LRUCacheSmartPtr::removeNode(std::shared_ptr<Node> node) {
    auto prevNode = node->prev.lock();
    auto nextNode = node->next;
    
    if (prevNode) {
        prevNode->next = nextNode;
    }
    if (nextNode) {
        nextNode->prev = prevNode;
    }
}

std::shared_ptr<LRUCacheSmartPtr::Node> LRUCacheSmartPtr::removeTail() {
    auto res = tail->prev.lock();
    if (res) {
        removeNode(res);
    }
    return res;
}

void LRUCacheSmartPtr::moveToHead(std::shared_ptr<Node> node) {
    removeNode(node);
    addToHead(node);
}

int LRUCacheSmartPtr::get(int key) {
    auto it = cache.find(key);
    if (it == cache.end()) {
        return -1;
    }
    
    moveToHead(it->second);
    return it->second->value;
}

void LRUCacheSmartPtr::put(int key, int value) {
    auto it = cache.find(key);
    
    if (it != cache.end()) {
        // Update existing key
        it->second->value = value;
        moveToHead(it->second);
    } else {
        // Add new key
        auto newNode = std::make_shared<Node>(key, value);
        cache[key] = newNode;
        addToHead(newNode);
        size++;
        
        if (size > capacity) {
            // Evict LRU
            auto lru = removeTail();
            if (lru) {
                cache.erase(lru->key);
                size--;
            }
        }
    }
}

// ============================================================================
// Approach 6: Deque + Hash Map (Simplified Approach)
// ============================================================================

LRUCacheDeque::LRUCacheDeque(int capacity) : capacity(capacity) {}

void LRUCacheDeque::removeKey(int key) {
    // Mark as invalid in deque (will be cleaned up later)
    for (auto& pair : cacheDeque) {
        if (pair.first == key) {
            pair.first = -1;  // Mark as invalid
        }
    }
}

void LRUCacheDeque::cleanupDeque() {
    // Remove invalid entries from back
    while (!cacheDeque.empty() && cacheDeque.back().first == -1) {
        cacheDeque.pop_back();
    }
    
    // Periodically do full cleanup if too many invalid entries
    int invalidCount = 0;
    for (const auto& pair : cacheDeque) {
        if (pair.first == -1) invalidCount++;
    }
    
    if (invalidCount > capacity / 2) {
        std::deque<std::pair<int, int>> newDeque;
        for (const auto& pair : cacheDeque) {
            if (pair.first != -1) {
                newDeque.push_back(pair);
            }
        }
        cacheDeque = std::move(newDeque);
    }
}

int LRUCacheDeque::get(int key) {
    auto it = cacheMap.find(key);
    if (it == cacheMap.end()) {
        return -1;
    }
    
    int value = it->second;
    
    // Move to front
    removeKey(key);
    cacheDeque.push_front({key, value});
    
    // Cleanup periodically
    if (cacheDeque.size() > capacity * 2) {
        cleanupDeque();
    }
    
    return value;
}

void LRUCacheDeque::put(int key, int value) {
    // Remove if exists
    if (cacheMap.find(key) != cacheMap.end()) {
        removeKey(key);
    }
    
    // Add to front
    cacheDeque.push_front({key, value});
    cacheMap[key] = value;
    
    // Evict if needed
    while (cacheMap.size() > capacity) {
        // Find actual LRU from back
        while (!cacheDeque.empty()) {
            auto& back = cacheDeque.back();
            if (back.first != -1 && back.first != key) {
                cacheMap.erase(back.first);
                cacheDeque.pop_back();
                break;
            }
            cacheDeque.pop_back();
        }
    }
    
    // Cleanup periodically
    if (cacheDeque.size() > capacity * 2) {
        cleanupDeque();
    }
}

}
}