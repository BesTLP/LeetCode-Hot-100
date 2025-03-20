#include <vector>

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
public:
    
    bool Search(TreeNode* root, int& minValue, int& maxValue)
    {
        if (!root)
        {
            minValue = root->val;
            maxValue = root->val;
            return true;
        }


        minValue = root->val;
        maxValue = root->val;
        if (root->left)
        {
            int minLeftValue, maxLeftValue;
            if (!Search(root->left, minLeftValue, maxLeftValue))
            {
                return false;
            }

            if (root->val <= maxLeftValue)
            {
                // ²»Âú×ã
                return false;
            }
            else
            {
                minValue = minLeftValue;
            }
        }

        if (root->right)
        {
            int minRightValue, maxRightValue;
            if (!Search(root->right, minRightValue, maxRightValue))
            {
                return false;
            }
            if (root->val >= minRightValue)
            {
                // ²»Âú×ã
                return false;
            }
            else
            {
                maxValue = maxRightValue;
            }
        }
        return true;
    }
    bool isValidBST(TreeNode* root)
    {
        int min, max;
        if (Search(root, min, max))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
//int main()
//{
//    TreeNode* root = new TreeNode(34);
//    root->left = new TreeNode(-6);
//    root->left->left = new TreeNode(-21);
//
//    Solution solution;
//    solution.isValidBST(root);
//}