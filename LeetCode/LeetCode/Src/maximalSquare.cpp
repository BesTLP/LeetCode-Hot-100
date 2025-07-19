#include <vector>
class Solution
{
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix)
    {
        std::vector<std::vector<int>> dp(matrix.size(), std::vector<int>(matrix[0].size(), 0));
        int maxLength = 0;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                if (matrix[i][j] == '0')
                {
                    dp[i][j] = 0;
                }
                else
                {
                    if (i - 1 >= 0 && j - 1 >= 0)
                        dp[i][j] = std::min(dp[i][j - 1], std::min(dp[i - 1][j], dp[i - 1][j - 1])) + 1;
                    else dp[i][j] = 1;

                    maxLength = std::max(maxLength, dp[i][j]);
                }
            }
        }
        return maxLength * maxLength;
    }
};