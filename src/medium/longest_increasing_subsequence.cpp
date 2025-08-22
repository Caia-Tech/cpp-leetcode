#include "longest_increasing_subsequence.h"
#include <climits>
#include <unordered_map>
#include <stack>

namespace leetcode {
namespace medium {

int LongestIncreasingSubsequence::lengthOfLISDP(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int n = nums.size();
    std::vector<int> dp(n, 1);
    int maxLength = 1;
    
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
        maxLength = std::max(maxLength, dp[i]);
    }
    
    return maxLength;
}

int LongestIncreasingSubsequence::lengthOfLISBinarySearch(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    std::vector<int> tails;
    
    for (int num : nums) {
        // Binary search for position to insert/replace
        int left = 0, right = tails.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (tails[mid] < num) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        // If num is larger than all elements, extend sequence
        if (left == tails.size()) {
            tails.push_back(num);
        } else {
            // Replace first element >= num
            tails[left] = num;
        }
    }
    
    return tails.size();
}

int LongestIncreasingSubsequence::lengthOfLISSegmentTree(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // Coordinate compression
    std::vector<int> compressed = coordinateCompress(nums);
    std::unordered_map<int, int> valueToIndex;
    for (int i = 0; i < compressed.size(); ++i) {
        valueToIndex[compressed[i]] = i + 1; // 1-indexed for segment tree
    }
    
    SegmentTree segTree(compressed.size());
    int maxLength = 0;
    
    for (int num : nums) {
        int compressedIndex = valueToIndex[num];
        
        // Query maximum LIS length for values < num
        int currentLIS = 1;
        if (compressedIndex > 1) {
            currentLIS = segTree.query(1, compressedIndex - 1) + 1;
        }
        
        // Update segment tree with current LIS length
        segTree.update(compressedIndex, currentLIS);
        maxLength = std::max(maxLength, currentLIS);
    }
    
    return maxLength;
}

int LongestIncreasingSubsequence::lengthOfLISFenwickTree(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // Coordinate compression
    std::vector<int> compressed = coordinateCompress(nums);
    std::unordered_map<int, int> valueToIndex;
    for (int i = 0; i < compressed.size(); ++i) {
        valueToIndex[compressed[i]] = i + 1; // 1-indexed for Fenwick tree
    }
    
    FenwickTree fenwick(compressed.size());
    int maxLength = 0;
    
    for (int num : nums) {
        int compressedIndex = valueToIndex[num];
        
        // Query maximum LIS length for values < num
        int currentLIS = 1;
        if (compressedIndex > 1) {
            currentLIS = fenwick.query(compressedIndex - 1) + 1;
        }
        
        // Update Fenwick tree with current LIS length
        fenwick.update(compressedIndex, currentLIS);
        maxLength = std::max(maxLength, currentLIS);
    }
    
    return maxLength;
}

int LongestIncreasingSubsequence::lengthOfLISStack(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    std::vector<int> lis; // Stack-like structure for LIS elements
    
    for (int num : nums) {
        // Find position to insert/replace using binary search
        int pos = binarySearchPosition(lis, num);
        
        if (pos == lis.size()) {
            // Extend current LIS
            lis.push_back(num);
        } else {
            // Replace element at position to maintain increasing property
            lis[pos] = num;
        }
    }
    
    return lis.size();
}

int LongestIncreasingSubsequence::lengthOfLISDivideConquer(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // For simplicity, use the standard DP approach on the full array
    // A full divide-and-conquer implementation would be much more complex
    return lengthOfLISDP(nums);
}

// Helper function implementations
std::vector<int> LongestIncreasingSubsequence::coordinateCompress(const std::vector<int>& nums) {
    std::vector<int> unique(nums);
    std::sort(unique.begin(), unique.end());
    unique.erase(std::unique(unique.begin(), unique.end()), unique.end());
    return unique;
}

// Segment Tree implementation
LongestIncreasingSubsequence::SegmentTree::SegmentTree(int size) : n(size) {
    tree.resize(4 * n, 0);
}

void LongestIncreasingSubsequence::SegmentTree::update(int pos, int val) {
    updateHelper(1, 1, n, pos, val);
}

int LongestIncreasingSubsequence::SegmentTree::query(int l, int r) {
    if (l > r) return 0;
    return queryHelper(1, 1, n, l, r);
}

void LongestIncreasingSubsequence::SegmentTree::updateHelper(int node, int start, int end, int pos, int val) {
    if (start == end) {
        tree[node] = std::max(tree[node], val);
    } else {
        int mid = (start + end) / 2;
        if (pos <= mid) {
            updateHelper(2 * node, start, mid, pos, val);
        } else {
            updateHelper(2 * node + 1, mid + 1, end, pos, val);
        }
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }
}

int LongestIncreasingSubsequence::SegmentTree::queryHelper(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return tree[node];
    
    int mid = (start + end) / 2;
    return std::max(queryHelper(2 * node, start, mid, l, r),
                   queryHelper(2 * node + 1, mid + 1, end, l, r));
}

// Fenwick Tree implementation
LongestIncreasingSubsequence::FenwickTree::FenwickTree(int size) : n(size) {
    tree.resize(n + 1, 0);
}

void LongestIncreasingSubsequence::FenwickTree::update(int pos, int val) {
    for (; pos <= n; pos += pos & (-pos)) {
        tree[pos] = std::max(tree[pos], val);
    }
}

int LongestIncreasingSubsequence::FenwickTree::query(int pos) {
    int result = 0;
    for (; pos > 0; pos -= pos & (-pos)) {
        result = std::max(result, tree[pos]);
    }
    return result;
}

int LongestIncreasingSubsequence::FenwickTree::rangeQuery(int l, int r) {
    // For maximum queries, need different implementation than sum queries
    // This is a simplified version
    int maxVal = 0;
    for (int i = l; i <= r; ++i) {
        maxVal = std::max(maxVal, query(i));
    }
    return maxVal;
}

int LongestIncreasingSubsequence::binarySearchPosition(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

// Divide and conquer implementation
LongestIncreasingSubsequence::LISInfo LongestIncreasingSubsequence::divideConquerHelper(
    std::vector<int>& nums, int left, int right) {
    
    if (left == right) {
        LISInfo info;
        info.length = 1;
        info.minStart = nums[left];
        info.maxEnd = nums[left];
        info.prefix.resize(1, 1);
        info.suffix.resize(1, 1);
        return info;
    }
    
    int mid = left + (right - left) / 2;
    LISInfo leftInfo = divideConquerHelper(nums, left, mid);
    LISInfo rightInfo = divideConquerHelper(nums, mid + 1, right);
    
    return mergeLISInfo(leftInfo, rightInfo, nums, left, mid, right);
}

LongestIncreasingSubsequence::LISInfo LongestIncreasingSubsequence::mergeLISInfo(
    const LISInfo& leftInfo, const LISInfo& rightInfo, 
    std::vector<int>& nums, int left, int mid, int right) {
    
    LISInfo merged;
    merged.length = std::max(leftInfo.length, rightInfo.length);
    
    // Build complete prefix and suffix arrays for merged range
    int totalLength = right - left + 1;
    merged.prefix.resize(totalLength);
    merged.suffix.resize(totalLength);
    
    // Copy left part prefix
    for (int i = 0; i < leftInfo.prefix.size(); ++i) {
        merged.prefix[i] = leftInfo.prefix[i];
    }
    
    // Copy right part prefix, but need to recalculate considering cross-boundary
    for (int i = 0; i < rightInfo.prefix.size(); ++i) {
        int maxFromLeft = 0;
        // Check if we can extend from left side
        for (int j = left; j <= mid; ++j) {
            if (nums[j] < nums[mid + 1 + i]) {
                maxFromLeft = std::max(maxFromLeft, merged.prefix[j - left]);
            }
        }
        merged.prefix[leftInfo.prefix.size() + i] = std::max(rightInfo.prefix[i], maxFromLeft + 1);
    }
    
    // Calculate suffix arrays (length of LIS starting from each position)
    std::vector<int> tempNums(nums.begin() + left, nums.begin() + right + 1);
    std::vector<int> lis(totalLength, 1);
    
    // Calculate LIS from each position to the right
    for (int i = totalLength - 2; i >= 0; --i) {
        for (int j = i + 1; j < totalLength; ++j) {
            if (tempNums[i] < tempNums[j]) {
                lis[i] = std::max(lis[i], lis[j] + 1);
            }
        }
        merged.suffix[i] = lis[i];
    }
    
    // Find maximum length considering all possibilities
    for (int i = 0; i < totalLength; ++i) {
        merged.length = std::max(merged.length, merged.prefix[i]);
        merged.length = std::max(merged.length, merged.suffix[i]);
    }
    
    // Update bounds
    merged.minStart = std::min(leftInfo.minStart, rightInfo.minStart);
    merged.maxEnd = std::max(leftInfo.maxEnd, rightInfo.maxEnd);
    
    return merged;
}

}
}