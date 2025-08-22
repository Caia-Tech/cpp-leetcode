#include <gtest/gtest.h>
#include "easy/missing_number.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class MissingNumberTest : public ::testing::Test {
protected:
    void testAllApproaches(std::vector<int> nums, int expected) {
        auto nums1 = nums;
        auto nums2 = nums;
        auto nums3 = nums;
        auto nums4 = nums;
        auto nums5 = nums;
        auto nums6 = nums;

        MissingNumberSort s1;
        MissingNumberHashSet s2;
        MissingNumberSum s3;
        MissingNumberXor s4;
        MissingNumberBitset s5;
        MissingNumberCyclicSort s6;

        EXPECT_EQ(s1.missingNumber(nums1), expected);
        EXPECT_EQ(s2.missingNumber(nums2), expected);
        EXPECT_EQ(s3.missingNumber(nums3), expected);
        EXPECT_EQ(s4.missingNumber(nums4), expected);
        EXPECT_EQ(s5.missingNumber(nums5), expected);
        EXPECT_EQ(s6.missingNumber(nums6), expected);
    }
};

TEST_F(MissingNumberTest, MissingAtEnd) {
    testAllApproaches({3,0,1}, 2);
}

TEST_F(MissingNumberTest, MissingAtStart) {
    testAllApproaches({1,2,3}, 0);
}

TEST_F(MissingNumberTest, MissingInMiddle) {
    testAllApproaches({0,1,3}, 2);
}

TEST_F(MissingNumberTest, SingleElement) {
    testAllApproaches({0}, 1);
}

TEST_F(MissingNumberTest, LargerArray) {
    testAllApproaches({9,6,4,2,3,5,7,0,1}, 8);
}

} // namespace test
} // namespace easy
} // namespace leetcode

