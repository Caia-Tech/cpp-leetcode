#include "happy_number.h"

namespace leetcode {
namespace easy {

// Helper function to calculate sum of squares of digits
int HappyNumber::getSumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

// Approach 1: Set-based cycle detection
// Time: O(log n), Space: O(log n)
// Intuition: Keep track of seen numbers. If we see a number again, we're in a cycle.
// If we reach 1, the number is happy.
bool HappyNumber::isHappySet(int n) {
    std::unordered_set<int> seen;
    
    while (n != 1 && seen.find(n) == seen.end()) {
        seen.insert(n);
        n = getSumOfSquares(n);
    }
    
    return n == 1;
}

// Approach 2: Floyd's cycle detection (two pointers)
// Time: O(log n), Space: O(1)
// Intuition: Use Floyd's cycle detection algorithm. One pointer moves one step at a time,
// the other moves two steps. If there's a cycle, they'll meet.
bool HappyNumber::isHappyFloyd(int n) {
    auto getNext = [](int num) -> int {
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            sum += digit * digit;
            num /= 10;
        }
        return sum;
    };
    
    int slow = n;
    int fast = getNext(n);
    
    // Floyd's cycle detection
    while (fast != 1 && slow != fast) {
        slow = getNext(slow);           // Move one step
        fast = getNext(getNext(fast));  // Move two steps
    }
    
    return fast == 1;
}

// Approach 3: Mathematical hardcoded cycle detection
// Time: O(log n), Space: O(1)
// Intuition: All unhappy numbers eventually cycle into the cycle: 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4
// We can hardcode this cycle for detection.
bool HappyNumber::isHappyMathematical(int n) {
    std::unordered_set<int> unhappyCycle = {4, 16, 37, 58, 89, 145, 42, 20};
    
    while (n != 1 && unhappyCycle.find(n) == unhappyCycle.end()) {
        n = getSumOfSquares(n);
    }
    
    return n == 1;
}

// Approach 4: Recursive with memoization
// Time: O(log n), Space: O(log n)
// Intuition: Use recursion with memoization to avoid recalculating same numbers
bool HappyNumber::isHappyMemoized(int n) {
    std::unordered_set<int> memo;
    return isHappyMemoizedHelper(n, memo);
}

bool HappyNumber::isHappyMemoizedHelper(int n, std::unordered_set<int>& memo) {
    if (n == 1) return true;
    if (memo.find(n) != memo.end()) return false;
    
    memo.insert(n);
    return isHappyMemoizedHelper(getSumOfSquares(n), memo);
}

// Approach 5: Iterative with limit
// Time: O(log n), Space: O(1)
// Intuition: Happy numbers reach 1 very quickly (within ~20 iterations for most cases).
// Set a reasonable limit to avoid infinite loops.
bool HappyNumber::isHappyLimited(int n) {
    const int MAX_ITERATIONS = 1000; // More than enough for any happy number
    
    for (int i = 0; i < MAX_ITERATIONS && n != 1; ++i) {
        n = getSumOfSquares(n);
    }
    
    return n == 1;
}

// Approach 6: Brent's cycle detection algorithm
// Time: O(log n), Space: O(1)
// Intuition: Brent's algorithm is an alternative to Floyd's with better average performance.
// It uses a "teleporting turtle" approach.
bool HappyNumber::isHappyBrent(int n) {
    auto getNext = [](int num) -> int {
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            sum += digit * digit;
            num /= 10;
        }
        return sum;
    };
    
    if (n == 1) return true;
    
    int power = 1;
    int lambda = 1;
    int tortoise = n;
    int hare = getNext(n);
    
    // Find the cycle length
    while (tortoise != hare) {
        if (power == lambda) {
            tortoise = hare;
            power *= 2;
            lambda = 0;
        }
        hare = getNext(hare);
        if (hare == 1) return true;
        lambda++;
    }
    
    // If we found a cycle and it doesn't contain 1, it's not happy
    return false;
}

} // namespace easy
} // namespace leetcode