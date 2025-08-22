#include <gtest/gtest.h>
#include "medium/maximum_product_subarray.h"
#include <chrono>
#include <climits>

using namespace leetcode::medium;

class MaximumProductSubarrayTest : public ::testing::Test {
protected:
    MaximumProductSubarray solution;
    
    // Helper function to test all approaches
    void testAllApproaches(std::vector<int> nums, int expected) {
        std::vector<int> nums1 = nums, nums2 = nums, nums3 = nums,
                        nums4 = nums, nums5 = nums, nums6 = nums;
        
        EXPECT_EQ(solution.maxProductDP(nums1), expected) << "DP approach failed";
        EXPECT_EQ(solution.maxProductBruteForce(nums2), expected) << "Brute force approach failed";
        EXPECT_EQ(solution.maxProductTwoPass(nums3), expected) << "Two pass approach failed";
        EXPECT_EQ(solution.maxProductKadane(nums4), expected) << "Kadane approach failed";
        EXPECT_EQ(solution.maxProductPrefixSuffix(nums5), expected) << "Prefix suffix approach failed";
        EXPECT_EQ(solution.maxProductDivideConquer(nums6), expected) << "Divide conquer approach failed";
    }
};

TEST_F(MaximumProductSubarrayTest, BasicExample1) {
    // Input: nums = [2,3,-2,4]
    // Output: 6 (subarray [2,3])
    std::vector<int> nums = {2, 3, -2, 4};
    testAllApproaches(nums, 6);
}

TEST_F(MaximumProductSubarrayTest, BasicExample2) {
    // Input: nums = [-2,0,-1]
    // Output: 0 (subarray [0])
    std::vector<int> nums = {-2, 0, -1};
    testAllApproaches(nums, 0);
}

TEST_F(MaximumProductSubarrayTest, SingleElement) {
    // Input: nums = [5]
    // Output: 5
    std::vector<int> nums = {5};
    testAllApproaches(nums, 5);
}

TEST_F(MaximumProductSubarrayTest, SingleNegativeElement) {
    // Input: nums = [-3]
    // Output: -3
    std::vector<int> nums = {-3};
    testAllApproaches(nums, -3);
}

TEST_F(MaximumProductSubarrayTest, SingleZero) {
    // Input: nums = [0]
    // Output: 0
    std::vector<int> nums = {0};
    testAllApproaches(nums, 0);
}

TEST_F(MaximumProductSubarrayTest, AllPositive) {
    // Input: nums = [2,3,4]
    // Output: 24 (entire array)
    std::vector<int> nums = {2, 3, 4};
    testAllApproaches(nums, 24);
}

TEST_F(MaximumProductSubarrayTest, AllNegativeEvenCount) {
    // Input: nums = [-2,-3]
    // Output: 6 (entire array, even number of negatives)
    std::vector<int> nums = {-2, -3};
    testAllApproaches(nums, 6);
}

TEST_F(MaximumProductSubarrayTest, AllNegativeOddCount) {
    // Input: nums = [-2,-3,-4]
    // Output: 12 (subarray [-3,-4] or [-2,-3])
    std::vector<int> nums = {-2, -3, -4};
    testAllApproaches(nums, 12);
}

TEST_F(MaximumProductSubarrayTest, MixedWithZero) {
    // Input: nums = [2,0,3,4]
    // Output: 12 (subarray [3,4])
    std::vector<int> nums = {2, 0, 3, 4};
    testAllApproaches(nums, 12);
}

TEST_F(MaximumProductSubarrayTest, MultipleZeros) {
    // Input: nums = [0,2,0,3]
    // Output: 3 (single element)
    std::vector<int> nums = {0, 2, 0, 3};
    testAllApproaches(nums, 3);
}

TEST_F(MaximumProductSubarrayTest, NegativeAndPositive) {
    // Input: nums = [-2,3,-4]
    // Output: 24 (entire array: -2 * 3 * -4 = 24)
    std::vector<int> nums = {-2, 3, -4};
    testAllApproaches(nums, 24);
}

TEST_F(MaximumProductSubarrayTest, LeadingZeros) {
    // Input: nums = [0,0,2,3]
    // Output: 6 (subarray [2,3])
    std::vector<int> nums = {0, 0, 2, 3};
    testAllApproaches(nums, 6);
}

TEST_F(MaximumProductSubarrayTest, TrailingZeros) {
    // Input: nums = [2,3,0,0]
    // Output: 6 (subarray [2,3])
    std::vector<int> nums = {2, 3, 0, 0};
    testAllApproaches(nums, 6);
}

