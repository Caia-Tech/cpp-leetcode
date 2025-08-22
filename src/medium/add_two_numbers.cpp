#include "add_two_numbers.h"
#include <stack>
#include <string>
#include <algorithm>

namespace leetcode {
namespace medium {

ListNode* AddTwoNumbers::addTwoNumbersElementary(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* current = &dummy;
    int carry = 0;
    
    // Process both lists while at least one has nodes or there's carry
    while (l1 || l2 || carry) {
        int sum = carry;
        
        // Add digit from first list if available
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        
        // Add digit from second list if available
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        // Create new node with digit value
        current->next = new ListNode(sum % 10);
        current = current->next;
        
        // Update carry for next iteration
        carry = sum / 10;
    }
    
    return dummy.next;
}

ListNode* AddTwoNumbers::addTwoNumbersRecursive(ListNode* l1, ListNode* l2) {
    return addRecursive(l1, l2, 0);
}

ListNode* AddTwoNumbers::addRecursive(ListNode* l1, ListNode* l2, int carry) {
    // Base case: if both lists are null and no carry
    if (!l1 && !l2 && carry == 0) {
        return nullptr;
    }
    
    int sum = carry;
    
    // Add values from both lists if they exist
    if (l1) {
        sum += l1->val;
        l1 = l1->next;
    }
    if (l2) {
        sum += l2->val;
        l2 = l2->next;
    }
    
    // Create current node and recursively compute the rest
    ListNode* result = new ListNode(sum % 10);
    result->next = addRecursive(l1, l2, sum / 10);
    
    return result;
}

ListNode* AddTwoNumbers::addTwoNumbersInteger(ListNode* l1, ListNode* l2) {
    // Convert lists to integers
    long long num1 = listToInteger(l1);
    long long num2 = listToInteger(l2);
    
    // Add the numbers
    long long sum = num1 + num2;
    
    // Convert result back to list
    return integerToList(sum);
}

long long AddTwoNumbers::listToInteger(ListNode* head) {
    long long result = 0;
    long long multiplier = 1;
    
    while (head) {
        result += head->val * multiplier;
        multiplier *= 10;
        head = head->next;
    }
    
    return result;
}

ListNode* AddTwoNumbers::integerToList(long long num) {
    if (num == 0) {
        return new ListNode(0);
    }
    
    ListNode dummy(0);
    ListNode* current = &dummy;
    
    while (num > 0) {
        current->next = new ListNode(num % 10);
        current = current->next;
        num /= 10;
    }
    
    return dummy.next;
}

ListNode* AddTwoNumbers::addTwoNumbersString(ListNode* l1, ListNode* l2) {
    // Convert lists to strings
    std::string str1 = listToString(l1);
    std::string str2 = listToString(l2);
    
    // Add strings
    std::string sum = addStrings(str1, str2);
    
    // Convert result back to list
    return stringToList(sum);
}

std::string AddTwoNumbers::listToString(ListNode* head) {
    std::string result;
    while (head) {
        result += std::to_string(head->val);
        head = head->next;
    }
    return result;
}

ListNode* AddTwoNumbers::stringToList(const std::string& str) {
    ListNode dummy(0);
    ListNode* current = &dummy;
    
    for (char c : str) {
        current->next = new ListNode(c - '0');
        current = current->next;
    }
    
    return dummy.next;
}

std::string AddTwoNumbers::addStrings(const std::string& num1, const std::string& num2) {
    std::string result;
    int i = 0, j = 0, carry = 0;
    
    // Add digits from right to left (both strings are in reverse order)
    while (i < num1.length() || j < num2.length() || carry) {
        int sum = carry;
        
        if (i < num1.length()) {
            sum += num1[i++] - '0';
        }
        if (j < num2.length()) {
            sum += num2[j++] - '0';
        }
        
        result += std::to_string(sum % 10);
        carry = sum / 10;
    }
    
    return result;
}

ListNode* AddTwoNumbers::addTwoNumbersStack(ListNode* l1, ListNode* l2) {
    // Since digits are already in reverse order, we reverse them to normal order
    // then use stacks to add from least significant digit
    
    std::stack<int> stack1, stack2;
    
    // Push all digits to stacks (this reverses them to normal order)
    ListNode* temp = l1;
    while (temp) {
        stack1.push(temp->val);
        temp = temp->next;
    }
    
    temp = l2;
    while (temp) {
        stack2.push(temp->val);
        temp = temp->next;
    }
    
    // Add from least significant digits
    std::stack<int> resultStack;
    int carry = 0;
    
    while (!stack1.empty() || !stack2.empty() || carry) {
        int sum = carry;
        
        if (!stack1.empty()) {
            sum += stack1.top();
            stack1.pop();
        }
        if (!stack2.empty()) {
            sum += stack2.top();
            stack2.pop();
        }
        
        resultStack.push(sum % 10);
        carry = sum / 10;
    }
    
    // Build result list from stack (digits will be in reverse order again)
    ListNode dummy(0);
    ListNode* current = &dummy;
    
    while (!resultStack.empty()) {
        current->next = new ListNode(resultStack.top());
        resultStack.pop();
        current = current->next;
    }
    
    return dummy.next;
}

ListNode* AddTwoNumbers::addTwoNumbersInPlace(ListNode* l1, ListNode* l2) {
    ListNode* current = l1;
    ListNode* prev = nullptr;
    int carry = 0;
    
    // Process while both lists have nodes
    while (current && l2) {
        int sum = current->val + l2->val + carry;
        current->val = sum % 10;
        carry = sum / 10;
        
        prev = current;
        current = current->next;
        l2 = l2->next;
    }
    
    // If l2 still has nodes, append them to l1
    if (l2) {
        prev->next = l2;
        current = prev->next;
    }
    
    // Continue processing remaining nodes with carry
    while (current && carry) {
        int sum = current->val + carry;
        current->val = sum % 10;
        carry = sum / 10;
        
        prev = current;
        current = current->next;
    }
    
    // If there's still carry, add new node
    if (carry) {
        prev->next = new ListNode(carry);
    }
    
    return l1;
}

ListNode* AddTwoNumbers::reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    
    while (current) {
        ListNode* nextTemp = current->next;
        current->next = prev;
        prev = current;
        current = nextTemp;
    }
    
    return prev;
}

}
}