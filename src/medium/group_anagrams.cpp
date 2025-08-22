#include "group_anagrams.h"

namespace leetcode {
namespace medium {

// Prime numbers for a-z (first 26 primes)
const std::vector<long long> GroupAnagrams::PRIMES = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101
};

std::vector<std::vector<std::string>> GroupAnagrams::groupAnagramsSorting(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> anagramGroups;
    
    for (const std::string& str : strs) {
        // Create sorted version as key
        std::string sortedStr = str;
        std::sort(sortedStr.begin(), sortedStr.end());
        
        // Group by sorted string
        anagramGroups[sortedStr].push_back(str);
    }
    
    // Convert map to result vector
    std::vector<std::vector<std::string>> result;
    for (const auto& pair : anagramGroups) {
        result.push_back(pair.second);
    }
    
    return result;
}

std::vector<std::vector<std::string>> GroupAnagrams::groupAnagramsFrequency(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> anagramGroups;
    
    for (const std::string& str : strs) {
        // Create frequency-based key
        std::string frequencyKey = getFrequencyString(str);
        
        // Group by frequency signature
        anagramGroups[frequencyKey].push_back(str);
    }
    
    // Convert map to result vector
    std::vector<std::vector<std::string>> result;
    for (const auto& pair : anagramGroups) {
        result.push_back(pair.second);
    }
    
    return result;
}

std::vector<std::vector<std::string>> GroupAnagrams::groupAnagramsPrime(std::vector<std::string>& strs) {
    std::unordered_map<long long, std::vector<std::string>> anagramGroups;
    
    for (const std::string& str : strs) {
        // Create prime product as key
        long long primeProduct = getPrimeProduct(str);
        
        // Group by prime product
        anagramGroups[primeProduct].push_back(str);
    }
    
    // Convert map to result vector
    std::vector<std::vector<std::string>> result;
    for (const auto& pair : anagramGroups) {
        result.push_back(pair.second);
    }
    
    return result;
}

std::vector<std::vector<std::string>> GroupAnagrams::groupAnagramsArray(std::vector<std::string>& strs) {
    std::unordered_map<std::array<int, 26>, std::vector<std::string>, ArrayHash> anagramGroups;
    
    for (const std::string& str : strs) {
        // Create frequency array as key
        std::vector<int> tempFreq = getFrequencyArray(str);
        std::array<int, 26> frequencyArray;
        std::copy(tempFreq.begin(), tempFreq.end(), frequencyArray.begin());
        
        // Group by frequency array
        anagramGroups[frequencyArray].push_back(str);
    }
    
    // Convert map to result vector
    std::vector<std::vector<std::string>> result;
    for (const auto& pair : anagramGroups) {
        result.push_back(pair.second);
    }
    
    return result;
}

std::vector<std::vector<std::string>> GroupAnagrams::groupAnagramsTrie(std::vector<std::string>& strs) {
    TrieNode* root = new TrieNode();
    
    // Insert all strings into trie
    for (const std::string& str : strs) {
        insertIntoTrie(root, str);
    }
    
    // Collect anagram groups from trie
    std::vector<std::vector<std::string>> result;
    collectAnagramGroups(root, result);
    
    delete root;
    return result;
}

std::vector<std::vector<std::string>> GroupAnagrams::groupAnagramsRollingHash(std::vector<std::string>& strs) {
    std::unordered_map<long long, std::vector<std::string>> anagramGroups;
    
    for (const std::string& str : strs) {
        // Create rolling hash as key
        long long hash = getRollingHash(str);
        
        // Group by hash value
        anagramGroups[hash].push_back(str);
    }
    
    // Convert map to result vector
    std::vector<std::vector<std::string>> result;
    for (const auto& pair : anagramGroups) {
        result.push_back(pair.second);
    }
    
    return result;
}

std::string GroupAnagrams::getFrequencyString(const std::string& str) {
    std::vector<int> count(26, 0);
    
    // Count character frequencies
    for (char c : str) {
        count[c - 'a']++;
    }
    
    // Build frequency string: "a1b2c0d1..." format
    std::string result;
    for (int i = 0; i < 26; ++i) {
        result += static_cast<char>('a' + i);
        result += std::to_string(count[i]);
    }
    
    return result;
}

long long GroupAnagrams::getPrimeProduct(const std::string& str) {
    long long product = 1;
    
    for (char c : str) {
        product *= PRIMES[c - 'a'];
        
        // Check for potential overflow (basic protection)
        if (product < 0) {
            // Overflow detected, use alternative approach or handle error
            // For this implementation, we'll continue but this should be handled properly
            break;
        }
    }
    
    return product;
}

std::vector<int> GroupAnagrams::getFrequencyArray(const std::string& str) {
    std::vector<int> frequency(26, 0);
    
    for (char c : str) {
        frequency[c - 'a']++;
    }
    
    return frequency;
}

long long GroupAnagrams::getRollingHash(const std::string& str) {
    long long hash = 0;
    const long long base = 257; // Prime base for hashing
    
    // Sum of character values raised to consistent power
    // This ensures anagrams have same hash value
    for (char c : str) {
        long long charValue = c - 'a' + 1; // 1-26 for a-z
        hash += charValue * charValue * charValue; // Cubic to reduce collisions
    }
    
    return hash;
}

void GroupAnagrams::insertIntoTrie(TrieNode* root, const std::string& str) {
    // Create sorted version to follow consistent path
    std::string sortedStr = str;
    std::sort(sortedStr.begin(), sortedStr.end());
    
    TrieNode* current = root;
    
    // Follow path for each character in sorted string
    for (char c : sortedStr) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    
    // Store original string at leaf
    current->words.push_back(str);
}

void GroupAnagrams::collectAnagramGroups(TrieNode* root, std::vector<std::vector<std::string>>& result) {
    // If this node has words, it's a leaf with anagram group
    if (!root->words.empty()) {
        result.push_back(root->words);
    }
    
    // Recursively collect from children
    for (const auto& pair : root->children) {
        collectAnagramGroups(pair.second, result);
    }
}

}
}