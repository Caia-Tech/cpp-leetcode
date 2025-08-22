#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <array>

namespace leetcode {
namespace easy {

/**
 * Problem 412: Fizz Buzz
 *
 * Return a string array answer (1-indexed) where:
 * - answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
 * - answer[i] == "Fizz" if i is divisible by 3.
 * - answer[i] == "Buzz" if i is divisible by 5.
 * - answer[i] == i (as a string) if none of the above conditions are true.
 *
 * Each class below demonstrates a distinct strategy for generating the sequence
 * along with reasoning and complexity analysis.
 */

/**
 * Approach 1: Classic If-Else Chain
 *
 * Straightforward conditional checks for divisibility by 15, 3, and 5.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) excluding output
 */
class FizzBuzzIfElse {
public:
    std::vector<std::string> fizzBuzz(int n);
};

/**
 * Approach 2: String Concatenation
 *
 * Build the string by appending "Fizz" for multiples of 3 and "Buzz" for
 * multiples of 5, falling back to the number when empty.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) excluding output
 */
class FizzBuzzConcat {
public:
    std::vector<std::string> fizzBuzz(int n);
};

/**
 * Approach 3: Hash Map of Divisors
 *
 * Iterate over a map of {divisor -> word} pairs and concatenate matches.
 * Demonstrates extensibility to other rules.
 *
 * Time Complexity: O(n * k) where k is number of rules (here 2)
 * Space Complexity: O(1) excluding output
 */
class FizzBuzzMap {
public:
    std::vector<std::string> fizzBuzz(int n);
};

/**
 * Approach 4: Switch on Modulo 15
 *
 * Use a switch statement on i % 15 to directly map patterns.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) excluding output
 */
class FizzBuzzSwitch {
public:
    std::vector<std::string> fizzBuzz(int n);
};

/**
 * Approach 5: Precomputed 15-Element Cycle
 *
 * Precompute the answers for numbers 1..15 and reuse them for higher numbers
 * by indexing into the cycle.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(15) ~ O(1)
 */
class FizzBuzzPrecompute {
public:
    std::vector<std::string> fizzBuzz(int n);
};

/**
 * Approach 6: Modulo Lookup Arrays
 *
 * Use arrays indexed by the remainder of division by 3 and 5 to fetch the
 * appropriate substrings and concatenate them.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) excluding output
 */
class FizzBuzzModuloArray {
public:
    std::vector<std::string> fizzBuzz(int n);
};

} // namespace easy
} // namespace leetcode

