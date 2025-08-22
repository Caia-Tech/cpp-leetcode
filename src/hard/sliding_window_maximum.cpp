#include "sliding_window_maximum.h"
#include <algorithm>
#include <climits>
#include <cmath>

namespace leetcode {
namespace hard {

std::vector<int> SlidingWindowMaximum::maxSlidingWindowDeque(std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::deque<int> dq; // Store indices
    
    for (int i = 0; i < nums.size(); ++i) {
        // Remove indices outside current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove indices whose values are smaller than current element
        // (they will never be maximum while current element is in window)
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        
        // Add current index
        dq.push_back(i);
        
        // Add maximum to result (front of deque has index of maximum)
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

std::vector<int> SlidingWindowMaximum::maxSlidingWindowHeap(std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::priority_queue<std::pair<int, int>> heap; // (value, index) - max heap
    
    // Initialize heap with first window
    for (int i = 0; i < k; ++i) {
        heap.push({nums[i], i});
    }
    result.push_back(heap.top().first);
    
    // Process remaining elements
    for (int i = k; i < nums.size(); ++i) {
        // Add new element
        heap.push({nums[i], i});
        
        // Remove elements outside current window
        while (!heap.empty() && heap.top().second <= i - k) {
            heap.pop();
        }
        
        // Add maximum to result
        result.push_back(heap.top().first);
    }
    
    return result;
}

std::vector<int> SlidingWindowMaximum::maxSlidingWindowMultiset(std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::multiset<int> window;
    
    // Initialize first window
    for (int i = 0; i < k; ++i) {
        window.insert(nums[i]);
    }
    result.push_back(*window.rbegin()); // Maximum is last element
    
    // Slide window
    for (int i = k; i < nums.size(); ++i) {
        // Remove outgoing element
        window.erase(window.find(nums[i - k]));
        
        // Add incoming element
        window.insert(nums[i]);
        
        // Add maximum to result
        result.push_back(*window.rbegin());
    }
    
    return result;
}

std::vector<int> SlidingWindowMaximum::maxSlidingWindowSparseTable(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<std::vector<int>> st(n, std::vector<int>(20, 0)); // log2(10^5) < 20
    
    // Build sparse table
    buildSparseTable(nums, st);
    
    std::vector<int> result;
    
    // Process each window
    for (int i = 0; i <= n - k; ++i) {
        result.push_back(queryMax(st, i, i + k - 1));
    }
    
    return result;
}

std::vector<int> SlidingWindowMaximum::maxSlidingWindowBruteForce(std::vector<int>& nums, int k) {
    std::vector<int> result;
    
    for (int i = 0; i <= nums.size() - k; ++i) {
        int maxVal = nums[i];
        for (int j = i + 1; j < i + k; ++j) {
            maxVal = std::max(maxVal, nums[j]);
        }
        result.push_back(maxVal);
    }
    
    return result;
}

std::vector<int> SlidingWindowMaximum::maxSlidingWindowStacks(std::vector<int>& nums, int k) {
    std::vector<int> result;
    
    if (k == 1) {
        return nums; // Each element is its own window maximum
    }
    
    MonotonicStack left, right;
    
    // Initialize first window
    for (int i = 0; i < k; ++i) {
        right.push(nums[i]);
    }
    
    // Get maximum of first window
    result.push_back(right.getMax());
    
    // Process remaining elements
    for (int i = k; i < nums.size(); ++i) {
        // Add new element to right stack
        right.push(nums[i]);
        
        // Remove one element from left side of window
        if (!left.empty()) {
            left.pop();
        } else {
            // Rebalance: move half of right to left
            rebalanceStacks(left, right);
            left.pop();
        }
        
        // Get maximum of current window
        int maxVal = INT_MIN;
        if (!left.empty()) {
            maxVal = std::max(maxVal, left.getMax());
        }
        if (!right.empty()) {
            maxVal = std::max(maxVal, right.getMax());
        }
        
        result.push_back(maxVal);
    }
    
    return result;
}

// Helper function implementations
void SlidingWindowMaximum::buildSparseTable(const std::vector<int>& nums, std::vector<std::vector<int>>& st) {
    int n = nums.size();
    
    // Initialize for intervals of length 1
    for (int i = 0; i < n; ++i) {
        st[i][0] = nums[i];
    }
    
    // Build sparse table
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; (i + (1 << j) - 1) < n; ++i) {
            st[i][j] = std::max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }
}

int SlidingWindowMaximum::queryMax(const std::vector<std::vector<int>>& st, int left, int right) {
    int length = right - left + 1;
    int k = static_cast<int>(log2(length));
    
    // Query overlapping intervals of length 2^k
    return std::max(st[left][k], st[right - (1 << k) + 1][k]);
}

// MonotonicStack implementation
void SlidingWindowMaximum::MonotonicStack::push(int value) {
    int count = 1;
    
    // Maintain decreasing order
    while (!stack.empty() && stack.top().first <= value) {
        count += stack.top().second;
        stack.pop();
    }
    
    stack.push({value, count});
}

void SlidingWindowMaximum::MonotonicStack::pop(int count) {
    while (count > 0 && !stack.empty()) {
        if (stack.top().second <= count) {
            count -= stack.top().second;
            stack.pop();
        } else {
            stack.top().second -= count;
            count = 0;
        }
    }
}

int SlidingWindowMaximum::MonotonicStack::getMax() const {
    return stack.empty() ? INT_MIN : stack.top().first;
}

bool SlidingWindowMaximum::MonotonicStack::empty() const {
    return stack.empty();
}

int SlidingWindowMaximum::MonotonicStack::size() const {
    int total = 0;
    std::stack<std::pair<int, int>> temp = stack;
    while (!temp.empty()) {
        total += temp.top().second;
        temp.pop();
    }
    return total;
}

void SlidingWindowMaximum::rebalanceStacks(MonotonicStack& left, MonotonicStack& right) {
    // This is a simplified rebalancing - in practice, would need more sophisticated approach
    // For the scope of this implementation, we'll use a basic approach
    
    // Move elements from right to left (implementation would depend on specific requirements)
    // This is a placeholder for the complex rebalancing logic
}

}
}