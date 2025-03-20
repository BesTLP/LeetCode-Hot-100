#include <vector>
#include <algorithm>
#include <queue>

//Definition for a binary tree node.
 struct TreeNode 
 {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

//class Solution
//{
//public:
//    std::vector<std::vector<int>> levelOrder(TreeNode* root)
//    {
//        if (root == nullptr)
//        {
//            return {};
//        }
//        std::queue<std::pair<TreeNode*, int>> queue;
//        std::vector<std::vector<int>> Result;
//        std::vector<int> currentResult;
//
//        queue.push({ root, 0 });
//        int currentLevel = 0;
//        while (!queue.empty())
//        {
//            std::pair<TreeNode*, int> front = queue.front();
//            queue.pop();
//
//            int val = front.first->val;
//            int level = front.second;
//            if (level != currentLevel)
//            {
//                Result.push_back(currentResult);
//                currentResult.clear();
//                currentLevel = level;
//            }
//
//            currentResult.push_back(val);
//
//            TreeNode* left = front.first->left;
//            TreeNode* right = front.first->right;
//            if (left != nullptr)
//            {
//                queue.push({ left, level + 1 });
//            }
//            if (right != nullptr)
//            {
//                queue.push({ right, level + 1 });
//            }
//        }
//        Result.push_back(currentResult);
//        return Result;
//    }
//};

class Solution
{
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root)
    {
        if (root == nullptr)
        {
            return {};
        }
        std::queue<TreeNode*> queue;
        std::vector<std::vector<int>> Result;

        queue.push(root);
        int currentLevel = 0;
        while (!queue.empty())
        {
            int size = queue.size(); // 获取当前层的节点数
            std::vector<int> currentResult;
            for (int i = 0; i < size; i++)
            {
                TreeNode* front = queue.front();
                queue.pop();

                int val = front->val;
                currentResult.push_back(val);
                TreeNode* left = front->left;
                TreeNode* right = front->right;
                if (left != nullptr)
                {
                    queue.push(left);
                }
                if (right != nullptr)
                {
                    queue.push(right);
                }
            }
            Result.push_back(std::move(currentResult));
        }
        return Result;
    }
};