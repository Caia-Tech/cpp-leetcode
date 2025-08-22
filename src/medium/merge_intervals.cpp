#include "merge_intervals.h"
#include <stack>
#include <unordered_map>
#include <climits>

namespace leetcode {
namespace medium {

std::vector<std::vector<int>> MergeIntervals::mergeIntervals(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Sort intervals by start time
    std::sort(intervals.begin(), intervals.end());
    
    std::vector<std::vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); ++i) {
        // If current interval overlaps with last merged interval
        if (intervals[i][0] <= merged.back()[1]) {
            // Merge by extending end time
            merged.back()[1] = std::max(merged.back()[1], intervals[i][1]);
        } else {
            // No overlap, add current interval
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}

std::vector<std::vector<int>> MergeIntervals::mergeIntervalsByEndTime(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Sort intervals by end time
    std::sort(intervals.begin(), intervals.end(), 
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[1] < b[1];
              });
    
    std::vector<std::vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); ++i) {
        // Check if current interval overlaps with any in merged result
        bool overlapped = false;
        for (auto& mergedInterval : merged) {
            if (intervalsOverlap(intervals[i], mergedInterval)) {
                // Merge intervals
                mergedInterval = mergeTwo(intervals[i], mergedInterval);
                overlapped = true;
                break;
            }
        }
        
        if (!overlapped) {
            merged.push_back(intervals[i]);
        }
    }
    
    // Since we sorted by end time, might need another pass to merge
    // intervals that became overlapping after previous merges
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < merged.size() && !changed; ++i) {
            for (int j = i + 1; j < merged.size(); ++j) {
                if (intervalsOverlap(merged[i], merged[j])) {
                    merged[i] = mergeTwo(merged[i], merged[j]);
                    merged.erase(merged.begin() + j);
                    changed = true;
                    break;
                }
            }
        }
    }
    
    return merged;
}

std::vector<std::vector<int>> MergeIntervals::mergeIntervalsStack(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Sort intervals by start time
    std::sort(intervals.begin(), intervals.end());
    
    std::stack<std::vector<int>> stack;
    stack.push(intervals[0]);
    
    for (int i = 1; i < intervals.size(); ++i) {
        std::vector<int> current = intervals[i];
        
        // Check if current interval overlaps with stack top
        if (current[0] <= stack.top()[1]) {
            // Merge intervals
            std::vector<int> merged = stack.top();
            stack.pop();
            merged[1] = std::max(merged[1], current[1]);
            stack.push(merged);
        } else {
            // No overlap, push current interval
            stack.push(current);
        }
    }
    
    // Convert stack to result vector
    std::vector<std::vector<int>> result;
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }
    
    // Reverse to maintain chronological order
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<std::vector<int>> MergeIntervals::mergeIntervalsSweepLine(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Create events
    std::vector<Event> events;
    for (const auto& interval : intervals) {
        events.push_back(Event(interval[0], 1));      // Start event
        events.push_back(Event(interval[1] + 1, -1)); // End event (exclusive)
    }
    
    // Sort events
    std::sort(events.begin(), events.end());
    
    std::vector<std::vector<int>> result;
    int activeIntervals = 0;
    int intervalStart = -1;
    
    for (const Event& event : events) {
        if (activeIntervals == 0 && event.type == 1) {
            // Starting new merged interval
            intervalStart = event.coordinate;
        }
        
        activeIntervals += event.type;
        
        if (activeIntervals == 0 && event.type == -1) {
            // Ending current merged interval
            result.push_back({intervalStart, event.coordinate - 1});
        }
    }
    
    return result;
}

std::vector<std::vector<int>> MergeIntervals::mergeIntervalsUnionFind(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    int n = intervals.size();
    UnionFind uf(n);
    
    // Find all overlapping pairs and union them
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (intervalsOverlap(intervals[i], intervals[j])) {
                uf.unite(i, j);
            }
        }
    }
    
    // Group intervals by their root parent
    std::unordered_map<int, std::vector<int>> groups;
    for (int i = 0; i < n; ++i) {
        groups[uf.find(i)].push_back(i);
    }
    
    // Merge intervals in each group
    std::vector<std::vector<int>> result;
    for (const auto& group : groups) {
        int minStart = INT_MAX, maxEnd = INT_MIN;
        for (int idx : group.second) {
            minStart = std::min(minStart, intervals[idx][0]);
            maxEnd = std::max(maxEnd, intervals[idx][1]);
        }
        result.push_back({minStart, maxEnd});
    }
    
    return result;
}

std::vector<std::vector<int>> MergeIntervals::mergeIntervalsIntervalTree(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // This is a simplified version - full interval tree implementation would be more complex
    // For demonstration, we'll use a basic approach that shows the concept
    
    std::vector<std::vector<int>> result;
    std::vector<bool> merged(intervals.size(), false);
    
    for (int i = 0; i < intervals.size(); ++i) {
        if (merged[i]) continue;
        
        std::vector<int> current = intervals[i];
        merged[i] = true;
        
        // Find all intervals that overlap with current
        bool changed = true;
        while (changed) {
            changed = false;
            for (int j = 0; j < intervals.size(); ++j) {
                if (!merged[j] && intervalsOverlap(current, intervals[j])) {
                    current = mergeTwo(current, intervals[j]);
                    merged[j] = true;
                    changed = true;
                }
            }
        }
        
        result.push_back(current);
    }
    
    return result;
}

// Helper function implementations
bool MergeIntervals::intervalsOverlap(const std::vector<int>& a, const std::vector<int>& b) {
    return a[0] <= b[1] && b[0] <= a[1];
}

std::vector<int> MergeIntervals::mergeTwo(const std::vector<int>& a, const std::vector<int>& b) {
    return {std::min(a[0], b[0]), std::max(a[1], b[1])};
}

// Interval Tree operations (simplified implementation)
MergeIntervals::IntervalTreeNode* MergeIntervals::insertInterval(IntervalTreeNode* root, int start, int end) {
    if (root == nullptr) {
        return new IntervalTreeNode(start, end);
    }
    
    // Simple BST insertion by start time
    if (start < root->start) {
        root->left = insertInterval(root->left, start, end);
    } else {
        root->right = insertInterval(root->right, start, end);
    }
    
    updateMaxEnd(root);
    return root;
}

void MergeIntervals::findOverlapping(IntervalTreeNode* root, int start, int end, std::vector<std::vector<int>>& result) {
    if (root == nullptr) return;
    
    // Check if current interval overlaps
    if (start <= root->end && root->start <= end) {
        result.push_back({root->start, root->end});
    }
    
    // Search left subtree if it might contain overlapping intervals
    if (root->left && root->left->maxEnd >= start) {
        findOverlapping(root->left, start, end, result);
    }
    
    // Search right subtree
    if (root->right) {
        findOverlapping(root->right, start, end, result);
    }
}

void MergeIntervals::deleteTree(IntervalTreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void MergeIntervals::updateMaxEnd(IntervalTreeNode* node) {
    if (node == nullptr) return;
    
    node->maxEnd = node->end;
    if (node->left) {
        node->maxEnd = std::max(node->maxEnd, node->left->maxEnd);
    }
    if (node->right) {
        node->maxEnd = std::max(node->maxEnd, node->right->maxEnd);
    }
}

}
}