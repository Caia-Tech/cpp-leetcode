#include "valid_palindrome.h"
#include <unordered_map>

namespace leetcode {
namespace easy {

bool ValidPalindrome::isPalindromeOptimal(std::string s) {
    int left = 0, right = s.length() - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters from left
        while (left < right && !isAlphanumeric(s[left])) {
            left++;
        }
        
        // Skip non-alphanumeric characters from right
        while (left < right && !isAlphanumeric(s[right])) {
            right--;
        }
        
        // Compare normalized characters
        if (normalize(s[left]) != normalize(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

bool ValidPalindrome::isPalindromeCleanFirst(std::string s) {
    // Clean the string: keep only alphanumeric, convert to lowercase
    std::string cleaned = cleanString(s);
    
    // Check if cleaned string is palindrome
    int left = 0, right = cleaned.length() - 1;
    
    while (left < right) {
        if (cleaned[left] != cleaned[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

bool ValidPalindrome::isPalindromeRecursive(std::string s) {
    return recursiveHelper(s, 0, s.length() - 1);
}

bool ValidPalindrome::isPalindromeSTL(std::string s) {
    // Clean string using STL algorithms
    std::string cleaned;
    
    // Copy only alphanumeric characters and convert to lowercase
    std::copy_if(s.begin(), s.end(), std::back_inserter(cleaned),
                [this](char c) { return isAlphanumericSTL(c); });
    
    // Convert to lowercase
    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(),
                  [this](char c) { return toLowerSTL(c); });
    
    // Check palindrome using std::equal with reverse iterator
    return std::equal(cleaned.begin(), cleaned.begin() + cleaned.length() / 2,
                     cleaned.rbegin());
}

bool ValidPalindrome::isPalindromeIndexBased(std::string s) {
    int n = s.length();
    int left = 0, right = n - 1;
    
    while (left < right) {
        // Find next valid character from left
        while (left < n && !isValidChar(s[left])) {
            left++;
        }
        
        // Find next valid character from right
        while (right >= 0 && !isValidChar(s[right])) {
            right--;
        }
        
        // If we've crossed, we're done
        if (left >= right) {
            break;
        }
        
        // Compare normalized characters
        if (std::tolower(s[left]) != std::tolower(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

bool ValidPalindrome::isPalindromeFrequency(std::string s) {
    // Count frequency of each alphanumeric character
    std::unordered_map<char, int> freq;
    
    for (char c : s) {
        if (isAlphanumeric(c)) {
            char normalized = normalize(c);
            freq[normalized]++;
        }
    }
    
    // Count characters with odd frequency
    int oddCount = 0;
    for (const auto& pair : freq) {
        if (pair.second % 2 == 1) {
            oddCount++;
        }
    }
    
    // For palindrome: at most one character can have odd frequency
    return oddCount <= 1;
}

// Helper function implementations
bool ValidPalindrome::isAlphanumeric(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= '0' && c <= '9');
}

char ValidPalindrome::normalize(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a'; // Convert to lowercase
    }
    return c;
}

bool ValidPalindrome::isValidChar(char c) {
    return isAlphanumeric(c);
}

std::string ValidPalindrome::cleanString(const std::string& s) {
    std::string result;
    
    for (char c : s) {
        if (isAlphanumeric(c)) {
            result += normalize(c);
        }
    }
    
    return result;
}

bool ValidPalindrome::recursiveHelper(const std::string& s, int left, int right) {
    // Base case: pointers have met or crossed
    if (left >= right) {
        return true;
    }
    
    // Skip non-alphanumeric from left
    if (!isAlphanumeric(s[left])) {
        return recursiveHelper(s, left + 1, right);
    }
    
    // Skip non-alphanumeric from right
    if (!isAlphanumeric(s[right])) {
        return recursiveHelper(s, left, right - 1);
    }
    
    // Compare current characters
    if (normalize(s[left]) != normalize(s[right])) {
        return false;
    }
    
    // Recursively check inner substring
    return recursiveHelper(s, left + 1, right - 1);
}

bool ValidPalindrome::isAlphanumericSTL(char c) {
    return std::isalnum(static_cast<unsigned char>(c));
}

char ValidPalindrome::toLowerSTL(char c) {
    return std::tolower(static_cast<unsigned char>(c));
}

}
}