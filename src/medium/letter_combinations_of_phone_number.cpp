#include "letter_combinations_of_phone_number.h"
#include <stack>

namespace leetcode {
namespace medium {

// Static member definition
const std::unordered_map<char, std::string> LetterCombinationsOfPhoneNumber::phoneMap = {
    {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
    {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
};

std::vector<std::string> LetterCombinationsOfPhoneNumber::letterCombinationsBacktracking(const std::string& digits) {
    if (digits.empty()) return {};
    
    std::vector<std::string> result;
    std::string current;
    backtrackHelper(digits, 0, current, result);
    return result;
}

void LetterCombinationsOfPhoneNumber::backtrackHelper(const std::string& digits, int index, 
                                                     std::string& current, std::vector<std::string>& result) {
    // Base case: we've processed all digits
    if (index == digits.length()) {
        result.push_back(current);
        return;
    }
    
    // Try each letter for the current digit
    const std::string& letters = phoneMap.at(digits[index]);
    for (char letter : letters) {
        current.push_back(letter);  // Make choice
        backtrackHelper(digits, index + 1, current, result);  // Recurse
        current.pop_back();  // Backtrack (undo choice)
    }
}

std::vector<std::string> LetterCombinationsOfPhoneNumber::letterCombinationsIterative(const std::string& digits) {
    if (digits.empty()) return {};
    
    std::queue<std::string> queue;
    queue.push("");
    
    for (char digit : digits) {
        const std::string& letters = phoneMap.at(digit);
        int queueSize = queue.size();
        
        // Process all combinations at current level
        for (int i = 0; i < queueSize; ++i) {
            std::string current = queue.front();
            queue.pop();
            
            // Extend current combination with each possible letter
            for (char letter : letters) {
                queue.push(current + letter);
            }
        }
    }
    
    // Convert queue to vector
    std::vector<std::string> result;
    while (!queue.empty()) {
        result.push_back(queue.front());
        queue.pop();
    }
    
    return result;
}

std::vector<std::string> LetterCombinationsOfPhoneNumber::letterCombinationsDP(const std::string& digits) {
    if (digits.empty()) return {};
    
    std::vector<std::vector<std::string>> dp(digits.length() + 1);
    dp[0] = {""};  // Base case: empty combination
    
    for (int i = 1; i <= digits.length(); ++i) {
        char digit = digits[i - 1];
        const std::string& letters = phoneMap.at(digit);
        
        // Combine all combinations from previous step with each letter of current digit
        for (const std::string& prev : dp[i - 1]) {
            for (char letter : letters) {
                dp[i].push_back(prev + letter);
            }
        }
    }
    
    return dp[digits.length()];
}

std::vector<std::string> LetterCombinationsOfPhoneNumber::letterCombinationsRecursiveFunc(const std::string& digits) {
    return generateCombinationsRecursive(digits, 0);
}

std::vector<std::string> LetterCombinationsOfPhoneNumber::generateCombinationsRecursive(const std::string& digits, int index) {
    // Base case: no more digits to process
    if (index == digits.length()) {
        return {""};
    }
    
    // Get combinations for remaining digits
    std::vector<std::string> restCombinations = generateCombinationsRecursive(digits, index + 1);
    
    // Combine current digit's letters with rest combinations
    std::vector<std::string> result;
    const std::string& letters = phoneMap.at(digits[index]);
    
    for (char letter : letters) {
        for (const std::string& rest : restCombinations) {
            result.push_back(letter + rest);
        }
    }
    
    return result;
}

std::vector<std::string> LetterCombinationsOfPhoneNumber::letterCombinationsBitManip(const std::string& digits) {
    if (digits.empty()) return {};
    
    // Calculate total number of combinations
    int totalCombinations = 1;
    std::vector<int> bases;
    
    for (char digit : digits) {
        int letterCount = phoneMap.at(digit).length();
        bases.push_back(letterCount);
        totalCombinations *= letterCount;
    }
    
    std::vector<std::string> result;
    result.reserve(totalCombinations);
    
    // Generate each combination using base-k counting
    for (int combo = 0; combo < totalCombinations; ++combo) {
        std::string current;
        int temp = combo;
        
        // Extract digit choice for each position
        for (int i = digits.length() - 1; i >= 0; --i) {
            int letterChoice = temp % bases[i];
            temp /= bases[i];
            
            const std::string& letters = phoneMap.at(digits[i]);
            current = letters[letterChoice] + current;
        }
        
        result.push_back(current);
    }
    
    return result;
}

std::vector<std::string> LetterCombinationsOfPhoneNumber::letterCombinationsStack(const std::string& digits) {
    if (digits.empty()) return {};
    
    std::vector<std::string> result;
    std::stack<StackState> stack;
    
    // Initialize stack with first digit's letters
    const std::string& firstLetters = phoneMap.at(digits[0]);
    for (int i = firstLetters.length() - 1; i >= 0; --i) {
        stack.push(StackState(std::string(1, firstLetters[i]), 1, 0));
    }
    
    while (!stack.empty()) {
        StackState state = stack.top();
        stack.pop();
        
        // If we've processed all digits, add to result
        if (state.digitIndex == digits.length()) {
            result.push_back(state.current);
            continue;
        }
        
        // Add next level states to stack
        const std::string& letters = phoneMap.at(digits[state.digitIndex]);
        for (int i = letters.length() - 1; i >= 0; --i) {
            std::string newCurrent = state.current + letters[i];
            stack.push(StackState(newCurrent, state.digitIndex + 1, 0));
        }
    }
    
    return result;
}

}
}