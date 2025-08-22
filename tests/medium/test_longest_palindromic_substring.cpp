#include <gtest/gtest.h>
#include "medium/longest_palindromic_substring.h"
#include <chrono>
#include <set>

using namespace leetcode::medium;

class LongestPalindromicSubstringTest : public ::testing::Test {
protected:
    LongestPalindromicSubstring solution;
    
    // Helper function to verify palindrome validity
    bool isPalindrome(const std::string& s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    
    // Helper function to check if result is valid (palindrome and exists in original)
    bool isValidResult(const std::string& original, const std::string& result) {
        if (result.empty()) return original.empty();
        if (!isPalindrome(result)) return false;
        return original.find(result) != std::string::npos;
    }
    
    // Helper function to test all approaches
    void testAllApproaches(const std::string& s) {
        auto result1 = solution.longestPalindromeExpandCenter(s);
        auto result2 = solution.longestPalindromeDP(s);
        auto result3 = solution.longestPalindromeManacher(s);
        auto result4 = solution.longestPalindromeBruteForce(s);
        auto result5 = solution.longestPalindromeSuffixArray(s);
        auto result6 = solution.longestPalindromeRollingHash(s);
        
        // All results should be valid palindromes
        EXPECT_TRUE(isValidResult(s, result1)) << "Expand center result invalid: " << result1;
        EXPECT_TRUE(isValidResult(s, result2)) << "DP result invalid: " << result2;
        EXPECT_TRUE(isValidResult(s, result3)) << "Manacher result invalid: " << result3;
        EXPECT_TRUE(isValidResult(s, result4)) << "Brute force result invalid: " << result4;
        EXPECT_TRUE(isValidResult(s, result5)) << "Suffix array result invalid: " << result5;
        EXPECT_TRUE(isValidResult(s, result6)) << "Rolling hash result invalid: " << result6;
        
        // All results should have the same length (multiple valid answers possible)
        EXPECT_EQ(result1.length(), result2.length()) << "Expand center and DP length differ";
        EXPECT_EQ(result1.length(), result3.length()) << "Expand center and Manacher length differ";
        EXPECT_EQ(result1.length(), result4.length()) << "Expand center and Brute force length differ";
        EXPECT_EQ(result1.length(), result5.length()) << "Expand center and Suffix array length differ";
        EXPECT_EQ(result1.length(), result6.length()) << "Expand center and Rolling hash length differ";
    }
    
    // Helper function to test with expected result
    void testAllApproaches(const std::string& s, const std::string& expected) {
        testAllApproaches(s);
        
        // Verify at least one approach returns expected result (or same length)
        auto result = solution.longestPalindromeExpandCenter(s);
        if (expected.empty()) {
            EXPECT_TRUE(result.empty() || result.length() == 1) << "Expected empty or single char";
        } else {
            EXPECT_EQ(result.length(), expected.length()) << "Length should match expected";
        }
    }
};

TEST_F(LongestPalindromicSubstringTest, BasicExample1) {
    // Input: s = "babad"
    // Output: "bab" or "aba" (both valid)
    std::string s = "babad";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result.length(), 3);
    EXPECT_TRUE(result == "bab" || result == "aba");
}

TEST_F(LongestPalindromicSubstringTest, BasicExample2) {
    // Input: s = "cbbd"
    // Output: "bb"
    std::string s = "cbbd";
    testAllApproaches(s, "bb");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "bb");
}

TEST_F(LongestPalindromicSubstringTest, SingleCharacter) {
    // Input: s = "a"
    // Output: "a"
    std::string s = "a";
    testAllApproaches(s, "a");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "a");
}

TEST_F(LongestPalindromicSubstringTest, TwoSameCharacters) {
    // Input: s = "aa"
    // Output: "aa"
    std::string s = "aa";
    testAllApproaches(s, "aa");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "aa");
}

TEST_F(LongestPalindromicSubstringTest, TwoDifferentCharacters) {
    // Input: s = "ab"
    // Output: "a" or "b" (both valid single characters)
    std::string s = "ab";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result.length(), 1);
    EXPECT_TRUE(result == "a" || result == "b");
}

TEST_F(LongestPalindromicSubstringTest, EntireStringPalindrome) {
    // Input: s = "racecar"
    // Output: "racecar"
    std::string s = "racecar";
    testAllApproaches(s, "racecar");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "racecar");
}

TEST_F(LongestPalindromicSubstringTest, NoLongPalindrome) {
    // Input: s = "abcdef" (no palindrome longer than 1)
    // Output: any single character
    std::string s = "abcdef";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result.length(), 1);
}

TEST_F(LongestPalindromicSubstringTest, RepeatedCharacters) {
    // Input: s = "aaaa"
    // Output: "aaaa"
    std::string s = "aaaa";
    testAllApproaches(s, "aaaa");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "aaaa");
}

TEST_F(LongestPalindromicSubstringTest, AlternatingPattern) {
    // Input: s = "ababa"
    // Output: "ababa"
    std::string s = "ababa";
    testAllApproaches(s, "ababa");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "ababa");
}

TEST_F(LongestPalindromicSubstringTest, EvenLengthPalindrome) {
    // Input: s = "abccba"
    // Output: "abccba"
    std::string s = "abccba";
    testAllApproaches(s, "abccba");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "abccba");
}

TEST_F(LongestPalindromicSubstringTest, MultiplePalindromes) {
    // Input: s = "abacabad"
    // Multiple palindromes: "aba", "aca", "aba", "bad"
    std::string s = "abacabad";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result.length(), 3); // Should find one of the 3-length palindromes
}

