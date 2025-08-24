#include <gtest/gtest.h>
#include "../../src/easy/remove_duplicates_from_sorted_list.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class RemoveDuplicatesFromSortedListTest : public ::testing::Test {
protected:
    // Helper to test all approaches with the same input
    void testAllApproaches(const std::vector<int>& input, const std::vector<int>& expected) {
        RemoveDuplicatesFromSortedList solution;
        
        // Create separate lists for each approach
        ListNode* list1 = solution.createList(input);
        ListNode* list2 = solution.createList(input);
        ListNode* list3 = solution.createList(input);
        ListNode* list4 = solution.createList(input);
        ListNode* list5 = solution.createList(input);
        ListNode* list6 = solution.createList(input);
        
        // Test each approach
        ListNode* result1 = solution.deleteDuplicatesIterative(list1);
        ListNode* result2 = solution.deleteDuplicatesRecursive(list2);
        ListNode* result3 = solution.deleteDuplicatesTwoPointer(list3);
        ListNode* result4 = solution.deleteDuplicatesHashSet(list4);
        ListNode* result5 = solution.deleteDuplicatesDummyHead(list5);
        ListNode* result6 = solution.deleteDuplicatesFunctional(list6);
        
        // Convert results to vectors for comparison
        std::vector<int> output1 = solution.listToVector(result1);
        std::vector<int> output2 = solution.listToVector(result2);
        std::vector<int> output3 = solution.listToVector(result3);
        std::vector<int> output4 = solution.listToVector(result4);
        std::vector<int> output5 = solution.listToVector(result5);
        std::vector<int> output6 = solution.listToVector(result6);
        
        // Verify all approaches give the same correct result
        EXPECT_EQ(output1, expected) << "Iterative approach failed for input: " << vectorToString(input);
        EXPECT_EQ(output2, expected) << "Recursive approach failed for input: " << vectorToString(input);
        EXPECT_EQ(output3, expected) << "Two-pointer approach failed for input: " << vectorToString(input);
        EXPECT_EQ(output4, expected) << "Hash set approach failed for input: " << vectorToString(input);
        EXPECT_EQ(output5, expected) << "Dummy head approach failed for input: " << vectorToString(input);
        EXPECT_EQ(output6, expected) << "Functional approach failed for input: " << vectorToString(input);
        
        // Clean up memory
        solution.deleteList(result1);
        solution.deleteList(result2);
        solution.deleteList(result3);
        solution.deleteList(result4);
        solution.deleteList(result5);
        solution.deleteList(result6);
    }
    
    // Helper to convert vector to string for error messages
    std::string vectorToString(const std::vector<int>& vec) {
        std::string result = "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) result += ", ";
            result += std::to_string(vec[i]);
        }
        result += "]";
        return result;
    }
};

// LeetCode Example Test Cases

TEST_F(RemoveDuplicatesFromSortedListTest, LeetCodeExample1) {
    // Input: head = [1,1,2]
    // Output: [1,2]
    testAllApproaches({1, 1, 2}, {1, 2});
}

TEST_F(RemoveDuplicatesFromSortedListTest, LeetCodeExample2) {
    // Input: head = [1,1,2,3,3]
    // Output: [1,2,3]
    testAllApproaches({1, 1, 2, 3, 3}, {1, 2, 3});
}

// Edge Cases

TEST_F(RemoveDuplicatesFromSortedListTest, EmptyList) {
    // Empty list should remain empty
    testAllApproaches({}, {});
}

TEST_F(RemoveDuplicatesFromSortedListTest, SingleElement) {
    // Single element list should remain unchanged
    testAllApproaches({5}, {5});
}

TEST_F(RemoveDuplicatesFromSortedListTest, TwoElementsNoDuplicate) {
    // Two different elements should remain unchanged
    testAllApproaches({1, 2}, {1, 2});
}

TEST_F(RemoveDuplicatesFromSortedListTest, TwoElementsDuplicate) {
    // Two identical elements should become one
    testAllApproaches({2, 2}, {2});
}

TEST_F(RemoveDuplicatesFromSortedListTest, AllSameElements) {
    // All identical elements should become one
    testAllApproaches({3, 3, 3, 3, 3}, {3});
}

TEST_F(RemoveDuplicatesFromSortedListTest, NoDuplicates) {
    // Already unique list should remain unchanged
    testAllApproaches({1, 2, 3, 4, 5}, {1, 2, 3, 4, 5});
}

// Pattern-based Tests

