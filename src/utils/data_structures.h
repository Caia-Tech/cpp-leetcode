#pragma once

#include <vector>
#include <optional>
#include <queue>

namespace leetcode {
namespace utils {

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

std::vector<int> listToVector(ListNode* head);
ListNode* vectorToList(const std::vector<int>& vals);
void deleteList(ListNode* head);

TreeNode* buildTree(const std::vector<std::optional<int>>& vals);
void deleteTree(TreeNode* root);
std::vector<std::optional<int>> treeToVector(TreeNode* root);

}
}