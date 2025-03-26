#include <vector>
class Solution
{
private:
    void backpack(std::vector<int>& nums, int index, int sum, int target, int& cnt)
    {
        if (index == nums.size())
        {
            if (sum == target)
            {
                cnt++;
            }
            return;
        }

        backpack(nums, index + 1, sum + nums[index], target, cnt);
        backpack(nums, index + 1, sum - nums[index], target, cnt);
    }
public:
    int findTargetSumWays(std::vector<int>& nums, int target)
    {
        int cnt = 0;
        backpack(nums, 0, 0, target, cnt);
        return cnt;

    }
};
//
//int main()
//{
//    std::vector<int> nums = { 1,1,1,1,1 };
//    Solution solution;
//    solution.findTargetSumWays(nums, 3);
//}