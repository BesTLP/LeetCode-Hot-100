#include <vector>

class Solution 
{
public:
    void backtrack(std::vector<int> nums, int start, std::vector<int> path, std::vector<std::vector<int>>& Result)
    {
        Result.push_back(path);

        for (int i = start; start < nums.size() - 1; i++)
        {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, Result);
            path.pop_back();
        }

    }
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> Result;
        backtrack(nums, 0, {}, Result);
        return Result;
    }
};