#include <gtest/gtest.h>
#include "../../src/medium/course_schedule.h"
#include <vector>
#include <algorithm>

namespace leetcode {
namespace medium {
namespace test {

class CourseScheduleTest : public ::testing::Test {
protected:
    CourseSchedule solution;
    
    void testAllApproaches(int numCourses, std::vector<std::vector<int>> prerequisites, bool expected) {
        // Make copies for each approach since some might modify input
        auto prereq1 = prerequisites;
        auto prereq2 = prerequisites;
        auto prereq3 = prerequisites;
        auto prereq4 = prerequisites;
        auto prereq5 = prerequisites;
        auto prereq6 = prerequisites;
        
        EXPECT_EQ(solution.canFinish(numCourses, prereq1), expected) 
            << "DFS with Cycle Detection failed";
        EXPECT_EQ(solution.canFinishKahn(numCourses, prereq2), expected) 
            << "Kahn's Algorithm failed";
        EXPECT_EQ(solution.canFinishDFSStack(numCourses, prereq3), expected) 
            << "DFS with Stack failed";
        EXPECT_EQ(solution.canFinishUnionFind(numCourses, prereq4), expected) 
            << "Union-Find approach failed";
        EXPECT_EQ(solution.canFinishMatrix(numCourses, prereq5), expected) 
            << "Matrix DFS failed";
        EXPECT_EQ(solution.canFinishIterative(numCourses, prereq6), expected) 
            << "Iterative DFS failed";
    }
};

// Basic functionality tests
TEST_F(CourseScheduleTest, LeetCodeExample1) {
    // numCourses = 2, prerequisites = [[1,0]]
    // To take course 1, you need to finish course 0. So it is possible.
    int numCourses = 2;
    std::vector<std::vector<int>> prerequisites = {{1, 0}};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, LeetCodeExample2) {
    // numCourses = 2, prerequisites = [[1,0],[0,1]]
    // To take course 1, you need course 0. To take course 0, you need course 1. Impossible.
    int numCourses = 2;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {0, 1}};
    testAllApproaches(numCourses, prerequisites, false);
}

// Edge cases
TEST_F(CourseScheduleTest, NoCourses) {
    int numCourses = 1;
    std::vector<std::vector<int>> prerequisites = {};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, NoPrerequisites) {
    int numCourses = 5;
    std::vector<std::vector<int>> prerequisites = {};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, SingleCourseNoPrereq) {
    int numCourses = 1;
    std::vector<std::vector<int>> prerequisites = {};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, SelfLoop) {
    // Course depends on itself - impossible
    int numCourses = 2;
    std::vector<std::vector<int>> prerequisites = {{0, 0}};
    testAllApproaches(numCourses, prerequisites, false);
}

// Simple cycles
TEST_F(CourseScheduleTest, SimpleCycle) {
    // 0 -> 1 -> 0 (cycle)
    int numCourses = 2;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {0, 1}};
    testAllApproaches(numCourses, prerequisites, false);
}

TEST_F(CourseScheduleTest, ThreeNodeCycle) {
    // 0 -> 1 -> 2 -> 0 (cycle)
    int numCourses = 3;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 1}, {0, 2}};
    testAllApproaches(numCourses, prerequisites, false);
}

TEST_F(CourseScheduleTest, FourNodeCycle) {
    // 0 -> 1 -> 2 -> 3 -> 0 (cycle)
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 1}, {3, 2}, {0, 3}};
    testAllApproaches(numCourses, prerequisites, false);
}

// Valid DAGs (Directed Acyclic Graphs)
TEST_F(CourseScheduleTest, LinearChain) {
    // 0 -> 1 -> 2 -> 3 -> 4 (no cycle)
    int numCourses = 5;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 1}, {3, 2}, {4, 3}};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, Tree) {
    // Tree structure: 0 -> 1, 0 -> 2, 1 -> 3, 1 -> 4
    int numCourses = 5;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {4, 1}};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, DiamondDAG) {
    // Diamond: 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, ComplexDAG) {
    // Complex valid DAG
    int numCourses = 6;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {2, 0}, {3, 1}, {3, 2}, {4, 3}, {5, 3}, {5, 4}
    };
    testAllApproaches(numCourses, prerequisites, true);
}

// Disconnected components
TEST_F(CourseScheduleTest, DisconnectedNoCycle) {
    // Two separate chains: 0 -> 1 and 2 -> 3
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {3, 2}};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, DisconnectedWithCycle) {
    // One component has cycle: 0 -> 1 -> 0, another is valid: 2 -> 3
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {0, 1}, {3, 2}};
    testAllApproaches(numCourses, prerequisites, false);
}

TEST_F(CourseScheduleTest, MultipleDisconnectedComponents) {
    // Three separate components, all valid
    int numCourses = 9;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {2, 1},  // Component 1
        {4, 3}, {5, 4},  // Component 2
        {7, 6}, {8, 7}   // Component 3
    };
    testAllApproaches(numCourses, prerequisites, true);
}

// Complex cycles
TEST_F(CourseScheduleTest, CycleWithBranch) {
    // Cycle with extra branch: 0 -> 1 -> 2 -> 0, and 1 -> 3
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 1}, {0, 2}, {3, 1}};
    testAllApproaches(numCourses, prerequisites, false);
}

TEST_F(CourseScheduleTest, NestedCycles) {
    // Two connected cycles
    int numCourses = 5;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {0, 1},  // First cycle
        {3, 2}, {2, 3},  // Second cycle
        {3, 1}           // Connection between cycles
    };
    testAllApproaches(numCourses, prerequisites, false);
}

TEST_F(CourseScheduleTest, LongPathWithCycle) {
    // Long path that eventually creates a cycle
    int numCourses = 10;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4},
        {6, 5}, {7, 6}, {8, 7}, {9, 8}, {0, 9}  // Back edge creates cycle
    };
    testAllApproaches(numCourses, prerequisites, false);
}

// Multiple prerequisites
TEST_F(CourseScheduleTest, MultiplePrerequisites) {
    // Course 3 requires both 0 and 1, course 4 requires both 1 and 2
    int numCourses = 5;
    std::vector<std::vector<int>> prerequisites = {
        {3, 0}, {3, 1}, {4, 1}, {4, 2}
    };
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, ConvergingPaths) {
    // Multiple paths converge to same course
    int numCourses = 7;
    std::vector<std::vector<int>> prerequisites = {
        {3, 0}, {3, 1}, {3, 2},  // Three courses lead to 3
        {4, 3}, {5, 3}, {6, 4}, {6, 5}  // Continue from 3
    };
    testAllApproaches(numCourses, prerequisites, true);
}

// Performance tests
TEST_F(CourseScheduleTest, LargeLinearChain) {
    // Long linear chain - no cycle
    int numCourses = 100;
    std::vector<std::vector<int>> prerequisites;
    for (int i = 1; i < numCourses; i++) {
        prerequisites.push_back({i, i - 1});
    }
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, LargeCycle) {
    // Large circular dependency
    int numCourses = 100;
    std::vector<std::vector<int>> prerequisites;
    for (int i = 1; i < numCourses; i++) {
        prerequisites.push_back({i, i - 1});
    }
    prerequisites.push_back({0, numCourses - 1}); // Complete the cycle
    testAllApproaches(numCourses, prerequisites, false);
}

TEST_F(CourseScheduleTest, CompleteGraph) {
    // Small complete graph (every node connects to every other)
    // This will have cycles
    int numCourses = 5;
    std::vector<std::vector<int>> prerequisites;
    for (int i = 0; i < numCourses; i++) {
        for (int j = 0; j < numCourses; j++) {
            if (i != j) {
                prerequisites.push_back({j, i});
            }
        }
    }
    testAllApproaches(numCourses, prerequisites, false);
}

// Boundary tests
TEST_F(CourseScheduleTest, MinimumCourses) {
    int numCourses = 1;
    std::vector<std::vector<int>> prerequisites = {};
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, MaxPrerequisitesNoCycle) {
    // Star pattern: course n-1 depends on all others
    int numCourses = 10;
    std::vector<std::vector<int>> prerequisites;
    for (int i = 0; i < numCourses - 1; i++) {
        prerequisites.push_back({numCourses - 1, i});
    }
    testAllApproaches(numCourses, prerequisites, true);
}

// Special patterns
TEST_F(CourseScheduleTest, ParallelPaths) {
    // Multiple independent paths
    int numCourses = 8;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {3, 2}, {5, 4}, {7, 6}  // Four parallel chains
    };
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, ForkAndJoin) {
    // Fork from one course, join at another
    int numCourses = 6;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {2, 0},  // Fork from 0
        {3, 1}, {4, 2},  // Continue paths
        {5, 3}, {5, 4}   // Join at 5
    };
    testAllApproaches(numCourses, prerequisites, true);
}

TEST_F(CourseScheduleTest, AlmostCycle) {
    // Graph that looks like it might have a cycle but doesn't
    int numCourses = 5;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {2, 1}, {3, 2}, {4, 3}, {4, 0}  // 4 depends on both 3 and 0
    };
    testAllApproaches(numCourses, prerequisites, true);
}

// Stress test
TEST_F(CourseScheduleTest, StressTestLargeDAG) {
    // Create a large DAG with many edges but no cycles
    int numCourses = 50;
    std::vector<std::vector<int>> prerequisites;
    
    // Create a layered DAG
    for (int layer = 0; layer < 5; layer++) {
        for (int i = layer * 10; i < (layer + 1) * 10 && i < numCourses - 10; i++) {
            for (int j = (layer + 1) * 10; j < std::min((layer + 2) * 10, numCourses); j++) {
                prerequisites.push_back({j, i});
            }
        }
    }
    
    testAllApproaches(numCourses, prerequisites, true);
}

// Edge case with isolated nodes
TEST_F(CourseScheduleTest, IsolatedNodes) {
    // Some courses have no prerequisites and are not prerequisites for others
    int numCourses = 10;
    std::vector<std::vector<int>> prerequisites = {
        {1, 0}, {2, 1}, {5, 4}, {6, 5}
        // Courses 3, 7, 8, 9 are isolated
    };
    testAllApproaches(numCourses, prerequisites, true);
}

// Specific algorithm tests
TEST_F(CourseScheduleTest, KahnAlgorithmOrder) {
    // Test that Kahn's algorithm works correctly
    int numCourses = 4;
    std::vector<std::vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    auto prereqs = prerequisites;
    EXPECT_TRUE(solution.canFinishKahn(numCourses, prereqs));
}

TEST_F(CourseScheduleTest, IterativeDFSDeepRecursion) {
    // Test iterative DFS with deep recursion that would overflow stack
    int numCourses = 1000;
    std::vector<std::vector<int>> prerequisites;
    for (int i = 1; i < numCourses; i++) {
        prerequisites.push_back({i, i - 1});
    }
    auto prereqs = prerequisites;
    EXPECT_TRUE(solution.canFinishIterative(numCourses, prereqs));
}

}
}
}