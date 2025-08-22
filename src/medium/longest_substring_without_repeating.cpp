#include "longest_substring_without_repeating.h"
#include <algorithm>
#include <vector>

namespace leetcode {
namespace medium {

bool LongestSubstringWithoutRepeating::hasUniqueCharacters(const std::string& s, int start, int end) {
    std::unordered_set<char> chars;
    for (int i = start; i <= end; ++i) {
        if (chars.find(s[i]) != chars.end()) {
            return false;
        }
        chars.insert(s[i]);
    }
    return true;
}

int LongestSubstringWithoutRepeating::lengthOfLongestSubstringBruteForce(const std::string& s) {
    int n = s.length();
    int maxLength = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (hasUniqueCharacters(s, i, j)) {
                maxLength = std::max(maxLength, j - i + 1);
            }
        }
    }
    
    return maxLength;
}

int LongestSubstringWithoutRepeating::lengthOfLongestSubstringHashSet(const std::string& s) {
    std::unordered_set<char> chars;
    int maxLength = 0;
    int left = 0, right = 0;
    
    while (right < s.length()) {
        if (chars.find(s[right]) == chars.end()) {
            chars.insert(s[right]);
            maxLength = std::max(maxLength, right - left + 1);
            right++;
        } else {
            chars.erase(s[left]);
            left++;
        }
    }
    
    return maxLength;
}

int LongestSubstringWithoutRepeating::lengthOfLongestSubstringHashMap(const std::string& s) {
    std::unordered_map<char, int> charIndex;
    int maxLength = 0;
    int left = 0;
    
    for (int right = 0; right < s.length(); ++right) {
        if (charIndex.find(s[right]) != charIndex.end()) {
            left = std::max(left, charIndex[s[right]] + 1);
        }
        charIndex[s[right]] = right;
        maxLength = std::max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

int LongestSubstringWithoutRepeating::lengthOfLongestSubstringASCII(const std::string& s) {
    std::vector<int> charIndex(128, -1);
    int maxLength = 0;
    int left = 0;
    
    for (int right = 0; right < s.length(); ++right) {
        if (charIndex[s[right]] >= left) {
            left = charIndex[s[right]] + 1;
        }
        charIndex[s[right]] = right;
        maxLength = std::max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

int LongestSubstringWithoutRepeating::lengthOfLongestSubstringDP(const std::string& s) {
    if (s.empty()) return 0;
    
    int n = s.length();
    std::vector<int> dp(n, 0);
    dp[0] = 1;
    int maxLength = 1;
    std::unordered_map<char, int> lastSeen;
    lastSeen[s[0]] = 0;
    
    for (int i = 1; i < n; ++i) {
        if (lastSeen.find(s[i]) == lastSeen.end() || 
            lastSeen[s[i]] < i - dp[i - 1]) {
            dp[i] = dp[i - 1] + 1;
        } else {
            dp[i] = i - lastSeen[s[i]];
        }
        lastSeen[s[i]] = i;
        maxLength = std::max(maxLength, dp[i]);
    }
    
    return maxLength;
}

int LongestSubstringWithoutRepeating::lengthOfLongestSubstringTwoPointers(const std::string& s) {
    std::unordered_map<char, int> charCount;
    int maxLength = 0;
    int left = 0;
    
    for (int right = 0; right < s.length(); ++right) {
        charCount[s[right]]++;
        
        while (charCount[s[right]] > 1) {
            charCount[s[left]]--;
            if (charCount[s[left]] == 0) {
                charCount.erase(s[left]);
            }
            left++;
        }
        
        maxLength = std::max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

}
}