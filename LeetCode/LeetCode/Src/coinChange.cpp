#include <vector>
//class Solution
//{
//public:
//    int coinChange(std::vector<int>& coins, int amount)
//    {
//        std::vector<int> dp(amount + 1, INT_MAX);
//        dp[0] = 0;
//        for (int i = 1; i <= amount; i++)
//        {
//            for (int coin : coins)
//            {
//                if (coin <= i && dp[i - coin] != INT_MAX)
//                {
//                    dp[i] = std::min(dp[i], dp[i - coin] + 1);
//                }
//            }
//        }
//        return dp[amount] == INT_MAX ? -1 : dp[amount];
//    }
//};

class Solution
{
private:
    int Search(std::vector<int>& coins,int index,  int amount)
    {
        if (amount == 0) return 0;

        if (index == coins.size()) return -1;
        if (amount < 0) return -1;

        if (coins[index] == amount) return 1;

        int ret = 0;
        // ����ѡ��ǰindex��Ӳ��
        ret += Search(coins, index, amount - coins[index]);

        // ����ѡ��ǰ��Ӳ��
        if (index + 1 < coins.size())
        {
            ret += Search(coins, index + 1, amount);
        }
    }
public:
    int coinChange(std::vector<int>& coins, int amount)
    {
        Search(coins, 0, amount);
    }
};