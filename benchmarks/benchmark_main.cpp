#include <benchmark/benchmark.h>
#include "easy/two_sum.h"
#include "easy/reverse_integer.h"
#include "easy/palindrome_number.h"
#include "easy/valid_parentheses.h"
#include "easy/best_time_to_buy_and_sell_stock.h"
#include "medium/longest_substring_without_repeating.h"
#include "medium/three_sum.h"
#include <vector>
#include <numeric>
#include <random>
#include <string>

using namespace leetcode::easy;
using namespace leetcode::medium;

// Two Sum Benchmarks
static void BM_TwoSumBruteForce(benchmark::State& state) {
    TwoSum solution;
    std::vector<int> nums(state.range(0));
    std::iota(nums.begin(), nums.end(), 1);
    int target = nums.size() + 1;
    
    for (auto _ : state) {
        auto result = solution.twoSumBruteForce(nums, target);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_TwoSumHashMapOnePass(benchmark::State& state) {
    TwoSum solution;
    std::vector<int> nums(state.range(0));
    std::iota(nums.begin(), nums.end(), 1);
    int target = nums.size() + 1;
    
    for (auto _ : state) {
        auto result = solution.twoSumHashMapOnePass(nums, target);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_TwoSumHashMapTwoPass(benchmark::State& state) {
    TwoSum solution;
    std::vector<int> nums(state.range(0));
    std::iota(nums.begin(), nums.end(), 1);
    int target = nums.size() + 1;
    
    for (auto _ : state) {
        auto result = solution.twoSumHashMapTwoPass(nums, target);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_TwoSumSortedTwoPointers(benchmark::State& state) {
    TwoSum solution;
    std::vector<int> nums(state.range(0));
    std::iota(nums.begin(), nums.end(), 1);
    int target = nums.size() + 1;
    
    for (auto _ : state) {
        auto result = solution.twoSumSortedTwoPointers(nums, target);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_TwoSumHashSet(benchmark::State& state) {
    TwoSum solution;
    std::vector<int> nums(state.range(0));
    std::iota(nums.begin(), nums.end(), 1);
    int target = nums.size() + 1;
    
    for (auto _ : state) {
        auto result = solution.twoSumHashSet(nums, target);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_TwoSumBinarySearch(benchmark::State& state) {
    TwoSum solution;
    std::vector<int> nums(state.range(0));
    std::iota(nums.begin(), nums.end(), 1);
    int target = nums.size() + 1;
    
    for (auto _ : state) {
        auto result = solution.twoSumBinarySearch(nums, target);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

// Reverse Integer Benchmarks
static void BM_ReverseIntegerMath(benchmark::State& state) {
    ReverseInteger solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.reverseMath(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_ReverseIntegerString(benchmark::State& state) {
    ReverseInteger solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.reverseString(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_ReverseIntegerLong(benchmark::State& state) {
    ReverseInteger solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.reverseLong(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_ReverseIntegerArray(benchmark::State& state) {
    ReverseInteger solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.reverseArray(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_ReverseIntegerRecursive(benchmark::State& state) {
    ReverseInteger solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.reverseRecursive(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_ReverseIntegerPreemptive(benchmark::State& state) {
    ReverseInteger solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.reversePreemptive(x);
        benchmark::DoNotOptimize(result);
    }
}

// Palindrome Number Benchmarks
static void BM_PalindromeFullReverse(benchmark::State& state) {
    PalindromeNumber solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.isPalindromeFullReverse(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_PalindromeHalfReverse(benchmark::State& state) {
    PalindromeNumber solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.isPalindromeHalfReverse(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_PalindromeString(benchmark::State& state) {
    PalindromeNumber solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.isPalindromeString(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_PalindromeArray(benchmark::State& state) {
    PalindromeNumber solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.isPalindromeArray(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_PalindromeRecursive(benchmark::State& state) {
    PalindromeNumber solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.isPalindromeRecursive(x);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_PalindromeDivision(benchmark::State& state) {
    PalindromeNumber solution;
    int x = state.range(0);
    
    for (auto _ : state) {
        auto result = solution.isPalindromeDivision(x);
        benchmark::DoNotOptimize(result);
    }
}

// Register Two Sum benchmarks
BENCHMARK(BM_TwoSumBruteForce)->Range(10, 10000)->Complexity();
BENCHMARK(BM_TwoSumHashMapOnePass)->Range(10, 10000)->Complexity();
BENCHMARK(BM_TwoSumHashMapTwoPass)->Range(10, 10000)->Complexity();
BENCHMARK(BM_TwoSumSortedTwoPointers)->Range(10, 10000)->Complexity();
BENCHMARK(BM_TwoSumHashSet)->Range(10, 10000)->Complexity();
BENCHMARK(BM_TwoSumBinarySearch)->Range(10, 10000)->Complexity();

// Register Reverse Integer benchmarks
BENCHMARK(BM_ReverseIntegerMath)->Arg(123456789);
BENCHMARK(BM_ReverseIntegerString)->Arg(123456789);
BENCHMARK(BM_ReverseIntegerLong)->Arg(123456789);
BENCHMARK(BM_ReverseIntegerArray)->Arg(123456789);
BENCHMARK(BM_ReverseIntegerRecursive)->Arg(123456789);
BENCHMARK(BM_ReverseIntegerPreemptive)->Arg(123456789);

// Valid Parentheses Benchmarks
static void BM_ValidParenthesesStack(benchmark::State& state) {
    ValidParentheses solution;
    std::string s = "()[]{}";
    for (int i = 0; i < state.range(0) / 6; ++i) {
        s += "()[]{}";
    }
    
    for (auto _ : state) {
        auto result = solution.isValidStack(s);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_ValidParenthesesArrayStack(benchmark::State& state) {
    ValidParentheses solution;
    std::string s = "()[]{}";
    for (int i = 0; i < state.range(0) / 6; ++i) {
        s += "()[]{}";
    }
    
    for (auto _ : state) {
        auto result = solution.isValidArrayStack(s);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

// Best Time to Buy and Sell Stock Benchmarks
static void BM_StockBruteForce(benchmark::State& state) {
    BestTimeToBuyAndSellStock solution;
    std::vector<int> prices(state.range(0));
    std::iota(prices.begin(), prices.end(), 1);
    
    for (auto _ : state) {
        auto result = solution.maxProfitBruteForce(prices);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_StockSinglePass(benchmark::State& state) {
    BestTimeToBuyAndSellStock solution;
    std::vector<int> prices(state.range(0));
    std::iota(prices.begin(), prices.end(), 1);
    
    for (auto _ : state) {
        auto result = solution.maxProfitSinglePass(prices);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

// Longest Substring Without Repeating Benchmarks
static void BM_LongestSubstringBruteForce(benchmark::State& state) {
    LongestSubstringWithoutRepeating solution;
    std::string s;
    for (int i = 0; i < state.range(0); ++i) {
        s += static_cast<char>('a' + (i % 26));
    }
    
    for (auto _ : state) {
        auto result = solution.lengthOfLongestSubstringBruteForce(s);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_LongestSubstringHashMap(benchmark::State& state) {
    LongestSubstringWithoutRepeating solution;
    std::string s;
    for (int i = 0; i < state.range(0); ++i) {
        s += static_cast<char>('a' + (i % 26));
    }
    
    for (auto _ : state) {
        auto result = solution.lengthOfLongestSubstringHashMap(s);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_LongestSubstringASCII(benchmark::State& state) {
    LongestSubstringWithoutRepeating solution;
    std::string s;
    for (int i = 0; i < state.range(0); ++i) {
        s += static_cast<char>('a' + (i % 26));
    }
    
    for (auto _ : state) {
        auto result = solution.lengthOfLongestSubstringASCII(s);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

// 3Sum Benchmarks
static void BM_ThreeSumBruteForce(benchmark::State& state) {
    ThreeSum solution;
    std::vector<int> nums(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        nums[i] = i - state.range(0) / 2;
    }
    
    for (auto _ : state) {
        auto numsCopy = nums;
        auto result = solution.threeSumBruteForce(numsCopy);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_ThreeSumTwoPointers(benchmark::State& state) {
    ThreeSum solution;
    std::vector<int> nums(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        nums[i] = i - state.range(0) / 2;
    }
    
    for (auto _ : state) {
        auto numsCopy = nums;
        auto result = solution.threeSumTwoPointers(numsCopy);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_ThreeSumOptimized(benchmark::State& state) {
    ThreeSum solution;
    std::vector<int> nums(state.range(0));
    for (int i = 0; i < state.range(0); ++i) {
        nums[i] = i - state.range(0) / 2;
    }
    
    for (auto _ : state) {
        auto numsCopy = nums;
        auto result = solution.threeSumOptimized(numsCopy);
        benchmark::DoNotOptimize(result);
    }
    state.SetComplexityN(state.range(0));
}

// Register Palindrome Number benchmarks
BENCHMARK(BM_PalindromeFullReverse)->Arg(1234554321);
BENCHMARK(BM_PalindromeHalfReverse)->Arg(1234554321);
BENCHMARK(BM_PalindromeString)->Arg(1234554321);
BENCHMARK(BM_PalindromeArray)->Arg(1234554321);
BENCHMARK(BM_PalindromeRecursive)->Arg(1234554321);
BENCHMARK(BM_PalindromeDivision)->Arg(1234554321);

// Register Valid Parentheses benchmarks
BENCHMARK(BM_ValidParenthesesStack)->Range(6, 600)->Complexity();
BENCHMARK(BM_ValidParenthesesArrayStack)->Range(6, 600)->Complexity();

// Register Stock benchmarks
BENCHMARK(BM_StockBruteForce)->Range(10, 1000)->Complexity();
BENCHMARK(BM_StockSinglePass)->Range(10, 10000)->Complexity();

// Register Longest Substring benchmarks
BENCHMARK(BM_LongestSubstringBruteForce)->Range(10, 100)->Complexity();
BENCHMARK(BM_LongestSubstringHashMap)->Range(10, 1000)->Complexity();
BENCHMARK(BM_LongestSubstringASCII)->Range(10, 1000)->Complexity();

// Register 3Sum benchmarks
BENCHMARK(BM_ThreeSumBruteForce)->Range(10, 100)->Complexity();
BENCHMARK(BM_ThreeSumTwoPointers)->Range(10, 500)->Complexity();
BENCHMARK(BM_ThreeSumOptimized)->Range(10, 500)->Complexity();

BENCHMARK_MAIN();