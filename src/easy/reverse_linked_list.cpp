#include "reverse_linked_list.h"
#include <stack>
#include <vector>

namespace leetcode {
namespace easy {

// Approach 1: Iterative with Three Pointers (Optimal)
ListNode* ReverseLinkedList::reverseListIterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    
    while (current != nullptr) {
        // Save next node before we change the link
        ListNode* next_temp = current->next;
        
        // Reverse the link
        current->next = prev;
        
        // Move pointers forward
        prev = current;
        current = next_temp;
    }
    
    // prev is now the new head
    return prev;
}

// Approach 2: Recursive
ListNode* ReverseLinkedList::reverseListRecursive(ListNode* head) {
    return reverseListRecursiveHelper(head);
}

ListNode* ReverseLinkedList::reverseListRecursiveHelper(ListNode* head) {
    // Base case: empty list or single node
    if (!head || !head->next) {
        return head;
    }
    
    // Recursively reverse the rest of the list
    ListNode* new_head = reverseListRecursiveHelper(head->next);
    
    // Put the current node at the end of the reversed list
    // head->next is the last node in the reversed sublist
    head->next->next = head;
    
    // Avoid cycle
    head->next = nullptr;
    
    return new_head;
}

// Approach 3: Using Stack
ListNode* ReverseLinkedList::reverseListStack(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    
    std::stack<ListNode*> node_stack;
    
    // Push all nodes onto the stack
    ListNode* current = head;
    while (current) {
        node_stack.push(current);
        current = current->next;
    }
    
    // Pop from stack to build reversed list
    ListNode* new_head = node_stack.top();
    node_stack.pop();
    current = new_head;
    
    while (!node_stack.empty()) {
        current->next = node_stack.top();
        node_stack.pop();
        current = current->next;
    }
    
    // Make sure the last node points to nullptr
    current->next = nullptr;
    
    return new_head;
}

// Approach 4: Array-Based Reversal
ListNode* ReverseLinkedList::reverseListArray(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    
    // Store all nodes in a vector
    std::vector<ListNode*> nodes;
    ListNode* current = head;
    
    while (current) {
        nodes.push_back(current);
        current = current->next;
    }
    
    // Rebuild connections in reverse order
    int n = nodes.size();
    for (int i = n - 1; i > 0; --i) {
        nodes[i]->next = nodes[i - 1];
    }
    
    // First node becomes last, pointing to nullptr
    nodes[0]->next = nullptr;
    
    // Last node becomes new head
    return nodes[n - 1];
}

// Approach 5: Tail Recursive with Accumulator
ListNode* ReverseLinkedList::reverseListTailRecursive(ListNode* head) {
    return reverseListTailRecursiveHelper(head, nullptr);
}

ListNode* ReverseLinkedList::reverseListTailRecursiveHelper(ListNode* current, ListNode* prev) {
    // Base case: reached end of list
    if (!current) {
        return prev;
    }
    
    // Save next node
    ListNode* next = current->next;
    
    // Reverse current node's pointer
    current->next = prev;
    
    // Tail recursive call with updated pointers
    return reverseListTailRecursiveHelper(next, current);
}

// Approach 6: Two-Pass with Node Value Swapping
ListNode* ReverseLinkedList::reverseListValueSwap(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    
    // First pass: collect all nodes
    std::vector<ListNode*> nodes;
    ListNode* current = head;
    
    while (current) {
        nodes.push_back(current);
        current = current->next;
    }
    
    // Second pass: swap values from both ends
    int left = 0;
    int right = nodes.size() - 1;
    
    while (left < right) {
        // Swap values (not nodes)
        int temp = nodes[left]->val;
        nodes[left]->val = nodes[right]->val;
        nodes[right]->val = temp;
        
        left++;
        right--;
    }
    
    // Return original head (structure unchanged, values swapped)
    return head;
}

}  // namespace easy
}  // namespace leetcode