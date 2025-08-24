#include "palindrome_linked_list.h"

namespace leetcode {
namespace easy {

// Approach 1: Convert to Array and Two Pointers (Simplest)
bool PalindromeLinkedList::isPalindromeArray(ListNode* head) {
    if (!head) return true;
    
    // Convert linked list to vector
    std::vector<int> values;
    ListNode* current = head;
    while (current) {
        values.push_back(current->val);
        current = current->next;
    }
    
    // Check palindrome using two pointers
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;
    
    while (left < right) {
        if (values[left] != values[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

// Approach 2: Stack-Based Comparison
bool PalindromeLinkedList::isPalindromeStack(ListNode* head) {
    if (!head) return true;
    
    // Get list length
    int length = getListLength(head);
    
    // Push first half onto stack
    std::stack<int> firstHalf;
    ListNode* current = head;
    
    for (int i = 0; i < length / 2; ++i) {
        firstHalf.push(current->val);
        current = current->next;
    }
    
    // Skip middle element for odd-length lists
    if (length % 2 == 1) {
        current = current->next;
    }
    
    // Compare second half with stack (reversed first half)
    while (current && !firstHalf.empty()) {
        if (current->val != firstHalf.top()) {
            return false;
        }
        firstHalf.pop();
        current = current->next;
    }
    
    return true;
}

// Approach 3: Reverse Second Half and Compare (Optimal)
bool PalindromeLinkedList::isPalindromeReverseSecondHalf(ListNode* head) {
    if (!head || !head->next) return true;
    
    // Find middle of the list
    ListNode* middle = findMiddle(head);
    
    // Reverse second half
    ListNode* secondHalf = reverseList(middle->next);
    
    // Store second half head for restoration
    ListNode* secondHalfHead = secondHalf;
    
    // Compare first half with reversed second half
    ListNode* firstHalf = head;
    bool isPalindrome = true;
    
    while (secondHalf) {
        if (firstHalf->val != secondHalf->val) {
            isPalindrome = false;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    
    // Restore original list structure
    middle->next = reverseList(secondHalfHead);
    
    return isPalindrome;
}

// Approach 4: Recursive with Global Variable
bool PalindromeLinkedList::isPalindromeRecursive(ListNode* head) {
    ListNode* frontPointer = head;
    return isPalindromeRecursiveHelper(head, frontPointer);
}

bool PalindromeLinkedList::isPalindromeRecursiveHelper(ListNode* node, ListNode*& frontPointer) {
    if (!node) return true;
    
    // Recurse to the end of the list
    bool isPalindromeSublist = isPalindromeRecursiveHelper(node->next, frontPointer);
    
    // Compare current node (from back) with front pointer (from front)
    bool isCurrentMatch = (node->val == frontPointer->val);
    
    // Move front pointer forward for next comparison
    frontPointer = frontPointer->next;
    
    return isPalindromeSublist && isCurrentMatch;
}

// Approach 5: Two-Pass with Mathematical Properties
bool PalindromeLinkedList::isPalindromeMathematical(ListNode* head) {
    if (!head) return true;
    if (!head->next) return true;  // Single element is palindrome
    
    // Convert to array first for easier mathematical operations
    std::vector<int> values;
    ListNode* current = head;
    while (current) {
        values.push_back(current->val);
        current = current->next;
    }
    
    int n = static_cast<int>(values.size());
    
    // Mathematical property: for palindrome, values[i] == values[n-1-i]
    // Calculate sum of differences between symmetric positions
    long long symmetryCheck = 0;
    
    for (int i = 0; i < n / 2; ++i) {
        // If palindrome, this difference should be 0
        symmetryCheck += abs(values[i] - values[n - 1 - i]);
    }
    
    // Additional check: calculate position-weighted checksum
    long long forwardChecksum = 0;
    long long reverseChecksum = 0;
    
    for (int i = 0; i < n; ++i) {
        forwardChecksum += values[i] * (i + 1);
        reverseChecksum += values[n - 1 - i] * (i + 1);
    }
    
    // For palindrome: symmetry check should be 0, and checksums should match
    return (symmetryCheck == 0) && (forwardChecksum == reverseChecksum);
}

// Approach 6: Functional Programming with Lambdas
bool PalindromeLinkedList::isPalindromeFunctional(ListNode* head) {
    auto valueExtractor = createValueExtractor();
    auto palindromeChecker = createPalindromeChecker();
    
    std::vector<int> values = valueExtractor(head);
    return palindromeChecker(values);
}

// Helper functions
ListNode* PalindromeLinkedList::reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    
    while (current) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

ListNode* PalindromeLinkedList::findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Find middle using slow/fast pointers
    // For odd length: slow will be at middle
    // For even length: slow will be at end of first half
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

int PalindromeLinkedList::getListLength(ListNode* head) {
    int length = 0;
    ListNode* current = head;
    while (current) {
        length++;
        current = current->next;
    }
    return length;
}

// Functional approach helpers
std::function<std::vector<int>(ListNode*)> PalindromeLinkedList::createValueExtractor() {
    return [](ListNode* head) -> std::vector<int> {
        std::vector<int> values;
        ListNode* current = head;
        while (current) {
            values.push_back(current->val);
            current = current->next;
        }
        return values;
    };
}

std::function<bool(const std::vector<int>&)> PalindromeLinkedList::createPalindromeChecker() {
    return [](const std::vector<int>& values) -> bool {
        if (values.empty()) return true;
        
        auto isPalindromeHelper = [&values](int left, int right) -> bool {
            std::function<bool(int, int)> checkRecursively = [&](int l, int r) -> bool {
                if (l >= r) return true;
                return (values[l] == values[r]) && checkRecursively(l + 1, r - 1);
            };
            return checkRecursively(left, right);
        };
        
        return isPalindromeHelper(0, static_cast<int>(values.size()) - 1);
    };
}

// Helper functions for testing
ListNode* PalindromeLinkedList::createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

std::vector<int> PalindromeLinkedList::listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    
    return result;
}

void PalindromeLinkedList::deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

}  // namespace easy
}  // namespace leetcode