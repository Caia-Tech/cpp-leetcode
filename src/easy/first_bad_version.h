#pragma once

#include <functional>
#include <vector>
#include <random>

namespace leetcode {
namespace easy {

/**
 * Problem 278: First Bad Version
 * 
 * You are a product manager and currently leading a team to develop a new product. 
 * Unfortunately, the latest version of your product fails the quality check. Since each 
 * version is developed based on the previous version, all the versions after a bad 
 * version are also bad.
 * 
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, 
 * which causes all the following ones to be bad.
 * 
 * You are given an API bool isBadVersion(version) which returns whether version is bad. 
 * Implement a function to find the first bad version. You should minimize the number of 
 * calls to the API.
 * 
 * Constraints:
 * - 1 <= bad <= n <= 2^31 - 1
 */

// Forward declaration for API function
bool isBadVersion(int version);

class FirstBadVersion {
public:
    // Constructor to set up mock API for testing
    FirstBadVersion(int firstBad = 1) : firstBadVersion(firstBad), apiCalls(0) {}
    
    // Reset API call counter for testing
    void resetApiCalls() { apiCalls = 0; }
    int getApiCalls() const { return apiCalls; }
    
    /**
     * Approach 1: Binary Search (Optimal)
     * 
     * Use binary search to find the first bad version.
     * 
     * Reasoning: This is the optimal solution. Since all versions after first
     * bad version are also bad, we have a sorted sequence: [good...good|bad...bad].
     * We want to find the first 'bad'. Use binary search: if mid is bad, search
     * left half (including mid); if mid is good, search right half (excluding mid).
     * This minimizes API calls to O(log n).
     * 
     * Time Complexity: O(log n) - binary search
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: Always - this is the optimal approach
     * Worst when: Never - this is the standard solution
     */
    int firstBadVersionBinarySearch(int n);

    /**
     * Approach 2: Linear Search
     * 
     * Check versions sequentially until finding first bad one.
     * 
     * Reasoning: Most straightforward approach - check each version from 1 to n
     * until finding the first bad one. While simple to understand, this makes
     * too many API calls in worst case (when first bad version is near the end).
     * Included for comparison and educational purposes to show why binary
     * search is much better.
     * 
     * Time Complexity: O(n) - may check all versions
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: Educational comparison, very small n
     * Worst when: Large n (too many API calls)
     */
    int firstBadVersionLinear(int n);

    /**
     * Approach 3: Exponential Search then Binary Search
     * 
     * Find range using exponential search, then binary search.
     * 
     * Reasoning: If first bad version is much smaller than n, we can find it
     * faster by first finding a range [2^k, 2^(k+1)] where first bad version
     * lies, then binary search in that range. Start with version 1, then 2, 4,
     * 8... until finding first bad, then binary search in the range. This is
     * particularly efficient when first bad version is near beginning.
     * 
     * Time Complexity: O(log k) where k is first bad version
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: First bad version is much smaller than n
     * Worst when: First bad version is near n (no advantage over binary search)
     */
    int firstBadVersionExponential(int n);

    /**
     * Approach 4: Ternary Search
     * 
     * Divide search space into three parts instead of two.
     * 
     * Reasoning: Instead of binary search's divide-by-2, divide search space
     * into three equal parts. Check two middle points, then eliminate one-third
     * of search space based on results. While this reduces search space by
     * more each iteration, it requires more API calls per iteration. 
     * Mathematically, binary search is still more efficient overall.
     * 
     * Time Complexity: O(log₃ n) iterations but more API calls per iteration
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: Educational purposes, understanding search variations
     * Worst when: Minimizing API calls (binary search is better)
     */
    int firstBadVersionTernary(int n);

    /**
     * Approach 5: Randomized Binary Search
     * 
     * Use randomized pivot selection in binary search.
     * 
     * Reasoning: Instead of always choosing middle point, randomly select
     * pivot within current range. On average, this behaves similar to binary
     * search but adds randomization. While interesting theoretically, it
     * doesn't improve worst-case performance and may be less predictable.
     * Demonstrates randomized algorithm concepts.
     * 
     * Time Complexity: O(log n) expected, O(n) worst case (very unlikely)
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: Learning randomized algorithms, avoiding worst-case inputs
     * Worst when: Predictable performance needed, minimizing API calls
     */
    int firstBadVersionRandomized(int n);

    /**
     * Approach 6: Golden Section Search
     * 
     * Use golden ratio to divide search space.
     * 
     * Reasoning: Instead of dividing by 2, use golden ratio (~1.618) to divide
     * search space. This is optimal for unimodal functions and demonstrates
     * mathematical optimization concepts. While interesting, it's not better
     * than binary search for this discrete problem and requires more complex
     * calculations. Included for mathematical completeness.
     * 
     * Time Complexity: O(log φ n) where φ is golden ratio
     * Space Complexity: O(1) - only using variables
     * 
     * Best when: Mathematical interest, continuous optimization backgrounds
     * Worst when: Simple discrete search needed
     */
    int firstBadVersionGoldenSection(int n);

private:
    int firstBadVersion;  // For testing purposes
    mutable int apiCalls; // Track API calls for analysis
    mutable std::mt19937 rng{std::random_device{}()}; // For randomized approach
    
    // Mock API function for testing
    bool mockIsBadVersion(int version) const;
    
    // Helper for exponential search
    int binarySearchInRange(int left, int right);
    
    // Golden ratio constant
    static constexpr double PHI = 1.618033988749;
};

}  // namespace easy
}  // namespace leetcode