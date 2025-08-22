#include "unique_paths.h"
#include <queue>
#include <algorithm>

namespace leetcode {
namespace medium {

int UniquePaths::uniquePathsDP2D(int m, int n) {
    // Create DP table
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
    
    // Fill the DP table
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    
    return dp[m-1][n-1];
}

int UniquePaths::uniquePathsDP1D(int m, int n) {
    // Use 1D array to save space
    std::vector<int> dp(n, 1);
    
    // Fill row by row
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j] + dp[j-1]; // dp[j] from above + dp[j-1] from left
        }
    }
    
    return dp[n-1];
}

int UniquePaths::uniquePathsMemo(int m, int n) {
    std::unordered_map<int, int> memo;
    return memoHelper(0, 0, m, n, memo);
}

int UniquePaths::uniquePathsMath(int m, int n) {
    // Need to choose (m-1) down moves out of (m+n-2) total moves
    // This is C(m+n-2, m-1) = C(m+n-2, n-1)
    
    int totalMoves = m + n - 2;
    int downMoves = m - 1;
    
    // Use smaller number for efficiency: C(n,k) = C(n,n-k)
    if (downMoves > totalMoves - downMoves) {
        downMoves = totalMoves - downMoves;
    }
    
    long long result = 1;
    
    // Calculate C(totalMoves, downMoves) = totalMoves! / (downMoves! * (totalMoves-downMoves)!)
    // Use iterative approach to avoid overflow: result = result * (totalMoves-i) / (i+1)
    for (int i = 0; i < downMoves; ++i) {
        result = result * (totalMoves - i) / (i + 1);
    }
    
    return static_cast<int>(result);
}

int UniquePaths::uniquePathsRecursive(int m, int n) {
    return recursiveHelper(0, 0, m, n);
}

int UniquePaths::uniquePathsBFS(int m, int n) {
    // Use BFS to count paths
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<int>> pathCount(m, std::vector<int>(n, 0));
    
    // Start from top-left
    queue.push({0, 0});
    pathCount[0][0] = 1;
    
    // BFS level by level
    while (!queue.empty()) {
        auto [i, j] = queue.front();
        queue.pop();
        
        // Move right
        if (j + 1 < n) {
            if (pathCount[i][j + 1] == 0) {
                queue.push({i, j + 1});
            }
            pathCount[i][j + 1] += pathCount[i][j];
        }
        
        // Move down
        if (i + 1 < m) {
            if (pathCount[i + 1][j] == 0) {
                queue.push({i + 1, j});
            }
            pathCount[i + 1][j] += pathCount[i][j];
        }
    }
    
    return pathCount[m-1][n-1];
}

// Helper function implementations
int UniquePaths::memoHelper(int i, int j, int m, int n, std::unordered_map<int, int>& memo) {
    // Base cases
    if (i == m - 1 && j == n - 1) {
        return 1; // Reached destination
    }
    if (i >= m || j >= n) {
        return 0; // Out of bounds
    }
    
    // Check memoization
    int key = getKey(i, j, n);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
    
    // Recursive case: sum of paths from right and down
    int paths = memoHelper(i + 1, j, m, n, memo) + memoHelper(i, j + 1, m, n, memo);
    
    memo[key] = paths;
    return paths;
}

int UniquePaths::recursiveHelper(int i, int j, int m, int n) {
    // Base cases
    if (i == m - 1 && j == n - 1) {
        return 1; // Reached destination
    }
    if (i >= m || j >= n) {
        return 0; // Out of bounds
    }
    
    // Recursive case: sum of paths from right and down
    return recursiveHelper(i + 1, j, m, n) + recursiveHelper(i, j + 1, m, n);
}

int UniquePaths::getKey(int i, int j, int n) {
    // Create unique key for memoization
    return i * n + j;
}

long long UniquePaths::binomialCoefficient(int n, int k) {
    if (k > n - k) k = n - k; // Take advantage of symmetry
    
    long long result = 1;
    for (int i = 0; i < k; ++i) {
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

long long UniquePaths::gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

}
}