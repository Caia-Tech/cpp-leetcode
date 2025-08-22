#include "data_structures.h"
#include <queue>

namespace leetcode {
namespace utils {

std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

ListNode* vectorToList(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    
    ListNode* head = new ListNode(vals[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < vals.size(); ++i) {
        current->next = new ListNode(vals[i]);
        current = current->next;
    }
    
    return head;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

TreeNode* buildTree(const std::vector<std::optional<int>>& vals) {
    if (vals.empty() || !vals[0].has_value()) return nullptr;
    
    TreeNode* root = new TreeNode(vals[0].value());
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    size_t i = 1;
    while (!queue.empty() && i < vals.size()) {
        TreeNode* current = queue.front();
        queue.pop();
        
        if (i < vals.size() && vals[i].has_value()) {
            current->left = new TreeNode(vals[i].value());
            queue.push(current->left);
        }
        i++;
        
        if (i < vals.size() && vals[i].has_value()) {
            current->right = new TreeNode(vals[i].value());
            queue.push(current->right);
        }
        i++;
    }
    
    return root;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

std::vector<std::optional<int>> treeToVector(TreeNode* root) {
    std::vector<std::optional<int>> result;
    if (!root) return result;
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    while (!queue.empty()) {
        TreeNode* current = queue.front();
        queue.pop();
        
        if (current) {
            result.push_back(current->val);
            queue.push(current->left);
            queue.push(current->right);
        } else {
            result.push_back(std::nullopt);
        }
    }
    
    while (!result.empty() && !result.back().has_value()) {
        result.pop_back();
    }
    
    return result;
}

}
}