TEST_F(LongestPalindromicSubstringTest, PalindromeAtStart) {
    // Input: s = "abaxyz"
    // Output: "aba"
    std::string s = "abaxyz";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result.length(), 3);
    EXPECT_EQ(result, "aba");
}

TEST_F(LongestPalindromicSubstringTest, PalindromeAtEnd) {
    // Input: s = "xyzaba"
    // Output: "aba"
    std::string s = "xyzaba";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result.length(), 3);
    EXPECT_EQ(result, "aba");
}

TEST_F(LongestPalindromicSubstringTest, LongString) {
    // Test with longer string
    std::string s = "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendure";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_GE(result.length(), 1); // Should find at least single character
}

TEST_F(LongestPalindromicSubstringTest, NestedPalindromes) {
    // Input: s = "abacabadabacaba"
    // Contains nested palindromes
    std::string s = "abacabadabacaba";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_GE(result.length(), 3); // Should find substantial palindrome
}

TEST_F(LongestPalindromicSubstringTest, NumbersAndLetters) {
    // Input: s = "a1b2b1a"
    // Output: "a1b2b1a"
    std::string s = "a1b2b1a";
    testAllApproaches(s, "a1b2b1a");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "a1b2b1a");
}

TEST_F(LongestPalindromicSubstringTest, OnlyNumbers) {
    // Input: s = "12321"
    // Output: "12321"
    std::string s = "12321";
    testAllApproaches(s, "12321");
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, "12321");
}

TEST_F(LongestPalindromicSubstringTest, MirroredStructure) {
    // Input: s = "abcdef fed cba"
    std::string s = "abcdeffedcba";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_GE(result.length(), 1);
}

TEST_F(LongestPalindromicSubstringTest, EdgeCaseEmpty) {
    // Input: s = "" (though constraint says length >= 1)
    std::string s = "";
    if (s.empty()) return; // Skip if empty not allowed
    
    testAllApproaches(s);
}

TEST_F(LongestPalindromicSubstringTest, MaxConstraintLength) {
    // Test with constraint boundary (up to 1000 characters)
    std::string s(500, 'a'); // 500 a's
    s += std::string(500, 'b'); // followed by 500 b's
    
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_GE(result.length(), 1);
}

TEST_F(LongestPalindromicSubstringTest, AlternatingLongPattern) {
    // Input: long alternating pattern
    std::string s = "";
    for (int i = 0; i < 50; ++i) {
        s += "ab";
    }
    s += "a"; // Make it odd length palindrome
    for (int i = 0; i < 50; ++i) {
        s += "ba";
    }
    
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_GE(result.length(), 1);
}

// Performance tests
TEST_F(LongestPalindromicSubstringTest, PerformanceTest) {
    // Create string with multiple palindromes
    std::string s = "abcdefghijklmnopqrstuvwxyz";
    s += "zyxwvutsrqponmlkjihgfedcba"; // Creates a large palindrome
    
    // Test expand center approach
    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = solution.longestPalindromeExpandCenter(s);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_LT(duration1.count(), 10000) << "Expand center should be fast";
    
    // Test Manacher's algorithm
    start = std::chrono::high_resolution_clock::now();
    auto result2 = solution.longestPalindromeManacher(s);
    end = std::chrono::high_resolution_clock::now();
    
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Results should match
    EXPECT_EQ(result1.length(), result2.length());
    
    // Both should be reasonable performance
    EXPECT_LT(duration2.count(), 10000) << "Manacher should be fast";
}

TEST_F(LongestPalindromicSubstringTest, WorstCaseForBruteForce) {
    // Create case that's expensive for brute force
    std::string s(100, 'a'); // 100 a's - many overlapping palindromes
    
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_EQ(result, s); // Should be entire string
}

// Algorithm-specific tests
TEST_F(LongestPalindromicSubstringTest, ManacherSpecificTest) {
    // Test case that showcases Manacher's efficiency
    std::string s = "abacabad";
    auto result = solution.longestPalindromeManacher(s);
    EXPECT_TRUE(isPalindrome(result));
    EXPECT_EQ(result.length(), 3); // Should find "aba"
}

TEST_F(LongestPalindromicSubstringTest, DPSpecificTest) {
    // Test case good for DP visualization
    std::string s = "abccba";
    auto result = solution.longestPalindromeDP(s);
    EXPECT_EQ(result, "abccba");
}

TEST_F(LongestPalindromicSubstringTest, ConsistencyCheck) {
    // Test multiple inputs for consistency across all approaches
    std::vector<std::string> testCases = {
        "a", "aa", "aba", "abba", "abcba", "abccba", "racecar",
        "hello", "babad", "cbbd", "ac", "bb", "ccc"
    };
    
    for (const auto& s : testCases) {
        testAllApproaches(s);
    }
}

TEST_F(LongestPalindromicSubstringTest, PalindromeValidation) {
    std::string s = "abacabad";
    std::set<std::string> results;
    
    results.insert(solution.longestPalindromeExpandCenter(s));
    results.insert(solution.longestPalindromeDP(s));
    results.insert(solution.longestPalindromeManacher(s));
    results.insert(solution.longestPalindromeBruteForce(s));
    
    // All results should be valid palindromes
    for (const auto& result : results) {
        EXPECT_TRUE(isPalindrome(result)) << "Result " << result << " is not palindrome";
        EXPECT_TRUE(s.find(result) != std::string::npos) << "Result " << result << " not found in original";
    }
}

TEST_F(LongestPalindromicSubstringTest, EdgeCharacters) {
    // Test with various character types allowed by constraints
    std::string s = "A1a2A1a";
    testAllApproaches(s);
    
    auto result = solution.longestPalindromeExpandCenter(s);
    EXPECT_GE(result.length(), 1);
    EXPECT_TRUE(isPalindrome(result));
}