#include "majority_element.h"
#include <algorithm>
#include <functional>

namespace leetcode {
namespace easy {

int MajorityElementSort::majorityElement(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];
}

int MajorityElementHashMap::majorityElement(std::vector<int>& nums) {
    std::unordered_map<int, int> counts;
    for (int n : nums) {
        if (++counts[n] > nums.size() / 2) return n;
    }
    return 0; // unreachable
}

int MajorityElementRandomized::majorityElement(std::vector<int>& nums) {
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, nums.size() - 1);
    while (true) {
        int candidate = nums[dist(gen)];
        int cnt = 0;
        for (int n : nums) if (n == candidate) ++cnt;
        if (cnt > nums.size() / 2) return candidate;
    }
}

int MajorityElementDivideConquer::majorityElement(std::vector<int>& nums) {
    std::function<int(int,int)> solve = [&](int l, int r) {
        if (l == r) return nums[l];
        int mid = l + (r - l) / 2;
        int left = solve(l, mid);
        int right = solve(mid + 1, r);
        if (left == right) return left;
        int leftCount = 0, rightCount = 0;
        for (int i = l; i <= r; ++i) {
            if (nums[i] == left) ++leftCount;
            else if (nums[i] == right) ++rightCount;
        }
        return leftCount > rightCount ? left : right;
    };
    return solve(0, nums.size() - 1);
}

int MajorityElementBit::majorityElement(std::vector<int>& nums) {
    int result = 0;
    int n = nums.size();
    for (int bit = 0; bit < 32; ++bit) {
        int ones = 0;
        for (int num : nums) {
            if (num >> bit & 1) ++ones;
        }
        if (ones > n / 2) result |= (1 << bit);
    }
    return result;
}

int MajorityElementBoyerMoore::majorityElement(std::vector<int>& nums) {
    int count = 0, candidate = 0;
    for (int n : nums) {
        if (count == 0) candidate = n;
        count += (n == candidate) ? 1 : -1;
    }
    return candidate;
}

} // namespace easy
} // namespace leetcode

