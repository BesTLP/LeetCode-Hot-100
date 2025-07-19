#include <vector>
class Solution
{
public:
    int rob(std::vector<int>& nums)
    {
        if (nums.size() == 0)return 0;
        if (nums.size() == 1) return nums[0];
        std::vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);
        int maxV = std::max(dp[0], dp[1]);
        for (int i = 2; i < nums.size(); i++)
        {
            dp[i] = std::max(nums[i] + dp[i - 2], dp[i - 1]);
            maxV = std::max(maxV, dp[i]);
        }
        return maxV;
    }
};