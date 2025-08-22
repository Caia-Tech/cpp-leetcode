#include <gtest/gtest.h>
#include "hard/edit_distance.h"
#include <chrono>

using namespace leetcode::hard;

class EditDistanceTest : public ::testing::Test {
protected:
    EditDistance solution;
    
    // Helper function to test approaches (excluding BFS for large inputs due to exponential space)
    void testMainApproaches(const std::string& word1, const std::string& word2, int expected) {
        EXPECT_EQ(solution.minDistanceDP2D(word1, word2), expected) << "DP 2D failed for '" << word1 << "' -> '" << word2 << "'";
        EXPECT_EQ(solution.minDistanceDP1D(word1, word2), expected) << "DP 1D failed for '" << word1 << "' -> '" << word2 << "'";
        EXPECT_EQ(solution.minDistanceMemo(word1, word2), expected) << "Memoization failed for '" << word1 << "' -> '" << word2 << "'";
        EXPECT_EQ(solution.minDistanceAStar(word1, word2), expected) << "A* failed for '" << word1 << "' -> '" << word2 << "'";
        EXPECT_EQ(solution.minDistanceIterativeDeepening(word1, word2), expected) << "Iterative deepening failed for '" << word1 << "' -> '" << word2 << "'";
    }
    
    // Helper for testing all approaches including BFS (for small inputs only)
    void testAllApproaches(const std::string& word1, const std::string& word2, int expected) {
        testMainApproaches(word1, word2, expected);
        
        // Only test BFS for small inputs to avoid exponential explosion
        if (word1.length() <= 3 && word2.length() <= 3) {
            EXPECT_EQ(solution.minDistanceBFS(word1, word2), expected) << "BFS failed for '" << word1 << "' -> '" << word2 << "'";
        }
    }
};

TEST_F(EditDistanceTest, BasicExample1) {
    // Input: word1 = "horse", word2 = "ros"
    // Output: 3
    // Explanation: horse -> rorse (replace 'h' with 'r')
    //              rorse -> rose (remove 'r')
    //              rose -> ros (remove 'e')
    testMainApproaches("horse", "ros", 3);
}

TEST_F(EditDistanceTest, BasicExample2) {
    // Input: word1 = "intention", word2 = "execution"  
    // Output: 5
    // Explanation: intention -> inention (remove 't')
    //              inention -> enention (replace 'i' with 'e')
    //              enention -> exention (replace 'n' with 'x')
    //              exention -> exection (replace 'n' with 'c')
    //              exection -> execution (insert 'u')
    testMainApproaches("intention", "execution", 5);
}

TEST_F(EditDistanceTest, EmptyStrings) {
    // Input: word1 = "", word2 = ""
    // Output: 0
    testAllApproaches("", "", 0);
}

TEST_F(EditDistanceTest, OneEmptyString) {
    // Input: word1 = "abc", word2 = ""
    // Output: 3 (delete all characters)
    testAllApproaches("abc", "", 3);
    
    // Input: word1 = "", word2 = "def"
    // Output: 3 (insert all characters)
    testAllApproaches("", "def", 3);
}

TEST_F(EditDistanceTest, IdenticalStrings) {
    // Input: word1 = "same", word2 = "same"
    // Output: 0
    testMainApproaches("same", "same", 0);
}

TEST_F(EditDistanceTest, SingleCharacter) {
    // Input: word1 = "a", word2 = "b"
    // Output: 1 (replace)
    testAllApproaches("a", "b", 1);
    
    // Input: word1 = "a", word2 = "a"
    // Output: 0
    testAllApproaches("a", "a", 0);
}

TEST_F(EditDistanceTest, SingleInsertion) {
    // Input: word1 = "ab", word2 = "abc"
    // Output: 1 (insert 'c')
    testAllApproaches("ab", "abc", 1);
}

TEST_F(EditDistanceTest, SingleDeletion) {
    // Input: word1 = "abc", word2 = "ab"
    // Output: 1 (delete 'c')
    testAllApproaches("abc", "ab", 1);
}

TEST_F(EditDistanceTest, SingleReplacement) {
    // Input: word1 = "abc", word2 = "abd"
    // Output: 1 (replace 'c' with 'd')
    testAllApproaches("abc", "abd", 1);
}

TEST_F(EditDistanceTest, CompletelyDifferent) {
    // Input: word1 = "abc", word2 = "xyz"
    // Output: 3 (replace all characters)
    testAllApproaches("abc", "xyz", 3);
}

TEST_F(EditDistanceTest, Substring) {
    // Input: word1 = "abcdef", word2 = "abc"
    // Output: 3 (delete "def")
    testMainApproaches("abcdef", "abc", 3);
    
    // Input: word1 = "abc", word2 = "abcdef"
    // Output: 3 (insert "def")
    testMainApproaches("abc", "abcdef", 3);
}

TEST_F(EditDistanceTest, Reversed) {
    // Input: word1 = "abc", word2 = "cba"
    // Output: 2 (replace 'a' with 'c', replace 'c' with 'a')
    testAllApproaches("abc", "cba", 2);
}

TEST_F(EditDistanceTest, RepeatCharacters) {
    // Input: word1 = "aaa", word2 = "aa"
    // Output: 1 (delete one 'a')
    testAllApproaches("aaa", "aa", 1);
    
    // Input: word1 = "aa", word2 = "aaa"
    // Output: 1 (insert one 'a')
    testAllApproaches("aa", "aaa", 1);
}

TEST_F(EditDistanceTest, LongerStrings) {
    // Input: word1 = "kitten", word2 = "sitting"
    // Output: 3
    // kitten -> sitten (substitute k->s)
    // sitten -> sittin (substitute e->i)  
    // sittin -> sitting (insert g)
    testMainApproaches("kitten", "sitting", 3);
}

TEST_F(EditDistanceTest, NoCommonCharacters) {
    // Input: word1 = "abcd", word2 = "efgh"
    // Output: 4 (replace all characters)
    testMainApproaches("abcd", "efgh", 4);
}

TEST_F(EditDistanceTest, MixedOperations) {
    // Input: word1 = "sunday", word2 = "saturday"
    // Output: 3
    // sunday -> satday (insert 'a', 't')  
    // satday -> saturday (insert 'r')
    testMainApproaches("sunday", "saturday", 3);
}

TEST_F(EditDistanceTest, LongCommonPrefix) {
    // Input: word1 = "prefixabc", word2 = "prefixdef"
    // Output: 3 (replace "abc" with "def")
    testMainApproaches("prefixabc", "prefixdef", 3);
}

TEST_F(EditDistanceTest, LongCommonSuffix) {
    // Input: word1 = "abcsuffix", word2 = "defsuffix"
    // Output: 3 (replace "abc" with "def")
    testMainApproaches("abcsuffix", "defsuffix", 3);
}

TEST_F(EditDistanceTest, InterleavePattern) {
    // Input: word1 = "abab", word2 = "baba"
    // Output: 2
    testMainApproaches("abab", "baba", 2);
}

TEST_F(EditDistanceTest, EdgeCaseLengths) {
    // Test with constraint boundary values
    
    // Single characters
    testAllApproaches("z", "a", 1);
    
    // Maximum single string (vs empty)
    std::string maxStr(10, 'a'); // Use smaller size for testing
    testMainApproaches(maxStr, "", 10);
    testMainApproaches("", maxStr, 10);
}

TEST_F(EditDistanceTest, SymmetryTest) {
    // Edit distance should be symmetric
    std::vector<std::pair<std::string, std::string>> testPairs = {
        {"abc", "def"},
        {"hello", "world"},
        {"cat", "dog"},
        {"short", "longer"}
    };
    
    for (const auto& pair : testPairs) {
        int dist1 = solution.minDistanceDP2D(pair.first, pair.second);
        int dist2 = solution.minDistanceDP2D(pair.second, pair.first);
        EXPECT_EQ(dist1, dist2) << "Edit distance should be symmetric for '" 
                                << pair.first << "' and '" << pair.second << "'";
    }
}

TEST_F(EditDistanceTest, TriangleInequality) {
    // Edit distance should satisfy triangle inequality: d(a,c) <= d(a,b) + d(b,c)
    std::string a = "abc";
    std::string b = "def"; 
    std::string c = "ghi";
    
    int d_ac = solution.minDistanceDP2D(a, c);
    int d_ab = solution.minDistanceDP2D(a, b);
    int d_bc = solution.minDistanceDP2D(b, c);
    
    EXPECT_LE(d_ac, d_ab + d_bc) << "Triangle inequality should hold";
}

// Performance tests
TEST_F(EditDistanceTest, PerformanceComparison) {
    std::string word1 = "abcdefghijklmnop";
    std::string word2 = "zyxwvutsrqponmlk";
    
    // Test DP 2D
    auto start = std::chrono::high_resolution_clock::now();
    int result1 = solution.minDistanceDP2D(word1, word2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test DP 1D  
    start = std::chrono::high_resolution_clock::now();
    int result2 = solution.minDistanceDP1D(word1, word2);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test memoization
    start = std::chrono::high_resolution_clock::now();
    int result3 = solution.minDistanceMemo(word1, word2);
    end = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Results should match
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, result3);
    
    // All should complete reasonably quickly
    EXPECT_LT(duration1.count(), 1000) << "DP 2D should be fast";
    EXPECT_LT(duration2.count(), 1000) << "DP 1D should be fast";
    EXPECT_LT(duration3.count(), 2000) << "Memoization should be reasonable";
    
    // 1D should be at least as fast as 2D
    // (Not always true due to system variation, but generally expected)
}

