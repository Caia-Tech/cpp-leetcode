#pragma once
#include <vector>

namespace leetcode {
namespace easy {

/**
 * Problem 204: Count Primes
 * 
 * Given an integer n, return the number of prime numbers that are less than n.
 * 
 * Example 1:
 * Input: n = 10
 * Output: 4
 * Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
 * 
 * Example 2:
 * Input: n = 0
 * Output: 0
 * 
 * Example 3:
 * Input: n = 1
 * Output: 0
 * 
 * Constraints:
 * 0 <= n <= 5 * 10^6
 */
class CountPrimes {
public:
    // Approach 1: Sieve of Eratosthenes (Standard)
    // Time: O(n log log n), Space: O(n)
    // Intuition: Mark multiples of each prime as composite
    static int countPrimesSieve(int n);
    
    // Approach 2: Optimized Sieve of Eratosthenes
    // Time: O(n log log n), Space: O(n)
    // Intuition: Only check odd numbers and start marking from p²
    static int countPrimesOptimizedSieve(int n);
    
    // Approach 3: Segmented Sieve for large n
    // Time: O(n log log n), Space: O(√n)
    // Intuition: Process numbers in segments to reduce memory usage
    static int countPrimesSegmentedSieve(int n);
    
    // Approach 4: Trial Division (Naive)
    // Time: O(n√n), Space: O(1)
    // Intuition: Check each number for primality by trial division
    static int countPrimesTrialDivision(int n);
    
    // Approach 5: Trial Division with Optimizations
    // Time: O(n√n), Space: O(1)
    // Intuition: Only check division by 2 and odd numbers up to √n
    static int countPrimesOptimizedTrial(int n);
    
    // Approach 6: Sieve with bitset for memory optimization
    // Time: O(n log log n), Space: O(n/8)
    // Intuition: Use bitset to reduce memory usage by 8x
    static int countPrimesBitsetSieve(int n);

private:
    // Helper function to check if a number is prime
    static bool isPrime(int num);
    
    // Helper function for optimized prime checking
    static bool isPrimeOptimized(int num);
};

} // namespace easy
} // namespace leetcode