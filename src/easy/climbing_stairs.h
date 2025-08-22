#pragma once

#include <vector>
#include <unordered_map>

namespace leetcode {
namespace easy {

/**
 * Problem 70: Climbing Stairs
 * 
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * 
 * Constraints:
 * - 1 <= n <= 45
 */
class ClimbingStairs {
public:
    /**
     * Approach 1: Recursive (Brute Force)
     * 
     * Try all possible combinations recursively.
     * 
     * Reasoning: This is the most intuitive approach. At each step, we can either
     * take 1 step or 2 steps. So ways(n) = ways(n-1) + ways(n-2). This leads to
     * a simple recursive solution. However, it recalculates the same subproblems
     * many times (exponential overlapping subproblems), making it very inefficient.
     * Good for understanding the problem structure.
     * 
     * Time Complexity: O(2^n) - exponential due to overlapping subproblems
     * Space Complexity: O(n) - recursion call stack depth
     * 
     * Best when: Understanding problem structure, very small n values
     * Worst when: n > 10, any practical use case due to exponential time
     */
    int climbStairsRecursive(int n);

    /**
     * Approach 2: Memoization (Top-Down DP)
     * 
     * Recursive with memoization to avoid recomputation.
     * 
     * Reasoning: This optimizes the recursive approach by storing previously computed
     * results in a hash map. Once we compute ways(k), we store it so future calls
     * to ways(k) return immediately. This eliminates the exponential redundancy
     * while maintaining the intuitive recursive structure. Classic top-down DP.
     * 
     * Time Complexity: O(n) - each subproblem computed once
     * Space Complexity: O(n) - memoization table + call stack
     * 
     * Best when: Recursive thinking is natural, not all subproblems may be needed
     * Worst when: Iterative DP is simpler or call stack depth is a concern
     */
    int climbStairsMemoization(int n);

    /**
     * Approach 3: Dynamic Programming (Bottom-Up)
     * 
     * Build solution from bottom using DP array.
     * 
     * Reasoning: This is the classic iterative DP approach. Build the solution
     * from the base cases upward. dp[i] represents number of ways to reach step i.
     * dp[i] = dp[i-1] + dp[i-2]. This approach is more intuitive for many developers
     * than recursion and has predictable memory access patterns (better cache locality).
     * 
     * Time Complexity: O(n) - single loop through all steps
     * Space Complexity: O(n) - DP array storage
     * 
     * Best when: Learning DP concepts, need all subproblem results
     * Worst when: Memory is constrained and space optimization is possible
     */
    int climbStairsDP(int n);

    /**
     * Approach 4: Fibonacci (Space Optimized)
     * 
     * Realize it's Fibonacci sequence, optimize space.
     * 
     * Reasoning: Key insight: this problem is equivalent to the Fibonacci sequence!
     * ways(n) = ways(n-1) + ways(n-2) with ways(1)=1, ways(2)=2. Since we only
     * need the previous two values to compute the next, we can optimize space from
     * O(n) to O(1) by keeping just two variables. This is the optimal practical solution.
     * 
     * Time Complexity: O(n) - single loop
     * Space Complexity: O(1) - only two variables needed
     * 
     * Best when: Need optimal space usage, recognize Fibonacci pattern
     * Worst when: Need to store all intermediate results for other purposes
     */
    int climbStairsFibonacci(int n);

    /**
     * Approach 5: Matrix Exponentiation
     * 
     * Use matrix multiplication for faster computation.
     * 
     * Reasoning: Since this is Fibonacci sequence, we can represent the recurrence
     * as matrix multiplication: [F(n+1), F(n)] = [F(n), F(n-1)] * [[1,1],[1,0]].
     * Using fast matrix exponentiation (similar to fast exponentiation), we can
     * compute F(n) in O(log n) time. While complex, this is optimal for very large n.
     * 
     * Time Complexity: O(log n) - fast exponentiation of 2x2 matrix
     * Space Complexity: O(1) - constant space for matrix operations
     * 
     * Best when: Very large n values, need theoretical optimality
     * Worst when: Implementation complexity outweighs benefits for typical n values
     */
    int climbStairsMatrix(int n);

    /**
     * Approach 6: Binet's Formula
     * 
     * Direct formula using golden ratio.
     * 
     * Reasoning: Binet's formula provides a direct calculation for Fibonacci numbers:
     * F(n) = (φ^n - ψ^n) / √5, where φ = (1+√5)/2 and ψ = (1-√5)/2. This gives
     * O(1) computation but has floating-point precision issues for large n.
     * Mathematically elegant but practically limited due to precision concerns.
     * 
     * Time Complexity: O(1) - direct formula computation
     * Space Complexity: O(1) - only constant variables
     * 
     * Best when: Educational purposes, small n with precision tolerance
     * Worst when: Large n or exact precision required (floating-point errors)
     */
    int climbStairsBinet(int n);

private:
    std::unordered_map<int, int> memo;
    int climbStairsMemo(int n, std::unordered_map<int, int>& memo);
    std::vector<std::vector<long long>> matrixMultiply(
        const std::vector<std::vector<long long>>& a,
        const std::vector<std::vector<long long>>& b);
    std::vector<std::vector<long long>> matrixPower(
        std::vector<std::vector<long long>>& matrix, int n);
};

}
}