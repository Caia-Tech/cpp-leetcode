#include "valid_perfect_square.h"

namespace leetcode {
namespace easy {

bool ValidPerfectSquareBruteForce::isPerfectSquare(int num) {
    long long i = 1;
    while (i * i <= num) {
        if (i * i == num) return true;
        ++i;
    }
    return false;
}

bool ValidPerfectSquareBinarySearch::isPerfectSquare(int num) {
    int left = 1, right = num;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long sq = mid * mid;
        if (sq == num) return true;
        if (sq < num) left = mid + 1; else right = mid - 1;
    }
    return false;
}

bool ValidPerfectSquareNewton::isPerfectSquare(int num) {
    if (num < 2) return true;
    long long x = num;
    while (x * x > num) {
        x = (x + num / x) / 2;
    }
    return x * x == num;
}

bool ValidPerfectSquareSumOdd::isPerfectSquare(int num) {
    int odd = 1;
    while (num > 0) {
        num -= odd;
        odd += 2;
    }
    return num == 0;
}

bool ValidPerfectSquareBit::isPerfectSquare(int num) {
    long long root = 0;
    long long bit = 1LL << 30; // highest power of four <= int range
    while (bit > 0) {
        long long candidate = root + bit;
        if (candidate * candidate <= num) {
            root = candidate;
        }
        bit >>= 1;
    }
    return root * root == num;
}

bool ValidPerfectSquareSqrt::isPerfectSquare(int num) {
    int r = static_cast<int>(std::sqrt(num));
    return r * r == num;
}

} // namespace easy
} // namespace leetcode

