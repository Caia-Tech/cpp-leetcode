#include "climbing_stairs.h"
#include <cmath>

namespace leetcode {
namespace easy {

int ClimbingStairs::climbStairsRecursive(int n) {
    if (n <= 2) return n;
    return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

int ClimbingStairs::climbStairsMemoization(int n) {
    std::unordered_map<int, int> memo;
    return climbStairsMemo(n, memo);
}

int ClimbingStairs::climbStairsMemo(int n, std::unordered_map<int, int>& memo) {
    if (n <= 2) return n;
    
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    
    memo[n] = climbStairsMemo(n - 1, memo) + climbStairsMemo(n - 2, memo);
    return memo[n];
}

int ClimbingStairs::climbStairsDP(int n) {
    if (n <= 2) return n;
    
    std::vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

int ClimbingStairs::climbStairsFibonacci(int n) {
    if (n <= 2) return n;
    
    int first = 1, second = 2;
    
    for (int i = 3; i <= n; ++i) {
        int third = first + second;
        first = second;
        second = third;
    }
    
    return second;
}

int ClimbingStairs::climbStairsMatrix(int n) {
    if (n <= 2) return n;
    
    std::vector<std::vector<long long>> base = {{1, 1}, {1, 0}};
    std::vector<std::vector<long long>> result = matrixPower(base, n);
    
    return result[0][0];
}

std::vector<std::vector<long long>> ClimbingStairs::matrixMultiply(
    const std::vector<std::vector<long long>>& a,
    const std::vector<std::vector<long long>>& b) {
    
    std::vector<std::vector<long long>> result(2, std::vector<long long>(2, 0));
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    return result;
}

std::vector<std::vector<long long>> ClimbingStairs::matrixPower(
    std::vector<std::vector<long long>>& matrix, int n) {
    
    if (n == 1) return matrix;
    
    std::vector<std::vector<long long>> result = {{1, 0}, {0, 1}};
    
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrixMultiply(result, matrix);
        }
        matrix = matrixMultiply(matrix, matrix);
        n /= 2;
    }
    
    return result;
}

int ClimbingStairs::climbStairsBinet(int n) {
    double sqrt5 = std::sqrt(5);
    double phi = (1 + sqrt5) / 2;
    double psi = (1 - sqrt5) / 2;
    
    return static_cast<int>(std::round((std::pow(phi, n + 1) - std::pow(psi, n + 1)) / sqrt5));
}

}
}