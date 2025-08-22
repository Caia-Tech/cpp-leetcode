#include <gtest/gtest.h>
#include "../../src/medium/lru_cache.h"
#include <vector>
#include <unordered_set>

namespace leetcode {
namespace medium {
namespace test {

class LRUCacheTest : public ::testing::Test {
protected:
    // Helper function to test basic operations
    template<typename CacheType>
    void testBasicOperations() {
        CacheType cache(2);
        
        cache.put(1, 1);
        cache.put(2, 2);
        EXPECT_EQ(cache.get(1), 1);
        
        cache.put(3, 3);  // Evicts key 2
        EXPECT_EQ(cache.get(2), -1);
        
        cache.put(4, 4);  // Evicts key 1
        EXPECT_EQ(cache.get(1), -1);
        EXPECT_EQ(cache.get(3), 3);
        EXPECT_EQ(cache.get(4), 4);
    }
    
    // Helper function to test LeetCode example
    template<typename CacheType>
    void testLeetCodeExample() {
        CacheType lRUCache(2);
        
        lRUCache.put(1, 1);
        lRUCache.put(2, 2);
        EXPECT_EQ(lRUCache.get(1), 1);
        
        lRUCache.put(3, 3);  // LRU key was 2, evicts key 2
        EXPECT_EQ(lRUCache.get(2), -1);
        
        lRUCache.put(4, 4);  // LRU key was 1, evicts key 1
        EXPECT_EQ(lRUCache.get(1), -1);
        EXPECT_EQ(lRUCache.get(3), 3);
        EXPECT_EQ(lRUCache.get(4), 4);
    }
    
    // Helper function to test update operations
    template<typename CacheType>
    void testUpdateOperations() {
        CacheType cache(2);
        
        cache.put(1, 1);
        cache.put(2, 2);
        cache.put(1, 10);  // Update value of key 1
        EXPECT_EQ(cache.get(1), 10);
        
        cache.put(3, 3);  // Should evict key 2, not key 1
        EXPECT_EQ(cache.get(2), -1);
        EXPECT_EQ(cache.get(1), 10);
    }
    
    // Helper function to test capacity 1
    template<typename CacheType>
    void testCapacityOne() {
        CacheType cache(1);
        
        cache.put(1, 1);
        EXPECT_EQ(cache.get(1), 1);
        
        cache.put(2, 2);
        EXPECT_EQ(cache.get(1), -1);
        EXPECT_EQ(cache.get(2), 2);
        
        cache.put(3, 3);
        EXPECT_EQ(cache.get(2), -1);
        EXPECT_EQ(cache.get(3), 3);
    }
    
