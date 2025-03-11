#include <vector>
#include <iostream>

//class Solution
//{
//public:
//    void DFS(int m, int n, int x, int y)
//    {
//        if (x == m - 1 && y == n - 1)
//        {
//            cnt++;
//        }
//        for (int i = 0; i < 2; i++)
//        {
//            int nx = x + moveX[i];
//            int ny = y + moveY[i];
//            if (nx < m && ny < n)
//                DFS(m, n, nx, ny);
//        }
//
//    }
//    int uniquePaths(int m, int n)
//    {
//        DFS(m, n, 0, 0);
//        return cnt;
//    }
//    int cnt = 0;
//    int moveX[2] = { 1, 0 };
//    int moveY[2] = { 0, 1 };
//};

class Solution
{
public:
	int uniquePaths(int m, int n)
	{
		std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
		dp[0][0] = 1;
		for (int i = 1; i < m; i++)
		{
			dp[i][0] = dp[i - 1][0];
		}
		for (int i = 1; i < n; i++)
		{
			dp[0][i] = dp[0][i - 1];
		}

		for (int i = 1; i < m; i++)
		{
			for (int j = 1; j < n; j++)
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};
//
//int main()
//{
//	Solution solution;
//	std::cout << solution.uniquePaths(3, 7);
//}