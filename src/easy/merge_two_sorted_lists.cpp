#include "merge_two_sorted_lists.h"
#include <queue>
#include <vector>
#include <algorithm>

namespace leetcode {
namespace easy {

ListNode* MergeTwoSortedLists::mergeTwoListsIterative(ListNode* list1, ListNode* list2) {
    // Create dummy head to simplify edge cases
    ListNode dummy(0);
    ListNode* current = &dummy;
    
    // Compare and merge while both lists have nodes
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }
    
    // Append remaining nodes (at most one list will have remaining nodes)
    current->next = list1 ? list1 : list2;
    
    return dummy.next;
}

ListNode* MergeTwoSortedLists::mergeTwoListsRecursive(ListNode* list1, ListNode* list2) {
    // Base cases: if one list is empty, return the other
    if (!list1) return list2;
    if (!list2) return list1;
    
    // Recursive case: choose smaller head and recursively merge the rest
    if (list1->val <= list2->val) {
        list1->next = mergeTwoListsRecursive(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoListsRecursive(list1, list2->next);
        return list2;
    }
}

ListNode* MergeTwoSortedLists::mergeTwoListsInPlace(ListNode* list1, ListNode* list2) {
    // Handle edge cases first
    if (!list1) return list2;
    if (!list2) return list1;
    
    // Determine the head of the result
    ListNode* head;
    ListNode* prev;
    
    if (list1->val <= list2->val) {
        head = list1;
        prev = list1;
        list1 = list1->next;
    } else {
        head = list2;
        prev = list2;
        list2 = list2->next;
    }
    
    // Merge the remaining nodes
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            prev->next = list1;
            prev = list1;
            list1 = list1->next;
        } else {
            prev->next = list2;
            prev = list2;
            list2 = list2->next;
        }
    }
    
    // Append remaining nodes
    prev->next = list1 ? list1 : list2;
    
    return head;
}

ListNode* MergeTwoSortedLists::mergeTwoListsArray(ListNode* list1, ListNode* list2) {
    // Convert linked lists to arrays
    std::vector<int> arr1 = listToArray(list1);
    std::vector<int> arr2 = listToArray(list2);
    
    // Merge arrays
    std::vector<int> merged = mergeArrays(arr1, arr2);
    
    // Convert back to linked list
    return arrayToList(merged);
}

std::vector<int> MergeTwoSortedLists::listToArray(ListNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

ListNode* MergeTwoSortedLists::arrayToList(const std::vector<int>& arr) {
    if (arr.empty()) return nullptr;
    
    ListNode* head = new ListNode(arr[0]);
    ListNode* current = head;
    
    for (int i = 1; i < arr.size(); ++i) {
        current->next = new ListNode(arr[i]);
        current = current->next;
    }
    
    return head;
}

std::vector<int> MergeTwoSortedLists::mergeArrays(const std::vector<int>& arr1, 
                                                  const std::vector<int>& arr2) {
    std::vector<int> result;
    result.reserve(arr1.size() + arr2.size());
    
    int i = 0, j = 0;
    
    // Merge while both arrays have elements
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] <= arr2[j]) {
            result.push_back(arr1[i++]);
        } else {
            result.push_back(arr2[j++]);
        }
    }
    
    // Add remaining elements
    while (i < arr1.size()) {
        result.push_back(arr1[i++]);
    }
    while (j < arr2.size()) {
        result.push_back(arr2[j++]);
    }
    
    return result;
}

ListNode* MergeTwoSortedLists::mergeTwoListsPriorityQueue(ListNode* list1, ListNode* list2) {
    // Use min-heap to always get smallest node
    std::priority_queue<ListNode*, std::vector<ListNode*>, NodeCompare> pq;
    
    // Add initial nodes to heap (if they exist)
    if (list1) pq.push(list1);
    if (list2) pq.push(list2);
    
    if (pq.empty()) return nullptr;
    
    ListNode dummy(0);
    ListNode* current = &dummy;
    
    while (!pq.empty()) {
        // Get the smallest node
        ListNode* smallest = pq.top();
        pq.pop();
        
        // Add it to result
        current->next = smallest;
        current = current->next;
        
        // Add the next node from the same list to heap
        if (smallest->next) {
            pq.push(smallest->next);
        }
    }
    
    return dummy.next;
}

ListNode* MergeTwoSortedLists::mergeTwoListsSentinel(ListNode* list1, ListNode* list2) {
    // Use sentinel node and maintain tail pointer
    ListNode sentinel(0);
    ListNode* tail = &sentinel;
    
    // Merge while both lists have nodes
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;  // Update tail pointer
    }
    
    // Append remaining nodes (if any)
    tail->next = list1 ? list1 : list2;
    
    return sentinel.next;
}

}
}