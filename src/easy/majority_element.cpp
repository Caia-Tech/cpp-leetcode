#include "majority_element.h"
#include <numeric>

namespace leetcode {
namespace easy {

// Approach 1: Boyer-Moore Voting Algorithm (Optimal)
int MajorityElement::majorityElementBoyerMoore(std::vector<int>& nums) {
    int candidate = 0;
    int count = 0;
    
    for (int num : nums) {
        if (count == 0) {
            candidate = num;
            count = 1;
        } else if (num == candidate) {
            count++;
        } else {
            count--;
        }
    }
    
    return candidate;
}

// Approach 2: Hash Map Counting
int MajorityElement::majorityElementHashMap(std::vector<int>& nums) {
    std::unordered_map<int, int> counts;
    int n = nums.size();
    int threshold = n / 2;
    
    for (int num : nums) {
        counts[num]++;
        if (counts[num] > threshold) {
            return num;
        }
    }
    
    // Should never reach here if majority element exists
    return nums[0];
}

// Approach 3: Sorting
int MajorityElement::majorityElementSorting(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];
}

// Approach 4: Divide and Conquer
int MajorityElement::majorityElementDivideConquer(std::vector<int>& nums) {
    return majorityElementDivideConquerHelper(nums, 0, nums.size() - 1);
}

int MajorityElement::majorityElementDivideConquerHelper(std::vector<int>& nums, int left, int right) {
    // Base case: single element
    if (left == right) {
        return nums[left];
    }
    
    // Divide: find majority in left and right halves
    int mid = left + (right - left) / 2;
    int leftMajority = majorityElementDivideConquerHelper(nums, left, mid);
    int rightMajority = majorityElementDivideConquerHelper(nums, mid + 1, right);
    
    // If both halves agree on the majority element
    if (leftMajority == rightMajority) {
        return leftMajority;
    }
    
    // Otherwise, count each element and return the one with higher count
    int leftCount = countInRange(nums, leftMajority, left, right);
    int rightCount = countInRange(nums, rightMajority, left, right);
    
    return leftCount > rightCount ? leftMajority : rightMajority;
}

int MajorityElement::countInRange(std::vector<int>& nums, int target, int left, int right) {
    int count = 0;
    for (int i = left; i <= right; i++) {
        if (nums[i] == target) {
            count++;
        }
    }
    return count;
}

// Approach 5: Bit Manipulation
int MajorityElement::majorityElementBitManipulation(std::vector<int>& nums) {
    int result = 0;
    int n = nums.size();
    
    // Check each bit position
    for (int bit = 0; bit < 32; bit++) {
        int setBitCount = 0;
        int mask = 1 << bit;
        
        // Count how many numbers have this bit set
        for (int num : nums) {
            if (num & mask) {
                setBitCount++;
            }
        }
        
        // If majority have this bit set, set it in result
        if (setBitCount > n / 2) {
            result |= mask;
        }
    }
    
    return result;
}

// Approach 6: Functional Programming with Reduce
int MajorityElement::majorityElementFunctional(std::vector<int>& nums) {
    auto voteReducer = createVoteReducer();
    
    VoteState initialState = {0, 0};
    
    VoteState finalState = std::accumulate(
        nums.begin(), 
        nums.end(),
        initialState,
        voteReducer
    );
    
    return finalState.candidate;
}

std::function<MajorityElement::VoteState(MajorityElement::VoteState, int)> 
MajorityElement::createVoteReducer() {
    return [](VoteState state, int num) -> VoteState {
        if (state.count == 0) {
            return {num, 1};
        } else if (state.candidate == num) {
            return {state.candidate, state.count + 1};
        } else {
            return {state.candidate, state.count - 1};
        }
    };
}

}  // namespace easy
}  // namespace leetcode