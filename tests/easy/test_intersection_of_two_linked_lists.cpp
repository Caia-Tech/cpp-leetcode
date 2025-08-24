#include <gtest/gtest.h>
#include "../../src/easy/intersection_of_two_linked_lists.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class IntersectionOfTwoLinkedListsTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(const std::vector<int>& listA, 
                          const std::vector<int>& listB,
                          const std::vector<int>& intersection,
                          bool expectIntersection) {
        IntersectionOfTwoLinkedLists solution;
        
        // Create intersected lists for each approach
        for (int approach = 0; approach < 6; ++approach) {
            ListNode* headA = nullptr;
            ListNode* headB = nullptr;
            ListNode* intersectionNode = solution.createIntersectedLists(listA, listB, intersection, headA, headB);
            
            ListNode* result = nullptr;
            
            switch (approach) {
                case 0:
                    result = solution.getIntersectionNodeTwoPointers(headA, headB);
                    break;
                case 1:
                    result = solution.getIntersectionNodeHashSet(headA, headB);
                    break;
                case 2:
                    result = solution.getIntersectionNodeCleverTwoPointers(headA, headB);
                    break;
                case 3:
                    result = solution.getIntersectionNodeStack(headA, headB);
                    break;
                case 4:
                    result = solution.getIntersectionNodeMarkAndRestore(headA, headB);
                    break;
                case 5:
                    result = solution.getIntersectionNodeFunctional(headA, headB);
                    break;
            }
            
            std::vector<std::string> approachNames = {
                "Two Pointers", "Hash Set", "Clever Two Pointers", 
                "Stack", "Mark and Restore", "Functional"
            };
            
            if (expectIntersection) {
                EXPECT_EQ(result, intersectionNode) 
                    << approachNames[approach] << " approach failed: should find intersection for lists A=" 
                    << vectorToString(listA) << ", B=" << vectorToString(listB) 
                    << ", intersection=" << vectorToString(intersection);
                
                if (result && !intersection.empty()) {
                    EXPECT_EQ(result->val, intersection[0])
                        << approachNames[approach] << " approach failed: intersection node value mismatch";
                }
            } else {
                EXPECT_EQ(result, nullptr) 
                    << approachNames[approach] << " approach failed: should not find intersection for lists A=" 
                    << vectorToString(listA) << ", B=" << vectorToString(listB);
            }
            
            // Clean up
            solution.deleteIntersectedLists(headA, headB, intersectionNode);
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

TEST_F(IntersectionOfTwoLinkedListsTest, LeetCodeExample1) {
    // Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
    // Output: Intersected at '8'
    testAllApproaches({4, 1}, {5, 6, 1}, {8, 4, 5}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, LeetCodeExample2) {
    // Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
    // Output: Intersected at '2'
    testAllApproaches({1, 9, 1}, {3}, {2, 4}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, LeetCodeExample3) {
    // Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
    // Output: No intersection
    testAllApproaches({2, 6, 4}, {1, 5}, {}, false);
}

// Edge Cases

TEST_F(IntersectionOfTwoLinkedListsTest, BothListsEmpty) {
    // Both lists empty
    testAllApproaches({}, {}, {}, false);
}

TEST_F(IntersectionOfTwoLinkedListsTest, OneListEmpty) {
    // One list empty, other non-empty
    testAllApproaches({}, {1, 2, 3}, {}, false);
    testAllApproaches({1, 2, 3}, {}, {}, false);
}

TEST_F(IntersectionOfTwoLinkedListsTest, SingleNodeBothLists) {
    // Both lists have single node, same node (intersection)
    testAllApproaches({}, {}, {5}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, SingleNodeBothListsDifferent) {
    // Both lists have single node, different nodes
    testAllApproaches({3}, {7}, {}, false);
}

TEST_F(IntersectionOfTwoLinkedListsTest, SingleNodeIntersection) {
    // Lists with single node intersection
    testAllApproaches({1, 2}, {3, 4}, {5}, true);
}

// Same Length Lists

TEST_F(IntersectionOfTwoLinkedListsTest, SameLengthWithIntersection) {
    // Same length lists with intersection
    testAllApproaches({1, 2}, {3, 4}, {5, 6}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, SameLengthNoIntersection) {
    // Same length lists without intersection
    testAllApproaches({1, 2, 3}, {4, 5, 6}, {}, false);
}

TEST_F(IntersectionOfTwoLinkedListsTest, SameLengthIntersectionAtStart) {
    // Intersection starts immediately (no unique parts)
    testAllApproaches({}, {}, {1, 2, 3}, true);
}

// Different Length Lists

TEST_F(IntersectionOfTwoLinkedListsTest, FirstListLonger) {
    // First list longer than second
    testAllApproaches({1, 2, 3, 4, 5}, {6, 7}, {8, 9}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, SecondListLonger) {
    // Second list longer than first
    testAllApproaches({1, 2}, {3, 4, 5, 6, 7}, {8, 9}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, VeryDifferentLengths) {
    // Very different lengths
    testAllApproaches({1}, {2, 3, 4, 5, 6, 7, 8, 9, 10}, {11}, true);
}

// Intersection Position Tests

TEST_F(IntersectionOfTwoLinkedListsTest, IntersectionAtBeginning) {
    // Intersection starts immediately for both lists
    testAllApproaches({}, {}, {1, 2, 3, 4}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, IntersectionAtEnd) {
    // Intersection is just the last node
    testAllApproaches({1, 2, 3}, {4, 5, 6}, {7}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, IntersectionInMiddle) {
    // Intersection in the middle of both lists
    testAllApproaches({1, 2}, {3, 4, 5}, {6, 7, 8}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, LongIntersection) {
    // Long intersection part
    testAllApproaches({1}, {2}, {3, 4, 5, 6, 7, 8, 9, 10}, true);
}

// Special Value Tests

TEST_F(IntersectionOfTwoLinkedListsTest, NegativeValues) {
    // Lists with negative values
    testAllApproaches({-1, -2}, {-3, -4}, {-5, -6}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, ZeroValues) {
    // Lists with zero values
    testAllApproaches({0, 1}, {2, 0}, {0, 3}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, MixedValues) {
    // Mix of negative, zero, and positive values
    testAllApproaches({-5, 0}, {10, -1}, {0, 7, -3}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, LargeValues) {
    // Large values within constraint
    testAllApproaches({99999, 50000}, {75000, 25000}, {100000}, true);
}

// Duplicate Values (Different Nodes)

TEST_F(IntersectionOfTwoLinkedListsTest, DuplicateValuesNoIntersection) {
    // Same values but different nodes (no intersection)
    testAllApproaches({1, 2, 3}, {1, 2, 3}, {}, false);
}

TEST_F(IntersectionOfTwoLinkedListsTest, DuplicateValuesWithIntersection) {
    // Same values in unique parts, but real intersection
    testAllApproaches({5, 5}, {5, 5}, {5, 5}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, RepeatingValuesInIntersection) {
    // Repeating values in intersection part
    testAllApproaches({1, 2}, {3, 4}, {7, 7, 7, 7}, true);
}

// Performance and Stress Tests

TEST_F(IntersectionOfTwoLinkedListsTest, LargeLists) {
    // Large lists within constraint
    std::vector<int> largeA, largeB, intersection;
    
    // Create large unique parts
    for (int i = 1; i <= 1000; ++i) {
        largeA.push_back(i);
    }
    
    for (int i = 2001; i <= 3000; ++i) {
        largeB.push_back(i);
    }
    
    // Small intersection
    intersection = {5001, 5002, 5003};
    
    testAllApproaches(largeA, largeB, intersection, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, VeryLongIntersection) {
    // Short unique parts, very long intersection
    std::vector<int> intersection;
    for (int i = 1; i <= 1000; ++i) {
        intersection.push_back(i);
    }
    
    testAllApproaches({-1}, {-2}, intersection, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, OneVeryLongOneShort) {
    // One very long list, one very short
    std::vector<int> longList;
    for (int i = 1; i <= 2000; ++i) {
        longList.push_back(i);
    }
    
    testAllApproaches(longList, {9999}, {10000}, true);
}

// Boundary Constraint Tests

TEST_F(IntersectionOfTwoLinkedListsTest, MinimumConstraints) {
    // Minimum constraint values
    testAllApproaches({}, {}, {1}, true);  // Minimum node value
}

TEST_F(IntersectionOfTwoLinkedListsTest, MaximumConstraints) {
    // Maximum constraint values
    testAllApproaches({100000}, {99999}, {}, false);  // Maximum node value
}

TEST_F(IntersectionOfTwoLinkedListsTest, MaximumListSize) {
    // Test with larger lists (subset of maximum constraint for test speed)
    std::vector<int> listA, listB;
    
    // Create lists of size ~1000 each
    for (int i = 1; i <= 1000; ++i) {
        listA.push_back(i);
    }
    
    for (int i = 2000; i <= 3000; ++i) {
        listB.push_back(i);
    }
    
    testAllApproaches(listA, listB, {50000}, true);
}

// Complex Scenarios

TEST_F(IntersectionOfTwoLinkedListsTest, AlmostIdenticalLists) {
    // Lists differ only in first node
    testAllApproaches({1}, {2}, {3, 4, 5, 6, 7}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, NestedPatterns) {
    // Lists with nested numerical patterns
    testAllApproaches({1, 1, 2, 3, 5}, {2, 4, 6, 8}, {8, 13, 21}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, ArithmeticSequences) {
    // Lists following arithmetic sequences
    testAllApproaches({2, 4, 6, 8}, {1, 3, 5, 7, 9}, {10, 12, 14}, true);
}

// Memory Management Tests

TEST_F(IntersectionOfTwoLinkedListsTest, MultipleOperations) {
    // Test multiple operations for memory leak detection
    for (int i = 0; i < 10; ++i) {
        testAllApproaches({1, 2}, {3, 4}, {5, 6}, true);
        testAllApproaches({7, 8, 9}, {10, 11}, {}, false);
    }
}

// Special Algorithm-Specific Tests

TEST_F(IntersectionOfTwoLinkedListsTest, CleverTwoPointersEdgeCase) {
    // Test the mathematical property of clever two pointers
    // After m+n steps, both pointers should be at same position
    testAllApproaches({1, 2, 3}, {4, 5}, {6, 7, 8, 9}, true);
}

TEST_F(IntersectionOfTwoLinkedListsTest, StackApproachBackwardTraversal) {
    // Test stack approach with various intersection positions
    testAllApproaches({1, 2, 3, 4, 5}, {6, 7, 8}, {9}, true);  // Intersection at end
    testAllApproaches({1}, {2}, {3, 4, 5, 6, 7}, true);        // Intersection at beginning of tail
}

TEST_F(IntersectionOfTwoLinkedListsTest, MarkAndRestoreComplexity) {
    // Test mark and restore with various list structures
    testAllApproaches({1, 2, 3}, {4, 5, 6, 7}, {8, 9}, true);
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode