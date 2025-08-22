#include "longest_palindromic_substring.h"
#include <unordered_map>
#include <climits>

namespace leetcode {
namespace medium {

std::string LongestPalindromicSubstring::longestPalindromeExpandCenter(std::string s) {
    if (s.empty()) return "";
    
    int start = 0, maxLen = 1;
    
    for (int i = 0; i < s.length(); ++i) {
        // Check for odd-length palindromes (center at i)
        int len1 = expandAroundCenter(s, i, i);
        
        // Check for even-length palindromes (center between i and i+1)
        int len2 = expandAroundCenter(s, i, i + 1);
        
        int currentMax = std::max(len1, len2);
        
        if (currentMax > maxLen) {
            maxLen = currentMax;
            // Calculate starting position
            start = i - (currentMax - 1) / 2;
        }
    }
    
    return s.substr(start, maxLen);
}

std::string LongestPalindromicSubstring::longestPalindromeDP(std::string s) {
    int n = s.length();
    if (n == 0) return "";
    
    // dp[i][j] represents whether s[i...j] is palindrome
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    
    int start = 0, maxLen = 1;
    
    // Single characters are always palindromes
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }
    
    // Check for palindromes of length 2
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }
    
    // Check for palindromes of length 3 and above
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            
            // Check if s[i...j] is palindrome
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                maxLen = len;
            }
        }
    }
    
    return s.substr(start, maxLen);
}

