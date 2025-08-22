#include "palindrome_number.h"
#include <string>
#include <algorithm>
#include <cmath>

namespace leetcode {
namespace easy {

bool PalindromeNumber::isPalindromeFullReverse(int x) {
    if (x < 0) return false;
    if (x == 0) return true;
    
    long long original = x;
    long long reversed = 0;
    
    while (x > 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    
    return original == reversed;
}

bool PalindromeNumber::isPalindromeHalfReverse(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }
    
    int reversedHalf = 0;
    while (x > reversedHalf) {
        reversedHalf = reversedHalf * 10 + x % 10;
        x /= 10;
    }
    
    return x == reversedHalf || x == reversedHalf / 10;
}

bool PalindromeNumber::isPalindromeString(int x) {
    if (x < 0) return false;
    
    std::string str = std::to_string(x);
    std::string reversed = str;
    std::reverse(reversed.begin(), reversed.end());
    
    return str == reversed;
}

bool PalindromeNumber::isPalindromeArray(int x) {
    if (x < 0) return false;
    if (x == 0) return true;
    
    std::vector<int> digits;
    int temp = x;
    
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    
    int left = 0;
    int right = digits.size() - 1;
    
    while (left < right) {
        if (digits[left] != digits[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

bool PalindromeNumber::isPalindromeRecursive(int x) {
    if (x < 0) return false;
    if (x == 0) return true;
    
    int numDigits = getNumberOfDigits(x);
    int divisor = static_cast<int>(std::pow(10, numDigits - 1));
    int original = x;
    
    return checkPalindromeRecursive(x, original, divisor);
}

bool PalindromeNumber::checkPalindromeRecursive(int x, int& original, int& divisor) {
    if (x == 0) return true;
    
    int first = original / divisor;
    int last = x % 10;
    
    if (first != last) return false;
    
    original = (original % divisor) / 10;
    divisor /= 100;
    
    return checkPalindromeRecursive(x / 10, original, divisor);
}

int PalindromeNumber::getNumberOfDigits(int x) {
    if (x == 0) return 1;
    int count = 0;
    while (x > 0) {
        count++;
        x /= 10;
    }
    return count;
}

bool PalindromeNumber::isPalindromeDivision(int x) {
    if (x < 0) return false;
    if (x == 0) return true;
    if (x % 10 == 0) return false;
    
    int divisor = 1;
    int temp = x;
    
    while (temp >= 10) {
        divisor *= 10;
        temp /= 10;
    }
    
    while (x > 0) {
        int first = x / divisor;
        int last = x % 10;
        
        if (first != last) return false;
        
        x = (x % divisor) / 10;
        
        divisor /= 100;
    }
    
    return true;
}

}
}