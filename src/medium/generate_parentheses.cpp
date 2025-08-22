#include "generate_parentheses.h"
#include <queue>

namespace leetcode {
namespace medium {

std::vector<std::string> GenerateParentheses::generateParenthesesBacktracking(int n) {
    std::vector<std::string> result;
    std::string current;
    backtrackHelper(n, current, 0, 0, result);
    return result;
}

void GenerateParentheses::backtrackHelper(int n, std::string& current, int open, int close, std::vector<std::string>& result) {
    // Base case: we've used all n pairs
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }
    
    // Add opening bracket if we haven't used all n
    if (open < n) {
        current.push_back('(');
        backtrackHelper(n, current, open + 1, close, result);
        current.pop_back();  // Backtrack
    }
    
    // Add closing bracket if it won't make string invalid
    if (close < open) {
        current.push_back(')');
        backtrackHelper(n, current, open, close + 1, result);
        current.pop_back();  // Backtrack
    }
}

std::vector<std::string> GenerateParentheses::generateParenthesesDP(int n) {
    std::vector<std::vector<std::string>> dp(n + 1);
    dp[0] = {""};  // Base case: 0 pairs = empty string
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            // For each way to split: "(" + dp[j] + ")" + dp[i-1-j]
            for (const std::string& left : dp[j]) {
                for (const std::string& right : dp[i - 1 - j]) {
                    dp[i].push_back("(" + left + ")" + right);
                }
            }
        }
    }
    
    return dp[n];
}

std::vector<std::string> GenerateParentheses::generateParenthesesClosure(int n) {
    return generateCombinations(n);
}

std::vector<std::string> GenerateParentheses::generateCombinations(int n) {
    if (n == 0) return {""};
    
    std::vector<std::string> result;
    
    // Use closure number: f(n) = Σ f(i) × f(n-1-i) for i from 0 to n-1
    for (int i = 0; i < n; ++i) {
        std::vector<std::string> left = generateCombinations(i);
        std::vector<std::string> right = generateCombinations(n - 1 - i);
        
        for (const std::string& l : left) {
            for (const std::string& r : right) {
                result.push_back("(" + l + ")" + r);
            }
        }
    }
    
    return result;
}

std::vector<std::string> GenerateParentheses::generateParenthesesBFS(int n) {
    std::vector<std::string> result;
    std::queue<BFSState> queue;
    
    // Start with empty string
    queue.push(BFSState("", 0, 0));
    
    while (!queue.empty()) {
        BFSState current = queue.front();
        queue.pop();
        
        // If we've built a complete string
        if (current.current.length() == 2 * n) {
            result.push_back(current.current);
            continue;
        }
        
        // Try adding opening bracket
        if (current.openCount < n) {
            queue.push(BFSState(current.current + "(", current.openCount + 1, current.closeCount));
        }
        
        // Try adding closing bracket
        if (current.closeCount < current.openCount) {
            queue.push(BFSState(current.current + ")", current.openCount, current.closeCount + 1));
        }
    }
    
    return result;
}

std::vector<std::string> GenerateParentheses::generateParenthesesIterativeDFS(int n) {
    std::vector<std::string> result;
    std::stack<DFSState> stack;
    
    // Start with empty string
    stack.push(DFSState("", 0, 0));
    
    while (!stack.empty()) {
        DFSState current = stack.top();
        stack.pop();
        
        // If we've built a complete string
        if (current.current.length() == 2 * n) {
            result.push_back(current.current);
            continue;
        }
        
        // Push states in reverse order to maintain DFS order
        // Try adding closing bracket first (will be processed later)
        if (current.closeCount < current.openCount) {
            stack.push(DFSState(current.current + ")", current.openCount, current.closeCount + 1));
        }
        
        // Try adding opening bracket second (will be processed first)
        if (current.openCount < n) {
            stack.push(DFSState(current.current + "(", current.openCount + 1, current.closeCount));
        }
    }
    
    return result;
}

std::vector<std::string> GenerateParentheses::generateParenthesesDivideConquer(int n) {
    return divideConquerHelper(0, n - 1);
}

std::vector<std::string> GenerateParentheses::divideConquerHelper(int left, int right) {
    if (left > right) return {""};
    if (left == right) return {"()"};
    
    std::vector<std::string> result;
    
    // Try all possible ways to divide the pairs
    for (int i = left; i <= right; ++i) {
        std::vector<std::string> leftPart = divideConquerHelper(left, i - 1);
        std::vector<std::string> rightPart = divideConquerHelper(i + 1, right);
        
        // Current pair wraps around one part
        std::vector<std::string> wrappedPart = divideConquerHelper(left, i - 1);
        
        for (const std::string& wrapped : wrappedPart) {
            for (const std::string& rightStr : rightPart) {
                result.push_back("(" + wrapped + ")" + rightStr);
            }
        }
    }
    
    // Also consider concatenating two independent parts
    for (int split = left; split < right; ++split) {
        std::vector<std::string> leftResults = divideConquerHelper(left, split);
        std::vector<std::string> rightResults = divideConquerHelper(split + 1, right);
        
        for (const std::string& leftStr : leftResults) {
            for (const std::string& rightStr : rightResults) {
                if (!leftStr.empty() && !rightStr.empty()) {
                    result.push_back(leftStr + rightStr);
                }
            }
        }
    }
    
    return result;
}

}
}