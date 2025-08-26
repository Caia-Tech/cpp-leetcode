#include "binary_tree_postorder_traversal.h"
#include <stack>
#include <algorithm>

namespace leetcode {
namespace easy {

// Approach 1: Recursive DFS (Classic)
// Detailed Reasoning: This follows the natural definition of postorder traversal.
// We recursively traverse left subtree, then right subtree, then visit the root.
// The recursion naturally handles the call stack and maintains the correct order.
std::vector<int> BinaryTreePostorderTraversal::postorderTraversalRecursive(utils::TreeNode* root) {
    std::vector<int> result;
    postorderHelper(root, result);
    return result;
}

// Approach 2: Iterative Two Stacks
// Detailed Reasoning: First stack is used for traversal (similar to preorder but with
// left/right reversed), second stack stores nodes in reverse postorder. This naturally
// gives us the postorder sequence when we pop from the second stack.
std::vector<int> BinaryTreePostorderTraversal::postorderTraversalTwoStacks(utils::TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    
    std::stack<utils::TreeNode*> stack1, stack2;
    stack1.push(root);
    
    // First stack: traverse in modified preorder (root-right-left)
    while (!stack1.empty()) {
        utils::TreeNode* node = stack1.top();
        stack1.pop();
        stack2.push(node);
        
        // Push left first, then right (opposite of preorder)
        if (node->left) stack1.push(node->left);
        if (node->right) stack1.push(node->right);
    }
    
    // Second stack contains nodes in reverse postorder
    while (!stack2.empty()) {
        result.push_back(stack2.top()->val);
        stack2.pop();
    }
    
    return result;
}

// Approach 3: Iterative Single Stack with Visited Tracking
// Detailed Reasoning: Use a single stack but track the last visited node to determine
// when we've processed both children of a node. This avoids the need for a second stack
// while still maintaining the correct postorder sequence.
std::vector<int> BinaryTreePostorderTraversal::postorderTraversalSingleStack(utils::TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    
    std::stack<utils::TreeNode*> stk;
    utils::TreeNode* lastVisited = nullptr;
    utils::TreeNode* current = root;
    
    while (current || !stk.empty()) {
        if (current) {
            // Go to the leftmost node
            stk.push(current);
            current = current->left;
        } else {
            utils::TreeNode* peekNode = stk.top();
            
            // If right child exists and hasn't been processed yet
            if (peekNode->right && lastVisited != peekNode->right) {
                current = peekNode->right;
            } else {
                // Both children processed, visit this node
                result.push_back(peekNode->val);
                lastVisited = stk.top();
                stk.pop();
            }
        }
    }
    
    return result;
}

// Approach 4: Morris Traversal (Threaded Binary Tree)
// Detailed Reasoning: Morris traversal for postorder is more complex than preorder/inorder.
// We need to create threads and carefully manage the traversal to ensure we visit nodes
// in the correct postorder sequence while maintaining O(1) space complexity.
std::vector<int> BinaryTreePostorderTraversal::postorderTraversalMorris(utils::TreeNode* root) {
    std::vector<int> result;
    utils::TreeNode dummy(0);
    dummy.left = root;
    utils::TreeNode* current = &dummy;
    
    while (current) {
        if (!current->left) {
            current = current->right;
        } else {
            utils::TreeNode* predecessor = current->left;
            
            // Find the rightmost node in left subtree
            while (predecessor->right && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            
            if (!predecessor->right) {
                // Create thread
                predecessor->right = current;
                current = current->left;
            } else {
                // Remove thread and process nodes
                predecessor->right = nullptr;
                reverseAddRange(result, current->left, predecessor);
                current = current->right;
            }
        }
    }
    
    return result;
}

// Approach 5: Reverse Preorder
// Detailed Reasoning: Postorder is the reverse of a modified preorder traversal.
// If we do preorder as Root->Right->Left and then reverse the result, we get
// Left->Right->Root which is postorder. This is an elegant solution.
std::vector<int> BinaryTreePostorderTraversal::postorderTraversalReversePreorder(utils::TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    
    std::stack<utils::TreeNode*> stk;
    stk.push(root);
    
    // Modified preorder: Root -> Right -> Left
    while (!stk.empty()) {
        utils::TreeNode* node = stk.top();
        stk.pop();
        result.push_back(node->val);
        
        // Push left first, then right (opposite of normal preorder)
        if (node->left) stk.push(node->left);
        if (node->right) stk.push(node->right);
    }
    
    // Reverse to get postorder
    std::reverse(result.begin(), result.end());
    return result;
}

// Approach 6: Iterative with State Tracking
// Detailed Reasoning: Explicitly track the state of each node (unvisited, left visited,
// right visited) to determine when to process it. This provides clear control flow
// and makes the algorithm easy to understand and debug.
std::vector<int> BinaryTreePostorderTraversal::postorderTraversalWithState(utils::TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    
    std::stack<NodeWithState> stk;
    stk.emplace(root, UNVISITED);
    
    while (!stk.empty()) {
        auto& [node, state] = stk.top();
        
        if (state == UNVISITED) {
            // First visit: push right child, then left child, then mark as left visited
            state = LEFT_VISITED;
            
            if (node->right) {
                stk.emplace(node->right, UNVISITED);
            }
            if (node->left) {
                stk.emplace(node->left, UNVISITED);
            }
        } else if (state == LEFT_VISITED) {
            // Left subtree processed, mark as right visited
            state = RIGHT_VISITED;
        } else {
            // Both subtrees processed, visit this node
            result.push_back(node->val);
            stk.pop();
        }
    }
    
    return result;
}

// Helper function for recursive approach
void BinaryTreePostorderTraversal::postorderHelper(utils::TreeNode* node, std::vector<int>& result) {
    if (!node) return;
    
    // Postorder: Left -> Right -> Root
    postorderHelper(node->left, result);   // Traverse left subtree
    postorderHelper(node->right, result);  // Traverse right subtree
    result.push_back(node->val);           // Visit root
}

// Helper function for Morris traversal
void BinaryTreePostorderTraversal::reverseAddRange(std::vector<int>& result, utils::TreeNode* from, utils::TreeNode* to) {
    std::vector<int> temp;
    utils::TreeNode* current = from;
    
    while (true) {
        temp.push_back(current->val);
        if (current == to) break;
        current = current->right;
    }
    
    // Add in reverse order
    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        result.push_back(*it);
    }
}

} // namespace easy
} // namespace leetcode