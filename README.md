# C++ LeetCode Solutions Collection

A comprehensive collection of LeetCode solutions implemented in modern C++17, featuring multiple algorithmic approaches for each problem with extensive testing and benchmarking.

## Features

- **Multiple Approaches**: Each problem is solved using 6 different algorithmic approaches
- **Comprehensive Testing**: 20+ test cases per problem covering edge cases, boundaries, and special scenarios
- **Performance Benchmarking**: Google Benchmark integration for performance analysis
- **Modern C++**: Utilizing C++17 features and best practices
- **Educational Focus**: Detailed complexity analysis and approach explanations

## Project Structure

```
cpp-leetcode/
├── CMakeLists.txt          # Build configuration
├── README.md               # Project documentation
├── src/                    # Source code
│   ├── easy/              # Easy difficulty problems
│   ├── medium/            # Medium difficulty problems
│   ├── hard/              # Hard difficulty problems
│   └── utils/             # Utility functions and data structures
├── tests/                  # Unit tests
│   └── easy/              # Tests for easy problems
├── benchmarks/            # Performance benchmarks
│   └── benchmark_main.cpp # Benchmark suite
└── build/                 # Build output directory
```

## Requirements

- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Google Test (optional, for unit tests)
- Google Benchmark (optional, for performance benchmarks)

## Building the Project

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make -j$(nproc)

# Run tests (if Google Test is available)
./leetcode_tests

# Run benchmarks (if Google Benchmark is available)
./leetcode_benchmarks
```

## Implemented Problems

### Medium Problems (4 problems)

#### 11. Container With Most Water
- **Approaches**: Two Pointers (Optimal), Brute Force, Divide and Conquer, Stack-Based, Optimized Brute Force, Binary Search on Height
- **Time Complexities**: O(n) to O(n²)
- **Space Complexities**: O(1) to O(n)

#### 133. Clone Graph
- **Approaches**: DFS Recursive, BFS Iterative, DFS Iterative, Union-Find, Adjacency Matrix, Parallel Processing
- **Time Complexities**: O(V + E) for all approaches
- **Space Complexities**: O(V) to O(V²)

#### 238. Product of Array Except Self
- **Approaches**: Optimal Two-Pass, Prefix-Suffix Arrays, Single Pass, Division-Based, Logarithmic Transform, Rolling Product
- **Time Complexities**: O(n) for all approaches
- **Space Complexities**: O(1) to O(n)

#### 994. Rotting Oranges
- **Approaches**: Multi-source BFS (Optimal), DFS Time Simulation, Iterative Simulation, Union-Find Time, Priority Queue, Bidirectional BFS
- **Time Complexities**: O(m×n) for all approaches
- **Space Complexities**: O(m×n) for all approaches

## Solution Format

Each problem solution includes:

```cpp
class Solution {
public:
    /**
     * Approach Name
     * 
     * Detailed explanation of the approach
     * Time Complexity: O(...)
     * Space Complexity: O(...)
     */
    ReturnType approachName(const Parameters& params);
    
    // ... 5 more approaches
};
```

## Testing

Each problem includes 25+ comprehensive test cases:

- **Edge Cases**: Empty input, single element, minimum/maximum values
- **Boundary Cases**: Integer overflow, underflow scenarios
- **Normal Cases**: Typical inputs with various patterns
- **Performance Cases**: Large inputs for stress testing
- **Special Cases**: Problem-specific edge scenarios

### Running Tests

```bash
# Run all tests
./leetcode_tests

# Run tests with detailed output
./leetcode_tests --gtest_verbose

# Run specific test suite
./leetcode_tests --gtest_filter=TwoSumTest.*

# Run specific test case
./leetcode_tests --gtest_filter=TwoSumTest.BasicCase
```

## Benchmarking

Performance benchmarks compare different approaches:

```bash
# Run all benchmarks
./leetcode_benchmarks

# Run specific benchmark
./leetcode_benchmarks --benchmark_filter=BM_TwoSum

# Output results to JSON
./leetcode_benchmarks --benchmark_out=results.json --benchmark_out_format=json
```

## Utility Classes

### Data Structures

- `ListNode`: Singly linked list node
- `TreeNode`: Binary tree node
- Helper functions for conversion and manipulation

### Test Utilities

- Vector comparison functions
- String conversion utilities
- Test data generators

## Code Style Guidelines

- Modern C++ features (auto, range-based loops, smart pointers)
- RAII for resource management
- Const-correctness
- Clear naming conventions
- Comprehensive documentation

## Contributing

When adding new problems:

1. Implement at least 6 different approaches
2. Add time/space complexity analysis
3. Create 20+ test cases
4. Add benchmark tests
5. Update documentation

## Algorithm Approach Guidelines

### When to Use Each Approach

**Brute Force**
- Educational purposes
- Small input sizes
- Baseline for comparison

**Hash Map/Set**
- O(1) lookup requirements
- Trading space for time
- Finding pairs or duplicates

**Two Pointers**
- Sorted arrays
- Finding pairs with target sum
- Palindrome checking

**Binary Search**
- Sorted data
- O(log n) search requirement
- Finding insertion points

**Sliding Window**
- Substring/subarray problems
- Consecutive elements
- Variable window size

**Dynamic Programming**
- Overlapping subproblems
- Optimal substructure
- Memoization opportunities

## Performance Insights

Based on benchmark results:

- Hash map approaches generally provide best time complexity for search problems
- Mathematical approaches outperform string conversion for number manipulation
- Half-reversal techniques can be 2x faster than full reversal for palindromes
- Pre-sorting can be beneficial when multiple queries are needed

## Future Enhancements

- [ ] Add more medium and hard problems
- [ ] Implement graph and tree traversal problems
- [ ] Add dynamic programming solutions
- [ ] Include backtracking problems
- [ ] Add concurrent solution approaches
- [ ] Implement custom memory allocators for performance
- [ ] Add visualization tools for algorithms

## License

This project is for educational purposes. LeetCode problems are property of LeetCode.

## Resources

- [LeetCode](https://leetcode.com)
- [C++ Reference](https://en.cppreference.com)
- [Google Test Documentation](https://google.github.io/googletest/)
- [Google Benchmark Documentation](https://github.com/google/benchmark)