#include "delete_node_in_linked_list.h"

namespace leetcode {
namespace easy {

// Approach 1: Copy Next Node Value (Optimal)
void DeleteNodeInLinkedList::deleteNodeCopyNext(ListNode* node) {
    if (!node || !node->next) return;  // Should not happen per constraints
    
    // Copy the next node's value to current node
    node->val = node->next->val;
    
    // Delete the next node
    ListNode* nodeToDelete = node->next;
    node->next = node->next->next;
    delete nodeToDelete;
}

// Approach 2: Shift All Values Left
void DeleteNodeInLinkedList::deleteNodeShiftValues(ListNode* node) {
    if (!node || !node->next) return;  // Should not happen per constraints
    
    ListNode* current = node;
    
    // Shift all values to the left
    while (current->next && current->next->next) {
        current->val = current->next->val;
        current = current->next;
    }
    
    // Handle the last two nodes
    if (current->next) {
        current->val = current->next->val;
        ListNode* lastNode = current->next;
        current->next = nullptr;
        delete lastNode;
    }
}

// Approach 3: Mark and Compact
void DeleteNodeInLinkedList::deleteNodeMarkAndCompact(ListNode* node) {
    if (!node || !node->next) return;  // Should not happen per constraints
    
    // Since we can't actually "mark" without changing values, 
    // we'll use a different strategy: collect all values except the target
    std::vector<int> validValues;
    ListNode* current = node->next;  // Start from next node
    
    // Collect all values after the target node
    while (current) {
        validValues.push_back(current->val);
        current = current->next;
    }
    
    // Now overwrite starting from the target node
    current = node;
    for (size_t i = 0; i < validValues.size(); ++i) {
        current->val = validValues[i];
        if (i == validValues.size() - 1) {
            // This is the last valid value, need to remove the next node
            ListNode* nodeToDelete = current->next;
            current->next = current->next ? current->next->next : nullptr;
            delete nodeToDelete;
        } else {
            current = current->next;
        }
    }
}

// Approach 4: Recursive Value Propagation
void DeleteNodeInLinkedList::deleteNodeRecursive(ListNode* node) {
    if (!node || !node->next) return;  // Should not happen per constraints
    
    deleteNodeRecursiveHelper(node, node);
}

int DeleteNodeInLinkedList::deleteNodeRecursiveHelper(ListNode* current, ListNode* target) {
    if (!current) return 0;  // Should not reach here
    
    if (current == target) {
        // Found the target node - copy next node's value and delete next node
        if (!current->next) return 0;  // Should not happen per constraints
        
        int nextValue = current->next->val;
        ListNode* nodeToDelete = current->next;
        current->next = current->next->next;
        delete nodeToDelete;
        
        current->val = nextValue;
        return nextValue;
    }
    
    // Not the target, continue recursively
    return deleteNodeRecursiveHelper(current->next, target);
}

// Approach 5: Two-Pointer Technique
void DeleteNodeInLinkedList::deleteNodeTwoPointers(ListNode* node) {
    if (!node || !node->next) return;  // Should not happen per constraints
    
    ListNode* writePtr = node;        // Points to where we write values
    ListNode* readPtr = node->next;   // Points to where we read values
    
    // Copy values from readPtr to writePtr
    while (readPtr && readPtr->next) {
        writePtr->val = readPtr->val;
        writePtr = writePtr->next;
        readPtr = readPtr->next;
    }
    
    // Handle the last node
    if (readPtr) {
        writePtr->val = readPtr->val;
        writePtr->next = nullptr;
        delete readPtr;
    }
}

// Approach 6: Functional Style with Lambda
void DeleteNodeInLinkedList::deleteNodeFunctional(ListNode* node) {
    auto deleter = createNodeDeleter();
    deleter(node);
}

std::function<void(ListNode*)> DeleteNodeInLinkedList::createNodeDeleter() {
    return [](ListNode* node) -> void {
        if (!node || !node->next) return;
        
        // Create a lambda for the deletion strategy
        auto copyNextStrategy = [](ListNode* target) -> void {
            target->val = target->next->val;
            ListNode* nodeToDelete = target->next;
            target->next = target->next->next;
            delete nodeToDelete;
        };
        
        // Create a validator lambda
        auto isValidTarget = [](ListNode* target) -> bool {
            return target && target->next;  // Must have a next node
        };
        
        // Apply the strategy if valid
        if (isValidTarget(node)) {
            copyNextStrategy(node);
        }
    };
}

// Helper functions for testing
ListNode* DeleteNodeInLinkedList::createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

std::vector<int> DeleteNodeInLinkedList::listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    
    return result;
}

void DeleteNodeInLinkedList::deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

ListNode* DeleteNodeInLinkedList::findNode(ListNode* head, int value) {
    ListNode* current = head;
    while (current) {
        if (current->val == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

}  // namespace easy
}  // namespace leetcode