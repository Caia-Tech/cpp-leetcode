#pragma once

#include <vector>
#include <queue>
#include <algorithm>

namespace leetcode {
namespace easy {

/**
 * Problem 283: Move Zeroes
 *
 * Given an integer array nums, move all 0's to the end of it while maintaining
 * the relative order of the non-zero elements. The operation must be done
 * in-place without making a copy of the array.
 */

// Approach 1: Two-pointer swap
class MoveZeroesTwoPointer {
public:
    void moveZeroes(std::vector<int>& nums);
};

// Approach 2: std::stable_partition
class MoveZeroesStablePartition {
public:
    void moveZeroes(std::vector<int>& nums);
};

// Approach 3: Counting zeros then fill
class MoveZeroesCountFill {
public:
    void moveZeroes(std::vector<int>& nums);
};

// Approach 4: Construct new array and copy back
class MoveZeroesCopyBack {
public:
    void moveZeroes(std::vector<int>& nums);
};

// Approach 5: Track zeros with a queue and swap forward
class MoveZeroesQueue {
public:
    void moveZeroes(std::vector<int>& nums);
};

// Approach 6: std::remove and fill
class MoveZeroesRemoveFill {
public:
    void moveZeroes(std::vector<int>& nums);
};

} // namespace easy
} // namespace leetcode

