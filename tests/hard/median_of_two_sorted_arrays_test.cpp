#include <gtest/gtest.h>
#include "hard/median_of_two_sorted_arrays.h"
#include <cmath>

using namespace leetcode::hard;

class MedianOfTwoSortedArraysTest : public ::testing::Test {
protected:
    MedianOfTwoSortedArrays solution;
    
    void verifyAllApproaches(std::vector<int> nums1, std::vector<int> nums2, double expected) {
        const double epsilon = 1e-5;
        
        auto n1_1 = nums1, n2_1 = nums2;
        auto n1_2 = nums1, n2_2 = nums2;
        auto n1_3 = nums1, n2_3 = nums2;
        auto n1_4 = nums1, n2_4 = nums2;
        auto n1_5 = nums1, n2_5 = nums2;
        auto n1_6 = nums1, n2_6 = nums2;
        
        EXPECT_NEAR(solution.findMedianMerge(n1_1, n2_1), expected, epsilon) 
            << "Merge approach failed";
        EXPECT_NEAR(solution.findMedianBinarySearch(n1_2, n2_2), expected, epsilon) 
            << "Binary Search approach failed";
        EXPECT_NEAR(solution.findMedianTwoPointers(n1_3, n2_3), expected, epsilon) 
            << "Two Pointers approach failed";
        EXPECT_NEAR(solution.findMedianDivideConquer(n1_4, n2_4), expected, epsilon) 
            << "Divide and Conquer approach failed";
        EXPECT_NEAR(solution.findMedianKthElement(n1_5, n2_5), expected, epsilon) 
            << "Kth Element approach failed";
        EXPECT_NEAR(solution.findMedianHeap(n1_6, n2_6), expected, epsilon) 
            << "Heap approach failed";
    }
};

TEST_F(MedianOfTwoSortedArraysTest, BasicEvenTotal) {
    verifyAllApproaches({1, 3}, {2}, 2.0);
}

TEST_F(MedianOfTwoSortedArraysTest, BasicOddTotal) {
    verifyAllApproaches({1, 2}, {3, 4}, 2.5);
}

TEST_F(MedianOfTwoSortedArraysTest, EmptyFirstArray) {
    verifyAllApproaches({}, {1}, 1.0);
}

TEST_F(MedianOfTwoSortedArraysTest, EmptySecondArray) {
    verifyAllApproaches({2}, {}, 2.0);
}

TEST_F(MedianOfTwoSortedArraysTest, BothSingleElement) {
    verifyAllApproaches({1}, {2}, 1.5);
}

TEST_F(MedianOfTwoSortedArraysTest, IdenticalArrays) {
    verifyAllApproaches({1, 2, 3}, {1, 2, 3}, 2.0);
}

TEST_F(MedianOfTwoSortedArraysTest, NoOverlap) {
    verifyAllApproaches({1, 2, 3}, {4, 5, 6}, 3.5);
}

TEST_F(MedianOfTwoSortedArraysTest, CompleteOverlap) {
    verifyAllApproaches({1, 3, 5}, {2, 4, 6}, 3.5);
}

TEST_F(MedianOfTwoSortedArraysTest, DifferentSizes) {
    verifyAllApproaches({1, 2}, {3, 4, 5, 6, 7}, 4.0);
}

TEST_F(MedianOfTwoSortedArraysTest, AllNegativeNumbers) {
    verifyAllApproaches({-5, -3, -1}, {-4, -2}, -3.0);
}

TEST_F(MedianOfTwoSortedArraysTest, MixedPositiveNegative) {
    verifyAllApproaches({-3, -1, 1}, {-2, 0, 2}, -0.5);
}

TEST_F(MedianOfTwoSortedArraysTest, SingleElementEach) {
    verifyAllApproaches({100}, {200}, 150.0);
}

TEST_F(MedianOfTwoSortedArraysTest, LargeArrays) {
    verifyAllApproaches({1, 3, 5, 7, 9}, {2, 4, 6, 8, 10}, 5.5);
}

TEST_F(MedianOfTwoSortedArraysTest, DuplicateElements) {
    verifyAllApproaches({1, 1, 1}, {1, 1, 1}, 1.0);
}

TEST_F(MedianOfTwoSortedArraysTest, EmptyBothArrays) {
    std::vector<int> empty1, empty2 = {1};
    verifyAllApproaches(empty1, empty2, 1.0);
}

TEST_F(MedianOfTwoSortedArraysTest, VeryDifferentSizes) {
    verifyAllApproaches({1}, {2, 3, 4, 5, 6, 7, 8}, 4.5);
}

TEST_F(MedianOfTwoSortedArraysTest, ConsecutiveNumbers) {
    verifyAllApproaches({1, 3, 5, 7}, {2, 4, 6, 8}, 4.5);
}

TEST_F(MedianOfTwoSortedArraysTest, GapBetweenArrays) {
    verifyAllApproaches({1, 2}, {100, 200}, 50.5);
}

TEST_F(MedianOfTwoSortedArraysTest, ZeroInArrays) {
    verifyAllApproaches({-1, 0}, {0, 1}, 0.0);
}

TEST_F(MedianOfTwoSortedArraysTest, AllZeros) {
    verifyAllApproaches({0, 0}, {0, 0}, 0.0);
}

TEST_F(MedianOfTwoSortedArraysTest, IncreasingSequence) {
    verifyAllApproaches({1, 2, 3}, {4, 5, 6, 7}, 4.0);
}

TEST_F(MedianOfTwoSortedArraysTest, InterleavedValues) {
    verifyAllApproaches({1, 4, 7}, {2, 5, 8}, 4.5);
}

TEST_F(MedianOfTwoSortedArraysTest, ExtremeDifference) {
    verifyAllApproaches({-1000000}, {1000000}, 0.0);
}

TEST_F(MedianOfTwoSortedArraysTest, MultipleDuplicates) {
    verifyAllApproaches({1, 2, 2, 3}, {2, 2, 3, 4}, 2.0);
}

TEST_F(MedianOfTwoSortedArraysTest, LongFirstShortSecond) {
    verifyAllApproaches({1, 2, 3, 4, 5, 6, 7, 8, 9}, {5}, 5.0);
}