#include <gtest/gtest.h>
#include "medium/group_anagrams.h"
#include <algorithm>
#include <set>
#include <chrono>

using namespace leetcode::medium;

class GroupAnagramsTest : public ::testing::Test {
protected:
    GroupAnagrams solution;
    
    // Helper function to normalize results for comparison (order-independent)
    void normalizeResult(std::vector<std::vector<std::string>>& result) {
        // Sort each group internally
        for (auto& group : result) {
            std::sort(group.begin(), group.end());
        }
        // Sort groups by their first element
        std::sort(result.begin(), result.end());
    }
    
    bool areResultsEquivalent(std::vector<std::vector<std::string>> result1, 
                             std::vector<std::vector<std::string>> result2) {
        normalizeResult(result1);
        normalizeResult(result2);
        return result1 == result2;
    }
    
    // Helper function to verify result correctness
    bool isValidAnagramGrouping(const std::vector<std::vector<std::string>>& result, 
                               const std::vector<std::string>& original) {
        // Count total strings in result
        int totalCount = 0;
        std::set<std::string> resultStrings;
        
        for (const auto& group : result) {
            if (group.empty()) return false; // No empty groups allowed
            
            totalCount += group.size();
            
            // Check if all strings in group are anagrams of each other
            std::string firstSorted = group[0];
            std::sort(firstSorted.begin(), firstSorted.end());
            
            for (const std::string& str : group) {
                std::string currentSorted = str;
                std::sort(currentSorted.begin(), currentSorted.end());
                
                if (currentSorted != firstSorted) {
                    return false; // Not anagrams
                }
                
                resultStrings.insert(str);
            }
        }
        
        // Check if all original strings are present
        if (totalCount != original.size()) return false;
        
        std::set<std::string> originalSet(original.begin(), original.end());
        return resultStrings == originalSet;
    }
    
    // Helper function to test all approaches
    void testAllApproaches(std::vector<std::string> strs) {
        std::vector<std::string> strs1 = strs, strs2 = strs, strs3 = strs,
                               strs4 = strs, strs5 = strs, strs6 = strs;
        
        auto result1 = solution.groupAnagramsSorting(strs1);
        auto result2 = solution.groupAnagramsFrequency(strs2);
        auto result3 = solution.groupAnagramsPrime(strs3);
        auto result4 = solution.groupAnagramsArray(strs4);
        auto result5 = solution.groupAnagramsTrie(strs5);
        auto result6 = solution.groupAnagramsRollingHash(strs6);
        
        EXPECT_TRUE(isValidAnagramGrouping(result1, strs)) << "Sorting approach failed validation";
        EXPECT_TRUE(isValidAnagramGrouping(result2, strs)) << "Frequency approach failed validation";
        EXPECT_TRUE(isValidAnagramGrouping(result3, strs)) << "Prime approach failed validation";
        EXPECT_TRUE(isValidAnagramGrouping(result4, strs)) << "Array approach failed validation";
        EXPECT_TRUE(isValidAnagramGrouping(result5, strs)) << "Trie approach failed validation";
        EXPECT_TRUE(isValidAnagramGrouping(result6, strs)) << "Rolling hash approach failed validation";
        
        // All approaches should produce equivalent results
        EXPECT_TRUE(areResultsEquivalent(result1, result2)) << "Sorting and Frequency differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result3)) << "Sorting and Prime differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result4)) << "Sorting and Array differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result5)) << "Sorting and Trie differ";
        EXPECT_TRUE(areResultsEquivalent(result1, result6)) << "Sorting and Rolling Hash differ";
    }
};

TEST_F(GroupAnagramsTest, BasicExample1) {
    // Input: strs = ["eat","tea","tan","ate","nat","bat"]
    // Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
    std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 3); // Three anagram groups
}

TEST_F(GroupAnagramsTest, BasicExample2) {
    // Input: strs = [""]
    // Output: [[""]]
    std::vector<std::string> strs = {""};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].size(), 1);
    EXPECT_EQ(result[0][0], "");
}

