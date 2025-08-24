#include <gtest/gtest.h>
#include "../../src/easy/delete_node_in_linked_list.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class DeleteNodeInLinkedListTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(const std::vector<int>& input, int valueToDelete, const std::vector<int>& expected) {
        DeleteNodeInLinkedList solution;
        
        // Test each approach
        for (int approach = 0; approach < 6; ++approach) {
            ListNode* list = solution.createList(input);
            ListNode* nodeToDelete = solution.findNode(list, valueToDelete);
            
            ASSERT_NE(nodeToDelete, nullptr) 
                << "Could not find node with value " << valueToDelete << " in list " << vectorToString(input);
            
            switch (approach) {
                case 0:
                    solution.deleteNodeCopyNext(nodeToDelete);
                    break;
                case 1:
                    solution.deleteNodeShiftValues(nodeToDelete);
                    break;
                case 2:
                    solution.deleteNodeMarkAndCompact(nodeToDelete);
                    break;
                case 3:
                    solution.deleteNodeRecursive(nodeToDelete);
                    break;
                case 4:
                    solution.deleteNodeTwoPointers(nodeToDelete);
                    break;
                case 5:
                    solution.deleteNodeFunctional(nodeToDelete);
                    break;
            }
            
            std::vector<int> result = solution.listToVector(list);
            
            std::vector<std::string> approachNames = {
                "Copy Next", "Shift Values", "Mark and Compact", 
                "Recursive", "Two Pointers", "Functional"
            };
            
            EXPECT_EQ(result, expected) 
                << approachNames[approach] << " approach failed for input: " << vectorToString(input)
                << ", deleting value: " << valueToDelete
                << ", expected: " << vectorToString(expected)
                << ", got: " << vectorToString(result);
            
            // Clean up
            solution.deleteList(list);
        }
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

TEST_F(DeleteNodeInLinkedListTest, LeetCodeExample1) {
    // Input: head = [4,5,1,9], node = 5
    // Output: [4,1,9]
    testAllApproaches({4, 5, 1, 9}, 5, {4, 1, 9});
}

TEST_F(DeleteNodeInLinkedListTest, LeetCodeExample2) {
    // Input: head = [4,5,1,9], node = 1
    // Output: [4,5,9]
    testAllApproaches({4, 5, 1, 9}, 1, {4, 5, 9});
}

// Two Element Lists (Minimum Constraint)

TEST_F(DeleteNodeInLinkedListTest, TwoElementsDeleteFirst) {
    // Delete first element from two-element list
    testAllApproaches({1, 2}, 1, {2});
}

TEST_F(DeleteNodeInLinkedListTest, TwoElementsDeleteSecond) {
    // Delete second element - this violates constraint (can't delete tail)
    // but we'll test it for robustness, expecting no change or graceful handling
    // Actually, let's skip this since it violates the problem constraints
}

TEST_F(DeleteNodeInLinkedListTest, TwoElementsNegativeValues) {
    // Two elements with negative values
    testAllApproaches({-5, 3}, -5, {3});
}

TEST_F(DeleteNodeInLinkedListTest, TwoElementsZeroAndPositive) {
    // Zero and positive value
    testAllApproaches({0, 7}, 0, {7});
}

// Three Element Lists

TEST_F(DeleteNodeInLinkedListTest, ThreeElementsDeleteFirst) {
    // Delete first element
    testAllApproaches({1, 2, 3}, 1, {2, 3});
}

TEST_F(DeleteNodeInLinkedListTest, ThreeElementsDeleteMiddle) {
    // Delete middle element
    testAllApproaches({1, 2, 3}, 2, {1, 3});
}

TEST_F(DeleteNodeInLinkedListTest, ThreeElementsWithNegatives) {
    // Three elements with negative values
    testAllApproaches({-10, -5, 15}, -5, {-10, 15});
}

TEST_F(DeleteNodeInLinkedListTest, ThreeElementsWithZero) {
    // Three elements including zero
    testAllApproaches({5, 0, -3}, 0, {5, -3});
}

// Four Element Lists

TEST_F(DeleteNodeInLinkedListTest, FourElementsDeleteFirst) {
    // Delete first element
    testAllApproaches({10, 20, 30, 40}, 10, {20, 30, 40});
}

TEST_F(DeleteNodeInLinkedListTest, FourElementsDeleteSecond) {
    // Delete second element
    testAllApproaches({10, 20, 30, 40}, 20, {10, 30, 40});
}

TEST_F(DeleteNodeInLinkedListTest, FourElementsDeleteThird) {
    // Delete third element
    testAllApproaches({10, 20, 30, 40}, 30, {10, 20, 40});
}

TEST_F(DeleteNodeInLinkedListTest, FourElementsAllNegative) {
    // All negative values
    testAllApproaches({-1, -2, -3, -4}, -2, {-1, -3, -4});
}

// Larger Lists

TEST_F(DeleteNodeInLinkedListTest, FiveElementsDeleteFirst) {
    // Five elements, delete first
    testAllApproaches({100, 200, 300, 400, 500}, 100, {200, 300, 400, 500});
}

