#include "squares_of_a_sorted_array.h"

namespace leetcode {
namespace easy {

std::vector<int> SortedSquares::squareAndSort(std::vector<int> nums) {
    for (int &n : nums) n *= n;
    std::sort(nums.begin(), nums.end());
    return nums;
}

std::vector<int> SortedSquares::twoPointers(std::vector<int> nums) {
    const int n = nums.size();
    std::vector<int> res(n);
    int l = 0, r = n - 1, pos = n - 1;
    while (l <= r) {
        if (std::abs(nums[l]) > std::abs(nums[r])) {
            res[pos--] = nums[l] * nums[l];
            ++l;
        } else {
            res[pos--] = nums[r] * nums[r];
            --r;
        }
    }
    return res;
}

std::vector<int> SortedSquares::splitAndMerge(std::vector<int> nums) {
    const int n = nums.size();
    int pos = std::lower_bound(nums.begin(), nums.end(), 0) - nums.begin();
    int neg = pos - 1;
    std::vector<int> res;
    res.reserve(n);
    while (neg >= 0 && pos < n) {
        int left = nums[neg] * nums[neg];
        int right = nums[pos] * nums[pos];
        if (left < right) {
            res.push_back(left);
            --neg;
        } else {
            res.push_back(right);
            ++pos;
        }
    }
    while (neg >= 0) {
        res.push_back(nums[neg] * nums[neg]);
        --neg;
    }
    while (pos < n) {
        res.push_back(nums[pos] * nums[pos]);
        ++pos;
    }
    return res;
}

std::vector<int> SortedSquares::heapApproach(const std::vector<int>& nums) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int n : nums) pq.push(n * n);
    std::vector<int> res;
    res.reserve(nums.size());
    while (!pq.empty()) {
        res.push_back(pq.top());
        pq.pop();
    }
    return res;
}

std::vector<int> SortedSquares::dequeApproach(const std::vector<int>& nums) {
    std::deque<int> dq(nums.begin(), nums.end());
    std::vector<int> res(nums.size());
    int pos = nums.size() - 1;
    while (!dq.empty()) {
        if (std::abs(dq.front()) > std::abs(dq.back())) {
            int v = dq.front();
            dq.pop_front();
            res[pos--] = v * v;
        } else {
            int v = dq.back();
            dq.pop_back();
            res[pos--] = v * v;
        }
    }
    return res;
}

std::vector<int> SortedSquares::countingMap(const std::vector<int>& nums) {
    std::map<int, int> freq;
    for (int n : nums) ++freq[n * n];
    std::vector<int> res;
    res.reserve(nums.size());
    for (const auto& [sq, count] : freq) {
        for (int i = 0; i < count; ++i) res.push_back(sq);
    }
    return res;
}

} // namespace easy
} // namespace leetcode

