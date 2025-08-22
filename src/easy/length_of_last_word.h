#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace leetcode {
namespace easy {

/**
 * Problem 58: Length of Last Word
 * 
 * Given a string s consisting of words and spaces, return the length of the last word.
 * A word is a maximal substring consisting of non-space characters only.
 * 
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - s consists of only English letters and spaces ' '.
 * - There is at least one word in s.
 */
class LengthOfLastWord {
public:
    /**
     * Approach 1: Reverse Iteration (Optimal)
     * 
     * Iterate from end of string, skip trailing spaces, then count word length.
     * 
     * Reasoning: This is the most efficient approach. Start from the end of string,
     * first skip any trailing spaces, then count characters until we hit another
     * space or reach the beginning. This avoids processing the entire string and
     * directly finds the last word. Only processes the minimum necessary characters.
     * 
     * Time Complexity: O(n) worst case, often much better in practice
     * Space Complexity: O(1) - only using constant extra space
     * 
     * Best when: Need optimal performance, many leading words or trailing spaces
     * Worst when: Last word is very long and starts near beginning of string
     */
    int lengthOfLastWordReverse(const std::string& s);

    /**
     * Approach 2: Forward Iteration with State Tracking
     * 
     * Scan forward and track current word length, reset on spaces.
     * 
     * Reasoning: Scan through string from beginning, maintaining current word length.
     * When we encounter a space, reset current word length to 0. When we encounter
     * a non-space character, increment current word length. The final current word
     * length is the length of the last word. Simple to understand but processes
     * entire string.
     * 
     * Time Complexity: O(n) - must scan entire string
     * Space Complexity: O(1) - only using counter variable
     * 
     * Best when: Simple implementation preferred, string is short
     * Worst when: String is very long with last word at the end
     */
    int lengthOfLastWordForward(const std::string& s);

    /**
     * Approach 3: String Stream Tokenization
     * 
     * Use stringstream to split into words and get the last one.
     * 
     * Reasoning: Use C++ stringstream to automatically handle word tokenization.
     * The stream treats spaces as delimiters and extracts words. Keep updating
     * a variable with each word until stream is exhausted - the final word is
     * the last word. While clean and handles multiple spaces automatically,
     * it has higher overhead due to stream operations.
     * 
     * Time Complexity: O(n) - stringstream processes entire string
     * Space Complexity: O(n) - stringstream and temporary word storage
     * 
     * Best when: Need robust word tokenization, handle multiple consecutive spaces
     * Worst when: Memory usage is critical or performance is paramount
     */
    int lengthOfLastWordStringStream(const std::string& s);

    /**
     * Approach 4: STL find_last_not_of and rfind
     * 
     * Use STL functions to find last word boundaries.
     * 
     * Reasoning: Use find_last_not_of(' ') to find the end of the last word,
     * then use rfind(' ') to find the beginning of the last word. Calculate
     * the length as the difference. This approach leverages optimized STL
     * string functions but requires careful handling of edge cases when
     * no spaces are found.
     * 
     * Time Complexity: O(n) - STL string search functions
     * Space Complexity: O(1) - only using position variables
     * 
     * Best when: Want to leverage STL optimizations, comfortable with STL
     * Worst when: Need to implement logic manually, STL functions are restricted
     */
    int lengthOfLastWordSTL(const std::string& s);

    /**
     * Approach 5: Two Pointers for Word Boundaries
     * 
     * Use two pointers to identify start and end of last word.
     * 
     * Reasoning: Start from end with right pointer, skip trailing spaces to find
     * end of last word. Then continue with left pointer to find start of last word.
     * Calculate length as difference between pointers. This approach explicitly
     * identifies word boundaries, making the algorithm very clear and easy to debug.
     * 
     * Time Complexity: O(n) worst case, often better in practice
     * Space Complexity: O(1) - only using two pointer variables
     * 
     * Best when: Word boundary identification is important, clear algorithm needed
     * Worst when: Single pointer approach is sufficient
     */
    int lengthOfLastWordTwoPointers(const std::string& s);

    /**
     * Approach 6: Regular Expression (Overkill)
     * 
     * Use regex to extract the last word.
     * 
     * Reasoning: Use regular expressions to match word patterns and extract the
     * last word. While this demonstrates regex usage, it's complete overkill for
     * this simple problem and has significant overhead. The regex engine provides
     * powerful pattern matching but at the cost of complexity and performance
     * for such a basic task.
     * 
     * Time Complexity: O(n) - regex processing overhead
     * Space Complexity: O(n) - regex compilation and match storage
     * 
     * Best when: Educational purposes, demonstrating regex capabilities
     * Worst when: Performance matters or simple solutions are preferred
     */
    int lengthOfLastWordRegex(const std::string& s);

private:
    // Helper function for regex approach
    std::vector<std::string> extractWords(const std::string& s);
};

}
}