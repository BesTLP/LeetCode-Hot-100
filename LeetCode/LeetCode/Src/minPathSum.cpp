#include <iostream>
#include <vector>
#include <queue>

///********************************
//*************  DFS  *************
//*********************************/
//
//class Solution 
//{
//public:
//    int minPathSum(std::vector<std::vector<int>>& grid)
//    {
//        minSum = INT_MAX;
//        DFS(grid, 0, 0, grid[0][0]);
//        return minSum;
//    }
//private:
//    void DFS(std::vector<std::vector<int>>& grid, int x, int y, int sum)
//    {
//        int m = grid.size();
//        int n = grid[0].size();
//        if (x == m - 1 && y == n - 1)
//        {
//            minSum = std::min(sum, minSum);
//            return;
//        }
//        int moveX[2] = { 1,0 };
//        int moveY[2] = { 0,1 };
//        for (int i = 0; i < 2; i++)
//        {
//            int nextX = x + moveX[i];
//            int nextY = y + moveY[i];
//            if (nextX >= 0 && nextX < m &&
//                nextY >= 0 && nextY < n )
//            {
//                DFS(grid, nextX, nextY, sum + grid[nextX][nextY]);
//            }
//        }
//    }
//    int minSum;
//};
//
//
///********************************
//*************  BFS  *************
//*********************************/
//
//class Solution
//{
//public:
//    struct Location
//    {
//        Location(int _x, int _y, int _sum)
//            : x(_x), y(_y), sum(_sum) {}
//
//        int x;
//        int y;
//        int sum;
//    };
//    int minPathSum(std::vector<std::vector<int>>& grid)
//    {
//        std::queue<Location> aQueue;
//        aQueue.emplace(Location(0, 0, grid[0][0]));
//        int minSum = INT_MAX;
//        while (!aQueue.empty())
//        {
//            Location front = aQueue.front();
//            int x = front.x;
//            int y = front.y;
//            int sum = front.sum;
//            aQueue.pop();
//            if (x == grid.size() - 1 && y == grid[0].size() - 1)
//            {
//                minSum = std::min(minSum, sum);
//            }
//            if (x + 1 < grid.size())
//            {
//                aQueue.emplace(Location(x + 1, y, sum + grid[x + 1][y]));
//            }
//            if (y + 1 < grid[0].size())
//            {
//                aQueue.emplace(Location(x, y + 1, sum + grid[x][y + 1]));
//            }
//        }
//        return minSum;
//    }
//
//};
//
///********************************
//*************  DP  *************
//*********************************/
//
//class Solution
//{
//public:
//
//    int minPathSum(std::vector<std::vector<int>>& grid)
//    {
//        int m = grid.size();
//        int n = grid[0].size();
//        std::vector<std::vector<int>> dp(grid.size(), std::vector<int>(grid[0].size(), 0));
//
//        dp[0][0] = grid[0][0];
//        for (int i = 1; i < m; i++)
//        {
//            dp[i][0] = dp[i - 1][0] + grid[i][0];
//        }
//        for (int i = 1; i < n; i++)
//        {
//            dp[0][i] = dp[0][i - 1] + grid[0][i];
//        }
//
//        for (int i = 1; i < m; i++)
//        {
//            for (int j = 1; j < n; j++)
//            {
//                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
//            }
//        }
//        return dp[m -1][n - 1];
//    }
//};
/********************************
**********  Dijkstra  ***********
*********************************/
class Solution
{
public:
    struct Location
    {
        Location(int _x, int _y, int _sum)
            : x(_x), y(_y), sum(_sum) {}
        int x, y, sum;
    };
    struct CompareLocation
    {
        bool operator()(const Location& L1, const Location& L2)
        {
            return L1.sum > L2.sum; // 最小堆
        }
    };
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        if (m == 0 || n == 0) return 0;

        //int moveX[4] = { 1,-1,0,0 };
        //int moveY[4] = { 0,0,1,-1 };
        int moveX[2] = { 1,0 }; // 本题只要求了向右向下走
        int moveY[2] = { 0,1};
        std::priority_queue<Location, std::vector<Location>, CompareLocation> priQueue;
        std::vector<std::vector<int>> dist(m, std::vector<int>(n, INT_MAX));

        priQueue.push(Location(0, 0, grid[0][0]));
        dist[0][0] = grid[0][0];

        while (!priQueue.empty())
        {
            Location top = priQueue.top();
            priQueue.pop();
            if (top.x == m - 1 && top.y == n - 1)
            {
                return top.sum;
            }

            for (int i = 0; i < 2; i++)
            {
                int nextX = top.x + moveX[i];
                int nextY = top.y + moveY[i];
                if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n)
                {
                    int newSum = top.sum + grid[nextX][nextY];
                    if (newSum < dist[nextX][nextY])
                    {
                        dist[nextX][nextY] = newSum;
                        priQueue.push(Location(nextX, nextY, newSum));
                    }
                }

            }
        }
        return -1;
    }
};


//int main()
//{
//    std::vector<std::vector<int>> grid =
//    {
//        {1, 3, 1},
//        {1, 5, 1},
//        {4, 2, 1}
//    };
//    Solution solution;
//    std::cout << solution.minPathSum(grid);
//}