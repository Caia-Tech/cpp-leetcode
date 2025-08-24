#include "valid_anagram.h"
#include <unordered_map>
#include <algorithm>

namespace leetcode {
namespace easy {

// Prime numbers for characters 'a' to 'z'
const long long ValidAnagram::primes[26] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101
};

// Approach 1: Sorting (Classic)
bool ValidAnagram::isAnagramSorting(std::string s, std::string t) {
    // Early termination: different lengths can't be anagrams
    if (s.length() != t.length()) {
        return false;
    }
    
    // Sort both strings and compare
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());
    
    return s == t;
}

// Approach 2: Character Count Array (Optimal for lowercase)
bool ValidAnagram::isAnagramCharArray(std::string s, std::string t) {
    // Early termination: different lengths can't be anagrams
    if (s.length() != t.length()) {
        return false;
    }
    
    // Fixed array for 26 lowercase letters
    int charCount[26] = {0};
    
    // Count characters from both strings
    for (size_t i = 0; i < s.length(); ++i) {
        charCount[s[i] - 'a']++;     // Increment for s
        charCount[t[i] - 'a']--;     // Decrement for t
    }
    
    // Check if all counts are zero
    for (int count : charCount) {
        if (count != 0) {
            return false;
        }
    }
    
    return true;
}

// Approach 3: Hash Map Counting
bool ValidAnagram::isAnagramHashMap(std::string s, std::string t) {
    // Early termination: different lengths can't be anagrams
    if (s.length() != t.length()) {
        return false;
    }
    
    std::unordered_map<char, int> charCount;
    
    // Count characters in first string
    for (char c : s) {
        charCount[c]++;
    }
    
    // Decrement counts for second string
    for (char c : t) {
        charCount[c]--;
        // If count becomes negative, not an anagram
        if (charCount[c] < 0) {
            return false;
        }
    }
    
    // Check if all counts are zero
    for (const auto& pair : charCount) {
        if (pair.second != 0) {
            return false;
        }
    }
    
    return true;
}

// Approach 4: Single Hash Map Pass
bool ValidAnagram::isAnagramSinglePass(std::string s, std::string t) {
    // Early termination: different lengths can't be anagrams
    if (s.length() != t.length()) {
        return false;
    }
    
    std::unordered_map<char, int> charCount;
    
    // Process both strings simultaneously
    for (size_t i = 0; i < s.length(); ++i) {
        charCount[s[i]]++;  // Increment for s
        charCount[t[i]]--;  // Decrement for t
    }
    
    // Check if all counts are zero
    for (const auto& pair : charCount) {
        if (pair.second != 0) {
            return false;
        }
    }
    
    return true;
}

// Approach 5: Bit Manipulation (XOR) - FLAWED APPROACH
bool ValidAnagram::isAnagramXOR(std::string s, std::string t) {
    // Early termination: different lengths can't be anagrams
    if (s.length() != t.length()) {
        return false;
    }
    
    // WARNING: This approach is mathematically flawed!
    // It only works for some cases but fails for others
    // Example: "aab" vs "abb" would incorrectly return true
    // Included only for educational purposes
    
    int xor_result = 0;
    
    // XOR all characters from both strings
    for (size_t i = 0; i < s.length(); ++i) {
        xor_result ^= s[i];  // XOR character from s
        xor_result ^= t[i];  // XOR character from t
    }
    
    // If result is 0, it might suggest anagram (but this is incorrect logic)
    return xor_result == 0;
}

// Approach 6: Prime Number Multiplication
bool ValidAnagram::isAnagramPrime(std::string s, std::string t) {
    // Early termination: different lengths can't be anagrams
    if (s.length() != t.length()) {
        return false;
    }
    
    long long product_s = 1;
    long long product_t = 1;
    
    // Calculate products for both strings
    for (size_t i = 0; i < s.length(); ++i) {
        // Check for potential overflow
        if (product_s > LLONG_MAX / getPrime(s[i]) ||
            product_t > LLONG_MAX / getPrime(t[i])) {
            // Fallback to safer approach on overflow risk
            return isAnagramCharArray(s, t);
        }
        
        product_s *= getPrime(s[i]);
        product_t *= getPrime(t[i]);
    }
    
    return product_s == product_t;
}

}  // namespace easy
}  // namespace leetcode