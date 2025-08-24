#include <gtest/gtest.h>
#include "../../src/easy/linked_list_cycle.h"
#include "../../src/utils/test_utils.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

using utils::ListNode;

class LinkedListCycleTest : public ::testing::Test {
protected:
    // Helper to create a linked list with optional cycle
    ListNode* createList(const std::vector<int>& values, int cycle_pos = -1) {
        if (values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        ListNode* current = head;
        ListNode* cycle_node = nullptr;
        
        if (cycle_pos == 0) {
            cycle_node = head;
        }
        
        for (size_t i = 1; i < values.size(); ++i) {
            current->next = new ListNode(values[i]);
            current = current->next;
            
            if (static_cast<int>(i) == cycle_pos) {
                cycle_node = current;
            }
        }
        
        // Create cycle if specified
        if (cycle_pos >= 0 && cycle_node) {
            current->next = cycle_node;
        }
        
        return head;
    }
    
    // Helper to safely delete a list (handles cycles)
    void deleteList(ListNode* head) {
        if (!head) return;
        
        std::unordered_set<ListNode*> visited;
        ListNode* current = head;
        
        while (current && visited.find(current) == visited.end()) {
            visited.insert(current);
            ListNode* next = current->next;
            
            // Only delete if next is not in visited (to handle cycles)
            if (visited.find(next) == visited.end()) {
                current = next;
            } else {
                break;
            }
        }
        
        // Delete all visited nodes
        for (ListNode* node : visited) {
            delete node;
        }
    }
    
    // Test all approaches with the same input
    void testAllApproaches(ListNode* head, bool expected) {
        LinkedListCycle solution;
        
        // Store original list structure for restoration between tests
        std::vector<ListNode*> nodes;
        std::vector<ListNode*> nexts;
        ListNode* current = head;
        std::unordered_set<ListNode*> visited;
        
        while (current && visited.find(current) == visited.end()) {
            visited.insert(current);
            nodes.push_back(current);
            nexts.push_back(current->next);
            current = current->next;
        }
        
        // Test each approach
        EXPECT_EQ(solution.hasCycleFloyd(head), expected) 
            << "Floyd's algorithm failed";
        
        EXPECT_EQ(solution.hasCycleHashSet(head), expected) 
            << "Hash set approach failed";
        
        EXPECT_EQ(solution.hasCycleNodeMarking(head), expected) 
            << "Node marking approach failed";
        
        EXPECT_EQ(solution.hasCycleCounter(head), expected) 
            << "Counter approach failed";
        
        // Skip reverse approach for cyclic lists as it's destructive
        if (!expected) {
            EXPECT_EQ(solution.hasCycleReverse(head), expected) 
                << "Reverse detection approach failed";
        }
        
        EXPECT_EQ(solution.hasCycleBrent(head), expected) 
            << "Brent's algorithm failed";
    }
};

// LeetCode Example Test Cases

TEST_F(LinkedListCycleTest, LeetCodeExample1) {
    // head = [3,2,0,-4], pos = 1
    // Creates cycle where tail connects to node index 1
    ListNode* head = createList({3, 2, 0, -4}, 1);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, LeetCodeExample2) {
    // head = [1,2], pos = 0
    // Creates cycle where tail connects to node index 0
    ListNode* head = createList({1, 2}, 0);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, LeetCodeExample3) {
    // head = [1], pos = -1
    // No cycle
    ListNode* head = createList({1}, -1);
    testAllApproaches(head, false);
    deleteList(head);
}

// Edge Cases

TEST_F(LinkedListCycleTest, EmptyList) {
    testAllApproaches(nullptr, false);
}

TEST_F(LinkedListCycleTest, SingleNodeNoCycle) {
    ListNode* head = createList({1}, -1);
    testAllApproaches(head, false);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, SingleNodeWithCycle) {
    // Single node pointing to itself
    ListNode* head = createList({1}, 0);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, TwoNodesNoCycle) {
    ListNode* head = createList({1, 2}, -1);
    testAllApproaches(head, false);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, TwoNodesCycleToFirst) {
    ListNode* head = createList({1, 2}, 0);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, TwoNodesCycleToSecond) {
    ListNode* head = createList({1, 2}, 1);
    testAllApproaches(head, true);
    deleteList(head);
}

// Various Cycle Positions

TEST_F(LinkedListCycleTest, CycleAtBeginning) {
    // Cycle starts at the head
    ListNode* head = createList({1, 2, 3, 4, 5}, 0);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, CycleInMiddle) {
    // Cycle starts in the middle
    ListNode* head = createList({1, 2, 3, 4, 5}, 2);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, CycleAtEnd) {
    // Cycle at the last node (points to itself)
    ListNode* head = createList({1, 2, 3, 4, 5}, 4);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, LongListNoCycle) {
    std::vector<int> values;
    for (int i = 0; i < 100; ++i) {
        values.push_back(i);
    }
    ListNode* head = createList(values, -1);
    testAllApproaches(head, false);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, LongListWithCycle) {
    std::vector<int> values;
    for (int i = 0; i < 100; ++i) {
        values.push_back(i);
    }
    // Create cycle from last node to middle
    ListNode* head = createList(values, 50);
    testAllApproaches(head, true);
    deleteList(head);
}

// Special Patterns

TEST_F(LinkedListCycleTest, AllSameValues) {
    // All nodes have same value but different memory addresses
    ListNode* head = createList({5, 5, 5, 5, 5}, 2);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, NegativeValues) {
    ListNode* head = createList({-1, -2, -3, -4}, 1);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, MixedValues) {
    ListNode* head = createList({-10, 0, 10, -5, 5}, 3);
    testAllApproaches(head, true);
    deleteList(head);
}

// Maximum Constraint Tests

TEST_F(LinkedListCycleTest, MinimumValueNodes) {
    // Nodes with minimum constraint value
    ListNode* head = createList({-100000, -100000, -100000}, 1);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, MaximumValueNodes) {
    // Nodes with maximum constraint value
    ListNode* head = createList({100000, 100000, 100000}, 2);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, AlternatingValues) {
    ListNode* head = createList({1, -1, 1, -1, 1}, -1);
    testAllApproaches(head, false);
    deleteList(head);
}

// Large Cycle Tests

TEST_F(LinkedListCycleTest, SmallCycleLargeTail) {
    // Long list with small cycle at the end
    std::vector<int> values;
    for (int i = 0; i < 50; ++i) {
        values.push_back(i);
    }
    ListNode* head = createList(values, 45);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, LargeCycleSmallTail) {
    // Short tail leading to large cycle
    std::vector<int> values;
    for (int i = 0; i < 50; ++i) {
        values.push_back(i);
    }
    ListNode* head = createList(values, 5);
    testAllApproaches(head, true);
    deleteList(head);
}

TEST_F(LinkedListCycleTest, EntireLisIsCycle) {
    // Entire list forms a cycle
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ListNode* head = createList(values, 0);
    testAllApproaches(head, true);
    deleteList(head);
}

// Performance Edge Cases

TEST_F(LinkedListCycleTest, MaximumSizeListNoCycle) {
    // Test with maximum constraint size (10000 nodes)
    std::vector<int> values;
    for (int i = 0; i < 10000; ++i) {
        values.push_back(i % 1000);
    }
    ListNode* head = createList(values, -1);
    
    LinkedListCycle solution;
    EXPECT_FALSE(solution.hasCycleFloyd(head));
    EXPECT_FALSE(solution.hasCycleHashSet(head));
    EXPECT_FALSE(solution.hasCycleBrent(head));
    
    deleteList(head);
}

TEST_F(LinkedListCycleTest, MaximumSizeListWithCycle) {
    // Large list with cycle
    std::vector<int> values;
    for (int i = 0; i < 1000; ++i) {
        values.push_back(i);
    }
    ListNode* head = createList(values, 500);
    
    LinkedListCycle solution;
    EXPECT_TRUE(solution.hasCycleFloyd(head));
    EXPECT_TRUE(solution.hasCycleHashSet(head));
    EXPECT_TRUE(solution.hasCycleBrent(head));
    
    deleteList(head);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode