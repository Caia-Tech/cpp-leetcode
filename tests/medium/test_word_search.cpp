#include <gtest/gtest.h>
#include "../../src/medium/word_search.h"
#include <vector>
#include <string>

namespace leetcode {
namespace medium {
namespace test {

class WordSearchTest : public ::testing::Test {
protected:
    // Helper function to test all approaches
    void testAllApproaches(std::vector<std::vector<char>> board, std::string word, bool expected) {
        // Make copies since some approaches modify the board
        auto board1 = board;
        auto board2 = board;
        auto board3 = board;
        auto board4 = board;
        auto board5 = board;
        auto board6 = board;
        
        WordSearch solution1;
        WordSearchBFS solution2;
        WordSearchIterative solution3;
        WordSearchOptimized solution4;
        WordSearchBidirectional solution5;
        WordSearchTrie solution6;
        
        EXPECT_EQ(solution1.exist(board1, word), expected) 
            << "DFS with Backtracking failed for word: " << word;
        EXPECT_EQ(solution2.exist(board2, word), expected) 
            << "BFS with State Tracking failed for word: " << word;
        EXPECT_EQ(solution3.exist(board3, word), expected) 
            << "Iterative DFS failed for word: " << word;
        EXPECT_EQ(solution4.exist(board4, word), expected) 
            << "Optimized with Pruning failed for word: " << word;
        EXPECT_EQ(solution5.exist(board5, word), expected) 
            << "Bidirectional Search failed for word: " << word;
        EXPECT_EQ(solution6.exist(board6, word), expected) 
            << "Trie-based Solution failed for word: " << word;
    }
};

// LeetCode examples
TEST_F(WordSearchTest, LeetCodeExample1) {
    // board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
    std::vector<std::vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    testAllApproaches(board, "ABCCED", true);
}

TEST_F(WordSearchTest, LeetCodeExample2) {
    // board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
    std::vector<std::vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    testAllApproaches(board, "SEE", true);
}

TEST_F(WordSearchTest, LeetCodeExample3) {
    // board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
    std::vector<std::vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    testAllApproaches(board, "ABCB", false);
}

// Edge cases
TEST_F(WordSearchTest, SingleCell) {
    std::vector<std::vector<char>> board = {{'A'}};
    testAllApproaches(board, "A", true);
    testAllApproaches(board, "B", false);
}

TEST_F(WordSearchTest, SingleRow) {
    std::vector<std::vector<char>> board = {{'A','B','C','D'}};
    testAllApproaches(board, "ABCD", true);
    testAllApproaches(board, "DCBA", true);
    testAllApproaches(board, "AC", false);  // Not adjacent
}

TEST_F(WordSearchTest, SingleColumn) {
    std::vector<std::vector<char>> board = {
        {'A'},
        {'B'},
        {'C'},
        {'D'}
    };
    testAllApproaches(board, "ABCD", true);
    testAllApproaches(board, "DCBA", true);
    testAllApproaches(board, "AD", false);  // Not adjacent
}

TEST_F(WordSearchTest, EmptyWord) {
    std::vector<std::vector<char>> board = {
        {'A','B'},
        {'C','D'}
    };
    testAllApproaches(board, "", false);
}

// Pattern tests
TEST_F(WordSearchTest, SnakePattern) {
    // Word forms a snake pattern through the board
    std::vector<std::vector<char>> board = {
        {'S','N','A'},
        {'P','A','K'},
        {'E','K','E'}
    };
    testAllApproaches(board, "SNAKE", true);
}

TEST_F(WordSearchTest, SpiralPattern) {
    // Word forms a spiral
    std::vector<std::vector<char>> board = {
        {'A','B','C'},
        {'H','I','D'},
        {'G','F','E'}
    };
    testAllApproaches(board, "ABCDEFGHI", true);
}

TEST_F(WordSearchTest, ZigzagPattern) {
    std::vector<std::vector<char>> board = {
        {'Z','I','G'},
        {'A','G','Z'},
        {'G','Z','A'}
    };
    testAllApproaches(board, "ZIGZAG", false);  // Not possible with adjacent cells
    testAllApproaches(board, "ZIG", true);  // This is possible
}

// Reuse prevention tests
TEST_F(WordSearchTest, CannotReuseCell) {
    std::vector<std::vector<char>> board = {
        {'A','A'},
        {'A','A'}
    };
    testAllApproaches(board, "AAAAA", false);  // Only 4 cells available
}

TEST_F(WordSearchTest, AlmostReuse) {
    // Word almost requires reusing a cell
    std::vector<std::vector<char>> board = {
        {'A','B','C'},
        {'D','E','F'},
        {'G','H','I'}
    };
    testAllApproaches(board, "ABCFEDGH", true);  // Actually valid path exists
    testAllApproaches(board, "ABCFEDGHB", false);  // This would need to reuse B
}

// Character variation tests
TEST_F(WordSearchTest, AllSameCharacter) {
    std::vector<std::vector<char>> board = {
        {'A','A','A'},
        {'A','A','A'},
        {'A','A','A'}
    };
    testAllApproaches(board, "AAAAAAAAA", true);  // All 9 A's
    testAllApproaches(board, "AAAAAAAAAA", false);  // 10 A's - too many
}

TEST_F(WordSearchTest, MixedCase) {
    std::vector<std::vector<char>> board = {
        {'a','B','c'},
        {'D','e','F'},
        {'g','H','i'}
    };
    testAllApproaches(board, "aBc", true);
    testAllApproaches(board, "DeF", true);
    testAllApproaches(board, "gHi", true);
}

// Complex paths
TEST_F(WordSearchTest, LongPath) {
    std::vector<std::vector<char>> board = {
        {'L','O','N','G'},
        {'O','N','G','P'},
        {'N','G','P','A'},
        {'G','P','A','T'},
        {'P','A','T','H'}
    };
    testAllApproaches(board, "LONGPATH", true);
}

TEST_F(WordSearchTest, MultiplePossiblePaths) {
    // Word can be formed in multiple ways
    std::vector<std::vector<char>> board = {
        {'C','A','T'},
        {'A','T','C'},
        {'T','C','A'}
    };
    testAllApproaches(board, "CAT", true);
}

TEST_F(WordSearchTest, DeadEnd) {
    // Path leads to dead end, must backtrack
    std::vector<std::vector<char>> board = {
        {'A','B','C','D'},
        {'B','C','D','E'},
        {'C','D','E','F'},
        {'D','E','F','G'}
    };
    testAllApproaches(board, "ABCDEFG", true);
}

// Performance tests
TEST_F(WordSearchTest, MaximumSizeBoard) {
    // 6x6 board (maximum size per constraints)
    std::vector<std::vector<char>> board = {
        {'A','B','C','D','E','F'},
        {'G','H','I','J','K','L'},
        {'M','N','O','P','Q','R'},
        {'S','T','U','V','W','X'},
        {'Y','Z','A','B','C','D'},
        {'E','F','G','H','I','J'}
    };
    testAllApproaches(board, "ABCDEF", true);
    testAllApproaches(board, "JIHGFE", true);
    testAllApproaches(board, "ABCXYZ", false);  // Not adjacent
}

TEST_F(WordSearchTest, MaximumLengthWord) {
    // Word of length 15 (maximum per constraints)
    std::vector<std::vector<char>> board = {
        {'A','B','C','D','E','F'},
        {'L','K','J','I','H','G'},
        {'M','N','O','P','Q','R'},
        {'X','W','V','U','T','S'},
        {'Y','Z','1','2','3','4'},
        {'9','8','7','6','5','0'}
    };
    testAllApproaches(board, "ABCDEFGHIJKLMNO", true);  // Snake pattern through board
}

// Not found cases
TEST_F(WordSearchTest, CharacterNotInBoard) {
    std::vector<std::vector<char>> board = {
        {'A','B','C'},
        {'D','E','F'},
        {'G','H','I'}
    };
    testAllApproaches(board, "XYZ", false);
}

TEST_F(WordSearchTest, PartialMatch) {
    std::vector<std::vector<char>> board = {
        {'P','A','R'},
        {'T','I','A'},
        {'L','M','A'}
    };
    testAllApproaches(board, "PARTIAL", false);  // Can't complete the word
}

TEST_F(WordSearchTest, AlmostConnected) {
    // Characters exist but not connected
    std::vector<std::vector<char>> board = {
        {'W','X','R'},
        {'O','X','D'},
        {'X','X','X'}
    };
    testAllApproaches(board, "WORD", false);  // W-O-R-D not adjacent
}

// Special patterns
TEST_F(WordSearchTest, CrossPattern) {
    std::vector<std::vector<char>> board = {
        {'X','C','X'},
        {'C','R','O'},
        {'X','O','S'},
        {'X','S','X'}
    };
    testAllApproaches(board, "CROSS", false);  // Actually not possible with adjacent cells
    testAllApproaches(board, "CRO", true);  // This is possible
}

TEST_F(WordSearchTest, DiagonalNotAllowed) {
    // Diagonal connections are not allowed
    std::vector<std::vector<char>> board = {
        {'D','X','X'},
        {'X','I','X'},
        {'X','X','A'}
    };
    testAllApproaches(board, "DIA", false);  // Would need diagonal
}

TEST_F(WordSearchTest, BacktrackingRequired) {
    // Must try multiple paths and backtrack
    std::vector<std::vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','B','S'},
        {'A','D','E','E'}
    };
    testAllApproaches(board, "ABCESEEDB", false);  // Close but not quite
}

// Boundary tests
TEST_F(WordSearchTest, MinimumConstraints) {
    // 1x1 board, 1 character word
    std::vector<std::vector<char>> board = {{'X'}};
    testAllApproaches(board, "X", true);
    testAllApproaches(board, "Y", false);
}

TEST_F(WordSearchTest, WordLongerThanCells) {
    // Word length exceeds total cells
    std::vector<std::vector<char>> board = {
        {'A','B'},
        {'C','D'}
    };
    testAllApproaches(board, "ABCDE", false);  // 5 chars, only 4 cells
}

// Corner cases
TEST_F(WordSearchTest, StartFromCorners) {
    std::vector<std::vector<char>> board = {
        {'C','O','R','N'},
        {'O','X','X','E'},
        {'R','X','X','R'},
        {'N','E','R','S'}
    };
    testAllApproaches(board, "CORNERS", true);
}

TEST_F(WordSearchTest, CenterOut) {
    std::vector<std::vector<char>> board = {
        {'O','U','T','X'},
        {'X','C','E','N'},
        {'X','T','E','R'},
        {'X','X','X','X'}
    };
    testAllApproaches(board, "CENTER", false);  // Actually not possible with adjacent cells
    testAllApproaches(board, "OUT", true);
    testAllApproaches(board, "CET", true);  // This is possible: C->E->T
}

// Stress test
TEST_F(WordSearchTest, ComplexMaze) {
    std::vector<std::vector<char>> board = {
        {'M','A','Z','E','S','T'},
        {'A','Z','E','X','O','A'},
        {'Z','E','X','X','L','R'},
        {'E','X','X','X','V','T'},
        {'X','X','X','X','E','X'},
        {'X','X','X','X','D','X'}
    };
    testAllApproaches(board, "MAZESOLVEDSTART", false);  // Too long path required
    testAllApproaches(board, "MAZE", true);
    testAllApproaches(board, "START", true);
}

}
}
}