#include <gtest/gtest.h>
#include "../../src/easy/majority_element.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class MajorityElementTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(std::vector<int> nums, int expected) {
        MajorityElement solution;
        
        // Make copies for each approach since some modify the array
        std::vector<int> nums1 = nums;
        std::vector<int> nums2 = nums;
        std::vector<int> nums3 = nums;
        std::vector<int> nums4 = nums;
        std::vector<int> nums5 = nums;
        std::vector<int> nums6 = nums;
        
        EXPECT_EQ(solution.majorityElementBoyerMoore(nums1), expected) 
            << "Boyer-Moore failed for input: " << vectorToString(nums);
        
        EXPECT_EQ(solution.majorityElementHashMap(nums2), expected)
            << "HashMap failed for input: " << vectorToString(nums);
        
        EXPECT_EQ(solution.majorityElementSorting(nums3), expected)
            << "Sorting failed for input: " << vectorToString(nums);
        
        EXPECT_EQ(solution.majorityElementDivideConquer(nums4), expected)
            << "Divide and Conquer failed for input: " << vectorToString(nums);
        
        EXPECT_EQ(solution.majorityElementBitManipulation(nums5), expected)
            << "Bit Manipulation failed for input: " << vectorToString(nums);
        
        EXPECT_EQ(solution.majorityElementFunctional(nums6), expected)
            << "Functional failed for input: " << vectorToString(nums);
    }
    
    // Helper to convert vector to string for error messages
    std::string vectorToString(const std::vector<int>& vec) {
        std::string result = "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) result += ", ";
            result += std::to_string(vec[i]);
        }
        result += "]";
        return result;
    }
};

// LeetCode Example Test Cases

TEST_F(MajorityElementTest, LeetCodeExample1) {
    // Input: nums = [3,2,3]
    // Output: 3
    testAllApproaches({3, 2, 3}, 3);
}

TEST_F(MajorityElementTest, LeetCodeExample2) {
    // Input: nums = [2,2,1,1,1,2,2]
    // Output: 2
    testAllApproaches({2, 2, 1, 1, 1, 2, 2}, 2);
}

// Single Element Tests

TEST_F(MajorityElementTest, SingleElement) {
    // Single element is always the majority
    testAllApproaches({5}, 5);
}

TEST_F(MajorityElementTest, SingleElementNegative) {
    // Single negative element
    testAllApproaches({-7}, -7);
}

TEST_F(MajorityElementTest, SingleElementZero) {
    // Single zero element
    testAllApproaches({0}, 0);
}

// Two Element Tests

TEST_F(MajorityElementTest, TwoIdenticalElements) {
    // Two identical elements
    testAllApproaches({4, 4}, 4);
}

TEST_F(MajorityElementTest, TwoIdenticalNegative) {
    // Two identical negative elements
    testAllApproaches({-3, -3}, -3);
}

// Three Element Tests

TEST_F(MajorityElementTest, ThreeElementsTwoSame) {
    // Three elements with two same
    testAllApproaches({1, 2, 1}, 1);
}

TEST_F(MajorityElementTest, ThreeElementsAllSame) {
    // Three identical elements
    testAllApproaches({7, 7, 7}, 7);
}

// Majority at Different Positions

TEST_F(MajorityElementTest, MajorityAtBeginning) {
    // Majority elements concentrated at beginning
    testAllApproaches({1, 1, 1, 1, 2, 3, 4}, 1);
}

TEST_F(MajorityElementTest, MajorityAtEnd) {
    // Majority elements concentrated at end
    testAllApproaches({1, 2, 3, 4, 4, 4, 4}, 4);
}

TEST_F(MajorityElementTest, MajorityScattered) {
    // Majority elements scattered throughout
    testAllApproaches({5, 1, 5, 2, 5, 3, 5}, 5);
}

TEST_F(MajorityElementTest, MajorityAlternating) {
    // Majority elements alternating
    testAllApproaches({1, 2, 1, 2, 1}, 1);
}

// Edge Cases with Exact Majority

TEST_F(MajorityElementTest, ExactMajorityOddLength) {
    // Odd length with exactly n/2 + 1 elements
    testAllApproaches({1, 2, 1, 3, 1}, 1);
}

TEST_F(MajorityElementTest, ExactMajorityEvenLength) {
    // Even length with exactly n/2 + 1 elements
    testAllApproaches({1, 2, 1, 3, 1, 1}, 1);
}

// Negative Number Tests

TEST_F(MajorityElementTest, AllNegativeNumbers) {
    // All negative numbers
    testAllApproaches({-1, -1, -2, -1, -3}, -1);
}

TEST_F(MajorityElementTest, MixedNegativePositive) {
    // Mix of negative and positive
    testAllApproaches({-5, 3, -5, 3, -5}, -5);
}

TEST_F(MajorityElementTest, NegativeMajority) {
    // Negative number as majority
    testAllApproaches({-10, -10, 5, -10}, -10);
}

// Zero Tests

TEST_F(MajorityElementTest, ZeroAsMajority) {
    // Zero as the majority element
    testAllApproaches({0, 1, 0, 2, 0}, 0);
}

