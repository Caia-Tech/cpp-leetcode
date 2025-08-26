#include "count_primes.h"
#include <cmath>
#include <bitset>

namespace leetcode {
namespace easy {

// Helper function to check if a number is prime (naive)
bool CountPrimes::isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Helper function for optimized prime checking
bool CountPrimes::isPrimeOptimized(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

// Approach 1: Sieve of Eratosthenes (Standard)
// Time: O(n log log n), Space: O(n)
// Intuition: Create a boolean array and mark all multiples of primes as composite.
// Count the remaining unmarked numbers.
int CountPrimes::countPrimesSieve(int n) {
    if (n <= 2) return 0;
    
    std::vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i < n; ++i) {
        if (isPrime[i]) {
            // Mark all multiples of i as composite
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i < n; ++i) {
        if (isPrime[i]) count++;
    }
    
    return count;
}

// Approach 2: Optimized Sieve of Eratosthenes
// Time: O(n log log n), Space: O(n)
// Intuition: Only process odd numbers (except 2) and start marking from i²
int CountPrimes::countPrimesOptimizedSieve(int n) {
    if (n <= 2) return 0;
    
    std::vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false;
    
    // Handle even numbers (only 2 is prime)
    for (int i = 4; i < n; i += 2) {
        isPrime[i] = false;
    }
    
    // Process odd numbers starting from 3
    for (int i = 3; i * i < n; i += 2) {
        if (isPrime[i]) {
            // Start from i² and increment by 2*i (only mark odd multiples)
            for (int j = i * i; j < n; j += 2 * i) {
                isPrime[j] = false;
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i < n; ++i) {
        if (isPrime[i]) count++;
    }
    
    return count;
}

// Approach 3: Segmented Sieve for large n
// Time: O(n log log n), Space: O(√n)
// Intuition: First find all primes up to √n, then use them to sieve segments
int CountPrimes::countPrimesSegmentedSieve(int n) {
    if (n <= 2) return 0;
    
    int limit = static_cast<int>(sqrt(n)) + 1;
    
    // Step 1: Find all primes up to √n using simple sieve
    std::vector<bool> isPrime(limit, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i < limit; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j < limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    // Collect primes up to √n
    std::vector<int> primes;
    for (int i = 2; i < limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    int count = primes.size();
    
    // Step 2: Use segmented sieve for numbers from √n to n
    int segmentSize = std::max(static_cast<int>(sqrt(n)), 32768);
    
    for (int low = limit; low < n; low += segmentSize) {
        int high = std::min(low + segmentSize - 1, n - 1);
        
        std::vector<bool> segment(high - low + 1, true);
        
        for (int prime : primes) {
            // Find the minimum number in [low, high] that is multiple of prime
            int start = std::max(prime * prime, (low + prime - 1) / prime * prime);
            
            for (int j = start; j <= high; j += prime) {
                segment[j - low] = false;
            }
        }
        
        for (int i = 0; i < segment.size(); ++i) {
            if (segment[i]) count++;
        }
    }
    
    return count;
}

// Approach 4: Trial Division (Naive)
// Time: O(n√n), Space: O(1)
// Intuition: For each number from 2 to n-1, check if it's prime by trial division
int CountPrimes::countPrimesTrialDivision(int n) {
    if (n <= 2) return 0;
    
    int count = 0;
    for (int i = 2; i < n; ++i) {
        if (isPrime(i)) {
            count++;
        }
    }
    
    return count;
}

// Approach 5: Trial Division with Optimizations
// Time: O(n√n), Space: O(1)
// Intuition: Only check 2, then odd numbers. For each candidate, only check
// odd divisors up to √candidate
int CountPrimes::countPrimesOptimizedTrial(int n) {
    if (n <= 2) return 0;
    
    int count = 0;
    
    // Check 2 separately
    if (n > 2) count = 1;
    
    // Check odd numbers starting from 3
    for (int i = 3; i < n; i += 2) {
        if (isPrimeOptimized(i)) {
            count++;
        }
    }
    
    return count;
}

// Approach 6: Sieve with bitset for memory optimization
// Time: O(n log log n), Space: O(n/8)
// Intuition: Use std::bitset to reduce memory usage significantly
int CountPrimes::countPrimesBitsetSieve(int n) {
    if (n <= 2) return 0;
    
    // Use bitset for memory efficiency (8 times less memory than vector<bool>)
    std::bitset<5000001> isPrime; // Max constraint is 5 * 10^6
    isPrime.set(); // Set all bits to 1
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i < n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i < n; ++i) {
        if (isPrime[i]) count++;
    }
    
    return count;
}

} // namespace easy
} // namespace leetcode