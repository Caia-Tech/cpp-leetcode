#include "plus_one.h"

namespace leetcode {
namespace easy {

std::vector<int> PlusOne::plusOneCarry(std::vector<int>& digits) {
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    
    // If we reach here, all digits were 9
    std::vector<int> result(digits.size() + 1, 0);
    result[0] = 1;
    return result;
}

std::vector<int> PlusOne::plusOneString(std::vector<int>& digits) {
    std::string numStr = vectorToString(digits);
    std::string resultStr = addOneToString(numStr);
    return stringToVector(resultStr);
}

std::string PlusOne::vectorToString(const std::vector<int>& digits) {
    std::string result;
    for (int digit : digits) {
        result += std::to_string(digit);
    }
    return result;
}

std::vector<int> PlusOne::stringToVector(const std::string& str) {
    std::vector<int> result;
    for (char c : str) {
        result.push_back(c - '0');
    }
    return result;
}

std::string PlusOne::addOneToString(const std::string& num) {
    std::string result = num;
    int carry = 1;
    
    for (int i = result.length() - 1; i >= 0 && carry; --i) {
        int digit = (result[i] - '0') + carry;
        result[i] = '0' + (digit % 10);
        carry = digit / 10;
    }
    
    if (carry) {
        result = "1" + result;
    }
    
    return result;
}

std::vector<int> PlusOne::plusOneRecursive(std::vector<int>& digits) {
    if (addOneRecursive(digits, digits.size() - 1)) {
        // Overflow occurred
        std::vector<int> result(digits.size() + 1, 0);
        result[0] = 1;
        return result;
    }
    
    return digits;
}

bool PlusOne::addOneRecursive(std::vector<int>& digits, int index) {
    if (index < 0) {
        return true; // Carry propagated beyond first digit
    }
    
    if (digits[index] < 9) {
        digits[index]++;
        return false; // No carry needed
    }
    
    digits[index] = 0;
    return addOneRecursive(digits, index - 1); // Propagate carry
}

std::vector<int> PlusOne::plusOneSpecialCase(std::vector<int>& digits) {
    // Check if all digits are 9
    if (isAllNines(digits)) {
        std::vector<int> result(digits.size() + 1, 0);
        result[0] = 1;
        return result;
    }
    
    // Standard carry propagation
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    
    // This should never be reached due to the all-9s check
    return digits;
}

bool PlusOne::isAllNines(const std::vector<int>& digits) {
    for (int digit : digits) {
        if (digit != 9) {
            return false;
        }
    }
    return true;
}

std::vector<int> PlusOne::plusOneTwoPass(std::vector<int>& digits) {
    // First pass: determine if overflow will occur
    bool overflow = isAllNines(digits);
    
    // Second pass: perform addition with known result size
    if (overflow) {
        std::vector<int> result(digits.size() + 1, 0);
        result[0] = 1;
        return result;
    } else {
        // Find the rightmost non-9 digit and increment it
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] < 9) {
                digits[i]++;
                break;
            }
            digits[i] = 0;
        }
        return digits;
    }
}

std::vector<int> PlusOne::plusOneInPlace(std::vector<int>& digits) {
    // Try to modify in-place first
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    
    // Overflow case: need new array
    digits.insert(digits.begin(), 1);
    return digits;
}

}
}