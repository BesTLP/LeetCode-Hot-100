#include <queue>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution 
{
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (root == nullptr) return nullptr;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode* front = q.front();
            q.pop();
            std::swap(front->left, front->right);
            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
        return root;
    }
};