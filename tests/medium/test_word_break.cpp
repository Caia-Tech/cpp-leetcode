#include <gtest/gtest.h>
#include "medium/word_break.h"
#include <chrono>

using namespace leetcode::medium;

class WordBreakTest : public ::testing::Test {
protected:
    WordBreak solution;
    
    // Helper function to test all approaches
    void testAllApproaches(std::string s, std::vector<std::string> wordDict, bool expected) {
        std::vector<std::string> dict1 = wordDict, dict2 = wordDict, dict3 = wordDict,
                                dict4 = wordDict, dict5 = wordDict, dict6 = wordDict;
        
        EXPECT_EQ(solution.wordBreakDP(s, dict1), expected) << "DP approach failed";
        EXPECT_EQ(solution.wordBreakMemo(s, dict2), expected) << "Memoization approach failed";
        EXPECT_EQ(solution.wordBreakBFS(s, dict3), expected) << "BFS approach failed";
        EXPECT_EQ(solution.wordBreakTrie(s, dict4), expected) << "Trie approach failed";
        EXPECT_EQ(solution.wordBreakBacktrack(s, dict5), expected) << "Backtrack approach failed";
        EXPECT_EQ(solution.wordBreakSlidingWindow(s, dict6), expected) << "Sliding window approach failed";
    }
};

