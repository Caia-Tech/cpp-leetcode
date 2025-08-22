#pragma once

#include <vector>
#include <unordered_map>

namespace leetcode {
namespace medium {

/**
 * Problem 238: Product of Array Except Self
 * 
 * Given an integer array nums, return an array answer such that answer[i] 
 * is equal to the product of all the elements of nums except nums[i].
 * 
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using the division operator.
 * 
 * Follow up: Can you solve the problem in O(1) extra memory space? (The output 
 * array does not count as extra memory space for space complexity analysis.)
 * 
 * Constraints:
 * - 2 <= nums.length <= 10^5
 * - -30 <= nums[i] <= 30
 * - The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * 
 * @author Marvin Tutt, Caia Tech
 * Implementation with detailed reasoning and comprehensive testing
 */

/**
 * Approach 1: Left and Right Product Arrays (Two-Pass)
 * 
 * Create separate arrays for left and right products, then combine them.
 * 
 * Reasoning: This is the most intuitive approach for understanding the problem.
 * We create one array storing the product of all elements to the left of each
 * index, and another array storing the product of all elements to the right.
 * The final answer is the element-wise product of these two arrays. This
 * approach clearly separates the left and right computations, making it easy
 * to understand and debug.
 * 
 * Time Complexity: O(n) - three passes through the array
 * Space Complexity: O(n) - two additional arrays of size n
 * 
 * Best when: Learning the problem, clear separation of concerns
 * Worst when: Memory optimization needed
 */
class ProductExceptSelfTwoArrays {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums);
};

/**
 * Approach 2: Single Pass with Division (Division Method)
 * 
 * Calculate total product and divide by each element to get result.
 * 
 * Reasoning: The mathematical approach is to compute the total product of all
 * elements, then for each position, divide by that element to get the product
 * of all others. We need special handling for zeros: if there's one zero, only
 * that position gets the product of all other elements; if there are multiple
 * zeros, all results are zero. This approach is mathematically elegant but
 * violates the problem constraint of not using division.
 * 
 * Time Complexity: O(n) - single pass to compute product, single pass to divide
 * Space Complexity: O(1) - excluding output array
 * 
 * Best when: Division allowed, mathematical approach preferred
 * Worst when: Division operator forbidden (violates constraint)
 */
class ProductExceptSelfDivision {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums);
};

/**
 * Approach 3: Two-Pass Optimal (Prefix/Suffix)
 * 
 * Use output array to store left products, then multiply with right products in-place.
 * 
 * Reasoning: This is the optimal solution that satisfies all constraints. In the
 * first pass, we store the product of all elements to the left of each index
 * in the output array. In the second pass, we traverse from right to left,
 * maintaining a running product of elements to the right, and multiply this
 * with the stored left products. This achieves O(1) extra space while maintaining
 * O(n) time complexity.
 * 
 * Time Complexity: O(n) - two passes through the array
 * Space Complexity: O(1) - only using the output array and a few variables
 * 
 * Best when: Optimal solution needed, space constraint important
 * Worst when: Clarity over optimization preferred
 */
class ProductExceptSelfOptimal {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums);
};

/**
 * Approach 4: Single Pass with Stack (Stack-based)
 * 
 * Use stack to maintain products and compute results in one traversal.
 * 
 * Reasoning: This approach uses a stack-based method to compute the product
 * array in a single pass. We push indices onto a stack and maintain running
 * products. When we process each element, we update the products for previous
 * elements using the stack. While this demonstrates an alternative approach
 * using data structures, it's more complex than necessary for this problem
 * and doesn't improve the time or space complexity.
 * 
 * Time Complexity: O(n) - single pass with stack operations
 * Space Complexity: O(n) - stack storage in worst case
 * 
 * Best when: Learning stack applications, single-pass preference
 * Worst when: Simplicity or space optimization needed
 */
class ProductExceptSelfStack {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums);
};

/**
 * Approach 5: Recursive with Memoization (Divide and Conquer)
 * 
 * Use recursion to divide the problem and memoize intermediate results.
 * 
 * Reasoning: This approach applies divide-and-conquer thinking to the problem.
 * We recursively compute the product for left and right halves of the array,
 * then combine them to get the final result. Memoization ensures we don't
 * recompute the same subproblems. While this demonstrates recursive problem
 * solving techniques, it's overkill for this particular problem and has
 * higher space complexity due to recursion stack and memoization.
 * 
 * Time Complexity: O(n log n) - divide and conquer with memoization
 * Space Complexity: O(n) - recursion stack and memoization table
 * 
 * Best when: Exploring divide-and-conquer, learning recursion patterns
 * Worst when: Performance optimization needed, simple solution preferred
 */
class ProductExceptSelfRecursive {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums);
    
private:
    std::unordered_map<std::string, std::vector<int>> memo;
    std::vector<int> helper(std::vector<int>& nums, int start, int end);
    std::string getKey(int start, int end);
};

/**
 * Approach 6: Logarithmic Transformation (Mathematical)
 * 
 * Use logarithms to convert multiplication to addition, then convert back.
 * 
 * Reasoning: This mathematical approach converts the multiplication problem
 * into an addition problem using logarithms. We compute log of each element,
 * find the sum, then for each position subtract that element's log and take
 * the exponential. This requires careful handling of zeros and negative numbers.
 * While mathematically interesting, this approach has precision issues with
 * floating-point arithmetic and is not practical for integer arrays.
 * 
 * Time Complexity: O(n) - single pass with log/exp operations
 * Space Complexity: O(n) - array to store logarithms
 * 
 * Best when: Mathematical exploration, learning log properties
 * Worst when: Precision important, integer arithmetic required
 */
class ProductExceptSelfLogarithmic {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums);
    
private:
    const double EPSILON = 1e-9;
};

}
}