TEST_F(EditDistanceTest, LargeInputTest) {
    // Test with moderately large inputs
    std::string word1(50, 'a');
    std::string word2(50, 'b');
    
    // Should be able to handle this quickly
    auto start = std::chrono::high_resolution_clock::now();
    int result = solution.minDistanceDP1D(word1, word2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_EQ(result, 50); // All replacements
    EXPECT_LT(duration.count(), 100) << "Should handle large input efficiently";
}

// Algorithm-specific tests
TEST_F(EditDistanceTest, BFSSmallInputsOnly) {
    // BFS only tested with very small inputs due to exponential space
    testAllApproaches("", "", 0);
    testAllApproaches("a", "", 1);
    testAllApproaches("", "a", 1);
    testAllApproaches("a", "b", 1);
    testAllApproaches("ab", "ba", 2);
    testAllApproaches("abc", "def", 3);
}

TEST_F(EditDistanceTest, IterativeDeepeningSpecific) {
    // Test iterative deepening with known distances
    EXPECT_EQ(solution.minDistanceIterativeDeepening("abc", "abc"), 0);
    EXPECT_EQ(solution.minDistanceIterativeDeepening("a", "b"), 1);
    EXPECT_EQ(solution.minDistanceIterativeDeepening("ab", "ba"), 2);
    EXPECT_EQ(solution.minDistanceIterativeDeepening("cat", "dog"), 3);
}

TEST_F(EditDistanceTest, AStarSpecific) {
    // Test A* search with various inputs
    EXPECT_EQ(solution.minDistanceAStar("kitten", "sitting"), 3);
    EXPECT_EQ(solution.minDistanceAStar("flaw", "lawn"), 2);
    EXPECT_EQ(solution.minDistanceAStar("gumbo", "gambol"), 2);
}

TEST_F(EditDistanceTest, SpaceOptimizationVerification) {
    // Verify 1D DP produces same results as 2D
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"", ""},
        {"a", ""},
        {"", "b"},
        {"cat", "dog"},
        {"kitten", "sitting"},
        {"intention", "execution"},
        {"horse", "ros"}
    };
    
    for (const auto& testCase : testCases) {
        int result2D = solution.minDistanceDP2D(testCase.first, testCase.second);
        int result1D = solution.minDistanceDP1D(testCase.first, testCase.second);
        EXPECT_EQ(result2D, result1D) << "1D and 2D DP should match for '" 
                                     << testCase.first << "' -> '" << testCase.second << "'";
    }
}

TEST_F(EditDistanceTest, MemoizationConsistency) {
    // Verify memoization produces same results
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"abc", "def"},
        {"hello", "world"},
        {"programming", "algorithm"},
        {"dynamic", "programming"}
    };
    
    for (const auto& testCase : testCases) {
        int resultDP = solution.minDistanceDP2D(testCase.first, testCase.second);
        int resultMemo = solution.minDistanceMemo(testCase.first, testCase.second);
        EXPECT_EQ(resultDP, resultMemo) << "DP and memoization should match for '" 
                                       << testCase.first << "' -> '" << testCase.second << "'";
    }
}

TEST_F(EditDistanceTest, WorstCaseScenario) {
    // Completely different strings of same length (all replacements)
    std::string word1 = "aaaaaaaaaa";
    std::string word2 = "bbbbbbbbbb";
    
    testMainApproaches(word1, word2, 10);
    
    // Completely different lengths (many insertions/deletions)
    std::string short_str = "abc";
    std::string long_str = "defghijklmnop";
    
    testMainApproaches(short_str, long_str, 13); // Delete 3, insert 13 = replace 3 + insert 10 = 13
}

TEST_F(EditDistanceTest, RealWorldExamples) {
    // Real-world word transformations
    testMainApproaches("color", "colour", 1);    // Insert 'u'
    testMainApproaches("center", "centre", 2);   // Replace 'e' with 'r', replace 'r' with 'e'  
    testMainApproaches("gray", "grey", 1);       // Replace 'a' with 'e'
    testMainApproaches("theater", "theatre", 2); // Insert 'r', replace 'r' with 'e'
}

TEST_F(EditDistanceTest, ConsistencyAcrossApproaches) {
    // Test various cases to ensure all approaches agree
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"", ""},
        {"a", "b"}, 
        {"ab", "ba"},
        {"abc", "def"},
        {"hello", "world"},
        {"kitten", "sitting"},
        {"sunday", "saturday"},
        {"intention", "execution"}
    };
    
    for (const auto& testCase : testCases) {
        int expected = solution.minDistanceDP2D(testCase.first, testCase.second);
        testMainApproaches(testCase.first, testCase.second, expected);
    }
}