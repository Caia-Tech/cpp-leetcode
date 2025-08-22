#include "container_with_most_water.h"

namespace leetcode {
namespace medium {

int ContainerWithMostWater::maxAreaTwoPointers(const std::vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int maxArea = 0;
    
    while (left < right) {
        int currentArea = std::min(height[left], height[right]) * (right - left);
        maxArea = std::max(maxArea, currentArea);
        
        // Move the pointer with smaller height
        if (height[left] < height[right]) {
            ++left;
        } else {
            --right;
        }
    }
    
    return maxArea;
}

int ContainerWithMostWater::maxAreaBruteForce(const std::vector<int>& height) {
    int maxArea = 0;
    int n = height.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int currentArea = std::min(height[i], height[j]) * (j - i);
            maxArea = std::max(maxArea, currentArea);
        }
    }
    
    return maxArea;
}

int ContainerWithMostWater::maxAreaDivideConquer(const std::vector<int>& height) {
    return maxAreaHelper(height, 0, height.size() - 1);
}

int ContainerWithMostWater::maxAreaHelper(const std::vector<int>& height, int left, int right) {
    if (left >= right) return 0;
    
    int mid = left + (right - left) / 2;
    
    // Maximum area in left half
    int leftMax = maxAreaHelper(height, left, mid);
    
    // Maximum area in right half
    int rightMax = maxAreaHelper(height, mid + 1, right);
    
    // Maximum area crossing the middle
    int crossMax = findMaxCrossingArea(height, left, mid, right);
    
    return std::max({leftMax, rightMax, crossMax});
}

int ContainerWithMostWater::findMaxCrossingArea(const std::vector<int>& height, int left, int mid, int right) {
    int maxArea = 0;
    
    // Try all combinations where one line is from left half and one from right half
    for (int i = left; i <= mid; ++i) {
        for (int j = mid + 1; j <= right; ++j) {
            int area = std::min(height[i], height[j]) * (j - i);
            maxArea = std::max(maxArea, area);
        }
    }
    
    return maxArea;
}

int ContainerWithMostWater::maxAreaStack(const std::vector<int>& height) {
    std::stack<int> stack;
    int maxArea = 0;
    int n = height.size();
    
    for (int i = 0; i < n; ++i) {
        while (!stack.empty() && height[i] >= height[stack.top()]) {
            int h = height[stack.top()];
            stack.pop();
            
            if (!stack.empty()) {
                int width = i - stack.top() - 1;
                maxArea = std::max(maxArea, h * width);
            }
        }
        stack.push(i);
    }
    
    // Also consider containers formed by remaining elements in stack
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int area = std::min(height[i], height[j]) * (j - i);
            maxArea = std::max(maxArea, area);
        }
    }
    
    return maxArea;
}

int ContainerWithMostWater::maxAreaOptimizedBruteForce(const std::vector<int>& height) {
    int maxArea = 0;
    int n = height.size();
    
    for (int i = 0; i < n - 1; ++i) {
        // Early termination: if remaining width * max possible height <= current max
        int maxPossibleArea = (n - 1 - i) * height[i];
        if (maxPossibleArea <= maxArea) continue;
        
        for (int j = i + 1; j < n; ++j) {
            int currentArea = std::min(height[i], height[j]) * (j - i);
            maxArea = std::max(maxArea, currentArea);
            
            // If current height[j] is much smaller, skip similar heights
            if (height[j] < height[i] / 2) {
                while (j + 1 < n && height[j + 1] <= height[j]) {
                    ++j;
                }
            }
        }
    }
    
    return maxArea;
}

int ContainerWithMostWater::maxAreaBinarySearch(const std::vector<int>& height) {
    int maxArea = 0;
    int n = height.size();
    
    // Create a vector of (height, index) pairs and sort by height
    std::vector<std::pair<int, int>> sortedHeights;
    for (int i = 0; i < n; ++i) {
        sortedHeights.push_back({height[i], i});
    }
    std::sort(sortedHeights.begin(), sortedHeights.end());
    
    for (int i = 0; i < n; ++i) {
        // For each line, find the farthest line of at least the same height
        int currentHeight = height[i];
        
        // Binary search for first element >= currentHeight
        auto it = std::lower_bound(sortedHeights.begin(), sortedHeights.end(),
                                   std::make_pair(currentHeight, -1));
        
        // Check all lines with height >= currentHeight
        while (it != sortedHeights.end()) {
            int j = it->second;
            if (j != i) {
                int area = std::min(height[i], height[j]) * std::abs(j - i);
                maxArea = std::max(maxArea, area);
            }
            ++it;
        }
    }
    
    return maxArea;
}

}
}