TEST_F(GroupAnagramsTest, BasicExample3) {
    // Input: strs = ["a"]
    // Output: [["a"]]
    std::vector<std::string> strs = {"a"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].size(), 1);
    EXPECT_EQ(result[0][0], "a");
}

TEST_F(GroupAnagramsTest, NoAnagrams) {
    // All strings are different, no anagrams
    std::vector<std::string> strs = {"abc", "def", "ghi"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 3); // Each string in its own group
    for (const auto& group : result) {
        EXPECT_EQ(group.size(), 1);
    }
}

TEST_F(GroupAnagramsTest, AllAnagrams) {
    // All strings are anagrams of each other
    std::vector<std::string> strs = {"abc", "bca", "cab", "acb", "bac", "cba"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 1); // All in one group
    EXPECT_EQ(result[0].size(), 6);
}

TEST_F(GroupAnagramsTest, DuplicateStrings) {
    // Input has duplicate strings
    std::vector<std::string> strs = {"eat", "tea", "eat", "tea", "ate"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 1); // All are anagrams
    EXPECT_EQ(result[0].size(), 5); // All 5 strings including duplicates
}

TEST_F(GroupAnagramsTest, SingleCharacters) {
    // Single character strings
    std::vector<std::string> strs = {"a", "b", "a", "c", "b"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 3); // Three groups: a, b, c
}

TEST_F(GroupAnagramsTest, EmptyAndNonEmpty) {
    // Mix of empty and non-empty strings
    std::vector<std::string> strs = {"", "a", "", "b", "ba", "ab"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 4); // Groups: [""], ["a"], ["b"], ["ba","ab"]
}

TEST_F(GroupAnagramsTest, LongStrings) {
    // Longer strings with anagrams
    std::vector<std::string> strs = {
        "listen", "silent", "enlist",
        "hello", "world", 
        "god", "dog", "good"
    };
    testAllApproaches(strs);
}

TEST_F(GroupAnagramsTest, RepeatedCharacters) {
    // Strings with repeated characters
    std::vector<std::string> strs = {"aab", "aba", "baa", "abc", "bca"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 2); // Two groups: aab variants and abc variants
}

TEST_F(GroupAnagramsTest, AllSameCharacter) {
    // Strings with all same character
    std::vector<std::string> strs = {"aa", "aa", "aaa", "a"};
    testAllApproaches(strs);
}

TEST_F(GroupAnagramsTest, MixedLengths) {
    // Strings of different lengths
    std::vector<std::string> strs = {
        "a", "ab", "abc", "bca", "ca", "ac", "ba"
    };
    testAllApproaches(strs);
}

TEST_F(GroupAnagramsTest, LargeAnagramGroups) {
    // Large groups of anagrams
    std::vector<std::string> strs;
    std::string base = "abc";
    
    // Generate all permutations of "abc"
    do {
        strs.push_back(base);
    } while (std::next_permutation(base.begin(), base.end()));
    
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 1); // All permutations in one group
    EXPECT_EQ(result[0].size(), 6); // 3! = 6 permutations
}

TEST_F(GroupAnagramsTest, AlphabeticalOrder) {
    // Test with alphabetically ordered strings
    std::vector<std::string> strs = {"abc", "def", "ghi", "cba", "fed", "ihg"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 3); // Three anagram pairs
}

TEST_F(GroupAnagramsTest, MaxLength) {
    // Test with maximum length strings (up to 100 characters)
    std::string longStr1(100, 'a');
    std::string longStr2 = longStr1;
    std::reverse(longStr2.begin(), longStr2.end()); // Still all 'a's, so anagram
    
    std::vector<std::string> strs = {longStr1, longStr2, "abc", "bca"};
    testAllApproaches(strs);
}

TEST_F(GroupAnagramsTest, AllDifferentLengths) {
    // Each string has different length
    std::vector<std::string> strs = {"", "a", "ab", "abc", "abcd", "abcde"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 6); // Each string in its own group
}

// Test for correctness of anagram detection
TEST_F(GroupAnagramsTest, AnagramDetectionTest) {
    std::vector<std::string> strs = {"abc", "bca", "xyz", "zyx", "def"};
    auto result = solution.groupAnagramsSorting(strs);
    
    EXPECT_EQ(result.size(), 3); // Three groups
    
    // Find and verify each group
    bool foundAbcGroup = false, foundXyzGroup = false, foundDefGroup = false;
    
    for (const auto& group : result) {
        if (group.size() == 2) {
            std::string sorted1 = group[0], sorted2 = group[1];
            std::sort(sorted1.begin(), sorted1.end());
            std::sort(sorted2.begin(), sorted2.end());
            
            if (sorted1 == "abc" && sorted2 == "abc") {
                foundAbcGroup = true;
            } else if (sorted1 == "xyz" && sorted2 == "xyz") {
                foundXyzGroup = true;
            }
        } else if (group.size() == 1 && group[0] == "def") {
            foundDefGroup = true;
        }
    }
    
    EXPECT_TRUE(foundAbcGroup && foundXyzGroup && foundDefGroup);
}

// Performance test with many strings
TEST_F(GroupAnagramsTest, PerformanceTest) {
    std::vector<std::string> strs;
    
    // Create 1000 strings with various anagram patterns
    for (int i = 0; i < 1000; ++i) {
        if (i % 3 == 0) strs.push_back("abc");
        else if (i % 3 == 1) strs.push_back("bca");
        else strs.push_back("cab");
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = solution.groupAnagramsSorting(strs);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    EXPECT_LT(duration.count(), 100) << "Algorithm should complete within 100ms for 1000 strings";
    
    EXPECT_EQ(result.size(), 1); // All anagrams, one group
    EXPECT_EQ(result[0].size(), 1000);
}

// Test time complexity comparison
TEST_F(GroupAnagramsTest, TimeComplexityTest) {
    // Compare sorting vs frequency approaches
    std::vector<std::string> strs;
    std::string longBase = "abcdefghijklmnopqrstuvwxyz"; // 26 characters
    
    for (int i = 0; i < 100; ++i) {
        strs.push_back(longBase);
        std::next_permutation(longBase.begin(), longBase.end());
    }
    
    // Test frequency approach (should be faster for long strings)
    auto start1 = std::chrono::high_resolution_clock::now();
    auto result1 = solution.groupAnagramsFrequency(strs);
    auto end1 = std::chrono::high_resolution_clock::now();
    
    // Test sorting approach
    auto start2 = std::chrono::high_resolution_clock::now();
    auto result2 = solution.groupAnagramsSorting(strs);
    auto end2 = std::chrono::high_resolution_clock::now();
    
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    
    // Both should produce same results
    EXPECT_TRUE(areResultsEquivalent(result1, result2));
    
    // Frequency approach should generally be faster for long strings
    // (This is not guaranteed in all cases due to system variations)
    EXPECT_LT(duration1.count(), duration2.count() * 2) << "Frequency approach should be competitive";
}

// Test result completeness
TEST_F(GroupAnagramsTest, CompletenessTest) {
    std::vector<std::string> strs = {"abc", "def", "bca", "fed", "xyz", "cab"};
    auto result = solution.groupAnagramsSorting(strs);
    
    // Collect all strings from result
    std::set<std::string> resultStrings;
    for (const auto& group : result) {
        for (const std::string& str : group) {
            resultStrings.insert(str);
        }
    }
    
    // Should match original input exactly
    std::set<std::string> originalStrings(strs.begin(), strs.end());
    EXPECT_EQ(resultStrings, originalStrings) << "Result should contain all original strings";
}

// Test no empty groups
TEST_F(GroupAnagramsTest, NoEmptyGroupsTest) {
    std::vector<std::string> strs = {"a", "b", "c", "abc", "bca"};
    auto result = solution.groupAnagramsSorting(strs);
    
    for (const auto& group : result) {
        EXPECT_FALSE(group.empty()) << "No group should be empty";
    }
}

// Test with special characters (edge case - but problem states lowercase only)
TEST_F(GroupAnagramsTest, LowercaseOnlyTest) {
    // Test boundary of lowercase letters
    std::vector<std::string> strs = {"az", "za", "by", "yb"};
    testAllApproaches(strs);
    
    auto result = solution.groupAnagramsSorting(strs);
    EXPECT_EQ(result.size(), 2); // Two anagram pairs
}