#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
class Solution
{
public:
    void DFS(std::vector<int>& candidates, std::vector<int> currentResult, int sum, int index, int target)
    {
        if (sum == target)
        {
            Result.push_back(currentResult);
            return;
        }
        else if (sum > target)
        {
            return;
        }

        for (int i = index; i < candidates.size(); i++)
        {
            currentResult.push_back(candidates[i]);
            DFS(candidates, currentResult, sum + candidates[i], i, target);
            currentResult.pop_back();
        }
    }
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
        std::vector<int> currentResult;
        DFS(candidates, currentResult, 0, 0, target);
        return Result;
    }
    std::vector<std::vector<int>> Result;

};
//
//int main()
//{
//    Solution solution;
//    std::vector<int> candidates = { 2, 3, 6, 7 };
//    solution.combinationSum(candidates, 7);
//}