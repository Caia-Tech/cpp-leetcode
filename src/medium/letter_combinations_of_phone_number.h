#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

namespace leetcode {
namespace medium {

/**
 * Problem 17: Letter Combinations of a Phone Number
 * 
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations 
 * that the number could represent. Return the answer in any order.
 * 
 * A mapping of digits to letters (just like on the telephone buttons) is given below. 
 * Note that 1 does not map to any letters.
 * 
 * 2: abc, 3: def, 4: ghi, 5: jkl, 6: mno, 7: pqrs, 8: tuv, 9: wxyz
 * 
 * Constraints:
 * - 0 <= digits.length <= 4
 * - digits[i] is a digit in the range ['2', '9'].
 */
class LetterCombinationsOfPhoneNumber {
public:
    /**
     * Approach 1: Backtracking (Optimal)
     * 
     * Use recursive backtracking to generate all combinations.
     * 
     * Reasoning: This is the classic backtracking approach and most intuitive solution.
     * For each digit, try all possible letters it maps to. Recursively build combinations
     * by making choices and undoing them (backtracking). The recursion naturally explores
     * all possible paths through the solution space. Base case is when we've processed
     * all digits. This approach is optimal in terms of not storing intermediate results.
     * 
     * Time Complexity: O(3^N × 4^M) - where N is digits with 3 letters, M is digits with 4 letters
     * Space Complexity: O(3^N × 4^M) - for result storage + O(N) for recursion stack
     * 
     * Best when: Need memory-efficient generation, understand backtracking well
     * Worst when: Want iterative solution or need to process results incrementally
     */
    std::vector<std::string> letterCombinationsBacktracking(const std::string& digits);

    /**
     * Approach 2: Iterative with Queue/BFS
     * 
     * Build combinations iteratively using BFS approach with queue.
     * 
     * Reasoning: Start with empty combination, then for each digit, take all current
     * combinations and extend each with every possible letter for that digit.
     * Use a queue to process combinations level by level (BFS-style). This approach
     * builds all combinations of length i before moving to length i+1, making the
     * process very systematic and easy to visualize.
     * 
     * Time Complexity: O(3^N × 4^M) - same as backtracking
     * Space Complexity: O(3^N × 4^M) - queue can hold all intermediate combinations
     * 
     * Best when: Iterative approach is preferred, want BFS-style generation
     * Worst when: Memory usage for intermediate results is concerning
     */
    std::vector<std::string> letterCombinationsIterative(const std::string& digits);

    /**
     * Approach 3: Dynamic Programming
     * 
     * Build combinations using dynamic programming approach.
     * 
     * Reasoning: Use DP where dp[i] contains all combinations for the first i digits.
     * For each new digit, combine all existing combinations with all letters of the
     * new digit. This approach makes the incremental building process very explicit
     * and could be useful if we needed to compute combinations for all prefixes.
     * 
     * Time Complexity: O(3^N × 4^M) - still need to generate all combinations
     * Space Complexity: O(3^N × 4^M) - DP table storage
     * 
     * Best when: Want explicit DP formulation, need prefix combinations
     * Worst when: Simple backtracking is sufficient
     */
    std::vector<std::string> letterCombinationsDP(const std::string& digits);

    /**
     * Approach 4: Recursive without Explicit Backtracking
     * 
     * Generate combinations using pure recursion without explicit backtrack state.
     * 
     * Reasoning: Instead of maintaining a current combination and backtracking,
     * each recursive call returns all possible combinations for the remaining digits.
     * Combine results from recursive calls with current digit's letters. This approach
     * is more functional in style and doesn't require maintaining mutable state.
     * 
     * Time Complexity: O(3^N × 4^M) - same generation complexity
     * Space Complexity: O(3^N × 4^M) - result storage + O(N) recursion stack
     * 
     * Best when: Functional programming style preferred, avoid mutable state
     * Worst when: Backtracking approach is more memory efficient
     */
    std::vector<std::string> letterCombinationsRecursiveFunc(const std::string& digits);

    /**
     * Approach 5: Bit Manipulation Based
     * 
     * Use bit manipulation to enumerate all possible combinations.
     * 
     * Reasoning: Treat each digit choice as selecting from available options using
     * bit patterns. For each digit with k letters, use base-k counting to enumerate
     * all choices. Convert counting patterns to actual letter selections. This
     * approach demonstrates how combinatorial problems can be solved using
     * systematic enumeration patterns.
     * 
     * Time Complexity: O(3^N × 4^M) - still need to generate all combinations
     * Space Complexity: O(3^N × 4^M) - result storage
     * 
     * Best when: Want to understand enumeration patterns, educational purposes
     * Worst when: Backtracking is more intuitive for this problem structure
     */
    std::vector<std::string> letterCombinationsBitManip(const std::string& digits);

    /**
     * Approach 6: Stack-based Iterative (DFS Style)
     * 
     * Use stack to simulate recursive backtracking iteratively.
     * 
     * Reasoning: Simulate the backtracking approach using an explicit stack instead
     * of recursion. Push states (current combination, next digit index) onto stack,
     * pop and process states, pushing new states for each letter choice. This
     * converts recursive backtracking to iterative while maintaining the same
     * exploration order (DFS).
     * 
     * Time Complexity: O(3^N × 4^M) - same exploration pattern as backtracking
     * Space Complexity: O(3^N × 4^M) - stack can hold many states + result storage
     * 
     * Best when: Want iterative DFS, avoid recursion stack limits
     * Worst when: Recursive backtracking is clearer and more natural
     */
    std::vector<std::string> letterCombinationsStack(const std::string& digits);

private:
    // Helper functions
    void backtrackHelper(const std::string& digits, int index, std::string& current, std::vector<std::string>& result);
    std::vector<std::string> generateCombinationsRecursive(const std::string& digits, int index);
    std::vector<int> getDigitChoices(int digit);
    
    // Phone mapping
    static const std::unordered_map<char, std::string> phoneMap;
    
    // Stack state for iterative DFS
    struct StackState {
        std::string current;
        int digitIndex;
        int letterIndex;
        
        StackState(const std::string& curr, int dIdx, int lIdx) 
            : current(curr), digitIndex(dIdx), letterIndex(lIdx) {}
    };
};

}
}