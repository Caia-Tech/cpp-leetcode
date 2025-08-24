#include <gtest/gtest.h>
#include "../../src/medium/number_of_islands.h"
#include <vector>

namespace leetcode {
namespace medium {
namespace test {

class NumberOfIslandsTest : public ::testing::Test {
protected:
    // Helper to create a copy of grid for testing
    std::vector<std::vector<char>> copyGrid(const std::vector<std::vector<char>>& grid) {
        return grid;
    }
    
    // Test all approaches
    void testAllApproaches(const std::vector<std::vector<char>>& original_grid, int expected) {
        NumberOfIslands solution;
        
        // Each approach may modify the grid, so we need fresh copies
        auto grid1 = copyGrid(original_grid);
        EXPECT_EQ(solution.numIslandsDFS(grid1), expected) 
            << "DFS approach failed";
        
        auto grid2 = copyGrid(original_grid);
        EXPECT_EQ(solution.numIslandsBFS(grid2), expected) 
            << "BFS approach failed";
        
        auto grid3 = copyGrid(original_grid);
        EXPECT_EQ(solution.numIslandsUnionFind(grid3), expected) 
            << "Union-Find approach failed";
        
        auto grid4 = copyGrid(original_grid);
        EXPECT_EQ(solution.numIslandsIterativeDFS(grid4), expected) 
            << "Iterative DFS approach failed";
        
        auto grid5 = copyGrid(original_grid);
        EXPECT_EQ(solution.numIslandsWithMarking(grid5), expected) 
            << "Marking approach failed";
        
        auto grid6 = copyGrid(original_grid);
        EXPECT_EQ(solution.numIslandsSink(grid6), expected) 
            << "Sink approach failed";
    }
};

// LeetCode Example Test Cases

TEST_F(NumberOfIslandsTest, LeetCodeExample1) {
    // grid = [
    //   ["1","1","1","1","0"],
    //   ["1","1","0","1","0"],
    //   ["1","1","0","0","0"],
    //   ["0","0","0","0","0"]
    // ]
    // Output: 1
    std::vector<std::vector<char>> grid = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    testAllApproaches(grid, 1);
}

TEST_F(NumberOfIslandsTest, LeetCodeExample2) {
    // grid = [
    //   ["1","1","0","0","0"],
    //   ["1","1","0","0","0"],
    //   ["0","0","1","0","0"],
    //   ["0","0","0","1","1"]
    // ]
    // Output: 3
    std::vector<std::vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    testAllApproaches(grid, 3);
}

// Edge Cases

TEST_F(NumberOfIslandsTest, EmptyGrid) {
    std::vector<std::vector<char>> grid;
    testAllApproaches(grid, 0);
}

TEST_F(NumberOfIslandsTest, SingleCellLand) {
    std::vector<std::vector<char>> grid = {{'1'}};
    testAllApproaches(grid, 1);
}

TEST_F(NumberOfIslandsTest, SingleCellWater) {
    std::vector<std::vector<char>> grid = {{'0'}};
    testAllApproaches(grid, 0);
}

TEST_F(NumberOfIslandsTest, AllWater) {
    std::vector<std::vector<char>> grid = {
        {'0','0','0'},
        {'0','0','0'},
        {'0','0','0'}
    };
    testAllApproaches(grid, 0);
}

TEST_F(NumberOfIslandsTest, AllLand) {
    std::vector<std::vector<char>> grid = {
        {'1','1','1'},
        {'1','1','1'},
        {'1','1','1'}
    };
    testAllApproaches(grid, 1);
}

// Different Shapes

TEST_F(NumberOfIslandsTest, SingleRow) {
    std::vector<std::vector<char>> grid = {
        {'1','0','1','0','1'}
    };
    testAllApproaches(grid, 3);
}

TEST_F(NumberOfIslandsTest, SingleColumn) {
    std::vector<std::vector<char>> grid = {
        {'1'},
        {'0'},
        {'1'},
        {'0'},
        {'1'}
    };
    testAllApproaches(grid, 3);
}

TEST_F(NumberOfIslandsTest, DiagonalIslands) {
    // Diagonal cells are not connected
    std::vector<std::vector<char>> grid = {
        {'1','0','0'},
        {'0','1','0'},
        {'0','0','1'}
    };
    testAllApproaches(grid, 3);
}

TEST_F(NumberOfIslandsTest, SnakeIsland) {
    std::vector<std::vector<char>> grid = {
        {'1','1','0','0','0'},
        {'0','1','0','0','0'},
        {'0','1','1','1','0'},
        {'0','0','0','1','0'},
        {'0','0','0','1','1'}
    };
    testAllApproaches(grid, 1);
}

// Complex Patterns

TEST_F(NumberOfIslandsTest, CheckerboardPattern) {
    std::vector<std::vector<char>> grid = {
        {'1','0','1','0'},
        {'0','1','0','1'},
        {'1','0','1','0'},
        {'0','1','0','1'}
    };
    testAllApproaches(grid, 8);
}

TEST_F(NumberOfIslandsTest, ConcentricIslands) {
    std::vector<std::vector<char>> grid = {
        {'1','1','1','1','1'},
        {'1','0','0','0','1'},
        {'1','0','1','0','1'},
        {'1','0','0','0','1'},
        {'1','1','1','1','1'}
    };
    testAllApproaches(grid, 2);
}

TEST_F(NumberOfIslandsTest, MultipleSmallIslands) {
    std::vector<std::vector<char>> grid = {
        {'1','0','1','0','1'},
        {'0','0','0','0','0'},
        {'1','0','1','0','1'},
        {'0','0','0','0','0'},
        {'1','0','1','0','1'}
    };
    testAllApproaches(grid, 9);
}

TEST_F(NumberOfIslandsTest, LargeConnectedIsland) {
    std::vector<std::vector<char>> grid = {
        {'1','1','1','1','1'},
        {'1','1','1','1','1'},
        {'1','1','1','1','1'},
        {'1','1','1','1','1'},
        {'1','1','1','1','1'}
    };
    testAllApproaches(grid, 1);
}

// Border Cases

TEST_F(NumberOfIslandsTest, IslandOnBorders) {
    std::vector<std::vector<char>> grid = {
        {'1','1','1','1','1'},
        {'1','0','0','0','1'},
        {'1','0','0','0','1'},
        {'1','0','0','0','1'},
        {'1','1','1','1','1'}
    };
    testAllApproaches(grid, 1);
}

TEST_F(NumberOfIslandsTest, IslandInCenter) {
    std::vector<std::vector<char>> grid = {
        {'0','0','0','0','0'},
        {'0','1','1','1','0'},
        {'0','1','1','1','0'},
        {'0','1','1','1','0'},
        {'0','0','0','0','0'}
    };
    testAllApproaches(grid, 1);
}

// Complex Connected Components

TEST_F(NumberOfIslandsTest, HShape) {
    std::vector<std::vector<char>> grid = {
        {'1','0','1'},
        {'1','1','1'},
        {'1','0','1'}
    };
    testAllApproaches(grid, 1);
}

TEST_F(NumberOfIslandsTest, CrossShape) {
    std::vector<std::vector<char>> grid = {
        {'0','1','0'},
        {'1','1','1'},
        {'0','1','0'}
    };
    testAllApproaches(grid, 1);
}

TEST_F(NumberOfIslandsTest, LShape) {
    std::vector<std::vector<char>> grid = {
        {'1','0','0'},
        {'1','0','0'},
        {'1','1','1'}
    };
    testAllApproaches(grid, 1);
}

// Large Grid Tests

TEST_F(NumberOfIslandsTest, LargeGridAlternating) {
    std::vector<std::vector<char>> grid(20, std::vector<char>(20));
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            grid[i][j] = ((i + j) % 2 == 0) ? '1' : '0';
        }
    }
    testAllApproaches(grid, 200);  // Checkerboard pattern
}

TEST_F(NumberOfIslandsTest, LargeGridStripes) {
    std::vector<std::vector<char>> grid(10, std::vector<char>(10));
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            grid[i][j] = (j % 2 == 0) ? '1' : '0';
        }
    }
    testAllApproaches(grid, 5);  // Vertical stripes
}

// Special Patterns

TEST_F(NumberOfIslandsTest, TwoByTwoIslands) {
    std::vector<std::vector<char>> grid = {
        {'1','1','0','1','1'},
        {'1','1','0','1','1'},
        {'0','0','0','0','0'},
        {'1','1','0','1','1'},
        {'1','1','0','1','1'}
    };
    testAllApproaches(grid, 4);
}

TEST_F(NumberOfIslandsTest, SpiralIsland) {
    std::vector<std::vector<char>> grid = {
        {'1','1','1','1','1'},
        {'0','0','0','0','1'},
        {'1','1','1','0','1'},
        {'1','0','0','0','1'},
        {'1','1','1','1','1'}
    };
    testAllApproaches(grid, 1);
}

TEST_F(NumberOfIslandsTest, FragmentedIslands) {
    std::vector<std::vector<char>> grid = {
        {'1','0','0','1','0'},
        {'0','0','0','0','0'},
        {'0','1','0','0','1'},
        {'0','0','0','0','0'},
        {'1','0','1','0','1'}
    };
    testAllApproaches(grid, 6);
}

// Maximum Size Test
TEST_F(NumberOfIslandsTest, MaximumSizeGrid) {
    // Create a 300x300 grid with alternating pattern
    std::vector<std::vector<char>> grid(300, std::vector<char>(300));
    int expected = 0;
    
    // Create islands in a pattern
    for (int i = 0; i < 300; i += 3) {
        for (int j = 0; j < 300; j += 3) {
            grid[i][j] = '1';
            expected++;
        }
    }
    
    NumberOfIslands solution;
    // Test only fastest approaches for large grid
    auto grid1 = copyGrid(grid);
    EXPECT_EQ(solution.numIslandsDFS(grid1), expected);
}

}  // namespace test
}  // namespace medium
}  // namespace leetcode