    // Helper function to test large capacity
    template<typename CacheType>
    void testLargeCapacity() {
        CacheType cache(100);
        
        // Fill cache
        for (int i = 1; i <= 100; i++) {
            cache.put(i, i * 10);
        }
        
        // All should be present
        for (int i = 1; i <= 100; i++) {
            EXPECT_EQ(cache.get(i), i * 10);
        }
        
        // Add one more, should evict least recently used (which is now 1)
        cache.put(101, 1010);
        EXPECT_EQ(cache.get(1), -1);
        EXPECT_EQ(cache.get(101), 1010);
    }
};

// Test Approach 1: Doubly Linked List + HashMap
TEST_F(LRUCacheTest, DoublyLinkedListBasic) {
    testBasicOperations<LRUCache>();
}

TEST_F(LRUCacheTest, DoublyLinkedListLeetCodeExample) {
    testLeetCodeExample<LRUCache>();
}

TEST_F(LRUCacheTest, DoublyLinkedListUpdate) {
    testUpdateOperations<LRUCache>();
}

TEST_F(LRUCacheTest, DoublyLinkedListCapacityOne) {
    testCapacityOne<LRUCache>();
}

TEST_F(LRUCacheTest, DoublyLinkedListLargeCapacity) {
    testLargeCapacity<LRUCache>();
}

// Test Approach 2: STL Implementation
TEST_F(LRUCacheTest, STLBasic) {
    testBasicOperations<LRUCacheSTL>();
}

TEST_F(LRUCacheTest, STLLeetCodeExample) {
    testLeetCodeExample<LRUCacheSTL>();
}

TEST_F(LRUCacheTest, STLUpdate) {
    testUpdateOperations<LRUCacheSTL>();
}

TEST_F(LRUCacheTest, STLCapacityOne) {
    testCapacityOne<LRUCacheSTL>();
}

TEST_F(LRUCacheTest, STLLargeCapacity) {
    testLargeCapacity<LRUCacheSTL>();
}

// Test Approach 3: Circular Buffer
TEST_F(LRUCacheTest, CircularBasic) {
    testBasicOperations<LRUCacheCircular>();
}

TEST_F(LRUCacheTest, CircularLeetCodeExample) {
    testLeetCodeExample<LRUCacheCircular>();
}

TEST_F(LRUCacheTest, CircularUpdate) {
    testUpdateOperations<LRUCacheCircular>();
}

TEST_F(LRUCacheTest, CircularCapacityOne) {
    testCapacityOne<LRUCacheCircular>();
}

// Test Approach 4: LinkedHashMap
TEST_F(LRUCacheTest, LinkedHashMapBasic) {
    testBasicOperations<LRUCacheLinkedHashMap>();
}

TEST_F(LRUCacheTest, LinkedHashMapLeetCodeExample) {
    testLeetCodeExample<LRUCacheLinkedHashMap>();
}

TEST_F(LRUCacheTest, LinkedHashMapUpdate) {
    testUpdateOperations<LRUCacheLinkedHashMap>();
}

TEST_F(LRUCacheTest, LinkedHashMapCapacityOne) {
    testCapacityOne<LRUCacheLinkedHashMap>();
}

// Test Approach 5: Smart Pointers
TEST_F(LRUCacheTest, SmartPtrBasic) {
    testBasicOperations<LRUCacheSmartPtr>();
}

TEST_F(LRUCacheTest, SmartPtrLeetCodeExample) {
    testLeetCodeExample<LRUCacheSmartPtr>();
}

TEST_F(LRUCacheTest, SmartPtrUpdate) {
    testUpdateOperations<LRUCacheSmartPtr>();
}

TEST_F(LRUCacheTest, SmartPtrCapacityOne) {
    testCapacityOne<LRUCacheSmartPtr>();
}

// Test Approach 6: Deque
TEST_F(LRUCacheTest, DequeBasic) {
    testBasicOperations<LRUCacheDeque>();
}

TEST_F(LRUCacheTest, DequeLeetCodeExample) {
    testLeetCodeExample<LRUCacheDeque>();
}

TEST_F(LRUCacheTest, DequeUpdate) {
    testUpdateOperations<LRUCacheDeque>();
}

TEST_F(LRUCacheTest, DequeCapacityOne) {
    testCapacityOne<LRUCacheDeque>();
}

// Additional edge case tests
TEST_F(LRUCacheTest, GetNonExistent) {
    LRUCache cache(2);
    EXPECT_EQ(cache.get(1), -1);
    
    cache.put(1, 1);
    EXPECT_EQ(cache.get(2), -1);
}

TEST_F(LRUCacheTest, EvictionOrder) {
    LRUCache cache(3);
    
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);
    
    // Access order: 1, 2, 3
    cache.get(1);  // Order now: 2, 3, 1
    cache.get(2);  // Order now: 3, 1, 2
    
    cache.put(4, 4);  // Should evict 3
    EXPECT_EQ(cache.get(3), -1);
    EXPECT_EQ(cache.get(1), 1);
    EXPECT_EQ(cache.get(2), 2);
    EXPECT_EQ(cache.get(4), 4);
}

TEST_F(LRUCacheTest, RepeatedGets) {
    LRUCache cache(2);
    
    cache.put(1, 1);
    cache.put(2, 2);
    
    // Repeated gets shouldn't affect correctness
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(cache.get(1), 1);
    }
    
    cache.put(3, 3);  // Should evict 2, not 1
    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(1), 1);
}

TEST_F(LRUCacheTest, UpdateDoesNotEvict) {
    LRUCache cache(2);
    
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(1, 10);  // Update shouldn't trigger eviction
    
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(2), 2);
}

