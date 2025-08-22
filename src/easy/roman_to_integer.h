#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace leetcode {
namespace easy {

/**
 * Problem 13: Roman to Integer
 * 
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * 
 * Given a roman numeral, convert it to an integer.
 * 
 * Constraints:
 * - 1 <= s.length <= 15
 * - s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M')
 * - It is guaranteed that s is a valid roman numeral in the range [1, 3999]
 */
class RomanToInteger {
public:
    /**
     * Approach 1: Hash Map with Look-ahead
     * 
     * Use hash map and check next character for subtraction cases.
     * 
     * Reasoning: This is the most straightforward approach. Use hash map for O(1)
     * character-to-value lookup. The key insight is handling subtraction cases
     * (IV, IX, XL, XC, CD, CM) by looking ahead to the next character. If current
     * character's value is less than next character's value, subtract instead of add.
     * This handles the Roman numeral rules naturally.
     * 
     * Time Complexity: O(n) - single pass through string
     * Space Complexity: O(1) - fixed size hash map (7 entries)
     * 
     * Best when: Clear, maintainable code needed, hash operations are fast
     * Worst when: Micro-optimizations needed or embedded systems
     */
    int romanToIntHashMap(const std::string& s);

    /**
     * Approach 2: Switch Statement
     * 
     * Use switch for character mapping.
     * 
     * Reasoning: Replace hash map with switch statement for potentially better
     * performance. Switch statements can be optimized to jump tables by compilers,
     * potentially faster than hash lookups for small, fixed sets. Same logic as
     * hash map approach but with explicit case handling for each Roman numeral
     * character. Trade flexibility for potential performance gain.
     * 
     * Time Complexity: O(n) - potentially faster constant factor than hash map
     * Space Complexity: O(1) - no hash map storage
     * 
     * Best when: Performance is critical, character set is fixed and small
     * Worst when: Code maintainability is more important than micro-optimizations
     */
    int romanToIntSwitch(const std::string& s);

    /**
     * Approach 3: Right to Left Processing
     * 
     * Process from right to left to handle subtraction naturally.
     * 
     * Reasoning: This is an elegant approach that eliminates the need for look-ahead.
     * Process the string from right to left. If current character's value is less
     * than the previous (rightward) character's value, subtract it; otherwise, add it.
     * This naturally handles subtraction cases without special case logic, making
     * the algorithm cleaner and easier to understand.
     * 
     * Time Complexity: O(n) - single pass through string (reverse direction)
     * Space Complexity: O(1) - only tracking previous value
     * 
     * Best when: Want elegant solution without special case handling
     * Worst when: Right-to-left processing is less intuitive for some developers
     */
    int romanToIntRightToLeft(const std::string& s);

    /**
     * Approach 4: Replace Subtraction Cases
     * 
     * Replace special cases then sum.
     * 
     * Reasoning: This approach pre-processes the string by replacing all subtraction
     * cases (IV, IX, XL, XC, CD, CM) with temporary characters or markers, then
     * processes the modified string normally. While this uses extra space and string
     * operations, it separates the concerns of handling subtraction vs normal addition,
     * making the logic very clear.
     * 
     * Time Complexity: O(n) - string replacement operations + processing
     * Space Complexity: O(n) - modified string storage
     * 
     * Best when: Clear separation of concerns desired, string operations are fast
     * Worst when: Memory usage is critical or string operations are expensive
     */
    int romanToIntReplace(std::string s);

    /**
     * Approach 5: State Machine
     * 
     * Use state machine to track valid transitions.
     * 
     * Reasoning: Model the Roman numeral parsing as a state machine where each state
     * represents the context of previously seen characters. This ensures we only
     * accept valid Roman numeral sequences and can handle subtraction cases based
     * on the current state. While more complex, this approach provides the strongest
     * validation and can detect invalid inputs.
     * 
     * Time Complexity: O(n) - process each character with state transitions
     * Space Complexity: O(1) - fixed number of states
     * 
     * Best when: Need strong input validation, formal approach preferred
     * Worst when: Simpler solutions suffice and complexity isn't justified
     */
    int romanToIntStateMachine(const std::string& s);

    /**
     * Approach 6: Array Lookup
     * 
     * Use array for faster character lookup.
     * 
     * Reasoning: Replace hash map with array indexed by ASCII values for potentially
     * faster lookup. Since Roman numeral characters have known ASCII values, we can
     * create a lookup array where values[char - offset] gives the Roman numeral value.
     * This eliminates hash computation overhead and provides O(1) lookup with better
     * cache locality than hash maps.
     * 
     * Time Complexity: O(n) - fastest constant factor for character lookup
     * Space Complexity: O(1) - small fixed-size array (much smaller than full ASCII)
     * 
     * Best when: Maximum performance needed, embedded systems
     * Worst when: Code clarity is more important than micro-optimizations
     */
    int romanToIntArray(const std::string& s);

private:
    int getValue(char c);
    int getValueSwitch(char c);
};

}
}