# C++ LeetCode Solutions Collection

A comprehensive collection of **99 LeetCode solutions** implemented in modern C++17, featuring multiple algorithmic approaches for each problem with extensive testing.

## 🚀 Features

- **Multiple Approaches**: Each problem solved using 6 different algorithmic approaches
- **Comprehensive Testing**: 20+ test cases per problem covering edge cases and boundaries  
- **Modern C++**: Utilizing C++17 features and best practices
- **Educational Focus**: Detailed complexity analysis and approach explanations
- **99 Problems**: 56 Easy, 34 Medium, 9 Hard difficulty problems

## 📊 Current Progress

- **Easy**: 56/~800 problems (7.0%)
- **Medium**: 34/~1600 problems (2.1%)  
- **Hard**: 9/~650 problems (1.4%)
- **Total**: 99 problems implemented

## 🏗️ Project Structure

```
cpp-leetcode/
├── CMakeLists.txt          # Build configuration
├── README.md               # Project documentation  
├── PROBLEM_TRACKER.md      # Detailed problem list
├── src/                    # Source code
│   ├── easy/              # Easy difficulty problems (56)
│   ├── medium/            # Medium difficulty problems (34)
│   ├── hard/              # Hard difficulty problems (9)
│   └── utils/             # Utility functions and data structures
├── tests/                  # Comprehensive unit tests
│   ├── easy/              # Tests for easy problems
│   ├── medium/            # Tests for medium problems
│   └── hard/              # Tests for hard problems
└── benchmarks/            # Performance benchmarks
```

## 🛠️ Requirements

- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Google Test (for unit tests)

## 🔧 Building the Project

```bash
# Clone and navigate to project
git clone <repository-url>
cd cpp-leetcode

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make -j4

# Run all tests
./leetcode_tests

# Run specific problem tests
./leetcode_tests --gtest_filter="TwoSumTest*"
./leetcode_tests --gtest_filter="HappyNumberTest*"
./leetcode_tests --gtest_filter="CountPrimesTest*"
```

## 📝 Solution Format

Each problem solution follows this structure:

```cpp
namespace leetcode::easy {
class ProblemName {
public:
    // Approach 1: Optimal solution
    // Time: O(...), Space: O(...)
    static ReturnType approach1(Parameters params);
    
    // Approach 2: Alternative algorithm
    // Time: O(...), Space: O(...)  
    static ReturnType approach2(Parameters params);
    
    // ... 4 more approaches with different trade-offs
};
}
```

## 🧪 Testing Philosophy

Each problem includes 20+ comprehensive test cases:

- **LeetCode Examples**: Official test cases from problem description
- **Edge Cases**: Empty inputs, single elements, boundary values
- **Stress Tests**: Large inputs for performance validation
- **Mathematical Properties**: Verification of algorithmic correctness
- **Consistency Tests**: All approaches produce identical results

### Example Test Categories

```cpp
TEST_F(ProblemTest, LeetCodeExamples) { ... }
TEST_F(ProblemTest, EdgeCases) { ... }
TEST_F(ProblemTest, StressTest) { ... }
TEST_F(ProblemTest, MathematicalProperties) { ... }
TEST_F(ProblemTest, ApproachConsistency) { ... }
```

## 🏆 Featured Problems

### Recently Added (Latest)
- **202. Happy Number** - Cycle detection algorithms (Floyd's, Brent's, mathematical)
- **204. Count Primes** - Sieve algorithms (Eratosthenes, segmented, optimized)
- **231. Power of Two** - Bit manipulation techniques

### Algorithm Categories Covered
- **Array & String**: Two-pointer, sliding window, prefix sums
- **Linked List**: Floyd's cycle detection, dummy nodes, reversal
- **Trees**: DFS/BFS traversal, Morris traversal, serialization
- **Math**: Number theory, bit manipulation, combinatorics
- **Dynamic Programming**: Memoization, tabulation, optimization
- **Hash Maps**: O(1) lookup, frequency counting, grouping
- **Graph**: BFS/DFS, topological sort, union-find
- **Binary Search**: Search space reduction, bisection

## 🔍 Key Algorithmic Insights

**Performance Optimizations:**
- Bit manipulation (`n & (n-1)`) for power-of-2 detection
- Mathematical formulas outperform iterative approaches for combinatorics
- Hash maps provide O(1) amortized lookup vs O(n) linear search
- Morris traversal achieves O(1) space for tree traversal
- Sieve of Eratosthenes scales to millions of numbers efficiently

**Common Patterns:**
- **Two Pointers**: Arrays, palindromes, target sums
- **Sliding Window**: Substring problems, contiguous subarrays  
- **Cycle Detection**: Floyd's tortoise-hare, mathematical analysis
- **Divide & Conquer**: Recursive problem decomposition
- **Greedy**: Local optimal choices leading to global optimum

## 📈 Running Tests

```bash
# Run all tests (recommended)
./leetcode_tests

# Run tests with verbose output
./leetcode_tests --gtest_verbose

# Test specific difficulty
./leetcode_tests --gtest_filter="*Easy*"
./leetcode_tests --gtest_filter="*Medium*"
./leetcode_tests --gtest_filter="*Hard*"

# Test specific algorithms
./leetcode_tests --gtest_filter="*BinarySearch*"
./leetcode_tests --gtest_filter="*TwoPointers*"
```

## 📚 Learning Resources

Each solution includes:
- **Time & Space Complexity Analysis**
- **Approach Intuition & Strategy**  
- **Trade-offs Between Methods**
- **Real-world Applications**
- **Edge Case Considerations**

## 🤝 Contributing

To maintain quality standards:

1. **Implement 6 approaches minimum** per problem
2. **Add 20+ comprehensive test cases**
3. **Document complexity analysis**
4. **Follow C++17 best practices**
5. **Ensure all tests pass**

## 📋 Problem Categories

See [PROBLEM_TRACKER.md](PROBLEM_TRACKER.md) for the complete list of implemented problems.

**Easy (56 problems)**: Two Sum, Palindrome Number, Valid Parentheses, Binary Tree Traversals, Happy Number, Count Primes, Power of Two, and more.

**Medium (34 problems)**: Add Two Numbers, Longest Substring, Container With Most Water, Clone Graph, Product Except Self, and more.

**Hard (9 problems)**: Median of Two Arrays, N-Queens, Edit Distance, Trapping Rain Water, and more.

## 🎯 Future Goals

- Expand to 200+ problems across all difficulty levels
- Add advanced data structure implementations (Trie, Segment Tree)
- Include concurrent/parallel algorithm variants
- Add algorithm visualization tools
- Implement custom memory allocators for performance

## 📄 License

This project is for educational purposes. LeetCode problems are property of LeetCode LLC.

---

⭐ **Star this repository if you find it helpful for your coding interview preparation!**