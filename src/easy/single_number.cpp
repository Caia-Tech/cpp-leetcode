#include "single_number.h"
#include <algorithm>
#include <numeric>

namespace leetcode {
namespace easy {

int SingleNumberSort::singleNumber(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size(); i += 2) {
        if (i + 1 == nums.size() || nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return 0; // unreachable
}

int SingleNumberHashMap::singleNumber(std::vector<int>& nums) {
    std::unordered_map<int, int> count;
    for (int n : nums) count[n]++;
    for (auto& [val, c] : count) if (c == 1) return val;
    return 0;
}

int SingleNumberXOR::singleNumber(std::vector<int>& nums) {
    int res = 0;
    for (int n : nums) res ^= n;
    return res;
}

int SingleNumberBitCount::singleNumber(std::vector<int>& nums) {
    int result = 0;
    for (int bit = 0; bit < 32; ++bit) {
        int sum = 0;
        for (int n : nums) {
            if (n >> bit & 1) sum++;
        }
        if (sum % 2) result |= (1 << bit);
    }
    return result;
}

int SingleNumberMath::singleNumber(std::vector<int>& nums) {
    std::unordered_set<int> uniq(nums.begin(), nums.end());
    int sumSet = std::accumulate(uniq.begin(), uniq.end(), 0);
    int sumAll = std::accumulate(nums.begin(), nums.end(), 0);
    return 2 * sumSet - sumAll;
}

int SingleNumberSetToggle::singleNumber(std::vector<int>& nums) {
    std::unordered_set<int> s;
    for (int n : nums) {
        if (s.count(n)) s.erase(n); else s.insert(n);
    }
    return *s.begin();
}

} // namespace easy
} // namespace leetcode

