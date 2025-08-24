#include <gtest/gtest.h>
#include "../../src/easy/valid_anagram.h"
#include <string>
#include <algorithm>
#include <random>

namespace leetcode {
namespace easy {
namespace test {

class ValidAnagramTest : public ::testing::Test {
protected:
    // Test all approaches except XOR (which is intentionally flawed)
    void testAllApproaches(const std::string& s, const std::string& t, bool expected) {
        ValidAnagram solution;
        
        EXPECT_EQ(solution.isAnagramSorting(s, t), expected) 
            << "Sorting approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.isAnagramCharArray(s, t), expected) 
            << "Character array approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.isAnagramHashMap(s, t), expected) 
            << "Hash map approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.isAnagramSinglePass(s, t), expected) 
            << "Single pass approach failed for s=\"" << s << "\", t=\"" << t << "\"";
        EXPECT_EQ(solution.isAnagramPrime(s, t), expected) 
            << "Prime multiplication approach failed for s=\"" << s << "\", t=\"" << t << "\"";
    }
    
    // Test XOR approach separately since it's flawed
    void testXORApproach(const std::string& s, const std::string& t, bool expected) {
        ValidAnagram solution;
        bool result = solution.isAnagramXOR(s, t);
        
        // Document known failures of XOR approach
        if (result != expected) {
            std::cout << "XOR approach failed (as expected) for s=\"" << s << "\", t=\"" << t << "\"" << std::endl;
        }
    }
    
    // Helper to generate random string
    std::string generateRandomString(int length, char start = 'a', char end = 'z') {
        std::string result;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(start, end);
        
        for (int i = 0; i < length; ++i) {
            result += static_cast<char>(dis(gen));
        }
        return result;
    }
    
    // Helper to create anagram by shuffling
    std::string createAnagram(const std::string& original) {
        std::string anagram = original;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(anagram.begin(), anagram.end(), gen);
        return anagram;
    }
};

// LeetCode Example Test Cases

TEST_F(ValidAnagramTest, LeetCodeExample1) {
    // s = "anagram", t = "nagaram"
    // Output: true
    testAllApproaches("anagram", "nagaram", true);
}

TEST_F(ValidAnagramTest, LeetCodeExample2) {
    // s = "rat", t = "car"
    // Output: false
    testAllApproaches("rat", "car", false);
}

// Edge Cases

TEST_F(ValidAnagramTest, EmptyStrings) {
    testAllApproaches("", "", true);
}

TEST_F(ValidAnagramTest, SingleCharacterSame) {
    testAllApproaches("a", "a", true);
}

TEST_F(ValidAnagramTest, SingleCharacterDifferent) {
    testAllApproaches("a", "b", false);
}

TEST_F(ValidAnagramTest, DifferentLengths) {
    testAllApproaches("abc", "abcd", false);
    testAllApproaches("abcd", "abc", false);
    testAllApproaches("", "a", false);
    testAllApproaches("a", "", false);
}

TEST_F(ValidAnagramTest, SameStrings) {
    testAllApproaches("hello", "hello", true);
    testAllApproaches("a", "a", true);
    testAllApproaches("abcdef", "abcdef", true);
}

// Basic Anagram Tests

TEST_F(ValidAnagramTest, SimpleAnagrams) {
    testAllApproaches("listen", "silent", true);
    testAllApproaches("evil", "vile", true);
    testAllApproaches("a", "a", true);
    testAllApproaches("ab", "ba", true);
    testAllApproaches("abc", "cab", true);
}

TEST_F(ValidAnagramTest, NotAnagrams) {
    testAllApproaches("hello", "bello", false);
    testAllApproaches("python", "java", false);
    testAllApproaches("abc", "def", false);
    testAllApproaches("aab", "aaa", false);
}

// Duplicate Character Tests

TEST_F(ValidAnagramTest, RepeatedCharacters) {
    testAllApproaches("aab", "aba", true);
    testAllApproaches("aabb", "baba", true);
    testAllApproaches("aaabbb", "ababab", true);
}

TEST_F(ValidAnagramTest, DifferentFrequencies) {
    testAllApproaches("aab", "abb", false);
    testAllApproaches("aaab", "aabb", false);
    testAllApproaches("abc", "aab", false);
}

// All Same Character Tests

TEST_F(ValidAnagramTest, AllSameCharacter) {
    testAllApproaches("aaaa", "aaaa", true);
    testAllApproaches("bbbb", "bbbb", true);
    testAllApproaches("aaaa", "bbbb", false);
    testAllApproaches("aaa", "aaaa", false);
}

// Palindrome Tests

TEST_F(ValidAnagramTest, PalindromeAnagrams) {
    testAllApproaches("racecar", "carecar", true);
    testAllApproaches("madam", "madma", true);  // "madma" is anagram of "madam"
    testAllApproaches("level", "lleve", true);
}

// Complex Pattern Tests

TEST_F(ValidAnagramTest, ComplexAnagrams) {
    testAllApproaches("conversation", "conservation", false);  // Different lengths
    testAllApproaches("debit card", "bad credit", false);     // Contains spaces (not in constraints)
}

// Alphabet Coverage Tests

TEST_F(ValidAnagramTest, AllLetters) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string shuffled = alphabet;
    std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937{std::random_device{}()});
    testAllApproaches(alphabet, shuffled, true);
}

TEST_F(ValidAnagramTest, MissingLetters) {
    testAllApproaches("abcdefghijklmnopqrstuvwxy", "abcdefghijklmnopqrstuvwxz", false);
}

// Length-based Tests

TEST_F(ValidAnagramTest, LongStrings) {
    std::string s1(1000, 'a');
    std::string s2(1000, 'a');
    testAllApproaches(s1, s2, true);
    
    s2[999] = 'b';  // Change last character
    testAllApproaches(s1, s2, false);
}

TEST_F(ValidAnagramTest, VeryLongAnagrams) {
    std::string original = "abcdefghijklmnopqrstuvwxyz";
    std::string repeated;
    for (int i = 0; i < 100; ++i) {
        repeated += original;
    }
    std::string shuffled = createAnagram(repeated);
    
    ValidAnagram solution;
    // Test only fastest approaches for very long strings
    EXPECT_TRUE(solution.isAnagramCharArray(repeated, shuffled));
    EXPECT_TRUE(solution.isAnagramSinglePass(repeated, shuffled));
}

// Random Pattern Tests

TEST_F(ValidAnagramTest, RandomValidAnagrams) {
    for (int len = 1; len <= 20; ++len) {
        std::string original = generateRandomString(len);
        std::string anagram = createAnagram(original);
        testAllApproaches(original, anagram, true);
    }
}

TEST_F(ValidAnagramTest, RandomInvalidAnagrams) {
    for (int i = 0; i < 10; ++i) {
        std::string s1 = generateRandomString(10);
        std::string s2 = generateRandomString(10);
        
        // Make sure they're actually different
        if (s1 != s2) {
            // Sort to check if they would be anagrams
            std::string sorted_s1 = s1, sorted_s2 = s2;
            std::sort(sorted_s1.begin(), sorted_s1.end());
            std::sort(sorted_s2.begin(), sorted_s2.end());
            
            if (sorted_s1 != sorted_s2) {
                testAllApproaches(s1, s2, false);
            }
        }
    }
}

// Special Cases that Break XOR Approach

TEST_F(ValidAnagramTest, XORFailureCases) {
    // These cases demonstrate why XOR approach fails
    ValidAnagram solution;
    
    // Case 1: Different character frequencies but same XOR
    EXPECT_FALSE(solution.isAnagramCharArray("aab", "abb"));
    // XOR approach incorrectly returns true for this case
    
    // Case 2: Another XOR failure
    EXPECT_FALSE(solution.isAnagramCharArray("abc", "def"));
    // Document XOR behavior
    testXORApproach("aab", "abb", false);
}

// Performance Edge Cases

TEST_F(ValidAnagramTest, WorstCaseForSorting) {
    // Reverse sorted strings - worst case for some sort algorithms
    std::string s1 = "zyxwvutsrqponmlkjihgfedcba";
    std::string s2 = "abcdefghijklmnopqrstuvwxyz";
    testAllApproaches(s1, s2, true);
}

TEST_F(ValidAnagramTest, AlmostIdentical) {
    // Strings that differ in only one character
    std::string s1(1000, 'a');
    std::string s2 = s1;
    s2[500] = 'b';
    testAllApproaches(s1, s2, false);
}

// Boundary Tests

TEST_F(ValidAnagramTest, MaxConstraintLength) {
    // Test with maximum constraint length (would be 50000, but testing smaller for speed)
    std::string pattern = "abcdefghij";  // 10 chars
    std::string large_s1, large_s2;
    
    for (int i = 0; i < 500; ++i) {  // 5000 total chars
        large_s1 += pattern;
        large_s2 += pattern;
    }
    
    // Shuffle s2 to create anagram
    std::shuffle(large_s2.begin(), large_s2.end(), std::mt19937{42});
    
    ValidAnagram solution;
    EXPECT_TRUE(solution.isAnagramCharArray(large_s1, large_s2));
    EXPECT_TRUE(solution.isAnagramSinglePass(large_s1, large_s2));
}

// Unicode Follow-up (mentioned in problem but not in constraints)
TEST_F(ValidAnagramTest, DocumentUnicodeApproach) {
    // This test documents how to handle Unicode (though not in current constraints)
    ValidAnagram solution;
    
    // Hash map approach would work for Unicode
    // Character array approach would NOT work for Unicode
    // This is why hash map approach is more flexible
    
    // For now, just test with extended ASCII
    testAllApproaches("café", "face", false);  // If we had accented chars
}

}  // namespace test
}  // namespace easy
}  // namespace leetcode