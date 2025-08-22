#include <gtest/gtest.h>
#include "medium/search_in_rotated_sorted_array.h"
#include <chrono>

using namespace leetcode::medium;

class SearchInRotatedSortedArrayTest : public ::testing::Test {
protected:
    SearchInRotatedSortedArray solution;
    
    // Helper function to test all approaches
    void testAllApproaches(const std::vector<int>& nums, int target, int expected) {
        EXPECT_EQ(solution.searchModifiedBinarySearch(nums, target), expected) 
            << "Modified binary search failed for target " << target;
        
        EXPECT_EQ(solution.searchFindPivotFirst(nums, target), expected) 
            << "Find pivot first approach failed for target " << target;
        
        EXPECT_EQ(solution.searchRecursive(nums, target), expected) 
            << "Recursive approach failed for target " << target;
        
        EXPECT_EQ(solution.searchLinear(nums, target), expected) 
            << "Linear approach failed for target " << target;
        
        EXPECT_EQ(solution.searchUnrotate(nums, target), expected) 
            << "Unrotate approach failed for target " << target;
        
        EXPECT_EQ(solution.searchThreeWayPartition(nums, target), expected) 
            << "Three-way partition approach failed for target " << target;
    }
};

TEST_F(SearchInRotatedSortedArrayTest, BasicExample1) {
    // Input: nums = [4,5,6,7,0,1,2], target = 0 -> Output: 4
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    testAllApproaches(nums, 0, 4);
}

TEST_F(SearchInRotatedSortedArrayTest, BasicExample2) {
    // Input: nums = [4,5,6,7,0,1,2], target = 3 -> Output: -1
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    testAllApproaches(nums, 3, -1);
}

TEST_F(SearchInRotatedSortedArrayTest, SingleElement) {
    // Input: nums = [1], target = 0 -> Output: -1
    std::vector<int> nums = {1};
    testAllApproaches(nums, 0, -1);
}

TEST_F(SearchInRotatedSortedArrayTest, SingleElementFound) {
    // Input: nums = [1], target = 1 -> Output: 0
    std::vector<int> nums = {1};
    testAllApproaches(nums, 1, 0);
}

TEST_F(SearchInRotatedSortedArrayTest, NoRotation) {
    // Input: nums = [1,2,3,4,5], target = 3 -> Output: 2
    std::vector<int> nums = {1, 2, 3, 4, 5};
    testAllApproaches(nums, 3, 2);
}

TEST_F(SearchInRotatedSortedArrayTest, NoRotationNotFound) {
    // Input: nums = [1,2,3,4,5], target = 6 -> Output: -1
    std::vector<int> nums = {1, 2, 3, 4, 5};
    testAllApproaches(nums, 6, -1);
}

TEST_F(SearchInRotatedSortedArrayTest, RotationAtBeginning) {
    // Input: nums = [2,3,4,5,1], target = 1 -> Output: 4
    std::vector<int> nums = {2, 3, 4, 5, 1};
    testAllApproaches(nums, 1, 4);
}

TEST_F(SearchInRotatedSortedArrayTest, RotationAtEnd) {
    // Input: nums = [5,1,2,3,4], target = 5 -> Output: 0
    std::vector<int> nums = {5, 1, 2, 3, 4};
    testAllApproaches(nums, 5, 0);
}

TEST_F(SearchInRotatedSortedArrayTest, TwoElements) {
    // Input: nums = [1,3], target = 3 -> Output: 1
    std::vector<int> nums = {1, 3};
    testAllApproaches(nums, 3, 1);
}

TEST_F(SearchInRotatedSortedArrayTest, TwoElementsRotated) {
    // Input: nums = [3,1], target = 1 -> Output: 1
    std::vector<int> nums = {3, 1};
    testAllApproaches(nums, 1, 1);
}

TEST_F(SearchInRotatedSortedArrayTest, TargetAtRotationPoint) {
    // Input: nums = [4,5,6,7,0,1,2], target = 7 -> Output: 3
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    testAllApproaches(nums, 7, 3);
}

TEST_F(SearchInRotatedSortedArrayTest, TargetAfterRotationPoint) {
    // Input: nums = [4,5,6,7,0,1,2], target = 1 -> Output: 5
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    testAllApproaches(nums, 1, 5);
}

TEST_F(SearchInRotatedSortedArrayTest, TargetBeforeRotationPoint) {
    // Input: nums = [4,5,6,7,0,1,2], target = 5 -> Output: 1
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    testAllApproaches(nums, 5, 1);
}

TEST_F(SearchInRotatedSortedArrayTest, LargerArray) {
    // Input: nums = [6,7,8,9,1,2,3,4,5], target = 2 -> Output: 5
    std::vector<int> nums = {6, 7, 8, 9, 1, 2, 3, 4, 5};
    testAllApproaches(nums, 2, 5);
}

