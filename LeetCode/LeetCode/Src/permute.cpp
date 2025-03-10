#include <vector>

class Solution
{
private:
    void DFS(std::vector<std::vector<int>>& Results, std::vector<int>& TempResult, std::vector<int>& nums, int cnt)
    {
        if (cnt == nums.size())
        {
            Results.push_back(TempResult);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!flag[i])
            {
                flag[i] = true;
                TempResult.push_back(nums[i]);
                DFS(Results, TempResult, nums, cnt + 1);
                TempResult.pop_back();
                flag[i] = false;
            }
        }
    }

public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> Results;
        std::vector<int> TempResult;
        DFS(Results, TempResult, nums, 0);

        return Results;
    }

    bool flag[10] = { false };
};