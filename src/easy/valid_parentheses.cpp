#include "valid_parentheses.h"
#include <stack>
#include <unordered_map>

namespace leetcode {
namespace easy {

bool ValidParentheses::isValidStack(const std::string& s) {
    std::stack<char> stack;
    std::unordered_map<char, char> mapping = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };
    
    for (char c : s) {
        if (mapping.find(c) != mapping.end()) {
            if (stack.empty() || stack.top() != mapping[c]) {
                return false;
            }
            stack.pop();
        } else {
            stack.push(c);
        }
    }
    
    return stack.empty();
}

bool ValidParentheses::isValidStackSwitch(const std::string& s) {
    std::stack<char> stack;
    
    for (char c : s) {
        switch (c) {
            case '(':
            case '{':
            case '[':
                stack.push(c);
                break;
            case ')':
                if (stack.empty() || stack.top() != '(') return false;
                stack.pop();
                break;
            case '}':
                if (stack.empty() || stack.top() != '{') return false;
                stack.pop();
                break;
            case ']':
                if (stack.empty() || stack.top() != '[') return false;
                stack.pop();
                break;
        }
    }
    
    return stack.empty();
}

bool ValidParentheses::isValidCounter(const std::string& s) {
    int roundCount = 0, curlyCount = 0, squareCount = 0;
    std::stack<char> orderStack;
    
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            orderStack.push(c);
            if (c == '(') roundCount++;
            else if (c == '{') curlyCount++;
            else squareCount++;
        } else {
            if (orderStack.empty()) return false;
            
            char expected;
            if (c == ')') {
                expected = '(';
                roundCount--;
                if (roundCount < 0) return false;
            } else if (c == '}') {
                expected = '{';
                curlyCount--;
                if (curlyCount < 0) return false;
            } else {
                expected = '[';
                squareCount--;
                if (squareCount < 0) return false;
            }
            
            if (orderStack.top() != expected) {
                bool found = false;
                std::stack<char> temp;
                while (!orderStack.empty()) {
                    if (orderStack.top() == expected) {
                        orderStack.pop();
                        found = true;
                        break;
                    }
                    temp.push(orderStack.top());
                    orderStack.pop();
                }
                while (!temp.empty()) {
                    orderStack.push(temp.top());
                    temp.pop();
                }
                if (!found) return false;
            } else {
                orderStack.pop();
            }
        }
    }
    
    return roundCount == 0 && curlyCount == 0 && squareCount == 0;
}

bool ValidParentheses::isValidReplace(const std::string& s) {
    std::string str = s;
    int prevSize;
    
    do {
        prevSize = str.size();
        str = removeValidPairs(str);
    } while (str.size() < prevSize && !str.empty());
    
    return str.empty();
}

std::string ValidParentheses::removeValidPairs(const std::string& s) {
    std::string result;
    for (char c : s) {
        if (!result.empty() && 
            ((result.back() == '(' && c == ')') ||
             (result.back() == '{' && c == '}') ||
             (result.back() == '[' && c == ']'))) {
            result.pop_back();
        } else {
            result.push_back(c);
        }
    }
    return result;
}

bool ValidParentheses::isValidRecursive(const std::string& s) {
    std::stack<char> stack;
    return recursiveHelper(s, 0, stack);
}

bool ValidParentheses::recursiveHelper(const std::string& s, int index, std::stack<char>& stack) {
    if (index == s.length()) {
        return stack.empty();
    }
    
    char c = s[index];
    
    if (c == '(' || c == '{' || c == '[') {
        stack.push(c);
        return recursiveHelper(s, index + 1, stack);
    } else {
        if (stack.empty()) return false;
        
        char top = stack.top();
        if ((c == ')' && top == '(') ||
            (c == '}' && top == '{') ||
            (c == ']' && top == '[')) {
            stack.pop();
            return recursiveHelper(s, index + 1, stack);
        }
        return false;
    }
}

bool ValidParentheses::isValidArrayStack(const std::string& s) {
    if (s.empty()) return true;
    if (s.length() % 2 != 0) return false;
    
    std::vector<char> stack;
    stack.reserve(s.length() / 2);
    
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            stack.push_back(c);
        } else {
            if (stack.empty()) return false;
            
            char last = stack.back();
            if ((c == ')' && last != '(') ||
                (c == '}' && last != '{') ||
                (c == ']' && last != '[')) {
                return false;
            }
            stack.pop_back();
        }
    }
    
    return stack.empty();
}

}
}