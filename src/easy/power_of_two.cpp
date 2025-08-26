#include "power_of_two.h"
#include <cmath>
#include <unordered_set>

namespace leetcode {
namespace easy {

// Approach 1: Bit manipulation - Check if only one bit is set
// Time: O(1), Space: O(1)
// Intuition: Powers of 2 in binary have exactly one bit set (e.g., 8 = 1000₂).
// The trick is that n & (n-1) removes the lowest set bit.
// For powers of 2, this should result in 0.
bool PowerOfTwo::isPowerOfTwoBitManipulation(int n) {
    // Must be positive and have exactly one bit set
    return n > 0 && (n & (n - 1)) == 0;
}

// Approach 2: Built-in popcount function
// Time: O(1), Space: O(1)
// Intuition: __builtin_popcount counts the number of 1-bits.
// Powers of 2 have exactly one bit set.
bool PowerOfTwo::isPowerOfTwoPopCount(int n) {
    return n > 0 && __builtin_popcount(n) == 1;
}

// Approach 3: Mathematical approach using logarithms
// Time: O(1), Space: O(1)
// Intuition: If n is a power of 2, then log₂(n) should be an integer.
// We can use the change of base formula: log₂(n) = log(n) / log(2).
bool PowerOfTwo::isPowerOfTwoMath(int n) {
    if (n <= 0) return false;
    
    double log_result = log2(n);
    return log_result == floor(log_result);
}

// Approach 4: Iterative division by 2
// Time: O(log n), Space: O(1)
// Intuition: Keep dividing by 2. If we can divide evenly until we reach 1,
// then it's a power of 2. If we get an odd number > 1, it's not.
bool PowerOfTwo::isPowerOfTwoDivision(int n) {
    if (n <= 0) return false;
    
    while (n > 1) {
        if (n % 2 != 0) return false;  // If odd and > 1, not a power of 2
        n /= 2;
    }
    
    return true;  // Successfully reduced to 1
}

// Approach 5: Check against all powers of 2
// Time: O(1), Space: O(1)
// Intuition: For 32-bit integers, there are only 31 possible powers of 2 (2^0 to 2^30).
// We can check if n is one of them. Alternative: use the largest power of 2 trick.
bool PowerOfTwo::isPowerOfTwoLookup(int n) {
    if (n <= 0) return false;
    
    // The largest power of 2 that fits in a 32-bit signed integer is 2^30 = 1073741824
    const int largest_power_of_two = 1 << 30;  // 2^30
    
    // If n is a power of 2, then the largest power of 2 should be divisible by n
    return largest_power_of_two % n == 0;
}

// Approach 6: Recursive approach
// Time: O(log n), Space: O(log n)
// Intuition: Base case: n == 1 (2^0). Recursive case: n is even and n/2 is a power of 2.
bool PowerOfTwo::isPowerOfTwoRecursive(int n) {
    return isPowerOfTwoRecursiveHelper(n);
}

bool PowerOfTwo::isPowerOfTwoRecursiveHelper(int n) {
    // Base cases
    if (n <= 0) return false;
    if (n == 1) return true;  // 2^0 = 1
    
    // If n is odd and not 1, it can't be a power of 2
    if (n % 2 != 0) return false;
    
    // Recursive case: check if n/2 is a power of 2
    return isPowerOfTwoRecursiveHelper(n / 2);
}

} // namespace easy
} // namespace leetcode