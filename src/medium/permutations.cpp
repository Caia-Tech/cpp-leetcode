#include "permutations.h"
#include <stack>

namespace leetcode {
namespace medium {

std::vector<std::vector<int>> Permutations::permuteBacktracking(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::vector<bool> used(nums.size(), false);
    
    backtrackHelper(nums, current, used, result);
    return result;
}

void Permutations::backtrackHelper(std::vector<int>& nums, std::vector<int>& current, 
                                 std::vector<bool>& used, std::vector<std::vector<int>>& result) {
    // Base case: current permutation is complete
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    
    // Try each unused element at current position
    for (int i = 0; i < nums.size(); ++i) {
        if (!used[i]) {
            // Choose: add element to current permutation
            current.push_back(nums[i]);
            used[i] = true;
            
            // Explore: recursively generate rest of permutation
            backtrackHelper(nums, current, used, result);
            
            // Unchoose: backtrack for next iteration
            current.pop_back();
            used[i] = false;
        }
    }
}

std::vector<std::vector<int>> Permutations::permuteSwapping(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    swapHelper(nums, 0, result);
    return result;
}

void Permutations::swapHelper(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result) {
    // Base case: all positions filled
    if (start == nums.size()) {
        result.push_back(nums);
        return;
    }
    
    // For each position from start to end
    for (int i = start; i < nums.size(); ++i) {
        // Swap current element to start position
        std::swap(nums[start], nums[i]);
        
        // Recursively generate permutations for remaining positions
        swapHelper(nums, start + 1, result);
        
        // Backtrack: restore original order
        std::swap(nums[start], nums[i]);
    }
}

std::vector<std::vector<int>> Permutations::permuteNextPermutation(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    
    // Sort to get first permutation in lexicographic order
    std::sort(nums.begin(), nums.end());
    
    do {
        result.push_back(nums);
    } while (std::next_permutation(nums.begin(), nums.end()));
    
    return result;
}

std::vector<std::vector<int>> Permutations::permuteHeaps(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    heapsHelper(nums, nums.size(), result);
    return result;
}

void Permutations::heapsHelper(std::vector<int>& nums, int n, std::vector<std::vector<int>>& result) {
    // Base case: single element permutation
    if (n == 1) {
        result.push_back(nums);
        return;
    }
    
    for (int i = 0; i < n; ++i) {
        // Generate permutations with first n-1 elements
        heapsHelper(nums, n - 1, result);
        
        // Swap based on n being odd or even
        if (n % 2 == 1) {
            // n is odd: swap first and last
            std::swap(nums[0], nums[n - 1]);
        } else {
            // n is even: swap i-th and last
            std::swap(nums[i], nums[n - 1]);
        }
    }
}

std::vector<std::vector<int>> Permutations::permuteIterative(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::stack<IterativeState> stack;
    
    // Start with empty permutation
    stack.push(IterativeState({}, {}));
    
    while (!stack.empty()) {
        IterativeState state = stack.top();
        stack.pop();
        
        // Complete permutation found
        if (state.current.size() == nums.size()) {
            result.push_back(state.current);
            continue;
        }
        
        // Try each unused element
        for (int num : nums) {
            if (state.used.find(num) == state.used.end()) {
                // Create new state with current element added
                std::vector<int> newCurrent = state.current;
                newCurrent.push_back(num);
                
                std::unordered_set<int> newUsed = state.used;
                newUsed.insert(num);
                
                stack.push(IterativeState(newCurrent, newUsed));
            }
        }
    }
    
    return result;
}

std::vector<std::vector<int>> Permutations::permuteFactorialSystem(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    
    // Calculate n! (factorial)
    int factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    
    // Generate all permutations using factorial number system
    for (int i = 0; i < factorial; ++i) {
        // Convert i to factorial base
        std::vector<int> factorialBase = intToFactorialBase(i, n);
        
        // Convert factorial base to permutation
        std::vector<int> permutation = factorialToPermutation(nums, factorialBase);
        
        result.push_back(permutation);
    }
    
    return result;
}

std::vector<int> Permutations::factorialToPermutation(const std::vector<int>& nums, 
                                                    const std::vector<int>& factorialBase) {
    std::vector<int> available = nums;  // Copy of available elements
    std::vector<int> result;
    
    for (int digit : factorialBase) {
        // Use factorial base digit as index into available elements
        result.push_back(available[digit]);
        
        // Remove used element from available list
        available.erase(available.begin() + digit);
    }
    
    return result;
}

std::vector<int> Permutations::intToFactorialBase(int num, int base) {
    std::vector<int> result;
    
    for (int i = 1; i <= base; ++i) {
        result.push_back(num % i);
        num /= i;
    }
    
    // Reverse to get most significant digit first
    std::reverse(result.begin(), result.end());
    return result;
}

}
}