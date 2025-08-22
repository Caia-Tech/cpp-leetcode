#include <gtest/gtest.h>
#include <vector>
#include "easy/remove_duplicates_from_sorted_array.h"

using namespace leetcode::easy;

class RemoveDuplicatesFromSortedArrayTest : public ::testing::Test {
protected:
    void verifyAll(const std::vector<int>& input, const std::vector<int>& expected) {
        RemoveDuplicatesFromSortedArray s;
        auto run = [&](auto method) {
            std::vector<int> nums = input;
            int k = (s.*method)(nums);
            EXPECT_EQ(k, expected.size());
            std::vector<int> result(nums.begin(), nums.begin() + k);
            EXPECT_EQ(result, expected);
        };
        run(&RemoveDuplicatesFromSortedArray::removeDuplicatesTwoPointers);
        run(&RemoveDuplicatesFromSortedArray::removeDuplicatesHashSet);
        run(&RemoveDuplicatesFromSortedArray::removeDuplicatesWriteIndex);
        run(&RemoveDuplicatesFromSortedArray::removeDuplicatesSTL);
        run(&RemoveDuplicatesFromSortedArray::removeDuplicatesOverwrite);
        run(&RemoveDuplicatesFromSortedArray::removeDuplicatesRecursive);
    }
};

TEST_F(RemoveDuplicatesFromSortedArrayTest, BasicCases) {
    verifyAll({1,1,2}, {1,2});
    verifyAll({0,0,1,1,1,2,2,3,3,4}, {0,1,2,3,4});
    verifyAll({1,2,3}, {1,2,3});
    verifyAll({1,1,1}, {1});
    verifyAll({1}, {1});
}

