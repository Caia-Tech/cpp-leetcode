#include <gtest/gtest.h>
#include "../../src/easy/single_number.h"
#include <vector>
#include <algorithm>
#include <random>

namespace leetcode {
namespace easy {
namespace test {

class SingleNumberTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(std::vector<int> nums, int expected) {
        SingleNumber solution;
        
        // Make copies for approaches that modify the input
        std::vector<int> nums1 = nums;
        std::vector<int> nums2 = nums;
        std::vector<int> nums3 = nums;
        std::vector<int> nums4 = nums;
        std::vector<int> nums5 = nums;
        std::vector<int> nums6 = nums;
        
        EXPECT_EQ(solution.singleNumberXOR(nums1), expected) 
            << "XOR approach failed";
        EXPECT_EQ(solution.singleNumberHashMap(nums2), expected) 
            << "Hash map approach failed";
        EXPECT_EQ(solution.singleNumberHashSet(nums3), expected) 
            << "Hash set approach failed";
        EXPECT_EQ(solution.singleNumberSort(nums4), expected) 
            << "Sorting approach failed";
        EXPECT_EQ(solution.singleNumberMath(nums5), expected) 
            << "Mathematical approach failed";
        EXPECT_EQ(solution.singleNumberBitCount(nums6), expected) 
            << "Bit counting approach failed";
    }
    
    // Helper to create test array with one single number
    std::vector<int> createTestArray(const std::vector<int>& pairs, int single) {
        std::vector<int> result;
        
        // Add all pairs twice
        for (int num : pairs) {
            result.push_back(num);
            result.push_back(num);
        }
        
        // Add the single number once
        result.push_back(single);
        
        // Shuffle for more realistic test
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(result.begin(), result.end(), gen);
        
        return result;
    }
};

// LeetCode Example Test Cases

TEST_F(SingleNumberTest, LeetCodeExample1) {
    // Input: nums = [2,2,1]
    // Output: 1
    testAllApproaches({2, 2, 1}, 1);
}

TEST_F(SingleNumberTest, LeetCodeExample2) {
    // Input: nums = [4,1,2,1,2]
    // Output: 4
    testAllApproaches({4, 1, 2, 1, 2}, 4);
}

TEST_F(SingleNumberTest, LeetCodeExample3) {
    // Input: nums = [1]
    // Output: 1
    testAllApproaches({1}, 1);
}

// Edge Cases

TEST_F(SingleNumberTest, SingleElement) {
    testAllApproaches({42}, 42);
    testAllApproaches({-1}, -1);
    testAllApproaches({0}, 0);
}

TEST_F(SingleNumberTest, ThreeElements) {
    testAllApproaches({1, 2, 1}, 2);
    testAllApproaches({3, 3, 5}, 5);
    testAllApproaches({7, 9, 7}, 9);
}

TEST_F(SingleNumberTest, SingleAtBeginning) {
    testAllApproaches({5, 1, 2, 3, 1, 2, 3}, 5);
}

TEST_F(SingleNumberTest, SingleInMiddle) {
    testAllApproaches({1, 2, 3, 5, 3, 2, 1}, 5);
}

TEST_F(SingleNumberTest, SingleAtEnd) {
    testAllApproaches({1, 2, 3, 1, 2, 3, 5}, 5);
}

// Special Values

TEST_F(SingleNumberTest, WithZero) {
    testAllApproaches({0, 1, 1}, 0);
    testAllApproaches({1, 0, 2, 1, 2}, 0);
    testAllApproaches({-1, 0, -1, 2, 2}, 0);
}

TEST_F(SingleNumberTest, AllNegative) {
    testAllApproaches({-1, -2, -3, -2, -1}, -3);
    testAllApproaches({-5, -10, -5}, -10);
}

TEST_F(SingleNumberTest, MixedPositiveNegative) {
    testAllApproaches({-1, 2, -3, 2, -1}, -3);
    testAllApproaches({1, -1, 2, -2, 3, -1, 1, -2, 2}, 3);
}

// Boundary Values

TEST_F(SingleNumberTest, MinimumConstraintValue) {
    testAllApproaches({-30000, 1, -30000}, 1);
    testAllApproaches({-30000, -30000, -29999}, -29999);
}

TEST_F(SingleNumberTest, MaximumConstraintValue) {
    testAllApproaches({30000, 1, 30000}, 1);
    testAllApproaches({30000, 30000, 29999}, 29999);
}

TEST_F(SingleNumberTest, ExtremeBoundaries) {
    testAllApproaches({-30000, 30000, -30000}, 30000);
    testAllApproaches({30000, -30000, 30000}, -30000);
}

// Large Arrays

TEST_F(SingleNumberTest, LargeArraySingleInMiddle) {
    std::vector<int> pairs;
    for (int i = 1; i <= 100; ++i) {
        if (i != 50) pairs.push_back(i);
    }
    auto nums = createTestArray(pairs, 50);
    testAllApproaches(nums, 50);
}

TEST_F(SingleNumberTest, LargeArrayNegativeSingle) {
    std::vector<int> pairs;
    for (int i = -50; i <= 50; ++i) {
        if (i != -25) pairs.push_back(i);
    }
    auto nums = createTestArray(pairs, -25);
    testAllApproaches(nums, -25);
}

// Pattern Tests

TEST_F(SingleNumberTest, ConsecutiveNumbers) {
    testAllApproaches({1, 2, 3, 4, 5, 1, 2, 4, 5}, 3);
}

TEST_F(SingleNumberTest, PowersOfTwo) {
    testAllApproaches({1, 2, 4, 8, 16, 1, 2, 8, 16}, 4);
}

TEST_F(SingleNumberTest, AlternatingPattern) {
    testAllApproaches({1, -1, 1, -1, 2, -2, -2, 3, 2}, 3);
}

TEST_F(SingleNumberTest, LargeNumbers) {
    testAllApproaches({10000, 20000, 10000}, 20000);
    testAllApproaches({-10000, -20000, -10000}, -20000);
}

// Specific Bit Pattern Tests

TEST_F(SingleNumberTest, SingleBitDifference) {
    // Numbers differing by single bits
    testAllApproaches({0b1010, 0b1011, 0b1010}, 0b1011);
    testAllApproaches({0b1111, 0b1110, 0b1111}, 0b1110);
}

TEST_F(SingleNumberTest, AllOnes) {
    testAllApproaches({-1, 0, -1}, 0);  // -1 is all ones in two's complement
}

TEST_F(SingleNumberTest, ComplementaryPairs) {
    // Pairs that are bitwise complements
    testAllApproaches({5, ~5, 5}, ~5);
    testAllApproaches({100, ~100, 100}, ~100);
}

// Random Order Tests

TEST_F(SingleNumberTest, RandomOrder1) {
    testAllApproaches({3, 1, 4, 1, 3}, 4);
}

TEST_F(SingleNumberTest, RandomOrder2) {
    testAllApproaches({7, 3, 5, 4, 5, 3, 4}, 7);
}

TEST_F(SingleNumberTest, RandomOrder3) {
    testAllApproaches({9, 1, 9, 1, 7, 7, 8}, 8);
}

// Maximum Size Tests

TEST_F(SingleNumberTest, NearMaximumSize) {
    // Create array with ~10000 elements
    std::vector<int> pairs;
    for (int i = 0; i < 5000; ++i) {
        pairs.push_back(i);
    }
    auto nums = createTestArray(pairs, 10000);
    
    SingleNumber solution;
    // Test only fastest approaches for large input
    EXPECT_EQ(solution.singleNumberXOR(nums), 10000);
}

TEST_F(SingleNumberTest, AllSameExceptOne) {
    // Many duplicates of same number
    std::vector<int> nums;
    for (int i = 0; i < 100; ++i) {
        nums.push_back(5);
        nums.push_back(5);
    }
    nums.push_back(7);  // The single number
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(nums.begin(), nums.end(), gen);
    
    testAllApproaches(nums, 7);
}

// Special Mathematical Properties

TEST_F(SingleNumberTest, PrimeNumbers) {
    testAllApproaches({2, 3, 5, 7, 3, 5, 2}, 7);
}

TEST_F(SingleNumberTest, FibonacciNumbers) {
    testAllApproaches({1, 1, 2, 3, 5, 2, 5}, 3);
}

TEST_F(SingleNumberTest, SquareNumbers) {
    testAllApproaches({1, 4, 9, 16, 25, 1, 4, 16, 25}, 9);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode