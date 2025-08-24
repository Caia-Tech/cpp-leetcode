#include "remove_linked_list_elements.h"

namespace leetcode {
namespace easy {

// Approach 1: Iterative with Dummy Head (Optimal)
ListNode* RemoveLinkedListElements::removeElementsIterativeDummy(ListNode* head, int val) {
    // Create dummy head to simplify edge cases
    ListNode dummy(0);
    dummy.next = head;
    
    ListNode* prev = &dummy;
    ListNode* current = head;
    
    while (current) {
        if (current->val == val) {
            // Remove current node
            prev->next = current->next;
            delete current;
            current = prev->next;
        } else {
            // Keep current node, advance both pointers
            prev = current;
            current = current->next;
        }
    }
    
    return dummy.next;
}

// Approach 2: Iterative without Dummy Head
ListNode* RemoveLinkedListElements::removeElementsIterativeNoDummy(ListNode* head, int val) {
    // Handle head removal first
    while (head && head->val == val) {
        ListNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    
    if (!head) return nullptr;
    
    // Process the rest of the list
    ListNode* current = head;
    while (current->next) {
        if (current->next->val == val) {
            ListNode* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        } else {
            current = current->next;
        }
    }
    
    return head;
}

// Approach 3: Recursive Solution
ListNode* RemoveLinkedListElements::removeElementsRecursive(ListNode* head, int val) {
    return removeElementsRecursiveHelper(head, val);
}

ListNode* RemoveLinkedListElements::removeElementsRecursiveHelper(ListNode* node, int val) {
    if (!node) return nullptr;
    
    // Recursively process the rest of the list
    node->next = removeElementsRecursiveHelper(node->next, val);
    
    // Decide whether to keep current node
    if (node->val == val) {
        ListNode* toDelete = node;
        ListNode* result = node->next;
        delete toDelete;
        return result;
    }
    
    return node;
}

// Approach 4: Stack-Based Processing
ListNode* RemoveLinkedListElements::removeElementsStack(ListNode* head, int val) {
    if (!head) return nullptr;
    
    std::stack<ListNode*> nodeStack;
    
    // Collect nodes that should be kept
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        if (current->val != val) {
            current->next = nullptr;  // Disconnect for clean rebuilding
            nodeStack.push(current);
        } else {
            delete current;
        }
        current = next;
    }
    
    if (nodeStack.empty()) return nullptr;
    
    // Rebuild list from stack (this reverses the order, so we need to fix it)
    std::vector<ListNode*> nodes;
    while (!nodeStack.empty()) {
        nodes.push_back(nodeStack.top());
        nodeStack.pop();
    }
    
    // Connect nodes in correct order
    for (int i = static_cast<int>(nodes.size()) - 1; i > 0; --i) {
        nodes[i]->next = nodes[i - 1];
    }
    
    return nodes.back();  // Return the original first node
}

// Approach 5: Two-Pass Solution
ListNode* RemoveLinkedListElements::removeElementsTwoPass(ListNode* head, int val) {
    if (!head) return nullptr;
    
    // First pass: count remaining nodes
    int remainingCount = 0;
    ListNode* current = head;
    while (current) {
        if (current->val != val) {
            remainingCount++;
        }
        current = current->next;
    }
    
    if (remainingCount == 0) {
        // Delete all nodes and return null
        deleteList(head);
        return nullptr;
    }
    
    // Second pass: build new list
    ListNode* newHead = nullptr;
    ListNode* newTail = nullptr;
    
    current = head;
    while (current) {
        if (current->val != val) {
            ListNode* newNode = new ListNode(current->val);
            if (!newHead) {
                newHead = newNode;
                newTail = newNode;
            } else {
                newTail->next = newNode;
                newTail = newNode;
            }
        }
        current = current->next;
    }
    
    // Delete original list
    deleteList(head);
    
    return newHead;
}

// Approach 6: Functional Programming with Lambda
ListNode* RemoveLinkedListElements::removeElementsFunctional(ListNode* head, int val) {
    auto elementRemover = createElementRemover();
    return elementRemover(head, val);
}

std::function<ListNode*(ListNode*, int)> RemoveLinkedListElements::createElementRemover() {
    return [](ListNode* head, int val) -> ListNode* {
        // Create a filter predicate
        auto shouldKeep = [val](const ListNode* node) {
            return node && node->val != val;
        };
        
        // Create processor function
        std::function<ListNode*(ListNode*)> processor = [val, shouldKeep](ListNode* node) -> ListNode* {
            if (!node) return nullptr;
            
            ListNode dummy(0);
            ListNode* prev = &dummy;
            ListNode* current = node;
            
            while (current) {
                if (shouldKeep(current)) {
                    prev->next = current;
                    prev = current;
                    current = current->next;
                } else {
                    ListNode* toDelete = current;
                    current = current->next;
                    delete toDelete;
                }
            }
            
            prev->next = nullptr;  // Ensure proper termination
            return dummy.next;
        };
        
        return processor(head);
    };
}

// Helper functions for testing
ListNode* RemoveLinkedListElements::createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

std::vector<int> RemoveLinkedListElements::listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    
    return result;
}

void RemoveLinkedListElements::deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

}  // namespace easy
}  // namespace leetcode