TEST_F(LRUCacheTest, ZeroKeyValue) {
    LRUCache cache(2);
    
    cache.put(0, 0);
    EXPECT_EQ(cache.get(0), 0);
    
    cache.put(1, 0);
    EXPECT_EQ(cache.get(1), 0);
    
    cache.put(0, 1);
    EXPECT_EQ(cache.get(0), 1);
}

TEST_F(LRUCacheTest, MaxConstraints) {
    // Test with maximum key and value
    LRUCache cache(2);
    
    cache.put(10000, 100000);
    EXPECT_EQ(cache.get(10000), 100000);
    
    cache.put(9999, 99999);
    EXPECT_EQ(cache.get(9999), 99999);
}

TEST_F(LRUCacheTest, ComplexSequence) {
    LRUCache cache(3);
    
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);
    cache.put(4, 4);  // Evicts 1
    
    EXPECT_EQ(cache.get(4), 4);
    EXPECT_EQ(cache.get(3), 3);
    EXPECT_EQ(cache.get(2), 2);
    EXPECT_EQ(cache.get(1), -1);
    
    cache.put(5, 5);  // Evicts 4
    EXPECT_EQ(cache.get(4), -1);
    EXPECT_EQ(cache.get(5), 5);
    
    cache.get(2);  // Move 2 to front
    cache.put(6, 6);  // Should evict 3, not 2
    
    EXPECT_EQ(cache.get(3), -1);
    EXPECT_EQ(cache.get(2), 2);
    EXPECT_EQ(cache.get(5), 5);
    EXPECT_EQ(cache.get(6), 6);
}

TEST_F(LRUCacheTest, PerformanceTest) {
    // Test with many operations
    LRUCache cache(100);
    
    // Fill cache
    for (int i = 0; i < 100; i++) {
        cache.put(i, i);
    }
    
    // Many gets
    for (int j = 0; j < 1000; j++) {
        int key = j % 100;
        EXPECT_EQ(cache.get(key), key);
    }
    
    // Overwrite with new values
    for (int i = 100; i < 200; i++) {
        cache.put(i, i);
    }
    
    // Old values should be evicted
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(cache.get(i), -1);
    }
    
    // New values should be present
    for (int i = 100; i < 200; i++) {
        EXPECT_EQ(cache.get(i), i);
    }
}

// Consistency test across all implementations
TEST_F(LRUCacheTest, ConsistencyAcrossImplementations) {
    std::vector<std::pair<char, std::pair<int, int>>> operations = {
        {'p', {1, 1}}, {'p', {2, 2}}, {'g', {1, 0}}, 
        {'p', {3, 3}}, {'g', {2, 0}}, {'p', {4, 4}},
        {'g', {1, 0}}, {'g', {3, 0}}, {'g', {4, 0}}
    };
    
    LRUCache cache1(2);
    LRUCacheSTL cache2(2);
    LRUCacheCircular cache3(2);
    LRUCacheLinkedHashMap cache4(2);
    LRUCacheSmartPtr cache5(2);
    LRUCacheDeque cache6(2);
    
    std::vector<int> results1, results2, results3, results4, results5, results6;
    
    for (const auto& op : operations) {
        if (op.first == 'p') {
            cache1.put(op.second.first, op.second.second);
            cache2.put(op.second.first, op.second.second);
            cache3.put(op.second.first, op.second.second);
            cache4.put(op.second.first, op.second.second);
            cache5.put(op.second.first, op.second.second);
            cache6.put(op.second.first, op.second.second);
        } else {
            results1.push_back(cache1.get(op.second.first));
            results2.push_back(cache2.get(op.second.first));
            results3.push_back(cache3.get(op.second.first));
            results4.push_back(cache4.get(op.second.first));
            results5.push_back(cache5.get(op.second.first));
            results6.push_back(cache6.get(op.second.first));
        }
    }
    
    // All implementations should give same results
    EXPECT_EQ(results1, results2) << "STL differs from DoublyLinkedList";
    EXPECT_EQ(results1, results3) << "Circular differs from DoublyLinkedList";
    EXPECT_EQ(results1, results4) << "LinkedHashMap differs from DoublyLinkedList";
    EXPECT_EQ(results1, results5) << "SmartPtr differs from DoublyLinkedList";
    EXPECT_EQ(results1, results6) << "Deque differs from DoublyLinkedList";
}

}
}
}