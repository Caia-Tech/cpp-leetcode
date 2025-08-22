#include <gtest/gtest.h>
#include "hard/merge_k_sorted_lists.h"
#include "utils/data_structures.h"
#include "utils/test_utils.h"

using namespace leetcode::hard;
using namespace leetcode::utils;

class MergeKSortedListsTest : public ::testing::Test {
protected:
    MergeKSortedLists solution;
    
    std::vector<ListNode*> createLists(const std::vector<std::vector<int>>& values) {
        std::vector<ListNode*> lists;
        for (const auto& vals : values) {
            lists.push_back(vectorToList(vals));
        }
        return lists;
    }
    
    void cleanupLists(std::vector<ListNode*>& lists) {
        for (auto list : lists) {
            deleteList(list);
        }
    }
    
    void verifyAllApproaches(std::vector<std::vector<int>> input, 
                           std::vector<int> expected) {
        auto lists1 = createLists(input);
        auto lists2 = createLists(input);
        auto lists3 = createLists(input);
        auto lists4 = createLists(input);
        auto lists5 = createLists(input);
        auto lists6 = createLists(input);
        
        ListNode* result1 = solution.mergeKListsBruteForce(lists1);
        ListNode* result2 = solution.mergeKListsHeap(lists2);
        ListNode* result3 = solution.mergeKListsSequential(lists3);
        ListNode* result4 = solution.mergeKListsDivideConquer(lists4);
        ListNode* result5 = solution.mergeKListsIterative(lists5);
        ListNode* result6 = solution.mergeKListsTournament(lists6);
        
        EXPECT_EQ(listToVector(result1), expected) << "Brute Force failed";
        EXPECT_EQ(listToVector(result2), expected) << "Heap failed";
        EXPECT_EQ(listToVector(result3), expected) << "Sequential failed";
        EXPECT_EQ(listToVector(result4), expected) << "Divide and Conquer failed";
        EXPECT_EQ(listToVector(result5), expected) << "Iterative failed";
        EXPECT_EQ(listToVector(result6), expected) << "Tournament failed";
        
        deleteList(result1);
        deleteList(result2);
        deleteList(result3);
        deleteList(result4);
        deleteList(result5);
        deleteList(result6);
    }
};

TEST_F(MergeKSortedListsTest, BasicCase) {
    verifyAllApproaches({{1,4,5}, {1,3,4}, {2,6}}, {1,1,2,3,4,4,5,6});
}

TEST_F(MergeKSortedListsTest, EmptyLists) {
    verifyAllApproaches({}, {});
}

TEST_F(MergeKSortedListsTest, SingleEmptyList) {
    verifyAllApproaches({{}}, {});
}

TEST_F(MergeKSortedListsTest, SingleList) {
    verifyAllApproaches({{1,2,3}}, {1,2,3});
}

TEST_F(MergeKSortedListsTest, TwoLists) {
    verifyAllApproaches({{1,3,5}, {2,4,6}}, {1,2,3,4,5,6});
}

TEST_F(MergeKSortedListsTest, AllSingleElements) {
    verifyAllApproaches({{1}, {2}, {3}}, {1,2,3});
}

TEST_F(MergeKSortedListsTest, MixedEmptyAndNonEmpty) {
    verifyAllApproaches({{}, {1,3}, {}, {2,4}}, {1,2,3,4});
}

TEST_F(MergeKSortedListsTest, DuplicateValues) {
    verifyAllApproaches({{1,1,1}, {1,1,1}}, {1,1,1,1,1,1});
}

TEST_F(MergeKSortedListsTest, NegativeNumbers) {
    verifyAllApproaches({{-3,-1}, {-2,0}, {1,2}}, {-3,-2,-1,0,1,2});
}

TEST_F(MergeKSortedListsTest, LargeLists) {
    verifyAllApproaches({{1,3,5,7,9}, {2,4,6,8,10}, {0,11,12}}, 
                        {0,1,2,3,4,5,6,7,8,9,10,11,12});
}

TEST_F(MergeKSortedListsTest, SingleElementLists) {
    verifyAllApproaches({{5}, {3}, {7}, {1}, {9}}, {1,3,5,7,9});
}

TEST_F(MergeKSortedListsTest, IdenticalLists) {
    verifyAllApproaches({{1,2,3}, {1,2,3}, {1,2,3}}, {1,1,1,2,2,2,3,3,3});
}

TEST_F(MergeKSortedListsTest, AlternatingValues) {
    verifyAllApproaches({{1,3,5}, {2,4,6}}, {1,2,3,4,5,6});
}

TEST_F(MergeKSortedListsTest, ReverseOrder) {
    verifyAllApproaches({{5,6}, {3,4}, {1,2}}, {1,2,3,4,5,6});
}

TEST_F(MergeKSortedListsTest, VaryingLengths) {
    verifyAllApproaches({{1}, {2,3}, {4,5,6}, {7,8,9,10}}, 
                        {1,2,3,4,5,6,7,8,9,10});
}

TEST_F(MergeKSortedListsTest, AllZeros) {
    verifyAllApproaches({{0,0}, {0}, {0,0,0}}, {0,0,0,0,0,0});
}

TEST_F(MergeKSortedListsTest, MixedPositiveNegative) {
    verifyAllApproaches({{-5,-2}, {-3,0}, {1,4}}, {-5,-3,-2,0,1,4});
}

TEST_F(MergeKSortedListsTest, ConsecutiveNumbers) {
    verifyAllApproaches({{1,2}, {3,4}, {5,6}}, {1,2,3,4,5,6});
}

TEST_F(MergeKSortedListsTest, GapsInValues) {
    verifyAllApproaches({{1,10}, {5,15}, {7,20}}, {1,5,7,10,15,20});
}

TEST_F(MergeKSortedListsTest, ManySmallLists) {
    verifyAllApproaches({{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}}, 
                        {1,2,3,4,5,6,7,8});
}

TEST_F(MergeKSortedListsTest, ExtremeBounds) {
    verifyAllApproaches({{-10000}, {0}, {10000}}, {-10000,0,10000});
}

TEST_F(MergeKSortedListsTest, NestedMerge) {
    verifyAllApproaches({{1,5,9}, {2,6,10}, {3,7,11}, {4,8,12}}, 
                        {1,2,3,4,5,6,7,8,9,10,11,12});
}

TEST_F(MergeKSortedListsTest, SingleLongList) {
    verifyAllApproaches({{1,2,3,4,5,6,7,8,9,10}}, {1,2,3,4,5,6,7,8,9,10});
}

TEST_F(MergeKSortedListsTest, InterleavedSmallLists) {
    verifyAllApproaches({{1,4}, {2,5}, {3,6}}, {1,2,3,4,5,6});
}