TEST_F(MajorityElementTest, AllZeros) {
    // All zeros
    testAllApproaches({0, 0, 0, 0}, 0);
}

TEST_F(MajorityElementTest, ZeroAndNegative) {
    // Zero and negative numbers
    testAllApproaches({0, -1, 0, -2, 0}, 0);
}

// Large Value Tests

TEST_F(MajorityElementTest, LargePositiveValues) {
    // Large positive values within constraints
    testAllApproaches({1000000000, 999999999, 1000000000}, 1000000000);
}

TEST_F(MajorityElementTest, LargeNegativeValues) {
    // Large negative values within constraints
    testAllApproaches({-1000000000, -999999999, -1000000000}, -1000000000);
}

TEST_F(MajorityElementTest, ExtremeMixedValues) {
    // Mix of extreme values
    testAllApproaches({-1000000000, 1000000000, -1000000000, -1000000000, 1000000000}, -1000000000);
}

// Pattern Tests

TEST_F(MajorityElementTest, ConsecutiveMajority) {
    // All majority elements consecutive
    testAllApproaches({1, 2, 3, 4, 4, 4, 4, 4}, 4);
}

TEST_F(MajorityElementTest, TwoDistinctValues) {
    // Only two distinct values
    testAllApproaches({1, 2, 1, 2, 1, 2, 1}, 1);
}

TEST_F(MajorityElementTest, MultipleDistinctMinorities) {
    // Many distinct minorities, one majority
    testAllApproaches({5, 1, 2, 5, 3, 5, 4, 5, 5}, 5);
}

// Larger Arrays

TEST_F(MajorityElementTest, LargeArrayMajorityAtStart) {
    // Large array with majority at start
    std::vector<int> nums(100, 7);
    for (int i = 60; i < 100; i++) {
        nums[i] = i;
    }
    testAllApproaches(nums, 7);
}

TEST_F(MajorityElementTest, LargeArrayMajorityAtEnd) {
    // Large array with majority at end
    std::vector<int> nums(100);
    for (int i = 0; i < 40; i++) {
        nums[i] = i;
    }
    for (int i = 40; i < 100; i++) {
        nums[i] = 99;
    }
    testAllApproaches(nums, 99);
}

TEST_F(MajorityElementTest, LargeArrayMajorityScattered) {
    // Large array with majority scattered
    std::vector<int> nums;
    for (int i = 0; i < 50; i++) {
        nums.push_back(42);
        if (i < 40) {
            nums.push_back(i);
        }
    }
    testAllApproaches(nums, 42);
}

// Special Pattern Tests

TEST_F(MajorityElementTest, PowerOfTwoLength) {
    // Array length is power of 2 (good for divide & conquer)
    testAllApproaches({1, 2, 1, 3, 1, 4, 1, 1}, 1);
}

TEST_F(MajorityElementTest, PrimeLength) {
    // Array length is prime number
    testAllApproaches({3, 1, 3, 2, 3, 4, 3}, 3);
}

TEST_F(MajorityElementTest, FibonacciPattern) {
    // Fibonacci-like distribution
    testAllApproaches({1, 1, 2, 1, 3, 1, 5, 1, 8, 1, 1}, 1);
}

// Boundary Cases

TEST_F(MajorityElementTest, MinimumConstraintValue) {
    // Minimum constraint value
    testAllApproaches({-1000000000, -1000000000, 0}, -1000000000);
}

TEST_F(MajorityElementTest, MaximumConstraintValue) {
    // Maximum constraint value
    testAllApproaches({1000000000, 1000000000, 0}, 1000000000);
}

TEST_F(MajorityElementTest, ExactlyHalfPlusOne) {
    // Exactly n/2 + 1 occurrences (minimum for majority)
    testAllApproaches({1, 2, 3, 4, 5, 5, 5, 5, 5}, 5);
}

// Complex Distribution Tests

TEST_F(MajorityElementTest, ThreeWayTie) {
    // Three numbers, one has slight majority
    testAllApproaches({1, 2, 3, 1, 2, 3, 1, 1, 1}, 1);
}

TEST_F(MajorityElementTest, AlmostEqual) {
    // Two numbers almost equal count, one is majority
    testAllApproaches({7, 8, 7, 8, 7, 8, 7}, 7);
}

TEST_F(MajorityElementTest, GradualIncrease) {
    // Majority element count gradually increases
    std::vector<int> nums = {1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1};
    testAllApproaches(nums, 1);
}

// Stress Tests

TEST_F(MajorityElementTest, MaximumSizeArray) {
    // Maximum size constraint (subset for test performance)
    std::vector<int> nums(1000, 123);
    for (int i = 0; i < 400; i++) {
        nums[i] = i;
    }
    testAllApproaches(nums, 123);
}

TEST_F(MajorityElementTest, AllSameElement) {
    // All elements are the same
    std::vector<int> nums(100, 42);
    testAllApproaches(nums, 42);
}

TEST_F(MajorityElementTest, BarelyMajority) {
    // Just barely a majority (51 out of 100)
    std::vector<int> nums;
    for (int i = 0; i < 51; i++) {
        nums.push_back(777);
    }
    for (int i = 0; i < 49; i++) {
        nums.push_back(i);
    }
    testAllApproaches(nums, 777);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode