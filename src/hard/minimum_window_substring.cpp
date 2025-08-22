#include "minimum_window_substring.h"
#include <algorithm>

namespace leetcode {
namespace hard {

// Approach 1: Sliding Window with Hash Map (Optimal)
std::string MinimumWindowSubstring::minWindow(std::string s, std::string t) {
    if (s.empty() || t.empty() || s.length() < t.length()) {
        return "";
    }
    
    // Build target character frequency map
    std::unordered_map<char, int> targetCount;
    for (char c : t) {
        targetCount[c]++;
    }
    
    int required = targetCount.size(); // Number of unique characters in t
    int formed = 0; // Number of unique characters with desired frequency in current window
    
    std::unordered_map<char, int> windowCount;
    
    // Sliding window pointers
    int left = 0, right = 0;
    
    // Result tracking
    int minLen = INT_MAX;
    int minStart = 0;
    
    while (right < s.length()) {
        // Expand window by including character at right
        char rightChar = s[right];
        windowCount[rightChar]++;
        
        // Check if this character's frequency matches target frequency
        if (targetCount.count(rightChar) && windowCount[rightChar] == targetCount[rightChar]) {
            formed++;
        }
        
        // Try to contract window from left while it's still valid
        while (formed == required && left <= right) {
            // Update result if this window is smaller
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            
            // Remove character at left from window
            char leftChar = s[left];
            windowCount[leftChar]--;
            
            if (targetCount.count(leftChar) && windowCount[leftChar] < targetCount[leftChar]) {
                formed--;
            }
            
            left++;
        }
        
        right++;
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

// Approach 2: Sliding Window with Array (Space Optimized)
std::string MinimumWindowSubstring::minWindowArray(std::string s, std::string t) {
    if (s.empty() || t.empty() || s.length() < t.length()) {
        return "";
    }
    
    // Use arrays for character counting (ASCII)
    std::vector<int> targetCount(128, 0);
    std::vector<int> windowCount(128, 0);
    std::unordered_set<char> targetChars;
    
    // Build target character frequency
    for (char c : t) {
        targetCount[c]++;
        targetChars.insert(c);
    }
    
    int required = targetChars.size();
    int formed = 0;
    
    int left = 0, right = 0;
    int minLen = INT_MAX;
    int minStart = 0;
    
    while (right < s.length()) {
        char rightChar = s[right];
        windowCount[rightChar]++;
        
        if (targetChars.count(rightChar) && windowCount[rightChar] == targetCount[rightChar]) {
            formed++;
        }
        
        while (formed == required && left <= right) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            
            char leftChar = s[left];
            windowCount[leftChar]--;
            
            if (targetChars.count(leftChar) && windowCount[leftChar] < targetCount[leftChar]) {
                formed--;
            }
            
            left++;
        }
        
        right++;
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

// Approach 3: Optimized Sliding Window with Filtered String
std::string MinimumWindowSubstring::minWindowFiltered(std::string s, std::string t) {
    if (s.empty() || t.empty() || s.length() < t.length()) {
        return "";
    }
    
    // Build target set and frequency map
    std::unordered_set<char> targetChars;
    std::unordered_map<char, int> targetCount;
    for (char c : t) {
        targetChars.insert(c);
        targetCount[c]++;
    }
    
    // Filter string s to only include relevant characters
    std::vector<FilteredChar> filtered = filterString(s, targetChars);
    
    if (filtered.size() < t.length()) {
        return "";
    }
    
    int required = targetCount.size();
    int formed = 0;
    std::unordered_map<char, int> windowCount;
    
    int left = 0, right = 0;
    int minLen = INT_MAX;
    int minStart = 0, minEnd = 0;
    
    while (right < filtered.size()) {
        char rightChar = filtered[right].c;
        windowCount[rightChar]++;
        
        if (windowCount[rightChar] == targetCount[rightChar]) {
            formed++;
        }
        
        while (formed == required && left <= right) {
            int windowLen = filtered[right].index - filtered[left].index + 1;
            if (windowLen < minLen) {
                minLen = windowLen;
                minStart = filtered[left].index;
                minEnd = filtered[right].index;
            }
            
            char leftChar = filtered[left].c;
            windowCount[leftChar]--;
            
            if (windowCount[leftChar] < targetCount[leftChar]) {
                formed--;
            }
            
            left++;
        }
        
        right++;
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minEnd - minStart + 1);
}

// Approach 4: Two-Pass Algorithm (Educational)
std::string MinimumWindowSubstring::minWindowTwoPass(std::string s, std::string t) {
    if (s.empty() || t.empty() || s.length() < t.length()) {
        return "";
    }
    
    // First pass: find all valid windows
    std::vector<WindowInfo> validWindows = findAllValidWindows(s, t);
    
    if (validWindows.empty()) {
        return "";
    }
    
    // Second pass: find minimum window
    WindowInfo minWindow = findMinimumWindow(validWindows);
    
    return s.substr(minWindow.start, minWindow.length);
}

// Approach 5: Sliding Window with Deque Optimization
std::string MinimumWindowSubstring::minWindowDeque(std::string s, std::string t) {
    if (s.empty() || t.empty() || s.length() < t.length()) {
        return "";
    }
    
    std::unordered_map<char, int> targetCount;
    std::unordered_set<char> targetChars;
    
    for (char c : t) {
        targetCount[c]++;
        targetChars.insert(c);
    }
    
    std::unordered_map<char, int> windowCount;
    std::deque<int> relevantPositions; // Store positions of relevant characters
    
    int required = targetCount.size();
    int formed = 0;
    int minLen = INT_MAX;
    int minStart = 0;
    
    for (int right = 0; right < s.length(); right++) {
        char rightChar = s[right];
        
        if (targetChars.count(rightChar)) {
            windowCount[rightChar]++;
            relevantPositions.push_back(right);
            
            if (windowCount[rightChar] == targetCount[rightChar]) {
                formed++;
            }
            
            // Contract window from left
            while (formed == required && !relevantPositions.empty()) {
                int left = relevantPositions.front();
                int windowLen = right - left + 1;
                
                if (windowLen < minLen) {
                    minLen = windowLen;
                    minStart = left;
                }
                
                // Remove leftmost relevant character
                char leftChar = s[left];
                windowCount[leftChar]--;
                relevantPositions.pop_front();
                
                if (windowCount[leftChar] < targetCount[leftChar]) {
                    formed--;
                }
            }
        }
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

// Approach 6: Brute Force with Pruning (Baseline)
std::string MinimumWindowSubstring::minWindowBruteForce(std::string s, std::string t) {
    if (s.empty() || t.empty() || s.length() < t.length()) {
        return "";
    }
    
    std::unordered_map<char, int> targetCount = getCharCount(t);
    
    int minLen = INT_MAX;
    int minStart = 0;
    
    for (int i = 0; i <= (int)s.length() - (int)t.length(); i++) {
        for (int j = i + t.length() - 1; j < s.length(); j++) {
            std::string window = s.substr(i, j - i + 1);
            
            if (containsAllChars(window, t)) {
                if (window.length() < minLen) {
                    minLen = window.length();
                    minStart = i;
                }
                break; // Found valid window starting at i, no need to check longer ones
            }
        }
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

// Helper function implementations

bool MinimumWindowSubstring::windowContainsTarget(const std::unordered_map<char, int>& windowCount,
                                                 const std::unordered_map<char, int>& targetCount) {
    for (const auto& pair : targetCount) {
        if (windowCount.count(pair.first) == 0 || windowCount.at(pair.first) < pair.second) {
            return false;
        }
    }
    return true;
}

bool MinimumWindowSubstring::isValidWindow(const std::unordered_map<char, int>& windowCount,
                                          const std::unordered_map<char, int>& targetCount) {
    return windowContainsTarget(windowCount, targetCount);
}

bool MinimumWindowSubstring::windowContainsTargetArray(const std::vector<int>& windowCount,
                                                      const std::vector<int>& targetCount,
                                                      const std::unordered_set<char>& targetChars) {
    for (char c : targetChars) {
        if (windowCount[c] < targetCount[c]) {
            return false;
        }
    }
    return true;
}

std::vector<MinimumWindowSubstring::FilteredChar> MinimumWindowSubstring::filterString(
    const std::string& s, const std::unordered_set<char>& targetChars) {
    std::vector<FilteredChar> filtered;
    
    for (int i = 0; i < s.length(); i++) {
        if (targetChars.count(s[i])) {
            filtered.emplace_back(s[i], i);
        }
    }
    
    return filtered;
}

std::vector<MinimumWindowSubstring::WindowInfo> MinimumWindowSubstring::findAllValidWindows(
    const std::string& s, const std::string& t) {
    std::vector<WindowInfo> validWindows;
    std::unordered_map<char, int> targetCount = getCharCount(t);
    
    int required = targetCount.size();
    int formed = 0;
    std::unordered_map<char, int> windowCount;
    
    int left = 0;
    
    for (int right = 0; right < s.length(); right++) {
        char rightChar = s[right];
        windowCount[rightChar]++;
        
        if (targetCount.count(rightChar) && windowCount[rightChar] == targetCount[rightChar]) {
            formed++;
        }
        
        while (formed == required && left <= right) {
            validWindows.emplace_back(left, right);
            
            char leftChar = s[left];
            windowCount[leftChar]--;
            
            if (targetCount.count(leftChar) && windowCount[leftChar] < targetCount[leftChar]) {
                formed--;
            }
            
            left++;
        }
    }
    
    return validWindows;
}

MinimumWindowSubstring::WindowInfo MinimumWindowSubstring::findMinimumWindow(
    const std::vector<WindowInfo>& windows) {
    WindowInfo minWindow = windows[0];
    
    for (const auto& window : windows) {
        if (window.length < minWindow.length) {
            minWindow = window;
        }
    }
    
    return minWindow;
}

void MinimumWindowSubstring::addCharToWindow(char c, int pos, std::unordered_map<char, int>& windowCount,
                                           std::deque<int>& positions, const std::unordered_set<char>& targetChars) {
    if (targetChars.count(c)) {
        windowCount[c]++;
        positions.push_back(pos);
    }
}

void MinimumWindowSubstring::removeCharFromWindow(char c, std::unordered_map<char, int>& windowCount) {
    windowCount[c]--;
}

bool MinimumWindowSubstring::containsAllChars(const std::string& window, const std::string& t) {
    std::unordered_map<char, int> windowCount = getCharCount(window);
    std::unordered_map<char, int> targetCount = getCharCount(t);
    
    return windowContainsTarget(windowCount, targetCount);
}

std::unordered_map<char, int> MinimumWindowSubstring::getCharCount(const std::string& str) {
    std::unordered_map<char, int> count;
    for (char c : str) {
        count[c]++;
    }
    return count;
}

}
}