TEST_F(DeleteNodeInLinkedListTest, FiveElementsDeleteMiddle) {
    // Five elements, delete middle
    testAllApproaches({100, 200, 300, 400, 500}, 300, {100, 200, 400, 500});
}

TEST_F(DeleteNodeInLinkedListTest, SixElementsDeleteSecond) {
    // Six elements, delete second
    testAllApproaches({1, 2, 3, 4, 5, 6}, 2, {1, 3, 4, 5, 6});
}

TEST_F(DeleteNodeInLinkedListTest, SevenElementsDeleteFourth) {
    // Seven elements, delete fourth
    testAllApproaches({7, 14, 21, 28, 35, 42, 49}, 28, {7, 14, 21, 35, 42, 49});
}

// Edge Value Tests

TEST_F(DeleteNodeInLinkedListTest, MinimumValues) {
    // Test with minimum constraint values
    testAllApproaches({-1000, -999, -998}, -1000, {-999, -998});
}

TEST_F(DeleteNodeInLinkedListTest, MaximumValues) {
    // Test with maximum constraint values
    testAllApproaches({998, 999, 1000}, 999, {998, 1000});
}

TEST_F(DeleteNodeInLinkedListTest, MixedExtremeValues) {
    // Mix of minimum and maximum values
    testAllApproaches({-1000, 0, 1000}, 0, {-1000, 1000});
}

TEST_F(DeleteNodeInLinkedListTest, AllZeros) {
    // Multiple zeros (but they should be unique per constraints)
    // This violates uniqueness constraint, so let's use unique values around zero
    testAllApproaches({-1, 0, 1}, 0, {-1, 1});
}

// Sequential Pattern Tests

TEST_F(DeleteNodeInLinkedListTest, AscendingSequence) {
    // Ascending sequence
    testAllApproaches({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5, {1, 2, 3, 4, 6, 7, 8, 9, 10});
}

TEST_F(DeleteNodeInLinkedListTest, DescendingSequence) {
    // Descending sequence
    testAllApproaches({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 7, {10, 9, 8, 6, 5, 4, 3, 2, 1});
}

TEST_F(DeleteNodeInLinkedListTest, EvenNumbers) {
    // Even numbers sequence
    testAllApproaches({2, 4, 6, 8, 10, 12}, 6, {2, 4, 8, 10, 12});
}

TEST_F(DeleteNodeInLinkedListTest, OddNumbers) {
    // Odd numbers sequence
    testAllApproaches({1, 3, 5, 7, 9, 11}, 7, {1, 3, 5, 9, 11});
}

// Random Pattern Tests

TEST_F(DeleteNodeInLinkedListTest, RandomPattern1) {
    // Random pattern 1
    testAllApproaches({42, -17, 88, 3, -99, 56}, -17, {42, 88, 3, -99, 56});
}

TEST_F(DeleteNodeInLinkedListTest, RandomPattern2) {
    // Random pattern 2
    testAllApproaches({100, -50, 25, -12, 75, -37}, 25, {100, -50, -12, 75, -37});
}

TEST_F(DeleteNodeInLinkedListTest, PrimeNumbers) {
    // Prime numbers
    testAllApproaches({2, 3, 5, 7, 11, 13, 17}, 7, {2, 3, 5, 11, 13, 17});
}

TEST_F(DeleteNodeInLinkedListTest, PowersOfTwo) {
    // Powers of 2
    testAllApproaches({1, 2, 4, 8, 16, 32, 64}, 8, {1, 2, 4, 16, 32, 64});
}

// Specific Position Tests

TEST_F(DeleteNodeInLinkedListTest, DeleteSecondFromLongList) {
    // Delete second element from longer list
    std::vector<int> input = {15, 25, 35, 45, 55, 65, 75, 85, 95};
    testAllApproaches(input, 25, {15, 35, 45, 55, 65, 75, 85, 95});
}

TEST_F(DeleteNodeInLinkedListTest, DeleteThirdFromLongList) {
    // Delete third element from longer list
    std::vector<int> input = {15, 25, 35, 45, 55, 65, 75, 85, 95};
    testAllApproaches(input, 35, {15, 25, 45, 55, 65, 75, 85, 95});
}

TEST_F(DeleteNodeInLinkedListTest, DeleteFourthFromLongList) {
    // Delete fourth element from longer list
    std::vector<int> input = {15, 25, 35, 45, 55, 65, 75, 85, 95};
    testAllApproaches(input, 45, {15, 25, 35, 55, 65, 75, 85, 95});
}

// Large List Tests

TEST_F(DeleteNodeInLinkedListTest, LargeListDeleteFirst) {
    // Large list, delete first element
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i);
        if (i != 1) expected.push_back(i);
    }
    
    testAllApproaches(input, 1, expected);
}

TEST_F(DeleteNodeInLinkedListTest, LargeListDeleteMiddle) {
    // Large list, delete middle element
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i);
        if (i != 25) expected.push_back(i);
    }
    
    testAllApproaches(input, 25, expected);
}

