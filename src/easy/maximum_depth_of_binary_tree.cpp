#include "easy/maximum_depth_of_binary_tree.h"

namespace leetcode {
namespace easy {

int MaxDepthRecursive::maxDepth(utils::TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

int MaxDepthTopDown::maxDepth(utils::TreeNode* root) {
    int best = 0;
    dfs(root, 1, best);
    return best;
}

void MaxDepthTopDown::dfs(utils::TreeNode* node, int depth, int& best) {
    if (!node) return;
    best = std::max(best, depth);
    dfs(node->left, depth + 1, best);
    dfs(node->right, depth + 1, best);
}

int MaxDepthIterativeDFS::maxDepth(utils::TreeNode* root) {
    if (!root) return 0;
    std::stack<std::pair<utils::TreeNode*, int>> st;
    st.push({root, 1});
    int best = 0;
    while (!st.empty()) {
        auto [node, depth] = st.top();
        st.pop();
        if (!node) continue;
        best = std::max(best, depth);
        st.push({node->left, depth + 1});
        st.push({node->right, depth + 1});
    }
    return best;
}

int MaxDepthBFSQueue::maxDepth(utils::TreeNode* root) {
    if (!root) return 0;
    std::queue<std::pair<utils::TreeNode*, int>> q;
    q.push({root, 1});
    int best = 0;
    while (!q.empty()) {
        auto [node, depth] = q.front();
        q.pop();
        best = std::max(best, depth);
        if (node->left) q.push({node->left, depth + 1});
        if (node->right) q.push({node->right, depth + 1});
    }
    return best;
}

int MaxDepthBFSSentinel::maxDepth(utils::TreeNode* root) {
    if (!root) return 0;
    std::queue<utils::TreeNode*> q;
    q.push(root);
    q.push(nullptr);
    int depth = 0;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        if (!node) {
            depth++;
            if (!q.empty()) q.push(nullptr);
        } else {
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return depth;
}

int MaxDepthLevelCount::maxDepth(utils::TreeNode* root) {
    if (!root) return 0;
    std::queue<utils::TreeNode*> q;
    q.push(root);
    int depth = 0;
    while (!q.empty()) {
        int levelSize = q.size();
        depth++;
        for (int i = 0; i < levelSize; ++i) {
            auto node = q.front();
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return depth;
}

}  // namespace easy
}  // namespace leetcode

