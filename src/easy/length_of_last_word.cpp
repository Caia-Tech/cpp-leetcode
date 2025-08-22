#include "length_of_last_word.h"
#include <regex>

namespace leetcode {
namespace easy {

int LengthOfLastWord::lengthOfLastWordReverse(const std::string& s) {
    int length = 0;
    int i = s.length() - 1;
    
    // Skip trailing spaces
    while (i >= 0 && s[i] == ' ') {
        --i;
    }
    
    // Count characters of the last word
    while (i >= 0 && s[i] != ' ') {
        ++length;
        --i;
    }
    
    return length;
}

int LengthOfLastWord::lengthOfLastWordForward(const std::string& s) {
    int currentWordLength = 0;
    
    for (char c : s) {
        if (c == ' ') {
            // Reset current word length on space (but don't update result yet)
            currentWordLength = 0;
        } else {
            // Increment current word length
            ++currentWordLength;
        }
    }
    
    return currentWordLength;
}

int LengthOfLastWord::lengthOfLastWordStringStream(const std::string& s) {
    std::stringstream ss(s);
    std::string word;
    std::string lastWord;
    
    // Extract all words, keeping track of the last one
    while (ss >> word) {
        lastWord = word;
    }
    
    return lastWord.length();
}

int LengthOfLastWord::lengthOfLastWordSTL(const std::string& s) {
    // Find the position of the last non-space character
    size_t endPos = s.find_last_not_of(' ');
    if (endPos == std::string::npos) return 0;
    
    // Find the position of the space before the last word
    size_t startPos = s.rfind(' ', endPos);
    
    if (startPos == std::string::npos) {
        // No space found, entire string (up to endPos) is the last word
        return endPos + 1;
    } else {
        // Calculate length between start and end positions
        return endPos - startPos;
    }
}

int LengthOfLastWord::lengthOfLastWordTwoPointers(const std::string& s) {
    int right = s.length() - 1;
    int left = right;
    
    // Skip trailing spaces with right pointer
    while (right >= 0 && s[right] == ' ') {
        --right;
    }
    
    if (right < 0) return 0; // All spaces
    
    // Find start of last word with left pointer
    left = right;
    while (left >= 0 && s[left] != ' ') {
        --left;
    }
    
    // Length is the difference between pointers
    return right - left;
}

int LengthOfLastWord::lengthOfLastWordRegex(const std::string& s) {
    std::vector<std::string> words = extractWords(s);
    return words.empty() ? 0 : words.back().length();
}

std::vector<std::string> LengthOfLastWord::extractWords(const std::string& s) {
    std::vector<std::string> words;
    std::regex wordRegex(R"([^\s]+)"); // Match any sequence of non-space characters
    std::sregex_iterator iter(s.begin(), s.end(), wordRegex);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        words.push_back(iter->str());
    }
    
    return words;
}

}
}