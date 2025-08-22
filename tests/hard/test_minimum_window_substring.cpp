#include <gtest/gtest.h>
#include "../../src/hard/minimum_window_substring.h"
#include <string>
#include <algorithm>

namespace leetcode {
namespace hard {
namespace test {

class MinimumWindowSubstringTest : public ::testing::Test {
protected:
    MinimumWindowSubstring solution;
    
    void testAllApproaches(const std::string& s, const std::string& t, const std::string& expected) {
        EXPECT_EQ(solution.minWindow(s, t), expected) 
            << "Sliding Window Hash Map approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.minWindowArray(s, t), expected) 
            << "Sliding Window Array approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.minWindowFiltered(s, t), expected) 
            << "Filtered String approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.minWindowTwoPass(s, t), expected) 
            << "Two-Pass approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.minWindowDeque(s, t), expected) 
            << "Deque Optimization approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.minWindowBruteForce(s, t), expected) 
            << "Brute Force approach failed for s=\"" << s << "\", t=\"" << t << "\"";
    }
};

// Basic functionality tests
TEST_F(MinimumWindowSubstringTest, LeetCodeExample1) {
    // Example 1: s = "ADOBECODEBANC", t = "ABC"
    // Output: "BANC"
    testAllApproaches("ADOBECODEBANC", "ABC", "BANC");
}

TEST_F(MinimumWindowSubstringTest, LeetCodeExample2) {
    // Example 2: s = "a", t = "a"  
    // Output: "a"
    testAllApproaches("a", "a", "a");
}

TEST_F(MinimumWindowSubstringTest, LeetCodeExample3) {
    // Example 3: s = "a", t = "aa"
    // Output: ""
    testAllApproaches("a", "aa", "");
}

// Edge cases
TEST_F(MinimumWindowSubstringTest, EmptyStrings) {
    testAllApproaches("", "", "");
    testAllApproaches("", "a", "");
    testAllApproaches("a", "", "");
}

TEST_F(MinimumWindowSubstringTest, SingleCharacter) {
    testAllApproaches("a", "a", "a");
    testAllApproaches("b", "a", "");
    testAllApproaches("a", "b", "");
}

TEST_F(MinimumWindowSubstringTest, TargetLongerThanSource) {
    testAllApproaches("ab", "abc", "");
    testAllApproaches("a", "aa", "");
    testAllApproaches("abc", "abcd", "");
}

TEST_F(MinimumWindowSubstringTest, NoValidWindow) {
    testAllApproaches("abc", "def", "");
    testAllApproaches("aaa", "b", "");
    testAllApproaches("abcdef", "xyz", "");
}

// Basic valid cases
TEST_F(MinimumWindowSubstringTest, ExactMatch) {
    testAllApproaches("abc", "abc", "abc");
    testAllApproaches("xyz", "xyz", "xyz");
    testAllApproaches("a", "a", "a");
}

TEST_F(MinimumWindowSubstringTest, WindowAtStart) {
    testAllApproaches("abcdef", "abc", "abc");
    testAllApproaches("xyzhello", "xyz", "xyz");
}

TEST_F(MinimumWindowSubstringTest, WindowAtEnd) {
    testAllApproaches("helloabc", "abc", "abc");
    testAllApproaches("worldxyz", "xyz", "xyz");
}

TEST_F(MinimumWindowSubstringTest, WindowInMiddle) {
    testAllApproaches("preabcpost", "abc", "abc");
    testAllApproaches("startxyzend", "xyz", "xyz");
}

// Duplicate characters in target
TEST_F(MinimumWindowSubstringTest, DuplicatesInTarget) {
    testAllApproaches("aabbcc", "abc", "abbc");
    testAllApproaches("aabbcc", "aab", "aabb");
    testAllApproaches("aaabbbccc", "abc", "aaabbbc");
}

TEST_F(MinimumWindowSubstringTest, MultipleOccurrences) {
    testAllApproaches("adobecodebanc", "abc", "banc");
    testAllApproaches("abcabcabc", "abc", "abc");
}

TEST_F(MinimumWindowSubstringTest, RepeatedCharacters) {
    testAllApproaches("aaaaaaa", "aa", "aa");
    testAllApproaches("aabbbaaa", "aa", "aa");
    testAllApproaches("abbbbbbbab", "ab", "ab");
}

// Complex cases
TEST_F(MinimumWindowSubstringTest, InterleavedPattern) {
    testAllApproaches("acbbaca", "aba", "bbaca");
    testAllApproaches("abcabcbb", "abcbb", "abcbb");
}

TEST_F(MinimumWindowSubstringTest, SparseMatching) {
    testAllApproaches("a00a00a", "aaa", "a00a00a");
    testAllApproaches("x0y0z0x0y0z", "xyz", "x0y0z");
}

TEST_F(MinimumWindowSubstringTest, OverlappingWindows) {
    testAllApproaches("abcdefabcdef", "abc", "abc");
    testAllApproaches("aabbccaabbcc", "abc", "abbc");
}

// Case sensitivity
TEST_F(MinimumWindowSubstringTest, CaseSensitive) {
    testAllApproaches("AaBbCc", "ABC", "AaBbC");
    testAllApproaches("AaBbCc", "abc", "aBbc");
    testAllApproaches("AbCdEf", "ACE", "AbCdE");
}

TEST_F(MinimumWindowSubstringTest, MixedCase) {
    testAllApproaches("aAbBcC", "AbC", "AbBc");
    testAllApproaches("Hello", "elo", "ello");
}

// Performance and stress tests
TEST_F(MinimumWindowSubstringTest, LongString) {
    std::string s = "a" + std::string(1000, 'x') + "bc";
    testAllApproaches(s, "abc", "a" + std::string(1000, 'x') + "bc");
}

TEST_F(MinimumWindowSubstringTest, ManyDuplicates) {
    testAllApproaches("aaaaaabbbbbccccc", "abc", "aaaaaabbbbbc");
    testAllApproaches("abcabcabcabc", "abc", "abc");
}

TEST_F(MinimumWindowSubstringTest, AllSameCharacter) {
    testAllApproaches("aaaaa", "aa", "aa");
    testAllApproaches("aaaaa", "aaa", "aaa");
    testAllApproaches("bbbbb", "bb", "bb");
}

// Minimum window edge cases
TEST_F(MinimumWindowSubstringTest, MinimumPossibleWindow) {
    testAllApproaches("abc", "c", "c");
    testAllApproaches("abcdef", "f", "f");
    testAllApproaches("hello", "l", "l");
}

TEST_F(MinimumWindowSubstringTest, EntireStringIsWindow) {
    testAllApproaches("abc", "abc", "abc");
    testAllApproaches("abcdef", "abcdef", "abcdef");
}

// Multiple valid windows of same minimum length
TEST_F(MinimumWindowSubstringTest, MultipleMinimumWindows) {
    // When multiple windows have same minimum length, any one is acceptable
    std::string result = solution.minWindow("abab", "ab");
    EXPECT_TRUE(result == "ab" || result == "ba") << "Expected 'ab' or 'ba', got: " << result;
}

// Boundary character positions
TEST_F(MinimumWindowSubstringTest, BoundaryPositions) {
    testAllApproaches("abcdef", "af", "abcdef");
    testAllApproaches("xyzabc", "ac", "xyzabc");
}

// Special patterns
TEST_F(MinimumWindowSubstringTest, PalindromeTargets) {
    testAllApproaches("abccba", "aba", "abccba");
    testAllApproaches("raceacar", "arc", "raceac");
}

TEST_F(MinimumWindowSubstringTest, ReversedTargets) {
    testAllApproaches("abcdef", "fed", "def");
    testAllApproaches("hello", "leh", "hello");
}

// Algorithm-specific edge cases
TEST_F(MinimumWindowSubstringTest, FilteredStringTest) {
    // Test case where filtering is beneficial
    testAllApproaches("a" + std::string(100, 'x') + "b" + std::string(100, 'y') + "c", "abc", 
                     "a" + std::string(100, 'x') + "b" + std::string(100, 'y') + "c");
}

TEST_F(MinimumWindowSubstringTest, DequeOptimizationTest) {
    // Test case where deque optimization helps
    testAllApproaches("axbxcxaxbxcx", "abc", "axbxc");
}

// Unicode and extended ASCII (within constraints)
TEST_F(MinimumWindowSubstringTest, ExtendedASCII) {
    // Test with full range of lowercase/uppercase as per constraints
    testAllApproaches("ABCDEFabcdef", "Aa", "ABCDEFa");
    testAllApproaches("zZyYxX", "xyz", "zZyYxX");
}

// Large target string
TEST_F(MinimumWindowSubstringTest, LargeTarget) {
    testAllApproaches("abcdefghijklmnopqrstuvwxyz", "abc", "abc");
    testAllApproaches("zyxwvutsrqponmlkjihgfedcba", "abc", "gfedcba");
}

// Stress test with maximum constraints
TEST_F(MinimumWindowSubstringTest, StressTest) {
    // Large string with sparse target characters
    std::string s = "a" + std::string(500, 'x') + "b" + std::string(500, 'y') + "c";
    std::string t = "abc";
    
    std::string result = solution.minWindow(s, t);
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.find('a') != std::string::npos);
    EXPECT_TRUE(result.find('b') != std::string::npos);
    EXPECT_TRUE(result.find('c') != std::string::npos);
}

// Window contraction scenarios
TEST_F(MinimumWindowSubstringTest, WindowContraction) {
    testAllApproaches("aabbccddabc", "abc", "abc");
    testAllApproaches("aaabbbcccabc", "abc", "abc");
}

// Target with all same characters
TEST_F(MinimumWindowSubstringTest, TargetAllSame) {
    testAllApproaches("abcdaaaa", "aaa", "aaaa");
    testAllApproaches("xbbbbbby", "bbb", "bbbb");
}

// Interleaved duplicate patterns
TEST_F(MinimumWindowSubstringTest, InterleavedDuplicates) {
    testAllApproaches("aabbaabb", "ab", "ab");
    testAllApproaches("abcabcabc", "cab", "cabcab");
}

}
}
}