#include "iostream"
#include "cstdio"
#include "cmath"
#include <vector>
class Solution
{
public:
    //int numSquares(int n)
    //{
    //    // ̰�ĵķ�ʽ���󣬵ò�����ȷ�Ĵ�
    //    // 12 = 9 + 1 + 1 + 1 (4)
    //    std::vector<int> SquareNumber;
    //    for (int i = 1; i <= std::sqrt(n); i++)
    //    {
    //        SquareNumber.push_back(std::pow(i, 2));
    //    }

    //    int index = SquareNumber.size() - 1;
    //    int cnt = 0;
    //    while (n != 0)
    //    {
    //        if (n - SquareNumber[index] >= 0)
    //        {
    //            n -= SquareNumber[index];
    //            cnt++;
    //        }
    //        else
    //        {
    //            index--;
    //        }
    //    }

    //    return cnt;
    //}
    int numSquares(int n)
    {
        // ��̬�滮�ķ�ʽ���󣬵���ȷ�Ĵ�
        // 12 = 4 + 4 + 4 (3)
        std::vector<int> dp(n + 1, INT_MAX);

        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j * j <= i; j++)
            {
                dp[i] = std::min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};
