#include "vector"
class Solution 
{
private:
    void DFS(std::vector<std::vector<int>>& Result, std::vector<int>& TempResult, std::vector<int>& nums, int index)
    {
        if (index == nums.size())
        {
            Result.push_back(TempResult);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!flag[i])
            {
                flag[i] = true;
                TempResult.push_back(nums[i]);
                DFS(Result, TempResult, nums, index + 1);
                TempResult.pop_back();
                flag[i] = false;
            }
        }
    }
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) 
    {
        std::vector<std::vector<int>> Result;
        std::vector<int> TempResult;
        DFS(Result, TempResult, nums, 0);

        return Result;
    }
    bool flag[10] = { false };
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 2, 3};
    solution.permute(nums);
}