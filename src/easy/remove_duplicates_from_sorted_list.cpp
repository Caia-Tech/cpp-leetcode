#include "remove_duplicates_from_sorted_list.h"

namespace leetcode {
namespace easy {

// Approach 1: Single Pass Iteration (Optimal)
ListNode* RemoveDuplicatesFromSortedList::deleteDuplicatesIterative(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* current = head;
    
    while (current && current->next) {
        if (current->val == current->next->val) {
            // Found duplicate, remove the next node
            ListNode* duplicate = current->next;
            current->next = current->next->next;
            delete duplicate;
        } else {
            // No duplicate, move to next node
            current = current->next;
        }
    }
    
    return head;
}

// Approach 2: Recursive Solution
ListNode* RemoveDuplicatesFromSortedList::deleteDuplicatesRecursive(ListNode* head) {
    if (!head) return nullptr;
    return removeDuplicatesRecursive(head);
}

ListNode* RemoveDuplicatesFromSortedList::removeDuplicatesRecursive(ListNode* node) {
    if (!node || !node->next) return node;
    
    // Recursively process the rest of the list
    node->next = removeDuplicatesRecursive(node->next);
    
    // Check if current node is duplicate with next
    if (node->val == node->next->val) {
        ListNode* duplicate = node->next;
        node->next = node->next->next;
        delete duplicate;
    }
    
    return node;
}

// Approach 3: Two-Pointer Technique
ListNode* RemoveDuplicatesFromSortedList::deleteDuplicatesTwoPointer(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* prev = head;
    ListNode* current = head->next;
    
    while (current) {
        if (prev->val == current->val) {
            // Found duplicate, remove current node
            prev->next = current->next;
            delete current;
            current = prev->next;
        } else {
            // No duplicate, advance both pointers
            prev = current;
            current = current->next;
        }
    }
    
    return head;
}

// Approach 4: Hash Set Tracking (Educational)
ListNode* RemoveDuplicatesFromSortedList::deleteDuplicatesHashSet(ListNode* head) {
    if (!head) return nullptr;
    
    std::unordered_set<int> seen;
    ListNode* current = head;
    ListNode* prev = nullptr;
    
    while (current) {
        if (seen.find(current->val) != seen.end()) {
            // Value already seen, remove this node
            prev->next = current->next;
            delete current;
            current = prev->next;
        } else {
            // First time seeing this value
            seen.insert(current->val);
            prev = current;
            current = current->next;
        }
    }
    
    return head;
}

// Approach 5: Dummy Head with Trailing Pointer
ListNode* RemoveDuplicatesFromSortedList::deleteDuplicatesDummyHead(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    ListNode* current = head;
    
    while (current) {
        if (current->next && current->val == current->next->val) {
            // Found duplicate, skip it
            ListNode* duplicate = current->next;
            current->next = current->next->next;
            delete duplicate;
            // Don't advance prev, as current might have more duplicates
        } else {
            // No duplicate found, advance prev
            prev = current;
            current = current->next;
        }
    }
    
    return dummy.next;
}

// Approach 6: Functional Programming with Lambda
ListNode* RemoveDuplicatesFromSortedList::deleteDuplicatesFunctional(ListNode* head) {
    if (!head) return nullptr;
    
    auto duplicateRemover = createDuplicateRemover();
    return duplicateRemover(head);
}

std::function<ListNode*(ListNode*)> RemoveDuplicatesFromSortedList::createDuplicateRemover() {
    return [](ListNode* head) -> ListNode* {
        if (!head) return nullptr;
        
        // Create a processor function that removes duplicates
        std::function<ListNode*(ListNode*)> processor = [](ListNode* node) -> ListNode* {
            if (!node) return nullptr;
            
            ListNode* current = node;
            
            while (current && current->next) {
                if (current->val == current->next->val) {
                    ListNode* duplicate = current->next;
                    current->next = current->next->next;
                    delete duplicate;
                } else {
                    current = current->next;
                }
            }
            
            return node;
        };
        
        return processor(head);
    };
}

// Helper functions for testing
ListNode* RemoveDuplicatesFromSortedList::createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

std::vector<int> RemoveDuplicatesFromSortedList::listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    
    return result;
}

void RemoveDuplicatesFromSortedList::deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

}  // namespace easy
}  // namespace leetcode