#include "contains_duplicate.h"

namespace leetcode {
namespace easy {

bool ContainsDuplicateSort::containsDuplicate(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] == nums[i - 1]) return true;
    }
    return false;
}

bool ContainsDuplicateHashSet::containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    for (int n : nums) {
        if (!seen.insert(n).second) return true;
    }
    return false;
}

bool ContainsDuplicateHashMap::containsDuplicate(const std::vector<int>& nums) {
    std::unordered_map<int, int> counts;
    for (int n : nums) {
        if (++counts[n] > 1) return true;
    }
    return false;
}

bool ContainsDuplicateBitVector::containsDuplicate(const std::vector<int>& nums) {
    if (nums.empty()) return false;
    auto [minIt, maxIt] = std::minmax_element(nums.begin(), nums.end());
    long long range = static_cast<long long>(*maxIt) - *minIt;
    if (range > 1e6) { // avoid huge allocations
        std::unordered_set<int> seen;
        for (int n : nums) {
            if (!seen.insert(n).second) return true;
        }
        return false;
    }
    std::vector<bool> seen(range + 1, false);
    int offset = *minIt;
    for (int n : nums) {
        int idx = n - offset;
        if (seen[idx]) return true;
        seen[idx] = true;
    }
    return false;
}

bool ContainsDuplicateBinarySearch::containsDuplicate(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size(); ++i) {
        if (std::binary_search(nums.begin() + i + 1, nums.end(), nums[i]))
            return true;
    }
    return false;
}

bool ContainsDuplicateSetSize::containsDuplicate(const std::vector<int>& nums) {
    std::set<int> s(nums.begin(), nums.end());
    return s.size() != nums.size();
}

} // namespace easy
} // namespace leetcode

