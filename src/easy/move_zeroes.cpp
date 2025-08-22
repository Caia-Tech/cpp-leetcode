#include "move_zeroes.h"

namespace leetcode {
namespace easy {

// Approach 1: Two-pointer swap
// Keep track of the position to place the next non-zero element.
// Iterate through the array, swapping non-zero elements forward.
void MoveZeroesTwoPointer::moveZeroes(std::vector<int>& nums) {
    int insertPos = 0;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (nums[i] != 0) {
            std::swap(nums[insertPos++], nums[i]);
        }
    }
}

// Approach 2: std::stable_partition
// Partition the array keeping non-zero elements in front while preserving order.
void MoveZeroesStablePartition::moveZeroes(std::vector<int>& nums) {
    auto it = std::stable_partition(nums.begin(), nums.end(), [](int x) { return x != 0; });
    // Elements after iterator are zeros already, nothing else needed.
}

// Approach 3: Counting zeros then fill
// First pass writes non-zero elements in order, second pass fills remaining with zeros.
void MoveZeroesCountFill::moveZeroes(std::vector<int>& nums) {
    int insertPos = 0;
    for (int num : nums) {
        if (num != 0) nums[insertPos++] = num;
    }
    std::fill(nums.begin() + insertPos, nums.end(), 0);
}

// Approach 4: Construct new array and copy back
// Builds a new vector of non-zero elements then appends zeros, copying back to input.
void MoveZeroesCopyBack::moveZeroes(std::vector<int>& nums) {
    std::vector<int> temp;
    temp.reserve(nums.size());
    for (int num : nums) if (num != 0) temp.push_back(num);
    temp.resize(nums.size(), 0);
    nums = std::move(temp);
}

// Approach 5: Track zeros with a queue and swap forward
// Queue stores indices of zeros; when encountering a non-zero, swap with earliest zero index.
void MoveZeroesQueue::moveZeroes(std::vector<int>& nums) {
    std::queue<int> zeroIdx;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (nums[i] == 0) {
            zeroIdx.push(i);
        } else if (!zeroIdx.empty()) {
            int zeroPos = zeroIdx.front();
            zeroIdx.pop();
            std::swap(nums[zeroPos], nums[i]);
            zeroIdx.push(i); // current position now holds zero
        }
    }
}

// Approach 6: std::remove and fill
// Use remove algorithm to move non-zeros forward, then fill tail with zeros.
void MoveZeroesRemoveFill::moveZeroes(std::vector<int>& nums) {
    auto it = std::remove(nums.begin(), nums.end(), 0);
    std::fill(it, nums.end(), 0);
}

} // namespace easy
} // namespace leetcode