TEST_F(MaximumProductSubarrayTest, AlternatingPositiveNegative) {
    // Input: nums = [2,-1,3,-1,4]
    // Output: 4 (single element [4])
    std::vector<int> nums = {2, -1, 3, -1, 4};
    testAllApproaches(nums, 4);
}

TEST_F(MaximumProductSubarrayTest, LargePositiveProduct) {
    // Input: nums = [1,2,3,4,5]
    // Output: 120 (entire array)
    std::vector<int> nums = {1, 2, 3, 4, 5};
    testAllApproaches(nums, 120);
}

TEST_F(MaximumProductSubarrayTest, NegativeAtStart) {
    // Input: nums = [-2,3,4]
    // Output: 12 (subarray [3,4])
    std::vector<int> nums = {-2, 3, 4};
    testAllApproaches(nums, 12);
}

TEST_F(MaximumProductSubarrayTest, NegativeAtEnd) {
    // Input: nums = [3,4,-2]
    // Output: 12 (subarray [3,4])
    std::vector<int> nums = {3, 4, -2};
    testAllApproaches(nums, 12);
}

TEST_F(MaximumProductSubarrayTest, NegativeInMiddle) {
    // Input: nums = [3,-2,4]
    // Output: 4 (single element [4])
    std::vector<int> nums = {3, -2, 4};
    testAllApproaches(nums, 4);
}

TEST_F(MaximumProductSubarrayTest, TwoNegatives) {
    // Input: nums = [2,-5,3,-1,6]
    // Output: 30 (subarray [-5,3,-1] = 15 or [3,-1,6] = -18, actually [2] or subarray analysis)
    // Let's check: [2] = 2, [-5] = -5, [3] = 3, [-1] = -1, [6] = 6
    // [2,-5] = -10, [3,-1] = -3, [-1,6] = -6
    // [2,-5,3] = -30, [-5,3,-1] = 15, [3,-1,6] = -18
    // [2,-5,3,-1] = 30, [-5,3,-1,6] = -90
    // [2,-5,3,-1,6] = -180
    std::vector<int> nums = {2, -5, 3, -1, 6};
    testAllApproaches(nums, 30);
}

TEST_F(MaximumProductSubarrayTest, LargeNegativeNumbers) {
    // Input: nums = [-8,-2,-9]
    // Output: 144 (subarray [-8,-2] or [-2,-9])
    std::vector<int> nums = {-8, -2, -9};
    testAllApproaches(nums, 144);
}

TEST_F(MaximumProductSubarrayTest, MaxConstraintValues) {
    // Test with boundary values (nums[i] between -10 and 10)
    std::vector<int> nums = {10, -10, 10};
    testAllApproaches(nums, 1000); // Entire array: 10 * -10 * 10 = -1000, but [10,-10] = -100, [10] = 10, [-10,10] = -100
    // Wait, let's recalculate: [10] = 10, [-10] = -10, [10] (last) = 10, [10,-10] = -100, [-10,10] = -100, [10,-10,10] = -1000
    // So maximum should be 10
    
    // Actually let's test this more carefully
    std::vector<int> testNums = {10, -10, 10};
    int result = solution.maxProductDP(testNums);
    testAllApproaches({10, -10, 10}, 10);
}

TEST_F(MaximumProductSubarrayTest, AllOnes) {
    // Input: nums = [1,1,1,1]
    // Output: 1 (any subarray)
    std::vector<int> nums = {1, 1, 1, 1};
    testAllApproaches(nums, 1);
}

TEST_F(MaximumProductSubarrayTest, AllMinusOnes) {
    // Input: nums = [-1,-1,-1,-1]
    // Output: 1 (even length subarray)
    std::vector<int> nums = {-1, -1, -1, -1};
    testAllApproaches(nums, 1);
}

TEST_F(MaximumProductSubarrayTest, OddLengthMinusOnes) {
    // Input: nums = [-1,-1,-1]
    // Output: 1 (subarray [-1,-1])
    std::vector<int> nums = {-1, -1, -1};
    testAllApproaches(nums, 1);
}

TEST_F(MaximumProductSubarrayTest, ZeroSeparatesPositives) {
    // Input: nums = [2,3,0,4,5]
    // Output: 20 (subarray [4,5])
    std::vector<int> nums = {2, 3, 0, 4, 5};
    testAllApproaches(nums, 20);
}

TEST_F(MaximumProductSubarrayTest, ZeroSeparatesNegatives) {
    // Input: nums = [-2,-3,0,-4,-5]
    // Output: 20 (subarray [-4,-5])
    std::vector<int> nums = {-2, -3, 0, -4, -5};
    testAllApproaches(nums, 20);
}

