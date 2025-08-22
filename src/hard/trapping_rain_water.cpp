#include "trapping_rain_water.h"
#include <algorithm>
#include <stack>

namespace leetcode {
namespace hard {

int TrappingRainWater::trapBruteForce(std::vector<int>& height) {
    if (height.size() < 3) return 0;
    
    int water = 0;
    int n = height.size();
    
    for (int i = 1; i < n - 1; ++i) {
        int leftMax = 0, rightMax = 0;
        
        for (int j = i; j >= 0; --j) {
            leftMax = std::max(leftMax, height[j]);
        }
        
        for (int j = i; j < n; ++j) {
            rightMax = std::max(rightMax, height[j]);
        }
        
        water += std::min(leftMax, rightMax) - height[i];
    }
    
    return water;
}

int TrappingRainWater::trapDP(std::vector<int>& height) {
    if (height.size() < 3) return 0;
    
    int n = height.size();
    std::vector<int> leftMax(n), rightMax(n);
    
    leftMax[0] = height[0];
    for (int i = 1; i < n; ++i) {
        leftMax[i] = std::max(leftMax[i - 1], height[i]);
    }
    
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        rightMax[i] = std::max(rightMax[i + 1], height[i]);
    }
    
    int water = 0;
    for (int i = 1; i < n - 1; ++i) {
        water += std::min(leftMax[i], rightMax[i]) - height[i];
    }
    
    return water;
}

int TrappingRainWater::trapStack(std::vector<int>& height) {
    if (height.size() < 3) return 0;
    
    std::stack<int> stack;
    int water = 0;
    
    for (int i = 0; i < height.size(); ++i) {
        while (!stack.empty() && height[i] > height[stack.top()]) {
            int top = stack.top();
            stack.pop();
            
            if (stack.empty()) break;
            
            int distance = i - stack.top() - 1;
            int boundedHeight = std::min(height[i], height[stack.top()]) - height[top];
            water += distance * boundedHeight;
        }
        
        stack.push(i);
    }
    
    return water;
}

int TrappingRainWater::trapTwoPointers(std::vector<int>& height) {
    if (height.size() < 3) return 0;
    
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    
    return water;
}

int TrappingRainWater::trapHorizontal(std::vector<int>& height) {
    if (height.size() < 3) return 0;
    
    int maxHeight = *std::max_element(height.begin(), height.end());
    int water = 0;
    
    for (int level = 1; level <= maxHeight; ++level) {
        int left = -1;
        
        for (int i = 0; i < height.size(); ++i) {
            if (height[i] >= level) {
                if (left != -1) {
                    water += i - left - 1;
                }
                left = i;
            }
        }
    }
    
    return water;
}

int TrappingRainWater::trapOptimized(std::vector<int>& height) {
    if (height.size() < 3) return 0;
    
    int n = height.size();
    int water = 0;
    int maxIdx = 0;
    
    for (int i = 1; i < n; ++i) {
        if (height[i] > height[maxIdx]) {
            maxIdx = i;
        }
    }
    
    int leftMax = 0;
    for (int i = 0; i < maxIdx; ++i) {
        if (height[i] > leftMax) {
            leftMax = height[i];
        } else {
            water += leftMax - height[i];
        }
    }
    
    int rightMax = 0;
    for (int i = n - 1; i > maxIdx; --i) {
        if (height[i] > rightMax) {
            rightMax = height[i];
        } else {
            water += rightMax - height[i];
        }
    }
    
    return water;
}

}
}