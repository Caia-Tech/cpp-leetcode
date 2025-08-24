#include <gtest/gtest.h>
#include "../../src/easy/reverse_linked_list.h"
#include "../../src/utils/test_utils.h"
#include <vector>

namespace leetcode {
namespace easy {
namespace test {

using utils::ListNode;

class ReverseLinkedListTest : public ::testing::Test {
protected:
    // Helper to create a linked list from vector
    ListNode* createList(const std::vector<int>& values) {
        if (values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        ListNode* current = head;
        
        for (size_t i = 1; i < values.size(); ++i) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
        
        return head;
    }
    
    // Helper to convert list to vector for comparison
    std::vector<int> listToVector(ListNode* head) {
        std::vector<int> result;
        ListNode* current = head;
        
        while (current) {
            result.push_back(current->val);
            current = current->next;
        }
        
        return result;
    }
    
    // Helper to delete a list
    void deleteList(ListNode* head) {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Helper to clone a list for testing multiple approaches
    ListNode* cloneList(ListNode* head) {
        if (!head) return nullptr;
        
        ListNode* new_head = new ListNode(head->val);
        ListNode* current_old = head->next;
        ListNode* current_new = new_head;
        
        while (current_old) {
            current_new->next = new ListNode(current_old->val);
            current_new = current_new->next;
            current_old = current_old->next;
        }
        
        return new_head;
    }
    
    // Test all approaches with the same input
    void testAllApproaches(const std::vector<int>& input, const std::vector<int>& expected) {
        ReverseLinkedList solution;
        
        // Test iterative approach
        ListNode* head1 = createList(input);
        ListNode* reversed1 = solution.reverseListIterative(head1);
        EXPECT_EQ(listToVector(reversed1), expected) << "Iterative approach failed";
        deleteList(reversed1);
        
        // Test recursive approach
        ListNode* head2 = createList(input);
        ListNode* reversed2 = solution.reverseListRecursive(head2);
        EXPECT_EQ(listToVector(reversed2), expected) << "Recursive approach failed";
        deleteList(reversed2);
        
        // Test stack approach
        ListNode* head3 = createList(input);
        ListNode* reversed3 = solution.reverseListStack(head3);
        EXPECT_EQ(listToVector(reversed3), expected) << "Stack approach failed";
        deleteList(reversed3);
        
        // Test array approach
        ListNode* head4 = createList(input);
        ListNode* reversed4 = solution.reverseListArray(head4);
        EXPECT_EQ(listToVector(reversed4), expected) << "Array approach failed";
        deleteList(reversed4);
        
        // Test tail recursive approach
        ListNode* head5 = createList(input);
        ListNode* reversed5 = solution.reverseListTailRecursive(head5);
        EXPECT_EQ(listToVector(reversed5), expected) << "Tail recursive approach failed";
        deleteList(reversed5);
        
        // Test value swap approach
        ListNode* head6 = createList(input);
        ListNode* reversed6 = solution.reverseListValueSwap(head6);
        EXPECT_EQ(listToVector(reversed6), expected) << "Value swap approach failed";
        deleteList(reversed6);
    }
};

// LeetCode Example Test Cases

TEST_F(ReverseLinkedListTest, LeetCodeExample1) {
    // Input: head = [1,2,3,4,5]
    // Output: [5,4,3,2,1]
    testAllApproaches({1, 2, 3, 4, 5}, {5, 4, 3, 2, 1});
}

TEST_F(ReverseLinkedListTest, LeetCodeExample2) {
    // Input: head = [1,2]
    // Output: [2,1]
    testAllApproaches({1, 2}, {2, 1});
}

TEST_F(ReverseLinkedListTest, LeetCodeExample3) {
    // Input: head = []
    // Output: []
    testAllApproaches({}, {});
}

// Edge Cases

TEST_F(ReverseLinkedListTest, EmptyList) {
    ReverseLinkedList solution;
    EXPECT_EQ(solution.reverseListIterative(nullptr), nullptr);
    EXPECT_EQ(solution.reverseListRecursive(nullptr), nullptr);
    EXPECT_EQ(solution.reverseListStack(nullptr), nullptr);
    EXPECT_EQ(solution.reverseListArray(nullptr), nullptr);
    EXPECT_EQ(solution.reverseListTailRecursive(nullptr), nullptr);
    EXPECT_EQ(solution.reverseListValueSwap(nullptr), nullptr);
}

TEST_F(ReverseLinkedListTest, SingleNode) {
    testAllApproaches({42}, {42});
}

TEST_F(ReverseLinkedListTest, TwoNodes) {
    testAllApproaches({1, 2}, {2, 1});
}

TEST_F(ReverseLinkedListTest, ThreeNodes) {
    testAllApproaches({1, 2, 3}, {3, 2, 1});
}

// Special Values

TEST_F(ReverseLinkedListTest, AllSameValues) {
    testAllApproaches({5, 5, 5, 5, 5}, {5, 5, 5, 5, 5});
}

TEST_F(ReverseLinkedListTest, NegativeValues) {
    testAllApproaches({-1, -2, -3, -4}, {-4, -3, -2, -1});
}

TEST_F(ReverseLinkedListTest, MixedPositiveNegative) {
    testAllApproaches({-2, -1, 0, 1, 2}, {2, 1, 0, -1, -2});
}

TEST_F(ReverseLinkedListTest, AlternatingValues) {
    testAllApproaches({1, -1, 1, -1, 1}, {1, -1, 1, -1, 1});
}

// Boundary Values

TEST_F(ReverseLinkedListTest, MinimumConstraintValue) {
    testAllApproaches({-5000, -4999, -4998}, {-4998, -4999, -5000});
}

TEST_F(ReverseLinkedListTest, MaximumConstraintValue) {
    testAllApproaches({4998, 4999, 5000}, {5000, 4999, 4998});
}

TEST_F(ReverseLinkedListTest, MinToMaxValues) {
    testAllApproaches({-5000, 0, 5000}, {5000, 0, -5000});
}

// Pattern Tests

TEST_F(ReverseLinkedListTest, IncreasingSequence) {
    testAllApproaches({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 
                      {10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
}

TEST_F(ReverseLinkedListTest, DecreasingSequence) {
    testAllApproaches({10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 
                      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
}

TEST_F(ReverseLinkedListTest, AlternatingHighLow) {
    testAllApproaches({10, 1, 9, 2, 8, 3}, {3, 8, 2, 9, 1, 10});
}

TEST_F(ReverseLinkedListTest, Palindrome) {
    testAllApproaches({1, 2, 3, 2, 1}, {1, 2, 3, 2, 1});
}

TEST_F(ReverseLinkedListTest, NonPalindrome) {
    testAllApproaches({1, 2, 3, 4, 5}, {5, 4, 3, 2, 1});
}

// Large Lists

TEST_F(ReverseLinkedListTest, LargeList100) {
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 1; i <= 100; ++i) {
        input.push_back(i);
        expected.push_back(101 - i);
    }
    
    testAllApproaches(input, expected);
}

TEST_F(ReverseLinkedListTest, LargeList1000) {
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 0; i < 1000; ++i) {
        input.push_back(i);
        expected.push_back(999 - i);
    }
    
    ReverseLinkedList solution;
    
    // Test only non-recursive approaches for very large lists
    ListNode* head1 = createList(input);
    ListNode* reversed1 = solution.reverseListIterative(head1);
    EXPECT_EQ(listToVector(reversed1), expected);
    deleteList(reversed1);
    
    ListNode* head2 = createList(input);
    ListNode* reversed2 = solution.reverseListStack(head2);
    EXPECT_EQ(listToVector(reversed2), expected);
    deleteList(reversed2);
    
    ListNode* head3 = createList(input);
    ListNode* reversed3 = solution.reverseListArray(head3);
    EXPECT_EQ(listToVector(reversed3), expected);
    deleteList(reversed3);
}

// Maximum Size Test

TEST_F(ReverseLinkedListTest, MaximumSizeList) {
    // Test with maximum constraint (5000 nodes)
    std::vector<int> input;
    std::vector<int> expected;
    
    for (int i = 0; i < 5000; ++i) {
        input.push_back(i % 100);  // Use modulo to keep values reasonable
        expected.push_back((4999 - i) % 100);
    }
    
    ReverseLinkedList solution;
    
    // Test only iterative approach for maximum size
    ListNode* head = createList(input);
    ListNode* reversed = solution.reverseListIterative(head);
    EXPECT_EQ(listToVector(reversed), expected);
    deleteList(reversed);
}

// Special Patterns

TEST_F(ReverseLinkedListTest, FibonacciSequence) {
    testAllApproaches({1, 1, 2, 3, 5, 8, 13}, {13, 8, 5, 3, 2, 1, 1});
}

TEST_F(ReverseLinkedListTest, PowersOfTwo) {
    testAllApproaches({1, 2, 4, 8, 16, 32}, {32, 16, 8, 4, 2, 1});
}

TEST_F(ReverseLinkedListTest, ZeroAtDifferentPositions) {
    testAllApproaches({0, 1, 2, 3}, {3, 2, 1, 0});
    testAllApproaches({1, 0, 2, 3}, {3, 2, 0, 1});
    testAllApproaches({1, 2, 0, 3}, {3, 0, 2, 1});
    testAllApproaches({1, 2, 3, 0}, {0, 3, 2, 1});
}

// Random Pattern Tests

TEST_F(ReverseLinkedListTest, RandomPattern1) {
    testAllApproaches({42, -17, 0, 99, -50}, {-50, 99, 0, -17, 42});
}

TEST_F(ReverseLinkedListTest, RandomPattern2) {
    testAllApproaches({100, 200, -300, 400, -500, 600}, 
                      {600, -500, 400, -300, 200, 100});
}

TEST_F(ReverseLinkedListTest, BinaryPattern) {
    testAllApproaches({0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0});
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode