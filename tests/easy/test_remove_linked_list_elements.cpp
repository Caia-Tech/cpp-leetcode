#include <gtest/gtest.h>
#include "../../src/easy/remove_linked_list_elements.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class RemoveLinkedListElementsTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(const std::vector<int>& input, int val, const std::vector<int>& expected) {
        RemoveLinkedListElements solution;
        
        // Test each approach
        for (int approach = 0; approach < 6; ++approach) {
            ListNode* list = solution.createList(input);
            ListNode* result = nullptr;
            
            switch (approach) {
                case 0:
                    result = solution.removeElementsIterativeDummy(list, val);
                    break;
                case 1:
                    result = solution.removeElementsIterativeNoDummy(list, val);
                    break;
                case 2:
                    result = solution.removeElementsRecursive(list, val);
                    break;
                case 3:
                    result = solution.removeElementsStack(list, val);
                    break;
                case 4:
                    result = solution.removeElementsTwoPass(list, val);
                    break;
                case 5:
                    result = solution.removeElementsFunctional(list, val);
                    break;
            }
            
            std::vector<int> output = solution.listToVector(result);
            
            std::vector<std::string> approachNames = {
                "Iterative Dummy", "Iterative No Dummy", "Recursive", 
                "Stack", "Two Pass", "Functional"
            };
            
            EXPECT_EQ(output, expected) 
                << approachNames[approach] << " approach failed for input: " << vectorToString(input)
                << ", val: " << val << ", expected: " << vectorToString(expected)
                << ", got: " << vectorToString(output);
            
            // Clean up
            solution.deleteList(result);
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

TEST_F(RemoveLinkedListElementsTest, LeetCodeExample1) {
    // Input: head = [1,2,6,3,4,5,6], val = 6
    // Output: [1,2,3,4,5]
    testAllApproaches({1, 2, 6, 3, 4, 5, 6}, 6, {1, 2, 3, 4, 5});
}

TEST_F(RemoveLinkedListElementsTest, LeetCodeExample2) {
    // Input: head = [], val = 1
    // Output: []
    testAllApproaches({}, 1, {});
}

TEST_F(RemoveLinkedListElementsTest, LeetCodeExample3) {
    // Input: head = [7,7,7,7], val = 7
    // Output: []
    testAllApproaches({7, 7, 7, 7}, 7, {});
}

// Edge Cases

TEST_F(RemoveLinkedListElementsTest, EmptyList) {
    // Empty list with any value
    testAllApproaches({}, 5, {});
}

TEST_F(RemoveLinkedListElementsTest, SingleElementRemove) {
    // Single element that should be removed
    testAllApproaches({5}, 5, {});
}

TEST_F(RemoveLinkedListElementsTest, SingleElementKeep) {
    // Single element that should be kept
    testAllApproaches({3}, 5, {3});
}

TEST_F(RemoveLinkedListElementsTest, TwoElementsBothRemove) {
    // Two elements, both should be removed
    testAllApproaches({7, 7}, 7, {});
}

TEST_F(RemoveLinkedListElementsTest, TwoElementsBothKeep) {
    // Two elements, both should be kept
    testAllApproaches({1, 2}, 5, {1, 2});
}

TEST_F(RemoveLinkedListElementsTest, TwoElementsFirstRemove) {
    // Two elements, first should be removed
    testAllApproaches({5, 3}, 5, {3});
}

TEST_F(RemoveLinkedListElementsTest, TwoElementsSecondRemove) {
    // Two elements, second should be removed
    testAllApproaches({3, 5}, 5, {3});
}

// Head Removal Cases

TEST_F(RemoveLinkedListElementsTest, RemoveHead) {
    // Remove only the head
    testAllApproaches({5, 1, 2, 3}, 5, {1, 2, 3});
}

TEST_F(RemoveLinkedListElementsTest, RemoveMultipleHeads) {
    // Remove multiple consecutive head nodes
    testAllApproaches({5, 5, 5, 1, 2, 3}, 5, {1, 2, 3});
}

TEST_F(RemoveLinkedListElementsTest, RemoveAllHeads) {
    // Remove all nodes starting from head
    testAllApproaches({5, 5, 5, 5}, 5, {});
}

// Tail Removal Cases

TEST_F(RemoveLinkedListElementsTest, RemoveTail) {
    // Remove only the tail
    testAllApproaches({1, 2, 3, 5}, 5, {1, 2, 3});
}

TEST_F(RemoveLinkedListElementsTest, RemoveMultipleTails) {
    // Remove multiple consecutive tail nodes
    testAllApproaches({1, 2, 3, 5, 5, 5}, 5, {1, 2, 3});
}

// Middle Removal Cases

TEST_F(RemoveLinkedListElementsTest, RemoveMiddle) {
    // Remove only middle elements
    testAllApproaches({1, 5, 2}, 5, {1, 2});
}

TEST_F(RemoveLinkedListElementsTest, RemoveMultipleMiddle) {
    // Remove multiple middle elements
    testAllApproaches({1, 5, 5, 5, 2}, 5, {1, 2});
}

TEST_F(RemoveLinkedListElementsTest, RemoveScattered) {
    // Remove scattered elements throughout list
    testAllApproaches({5, 1, 5, 2, 5, 3, 5}, 5, {1, 2, 3});
}

// Value Range Tests

TEST_F(RemoveLinkedListElementsTest, RemoveMinimumValue) {
    // Remove minimum constraint value (1)
    testAllApproaches({1, 2, 3, 1, 4}, 1, {2, 3, 4});
}

TEST_F(RemoveLinkedListElementsTest, RemoveMaximumValue) {
    // Remove maximum constraint value (50)
    testAllApproaches({50, 25, 50, 10, 50}, 50, {25, 10});
}

TEST_F(RemoveLinkedListElementsTest, RemoveZero) {
    // Remove zero (minimum val constraint)
    testAllApproaches({0, 1, 0, 2, 0}, 0, {1, 2});
}

// Pattern-based Tests

TEST_F(RemoveLinkedListElementsTest, AlternatingPattern) {
    // Alternating pattern of target and non-target values
    testAllApproaches({1, 5, 1, 5, 1, 5}, 5, {1, 1, 1});
}

TEST_F(RemoveLinkedListElementsTest, ConsecutiveTargets) {
    // Multiple consecutive target values
    testAllApproaches({1, 2, 5, 5, 5, 3, 4}, 5, {1, 2, 3, 4});
}

TEST_F(RemoveLinkedListElementsTest, NoMatches) {
    // No elements match target value
    testAllApproaches({1, 2, 3, 4, 6, 7, 8}, 5, {1, 2, 3, 4, 6, 7, 8});
}

TEST_F(RemoveLinkedListElementsTest, AllMatches) {
    // All elements match target value
    testAllApproaches({3, 3, 3, 3, 3}, 3, {});
}

// Larger Lists

TEST_F(RemoveLinkedListElementsTest, LargeListRemoveSpecificValue) {
    // Large list, remove specific value
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 1; i <= 20; ++i) {
        input.push_back(i);
        if (i != 10) {  // Remove value 10
            expected.push_back(i);
        }
    }
    
    testAllApproaches(input, 10, expected);
}

TEST_F(RemoveLinkedListElementsTest, LargeListRemoveSpecific) {
    // Large list, remove specific value
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 1; i <= 100; ++i) {
        input.push_back(i % 10);  // Values 0-9 repeating
        if (i % 10 != 5) {        // Remove all 5's
            expected.push_back(i % 10);
        }
    }
    
    testAllApproaches(input, 5, expected);
}

// Boundary Value Tests

TEST_F(RemoveLinkedListElementsTest, MaxConstraintSize) {
    // Test with larger list (subset of maximum 10^4 for test speed)
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 0; i < 1000; ++i) {
        int val = (i % 5) + 1;  // Values 1-5
        input.push_back(val);
        if (val != 3) {  // Remove all 3's
            expected.push_back(val);
        }
    }
    
    testAllApproaches(input, 3, expected);
}

TEST_F(RemoveLinkedListElementsTest, AllConstraintValues) {
    // Test with all possible node values (1-50)
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i);
        if (i != 25) {  // Remove value 25
            expected.push_back(i);
        }
    }
    
    testAllApproaches(input, 25, expected);
}

// Duplicate Value Tests

TEST_F(RemoveLinkedListElementsTest, DuplicateValuesKeepSome) {
    // List with duplicates, remove some but not all
    testAllApproaches({1, 2, 2, 3, 2, 4, 2}, 2, {1, 3, 4});
}

TEST_F(RemoveLinkedListElementsTest, DuplicateValuesKeepAll) {
    // List with duplicates, remove none
    testAllApproaches({1, 2, 2, 3, 2, 4, 2}, 5, {1, 2, 2, 3, 2, 4, 2});
}

TEST_F(RemoveLinkedListElementsTest, OnlyDuplicates) {
    // List contains only duplicate values
    testAllApproaches({7, 7, 7, 7, 7, 7, 7}, 7, {});
}

// Complex Patterns

TEST_F(RemoveLinkedListElementsTest, NestedPattern) {
    // Nested pattern with target values
    testAllApproaches({1, 5, 2, 5, 5, 3, 5, 4, 5, 5, 5}, 5, {1, 2, 3, 4});
}

TEST_F(RemoveLinkedListElementsTest, MirrorPattern) {
    // Mirror pattern where target appears symmetrically
    testAllApproaches({1, 2, 5, 3, 5, 2, 1}, 5, {1, 2, 3, 2, 1});
}

TEST_F(RemoveLinkedListElementsTest, FibonacciWithTarget) {
    // Fibonacci-like sequence with target values
    testAllApproaches({1, 1, 2, 3, 5, 8, 5, 13, 5}, 5, {1, 1, 2, 3, 8, 13});
}

// Performance Tests

TEST_F(RemoveLinkedListElementsTest, RemoveFirstHalf) {
    // Remove first half of elements
    std::vector<int> input = {3, 3, 3, 3, 3, 1, 2, 4, 5, 6};
    testAllApproaches(input, 3, {1, 2, 4, 5, 6});
}

TEST_F(RemoveLinkedListElementsTest, RemoveSecondHalf) {
    // Remove second half of elements  
    std::vector<int> input = {1, 2, 4, 5, 6, 3, 3, 3, 3, 3};
    testAllApproaches(input, 3, {1, 2, 4, 5, 6});
}

TEST_F(RemoveLinkedListElementsTest, RemoveAlternatingGroups) {
    // Remove alternating groups of elements
    testAllApproaches({1, 5, 5, 2, 3, 5, 5, 4}, 5, {1, 2, 3, 4});
}

// Memory Management Tests

TEST_F(RemoveLinkedListElementsTest, MultipleOperations) {
    // Test multiple operations for memory leak detection
    for (int i = 0; i < 10; ++i) {
        testAllApproaches({1, 2, 3, 4, 5}, 3, {1, 2, 4, 5});
        testAllApproaches({5, 5, 5, 5}, 5, {});
        testAllApproaches({1, 2, 3, 4}, 6, {1, 2, 3, 4});
    }
}

// Special Algorithm Tests

TEST_F(RemoveLinkedListElementsTest, RecursiveDeepList) {
    // Test recursive approach with moderately deep list
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 0; i < 100; ++i) {
        input.push_back(i % 3);  // Values 0, 1, 2 repeating
        if (i % 3 != 1) {       // Remove all 1's
            expected.push_back(i % 3);
        }
    }
    
    testAllApproaches(input, 1, expected);
}

TEST_F(RemoveLinkedListElementsTest, StackApproachTest) {
    // Test stack approach with specific pattern
    testAllApproaches({1, 5, 2, 5, 3, 5, 4}, 5, {1, 2, 3, 4});
}

TEST_F(RemoveLinkedListElementsTest, TwoPassConsistency) {
    // Test two-pass approach consistency
    testAllApproaches({10, 20, 10, 30, 10, 40}, 10, {20, 30, 40});
}

// Edge Cases for Specific Approaches

TEST_F(RemoveLinkedListElementsTest, NoDummyHeadEdgeCase) {
    // Test case that challenges no-dummy approach
    testAllApproaches({5, 5, 1, 5, 5}, 5, {1});
}

TEST_F(RemoveLinkedListElementsTest, FunctionalFilterTest) {
    // Test functional approach with various filters
    testAllApproaches({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5, {1, 2, 3, 4, 6, 7, 8, 9, 10});
}

// Comprehensive Edge Case
TEST_F(RemoveLinkedListElementsTest, ComprehensiveEdgeCase) {
    // Single node that should be kept with different target
    testAllApproaches({42}, 13, {42});
    
    // Single node that should be removed
    testAllApproaches({13}, 13, {});
    
    // Two identical nodes with different target
    testAllApproaches({7, 7}, 3, {7, 7});
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode