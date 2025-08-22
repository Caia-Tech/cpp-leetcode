#include "reverse_integer.h"
#include <string>
#include <algorithm>
#include <vector>

namespace leetcode {
namespace easy {

int ReverseInteger::reverseMath(int x) {
    int reversed = 0;
    
    while (x != 0) {
        int digit = x % 10;
        x /= 10;
        
        if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && digit > 7)) {
            return 0;
        }
        if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && digit < -8)) {
            return 0;
        }
        
        reversed = reversed * 10 + digit;
    }
    
    return reversed;
}

int ReverseInteger::reverseString(int x) {
    bool negative = x < 0;
    std::string str = std::to_string(x);
    
    if (negative) {
        str = str.substr(1);
    }
    
    std::reverse(str.begin(), str.end());
    
    try {
        long long result = std::stoll(str);
        if (negative) result = -result;
        
        if (result > INT_MAX || result < INT_MIN) {
            return 0;
        }
        
        return static_cast<int>(result);
    } catch (...) {
        return 0;
    }
}

int ReverseInteger::reverseLong(int x) {
    long long reversed = 0;
    
    while (x != 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    
    if (reversed > INT_MAX || reversed < INT_MIN) {
        return 0;
    }
    
    return static_cast<int>(reversed);
}

int ReverseInteger::reverseArray(int x) {
    bool negative = x < 0;
    if (x == INT_MIN) return 0;
    
    x = std::abs(x);
    std::vector<int> digits;
    
    while (x > 0) {
        digits.push_back(x % 10);
        x /= 10;
    }
    
    int reversed = 0;
    for (int digit : digits) {
        if (reversed > INT_MAX / 10) {
            return 0;
        }
        reversed = reversed * 10 + digit;
    }
    
    if (negative) {
        reversed = -reversed;
    }
    
    return reversed;
}

int ReverseInteger::reverseRecursive(int x) {
    if (x == 0) return 0;
    return reverseRecursiveHelper(x, 0);
}

int ReverseInteger::reverseRecursiveHelper(int x, int reversed) {
    if (x == 0) {
        return reversed;
    }
    
    int digit = x % 10;
    
    if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && digit > 7)) {
        return 0;
    }
    if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && digit < -8)) {
        return 0;
    }
    
    return reverseRecursiveHelper(x / 10, reversed * 10 + digit);
}

int ReverseInteger::reversePreemptive(int x) {
    int reversed = 0;
    const int maxDiv10 = INT_MAX / 10;
    const int minDiv10 = INT_MIN / 10;
    
    while (x != 0) {
        int digit = x % 10;
        x /= 10;
        
        if (reversed > maxDiv10) return 0;
        if (reversed < minDiv10) return 0;
        
        if (reversed == maxDiv10) {
            if (digit > 7) return 0;
        }
        if (reversed == minDiv10) {
            if (digit < -8) return 0;
        }
        
        reversed = reversed * 10 + digit;
    }
    
    return reversed;
}

}
}