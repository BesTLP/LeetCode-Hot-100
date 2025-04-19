#include <vector>
class Solution {
public:
    int climbStairs(int n)
    {
        std::vector<int> dp(n + 1, 0);
        
        dp[0] = 1;
        dp[1] = 1; // 到达一阶只有一种办法
        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};