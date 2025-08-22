#include "integer_to_roman.h"

namespace leetcode {
namespace medium {

// Static member definitions
const std::vector<std::string> IntegerToRoman::thousands = {"", "M", "MM", "MMM"};
const std::vector<std::string> IntegerToRoman::hundreds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
const std::vector<std::string> IntegerToRoman::tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
const std::vector<std::string> IntegerToRoman::ones = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

const std::vector<std::pair<int, std::string>> IntegerToRoman::valueSymbolPairs = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

std::string IntegerToRoman::intToRomanGreedy(int num) {
    std::string result;
    
    for (const auto& pair : valueSymbolPairs) {
        while (num >= pair.first) {
            result += pair.second;
            num -= pair.first;
        }
    }
    
    return result;
}

std::string IntegerToRoman::intToRomanDigitByDigit(int num) {
    std::string result;
    
    // Process thousands
    int thousandsDigit = num / 1000;
    result += std::string(thousandsDigit, 'M');
    num %= 1000;
    
    // Process hundreds
    int hundredsDigit = num / 100;
    if (hundredsDigit == 9) {
        result += "CM";
    } else if (hundredsDigit >= 5) {
        result += "D" + std::string(hundredsDigit - 5, 'C');
    } else if (hundredsDigit == 4) {
        result += "CD";
    } else {
        result += std::string(hundredsDigit, 'C');
    }
    num %= 100;
    
    // Process tens
    int tensDigit = num / 10;
    if (tensDigit == 9) {
        result += "XC";
    } else if (tensDigit >= 5) {
        result += "L" + std::string(tensDigit - 5, 'X');
    } else if (tensDigit == 4) {
        result += "XL";
    } else {
        result += std::string(tensDigit, 'X');
    }
    num %= 10;
    
    // Process ones
    int onesDigit = num;
    if (onesDigit == 9) {
        result += "IX";
    } else if (onesDigit >= 5) {
        result += "V" + std::string(onesDigit - 5, 'I');
    } else if (onesDigit == 4) {
        result += "IV";
    } else {
        result += std::string(onesDigit, 'I');
    }
    
    return result;
}

std::string IntegerToRoman::intToRomanLookupTable(int num) {
    return thousands[num / 1000] +
           hundreds[(num % 1000) / 100] +
           tens[(num % 100) / 10] +
           ones[num % 10];
}

std::string IntegerToRoman::intToRomanRecursive(int num) {
    return intToRomanHelper(num, valueSymbolPairs);
}

std::string IntegerToRoman::intToRomanHelper(int num, const std::vector<std::pair<int, std::string>>& values) {
    if (num == 0) return "";
    
    for (const auto& pair : values) {
        if (num >= pair.first) {
            return pair.second + intToRomanHelper(num - pair.first, values);
        }
    }
    
    return "";
}

std::string IntegerToRoman::intToRomanStringBuilding(int num) {
    std::string result;
    
    for (const auto& pair : valueSymbolPairs) {
        int count = num / pair.first;
        if (count > 0) {
            result += repeatString(pair.second, count);
            num %= pair.first;
        }
    }
    
    return result;
}

std::string IntegerToRoman::repeatString(const std::string& str, int count) {
    std::string result;
    for (int i = 0; i < count; ++i) {
        result += str;
    }
    return result;
}

std::string IntegerToRoman::intToRomanPatternBased(int num) {
    std::string result;
    
    // Thousands place (1000-3000)
    int thousands = num / 1000;
    result += processDigit(thousands, "M", "", "");
    num %= 1000;
    
    // Hundreds place (100-900)
    int hundreds = num / 100;
    result += processDigit(hundreds, "C", "D", "M");
    num %= 100;
    
    // Tens place (10-90)
    int tens = num / 10;
    result += processDigit(tens, "X", "L", "C");
    num %= 10;
    
    // Ones place (1-9)
    result += processDigit(num, "I", "V", "X");
    
    return result;
}

std::string IntegerToRoman::processDigit(int digit, const std::string& one, const std::string& five, const std::string& ten) {
    if (digit == 0) return "";
    if (digit <= 3) return std::string(digit, one[0]);
    if (digit == 4) return one + five;
    if (digit <= 8) return five + std::string(digit - 5, one[0]);
    if (digit == 9) return one + ten;
    return "";
}

}
}