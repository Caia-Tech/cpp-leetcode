#include "power_of_three.h"

namespace leetcode {
namespace easy {

bool PowerOfThreeIterative::isPowerOfThree(int n) {
    if (n <= 0) return false;
    while (n % 3 == 0) {
        n /= 3;
    }
    return n == 1;
}

bool PowerOfThreeRecursive::isPowerOfThree(int n) {
    if (n == 1) return true;
    if (n <= 0 || n % 3 != 0) return false;
    return isPowerOfThree(n / 3);
}

bool PowerOfThreeLogarithm::isPowerOfThree(int n) {
    if (n <= 0) return false;
    double x = std::log10(n) / std::log10(3);
    double rounded = std::round(x);
    return std::abs(x - rounded) < 1e-10;
}

bool PowerOfThreeBase3::isPowerOfThree(int n) {
    if (n <= 0) return false;
    std::string digits;
    while (n > 0) {
        digits.push_back('0' + n % 3);
        n /= 3;
    }
    // digits are reversed; a power of three in base 3 is '1' followed by zeros
    if (digits.back() != '1') return false;
    for (size_t i = 0; i + 1 < digits.size(); ++i) {
        if (digits[i] != '0') return false;
    }
    return true;
}

bool PowerOfThreeMaxPower::isPowerOfThree(int n) {
    const int MAX_POWER = 1162261467; // 3^19
    return n > 0 && (MAX_POWER % n == 0);
}

PowerOfThreePrecompute::PowerOfThreePrecompute() {
    long value = 1;
    while (value <= INT32_MAX) {
        powers.insert(static_cast<int>(value));
        value *= 3;
    }
}

bool PowerOfThreePrecompute::isPowerOfThree(int n) {
    return powers.count(n) > 0;
}

} // namespace easy
} // namespace leetcode

