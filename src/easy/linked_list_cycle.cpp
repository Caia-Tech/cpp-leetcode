#include "linked_list_cycle.h"
#include <unordered_set>

namespace leetcode {
namespace easy {

// Approach 1: Floyd's Cycle Detection (Two Pointers) - Optimal
bool LinkedListCycle::hasCycleFloyd(ListNode* head) {
    if (!head || !head->next) {
        return false;
    }
    
    ListNode* slow = head;
    ListNode* fast = head->next;
    
    // Fast pointer moves twice as fast as slow pointer
    // If there's a cycle, they will eventually meet
    while (fast && fast->next) {
        if (slow == fast) {
            return true;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return false;
}

// Approach 2: Hash Set
bool LinkedListCycle::hasCycleHashSet(ListNode* head) {
    std::unordered_set<ListNode*> visited;
    
    ListNode* current = head;
    while (current) {
        // If we've seen this node before, there's a cycle
        if (visited.find(current) != visited.end()) {
            return true;
        }
        visited.insert(current);
        current = current->next;
    }
    
    return false;
}

// Approach 3: Node Marking (Destructive)
bool LinkedListCycle::hasCycleNodeMarking(ListNode* head) {
    if (!head) return false;
    
    std::vector<int> original_values;
    ListNode* current = head;
    
    while (current) {
        // Check if this node has been marked
        if (current->val == SENTINEL) {
            // Restore original values before returning
            restoreNodes(head, original_values);
            return true;
        }
        
        // Store original value and mark the node
        original_values.push_back(current->val);
        current->val = SENTINEL;
        current = current->next;
    }
    
    // Restore original values
    restoreNodes(head, original_values);
    return false;
}

// Approach 4: Try-Catch with Timeout (Counter-based)
bool LinkedListCycle::hasCycleCounter(ListNode* head) {
    if (!head) return false;
    
    const int MAX_NODES = 10001;  // Based on problem constraint
    int count = 0;
    ListNode* current = head;
    
    while (current) {
        if (++count > MAX_NODES) {
            // We've traversed more nodes than possible without a cycle
            return true;
        }
        current = current->next;
    }
    
    return false;
}

// Approach 5: Reverse Detection
bool LinkedListCycle::hasCycleReverse(ListNode* head) {
    if (!head || !head->next) return false;
    
    ListNode* original_head = head;
    ListNode* prev = nullptr;
    ListNode* current = head;
    int node_count = 0;
    const int MAX_ITERATIONS = 10001;
    
    // Reverse the list while checking for cycle
    while (current && node_count < MAX_ITERATIONS) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        node_count++;
        
        // If we've come back to the original head, there's a cycle
        if (prev == original_head && node_count > 1) {
            // Restore the list (reverse again)
            current = prev;
            prev = nullptr;
            while (current && node_count-- > 0) {
                ListNode* next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            return true;
        }
    }
    
    // Check if we exceeded max iterations (indicates cycle)
    bool has_cycle = (node_count >= MAX_ITERATIONS);
    
    // Restore the list (reverse back)
    current = prev;
    prev = nullptr;
    while (current && node_count-- > 0) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return has_cycle;
}

// Approach 6: Brent's Algorithm (Optimized Floyd)
bool LinkedListCycle::hasCycleBrent(ListNode* head) {
    if (!head || !head->next) return false;
    
    ListNode* slow = head;
    ListNode* fast = head->next;
    int power = 1;
    int lambda = 1;  // Proposed cycle length
    
    // First phase: find if cycle exists
    while (fast && fast != slow) {
        if (lambda == power) {
            // Move slow pointer to fast pointer's position
            slow = fast;
            power *= 2;
            lambda = 0;
        }
        fast = fast->next;
        lambda++;
    }
    
    // If fast became null, no cycle
    return fast != nullptr;
}

// Helper to restore marked nodes
void LinkedListCycle::restoreNodes(ListNode* head, const std::vector<int>& original_values) {
    ListNode* current = head;
    size_t index = 0;
    
    while (current && index < original_values.size()) {
        if (current->val == SENTINEL) {
            current->val = original_values[index];
        }
        current = current->next;
        index++;
    }
}

}  // namespace easy
}  // namespace leetcode