#include <gtest/gtest.h>
#include "medium/kth_largest_element.h"
#include <vector>
#include <algorithm>
#include <random>

namespace leetcode {
namespace medium {
namespace test {

class KthLargestElementTest : public ::testing::Test {
protected:
    KthLargestElement solution;
    
    void testAllApproaches(std::vector<int> nums, int k, int expected) {
        // Create copies for each approach since some modify the input
        std::vector<int> nums1 = nums;
        std::vector<int> nums2 = nums;
        std::vector<int> nums3 = nums;
        std::vector<int> nums4 = nums;
        std::vector<int> nums5 = nums;
        std::vector<int> nums6 = nums;
        
        EXPECT_EQ(solution.findKthLargest(nums1, k), expected) 
            << "Min-Heap approach failed";
        EXPECT_EQ(solution.findKthLargestQuickSelect(nums2, k), expected) 
            << "QuickSelect approach failed";
        EXPECT_EQ(solution.findKthLargestMedianOfMedians(nums3, k), expected) 
            << "Median-of-Medians approach failed";
        EXPECT_EQ(solution.findKthLargestCountingSort(nums4, k), expected) 
            << "Counting Sort approach failed";
        EXPECT_EQ(solution.findKthLargestMaxHeap(nums5, k), expected) 
            << "Max-Heap approach failed";
        EXPECT_EQ(solution.findKthLargestSTL(nums6, k), expected) 
            << "STL nth_element approach failed";
    }
    
