#include "find_index_of_first_occurrence.h"
#include <unordered_map>
#include <cmath>

namespace leetcode {
namespace easy {

int FindIndexOfFirstOccurrence::strStrBruteForce(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    if (needle.length() > haystack.length()) return -1;
    
    for (int i = 0; i <= static_cast<int>(haystack.length()) - static_cast<int>(needle.length()); ++i) {
        int j = 0;
        while (j < needle.length() && haystack[i + j] == needle[j]) {
            ++j;
        }
        if (j == needle.length()) {
            return i;
        }
    }
    
    return -1;
}

int FindIndexOfFirstOccurrence::strStrSTL(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) : -1;
}

int FindIndexOfFirstOccurrence::strStrKMP(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    if (needle.length() > haystack.length()) return -1;
    
    std::vector<int> failure = computeFailureFunction(needle);
    
    int i = 0, j = 0;
    while (i < haystack.length()) {
        if (haystack[i] == needle[j]) {
            ++i;
            ++j;
            if (j == needle.length()) {
                return i - j;
            }
        } else if (j > 0) {
            j = failure[j - 1];
        } else {
            ++i;
        }
    }
    
    return -1;
}

std::vector<int> FindIndexOfFirstOccurrence::computeFailureFunction(const std::string& needle) {
    std::vector<int> failure(needle.length(), 0);
    int j = 0;
    
    for (int i = 1; i < needle.length(); ++i) {
        while (j > 0 && needle[i] != needle[j]) {
            j = failure[j - 1];
        }
        if (needle[i] == needle[j]) {
            ++j;
        }
        failure[i] = j;
    }
    
    return failure;
}

int FindIndexOfFirstOccurrence::strStrRabinKarp(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    if (needle.length() > haystack.length()) return -1;
    
    int needleLen = needle.length();
    long long needleHash = computeHash(needle, needleLen);
    long long haystackHash = computeHash(haystack, needleLen);
    
    long long pow = 1;
    for (int i = 0; i < needleLen - 1; ++i) {
        pow = (pow * 256) % PRIME;
    }
    
    for (int i = 0; i <= static_cast<int>(haystack.length()) - needleLen; ++i) {
        if (needleHash == haystackHash) {
            // Verify actual match to handle hash collisions
            bool match = true;
            for (int j = 0; j < needleLen; ++j) {
                if (haystack[i + j] != needle[j]) {
                    match = false;
                    break;
                }
            }
            if (match) return i;
        }
        
        // Compute rolling hash for next position
        if (i < static_cast<int>(haystack.length()) - needleLen) {
            haystackHash = rollingHash(haystackHash, haystack[i], haystack[i + needleLen], pow);
        }
    }
    
    return -1;
}

long long FindIndexOfFirstOccurrence::computeHash(const std::string& str, int len) {
    long long hash = 0;
    for (int i = 0; i < len; ++i) {
        hash = (hash * 256 + str[i]) % PRIME;
    }
    return hash;
}

long long FindIndexOfFirstOccurrence::rollingHash(long long oldHash, char oldChar, char newChar, long long pow) {
    return ((oldHash - (oldChar * pow) % PRIME + PRIME) * 256 + newChar) % PRIME;
}

int FindIndexOfFirstOccurrence::strStrTwoPointers(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    if (needle.length() > haystack.length()) return -1;
    
    int i = 0, j = 0;
    int start = 0;
    
    while (i < haystack.length() && j < needle.length()) {
        if (haystack[i] == needle[j]) {
            ++i;
            ++j;
            if (j == needle.length()) {
                return start;
            }
        } else {
            ++start;
            i = start;
            j = 0;
            if (start > static_cast<int>(haystack.length()) - static_cast<int>(needle.length())) {
                break;
            }
        }
    }
    
    return -1;
}

int FindIndexOfFirstOccurrence::strStrBoyerMooreSimple(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    if (needle.length() > haystack.length()) return -1;
    
    std::vector<int> lastOcc = buildLastOccurrence(needle);
    
    int i = needle.length() - 1;  // Start from end of first potential match
    
    while (i < haystack.length()) {
        int j = needle.length() - 1;  // Start comparing from end of needle
        int k = i;
        
        // Compare backwards
        while (j >= 0 && haystack[k] == needle[j]) {
            --j;
            --k;
        }
        
        if (j < 0) {
            return k + 1;  // Found match
        }
        
        // Skip based on bad character rule
        char badChar = haystack[k];
        int skip = std::max(1, j - lastOcc[static_cast<unsigned char>(badChar)]);
        i += skip;
    }
    
    return -1;
}

std::vector<int> FindIndexOfFirstOccurrence::buildLastOccurrence(const std::string& needle) {
    std::vector<int> lastOcc(256, -1);  // ASCII characters
    
    for (int i = 0; i < needle.length(); ++i) {
        lastOcc[static_cast<unsigned char>(needle[i])] = i;
    }
    
    return lastOcc;
}

}
}