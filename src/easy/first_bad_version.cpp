#include "first_bad_version.h"
#include <algorithm>
#include <random>
#include <cmath>

namespace leetcode {
namespace easy {

// Mock API function for testing
bool FirstBadVersion::mockIsBadVersion(int version) const {
    apiCalls++;
    return version >= firstBadVersion;
}

// Approach 1: Binary Search (Optimal)
int FirstBadVersion::firstBadVersionBinarySearch(int n) {
    int left = 1, right = n;
    
    while (left < right) {
        // Avoid overflow: left + (right - left) / 2
        int mid = left + (right - left) / 2;
        
        if (mockIsBadVersion(mid)) {
            // mid is bad, so first bad is at mid or to the left
            right = mid;
        } else {
            // mid is good, so first bad is to the right
            left = mid + 1;
        }
    }
    
    return left;
}

// Approach 2: Linear Search
int FirstBadVersion::firstBadVersionLinear(int n) {
    for (int version = 1; version <= n; ++version) {
        if (mockIsBadVersion(version)) {
            return version;
        }
    }
    return n; // Should never reach here given problem constraints
}

// Approach 3: Exponential Search then Binary Search
int FirstBadVersion::firstBadVersionExponential(int n) {
    if (mockIsBadVersion(1)) {
        return 1;
    }
    
    // Find range where first bad version lies
    int bound = 1;
    while (bound <= n && !mockIsBadVersion(bound)) {
        bound *= 2;
    }
    
    // Binary search in the range [bound/2, min(bound, n)]
    return binarySearchInRange(bound / 2, std::min(bound, n));
}

int FirstBadVersion::binarySearchInRange(int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (mockIsBadVersion(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// Approach 4: Ternary Search
int FirstBadVersion::firstBadVersionTernary(int n) {
    int left = 1, right = n;
    
    while (left < right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        bool isMid1Bad = mockIsBadVersion(mid1);
        bool isMid2Bad = mockIsBadVersion(mid2);
        
        if (isMid1Bad) {
            // First bad is at mid1 or to the left
            right = mid1;
        } else if (!isMid2Bad) {
            // Both mid1 and mid2 are good, search right third
            left = mid2 + 1;
        } else {
            // mid1 is good, mid2 is bad, search middle third
            left = mid1 + 1;
            right = mid2;
        }
    }
    
    return left;
}

// Approach 5: Randomized Binary Search
int FirstBadVersion::firstBadVersionRandomized(int n) {
    int left = 1, right = n;
    
    while (left < right) {
        // Randomly choose pivot in range [left, right)
        std::uniform_int_distribution<int> dist(left, right - 1);
        int mid = dist(rng);
        
        if (mockIsBadVersion(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

// Approach 6: Golden Section Search
int FirstBadVersion::firstBadVersionGoldenSection(int n) {
    int left = 1, right = n;
    
    while (right - left > 2) {
        // Use golden ratio to divide the interval
        int range = right - left;
        int mid = left + static_cast<int>(range / PHI);
        
        if (mockIsBadVersion(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    // Handle remaining small range
    for (int i = left; i <= right; ++i) {
        if (mockIsBadVersion(i)) {
            return i;
        }
    }
    
    return right;
}

}  // namespace easy
}  // namespace leetcode