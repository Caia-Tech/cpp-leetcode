#pragma once

#include <vector>
#include <string>
#include <stack>

namespace leetcode {
namespace medium {

/**
 * Problem 22: Generate Parentheses
 * 
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 * 
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * 
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 * 
 * Constraints:
 * - 1 <= n <= 8
 */
class GenerateParentheses {
public:
    /**
     * Approach 1: Backtracking (Optimal)
     * 
     * Use recursive backtracking to build valid parentheses combinations.
     * 
     * Reasoning: This is the optimal and most intuitive approach. Build strings
     * character by character, making valid choices at each step. At any point,
     * we can add '(' if we haven't used all n opening brackets, and we can add ')'
     * if it wouldn't make the string invalid (i.e., count of ')' < count of '(').
     * Backtrack when string is complete. This ensures we only generate valid combinations.
     * 
     * Time Complexity: O(4^n / √n) - Catalan number for well-formed parentheses
     * Space Complexity: O(4^n / √n) - result storage + O(n) recursion stack
     * 
     * Best when: Need to understand backtracking, memory-efficient generation
     * Worst when: Want iterative solution or different generation order
     */
    std::vector<std::string> generateParenthesesBacktracking(int n);

    /**
     * Approach 2: Dynamic Programming
     * 
     * Build solutions incrementally using previously computed results.
     * 
     * Reasoning: Use DP where dp[i] contains all valid combinations with i pairs.
     * For dp[i], consider all ways to split into dp[j] + "(" + dp[i-1-j] + ")"
     * where j ranges from 0 to i-1. This represents placing the first closing
     * parenthesis at different positions. Each combination ensures the first
     * opening bracket is matched with some closing bracket.
     * 
     * Time Complexity: O(4^n / √n) - same total combinations generated
     * Space Complexity: O(4^n / √n) - DP table storage for all intermediate results
     * 
     * Best when: Want iterative DP approach, need all intermediate results
     * Worst when: Only final result needed, memory usage is critical
     */
    std::vector<std::string> generateParenthesesDP(int n);

    /**
     * Approach 3: Closure Number (Mathematical)
     * 
     * Generate using closure number pattern based on Catalan sequence.
     * 
     * Reasoning: Every valid parentheses string can be written as "(" + A + ")" + B
     * where A and B are valid parentheses strings. This gives the recurrence:
     * f(n) = Σ f(i) × f(n-1-i) for i from 0 to n-1. This is the mathematical
     * foundation behind the Catalan numbers and provides a systematic generation method.
     * 
     * Time Complexity: O(4^n / √n) - Catalan number generation
     * Space Complexity: O(4^n / √n) - storage for all combinations
     * 
     * Best when: Want to understand mathematical structure, Catalan number connection
     * Worst when: Backtracking approach is more intuitive
     */
    std::vector<std::string> generateParenthesesClosure(int n);

    /**
     * Approach 4: BFS/Level-by-Level Generation
     * 
     * Generate combinations level by level using BFS approach.
     * 
     * Reasoning: Start with empty string, then generate all possible next states
     * by adding '(' or ')' where valid. Use queue to process each level completely
     * before moving to next. This generates combinations in breadth-first order
     * and makes the level-by-level construction very explicit.
     * 
     * Time Complexity: O(4^n / √n) - same total combinations
     * Space Complexity: O(4^n / √n) - queue storage + result storage
     * 
     * Best when: Want BFS-style generation, level-by-level processing
     * Worst when: DFS/backtracking is more memory efficient
     */
    std::vector<std::string> generateParenthesesBFS(int n);

    /**
     * Approach 5: Stack-based Iterative DFS
     * 
     * Use stack to simulate recursive backtracking iteratively.
     * 
     * Reasoning: Convert recursive backtracking to iterative using explicit stack.
     * Each stack entry contains current string, count of opening brackets used,
     * and count of closing brackets used. This avoids recursion stack limits
     * while maintaining the same DFS exploration order as backtracking.
     * 
     * Time Complexity: O(4^n / √n) - same exploration pattern
     * Space Complexity: O(4^n / √n) - stack storage + result storage
     * 
     * Best when: Want iterative DFS, avoid recursion stack limits
     * Worst when: Recursive backtracking is clearer and more natural
     */
    std::vector<std::string> generateParenthesesIterativeDFS(int n);

    /**
     * Approach 6: Divide and Conquer
     * 
     * Divide problem by considering all possible splits of parentheses pairs.
     * 
     * Reasoning: For n pairs, consider all ways to distribute pairs between
     * two independent groups, then combine their results. This demonstrates
     * divide-and-conquer thinking but is less efficient due to repeated
     * computation and combination overhead. Mainly educational value.
     * 
     * Time Complexity: O(4^n / √n × n) - additional factor for combinations
     * Space Complexity: O(4^n / √n × log n) - recursion stack + result storage
     * 
     * Best when: Educational purposes, understanding divide-and-conquer
     * Worst when: More efficient approaches are available
     */
    std::vector<std::string> generateParenthesesDivideConquer(int n);

private:
    // Helper functions
    void backtrackHelper(int n, std::string& current, int open, int close, std::vector<std::string>& result);
    std::vector<std::string> generateCombinations(int n);
    std::vector<std::string> divideConquerHelper(int left, int right);
    
    // State for iterative DFS
    struct DFSState {
        std::string current;
        int openCount;
        int closeCount;
        
        DFSState(const std::string& curr, int open, int close) 
            : current(curr), openCount(open), closeCount(close) {}
    };
    
    // State for BFS
    struct BFSState {
        std::string current;
        int openCount;
        int closeCount;
        
        BFSState(const std::string& curr, int open, int close) 
            : current(curr), openCount(open), closeCount(close) {}
    };
};

}
}