TEST_F(SearchInRotatedSortedArrayTest, RotationInMiddle) {
    // Input: nums = [3,4,5,1,2], target = 4 -> Output: 1
    std::vector<int> nums = {3, 4, 5, 1, 2};
    testAllApproaches(nums, 4, 1);
}

TEST_F(SearchInRotatedSortedArrayTest, SearchFirstElement) {
    // Input: nums = [4,5,6,7,0,1,2], target = 4 -> Output: 0
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    testAllApproaches(nums, 4, 0);
}

TEST_F(SearchInRotatedSortedArrayTest, SearchLastElement) {
    // Input: nums = [4,5,6,7,0,1,2], target = 2 -> Output: 6
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    testAllApproaches(nums, 2, 6);
}

TEST_F(SearchInRotatedSortedArrayTest, NegativeNumbers) {
    // Input: nums = [-1,0,3,5,9,12], target = 9 -> Output: 4
    std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
    testAllApproaches(nums, 9, 4);
}

TEST_F(SearchInRotatedSortedArrayTest, NegativeNumbersRotated) {
    // Input: nums = [9,12,-1,0,3,5], target = 0 -> Output: 3
    std::vector<int> nums = {9, 12, -1, 0, 3, 5};
    testAllApproaches(nums, 0, 3);
}

TEST_F(SearchInRotatedSortedArrayTest, AllNegativeNumbers) {
    // Input: nums = [-5,-3,-1], target = -3 -> Output: 1
    std::vector<int> nums = {-5, -3, -1};
    testAllApproaches(nums, -3, 1);
}

TEST_F(SearchInRotatedSortedArrayTest, AllNegativeRotated) {
    // Input: nums = [-1,-5,-3], target = -3 -> Output: 2
    std::vector<int> nums = {-1, -5, -3};
    testAllApproaches(nums, -3, 2);
}

TEST_F(SearchInRotatedSortedArrayTest, BoundaryValues) {
    // Test with constraint boundary values
    std::vector<int> nums = {10000, -10000, -5000, 0, 5000};
    testAllApproaches(nums, -5000, 2);
    testAllApproaches(nums, 10000, 0);
    testAllApproaches(nums, 0, 3);
}

TEST_F(SearchInRotatedSortedArrayTest, MinimalRotation) {
    // Rotation by 1 position
    std::vector<int> nums = {2, 1};
    testAllApproaches(nums, 1, 1);
    testAllApproaches(nums, 2, 0);
}

TEST_F(SearchInRotatedSortedArrayTest, MaximalRotation) {
    // Rotation by n-1 positions (almost full rotation)
    std::vector<int> nums = {5, 1, 2, 3, 4};
    testAllApproaches(nums, 3, 3);
}

// Performance test for O(log n) complexity
TEST_F(SearchInRotatedSortedArrayTest, PerformanceTest) {
    // Create larger rotated array
    std::vector<int> nums;
    int rotationPoint = 500;
    
    // Add elements after rotation point (0 to 999)
    for (int i = rotationPoint; i < 1000; ++i) {
        nums.push_back(i);
    }
    // Add elements before rotation point (1000 to 1000 + rotationPoint - 1)
    for (int i = 1000; i < 1000 + rotationPoint; ++i) {
        nums.push_back(i);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    int result = solution.searchModifiedBinarySearch(nums, 750);
    auto end = std::chrono::high_resolution_clock::now();
    
    EXPECT_EQ(result, 250); // 750 should be at index 250
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 100) << "Algorithm should complete quickly for size 1000";
}

// Test edge case where target is at rotation boundary
TEST_F(SearchInRotatedSortedArrayTest, RotationBoundaryTests) {
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    
    // Test elements right before and after rotation
    testAllApproaches(nums, 7, 3); // Last element before rotation
    testAllApproaches(nums, 0, 4); // First element after rotation
}

// Test correctness across different rotation amounts
TEST_F(SearchInRotatedSortedArrayTest, VariousRotationAmounts) {
    std::vector<int> base = {1, 2, 3, 4, 5, 6, 7};
    
    // Test different rotation amounts
    for (int rotation = 0; rotation < base.size(); ++rotation) {
        std::vector<int> rotated;
        for (int i = rotation; i < base.size(); ++i) {
            rotated.push_back(base[i]);
        }
        for (int i = 0; i < rotation; ++i) {
            rotated.push_back(base[i]);
        }
        
        // Test finding each element in rotated array
        for (int target = 1; target <= 7; ++target) {
            int expectedIndex = (target - 1 - rotation + base.size()) % base.size();
            testAllApproaches(rotated, target, expectedIndex);
        }
    }
}