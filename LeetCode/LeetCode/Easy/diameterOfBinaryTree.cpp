#include <vector>
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
    int ret = 0;
    int getMaxHeight(TreeNode* root)
    {
        if (root == nullptr) return 0;

        int leftHeight = getMaxHeight(root->left);
        int rightHeight = getMaxHeight(root->right);

        ret = std::max(ret, leftHeight + rightHeight);
        return std::max(leftHeight, rightHeight)+ 1;
    }
    int diameterOfBinaryTree(TreeNode* root) 
    {
        getMaxHeight(root);
        return ret;
    }
};