std::string LongestPalindromicSubstring::longestPalindromeManacher(std::string s) {
    if (s.empty()) return "";
    
    // Preprocess string: "abc" becomes "^#a#b#c#$"
    std::string processed = preprocessForManacher(s);
    int n = processed.length();
    
    std::vector<int> P(n, 0); // P[i] = radius of palindrome centered at i
    int center = 0, right = 0; // rightmost palindrome boundary
    
    int maxLen = 0, centerIndex = 0;
    
    for (int i = 1; i < n - 1; ++i) {
        // Mirror of i with respect to center
        int mirror = 2 * center - i;
        
        // If i is within right boundary, we can use previously computed values
        if (i < right) {
            P[i] = std::min(right - i, P[mirror]);
        }
        
        // Try to expand palindrome centered at i
        while (processed[i + 1 + P[i]] == processed[i - 1 - P[i]]) {
            P[i]++;
        }
        
        // If palindrome centered at i extends past right, adjust center and right
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
        
        // Update maximum length palindrome found
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    
    // Extract the longest palindrome from original string
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

std::string LongestPalindromicSubstring::longestPalindromeBruteForce(std::string s) {
    int n = s.length();
    if (n == 0) return "";
    
    std::string longest = "";
    
    // Check all possible substrings, starting from longest
    for (int len = n; len >= 1; --len) {
        for (int i = 0; i <= n - len; ++i) {
            if (isPalindrome(s, i, i + len - 1)) {
                return s.substr(i, len);
            }
        }
    }
    
    return s.substr(0, 1); // Single character fallback
}

std::string LongestPalindromicSubstring::longestPalindromeSuffixArray(std::string s) {
    if (s.empty()) return "";
    
    int n = s.length();
    std::string reversed = s;
    std::reverse(reversed.begin(), reversed.end());
    
    // Create combined string: original + separator + reversed
    std::string combined = s + "#" + reversed;
    
    std::vector<int> suffixArray = buildSuffixArray(combined);
    std::vector<int> lcpArray = computeLCPArray(combined, suffixArray);
    
    int maxLen = 1, start = 0;
    
    // Find longest common prefix between suffixes from original and reversed parts
    for (int i = 1; i < suffixArray.size(); ++i) {
        int pos1 = suffixArray[i - 1];
        int pos2 = suffixArray[i];
        
        // Check if one suffix is from original string and other from reversed
        bool fromDifferentParts = (pos1 <= n && pos2 > n) || (pos1 > n && pos2 <= n);
        
        if (fromDifferentParts && lcpArray[i] > maxLen) {
            // Verify this corresponds to a valid palindrome
            int originalPos = (pos1 <= n) ? pos1 : pos2 - n - 1;
            if (originalPos + lcpArray[i] <= n) {
                maxLen = lcpArray[i];
                start = originalPos;
            }
        }
    }
    
    return s.substr(start, maxLen);
}

std::string LongestPalindromicSubstring::longestPalindromeRollingHash(std::string s) {
    if (s.empty()) return "";
    
    int n = s.length();
    int start = 0, maxLen = 1;
    
    for (int i = 0; i < n; ++i) {
        // Check odd-length palindromes
        int left = i, right = i;
        while (left >= 0 && right < n) {
            // Use rolling hash for quick check
            long long forwardHash = computeHash(s, left, right - left + 1);
            long long reverseHash = computeReverseHash(s, left, right - left + 1);
            
            if (forwardHash == reverseHash) {
                // Verify with actual comparison (handle hash collisions)
                if (isPalindrome(s, left, right)) {
                    if (right - left + 1 > maxLen) {
                        maxLen = right - left + 1;
                        start = left;
                    }
                    left--;
                    right++;
                } else {
                    break; // Hash collision, stop expansion
                }
            } else {
                break;
            }
        }
        
        // Check even-length palindromes
        left = i;
        right = i + 1;
        while (left >= 0 && right < n) {
            long long forwardHash = computeHash(s, left, right - left + 1);
            long long reverseHash = computeReverseHash(s, left, right - left + 1);
            
            if (forwardHash == reverseHash) {
                if (isPalindrome(s, left, right)) {
                    if (right - left + 1 > maxLen) {
                        maxLen = right - left + 1;
                        start = left;
                    }
                    left--;
                    right++;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
    
    return s.substr(start, maxLen);
}

// Helper function implementations
int LongestPalindromicSubstring::expandAroundCenter(const std::string& s, int left, int right) {
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

bool LongestPalindromicSubstring::isPalindrome(const std::string& s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

std::string LongestPalindromicSubstring::preprocessForManacher(const std::string& s) {
    std::string result = "^";
    for (char c : s) {
        result += "#" + std::string(1, c);
    }
    result += "#$";
    return result;
}

std::vector<int> LongestPalindromicSubstring::buildSuffixArray(const std::string& s) {
    int n = s.length();
    std::vector<int> suffixArray(n);
    
    // Simple O(n^2 log n) implementation for clarity
    // In practice, would use O(n log n) or O(n) algorithms
    std::vector<std::pair<std::string, int>> suffixes;
    
    for (int i = 0; i < n; ++i) {
        suffixes.push_back({s.substr(i), i});
    }
    
    std::sort(suffixes.begin(), suffixes.end());
    
    for (int i = 0; i < n; ++i) {
        suffixArray[i] = suffixes[i].second;
    }
    
    return suffixArray;
}

std::vector<int> LongestPalindromicSubstring::computeLCPArray(const std::string& s, const std::vector<int>& suffixArray) {
    int n = s.length();
    std::vector<int> lcp(n, 0);
    
    for (int i = 1; i < n; ++i) {
        int pos1 = suffixArray[i - 1];
        int pos2 = suffixArray[i];
        
        int commonLen = 0;
        while (pos1 + commonLen < n && pos2 + commonLen < n && 
               s[pos1 + commonLen] == s[pos2 + commonLen]) {
            commonLen++;
        }
        
        lcp[i] = commonLen;
    }
    
    return lcp;
}

long long LongestPalindromicSubstring::computeHash(const std::string& s, int start, int len) {
    long long hash = 0;
    long long power = 1;
    
    for (int i = 0; i < len; ++i) {
        hash = (hash + (s[start + i] * power) % MOD) % MOD;
        power = (power * BASE) % MOD;
    }
    
    return hash;
}

long long LongestPalindromicSubstring::computeReverseHash(const std::string& s, int start, int len) {
    long long hash = 0;
    long long power = 1;
    
    for (int i = len - 1; i >= 0; --i) {
        hash = (hash + (s[start + i] * power) % MOD) % MOD;
        power = (power * BASE) % MOD;
    }
    
    return hash;
}

}
}