TEST_F(DeleteNodeInLinkedListTest, LargeListDeleteNearEnd) {
    // Large list, delete near end (but not last)
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i);
        if (i != 48) expected.push_back(i);
    }
    
    testAllApproaches(input, 48, expected);
}

// Boundary Constraint Tests

TEST_F(DeleteNodeInLinkedListTest, MinimumListSize) {
    // Minimum list size (2 elements)
    testAllApproaches({-500, 500}, -500, {500});
}

TEST_F(DeleteNodeInLinkedListTest, NearMaximumListSize) {
    // Test with larger list (subset of 1000 for performance)
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 0; i < 100; ++i) {
        input.push_back(i);
        if (i != 50) expected.push_back(i);
    }
    
    testAllApproaches(input, 50, expected);
}

// Negative Number Tests

TEST_F(DeleteNodeInLinkedListTest, AllNegativeNumbers) {
    // All negative numbers
    testAllApproaches({-100, -75, -50, -25, -10}, -50, {-100, -75, -25, -10});
}

TEST_F(DeleteNodeInLinkedListTest, NegativeAndPositiveMix) {
    // Mix of negative and positive
    testAllApproaches({-30, -15, 0, 15, 30, 45}, 15, {-30, -15, 0, 30, 45});
}

TEST_F(DeleteNodeInLinkedListTest, AroundZero) {
    // Numbers around zero
    testAllApproaches({-3, -2, -1, 1, 2, 3}, -1, {-3, -2, 1, 2, 3});
}

// Mathematical Pattern Tests

TEST_F(DeleteNodeInLinkedListTest, FibonacciSequence) {
    // Fibonacci-like sequence
    testAllApproaches({1, 1, 2, 3, 5, 8, 13}, 3, {1, 1, 2, 5, 8, 13});
}

TEST_F(DeleteNodeInLinkedListTest, SquareNumbers) {
    // Square numbers
    testAllApproaches({1, 4, 9, 16, 25, 36}, 16, {1, 4, 9, 25, 36});
}

TEST_F(DeleteNodeInLinkedListTest, TriangleNumbers) {
    // Triangle numbers
    testAllApproaches({1, 3, 6, 10, 15, 21}, 10, {1, 3, 6, 15, 21});
}

// Complex Patterns

TEST_F(DeleteNodeInLinkedListTest, AlternatingSignPattern) {
    // Alternating positive/negative pattern
    testAllApproaches({5, -10, 15, -20, 25, -30}, -20, {5, -10, 15, 25, -30});
}

TEST_F(DeleteNodeInLinkedListTest, GeometricProgression) {
    // Geometric progression
    testAllApproaches({2, 6, 18, 54, 162}, 18, {2, 6, 54, 162});
}

TEST_F(DeleteNodeInLinkedListTest, ArithmeticProgression) {
    // Arithmetic progression
    testAllApproaches({7, 14, 21, 28, 35, 42}, 21, {7, 14, 28, 35, 42});
}

// Edge Cases for Specific Approaches

TEST_F(DeleteNodeInLinkedListTest, RecursiveApproachDeepList) {
    // Test recursive approach with moderate depth
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 0; i < 50; ++i) {
        input.push_back(i);
        if (i != 10) expected.push_back(i);
    }
    
    testAllApproaches(input, 10, expected);
}

TEST_F(DeleteNodeInLinkedListTest, TwoPointersEdgeCase) {
    // Test two pointers with specific pattern
    testAllApproaches({-999, -500, 0, 500, 999}, 0, {-999, -500, 500, 999});
}

TEST_F(DeleteNodeInLinkedListTest, MarkAndCompactEdgeCase) {
    // Test mark and compact with values near sentinel
    testAllApproaches({-1000, -999, -1, 0, 1}, -999, {-1000, -1, 0, 1});
}

// Performance Tests

TEST_F(DeleteNodeInLinkedListTest, LargeSequentialList) {
    // Large sequential list
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 100; i < 200; ++i) {
        input.push_back(i);
        if (i != 150) expected.push_back(i);
    }
    
    testAllApproaches(input, 150, expected);
}

// Memory Management Tests

TEST_F(DeleteNodeInLinkedListTest, MultipleOperations) {
    // Test multiple operations for memory leak detection
    for (int i = 0; i < 10; ++i) {
        testAllApproaches({1, 2, 3, 4, 5}, 3, {1, 2, 4, 5});
        testAllApproaches({10, 20, 30}, 20, {10, 30});
    }
}

// Comprehensive Edge Case

TEST_F(DeleteNodeInLinkedListTest, ComprehensiveEdgeCase) {
    // Various patterns in one test
    testAllApproaches({-1000, -1}, -1000, {-1});  // Minimum values
    testAllApproaches({999, 1000}, 999, {1000});  // Maximum values
    testAllApproaches({-1, 0, 1}, 0, {-1, 1});    // Around zero
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode