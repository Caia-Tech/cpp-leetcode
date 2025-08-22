#include <gtest/gtest.h>
#include "../../src/medium/product_except_self.h"
#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {
namespace test {

class ProductExceptSelfTest : public ::testing::Test {
protected:
    // Helper function to test all approaches
    void testAllApproaches(std::vector<int> nums, const std::vector<int>& expected) {
        // Make copies since some approaches might modify input
        auto nums1 = nums;
        auto nums2 = nums;
        auto nums3 = nums;
        auto nums4 = nums;
        auto nums5 = nums;
        auto nums6 = nums;
        
        ProductExceptSelfTwoArrays solution1;
        ProductExceptSelfDivision solution2;
        ProductExceptSelfOptimal solution3;
        ProductExceptSelfStack solution4;
        ProductExceptSelfRecursive solution5;
        ProductExceptSelfLogarithmic solution6;
        
        auto result1 = solution1.productExceptSelf(nums1);
        auto result2 = solution2.productExceptSelf(nums2);
        auto result3 = solution3.productExceptSelf(nums3);
        auto result4 = solution4.productExceptSelf(nums4);
        auto result5 = solution5.productExceptSelf(nums5);
        auto result6 = solution6.productExceptSelf(nums6);
        
        EXPECT_EQ(result1, expected) << "Two Arrays approach failed";
        EXPECT_EQ(result2, expected) << "Division approach failed";
        EXPECT_EQ(result3, expected) << "Optimal approach failed";
        EXPECT_EQ(result4, expected) << "Stack approach failed";
        EXPECT_EQ(result5, expected) << "Recursive approach failed";
        
        // Logarithmic approach may have precision issues, so we test with tolerance
        EXPECT_EQ(result6.size(), expected.size()) << "Logarithmic approach size mismatch";
        for (size_t i = 0; i < expected.size(); i++) {
            // For logarithmic approach, allow small tolerance due to floating point precision
            if (expected[i] == 0) {
                EXPECT_EQ(result6[i], 0) << "Logarithmic approach failed at index " << i;
            } else {
                double ratio = static_cast<double>(result6[i]) / expected[i];
                EXPECT_TRUE(ratio > 0.99 && ratio < 1.01) 
                    << "Logarithmic approach failed at index " << i 
                    << " Expected: " << expected[i] << " Got: " << result6[i];
            }
        }
    }
};

// LeetCode examples
TEST_F(ProductExceptSelfTest, LeetCodeExample1) {
    // nums = [1,2,3,4], output = [24,12,8,6]
    std::vector<int> nums = {1, 2, 3, 4};
    std::vector<int> expected = {24, 12, 8, 6};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, LeetCodeExample2) {
    // nums = [-1,1,0,-3,3], output = [0,0,9,0,0]
    std::vector<int> nums = {-1, 1, 0, -3, 3};
    std::vector<int> expected = {0, 0, 9, 0, 0};
    testAllApproaches(nums, expected);
}

// Edge cases
TEST_F(ProductExceptSelfTest, TwoElements) {
    // Minimum constraint case
    std::vector<int> nums = {2, 3};
    std::vector<int> expected = {3, 2};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, TwoElementsWithZero) {
    std::vector<int> nums = {0, 1};
    std::vector<int> expected = {1, 0};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, AllZeros) {
    std::vector<int> nums = {0, 0, 0};
    std::vector<int> expected = {0, 0, 0};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, SingleZero) {
    std::vector<int> nums = {1, 2, 0, 4, 5};
    std::vector<int> expected = {0, 0, 40, 0, 0};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, MultipleZeros) {
    std::vector<int> nums = {1, 0, 3, 0, 5};
    std::vector<int> expected = {0, 0, 0, 0, 0};
    testAllApproaches(nums, expected);
}

// Negative numbers
TEST_F(ProductExceptSelfTest, AllNegative) {
    std::vector<int> nums = {-1, -2, -3};
    std::vector<int> expected = {6, 3, 2};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, MixedSigns) {
    std::vector<int> nums = {-1, 2, -3, 4};
    std::vector<int> expected = {-24, 12, -8, 6};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, SingleNegative) {
    std::vector<int> nums = {1, -2, 3, 4};
    std::vector<int> expected = {-24, 12, -8, -6};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, TwoNegatives) {
    std::vector<int> nums = {-1, 2, -3, 4};
    std::vector<int> expected = {-24, 12, -8, 6};
    testAllApproaches(nums, expected);
}

// Special values
TEST_F(ProductExceptSelfTest, WithOnes) {
    std::vector<int> nums = {1, 1, 1, 1, 1};
    std::vector<int> expected = {1, 1, 1, 1, 1};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, WithMinusOnes) {
    std::vector<int> nums = {-1, -1, -1, -1};
    std::vector<int> expected = {-1, -1, -1, -1};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, LargePositiveNumbers) {
    std::vector<int> nums = {10, 20, 30};
    std::vector<int> expected = {600, 300, 200};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, LargeNegativeNumbers) {
    std::vector<int> nums = {-10, -20, -30};
    std::vector<int> expected = {600, 300, 200};
    testAllApproaches(nums, expected);
}

// Boundary constraint values
TEST_F(ProductExceptSelfTest, MaxConstraintValues) {
    // Using values at constraint boundary: -30 <= nums[i] <= 30
    std::vector<int> nums = {30, -30, 1, -1};
    std::vector<int> expected = {30, -30, 900, -900};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, MinConstraintValues) {
    std::vector<int> nums = {-30, 1};
    std::vector<int> expected = {1, -30};
    testAllApproaches(nums, expected);
}

// Longer arrays
TEST_F(ProductExceptSelfTest, LongerArray) {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<int> expected = {720, 360, 240, 180, 144, 120};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, AlternatingPattern) {
    std::vector<int> nums = {1, -1, 1, -1, 1};
    std::vector<int> expected = {1, -1, 1, -1, 1};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, IncreasingSequence) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> expected = {120, 60, 40, 30, 24};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, DecreasingSequence) {
    std::vector<int> nums = {5, 4, 3, 2, 1};
    std::vector<int> expected = {24, 30, 40, 60, 120};
    testAllApproaches(nums, expected);
}

// Complex patterns
TEST_F(ProductExceptSelfTest, RepeatedValues) {
    std::vector<int> nums = {2, 2, 2, 2};
    std::vector<int> expected = {8, 8, 8, 8};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, RepeatedNegativeValues) {
    std::vector<int> nums = {-2, -2, -2};
    std::vector<int> expected = {4, 4, 4};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, PrimesOnly) {
    std::vector<int> nums = {2, 3, 5, 7};
    std::vector<int> expected = {105, 70, 42, 30};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, PowersOfTwo) {
    std::vector<int> nums = {1, 2, 4, 8};
    std::vector<int> expected = {64, 32, 16, 8};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, MixedSmallLarge) {
    std::vector<int> nums = {1, 30, 1, -30};
    std::vector<int> expected = {-900, -30, -900, 30};
    testAllApproaches(nums, expected);
}

// Zero position variations
TEST_F(ProductExceptSelfTest, ZeroAtBeginning) {
    std::vector<int> nums = {0, 2, 3, 4};
    std::vector<int> expected = {24, 0, 0, 0};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, ZeroAtEnd) {
    std::vector<int> nums = {1, 2, 3, 0};
    std::vector<int> expected = {0, 0, 0, 6};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, ZeroInMiddle) {
    std::vector<int> nums = {1, 2, 0, 4};
    std::vector<int> expected = {0, 0, 8, 0};
    testAllApproaches(nums, expected);
}

// Symmetrical patterns
TEST_F(ProductExceptSelfTest, SymmetricalArray) {
    std::vector<int> nums = {1, 2, 3, 2, 1};
    std::vector<int> expected = {12, 6, 4, 6, 12};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, PalindromeArray) {
    std::vector<int> nums = {2, 3, 4, 3, 2};
    std::vector<int> expected = {72, 48, 36, 48, 72};
    testAllApproaches(nums, expected);
}

// Product overflow edge cases (within constraint guarantees)
TEST_F(ProductExceptSelfTest, LargeProducts) {
    // Test with values that would create large products but within 32-bit limits
    std::vector<int> nums = {10, 10, 10};
    std::vector<int> expected = {100, 100, 100};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, AlternatingZeros) {
    std::vector<int> nums = {1, 0, 2, 0, 3};
    std::vector<int> expected = {0, 0, 0, 0, 0};
    testAllApproaches(nums, expected);
}

// Complex negative patterns
TEST_F(ProductExceptSelfTest, OddNegatives) {
    // Odd number of negatives results in negative products
    std::vector<int> nums = {-1, 2, -3, 4, -5};
    std::vector<int> expected = {120, -60, 40, -30, 24};
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, EvenNegatives) {
    // Even number of negatives results in positive products
    std::vector<int> nums = {-1, 2, -3, 4};
    std::vector<int> expected = {-24, 12, -8, 6};
    testAllApproaches(nums, expected);
}

// Stress tests
TEST_F(ProductExceptSelfTest, ManyOnes) {
    std::vector<int> nums(20, 1);
    std::vector<int> expected(20, 1);
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, AlternatingOnesMinusOnes) {
    std::vector<int> nums;
    std::vector<int> expected;
    for (int i = 0; i < 10; i++) {
        nums.push_back((i % 2 == 0) ? 1 : -1);
        // If we exclude nums[i]: 
        // - Exclude 1: 4 ones, 5 minus ones -> (-1)^5 = -1
        // - Exclude -1: 5 ones, 4 minus ones -> (-1)^4 = 1
        expected.push_back((i % 2 == 0) ? -1 : 1);
    }
    testAllApproaches(nums, expected);
}

TEST_F(ProductExceptSelfTest, Sequential) {
    // nums = [1, 2, 3, ..., 10]
    std::vector<int> nums;
    for (int i = 1; i <= 10; i++) {
        nums.push_back(i);
    }
    
    // Calculate expected: for each i, product of all except nums[i-1]
    std::vector<int> expected;
    int totalProduct = 1;
    for (int i = 1; i <= 10; i++) {
        totalProduct *= i;
    }
    for (int i = 1; i <= 10; i++) {
        expected.push_back(totalProduct / i);
    }
    
    testAllApproaches(nums, expected);
}

}
}
}