TEST_F(RemoveDuplicatesFromSortedListTest, ConsecutivePairs) {
    // Pattern: a, a, b, b, c, c
    testAllApproaches({1, 1, 3, 3, 5, 5}, {1, 3, 5});
}

TEST_F(RemoveDuplicatesFromSortedListTest, MixedDuplicatesAndSingles) {
    // Mixed pattern of duplicates and singles
    testAllApproaches({1, 2, 2, 3, 4, 4, 4, 5}, {1, 2, 3, 4, 5});
}

TEST_F(RemoveDuplicatesFromSortedListTest, DuplicatesAtBeginning) {
    // Duplicates at the start
    testAllApproaches({1, 1, 1, 2, 3, 4}, {1, 2, 3, 4});
}

TEST_F(RemoveDuplicatesFromSortedListTest, DuplicatesAtEnd) {
    // Duplicates at the end
    testAllApproaches({1, 2, 3, 4, 4, 4}, {1, 2, 3, 4});
}

TEST_F(RemoveDuplicatesFromSortedListTest, DuplicatesInMiddle) {
    // Duplicates in the middle
    testAllApproaches({1, 2, 3, 3, 3, 4, 5}, {1, 2, 3, 4, 5});
}

TEST_F(RemoveDuplicatesFromSortedListTest, AlternatingPattern) {
    // Pattern: single, duplicate, single, duplicate
    testAllApproaches({1, 2, 2, 3, 4, 4}, {1, 2, 3, 4});
}

// Negative Numbers

TEST_F(RemoveDuplicatesFromSortedListTest, NegativeNumbers) {
    // Test with negative numbers
    testAllApproaches({-3, -3, -2, -1, -1}, {-3, -2, -1});
}

TEST_F(RemoveDuplicatesFromSortedListTest, MixedNegativePositive) {
    // Mixed negative and positive numbers
    testAllApproaches({-2, -2, -1, 0, 1, 1, 2}, {-2, -1, 0, 1, 2});
}

TEST_F(RemoveDuplicatesFromSortedListTest, AllNegatives) {
    // All negative numbers with duplicates
    testAllApproaches({-5, -4, -4, -3, -3, -3, -2}, {-5, -4, -3, -2});
}

// Zero Values

TEST_F(RemoveDuplicatesFromSortedListTest, ZeroValues) {
    // Test with zeros
    testAllApproaches({-1, 0, 0, 0, 1}, {-1, 0, 1});
}

TEST_F(RemoveDuplicatesFromSortedListTest, AllZeros) {
    // All zeros
    testAllApproaches({0, 0, 0, 0}, {0});
}

TEST_F(RemoveDuplicatesFromSortedListTest, ZerosAndNonZeros) {
    // Zeros mixed with non-zeros
    testAllApproaches({-1, -1, 0, 0, 1, 1}, {-1, 0, 1});
}

// Boundary Values

TEST_F(RemoveDuplicatesFromSortedListTest, MinimumValues) {
    // Test with minimum constraint values
    testAllApproaches({-100, -100, -99}, {-100, -99});
}

TEST_F(RemoveDuplicatesFromSortedListTest, MaximumValues) {
    // Test with maximum constraint values
    testAllApproaches({99, 100, 100}, {99, 100});
}

TEST_F(RemoveDuplicatesFromSortedListTest, ConstraintRange) {
    // Test across full constraint range
    testAllApproaches({-100, -100, 0, 100, 100}, {-100, 0, 100});
}

// Longer Lists

TEST_F(RemoveDuplicatesFromSortedListTest, LongListWithDuplicates) {
    // Longer list with various duplicates
    testAllApproaches({1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 10, 10}, 
                     {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
}

TEST_F(RemoveDuplicatesFromSortedListTest, SequentialNumbers) {
    // Sequential numbers with each appearing multiple times
    std::vector<int> input, expected;
    for (int i = 1; i <= 20; ++i) {
        // Add each number i times
        for (int j = 0; j < i; ++j) {
            input.push_back(i);
        }
        expected.push_back(i);
    }
    testAllApproaches(input, expected);
}

// Specific Duplicate Patterns

TEST_F(RemoveDuplicatesFromSortedListTest, DoubleDuplicates) {
    // Each number appears exactly twice
    testAllApproaches({1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, {1, 2, 3, 4, 5});
}

TEST_F(RemoveDuplicatesFromSortedListTest, TripleDuplicates) {
    // Each number appears exactly three times
    testAllApproaches({2, 2, 2, 4, 4, 4, 6, 6, 6}, {2, 4, 6});
}

TEST_F(RemoveDuplicatesFromSortedListTest, VaryingDuplicateCounts) {
    // Different numbers have different duplicate counts
    testAllApproaches({1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5}, {1, 2, 3, 4, 5});
}

TEST_F(RemoveDuplicatesFromSortedListTest, LargeDuplicateGroups) {
    // Large groups of identical numbers
    testAllApproaches({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3}, {1, 2, 3});
}

// Memory and Performance Tests

TEST_F(RemoveDuplicatesFromSortedListTest, MaxConstraintSize) {
    // Test with maximum constraint size (300 nodes)
    std::vector<int> input, expected;
    // Create 300 nodes with pattern: each value from 1-100 appears 3 times
    for (int i = 1; i <= 100; ++i) {
        input.push_back(i);
        input.push_back(i);
        input.push_back(i);
        expected.push_back(i);
    }
    testAllApproaches(input, expected);
}

TEST_F(RemoveDuplicatesFromSortedListTest, SingleValueRepeated) {
    // Single value repeated many times
    std::vector<int> input(50, 42);  // 50 nodes all with value 42
    std::vector<int> expected = {42};
    testAllApproaches(input, expected);
}

// Edge Case Combinations

TEST_F(RemoveDuplicatesFromSortedListTest, StartAndEndDuplicates) {
    // Duplicates at both start and end
    testAllApproaches({1, 1, 1, 2, 3, 4, 5, 5, 5}, {1, 2, 3, 4, 5});
}

TEST_F(RemoveDuplicatesFromSortedListTest, OnlyMiddleUnique) {
    // Only middle element is unique
    testAllApproaches({1, 1, 1, 2, 3, 3, 3}, {1, 2, 3});
}

TEST_F(RemoveDuplicatesFromSortedListTest, AlternatingDuplicatesAndSingles) {
    // Alternating pattern of duplicates and singles
    testAllApproaches({1, 2, 2, 3, 4, 4, 5, 6, 6}, {1, 2, 3, 4, 5, 6});
}

// Special Numerical Patterns

TEST_F(RemoveDuplicatesFromSortedListTest, EvenNumbersOnly) {
    // Only even numbers with duplicates
    testAllApproaches({2, 2, 4, 6, 6, 8, 10, 10}, {2, 4, 6, 8, 10});
}

TEST_F(RemoveDuplicatesFromSortedListTest, OddNumbersOnly) {
    // Only odd numbers with duplicates
    testAllApproaches({1, 1, 3, 5, 5, 7, 9, 9}, {1, 3, 5, 7, 9});
}

TEST_F(RemoveDuplicatesFromSortedListTest, FibonacciSequence) {
    // Fibonacci-like sequence with duplicates
    testAllApproaches({1, 1, 1, 2, 2, 3, 3, 5, 5, 8, 8}, {1, 2, 3, 5, 8});
}

TEST_F(RemoveDuplicatesFromSortedListTest, PowersOfTwo) {
    // Powers of 2 with duplicates
    testAllApproaches({1, 2, 2, 4, 4, 8, 8, 16, 16}, {1, 2, 4, 8, 16});
}

// Stress Tests

TEST_F(RemoveDuplicatesFromSortedListTest, MostlyDuplicates) {
    // List where most elements are duplicates
    testAllApproaches({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {1, 2, 3});
}

TEST_F(RemoveDuplicatesFromSortedListTest, WorstCaseScenario) {
    // Worst case: all elements the same except last one
    std::vector<int> input(99, 5);
    input.push_back(6);
    std::vector<int> expected = {5, 6};
    testAllApproaches(input, expected);
}

TEST_F(RemoveDuplicatesFromSortedListTest, BestCaseScenario) {
    // Best case: no duplicates at all
    std::vector<int> input, expected;
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i);
        expected.push_back(i);
    }
    testAllApproaches(input, expected);
}

// Memory Management Verification

TEST_F(RemoveDuplicatesFromSortedListTest, MemoryHandling) {
    // Test that memory is properly managed across multiple operations
    RemoveDuplicatesFromSortedList solution;
    
    for (int test = 0; test < 10; ++test) {
        ListNode* list = solution.createList({1, 1, 2, 2, 3, 3});
        ListNode* result = solution.deleteDuplicatesIterative(list);
        std::vector<int> output = solution.listToVector(result);
        
        EXPECT_EQ(output, std::vector<int>({1, 2, 3}));
        solution.deleteList(result);
    }
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode