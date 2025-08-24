#include <gtest/gtest.h>
#include "../../src/easy/palindrome_linked_list.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

class PalindromeLinkedListTest : public ::testing::Test {
protected:
    // Helper to test all approaches
    void testAllApproaches(const std::vector<int>& input, bool expected) {
        PalindromeLinkedList solution;
        
        // Test each approach
        for (int approach = 0; approach < 6; ++approach) {
            ListNode* list = solution.createList(input);
            bool result = false;
            
            switch (approach) {
                case 0:
                    result = solution.isPalindromeArray(list);
                    break;
                case 1:
                    result = solution.isPalindromeStack(list);
                    break;
                case 2:
                    result = solution.isPalindromeReverseSecondHalf(list);
                    break;
                case 3:
                    result = solution.isPalindromeRecursive(list);
                    break;
                case 4:
                    result = solution.isPalindromeMathematical(list);
                    break;
                case 5:
                    result = solution.isPalindromeFunctional(list);
                    break;
            }
            
            std::vector<std::string> approachNames = {
                "Array", "Stack", "Reverse Second Half", 
                "Recursive", "Mathematical", "Functional"
            };
            
            EXPECT_EQ(result, expected) 
                << approachNames[approach] << " approach failed for input: " << vectorToString(input)
                << ", expected: " << (expected ? "true" : "false")
                << ", got: " << (result ? "true" : "false");
            
            // Verify list structure is preserved (especially for reverse second half approach)
            std::vector<int> afterProcessing = solution.listToVector(list);
            EXPECT_EQ(afterProcessing, input)
                << approachNames[approach] << " approach modified the original list";
            
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

TEST_F(PalindromeLinkedListTest, LeetCodeExample1) {
    // Input: head = [1,2,2,1]
    // Output: true
    testAllApproaches({1, 2, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, LeetCodeExample2) {
    // Input: head = [1,2]
    // Output: false
    testAllApproaches({1, 2}, false);
}

// Single Element Tests

TEST_F(PalindromeLinkedListTest, SingleElementZero) {
    // Single element with value 0
    testAllApproaches({0}, true);
}

TEST_F(PalindromeLinkedListTest, SingleElementNonZero) {
    // Single element with non-zero value
    testAllApproaches({5}, true);
}

TEST_F(PalindromeLinkedListTest, SingleElementMaxValue) {
    // Single element with maximum constraint value
    testAllApproaches({9}, true);
}

// Two Element Tests

TEST_F(PalindromeLinkedListTest, TwoElementsPalindrome) {
    // Two identical elements
    testAllApproaches({3, 3}, true);
}

TEST_F(PalindromeLinkedListTest, TwoElementsNotPalindrome) {
    // Two different elements
    testAllApproaches({1, 2}, false);
}

TEST_F(PalindromeLinkedListTest, TwoElementsZeros) {
    // Two zeros
    testAllApproaches({0, 0}, true);
}

TEST_F(PalindromeLinkedListTest, TwoElementsMaxValues) {
    // Two maximum values
    testAllApproaches({9, 9}, true);
}

// Three Element Tests

TEST_F(PalindromeLinkedListTest, ThreeElementsPalindrome) {
    // Three elements forming palindrome
    testAllApproaches({1, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, ThreeElementsNotPalindrome) {
    // Three elements not forming palindrome
    testAllApproaches({1, 2, 3}, false);
}

TEST_F(PalindromeLinkedListTest, ThreeElementsAllSame) {
    // Three identical elements
    testAllApproaches({7, 7, 7}, true);
}

TEST_F(PalindromeLinkedListTest, ThreeElementsWithZero) {
    // Three elements with zero in middle
    testAllApproaches({5, 0, 5}, true);
}

// Four Element Tests

TEST_F(PalindromeLinkedListTest, FourElementsPalindrome) {
    // Four elements forming palindrome
    testAllApproaches({1, 2, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, FourElementsNotPalindrome) {
    // Four elements not forming palindrome
    testAllApproaches({1, 2, 3, 4}, false);
}

TEST_F(PalindromeLinkedListTest, FourElementsAllSame) {
    // Four identical elements
    testAllApproaches({4, 4, 4, 4}, true);
}

TEST_F(PalindromeLinkedListTest, FourElementsSymmetricPairs) {
    // Four elements with symmetric pairs
    testAllApproaches({1, 9, 9, 1}, true);
}

// Odd Length Palindromes

TEST_F(PalindromeLinkedListTest, FiveElementsPalindrome) {
    // Five elements palindrome
    testAllApproaches({1, 2, 3, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, SevenElementsPalindrome) {
    // Seven elements palindrome
    testAllApproaches({1, 2, 3, 4, 3, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, NineElementsPalindrome) {
    // Nine elements palindrome
    testAllApproaches({9, 8, 7, 6, 5, 6, 7, 8, 9}, true);
}

TEST_F(PalindromeLinkedListTest, OddLengthWithZeroCenter) {
    // Odd length with zero in center
    testAllApproaches({3, 2, 1, 0, 1, 2, 3}, true);
}

// Even Length Palindromes

TEST_F(PalindromeLinkedListTest, SixElementsPalindrome) {
    // Six elements palindrome
    testAllApproaches({1, 2, 3, 3, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, EightElementsPalindrome) {
    // Eight elements palindrome
    testAllApproaches({1, 2, 3, 4, 4, 3, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, TenElementsPalindrome) {
    // Ten elements palindrome
    testAllApproaches({9, 8, 7, 6, 5, 5, 6, 7, 8, 9}, true);
}

// Non-Palindrome Tests

TEST_F(PalindromeLinkedListTest, FiveElementsNotPalindrome) {
    // Five elements not palindrome
    testAllApproaches({1, 2, 3, 4, 5}, false);
}

TEST_F(PalindromeLinkedListTest, SixElementsNotPalindrome) {
    // Six elements not palindrome
    testAllApproaches({1, 2, 3, 4, 5, 6}, false);
}

TEST_F(PalindromeLinkedListTest, AlmostPalindrome) {
    // Almost palindrome (one element different)
    testAllApproaches({1, 2, 3, 2, 2}, false);
}

TEST_F(PalindromeLinkedListTest, ReverseOrder) {
    // Reverse of palindrome
    testAllApproaches({1, 2, 3, 4}, false);
}

// Special Value Tests

TEST_F(PalindromeLinkedListTest, AllZeros) {
    // List with all zeros
    testAllApproaches({0, 0, 0, 0, 0}, true);
}

TEST_F(PalindromeLinkedListTest, AllMaxValues) {
    // List with all maximum values
    testAllApproaches({9, 9, 9, 9, 9, 9}, true);
}

TEST_F(PalindromeLinkedListTest, MixedZerosAndOnes) {
    // Mix of zeros and ones
    testAllApproaches({0, 1, 0, 1, 0}, true);
}

TEST_F(PalindromeLinkedListTest, ZeroAndMaxValuePalindrome) {
    // Palindrome with minimum and maximum values
    testAllApproaches({0, 9, 0}, true);
}

// Edge Pattern Tests

TEST_F(PalindromeLinkedListTest, AlternatingPattern) {
    // Alternating pattern that's palindrome
    testAllApproaches({1, 2, 1, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, AlternatingPatternNotPalindrome) {
    // Alternating pattern that's not palindrome
    testAllApproaches({1, 2, 1, 2, 3}, false);
}

TEST_F(PalindromeLinkedListTest, IncreasingThenDecreasing) {
    // Increasing then decreasing (mountain pattern)
    testAllApproaches({1, 2, 3, 4, 3, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, DecreasingThenIncreasing) {
    // Decreasing then increasing (valley pattern)
    testAllApproaches({4, 3, 2, 1, 2, 3, 4}, true);
}

// Repeated Element Tests

TEST_F(PalindromeLinkedListTest, RepeatedElementsPalindrome) {
    // Repeated elements forming palindrome
    testAllApproaches({5, 5, 3, 3, 3, 5, 5}, true);
}

TEST_F(PalindromeLinkedListTest, RepeatedElementsNotPalindrome) {
    // Repeated elements not forming palindrome
    testAllApproaches({5, 5, 3, 3, 2, 5, 5}, false);
}

TEST_F(PalindromeLinkedListTest, MostlyRepeatedWithDifference) {
    // Mostly repeated elements with one difference
    testAllApproaches({7, 7, 7, 8, 7, 7, 7}, true);
}

// Large List Tests

TEST_F(PalindromeLinkedListTest, LargePalindromeOdd) {
    // Large odd-length palindrome
    std::vector<int> input;
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i % 10);
    }
    for (int i = 49; i >= 1; --i) {
        input.push_back(i % 10);
    }
    testAllApproaches(input, true);
}

TEST_F(PalindromeLinkedListTest, LargePalindromeEven) {
    // Large even-length palindrome
    std::vector<int> input;
    for (int i = 1; i <= 50; ++i) {
        input.push_back(i % 10);
    }
    for (int i = 50; i >= 1; --i) {
        input.push_back(i % 10);
    }
    testAllApproaches(input, true);
}

TEST_F(PalindromeLinkedListTest, LargeNotPalindrome) {
    // Large list that's not palindrome
    std::vector<int> input;
    for (int i = 1; i <= 100; ++i) {
        input.push_back(i % 10);
    }
    testAllApproaches(input, false);
}

// Boundary Constraint Tests

TEST_F(PalindromeLinkedListTest, MinimumLength) {
    // Minimum constraint: single node
    testAllApproaches({0}, true);
    testAllApproaches({9}, true);
}

TEST_F(PalindromeLinkedListTest, LongSequentialPalindrome) {
    // Long palindrome with sequential numbers
    std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    testAllApproaches(input, true);
}

TEST_F(PalindromeLinkedListTest, MaxValueSequence) {
    // Sequence using maximum values
    testAllApproaches({9, 8, 7, 6, 7, 8, 9}, true);
}

// Complex Pattern Tests

TEST_F(PalindromeLinkedListTest, FibonacciLikePalindrome) {
    // Fibonacci-like sequence that forms palindrome
    testAllApproaches({1, 1, 2, 3, 5, 3, 2, 1, 1}, true);
}

TEST_F(PalindromeLinkedListTest, NestedSymmetry) {
    // Nested symmetric patterns
    testAllApproaches({1, 2, 1, 3, 1, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, MultipleZerosSymmetric) {
    // Multiple zeros in symmetric positions
    testAllApproaches({0, 1, 0, 0, 0, 1, 0}, true);
}

// Mathematical Property Tests

TEST_F(PalindromeLinkedListTest, PowersOfTwoPalindrome) {
    // Powers of 2 (mod 10) palindrome
    testAllApproaches({1, 2, 4, 8, 6, 2, 4, 8, 6}, false);
}

TEST_F(PalindromeLinkedListTest, DigitsOfPi) {
    // First few digits of pi in palindrome format
    testAllApproaches({3, 1, 4, 1, 3}, true);
}

// Edge Cases for Specific Approaches

TEST_F(PalindromeLinkedListTest, EvenLengthForStackApproach) {
    // Even length that tests stack approach middle handling
    testAllApproaches({1, 2, 3, 3, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, OddLengthForStackApproach) {
    // Odd length that tests stack approach middle handling
    testAllApproaches({1, 2, 3, 4, 3, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, RecursiveDeepNesting) {
    // Test recursive approach with moderate depth
    std::vector<int> input;
    for (int i = 0; i < 50; ++i) {
        input.push_back(i % 5);
    }
    for (int i = 49; i >= 0; --i) {
        input.push_back(i % 5);
    }
    testAllApproaches(input, true);
}

// Mathematical Approach Specific Tests

TEST_F(PalindromeLinkedListTest, MathematicalEdgeCase1) {
    // Test mathematical approach with specific values
    testAllApproaches({1, 0, 1}, true);
}

TEST_F(PalindromeLinkedListTest, MathematicalEdgeCase2) {
    // Test mathematical approach with larger numbers
    testAllApproaches({9, 0, 9}, true);
}

TEST_F(PalindromeLinkedListTest, MathematicalNotPalindrome) {
    // Test mathematical approach with non-palindrome
    testAllApproaches({1, 0, 2}, false);
}

// Functional Approach Tests

TEST_F(PalindromeLinkedListTest, FunctionalSimplePalindrome) {
    // Simple palindrome for functional approach
    testAllApproaches({1, 2, 1}, true);
}

TEST_F(PalindromeLinkedListTest, FunctionalComplexPalindrome) {
    // Complex palindrome for functional approach
    testAllApproaches({5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5}, true);
}

// Performance and Stress Tests

TEST_F(PalindromeLinkedListTest, AllSameValues) {
    // All elements are the same (stress test)
    std::vector<int> input(100, 7);
    testAllApproaches(input, true);
}

TEST_F(PalindromeLinkedListTest, LargeAlternatingPalindrome) {
    // Large alternating palindrome
    std::vector<int> input;
    for (int i = 0; i < 100; ++i) {
        input.push_back(i % 2);
    }
    for (int i = 99; i >= 0; --i) {
        input.push_back(i % 2);
    }
    testAllApproaches(input, true);
}

// Memory Management Tests

TEST_F(PalindromeLinkedListTest, MultipleOperations) {
    // Test multiple operations for memory leak detection
    for (int i = 0; i < 10; ++i) {
        testAllApproaches({1, 2, 3, 2, 1}, true);
        testAllApproaches({1, 2, 3, 4, 5}, false);
    }
}

// Comprehensive Edge Case

TEST_F(PalindromeLinkedListTest, ComprehensiveEdgeCase) {
    // Various edge cases in one test
    testAllApproaches({0}, true);                    // Single zero
    testAllApproaches({9}, true);                    // Single max value
    testAllApproaches({0, 0}, true);                 // Two zeros
    testAllApproaches({9, 9}, true);                 // Two max values
    testAllApproaches({0, 9, 0}, true);              // Min-max-min palindrome
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode