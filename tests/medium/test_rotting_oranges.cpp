#include <gtest/gtest.h>
#include "medium/rotting_oranges.h"
#include <vector>

namespace leetcode {
namespace medium {
namespace test {

class RottingOrangesTest : public ::testing::Test {
protected:
    // Helper function to test all approaches
    void testAllApproaches(std::vector<std::vector<int>> grid, int expected) {
        // Make copies since some approaches modify input
        auto grid1 = grid;
        auto grid2 = grid;
        auto grid3 = grid;
        auto grid4 = grid;
        auto grid5 = grid;
        auto grid6 = grid;
        
        RottingOranges solution1;
        RottingOrangesDFS solution2;
        RottingOrangesIterative solution3;
        RottingOrangesUnionFind solution4;
        RottingOrangesPriorityQueue solution5;
        RottingOrangesBidirectional solution6;
        
        EXPECT_EQ(solution1.orangesRotting(grid1), expected) 
            << "Multi-source BFS failed";
        EXPECT_EQ(solution2.orangesRotting(grid2), expected) 
            << "DFS Simulation failed";
        EXPECT_EQ(solution3.orangesRotting(grid3), expected) 
            << "Iterative Simulation failed";
        EXPECT_EQ(solution4.orangesRotting(grid4), expected) 
            << "Union-Find failed";
        EXPECT_EQ(solution5.orangesRotting(grid5), expected) 
            << "Priority Queue failed";
        EXPECT_EQ(solution6.orangesRotting(grid6), expected) 
            << "Bidirectional BFS failed";
    }
};

// LeetCode examples
TEST_F(RottingOrangesTest, LeetCodeExample1) {
    // grid = [[2,1,1],[1,1,0],[0,1,1]]
    // Output: 4
    std::vector<std::vector<int>> grid = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };
    testAllApproaches(grid, 4);
}

TEST_F(RottingOrangesTest, LeetCodeExample2) {
    // grid = [[2,1,1],[0,1,1],[1,0,1]]
    // Output: -1 (bottom left orange can never rot)
    std::vector<std::vector<int>> grid = {
        {2,1,1},
        {0,1,1},
        {1,0,1}
    };
    testAllApproaches(grid, -1);
}

TEST_F(RottingOrangesTest, LeetCodeExample3) {
    // grid = [[0,2]]
    // Output: 0 (no fresh oranges)
    std::vector<std::vector<int>> grid = {{0,2}};
    testAllApproaches(grid, 0);
}

// Edge cases
TEST_F(RottingOrangesTest, SingleCell) {
    // Single cell tests
    testAllApproaches({{0}}, 0);  // Empty
    testAllApproaches({{1}}, -1); // Fresh orange with no rotten
    testAllApproaches({{2}}, 0);  // Already rotten
}

TEST_F(RottingOrangesTest, NoFreshOranges) {
    std::vector<std::vector<int>> grid = {
        {2,0,2},
        {0,0,0},
        {2,0,2}
    };
    testAllApproaches(grid, 0);
}

TEST_F(RottingOrangesTest, NoRottenOranges) {
    std::vector<std::vector<int>> grid = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
    testAllApproaches(grid, -1);
}

TEST_F(RottingOrangesTest, AllEmpty) {
    std::vector<std::vector<int>> grid = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };
    testAllApproaches(grid, 0);
}

// Simple patterns
TEST_F(RottingOrangesTest, SingleRow) {
    // Horizontal spreading
    testAllApproaches({{2,1,1,1,1}}, 4);
    testAllApproaches({{1,1,2,1,1}}, 2);
    testAllApproaches({{1,1,0,2,1}}, -1);
}

TEST_F(RottingOrangesTest, SingleColumn) {
    // Vertical spreading
    std::vector<std::vector<int>> grid1 = {{2},{1},{1},{1},{1}};
    std::vector<std::vector<int>> grid2 = {{1},{1},{2},{1},{1}};
    std::vector<std::vector<int>> grid3 = {{1},{1},{0},{2},{1}};
    
    testAllApproaches(grid1, 4);
    testAllApproaches(grid2, 2);
    testAllApproaches(grid3, -1);
}

// Multi-source scenarios
TEST_F(RottingOrangesTest, TwoRottenSources) {
    std::vector<std::vector<int>> grid = {
        {2,1,1,1,2},
        {1,1,1,1,1},
        {1,1,1,1,1}
    };
    testAllApproaches(grid, 4);  // Fixed: longest path is from corner to center (2,2)
}

TEST_F(RottingOrangesTest, FourCornersSources) {
    std::vector<std::vector<int>> grid = {
        {2,1,1,1,2},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {2,1,1,1,2}
    };
    testAllApproaches(grid, 4);  // Fixed: center (2,2) takes 4 steps from any corner
}

TEST_F(RottingOrangesTest, CenterSource) {
    std::vector<std::vector<int>> grid = {
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,2,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1}
    };
    testAllApproaches(grid, 4);
}

// Obstruction patterns
TEST_F(RottingOrangesTest, WallObstruction) {
    std::vector<std::vector<int>> grid = {
        {2,1,1},
        {0,0,0},
        {1,1,1}
    };
    testAllApproaches(grid, -1);
}

TEST_F(RottingOrangesTest, PartialObstruction) {
    std::vector<std::vector<int>> grid = {
        {2,1,1},
        {0,0,1},
        {1,1,1}
    };
    testAllApproaches(grid, 6);
}

TEST_F(RottingOrangesTest, MazePattern) {
    std::vector<std::vector<int>> grid = {
        {2,1,0,1,1},
        {1,0,0,0,1},
        {1,0,1,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    };
    testAllApproaches(grid, -1);
}

// Connected components
TEST_F(RottingOrangesTest, TwoSeparateRegions) {
    std::vector<std::vector<int>> grid = {
        {2,1,0,1,1},
        {1,1,0,1,1},
        {0,0,0,0,0},
        {1,1,0,2,1},
        {1,1,0,1,1}
    };
    testAllApproaches(grid, -1);
}

TEST_F(RottingOrangesTest, ConnectedRegions) {
    std::vector<std::vector<int>> grid = {
        {2,1,1,1,1},
        {1,1,0,1,1},
        {1,0,0,0,1},
        {1,1,1,1,1},
        {1,1,1,1,2}
    };
    testAllApproaches(grid, 4);
}

// Complex spreading patterns
TEST_F(RottingOrangesTest, CircularSpread) {
    std::vector<std::vector<int>> grid = {
        {1,1,1,1,1},
        {1,2,1,2,1},
        {1,1,1,1,1},
        {1,2,1,2,1},
        {1,1,1,1,1}
    };
    testAllApproaches(grid, 2);
}

TEST_F(RottingOrangesTest, DiamondPattern) {
    std::vector<std::vector<int>> grid = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,2,1,1},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };
    testAllApproaches(grid, 2);
}

TEST_F(RottingOrangesTest, SpiralPattern) {
    std::vector<std::vector<int>> grid = {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,2,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    };
    testAllApproaches(grid, -1);
}

// Performance and boundary tests
TEST_F(RottingOrangesTest, MaximumSize) {
    // 10x10 grid (maximum constraint)
    std::vector<std::vector<int>> grid(10, std::vector<int>(10, 1));
    grid[0][0] = 2;  // Single source in corner
    testAllApproaches(grid, 18);  // Manhattan distance to furthest corner
}

TEST_F(RottingOrangesTest, CheckerboardPattern) {
    std::vector<std::vector<int>> grid = {
        {2,0,1,0,1},
        {0,1,0,1,0},
        {1,0,1,0,1},
        {0,1,0,1,0},
        {1,0,1,0,1}
    };
    testAllApproaches(grid, -1);
}

TEST_F(RottingOrangesTest, AlternatingRows) {
    std::vector<std::vector<int>> grid = {
        {2,1,1,1,1},
        {0,0,0,0,0},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {1,1,1,1,2}
    };
    testAllApproaches(grid, -1);
}

// Time progression tests
TEST_F(RottingOrangesTest, StepByStepProgression) {
    // Grid where we can trace exact time steps
    std::vector<std::vector<int>> grid = {
        {2,1,1,1},
        {0,0,0,1},
        {0,0,0,1},
        {0,0,0,1}
    };
    testAllApproaches(grid, 6);
}

TEST_F(RottingOrangesTest, SimultaneousSpread) {
    std::vector<std::vector<int>> grid = {
        {1,1,1},
        {1,2,1},
        {1,1,1}
    };
    testAllApproaches(grid, 2);
}

// Edge connectivity
TEST_F(RottingOrangesTest, LShapePattern) {
    std::vector<std::vector<int>> grid = {
        {2,1,1},
        {1,0,0},
        {1,0,0},
        {1,1,1}
    };
    testAllApproaches(grid, 5);
}

TEST_F(RottingOrangesTest, NarrowCorridor) {
    std::vector<std::vector<int>> grid = {
        {2,1,1,1,1,1,1,1,1,1}
    };
    testAllApproaches(grid, 9);
}

// Special cases
TEST_F(RottingOrangesTest, AllAlreadyRotten) {
    std::vector<std::vector<int>> grid = {
        {2,2,2},
        {2,2,2},
        {2,2,2}
    };
    testAllApproaches(grid, 0);
}

TEST_F(RottingOrangesTest, MixedWithEmpty) {
    std::vector<std::vector<int>> grid = {
        {2,0,1,0,1},
        {1,0,0,0,1},
        {0,0,2,0,0},
        {1,0,0,0,1},
        {1,0,1,0,1}
    };
    testAllApproaches(grid, -1);
}

TEST_F(RottingOrangesTest, DoubleBarrier) {
    std::vector<std::vector<int>> grid = {
        {2,1,0,0,1},
        {1,1,0,0,1},
        {1,1,1,1,1},
        {1,1,0,0,1},
        {1,1,0,0,1}
    };
    testAllApproaches(grid, 8);
}

// Minimum grid size
TEST_F(RottingOrangesTest, OneByOne) {
    testAllApproaches({{2}}, 0);
    testAllApproaches({{1}}, -1);
    testAllApproaches({{0}}, 0);
}

TEST_F(RottingOrangesTest, TwoByTwo) {
    testAllApproaches({{2,1},{1,1}}, 2);
    testAllApproaches({{2,1},{0,1}}, 2);
    testAllApproaches({{2,0},{0,1}}, -1);
    testAllApproaches({{2,2},{2,2}}, 0);
}

// Stress test patterns
TEST_F(RottingOrangesTest, ComplexMaze) {
    std::vector<std::vector<int>> grid = {
        {1,1,0,1,1,1,0,1,1,1},
        {1,0,0,0,1,0,0,0,1,1},
        {1,0,1,1,1,1,1,0,1,1},
        {1,0,1,0,0,0,1,0,1,1},
        {1,0,1,0,2,0,1,0,1,1},
        {1,0,1,0,0,0,1,0,1,1},
        {1,0,1,1,1,1,1,0,1,1},
        {1,0,0,0,1,0,0,0,1,1},
        {1,1,1,0,1,0,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    testAllApproaches(grid, -1);
}

}
}
}