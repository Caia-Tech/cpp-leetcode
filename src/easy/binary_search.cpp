#include "binary_search.h"

namespace leetcode {
namespace easy {

int BinarySearchIterative::search(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) left = mid + 1; else right = mid - 1;
    }
    return -1;
}

int BinarySearchRecursive::search(const std::vector<int>& nums, int target) {
    return helper(nums, 0, static_cast<int>(nums.size()) - 1, target);
}

int BinarySearchRecursive::helper(const std::vector<int>& nums, int left, int right, int target) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target) return helper(nums, mid + 1, right, target);
    return helper(nums, left, mid - 1, target);
}

int BinarySearchLowerBound::search(const std::vector<int>& nums, int target) {
    auto it = std::lower_bound(nums.begin(), nums.end(), target);
    if (it != nums.end() && *it == target) return static_cast<int>(it - nums.begin());
    return -1;
}

int BinarySearchStdBinarySearch::search(const std::vector<int>& nums, int target) {
    if (!std::binary_search(nums.begin(), nums.end(), target)) return -1;
    return static_cast<int>(std::lower_bound(nums.begin(), nums.end(), target) - nums.begin());
}

int BinarySearchHalfOpen::search(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size());
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1; else right = mid;
    }
    if (left < static_cast<int>(nums.size()) && nums[left] == target) return left;
    return -1;
}

int BinarySearchBitwiseMid::search(const std::vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) left = mid + 1; else right = mid - 1;
    }
    return -1;
}

} // namespace easy
} // namespace leetcode