    // Helper to get expected result by sorting
    int getExpected(std::vector<int> nums, int k) {
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        return nums[k - 1];
    }
};

// Basic functionality tests
TEST_F(KthLargestElementTest, LeetCodeExample1) {
    // Example 1: [3,2,1,5,6,4], k = 2
    // Output: 5 (sorted: [6,5,4,3,2,1], 2nd largest is 5)
    testAllApproaches({3,2,1,5,6,4}, 2, 5);
}

TEST_F(KthLargestElementTest, LeetCodeExample2) {
    // Example 2: [3,2,3,1,2,4,5,5,6], k = 4
    // Output: 4 (sorted: [6,5,5,4,3,3,2,2,1], 4th largest is 4)
    testAllApproaches({3,2,3,1,2,4,5,5,6}, 4, 4);
}

// Edge cases
TEST_F(KthLargestElementTest, SingleElement) {
    testAllApproaches({1}, 1, 1);
    testAllApproaches({-5}, 1, -5);
    testAllApproaches({100}, 1, 100);
}

TEST_F(KthLargestElementTest, TwoElements) {
    testAllApproaches({1, 2}, 1, 2);
    testAllApproaches({1, 2}, 2, 1);
    testAllApproaches({5, 3}, 1, 5);
    testAllApproaches({5, 3}, 2, 3);
}

TEST_F(KthLargestElementTest, KEqualsOne) {
    testAllApproaches({3,2,1,5,6,4}, 1, 6);
    testAllApproaches({1,2,3,4,5}, 1, 5);
    testAllApproaches({-1,-2,-3}, 1, -1);
}

TEST_F(KthLargestElementTest, KEqualsLength) {
    testAllApproaches({3,2,1,5,6,4}, 6, 1);
    testAllApproaches({1,2,3,4,5}, 5, 1);
    testAllApproaches({10,20,30}, 3, 10);
}

// Duplicate elements
TEST_F(KthLargestElementTest, AllSameElements) {
    testAllApproaches({5,5,5,5,5}, 1, 5);
    testAllApproaches({5,5,5,5,5}, 3, 5);
    testAllApproaches({5,5,5,5,5}, 5, 5);
}

TEST_F(KthLargestElementTest, SomeDuplicates) {
    testAllApproaches({1,1,1,2,2,3}, 1, 3);
    testAllApproaches({1,1,1,2,2,3}, 2, 2);  // 2nd largest is 2
    testAllApproaches({1,1,1,2,2,3}, 4, 1);  // 4th largest is 1
    testAllApproaches({1,1,1,2,2,3}, 6, 1);
}

TEST_F(KthLargestElementTest, ManyDuplicates) {
    testAllApproaches({4,5,8,2,8,8,8}, 3, 8);
    testAllApproaches({1,2,2,2,2,3,3}, 2, 3);
}

// Negative numbers
TEST_F(KthLargestElementTest, AllNegative) {
    testAllApproaches({-1,-2,-3,-4,-5}, 1, -1);
    testAllApproaches({-1,-2,-3,-4,-5}, 3, -3);
    testAllApproaches({-1,-2,-3,-4,-5}, 5, -5);
}

TEST_F(KthLargestElementTest, MixedPositiveNegative) {
    testAllApproaches({-1,2,-3,4,-5}, 1, 4);
    testAllApproaches({-1,2,-3,4,-5}, 2, 2);
    testAllApproaches({-1,2,-3,4,-5}, 3, -1);
    testAllApproaches({-1,2,-3,4,-5}, 5, -5);
}

// Zero elements
TEST_F(KthLargestElementTest, WithZeros) {
    testAllApproaches({0,1,-1,0,2}, 1, 2);
    testAllApproaches({0,1,-1,0,2}, 2, 1);
    testAllApproaches({0,1,-1,0,2}, 3, 0);
    testAllApproaches({0,0,0}, 2, 0);
}

// Ordered arrays
TEST_F(KthLargestElementTest, AlreadySortedAscending) {
    testAllApproaches({1,2,3,4,5}, 1, 5);
    testAllApproaches({1,2,3,4,5}, 3, 3);
    testAllApproaches({1,2,3,4,5}, 5, 1);
}

TEST_F(KthLargestElementTest, AlreadySortedDescending) {
    testAllApproaches({5,4,3,2,1}, 1, 5);
    testAllApproaches({5,4,3,2,1}, 3, 3);
    testAllApproaches({5,4,3,2,1}, 5, 1);
}

TEST_F(KthLargestElementTest, ReverseSorted) {
    testAllApproaches({10,9,8,7,6,5,4,3,2,1}, 1, 10);
    testAllApproaches({10,9,8,7,6,5,4,3,2,1}, 5, 6);
    testAllApproaches({10,9,8,7,6,5,4,3,2,1}, 10, 1);
}

// Large arrays and performance tests
TEST_F(KthLargestElementTest, LargeArray) {
    std::vector<int> nums;
    for (int i = 1; i <= 100; i++) {
        nums.push_back(i);
    }
    
    testAllApproaches(nums, 1, 100);
    testAllApproaches(nums, 25, 76);
    testAllApproaches(nums, 50, 51);
    testAllApproaches(nums, 100, 1);
}

TEST_F(KthLargestElementTest, RandomArray) {
    std::vector<int> nums = {23, 45, 12, 67, 89, 34, 56, 78, 90, 11, 22, 33, 44, 55, 66};
    int k = 5;
    int expected = getExpected(nums, k);
    
    testAllApproaches(nums, k, expected);
}

// Constraint boundary tests
TEST_F(KthLargestElementTest, MinConstraints) {
    testAllApproaches({-10000}, 1, -10000);
    testAllApproaches({-10000, -9999}, 1, -9999);
    testAllApproaches({-10000, -9999}, 2, -10000);
}

TEST_F(KthLargestElementTest, MaxConstraints) {
    testAllApproaches({10000}, 1, 10000);
    testAllApproaches({9999, 10000}, 1, 10000);
    testAllApproaches({9999, 10000}, 2, 9999);
}

TEST_F(KthLargestElementTest, FullRange) {
    testAllApproaches({-10000, 0, 10000}, 1, 10000);
    testAllApproaches({-10000, 0, 10000}, 2, 0);
    testAllApproaches({-10000, 0, 10000}, 3, -10000);
}

// Special patterns
TEST_F(KthLargestElementTest, AlternatingPattern) {
    testAllApproaches({1,10,2,9,3,8,4,7,5,6}, 1, 10);
    testAllApproaches({1,10,2,9,3,8,4,7,5,6}, 5, 6);
    testAllApproaches({1,10,2,9,3,8,4,7,5,6}, 10, 1);
}

TEST_F(KthLargestElementTest, PeaksAndValleys) {
    testAllApproaches({5,1,9,3,7,2,8,4,6}, 1, 9);
    testAllApproaches({5,1,9,3,7,2,8,4,6}, 4, 6);
}

// Stress tests for different algorithms
TEST_F(KthLargestElementTest, QuickSelectWorstCase) {
    // Already sorted array can be worst case for poorly implemented quickselect
    std::vector<int> nums;
    for (int i = 1; i <= 50; i++) {
        nums.push_back(i);
    }
    
    testAllApproaches(nums, 25, 26);
}

TEST_F(KthLargestElementTest, HeapStressTest) {
    // Test where k is small relative to n (good for min-heap)
    std::vector<int> nums;
    for (int i = 100; i >= 1; i--) {
        nums.push_back(i);
    }
    
    testAllApproaches(nums, 3, 98); // 3rd largest in [100,99,98,...,1] is 98
}

TEST_F(KthLargestElementTest, CountingSortIdeal) {
    // Small range, many duplicates - ideal for counting sort
    std::vector<int> nums;
    for (int i = 0; i < 20; i++) {
        nums.push_back(i % 5);  // Only values 0,1,2,3,4
    }
    
    int expected = getExpected(nums, 10);
    testAllApproaches(nums, 10, expected);
}

// Middle element tests
TEST_F(KthLargestElementTest, MiddleElement) {
    testAllApproaches({1,2,3,4,5,6,7}, 4, 4); // Middle of odd-length array
    testAllApproaches({1,2,3,4,5,6}, 3, 4);   // Upper middle of even-length array
}

// Performance characteristics tests
TEST_F(KthLargestElementTest, SmallK) {
    // When k is small, min-heap should be efficient
    std::vector<int> nums;
    for (int i = 1000; i >= 1; i--) {
        nums.push_back(i);
    }
    
    testAllApproaches(nums, 1, 1000);
    testAllApproaches(nums, 2, 999);
    testAllApproaches(nums, 3, 998);
}

TEST_F(KthLargestElementTest, LargeK) {
    // When k is large (close to n), different algorithms might be better
    std::vector<int> nums = {10,9,8,7,6,5,4,3,2,1};
    
    testAllApproaches(nums, 8, 3);
    testAllApproaches(nums, 9, 2);
    testAllApproaches(nums, 10, 1);
}

// Randomized input tests
TEST_F(KthLargestElementTest, RandomizedInput) {
    std::vector<int> nums = {42, 17, 83, 29, 64, 91, 36, 58, 75, 12, 47, 68, 23, 95, 31};
    
    for (int k = 1; k <= nums.size(); k += 3) {
        int expected = getExpected(nums, k);
        testAllApproaches(nums, k, expected);
    }
}

// Median finding
TEST_F(KthLargestElementTest, FindMedian) {
    // Odd length - exact middle
    testAllApproaches({3,1,4,1,5,9,2}, 4, 3);
    
    // Even length - upper middle (4th of 6 elements)
    testAllApproaches({6,3,1,4,1,5}, 3, 4);
}

// Algorithm validation
TEST_F(KthLargestElementTest, AlgorithmConsistency) {
    // Test that all algorithms give same results
    std::vector<int> testCases[] = {
        {1},
        {2,1},
        {1,2,3},
        {3,2,1},
        {1,1,1},
        {1,2,1,2,1},
        {5,4,3,2,1,0,-1,-2},
        {-5,-4,-3,-2,-1,0,1,2}
    };
    
    for (auto& nums : testCases) {
        for (int k = 1; k <= nums.size(); k++) {
            int expected = getExpected(nums, k);
            
            // Create copies for each algorithm
            std::vector<int> nums1 = nums, nums2 = nums, nums3 = nums;
            std::vector<int> nums4 = nums, nums5 = nums, nums6 = nums;
            
            int result1 = solution.findKthLargest(nums1, k);
            int result2 = solution.findKthLargestQuickSelect(nums2, k);
            int result3 = solution.findKthLargestMedianOfMedians(nums3, k);
            int result4 = solution.findKthLargestCountingSort(nums4, k);
            int result5 = solution.findKthLargestMaxHeap(nums5, k);
            int result6 = solution.findKthLargestSTL(nums6, k);
            
            EXPECT_EQ(result1, expected) << "Min-heap failed for k=" << k;
            EXPECT_EQ(result2, expected) << "QuickSelect failed for k=" << k;
            EXPECT_EQ(result3, expected) << "Median-of-medians failed for k=" << k;
            EXPECT_EQ(result4, expected) << "Counting sort failed for k=" << k;
            EXPECT_EQ(result5, expected) << "Max-heap failed for k=" << k;
            EXPECT_EQ(result6, expected) << "STL failed for k=" << k;
            
            // All algorithms should agree
            EXPECT_EQ(result1, result2) << "Min-heap and QuickSelect disagree";
            EXPECT_EQ(result1, result3) << "Min-heap and Median-of-medians disagree";
            EXPECT_EQ(result1, result4) << "Min-heap and Counting sort disagree";
            EXPECT_EQ(result1, result5) << "Min-heap and Max-heap disagree";
            EXPECT_EQ(result1, result6) << "Min-heap and STL disagree";
        }
    }
}

}
}
}