#include <gtest/gtest.h>
#include "easy/merge_two_sorted_lists.h"
#include "utils/data_structures.h"

using namespace std;
using namespace leetcode::utils;

namespace leetcode {
namespace easy {
namespace test {

class MergeTwoSortedListsTest : public ::testing::Test {
protected:
    void verifyAllApproaches(const vector<int>& a, const vector<int>& b, const vector<int>& expected) {
        MergeTwoSortedLists solver;

        auto run = [&](auto func) {
            ListNode* l1 = vectorToList(a);
            ListNode* l2 = vectorToList(b);
            ListNode* res = (solver.*func)(l1, l2);
            vector<int> out = listToVector(res);
            deleteList(res);
            return out;
        };

        EXPECT_EQ(run(&MergeTwoSortedLists::mergeTwoListsIterative), expected);
        EXPECT_EQ(run(&MergeTwoSortedLists::mergeTwoListsRecursive), expected);
        EXPECT_EQ(run(&MergeTwoSortedLists::mergeTwoListsInPlace), expected);
        EXPECT_EQ(run(&MergeTwoSortedLists::mergeTwoListsArray), expected);
        EXPECT_EQ(run(&MergeTwoSortedLists::mergeTwoListsPriorityQueue), expected);
        EXPECT_EQ(run(&MergeTwoSortedLists::mergeTwoListsSentinel), expected);
    }
};

TEST_F(MergeTwoSortedListsTest, Typical) {
    verifyAllApproaches({1,2,4}, {1,3,4}, {1,1,2,3,4,4});
}

TEST_F(MergeTwoSortedListsTest, OneEmpty) {
    verifyAllApproaches({}, {0}, {0});
}

TEST_F(MergeTwoSortedListsTest, BothEmpty) {
    verifyAllApproaches({}, {}, {});
}

TEST_F(MergeTwoSortedListsTest, DifferentLengths) {
    verifyAllApproaches({1,2,4,5}, {3,4}, {1,2,3,4,4,5});
}

} // namespace test
} // namespace easy
} // namespace leetcode

