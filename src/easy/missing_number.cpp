#include "missing_number.h"

namespace leetcode {
namespace easy {

int MissingNumberSort::missingNumber(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (nums[i] != i) return i;
    }
    return n;
}

int MissingNumberHashSet::missingNumber(const std::vector<int>& nums) {
    std::unordered_set<int> seen(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 0; i <= n; ++i) {
        if (seen.find(i) == seen.end()) return i;
    }
    return -1; // unreachable
}

int MissingNumberSum::missingNumber(const std::vector<int>& nums) {
    int n = nums.size();
    long long expected = static_cast<long long>(n) * (n + 1) / 2;
    long long actual = std::accumulate(nums.begin(), nums.end(), 0LL);
    return static_cast<int>(expected - actual);
}

int MissingNumberXor::missingNumber(const std::vector<int>& nums) {
    int n = nums.size();
    int x = n;
    for (int i = 0; i < n; ++i) {
        x ^= i ^ nums[i];
    }
    return x;
}

int MissingNumberBitset::missingNumber(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<bool> seen(n + 1, false);
    for (int v : nums) seen[v] = true;
    for (int i = 0; i <= n; ++i) if (!seen[i]) return i;
    return -1;
}

int MissingNumberCyclicSort::missingNumber(std::vector<int>& nums) {
    int n = nums.size();
    int i = 0;
    while (i < n) {
        if (nums[i] < n && nums[i] != nums[nums[i]]) {
            std::swap(nums[i], nums[nums[i]]);
        } else {
            ++i;
        }
    }
    for (int i2 = 0; i2 < n; ++i2) {
        if (nums[i2] != i2) return i2;
    }
    return n;
}

} // namespace easy
} // namespace leetcode

