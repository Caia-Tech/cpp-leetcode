#include "roman_to_integer.h"
#include <unordered_map>

namespace leetcode {
namespace easy {

int RomanToInteger::romanToIntHashMap(const std::string& s) {
    std::unordered_map<char, int> roman = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    
    int result = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (i < s.length() - 1 && roman[s[i]] < roman[s[i + 1]]) {
            result -= roman[s[i]];
        } else {
            result += roman[s[i]];
        }
    }
    
    return result;
}

int RomanToInteger::getValueSwitch(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int RomanToInteger::romanToIntSwitch(const std::string& s) {
    int result = 0;
    for (int i = 0; i < s.length(); ++i) {
        int current = getValueSwitch(s[i]);
        int next = (i + 1 < s.length()) ? getValueSwitch(s[i + 1]) : 0;
        
        if (current < next) {
            result -= current;
        } else {
            result += current;
        }
    }
    
    return result;
}

int RomanToInteger::romanToIntRightToLeft(const std::string& s) {
    std::unordered_map<char, int> roman = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    
    int result = 0;
    int prev = 0;
    
    for (int i = s.length() - 1; i >= 0; --i) {
        int current = roman[s[i]];
        if (current < prev) {
            result -= current;
        } else {
            result += current;
        }
        prev = current;
    }
    
    return result;
}

int RomanToInteger::romanToIntReplace(std::string s) {
    std::unordered_map<std::string, int> special = {
        {"IV", 4}, {"IX", 9}, {"XL", 40}, {"XC", 90},
        {"CD", 400}, {"CM", 900}
    };
    
    int result = 0;
    
    for (const auto& [pattern, value] : special) {
        size_t pos = s.find(pattern);
        while (pos != std::string::npos) {
            result += value;
            s[pos] = s[pos + 1] = ' ';
            pos = s.find(pattern);
        }
    }
    
    std::unordered_map<char, int> roman = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    
    for (char c : s) {
        if (c != ' ') {
            result += roman[c];
        }
    }
    
    return result;
}

int RomanToInteger::romanToIntStateMachine(const std::string& s) {
    int result = 0;
    int i = 0;
    
    while (i < s.length()) {
        if (s[i] == 'M') {
            result += 1000;
            i++;
        } else if (s[i] == 'D') {
            result += 500;
            i++;
        } else if (s[i] == 'C') {
            if (i + 1 < s.length()) {
                if (s[i + 1] == 'D') {
                    result += 400;
                    i += 2;
                } else if (s[i + 1] == 'M') {
                    result += 900;
                    i += 2;
                } else {
                    result += 100;
                    i++;
                }
            } else {
                result += 100;
                i++;
            }
        } else if (s[i] == 'L') {
            result += 50;
            i++;
        } else if (s[i] == 'X') {
            if (i + 1 < s.length()) {
                if (s[i + 1] == 'L') {
                    result += 40;
                    i += 2;
                } else if (s[i + 1] == 'C') {
                    result += 90;
                    i += 2;
                } else {
                    result += 10;
                    i++;
                }
            } else {
                result += 10;
                i++;
            }
        } else if (s[i] == 'V') {
            result += 5;
            i++;
        } else if (s[i] == 'I') {
            if (i + 1 < s.length()) {
                if (s[i + 1] == 'V') {
                    result += 4;
                    i += 2;
                } else if (s[i + 1] == 'X') {
                    result += 9;
                    i += 2;
                } else {
                    result += 1;
                    i++;
                }
            } else {
                result += 1;
                i++;
            }
        }
    }
    
    return result;
}

int RomanToInteger::romanToIntArray(const std::string& s) {
    int values[256] = {0};
    values['I'] = 1;
    values['V'] = 5;
    values['X'] = 10;
    values['L'] = 50;
    values['C'] = 100;
    values['D'] = 500;
    values['M'] = 1000;
    
    int result = 0;
    for (int i = 0; i < s.length(); ++i) {
        int current = values[s[i]];
        int next = (i + 1 < s.length()) ? values[s[i + 1]] : 0;
        
        if (current < next) {
            result -= current;
        } else {
            result += current;
        }
    }
    
    return result;
}

}
}