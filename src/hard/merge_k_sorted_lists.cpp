#include "merge_k_sorted_lists.h"
#include <algorithm>
#include <queue>

namespace leetcode {
namespace hard {

ListNode* MergeKSortedLists::mergeKListsBruteForce(std::vector<ListNode*>& lists) {
    std::vector<int> values;
    
    for (ListNode* list : lists) {
        while (list) {
            values.push_back(list->val);
            list = list->next;
        }
    }
    
    if (values.empty()) return nullptr;
    
    std::sort(values.begin(), values.end());
    
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    
    for (int val : values) {
        current->next = new ListNode(val);
        current = current->next;
    }
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}

ListNode* MergeKSortedLists::mergeKListsHeap(std::vector<ListNode*>& lists) {
    std::priority_queue<ListNode*, std::vector<ListNode*>, Compare> minHeap;
    
    for (ListNode* list : lists) {
        if (list) {
            minHeap.push(list);
        }
    }
    
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    
    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        
        current->next = node;
        current = current->next;
        
        if (node->next) {
            minHeap.push(node->next);
        }
    }
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}

ListNode* MergeKSortedLists::mergeKListsSequential(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    
    ListNode* result = nullptr;
    
    for (ListNode* list : lists) {
        result = mergeTwoLists(result, list);
    }
    
    return result;
}

ListNode* MergeKSortedLists::mergeKListsDivideConquer(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    return mergeHelper(lists, 0, lists.size() - 1);
}

ListNode* MergeKSortedLists::mergeHelper(std::vector<ListNode*>& lists, int left, int right) {
    if (left == right) return lists[left];
    if (left > right) return nullptr;
    
    int mid = left + (right - left) / 2;
    ListNode* l1 = mergeHelper(lists, left, mid);
    ListNode* l2 = mergeHelper(lists, mid + 1, right);
    
    return mergeTwoLists(l1, l2);
}

ListNode* MergeKSortedLists::mergeKListsIterative(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    
    int interval = 1;
    int n = lists.size();
    
    while (interval < n) {
        for (int i = 0; i + interval < n; i += interval * 2) {
            lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
        }
        interval *= 2;
    }
    
    return lists[0];
}

ListNode* MergeKSortedLists::mergeKListsTournament(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    
    std::vector<ListNode*> tournament;
    for (ListNode* list : lists) {
        if (list) {
            tournament.push_back(list);
        }
    }
    
    if (tournament.empty()) return nullptr;
    
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    
    while (!tournament.empty()) {
        int minIdx = 0;
        for (int i = 1; i < tournament.size(); ++i) {
            if (tournament[i]->val < tournament[minIdx]->val) {
                minIdx = i;
            }
        }
        
        current->next = tournament[minIdx];
        current = current->next;
        
        if (tournament[minIdx]->next) {
            tournament[minIdx] = tournament[minIdx]->next;
        } else {
            tournament.erase(tournament.begin() + minIdx);
        }
    }
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}

ListNode* MergeKSortedLists::mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

}
}