#include "product_except_self.h"
#include <stack>
#include <cmath>
#include <algorithm>

namespace leetcode {
namespace medium {

// ============================================================================
// Approach 1: Left and Right Product Arrays (Two-Pass)
// ============================================================================

std::vector<int> ProductExceptSelfTwoArrays::productExceptSelf(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> leftProducts(n, 1);
    std::vector<int> rightProducts(n, 1);
    std::vector<int> result(n);
    
    // Fill left products array
    for (int i = 1; i < n; i++) {
        leftProducts[i] = leftProducts[i - 1] * nums[i - 1];
    }
    
    // Fill right products array
    for (int i = n - 2; i >= 0; i--) {
        rightProducts[i] = rightProducts[i + 1] * nums[i + 1];
    }
    
    // Combine left and right products
    for (int i = 0; i < n; i++) {
        result[i] = leftProducts[i] * rightProducts[i];
    }
    
    return result;
}

// ============================================================================
// Approach 2: Single Pass with Division (Division Method)
// ============================================================================

std::vector<int> ProductExceptSelfDivision::productExceptSelf(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n);
    
    // Count zeros and calculate product of non-zero elements
    int zeroCount = 0;
    int product = 1;
    
    for (int num : nums) {
        if (num == 0) {
            zeroCount++;
        } else {
            product *= num;
        }
    }
    
    // Handle different cases based on zero count
    for (int i = 0; i < n; i++) {
        if (zeroCount > 1) {
            // Multiple zeros: all results are 0
            result[i] = 0;
        } else if (zeroCount == 1) {
            // Single zero: only that position gets the product
            result[i] = (nums[i] == 0) ? product : 0;
        } else {
            // No zeros: divide total product by current element
            result[i] = product / nums[i];
        }
    }
    
    return result;
}

// ============================================================================
// Approach 3: Two-Pass Optimal (Prefix/Suffix)
// ============================================================================

std::vector<int> ProductExceptSelfOptimal::productExceptSelf(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, 1);
    
    // First pass: fill result with left products
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] * nums[i - 1];
    }
    
    // Second pass: multiply with right products
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    
    return result;
}

// ============================================================================
// Approach 4: Single Pass with Stack (Stack-based)
// ============================================================================

std::vector<int> ProductExceptSelfStack::productExceptSelf(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n, 1);
    std::stack<int> stack;
    
    // Initialize result with left products using stack
    for (int i = 0; i < n; i++) {
        // Calculate left product for current position
        int leftProduct = 1;
        std::stack<int> tempStack = stack;
        while (!tempStack.empty()) {
            leftProduct *= nums[tempStack.top()];
            tempStack.pop();
        }
        result[i] = leftProduct;
        stack.push(i);
    }
    
    // Now multiply with right products
    stack = std::stack<int>(); // Clear stack
    for (int i = n - 1; i >= 0; i--) {
        // Calculate right product for current position
        int rightProduct = 1;
        std::stack<int> tempStack = stack;
        while (!tempStack.empty()) {
            rightProduct *= nums[tempStack.top()];
            tempStack.pop();
        }
        result[i] *= rightProduct;
        stack.push(i);
    }
    
    return result;
}

// ============================================================================
// Approach 5: Recursive with Memoization (Divide and Conquer)
// ============================================================================

std::vector<int> ProductExceptSelfRecursive::productExceptSelf(std::vector<int>& nums) {
    memo.clear();
    int n = nums.size();
    std::vector<int> result(n);
    
    for (int i = 0; i < n; i++) {
        // For each position, compute product of left and right parts
        std::vector<int> leftPart = (i > 0) ? helper(nums, 0, i - 1) : std::vector<int>{1};
        std::vector<int> rightPart = (i < n - 1) ? helper(nums, i + 1, n - 1) : std::vector<int>{1};
        
        int leftProduct = 1;
        for (int val : leftPart) leftProduct *= val;
        
        int rightProduct = 1;
        for (int val : rightPart) rightProduct *= val;
        
        result[i] = leftProduct * rightProduct;
    }
    
    return result;
}

std::vector<int> ProductExceptSelfRecursive::helper(std::vector<int>& nums, int start, int end) {
    if (start > end) return {1};
    if (start == end) return {nums[start]};
    
    std::string key = getKey(start, end);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
    
    int mid = start + (end - start) / 2;
    std::vector<int> left = helper(nums, start, mid);
    std::vector<int> right = helper(nums, mid + 1, end);
    
    // Combine left and right results
    std::vector<int> result;
    for (int val : left) result.push_back(val);
    for (int val : right) result.push_back(val);
    
    memo[key] = result;
    return result;
}

std::string ProductExceptSelfRecursive::getKey(int start, int end) {
    return std::to_string(start) + "," + std::to_string(end);
}

// ============================================================================
// Approach 6: Logarithmic Transformation (Mathematical)
// ============================================================================

std::vector<int> ProductExceptSelfLogarithmic::productExceptSelf(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n);
    
    // Handle zeros separately
    int zeroCount = 0;
    int zeroIndex = -1;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) {
            zeroCount++;
            zeroIndex = i;
        }
    }
    
    if (zeroCount > 1) {
        // Multiple zeros: all results are 0
        return std::vector<int>(n, 0);
    } else if (zeroCount == 1) {
        // Single zero: compute product of all non-zero elements
        int product = 1;
        for (int i = 0; i < n; i++) {
            if (i != zeroIndex) {
                product *= nums[i];
            }
        }
        result[zeroIndex] = product;
        return result;
    }
    
    // No zeros: use logarithmic approach
    std::vector<double> logs(n);
    double totalLogSum = 0;
    
    // Calculate logarithms and handle negative numbers
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            logs[i] = std::log(nums[i]);
        } else {
            // For negative numbers, we'll handle the sign separately
            logs[i] = std::log(-nums[i]);
        }
        totalLogSum += logs[i];
    }
    
    // Count negative numbers to determine final sign
    int negativeCount = 0;
    for (int num : nums) {
        if (num < 0) negativeCount++;
    }
    
    // Calculate results
    for (int i = 0; i < n; i++) {
        double logResult = totalLogSum - logs[i];
        int absResult = static_cast<int>(std::round(std::exp(logResult)));
        
        // Determine sign: if we exclude nums[i] and remaining negative count is odd
        int remainingNegatives = negativeCount;
        if (nums[i] < 0) remainingNegatives--;
        
        result[i] = (remainingNegatives % 2 == 0) ? absResult : -absResult;
    }
    
    return result;
}

}
}