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

### Easy Problems (36 problems)
- 1. Two Sum
- 7. Reverse Integer
- 9. Palindrome Number
- 13. Roman to Integer
- 14. Longest Common Prefix
- 20. Valid Parentheses
- 21. Merge Two Sorted Lists
- 26. Remove Duplicates from Sorted Array
- 27. Remove Element
- 28. Find the Index of the First Occurrence in a String
- 35. Search Insert Position
- 53. Maximum Subarray
- 58. Length of Last Word
- 66. Plus One
- 67. Add Binary
- 69. Sqrt(x)
- 70. Climbing Stairs
- 94. Binary Tree Inorder Traversal
- 104. Maximum Depth of Binary Tree
- 121. Best Time to Buy and Sell Stock
- 125. Valid Palindrome
- 136. Single Number
- 169. Majority Element
- 198. House Robber
- 217. Contains Duplicate
- 242. Valid Anagram
- 268. Missing Number
- 283. Move Zeroes
- 326. Power of Three
- 344. Reverse String
- 350. Intersection of Two Arrays II
- 367. Valid Perfect Square
- 383. Ransom Note
- 412. Fizz Buzz
- 704. Binary Search
- 977. Squares of a Sorted Array

### Medium Problems (33 problems)
- 2. Add Two Numbers
- 3. Longest Substring Without Repeating Characters
- 5. Longest Palindromic Substring
- 11. Container With Most Water
- 12. Integer to Roman
- 15. 3Sum
- 17. Letter Combinations of a Phone Number
- 18. 4Sum
- 22. Generate Parentheses
- 31. Next Permutation
- 33. Search in Rotated Sorted Array
- 36. Valid Sudoku
- 39. Combination Sum
- 46. Permutations
- 49. Group Anagrams
- 56. Merge Intervals
- 62. Unique Paths
- 79. Word Search
- 98. Validate Binary Search Tree
- 102. Binary Tree Level Order Traversal
- 127. Word Ladder
- 133. Clone Graph
- 139. Word Break
- 146. LRU Cache
- 152. Maximum Product Subarray
- 207. Course Schedule
- 215. Kth Largest Element in an Array
- 238. Product of Array Except Self
- 300. Longest Increasing Subsequence
- 322. Coin Change
- 347. Top K Frequent Elements
- 647. Palindromic Substrings
- 994. Rotting Oranges

### Hard Problems (9 problems)
- 4. Median of Two Sorted Arrays
- 23. Merge k Sorted Lists
- 41. First Missing Positive
- 42. Trapping Rain Water
- 51. N-Queens
- 72. Edit Distance
- 76. Minimum Window Substring
- 239. Sliding Window Maximum
- 297. Serialize and Deserialize Binary Tree

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
