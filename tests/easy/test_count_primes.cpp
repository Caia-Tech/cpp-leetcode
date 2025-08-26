#include <gtest/gtest.h>
#include "../../src/easy/count_primes.h"
#include <vector>
#include <cmath>

using namespace leetcode::easy;

// Test fixture for Count Primes
class CountPrimesTest : public ::testing::Test {
protected:
    void testAllApproaches(int n, int expected) {
        EXPECT_EQ(CountPrimes::countPrimesSieve(n), expected) 
            << "Sieve approach failed for n=" << n;
        EXPECT_EQ(CountPrimes::countPrimesOptimizedSieve(n), expected) 
            << "Optimized sieve approach failed for n=" << n;
        EXPECT_EQ(CountPrimes::countPrimesSegmentedSieve(n), expected) 
            << "Segmented sieve approach failed for n=" << n;
        
        // Skip trial division for large n to avoid timeout
        if (n <= 1000) {
            EXPECT_EQ(CountPrimes::countPrimesTrialDivision(n), expected) 
                << "Trial division approach failed for n=" << n;
            EXPECT_EQ(CountPrimes::countPrimesOptimizedTrial(n), expected) 
                << "Optimized trial approach failed for n=" << n;
        }
        
        EXPECT_EQ(CountPrimes::countPrimesBitsetSieve(n), expected) 
            << "Bitset sieve approach failed for n=" << n;
    }
};

// Test Case 1: LeetCode examples
TEST_F(CountPrimesTest, LeetCodeExamples) {
    testAllApproaches(10, 4);  // Primes: 2, 3, 5, 7
    testAllApproaches(0, 0);   // No primes less than 0
    testAllApproaches(1, 0);   // No primes less than 1
}

// Test Case 2: Small numbers
TEST_F(CountPrimesTest, SmallNumbers) {
    testAllApproaches(2, 0);   // No primes less than 2
    testAllApproaches(3, 1);   // Prime: 2
    testAllApproaches(4, 2);   // Primes: 2, 3
    testAllApproaches(5, 2);   // Primes: 2, 3
    testAllApproaches(6, 3);   // Primes: 2, 3, 5
    testAllApproaches(7, 3);   // Primes: 2, 3, 5
    testAllApproaches(8, 4);   // Primes: 2, 3, 5, 7
    testAllApproaches(9, 4);   // Primes: 2, 3, 5, 7
}

// Test Case 3: Numbers up to 100
TEST_F(CountPrimesTest, UpTo100) {
    testAllApproaches(11, 4);  // Primes: 2, 3, 5, 7
    testAllApproaches(12, 5);  // Primes: 2, 3, 5, 7, 11
    testAllApproaches(13, 5);  // Primes: 2, 3, 5, 7, 11
    testAllApproaches(14, 6);  // Primes: 2, 3, 5, 7, 11, 13
    testAllApproaches(15, 6);  // Primes: 2, 3, 5, 7, 11, 13
    testAllApproaches(20, 8);  // Primes: 2, 3, 5, 7, 11, 13, 17, 19
    testAllApproaches(30, 10); // Primes: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29
    testAllApproaches(50, 15); // 15 primes less than 50
    testAllApproaches(100, 25); // 25 primes less than 100
}

// Test Case 4: Powers of 10
TEST_F(CountPrimesTest, PowersOfTen) {
    testAllApproaches(10, 4);     // 4 primes < 10
    testAllApproaches(100, 25);   // 25 primes < 100
    testAllApproaches(1000, 168); // 168 primes < 1000
}

// Test Case 5: Prime numbers themselves
TEST_F(CountPrimesTest, PrimeNumbers) {
    testAllApproaches(2, 0);   // 0 primes less than 2
    testAllApproaches(3, 1);   // 1 prime less than 3 (which is 2)
    testAllApproaches(5, 2);   // 2 primes less than 5 (which are 2, 3)
    testAllApproaches(7, 3);   // 3 primes less than 7 (which are 2, 3, 5)
    testAllApproaches(11, 4);  // 4 primes less than 11
    testAllApproaches(13, 5);  // 5 primes less than 13
    testAllApproaches(17, 6);  // 6 primes less than 17
    testAllApproaches(19, 7);  // 7 primes less than 19
    testAllApproaches(23, 8);  // 8 primes less than 23
    testAllApproaches(29, 9);  // 9 primes less than 29
    testAllApproaches(31, 10); // 10 primes less than 31
}

// Test Case 6: Composite numbers
TEST_F(CountPrimesTest, CompositeNumbers) {
    testAllApproaches(4, 2);   // 2 primes less than 4
    testAllApproaches(6, 3);   // 3 primes less than 6
    testAllApproaches(8, 4);   // 4 primes less than 8
    testAllApproaches(9, 4);   // 4 primes less than 9
    testAllApproaches(10, 4);  // 4 primes less than 10
    testAllApproaches(12, 5);  // 5 primes less than 12
    testAllApproaches(14, 6);  // 6 primes less than 14
    testAllApproaches(15, 6);  // 6 primes less than 15
    testAllApproaches(16, 6);  // 6 primes less than 16
}

// Test Case 7: Sequential ranges for pattern verification
TEST_F(CountPrimesTest, SequentialRanges) {
    // Test range 1-20
    std::vector<int> expected = {0, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 8};
    for (int i = 1; i <= 20; ++i) {
        testAllApproaches(i, expected[i]);
    }
}

// Test Case 8: Larger numbers (skip trial division for performance)
TEST_F(CountPrimesTest, LargerNumbers) {
    // Only test efficient approaches for larger numbers
    EXPECT_EQ(CountPrimes::countPrimesSieve(1000), 168);
    EXPECT_EQ(CountPrimes::countPrimesOptimizedSieve(1000), 168);
    EXPECT_EQ(CountPrimes::countPrimesSegmentedSieve(1000), 168);
    EXPECT_EQ(CountPrimes::countPrimesBitsetSieve(1000), 168);
    
    EXPECT_EQ(CountPrimes::countPrimesSieve(5000), 669);
    EXPECT_EQ(CountPrimes::countPrimesOptimizedSieve(5000), 669);
    EXPECT_EQ(CountPrimes::countPrimesSegmentedSieve(5000), 669);
    EXPECT_EQ(CountPrimes::countPrimesBitsetSieve(5000), 669);
    
    EXPECT_EQ(CountPrimes::countPrimesSieve(10000), 1229);
    EXPECT_EQ(CountPrimes::countPrimesOptimizedSieve(10000), 1229);
    EXPECT_EQ(CountPrimes::countPrimesSegmentedSieve(10000), 1229);
    EXPECT_EQ(CountPrimes::countPrimesBitsetSieve(10000), 1229);
}

// Test Case 9: Edge cases around perfect squares
TEST_F(CountPrimesTest, PerfectSquares) {
    testAllApproaches(4, 2);    // 2² = 4
    testAllApproaches(9, 4);    // 3² = 9
    testAllApproaches(25, 9);   // 5² = 25
    testAllApproaches(49, 15);  // 7² = 49, primes: 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47 = 15
    testAllApproaches(121, 30); // 11² = 121, there are 30 primes less than 121
}

// Test Case 10: Numbers around small primes
TEST_F(CountPrimesTest, AroundSmallPrimes) {
    // Around 2
    testAllApproaches(1, 0);
    testAllApproaches(2, 0);
    testAllApproaches(3, 1);
    
    // Around 3
    testAllApproaches(3, 1);
    testAllApproaches(4, 2);
    
    // Around 5
    testAllApproaches(4, 2);
    testAllApproaches(5, 2);
    testAllApproaches(6, 3);
    
    // Around 7
    testAllApproaches(6, 3);
    testAllApproaches(7, 3);
    testAllApproaches(8, 4);
}

// Test Case 11: Verify prime counting function properties
TEST_F(CountPrimesTest, PrimeCountingProperties) {
    // π(n) should be non-decreasing
    for (int i = 2; i <= 50; ++i) {
        int current = CountPrimes::countPrimesSieve(i);
        int next = CountPrimes::countPrimesSieve(i + 1);
        EXPECT_LE(current, next) << "Prime count should be non-decreasing";
    }
}

// Test Case 12: Twin primes and prime gaps
TEST_F(CountPrimesTest, TwinPrimesAndGaps) {
    // Test around twin primes (3,5), (5,7), (11,13), (17,19), (29,31)
    testAllApproaches(6, 3);   // Contains twin primes 3,5
    testAllApproaches(8, 4);   // Contains twin primes 5,7
    testAllApproaches(14, 6);  // Contains twin primes 11,13
    testAllApproaches(20, 8);  // Contains twin primes 17,19
    testAllApproaches(32, 11); // Contains twin primes 29,31
}

// Test Case 13: Performance comparison ranges
TEST_F(CountPrimesTest, PerformanceRanges) {
    // Test ranges where different algorithms show different performance characteristics
    std::vector<int> testSizes = {100, 200, 500, 1000, 2000};
    
    for (int n : testSizes) {
        int sieveResult = CountPrimes::countPrimesSieve(n);
        int optimizedSieveResult = CountPrimes::countPrimesOptimizedSieve(n);
        int segmentedResult = CountPrimes::countPrimesSegmentedSieve(n);
        int bitsetResult = CountPrimes::countPrimesBitsetSieve(n);
        
        EXPECT_EQ(sieveResult, optimizedSieveResult) << "Inconsistency at n=" << n;
        EXPECT_EQ(sieveResult, segmentedResult) << "Inconsistency at n=" << n;
        EXPECT_EQ(sieveResult, bitsetResult) << "Inconsistency at n=" << n;
    }
}

