#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <climits>

namespace leetcode {
namespace hard {

/**
 * Problem 76: Minimum Window Substring
 * 
 * Given two strings s and t of lengths m and n respectively, return the minimum window 
 * substring of s such that every character in t (including duplicates) is included in 
 * the window. If there is no such window in s that covers all characters in t, return 
 * the empty string "".
 * 
 * Note that If there is such a window, it is guaranteed that there will always be only 
 * one unique minimum window in s.
 * 
 * Constraints:
 * - m == s.length
 * - n == t.length
 * - 1 <= m, n <= 10^5
 * - s and t consist of uppercase and lowercase English letters.
 * 
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */
class MinimumWindowSubstring {
public:
    /**
     * Approach 1: Sliding Window with Hash Map (Optimal)
     * 
     * Use two pointers to maintain a sliding window and hash map for character counts.
     * 
     * Reasoning: This is the classic sliding window approach. Maintain frequency map
     * of characters in t. Use two pointers (left, right) to form window. Expand right
     * pointer to include more characters until window contains all required characters.
     * Then shrink from left to find minimum valid window. Key insight: track number
     * of unique characters that have reached required frequency to avoid scanning
     * entire frequency map. This achieves O(m+n) time complexity.
     * 
     * Time Complexity: O(m + n) - each character processed at most twice
     * Space Complexity: O(|Σ|) - hash map size bounded by alphabet size
     * 
     * Best when: Need optimal performance, standard sliding window problem
     * Worst when: Simple implementation preferred, small inputs where optimization unnecessary
     */
    std::string minWindow(std::string s, std::string t);

    /**
     * Approach 2: Sliding Window with Array (Space Optimized)
     * 
     * Use fixed-size arrays instead of hash maps for ASCII character tracking.
     * 
     * Reasoning: Since constraints mention only English letters, we can use arrays
     * of size 128 (ASCII) or 256 for character counting instead of hash maps.
     * This provides faster access (O(1) vs O(1) average but better constants) and
     * avoids hash overhead. Same sliding window logic but with array-based tracking.
     * Particularly effective when character set is small and well-defined.
     * 
     * Time Complexity: O(m + n) - same as hash map approach
     * Space Complexity: O(1) - fixed array size regardless of input
     * 
     * Best when: Performance critical, ASCII/limited character set, avoid hash overhead
     * Worst when: Unicode support needed, hash map clarity preferred
     */
    std::string minWindowArray(std::string s, std::string t);

    /**
     * Approach 3: Optimized Sliding Window with Filtered String
     * 
     * Pre-filter string to only include relevant characters before sliding window.
     * 
     * Reasoning: When t is small relative to s, most characters in s are irrelevant.
     * Create filtered version of s containing only characters present in t, along
     * with their original indices. Run sliding window on filtered string. This
     * reduces effective input size when t contains few unique characters relative
     * to s. Particularly effective for sparse matching scenarios.
     * 
     * Time Complexity: O(m + n) - filtering is O(m), sliding window on filtered is O(filtered_size)
     * Space Complexity: O(m) - filtered string storage in worst case
     * 
     * Best when: t is small relative to s, sparse character matches
     * Worst when: Most characters in s are relevant, filtering overhead not worth it
     */
    std::string minWindowFiltered(std::string s, std::string t);

    /**
     * Approach 4: Two-Pass Algorithm (Educational)
     * 
     * First pass finds all valid windows, second pass finds minimum among them.
     * 
     * Reasoning: Educational approach showing separation of concerns. First pass
     * identifies all valid window positions using sliding window technique. Store
     * start/end positions of valid windows. Second pass finds minimum length window.
     * While not optimal, demonstrates how to decompose problem into finding all
     * solutions then selecting best. Useful for understanding problem structure
     * and when additional processing needed on valid windows.
     * 
     * Time Complexity: O(m + n) - two linear passes
     * Space Complexity: O(k) - store k valid windows found
     * 
     * Best when: Need all valid windows, educational purposes, additional window processing
     * Worst when: Only minimum needed, want to minimize space usage
     */
    std::string minWindowTwoPass(std::string s, std::string t);

    /**
     * Approach 5: Sliding Window with Deque Optimization
     * 
     * Use deque to track window bounds and optimize shrinking operations.
     * 
     * Reasoning: Standard sliding window shrinks left pointer one step at a time.
     * Use deque to track positions of relevant characters, enabling faster shrinking
     * by jumping to next relevant position instead of incrementing step by step.
     * This optimization is most beneficial when s has many irrelevant characters
     * between relevant ones. Deque maintains ordered positions for efficient
     * front/back operations during window expansion and contraction.
     * 
     * Time Complexity: O(m + n) - amortized, each position added/removed once
     * Space Complexity: O(m) - deque stores positions in worst case
     * 
     * Best when: Sparse relevant characters, want to optimize shrinking phase
     * Worst when: Most characters relevant, standard approach simpler
     */
    std::string minWindowDeque(std::string s, std::string t);

    /**
     * Approach 6: Brute Force with Pruning (Baseline)
     * 
     * Check all possible substrings with optimizations to avoid redundant work.
     * 
     * Reasoning: Brute force approach for comparison and validation. Check every
     * possible substring of s to see if it contains all characters of t. Use
     * pruning optimizations: skip if substring shorter than t, early termination
     * when valid window found at current start position. While O(m²) in worst case,
     * provides baseline for correctness verification and performs reasonably on
     * small inputs. Useful for testing and understanding problem constraints.
     * 
     * Time Complexity: O(m² × n) - m² substrings, n time to check each
     * Space Complexity: O(|Σ|) - character frequency tracking
     * 
     * Best when: Small inputs, correctness verification, educational baseline
     * Worst when: Large inputs where quadratic time prohibitive
     */
    std::string minWindowBruteForce(std::string s, std::string t);

private:
    // Helper functions for sliding window approach
    bool windowContainsTarget(const std::unordered_map<char, int>& windowCount,
                             const std::unordered_map<char, int>& targetCount);
    bool isValidWindow(const std::unordered_map<char, int>& windowCount,
                      const std::unordered_map<char, int>& targetCount);
    
    // Helper functions for array-based approach
    bool windowContainsTargetArray(const std::vector<int>& windowCount,
                                  const std::vector<int>& targetCount,
                                  const std::unordered_set<char>& targetChars);
    
    // Helper functions for filtered approach
    struct FilteredChar {
        char c;
        int index;
        FilteredChar(char ch, int idx) : c(ch), index(idx) {}
    };
    std::vector<FilteredChar> filterString(const std::string& s, const std::unordered_set<char>& targetChars);
    
    // Helper functions for two-pass approach
    struct WindowInfo {
        int start;
        int end;
        int length;
        WindowInfo(int s, int e) : start(s), end(e), length(e - s + 1) {}
    };
    std::vector<WindowInfo> findAllValidWindows(const std::string& s, const std::string& t);
    WindowInfo findMinimumWindow(const std::vector<WindowInfo>& windows);
    
    // Helper functions for deque approach
    void addCharToWindow(char c, int pos, std::unordered_map<char, int>& windowCount,
                        std::deque<int>& positions, const std::unordered_set<char>& targetChars);
    void removeCharFromWindow(char c, std::unordered_map<char, int>& windowCount);
    
    // Helper functions for brute force approach
    bool containsAllChars(const std::string& window, const std::string& t);
    std::unordered_map<char, int> getCharCount(const std::string& str);
};

}
}