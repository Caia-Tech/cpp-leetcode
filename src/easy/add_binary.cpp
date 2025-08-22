#include "add_binary.h"

namespace leetcode {
namespace easy {

std::string AddBinary::addBinaryTwoPointers(const std::string& a, const std::string& b) {
    std::string result;
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        
        if (i >= 0) {
            sum += a[i] - '0';
            --i;
        }
        
        if (j >= 0) {
            sum += b[j] - '0';
            --j;
        }
        
        result = char('0' + (sum % 2)) + result;
        carry = sum / 2;
    }
    
    return result;
}

std::string AddBinary::addBinaryPadding(const std::string& a, const std::string& b) {
    int maxLen = std::max(a.length(), b.length());
    std::string paddedA = padWithZeros(a, maxLen);
    std::string paddedB = padWithZeros(b, maxLen);
    
    std::string result;
    int carry = 0;
    
    for (int i = maxLen - 1; i >= 0; --i) {
        int sum = (paddedA[i] - '0') + (paddedB[i] - '0') + carry;
        result = char('0' + (sum % 2)) + result;
        carry = sum / 2;
    }
    
    if (carry) {
        result = "1" + result;
    }
    
    return result;
}

std::string AddBinary::padWithZeros(const std::string& str, int targetLength) {
    if (str.length() >= targetLength) {
        return str;
    }
    return std::string(targetLength - str.length(), '0') + str;
}

std::string AddBinary::addBinaryReverse(const std::string& a, const std::string& b) {
    std::string revA = a;
    std::string revB = b;
    std::reverse(revA.begin(), revA.end());
    std::reverse(revB.begin(), revB.end());
    
    std::string result;
    int carry = 0;
    int maxLen = std::max(revA.length(), revB.length());
    
    for (int i = 0; i < maxLen || carry; ++i) {
        int sum = carry;
        
        if (i < revA.length()) {
            sum += revA[i] - '0';
        }
        
        if (i < revB.length()) {
            sum += revB[i] - '0';
        }
        
        result += char('0' + (sum % 2));
        carry = sum / 2;
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

std::string AddBinary::addBinaryRecursive(const std::string& a, const std::string& b) {
    return addBinaryRecHelper(a, b, a.length() - 1, b.length() - 1, 0);
}

std::string AddBinary::addBinaryRecHelper(const std::string& a, const std::string& b, int i, int j, int carry) {
    if (i < 0 && j < 0 && carry == 0) {
        return "";
    }
    
    int sum = carry;
    if (i >= 0) {
        sum += a[i] - '0';
    }
    if (j >= 0) {
        sum += b[j] - '0';
    }
    
    char currentBit = '0' + (sum % 2);
    int newCarry = sum / 2;
    
    return addBinaryRecHelper(a, b, i - 1, j - 1, newCarry) + currentBit;
}

std::string AddBinary::addBinaryBitwise(const std::string& a, const std::string& b) {
    // Note: This approach is limited by integer size
    // For demonstration purposes only, not suitable for very large numbers
    
    long long numA = binaryStringToInt(a);
    long long numB = binaryStringToInt(b);
    
    // Simulate addition using bitwise operations
    while (numB != 0) {
        long long carry = numA & numB;  // Calculate carry
        numA = numA ^ numB;             // Sum without carry
        numB = carry << 1;              // Shift carry left
    }
    
    return intToBinaryString(numA);
}

long long AddBinary::binaryStringToInt(const std::string& binary) {
    long long result = 0;
    for (char bit : binary) {
        result = (result << 1) + (bit - '0');
    }
    return result;
}

std::string AddBinary::intToBinaryString(long long num) {
    if (num == 0) return "0";
    
    std::string result;
    while (num > 0) {
        result = char('0' + (num % 2)) + result;
        num /= 2;
    }
    return result;
}

std::string AddBinary::addBinaryBitset(const std::string& a, const std::string& b) {
    // Note: This approach is limited by bitset size
    // Using bitset<64> for demonstration, may not work for very large inputs
    
    const int BITSET_SIZE = 64;
    std::bitset<BITSET_SIZE> bitsetA(a);
    std::bitset<BITSET_SIZE> bitsetB(b);
    
    // Simulate addition using bitset operations
    std::bitset<BITSET_SIZE> result;
    std::bitset<BITSET_SIZE> carry;
    
    do {
        result = bitsetA ^ bitsetB;  // XOR for sum without carry
        carry = (bitsetA & bitsetB) << 1;  // AND and shift for carry
        bitsetA = result;
        bitsetB = carry;
    } while (carry.any());
    
    std::string resultStr = result.to_string();
    
    // Remove leading zeros
    size_t firstOne = resultStr.find('1');
    if (firstOne == std::string::npos) {
        return "0";
    }
    
    return resultStr.substr(firstOne);
}

}
}