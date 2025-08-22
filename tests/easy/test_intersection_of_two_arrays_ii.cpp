#include <gtest/gtest.h>
#include <algorithm>
#include "easy/intersection_of_two_arrays_ii.h"

using namespace leetcode::easy;

class IntersectionOfTwoArraysIITest : public ::testing::Test {
protected:
    void verify(std::vector<int> a, std::vector<int> b, std::vector<int> expected) {
        std::sort(expected.begin(), expected.end());

        std::vector<int> r1 = IntersectionHashMap().intersect(a, b);
        std::sort(r1.begin(), r1.end());
        EXPECT_EQ(r1, expected);

        std::vector<int> r2 = IntersectionSortTwoPointers().intersect(a, b);
        std::sort(r2.begin(), r2.end());
        EXPECT_EQ(r2, expected);

        std::vector<int> r3 = IntersectionSortBinarySearch().intersect(a, b);
        std::sort(r3.begin(), r3.end());
        EXPECT_EQ(r3, expected);

        std::vector<int> r4 = IntersectionMultiset().intersect(a, b);
        std::sort(r4.begin(), r4.end());
        EXPECT_EQ(r4, expected);

        std::vector<int> r5 = IntersectionHashMapOptimized().intersect(a, b);
        std::sort(r5.begin(), r5.end());
        EXPECT_EQ(r5, expected);

        std::vector<int> r6 = IntersectionFrequencyArray().intersect(a, b);
        std::sort(r6.begin(), r6.end());
        EXPECT_EQ(r6, expected);
    }
};

TEST_F(IntersectionOfTwoArraysIITest, BasicDuplicates) {
    verify({1,2,2,1}, {2,2}, {2,2});
}

TEST_F(IntersectionOfTwoArraysIITest, DifferentSizes) {
    verify({4,9,5}, {9,4,9,8,4}, {4,9});
}

TEST_F(IntersectionOfTwoArraysIITest, NoIntersection) {
    verify({1,2,3}, {4,5,6}, {});
}

TEST_F(IntersectionOfTwoArraysIITest, ManyZeros) {
    verify({0,0,0}, {0,0}, {0,0});
}

TEST_F(IntersectionOfTwoArraysIITest, SingleElement) {
    verify({1}, {1,1,1}, {1});
}