// Test Case 14: Mersenne prime related numbers
TEST_F(CountPrimesTest, MersennePrimeRelated) {
    // Test numbers related to Mersenne primes (2^p - 1 where p is prime)
    testAllApproaches(3, 1);   // 2^2 - 1 = 3 (Mersenne prime)
    testAllApproaches(7, 3);   // 2^3 - 1 = 7 (Mersenne prime)  
    testAllApproaches(31, 10); // 2^5 - 1 = 31 (Mersenne prime)
    testAllApproaches(127, 30); // 2^7 - 1 = 127 (Mersenne prime)
}

// Test Case 15: Fibonacci numbers
TEST_F(CountPrimesTest, FibonacciNumbers) {
    // Test prime counting at Fibonacci numbers
    testAllApproaches(1, 0);   // F(1) = 1
    testAllApproaches(2, 0);   // F(2) = 1, F(3) = 2
    testAllApproaches(3, 1);   // F(4) = 3
    testAllApproaches(5, 2);   // F(5) = 5
    testAllApproaches(8, 4);   // F(6) = 8
    testAllApproaches(13, 5);  // F(7) = 13
    testAllApproaches(21, 8);  // F(8) = 21
    testAllApproaches(34, 11); // F(9) = 34
    testAllApproaches(55, 16); // F(10) = 55, primes less than 55: 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53 = 16
    testAllApproaches(89, 23); // F(11) = 89
}

// Test Case 16: Highly composite numbers
TEST_F(CountPrimesTest, HighlyCompositeNumbers) {
    // Test at highly composite numbers (numbers with many divisors)
    testAllApproaches(12, 5);  // 12 has divisors: 1,2,3,4,6,12
    testAllApproaches(24, 9);  // 24 has many divisors
    testAllApproaches(36, 11); // 36 has many divisors
    testAllApproaches(48, 15); // 48 has many divisors, primes less than 48: 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47 = 15
    testAllApproaches(60, 17); // 60 has many divisors
}

// Test Case 17: Carmichael numbers and pseudoprimes
TEST_F(CountPrimesTest, CarmichaelNumbers) {
    // Test around smallest Carmichael number (561)
    EXPECT_EQ(CountPrimes::countPrimesSieve(561), 102);
    EXPECT_EQ(CountPrimes::countPrimesSieve(562), 102); // 561 is composite
}

// Test Case 18: Large primes boundary testing
TEST_F(CountPrimesTest, LargePrimeBoundaries) {
    // Test around some larger primes for boundary conditions
    EXPECT_EQ(CountPrimes::countPrimesSieve(97), 24);   // 97 is prime, 24 primes less than 97
    EXPECT_EQ(CountPrimes::countPrimesSieve(98), 25);   // 98 is composite, includes 97 so 25 primes
    EXPECT_EQ(CountPrimes::countPrimesSieve(101), 25);  // 101 is prime, still 25 primes less than 101
    EXPECT_EQ(CountPrimes::countPrimesSieve(102), 26);  // 102 is composite, includes 101 so 26 primes
}

// Test Case 19: Stress test with approach consistency
TEST_F(CountPrimesTest, StressTestConsistency) {
    // Test consistency across all approaches for a range of values
    for (int n = 2; n <= 200; n += 13) { // Test every 13th number
        int sieveResult = CountPrimes::countPrimesSieve(n);
        int optimizedResult = CountPrimes::countPrimesOptimizedSieve(n);
        int segmentedResult = CountPrimes::countPrimesSegmentedSieve(n);
        int bitsetResult = CountPrimes::countPrimesBitsetSieve(n);
        
        EXPECT_EQ(sieveResult, optimizedResult) << "Inconsistency at n=" << n;
        EXPECT_EQ(sieveResult, segmentedResult) << "Inconsistency at n=" << n;
        EXPECT_EQ(sieveResult, bitsetResult) << "Inconsistency at n=" << n;
        
        // Also test trial division for smaller values
        if (n <= 500) {
            int trialResult = CountPrimes::countPrimesTrialDivision(n);
            int optimizedTrialResult = CountPrimes::countPrimesOptimizedTrial(n);
            EXPECT_EQ(sieveResult, trialResult) << "Trial division inconsistency at n=" << n;
            EXPECT_EQ(sieveResult, optimizedTrialResult) << "Optimized trial inconsistency at n=" << n;
        }
    }
}

// Test Case 20: Mathematical verification
TEST_F(CountPrimesTest, MathematicalVerification) {
    // Test against known values of π(n) for mathematical verification
    struct KnownValue {
        int n;
        int prime_count;
    };
    
    std::vector<KnownValue> known_values = {
        {10, 4}, {20, 8}, {30, 10}, {40, 12}, {50, 15},
        {100, 25}, {200, 46}, {300, 62}, {400, 78}, {500, 95},
        {1000, 168}, {1500, 239}, {2000, 303}, {2500, 367}, {3000, 430}
    };
    
    for (const auto& kv : known_values) {
        EXPECT_EQ(CountPrimes::countPrimesSieve(kv.n), kv.prime_count) 
            << "Mathematical verification failed for n=" << kv.n;
    }
}