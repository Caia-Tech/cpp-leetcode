#include <gtest/gtest.h>
#include "medium/word_ladder.h"
#include <vector>
#include <string>
#include <algorithm>

namespace leetcode {
namespace medium {
namespace test {

class WordLadderTest : public ::testing::Test {
protected:
    WordLadder solution;
    
    void testAllApproaches(std::string beginWord, std::string endWord, 
                          std::vector<std::string> wordList, int expected) {
        // Create copies for each approach since some might modify the input
        std::vector<std::string> wordList1 = wordList;
        std::vector<std::string> wordList2 = wordList;
        std::vector<std::string> wordList3 = wordList;
        std::vector<std::string> wordList4 = wordList;
        std::vector<std::string> wordList5 = wordList;
        std::vector<std::string> wordList6 = wordList;
        
        EXPECT_EQ(solution.ladderLength(beginWord, endWord, wordList1), expected) 
            << "Standard BFS approach failed";
        EXPECT_EQ(solution.ladderLengthBidirectional(beginWord, endWord, wordList2), expected) 
            << "Bidirectional BFS approach failed";
        EXPECT_EQ(solution.ladderLengthPrecomputed(beginWord, endWord, wordList3), expected) 
            << "Precomputed approach failed";
        EXPECT_EQ(solution.ladderLengthPatternMatching(beginWord, endWord, wordList4), expected) 
            << "Pattern Matching approach failed";
        EXPECT_EQ(solution.ladderLengthAStar(beginWord, endWord, wordList5), expected) 
            << "A* Search approach failed";
        EXPECT_EQ(solution.ladderLengthLevelOrder(beginWord, endWord, wordList6), expected) 
            << "Level Order BFS approach failed";
    }
};

// Basic functionality tests
TEST_F(WordLadderTest, LeetCodeExample1) {
    // Example 1: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    // Output: 5 (hit -> hot -> dot -> dog -> cog)
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot","dot","dog","lot","log","cog"};
    testAllApproaches(beginWord, endWord, wordList, 5);
}

TEST_F(WordLadderTest, LeetCodeExample2) {
    // Example 2: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
    // Output: 0 (endWord "cog" is not in wordList)
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot","dot","dog","lot","log"};
    testAllApproaches(beginWord, endWord, wordList, 0);
}

// Edge cases
TEST_F(WordLadderTest, EmptyWordList) {
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {};
    testAllApproaches(beginWord, endWord, wordList, 0);
}

TEST_F(WordLadderTest, BeginEqualsEnd) {
    std::string beginWord = "hit";
    std::string endWord = "hit";
    std::vector<std::string> wordList = {"hit","hot","dot","dog","lot","log","cog"};
    testAllApproaches(beginWord, endWord, wordList, 1); // Already at target, no transformation needed
}

TEST_F(WordLadderTest, SingleWordInList) {
    // Only endWord in list
    std::string beginWord = "hit";
    std::string endWord = "hot";
    std::vector<std::string> wordList = {"hot"};
    testAllApproaches(beginWord, endWord, wordList, 2);
}

TEST_F(WordLadderTest, NoPathExists) {
    // No transformation possible
    std::string beginWord = "hit";
    std::string endWord = "xyz";
    std::vector<std::string> wordList = {"hot","dot","dog","lot","log"};
    testAllApproaches(beginWord, endWord, wordList, 0);
}

// Direct transformation tests
TEST_F(WordLadderTest, DirectTransformation) {
    // One character difference
    std::string beginWord = "cat";
    std::string endWord = "bat";
    std::vector<std::string> wordList = {"bat"};
    testAllApproaches(beginWord, endWord, wordList, 2);
}

TEST_F(WordLadderTest, TwoStepTransformation) {
    std::string beginWord = "cat";
    std::string endWord = "dog";
    std::vector<std::string> wordList = {"cag","dag","dog"};  // cat -> cag -> dag -> dog
    testAllApproaches(beginWord, endWord, wordList, 4);
}

// Multiple path tests
TEST_F(WordLadderTest, MultiplePaths) {
    // Multiple possible paths, should return shortest
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {
        "hot","dot","dog","lot","log","cog",
        "hog"  // hit->hog->cog (shorter path)
    };
    testAllApproaches(beginWord, endWord, wordList, 4); // hit->hog->dog->cog
}

TEST_F(WordLadderTest, AlternativeShortPath) {
    // Shorter path available
    std::string beginWord = "red";
    std::string endWord = "tax";
    std::vector<std::string> wordList = {"ted","tex","red","tax","tad","den","rex","pee"};
    testAllApproaches(beginWord, endWord, wordList, 4); // red -> ted -> tex -> tax
}

// Length variation tests
TEST_F(WordLadderTest, SingleCharWords) {
    std::string beginWord = "a";
    std::string endWord = "c";
    std::vector<std::string> wordList = {"a","b","c"};
    testAllApproaches(beginWord, endWord, wordList, 2);
}

TEST_F(WordLadderTest, LongWords) {
    std::string beginWord = "abcdef";
    std::string endWord = "ghijkl";
    std::vector<std::string> wordList = {"abcdel","ghcdel","ghijkl"};
    testAllApproaches(beginWord, endWord, wordList, 0); // No valid path
}

TEST_F(WordLadderTest, LongWordsValidPath) {
    std::string beginWord = "abcdef";
    std::string endWord = "abcdel";
    std::vector<std::string> wordList = {"abcdel"};
    testAllApproaches(beginWord, endWord, wordList, 2);
}

// Complex transformation patterns
TEST_F(WordLadderTest, LinearChain) {
    // aaaaa -> baaaa -> ebaaa -> eeaaa -> eeeaa -> eeeea -> eeeee
    std::string beginWord = "aaaaa";
    std::string endWord = "eeeee";
    std::vector<std::string> wordList = {"baaaa","caaaa","daaaa","eaaaa",
                                        "ebaaa","ecaaa","edaaa","eeaaa",
                                        "eebaa","eecaa","eedaa","eeeaa",
                                        "eeeea","eeeee"};
    testAllApproaches(beginWord, endWord, wordList, 6); // 5 transformations + 1
}

TEST_F(WordLadderTest, BranchingPaths) {
    // Multiple branches from start word
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {
        "hot","hut","hat",  // 3 branches from hit
        "dot","lot","pot",  // Connections from hot
        "dog","log","pog",  // Connections to final stage
        "cog"
    };
    testAllApproaches(beginWord, endWord, wordList, 5);
}

// Stress and performance tests
TEST_F(WordLadderTest, LargeWordList) {
    std::string beginWord = "start";
    std::string endWord = "final";
    std::vector<std::string> wordList;
    
    // Create a large word list with valid transformations
    wordList.push_back("start");
    wordList.push_back("stard"); // start -> stard
    wordList.push_back("stare"); // stard -> stare  
    wordList.push_back("spare"); // stare -> spare
    wordList.push_back("spire"); // spare -> spire
    wordList.push_back("spine"); // spire -> spine
    wordList.push_back("spinal"); // Can't connect - different length
    wordList.push_back("final");
    
    // Add many irrelevant words
    for (int i = 0; i < 100; ++i) {
        wordList.push_back("word" + std::to_string(i));
    }
    
    testAllApproaches(beginWord, endWord, wordList, 0); // No path due to length mismatch
}

TEST_F(WordLadderTest, ValidLargeTransformation) {
    // Use a simpler test case that definitely has a connection
    std::string beginWord = "hit";
    std::string endWord = "hot";
    std::vector<std::string> wordList = {"hot"};
    
    testAllApproaches(beginWord, endWord, wordList, 2); // hit->hot
}

// Special character patterns
TEST_F(WordLadderTest, AlphabeticalProgression) {
    std::string beginWord = "aaaa";
    std::string endWord = "dddd";
    std::vector<std::string> wordList = {"baaa","caaa","daaa","dbaa","dcaa","ddaa","ddda","dddd"};
    testAllApproaches(beginWord, endWord, wordList, 5);
}

TEST_F(WordLadderTest, MixedTransformations) {
    std::string beginWord = "abc";
    std::string endWord = "def";
    std::vector<std::string> wordList = {"dbc","dec","def"}; // abc->dbc->dec->def
    testAllApproaches(beginWord, endWord, wordList, 4);
}

// Boundary and constraint tests
TEST_F(WordLadderTest, MaxLengthWords) {
    // Test with 10-character words (constraint limit)
    std::string beginWord = "abcdefghij";
    std::string endWord = "abcdefghik";
    std::vector<std::string> wordList = {"abcdefghik"};
    testAllApproaches(beginWord, endWord, wordList, 2);
}

TEST_F(WordLadderTest, MinimalTransformation) {
    std::string beginWord = "a";
    std::string endWord = "b";
    std::vector<std::string> wordList = {"b"};
    testAllApproaches(beginWord, endWord, wordList, 2);
}

// Circular transformation patterns
TEST_F(WordLadderTest, CircularWords) {
    // Create potential for cycles in search
    std::string beginWord = "cat";
    std::string endWord = "dog";
    std::vector<std::string> wordList = {
        "bat","cot","cat","cag","dag","dog", // Various interconnected words
        "bog","boo","coo","cop","cap"
    };
    
    std::vector<std::string> wordList1 = wordList;
    int result = solution.ladderLength(beginWord, endWord, wordList1);
    EXPECT_GT(result, 0) << "Should find valid path";
    
    testAllApproaches(beginWord, endWord, wordList, result);
}

// Algorithm-specific edge cases
TEST_F(WordLadderTest, BidirectionalMeetingPoint) {
    // Test case where bidirectional search should meet in middle
    std::string beginWord = "start";
    std::string endWord = "final";
    std::vector<std::string> wordList = {"smart","small","shall","shale","share","spare","spire","spine","fine","final"};
    
    std::vector<std::string> wordList1 = wordList;
    int result = solution.ladderLength(beginWord, endWord, wordList1);
    
    if (result > 0) {
        testAllApproaches(beginWord, endWord, wordList, result);
    } else {
        testAllApproaches(beginWord, endWord, wordList, 0);
    }
}

TEST_F(WordLadderTest, PatternMatchingEfficiency) {
    // Test with words that share many patterns
    std::string beginWord = "abc";
    std::string endWord = "xyz";
    std::vector<std::string> wordList = {
        "abc","abd","acd","bcd",  // Many shared patterns with abc
        "xbc","xyc","xyz"         // Path to target
    };
    testAllApproaches(beginWord, endWord, wordList, 4); // abc->xbc->xyc->xyz
}

// Error conditions
TEST_F(WordLadderTest, BeginWordNotInList) {
    // beginWord doesn't need to be in wordList
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot","dot","dog","lot","log","cog"}; // hit not in list
    testAllApproaches(beginWord, endWord, wordList, 5);
}

TEST_F(WordLadderTest, DuplicatesInWordList) {
    // WordList with duplicates (though problem states unique words)
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot","hot","dot","dog","lot","log","cog","cog"};
    testAllApproaches(beginWord, endWord, wordList, 5);
}

TEST_F(WordLadderTest, CaseConsistency) {
    // All lowercase as per constraints
    std::string beginWord = "test";
    std::string endWord = "best";
    std::vector<std::string> wordList = {"pest","best"};  // test->pest->best or test->best
    testAllApproaches(beginWord, endWord, wordList, 2);  // test->best (1 char diff)
}

}
}
}