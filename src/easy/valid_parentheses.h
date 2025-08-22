#pragma once

#include <string>
#include <stack>
#include <unordered_map>
#include <vector>

namespace leetcode {
namespace easy {

/**
 * Problem 20: Valid Parentheses
 * 
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * 
 * An input string is valid if:
 * - Open brackets must be closed by the same type of brackets.
 * - Open brackets must be closed in the correct order.
 * - Every close bracket has a corresponding open bracket of the same type.
 * 
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - s consists of parentheses only '()[]{}'.
 */
class ValidParentheses {
public:
    /**
     * Approach 1: Stack with Hash Map
     * 
     * Use stack to track opening brackets and hash map for matching.
     * 
     * Reasoning: This is the classic and most intuitive solution. Stack naturally
     * handles the Last-In-First-Out nature of bracket matching. Hash map provides
     * O(1) lookup for bracket pairs. For each character: if opening bracket, push
     * to stack; if closing bracket, check if it matches the top of stack. The
     * stack ensures proper nesting order.
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(n) - stack can hold up to n/2 opening brackets
     * 
     * Best when: Standard solution, clear and maintainable code needed
     * Worst when: Memory is extremely constrained
     */
    bool isValidStack(const std::string& s);

    /**
     * Approach 2: Stack with Switch Statement
     * 
     * Use stack with switch for bracket matching.
     * 
     * Reasoning: Alternative to hash map approach that uses switch statement for
     * bracket matching. Potentially faster than hash map for small, fixed set of
     * brackets since switch can be optimized to jump table. Stack logic remains
     * the same. This approach trades hash map flexibility for potential performance
     * gain with explicit case handling.
     * 
     * Time Complexity: O(n) - single pass, potentially faster constant factor
     * Space Complexity: O(n) - stack storage
     * 
     * Best when: Performance is critical, bracket types are fixed and small
     * Worst when: Need to support variable bracket types
     */
    bool isValidStackSwitch(const std::string& s);

    /**
     * Approach 3: Counter-based (Limited - only works for single type)
     * 
     * Track counts of each bracket type with validation.
     * 
     * Reasoning: This approach works only for strings with single bracket type
     * (e.g., only parentheses). Use counters to track open vs close brackets.
     * For mixed bracket types, this fails because it doesn't enforce proper nesting.
     * Example: "([)]" would pass counter check but is invalid. Included to show
     * the limitation and why stack is necessary for proper validation.
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(1) - only counter variables
     * 
     * Best when: Only single bracket type guaranteed, memory is critical
     * Worst when: Mixed bracket types need proper nesting validation
     */
    bool isValidCounter(const std::string& s);

    /**
     * Approach 4: Replace Method
     * 
     * Repeatedly remove valid pairs until string is empty or no more pairs.
     * 
     * Reasoning: This brute force approach repeatedly scans the string looking for
     * adjacent valid pairs (like "()", "{}", "[]") and removes them. Continue until
     * no more pairs can be found. If string becomes empty, it was valid. While
     * intuitive, this is inefficient due to multiple string operations and passes.
     * Good for educational purposes to understand the problem.
     * 
     * Time Complexity: O(n^2) - potentially n passes through string
     * Space Complexity: O(n) - string manipulation creates copies
     * 
     * Best when: Educational purposes, understanding problem nature
     * Worst when: Performance matters, large input strings
     */
    bool isValidReplace(const std::string& s);

    /**
     * Approach 5: Recursive
     * 
     * Recursively validate and remove matching pairs.
     * 
     * Reasoning: This approach recursively processes the string, maintaining a stack
     * through recursive calls. Each recursive call handles one character and maintains
     * validation state. While this demonstrates recursive thinking, it's less efficient
     * than iterative stack approach due to call stack overhead and potential for
     * deep recursion on long strings.
     * 
     * Time Complexity: O(n^2) - worst case due to string operations
     * Space Complexity: O(n) - call stack depth plus string storage
     * 
     * Best when: Functional programming style preferred, educational recursion
     * Worst when: Large strings risk stack overflow, performance is critical
     */
    bool isValidRecursive(const std::string& s);

    /**
     * Approach 6: Array-based Stack
     * 
     * Use array as stack for better cache locality.
     * 
     * Reasoning: Instead of std::stack, use a simple array and index to simulate
     * stack operations. This can provide better cache locality and avoid the overhead
     * of dynamic memory allocation that std::stack might have. Manual stack management
     * gives more control over memory usage and can be faster for simple operations
     * like bracket matching.
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(n) - array storage, but more memory-efficient than std::stack
     * 
     * Best when: Performance optimization needed, embedded systems
     * Worst when: Code simplicity is more important than micro-optimizations
     */
    bool isValidArrayStack(const std::string& s);

private:
    bool recursiveHelper(const std::string& s, int index, std::stack<char>& stack);
    std::string removeValidPairs(const std::string& s);
};

}
}