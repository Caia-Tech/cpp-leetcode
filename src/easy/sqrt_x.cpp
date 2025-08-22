#include "sqrt_x.h"

namespace leetcode {
namespace easy {

int SqrtX::mySqrtBinarySearch(int x) {
    if (x < 2) return x;
    
    long long left = 1;
    long long right = x / 2;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long square = mid * mid;
        
        if (square == x) {
            return static_cast<int>(mid);
        } else if (square < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return static_cast<int>(right);
}

int SqrtX::mySqrtNewton(int x) {
    if (x < 2) return x;
    
    long long current = x;
    
    while (current * current > x) {
        current = (current + x / current) / 2;
    }
    
    return static_cast<int>(current);
}

int SqrtX::mySqrtLinear(int x) {
    if (x < 2) return x;
    
    long long i = 1;
    while (i * i <= x) {
        ++i;
    }
    
    return static_cast<int>(i - 1);
}

int SqrtX::mySqrtBitManipulation(int x) {
    if (x < 2) return x;
    
    int result = 0;
    
    // Start from the highest possible bit (15 for 32-bit integers)
    for (int bit = 15; bit >= 0; --bit) {
        int candidate = result | (1 << bit);
        
        if (canSquare(candidate, x)) {
            result = candidate;
        }
    }
    
    return result;
}

bool SqrtX::canSquare(long long mid, int x) {
    return mid * mid <= x;
}

int SqrtX::mySqrtExponential(int x) {
    if (x < 2) return x;
    
    // Using the identity: sqrt(x) = e^(ln(x)/2)
    // Note: This violates the constraint of not using built-in functions
    double result = std::exp(0.5 * std::log(x));
    return static_cast<int>(result);
}

int SqrtX::mySqrtDigitByDigit(int x) {
    return digitByDigitHelper(x);
}

int SqrtX::digitByDigitHelper(int x) {
    if (x < 2) return x;
    
    // Find the number of digits in x
    int temp = x;
    int digits = 0;
    while (temp > 0) {
        temp /= 10;
        ++digits;
    }
    
    // Start with the most significant digit pair
    int result = 0;
    int remainder = 0;
    
    // Process pairs of digits from left to right
    for (int i = digits - 1; i >= 0; i -= 2) {
        // Extract current pair (or single digit)
        int currentPair = 0;
        
        if (i > 0) {
            // Extract two digits
            int divisor = 1;
            for (int j = 0; j < i - 1; ++j) {
                divisor *= 10;
            }
            currentPair = (x / divisor) % 100;
        } else {
            // Extract single digit
            currentPair = x % 10;
        }
        
        remainder = remainder * 100 + currentPair;
        
        // Find the largest digit d such that (20*result + d) * d <= remainder
        int d = 0;
        while (d <= 9) {
            int candidate = 20 * result + d;
            if (candidate * d <= remainder) {
                ++d;
            } else {
                break;
            }
        }
        --d;
        
        result = result * 10 + d;
        remainder -= (20 * (result / 10) + d) * d;
        
        // Update x to remove processed digits
        int divisor = 1;
        for (int j = 0; j <= i; ++j) {
            divisor *= 10;
        }
        x %= divisor;
    }
    
    return result;
}

}
}