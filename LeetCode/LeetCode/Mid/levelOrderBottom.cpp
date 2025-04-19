#include <vector>
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
public:
    std::vector<std::vector<int>> levelOrderBottom(TreeNode* root) 
    {

        std::queue<TreeNode*> q;
        q.push(root);
        std::vector<std::vector<int>> ret;
        while (!q.empty())
        {
            int size = q.size();

            std::vector<int> vec;
            for (int i = 0; i < size; i++)
            {
                TreeNode* front = q.front();
                q.pop();
                vec.push_back(front->val);
                if (front->left) q.push(front->left);
                if (front->right)q.push(front->right);
            }
            ret.push_back(vec);
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};