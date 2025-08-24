#include "intersection_of_two_linked_lists.h"
#include <stack>

namespace leetcode {
namespace easy {

// Approach 1: Two Pointers with Length Alignment (Optimal)
ListNode* IntersectionOfTwoLinkedLists::getIntersectionNodeTwoPointers(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    // Get lengths of both lists
    int lengthA = getListLength(headA);
    int lengthB = getListLength(headB);
    
    // Align the starting positions
    ListNode* ptrA = headA;
    ListNode* ptrB = headB;
    
    if (lengthA > lengthB) {
        ptrA = advanceList(ptrA, lengthA - lengthB);
    } else if (lengthB > lengthA) {
        ptrB = advanceList(ptrB, lengthB - lengthA);
    }
    
    // Traverse both lists simultaneously
    while (ptrA && ptrB) {
        if (ptrA == ptrB) {
            return ptrA;  // Found intersection
        }
        ptrA = ptrA->next;
        ptrB = ptrB->next;
    }
    
    return nullptr;  // No intersection
}

// Approach 2: Hash Set for Node Tracking
ListNode* IntersectionOfTwoLinkedLists::getIntersectionNodeHashSet(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    std::unordered_set<ListNode*> visitedNodes;
    
    // Store all nodes from list A
    ListNode* current = headA;
    while (current) {
        visitedNodes.insert(current);
        current = current->next;
    }
    
    // Check if any node from list B exists in the set
    current = headB;
    while (current) {
        if (visitedNodes.find(current) != visitedNodes.end()) {
            return current;  // Found intersection
        }
        current = current->next;
    }
    
    return nullptr;  // No intersection
}

// Approach 3: Clever Two Pointers (Mathematical)
ListNode* IntersectionOfTwoLinkedLists::getIntersectionNodeCleverTwoPointers(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    ListNode* ptrA = headA;
    ListNode* ptrB = headB;
    
    // Continue until they meet or both become null
    while (ptrA != ptrB) {
        // When reaching end, switch to the other list's head
        ptrA = (ptrA == nullptr) ? headB : ptrA->next;
        ptrB = (ptrB == nullptr) ? headA : ptrB->next;
    }
    
    return ptrA;  // Either intersection node or null
}

// Approach 4: Stack-Based Comparison
ListNode* IntersectionOfTwoLinkedLists::getIntersectionNodeStack(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    std::stack<ListNode*> stackA, stackB;
    
    // Push all nodes from list A onto stack
    ListNode* current = headA;
    while (current) {
        stackA.push(current);
        current = current->next;
    }
    
    // Push all nodes from list B onto stack
    current = headB;
    while (current) {
        stackB.push(current);
        current = current->next;
    }
    
    ListNode* intersection = nullptr;
    
    // Pop from both stacks and compare
    while (!stackA.empty() && !stackB.empty()) {
        ListNode* nodeA = stackA.top();
        ListNode* nodeB = stackB.top();
        stackA.pop();
        stackB.pop();
        
        if (nodeA == nodeB) {
            intersection = nodeA;
        } else {
            break;  // Found the last common node
        }
    }
    
    return intersection;
}

// Approach 5: Mark and Restore Technique
ListNode* IntersectionOfTwoLinkedLists::getIntersectionNodeMarkAndRestore(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    // Find the tail of list A
    ListNode* tailA = headA;
    while (tailA->next) {
        tailA = tailA->next;
    }
    
    // Create a cycle by connecting tail of A to head of A
    tailA->next = headA;
    
    // Detect cycle start in list B (which would be the intersection)
    ListNode* intersection = detectCycleStart(headB);
    
    // Restore original structure
    tailA->next = nullptr;
    
    return intersection;
}

// Approach 6: Functional Programming with Lambda
ListNode* IntersectionOfTwoLinkedLists::getIntersectionNodeFunctional(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    auto intersectionFinder = createIntersectionFinder();
    return intersectionFinder(headA, headB);
}

// Helper function implementations
int IntersectionOfTwoLinkedLists::getListLength(ListNode* head) {
    int length = 0;
    while (head) {
        length++;
        head = head->next;
    }
    return length;
}

ListNode* IntersectionOfTwoLinkedLists::advanceList(ListNode* head, int steps) {
    while (steps > 0 && head) {
        head = head->next;
        steps--;
    }
    return head;
}

ListNode* IntersectionOfTwoLinkedLists::detectCycleStart(ListNode* head) {
    if (!head || !head->next) return nullptr;
    
    // Floyd's cycle detection
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Detect if cycle exists
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    if (!fast || !fast->next) return nullptr;  // No cycle
    
    // Find cycle start
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}

std::function<ListNode*(ListNode*, ListNode*)> IntersectionOfTwoLinkedLists::createIntersectionFinder() {
    return [this](ListNode* headA, ListNode* headB) -> ListNode* {
        // Use the clever two pointers approach within the lambda
        if (!headA || !headB) return nullptr;
        
        ListNode* ptrA = headA;
        ListNode* ptrB = headB;
        
        while (ptrA != ptrB) {
            ptrA = (ptrA == nullptr) ? headB : ptrA->next;
            ptrB = (ptrB == nullptr) ? headA : ptrB->next;
        }
        
        return ptrA;
    };
}

// Testing helper functions
ListNode* IntersectionOfTwoLinkedLists::createIntersectedLists(
    const std::vector<int>& listA, 
    const std::vector<int>& listB,
    const std::vector<int>& intersection,
    ListNode*& headA, 
    ListNode*& headB) {
    
    // Create intersection part first
    ListNode* intersectionHead = nullptr;
    ListNode* intersectionTail = nullptr;
    
    if (!intersection.empty()) {
        intersectionHead = new ListNode(intersection[0]);
        intersectionTail = intersectionHead;
        
        for (size_t i = 1; i < intersection.size(); ++i) {
            intersectionTail->next = new ListNode(intersection[i]);
            intersectionTail = intersectionTail->next;
        }
    }
    
    // Create list A
    headA = nullptr;
    ListNode* tailA = nullptr;
    
    for (int val : listA) {
        ListNode* newNode = new ListNode(val);
        if (!headA) {
            headA = newNode;
            tailA = newNode;
        } else {
            tailA->next = newNode;
            tailA = newNode;
        }
    }
    
    // Connect list A to intersection
    if (tailA && intersectionHead) {
        tailA->next = intersectionHead;
    } else if (!headA && intersectionHead) {
        headA = intersectionHead;
    }
    
    // Create list B
    headB = nullptr;
    ListNode* tailB = nullptr;
    
    for (int val : listB) {
        ListNode* newNode = new ListNode(val);
        if (!headB) {
            headB = newNode;
            tailB = newNode;
        } else {
            tailB->next = newNode;
            tailB = newNode;
        }
    }
    
    // Connect list B to intersection
    if (tailB && intersectionHead) {
        tailB->next = intersectionHead;
    } else if (!headB && intersectionHead) {
        headB = intersectionHead;
    }
    
    return intersectionHead;
}

void IntersectionOfTwoLinkedLists::deleteIntersectedLists(ListNode* headA, ListNode* headB, ListNode* intersection) {
    // Delete unique part of list A
    ListNode* current = headA;
    while (current && current != intersection) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    
    // Delete unique part of list B
    current = headB;
    while (current && current != intersection) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    
    // Delete intersection part
    current = intersection;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

std::vector<int> IntersectionOfTwoLinkedLists::listToVector(ListNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

void IntersectionOfTwoLinkedLists::deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

}  // namespace easy
}  // namespace leetcode