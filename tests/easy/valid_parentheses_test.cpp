#include <gtest/gtest.h>
#include "easy/valid_parentheses.h"

using namespace leetcode::easy;

class ValidParenthesesTest : public ::testing::Test {
protected:
    ValidParentheses solution;
    
    void verifyAllApproaches(const std::string& input, bool expected) {
        EXPECT_EQ(solution.isValidStack(input), expected) 
            << "Stack approach failed for input: " << input;
        EXPECT_EQ(solution.isValidStackSwitch(input), expected) 
            << "Stack Switch approach failed for input: " << input;
        EXPECT_EQ(solution.isValidCounter(input), expected) 
            << "Counter approach failed for input: " << input;
        EXPECT_EQ(solution.isValidReplace(input), expected) 
            << "Replace approach failed for input: " << input;
        EXPECT_EQ(solution.isValidRecursive(input), expected) 
            << "Recursive approach failed for input: " << input;
        EXPECT_EQ(solution.isValidArrayStack(input), expected) 
            << "Array Stack approach failed for input: " << input;
    }
};

TEST_F(ValidParenthesesTest, SimpleValid) {
    verifyAllApproaches("()", true);
}

TEST_F(ValidParenthesesTest, MultipleTypesValid) {
    verifyAllApproaches("()[]{}", true);
}

TEST_F(ValidParenthesesTest, NestedValid) {
    verifyAllApproaches("{[]}", true);
}

TEST_F(ValidParenthesesTest, ComplexNestedValid) {
    verifyAllApproaches("([{}])", true);
}

TEST_F(ValidParenthesesTest, SimpleInvalid) {
    verifyAllApproaches("(]", false);
}

TEST_F(ValidParenthesesTest, WrongOrderInvalid) {
    verifyAllApproaches("([)]", false);
}

TEST_F(ValidParenthesesTest, SingleOpeningBracket) {
    verifyAllApproaches("(", false);
}

TEST_F(ValidParenthesesTest, SingleClosingBracket) {
    verifyAllApproaches(")", false);
}

TEST_F(ValidParenthesesTest, MismatchedPairs) {
    verifyAllApproaches("(}", false);
}

TEST_F(ValidParenthesesTest, ExtraOpeningBrackets) {
    verifyAllApproaches("((", false);
}

TEST_F(ValidParenthesesTest, ExtraClosingBrackets) {
    verifyAllApproaches("))", false);
}

TEST_F(ValidParenthesesTest, ComplexValid) {
    verifyAllApproaches("{[()()]}", true);
}

TEST_F(ValidParenthesesTest, AllSameTypeValid) {
    verifyAllApproaches("(((())))", true);
}

TEST_F(ValidParenthesesTest, AllSameTypeInvalid) {
    verifyAllApproaches("((())", false);
}

TEST_F(ValidParenthesesTest, AlternatingValid) {
    verifyAllApproaches("()()()[][]{}{}",   true);
}

TEST_F(ValidParenthesesTest, ReverseOrderInvalid) {
    verifyAllApproaches("}{", false);
}

TEST_F(ValidParenthesesTest, LongNestedValid) {
    verifyAllApproaches("(({[()]}))", true);
}

TEST_F(ValidParenthesesTest, InterleavedInvalid) {
    verifyAllApproaches("([{)]}", false);
}

TEST_F(ValidParenthesesTest, PartiallyValidSequence) {
    verifyAllApproaches("(){}][", false);
}

TEST_F(ValidParenthesesTest, DeeplyNestedValid) {
    verifyAllApproaches("[[[[[[]]]]]]", true);
}

TEST_F(ValidParenthesesTest, ComplexMixedValid) {
    verifyAllApproaches("{()[][{}]}", true);
}

TEST_F(ValidParenthesesTest, StartClosingInvalid) {
    verifyAllApproaches("]()[]", false);
}

TEST_F(ValidParenthesesTest, MiddleMismatchInvalid) {
    verifyAllApproaches("(){]}", false);
}

TEST_F(ValidParenthesesTest, EmptyStringValid) {
    verifyAllApproaches("", true);
}

TEST_F(ValidParenthesesTest, MaximumNestingValid) {
    verifyAllApproaches("([([([([])])])])", true);
}