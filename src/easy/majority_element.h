#pragma once

#include <vector>
#include <unordered_map>
#include <random>

namespace leetcode {
namespace easy {

/**
 * Problem 169: Majority Element
 *
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times.
 * You may assume that the majority element always exists in the array.
 */

// Approach 1: Sort and pick middle element
class MajorityElementSort {
public:
    int majorityElement(std::vector<int>& nums);
};

// Approach 2: Hash map counting
class MajorityElementHashMap {
public:
    int majorityElement(std::vector<int>& nums);
};

// Approach 3: Randomized search
class MajorityElementRandomized {
public:
    int majorityElement(std::vector<int>& nums);
};

// Approach 4: Divide and conquer
class MajorityElementDivideConquer {
public:
    int majorityElement(std::vector<int>& nums);
};

// Approach 5: Bit manipulation
class MajorityElementBit {
public:
    int majorityElement(std::vector<int>& nums);
};

// Approach 6: Boyer-Moore Voting
class MajorityElementBoyerMoore {
public:
    int majorityElement(std::vector<int>& nums);
};

} // namespace easy
} // namespace leetcode

