#include <queue>
// Definition for a binary tree node.
struct TreeNode  
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
private:
    long long Search(TreeNode* root, long long targetSum)
    {
        if (root == nullptr)
        {
            return 0;
        }

        long long result = 0;
        if (root->val == targetSum) result++;

        result += Search(root->left, targetSum - root->val);
        result += Search(root->right, targetSum - root->val);

        return result;
    }
public:
    long long pathSum(TreeNode* root, long long targetSum)
    {
        if (!root) return 0;

        long long result = Search(root, targetSum); // µ±Ç°

        result += pathSum(root->left, targetSum);
        result += pathSum(root->right, targetSum);

        return result;
    }
};
//
//int main()
//{
//    TreeNode* root = new TreeNode(10);
//    root->left = new TreeNode(5);
//    root->right = new TreeNode(-3);
//    root->right->right = new TreeNode(11);
//    root->left->left = new TreeNode(3);
//    root->left->right = new TreeNode(2);
//    root->left->left->left = new TreeNode(3);
//    root->left->left->right = new TreeNode(-2);
//    root->left->right->right = new TreeNode(1);
//    Solution solution;
//    solution.pathSum(root, 8);
//}