TEST_F(WordBreakTest, BasicExample1) {
    // Input: s = "leetcode", wordDict = ["leet","code"]
    // Output: true (can be segmented as "leet code")
    std::string s = "leetcode";
    std::vector<std::string> wordDict = {"leet", "code"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, BasicExample2) {
    // Input: s = "applepenapple", wordDict = ["apple","pen"]
    // Output: true (can be segmented as "apple pen apple")
    std::string s = "applepenapple";
    std::vector<std::string> wordDict = {"apple", "pen"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, BasicExample3) {
    // Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
    // Output: false (cannot be segmented)
    std::string s = "catsandog";
    std::vector<std::string> wordDict = {"cats", "dog", "sand", "and", "cat"};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, SingleCharacter) {
    // Input: s = "a", wordDict = ["a"]
    // Output: true
    std::string s = "a";
    std::vector<std::string> wordDict = {"a"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, SingleCharacterNotInDict) {
    // Input: s = "a", wordDict = ["b"]
    // Output: false
    std::string s = "a";
    std::vector<std::string> wordDict = {"b"};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, EmptyDict) {
    // Input: s = "abc", wordDict = []
    // Output: false
    std::string s = "abc";
    std::vector<std::string> wordDict = {};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, ExactMatch) {
    // Input: s = "hello", wordDict = ["hello"]
    // Output: true
    std::string s = "hello";
    std::vector<std::string> wordDict = {"hello"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, RepeatedWords) {
    // Input: s = "aaaa", wordDict = ["a", "aa"]
    // Output: true (can be segmented in multiple ways)
    std::string s = "aaaa";
    std::vector<std::string> wordDict = {"a", "aa"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, OverlappingWords) {
    // Input: s = "abcd", wordDict = ["ab", "abc", "cd"]
    // Output: true ("abc" + "d" won't work, but "ab" + "cd" works)
    std::string s = "abcd";
    std::vector<std::string> wordDict = {"ab", "abc", "cd"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, NoValidSegmentation) {
    // Input: s = "abcdef", wordDict = ["abc", "def", "gh"]
    // Output: false (missing connection between abc and def)
    std::string s = "abcdef";
    std::vector<std::string> wordDict = {"abc", "def", "gh"};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, LongWordInDict) {
    // Input: s = "programming", wordDict = ["program", "ming"]
    // Output: true
    std::string s = "programming";
    std::vector<std::string> wordDict = {"program", "ming"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, MultipleValidSegmentations) {
    // Input: s = "catdog", wordDict = ["cat", "dog", "ca", "tdog"]
    // Output: true (both "cat"+"dog" and "ca"+"tdog" work)
    std::string s = "catdog";
    std::vector<std::string> wordDict = {"cat", "dog", "ca", "tdog"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, PrefixPresentButNotComplete) {
    // Input: s = "cars", wordDict = ["car", "ca", "rs"]
    // Output: false (can't segment "s" after "car")
    std::string s = "cars";
    std::vector<std::string> wordDict = {"car", "ca", "rs"};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, AllSingleCharacters) {
    // Input: s = "abcd", wordDict = ["a", "b", "c", "d"]
    // Output: true
    std::string s = "abcd";
    std::vector<std::string> wordDict = {"a", "b", "c", "d"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, MissingSingleCharacter) {
    // Input: s = "abcd", wordDict = ["a", "b", "d"]
    // Output: false (missing "c")
    std::string s = "abcd";
    std::vector<std::string> wordDict = {"a", "b", "d"};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, RepeatedWordUsage) {
    // Input: s = "aaaaaaa", wordDict = ["aaa", "aaaa"]
    // Output: true (can use "aaa" + "aaaa" or "aaaa" + "aaa")
    std::string s = "aaaaaaa";
    std::vector<std::string> wordDict = {"aaa", "aaaa"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, LongString) {
    // Test with longer string
    std::string s = "thequickbrownfoxjumpsoverthelazydog";
    std::vector<std::string> wordDict = {"the", "quick", "brown", "fox", "jumps", "over", "lazy", "dog"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, ComplexOverlapping) {
    // Input: s = "abab", wordDict = ["ab", "aba", "bab"]
    // Output: true ("ab" + "ab")
    std::string s = "abab";
    std::vector<std::string> wordDict = {"ab", "aba", "bab"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, WordLongerThanString) {
    // Input: s = "abc", wordDict = ["abcd"]
    // Output: false (word longer than string)
    std::string s = "abc";
    std::vector<std::string> wordDict = {"abcd"};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, PartialMatch) {
    // Input: s = "goalspecial", wordDict = ["go", "goal", "goals", "special"]
    // Output: true ("goal" + "special")
    std::string s = "goalspecial";
    std::vector<std::string> wordDict = {"go", "goal", "goals", "special"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, NoPartialMatch) {
    // Input: s = "wordbreak", wordDict = ["word", "break", "work"]
    // Output: true ("word" + "break")
    std::string s = "wordbreak";
    std::vector<std::string> wordDict = {"word", "break", "work"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, CaseWithBacktracking) {
    // This case requires backtracking from wrong initial choices
    std::string s = "abcdef";
    std::vector<std::string> wordDict = {"abc", "ab", "cdef", "def"};
    testAllApproaches(s, wordDict, true); // "abc" + "def" works
}

TEST_F(WordBreakTest, ComplexCase) {
    // More complex test case
    std::string s = "leetcodeleet";
    std::vector<std::string> wordDict = {"leet", "code", "leetcode"};
    testAllApproaches(s, wordDict, true); // "leet" + "code" + "leet"
}

TEST_F(WordBreakTest, TrieAdvantageCase) {
    // Case where trie approach might show advantage with many words sharing prefixes
    std::string s = "programming";
    std::vector<std::string> wordDict = {"prog", "program", "programming", "gram", "ming"};
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, MaxLengthConstraints) {
    // Test with constraint boundaries
    std::string s(300, 'a'); // Maximum string length
    std::vector<std::string> wordDict = {std::string(20, 'a')}; // Maximum word length
    testAllApproaches(s, wordDict, true); // 300/20 = 15 repetitions
}

TEST_F(WordBreakTest, ManyShortWords) {
    std::string s = "abcdefghijk";
    std::vector<std::string> wordDict;
    
    // Create dictionary with all single characters
    for (char c = 'a'; c <= 'k'; ++c) {
        wordDict.push_back(std::string(1, c));
    }
    
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, CircularDependency) {
    // Test case that might cause issues with circular references
    std::string s = "abcabc";
    std::vector<std::string> wordDict = {"abc", "abca", "bcab", "cab", "cabc"};
    testAllApproaches(s, wordDict, true); // "abc" + "abc"
}

// Performance tests
TEST_F(WordBreakTest, PerformanceTest) {
    // Create a moderately complex case
    std::string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    std::vector<std::string> wordDict = {"a", "aa", "aaa", "aaaa", "aaaaa"};
    
    // Test DP approach (should be efficient)
    auto start = std::chrono::high_resolution_clock::now();
    bool result1 = solution.wordBreakDP(s, wordDict);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration.count(), 10000) << "DP approach should complete quickly";
    
    // Test memoization approach
    start = std::chrono::high_resolution_clock::now();
    bool result2 = solution.wordBreakMemo(s, wordDict);
    end = std::chrono::high_resolution_clock::now();
    
    auto memoDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Results should match
    EXPECT_EQ(result1, result2);
    EXPECT_FALSE(result1); // This should be false (can't segment the 'b' at the end)
}

TEST_F(WordBreakTest, WorstCaseScenario) {
    // Worst case for some algorithms: many overlapping possibilities that fail
    std::string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    std::vector<std::string> wordDict;
    
    // Add various lengths of 'a' strings
    for (int i = 1; i <= 10; ++i) {
        wordDict.push_back(std::string(i, 'a'));
    }
    
    testAllApproaches(s, wordDict, false); // Should be false due to 'b' at end
}

// Edge case tests
TEST_F(WordBreakTest, EdgeCases) {
    // Test minimum constraints
    std::string s = "a";
    std::vector<std::string> wordDict = {"a"};
    testAllApproaches(s, wordDict, true);
    
    // Test with repeated characters but no valid segmentation
    s = "aaab";
    wordDict = {"aa", "aaa"};
    testAllApproaches(s, wordDict, false); // Can't handle the 'b'
    
    // Test with all same characters that CAN be segmented
    s = "aaaa";
    wordDict = {"aa"};
    testAllApproaches(s, wordDict, true); // "aa" + "aa"
}

TEST_F(WordBreakTest, StringNotInDictionary) {
    // String contains characters not in any dictionary word
    std::string s = "abcxyz";
    std::vector<std::string> wordDict = {"abc", "def"};
    testAllApproaches(s, wordDict, false);
}

TEST_F(WordBreakTest, LargerDictionary) {
    // Test with larger dictionary (up to constraint limit)
    std::string s = "thequickbrownfox";
    std::vector<std::string> wordDict;
    
    // Add many words
    wordDict = {"the", "a", "quick", "brown", "fox", "jumps", "over", "lazy", "dog",
                "th", "he", "qu", "ic", "ck", "br", "ow", "wn", "fo", "ox"};
    
    testAllApproaches(s, wordDict, true);
}

TEST_F(WordBreakTest, ApproachConsistencyTest) {
    // Test multiple cases to ensure all approaches are consistent
    std::vector<std::pair<std::string, std::vector<std::string>>> testCases = {
        {"leetcode", {"leet", "code"}},
        {"applepenapple", {"apple", "pen"}},
        {"catsandog", {"cats", "dog", "sand", "and", "cat"}},
        {"cars", {"car", "ca", "rs"}},
        {"aaaaaaa", {"aaa", "aaaa"}},
    };
    
    for (const auto& testCase : testCases) {
        // Get expected result from DP approach
        std::vector<std::string> dict = testCase.second;
        bool expected = solution.wordBreakDP(testCase.first, dict);
        
        // Test all approaches against this expected result
        testAllApproaches(testCase.first, testCase.second, expected);
    }
}

TEST_F(WordBreakTest, UniqueWordsVerification) {
    // Verify that dictionary uniqueness constraint doesn't affect our algorithms
    std::string s = "abab";
    std::vector<std::string> wordDict = {"ab"}; // Only one unique word, used twice
    testAllApproaches(s, wordDict, true);
}