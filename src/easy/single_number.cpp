#include "single_number.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: XOR Bit Manipulation (Optimal)
int SingleNumber::singleNumberXOR(std::vector<int>& nums) {
    int result = 0;
    
    // XOR all numbers - pairs cancel out, leaving only the single number
    for (int num : nums) {
        result ^= num;
    }
    
    return result;
}

// Approach 2: Hash Map Counting
int SingleNumber::singleNumberHashMap(std::vector<int>& nums) {
    std::unordered_map<int, int> count_map;
    
    // Count occurrences of each number
    for (int num : nums) {
        count_map[num]++;
    }
    
    // Find the number with count 1
    for (const auto& pair : count_map) {
        if (pair.second == 1) {
            return pair.first;
        }
    }
    
    // Should never reach here given problem constraints
    return 0;
}

// Approach 3: Hash Set Toggle
int SingleNumber::singleNumberHashSet(std::vector<int>& nums) {
    std::unordered_set<int> unique_set;
    
    for (int num : nums) {
        // If number exists in set, remove it (second occurrence)
        // If not, add it (first occurrence)
        if (unique_set.find(num) != unique_set.end()) {
            unique_set.erase(num);
        } else {
            unique_set.insert(num);
        }
    }
    
    // The single number is the only one left in the set
    return *unique_set.begin();
}

// Approach 4: Sorting
int SingleNumber::singleNumberSort(std::vector<int>& nums) {
    // Sort the array
    std::sort(nums.begin(), nums.end());
    
    int n = nums.size();
    
    // Check pairs - if a number doesn't match its pair, it's the single one
    for (int i = 0; i < n - 1; i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    
    // If we haven't found it yet, it must be the last element
    return nums[n - 1];
}

// Approach 5: Mathematical Sum
int SingleNumber::singleNumberMath(std::vector<int>& nums) {
    std::unordered_set<int> unique_nums(nums.begin(), nums.end());
    
    // Calculate sum of unique elements
    long long unique_sum = 0;
    for (int num : unique_nums) {
        unique_sum += num;
    }
    
    // Calculate sum of all elements
    long long total_sum = 0;
    for (int num : nums) {
        total_sum += num;
    }
    
    // The single number = 2 * sum(unique) - sum(all)
    // This works because if all appeared twice, sum would be 2 * sum(unique)
    // The difference is the single number
    return static_cast<int>(2 * unique_sum - total_sum);
}

// Approach 6: Bit Counting
int SingleNumber::singleNumberBitCount(std::vector<int>& nums) {
    int result = 0;
    
    // Check each bit position
    for (int bit = 0; bit < INT_BITS; ++bit) {
        int count = 0;
        
        // Count how many numbers have this bit set
        for (int num : nums) {
            if (num & (1 << bit)) {
                count++;
            }
        }
        
        // If count is odd, this bit is set in the single number
        // (pairs contribute even count, single contributes 1)
        if (count % 2 == 1) {
            result |= (1 << bit);
        }
    }
    
    return result;
}

}  // namespace easy
}  // namespace leetcode