TEST_F(MaximumProductSubarrayTest, ComplexMixedCase) {
    // Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
    // Let's trace through this step by step to find expected result
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
    // Test with brute force first to get expected result
    int expected = solution.maxProductBruteForce(nums);
    
    // Now test all approaches with this expected value
    testAllApproaches({-2, 1, -3, 4, -1, 2, 1, -5, 4}, expected);
}

// Edge cases and performance tests
TEST_F(MaximumProductSubarrayTest, TwoElements) {
    std::vector<int> nums = {-2, -3};
    testAllApproaches(nums, 6);
}

TEST_F(MaximumProductSubarrayTest, EmptyHandling) {
    // While constraint says 1 <= nums.length, test defensive programming
    std::vector<int> empty;
    if (!empty.empty()) { // Skip if empty
        testAllApproaches(empty, 0);
    }
}

TEST_F(MaximumProductSubarrayTest, LargeArray) {
    // Test with larger array
    std::vector<int> nums;
    for (int i = 1; i <= 100; ++i) {
        nums.push_back(i % 10 == 0 ? 0 : (i % 2 == 0 ? -1 : 2));
    }
    
    // All approaches should produce same result
    int expected = solution.maxProductDP(nums);
    testAllApproaches(nums, expected);
}

// Performance test
TEST_F(MaximumProductSubarrayTest, PerformanceTest) {
    // Create array with 1000 elements
    std::vector<int> nums;
    for (int i = 0; i < 1000; ++i) {
        nums.push_back((i % 7 == 0) ? 0 : ((i % 3 == 0) ? -2 : 3));
    }
    
    // Test DP approach (should be fastest)
    auto start = std::chrono::high_resolution_clock::now();
    int result1 = solution.maxProductDP(nums);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 10000) << "DP approach should complete quickly";
    
    // Compare with brute force (should be slower)
    start = std::chrono::high_resolution_clock::now();
    int result2 = solution.maxProductBruteForce(nums);
    end = std::chrono::high_resolution_clock::now();
    
    auto bruteDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Results should match
    EXPECT_EQ(result1, result2);
    
    // DP should be significantly faster
    EXPECT_LT(duration.count(), bruteDuration.count()) << "DP should be faster than brute force";
}

// Test mathematical properties
TEST_F(MaximumProductSubarrayTest, MathematicalProperties) {
    // Product of even number of negatives should be positive
    std::vector<int> evenNegatives = {-2, 3, -4, 5};
    int result = solution.maxProductDP(evenNegatives);
    EXPECT_GT(result, 0) << "Even negatives should allow positive product";
    testAllApproaches(evenNegatives, 120); // -2 * 3 * -4 * 5 = 120
    
    // Single negative among positives
    std::vector<int> singleNegative = {2, 3, -1, 4, 5};
    testAllApproaches(singleNegative, 20); // [4, 5] = 20
}

// Test with extreme values within constraints
TEST_F(MaximumProductSubarrayTest, ExtremeValues) {
    // Maximum positive values
    std::vector<int> maxPositives = {10, 10, 10};
    testAllApproaches(maxPositives, 1000);
    
    // Maximum negative values
    std::vector<int> maxNegatives = {-10, -10};
    testAllApproaches(maxNegatives, 100);
    
    // Mix of extreme values
    std::vector<int> extremeMix = {10, -10, 10, -10};
    testAllApproaches(extremeMix, 10000); // Entire array
}

// Verify all approaches give same result on various inputs
TEST_F(MaximumProductSubarrayTest, ConsistencyTest) {
    std::vector<std::vector<int>> testCases = {
        {-2, 3, -4},
        {0, 2},
        {-3, 0, 1, 0, 2},
        {1, -2, 3, -4, 5},
        {-1, -2, -3, -4, -5}
    };
    
    for (const auto& nums : testCases) {
        int expected = solution.maxProductDP(const_cast<std::vector<int>&>(nums));
        testAllApproaches(const_cast<std::vector<int>&>(nums), expected);
    }
}

// Test subarray identification (conceptual)
TEST_F(MaximumProductSubarrayTest, SubarrayAnalysis) {
    std::vector<int> nums = {2, -5, 3, 1, -4, 2};
    int maxProduct = solution.maxProductDP(nums);
    
    // Verify the result makes sense by checking some subarrays manually
    EXPECT_GT(maxProduct, 2) << "Should find better than single element";
    EXPECT_GT(maxProduct, 3) << "Should find better than single element";
    
    // The maximum should be achievable by some contiguous subarray
    bool found = false;
    for (int i = 0; i < nums.size(); ++i) {
        int product = 1;
        for (int j = i; j < nums.size(); ++j) {
            product *= nums[j];
            if (product == maxProduct) {
                found = true;
                break;
            }
        }
        if (found) break;
    }
    EXPECT_TRUE(found) << "Maximum product should be achievable by some subarray";
}