#include <vector>
#include <iostream>
#include <queue>
class Solution
{
public:
    void BFS(int x, int y, std::vector<std::vector<char>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int mX[4] = { 1,-1,0,0 };
        int mY[4] = { 0,0,1,-1 };

        std::queue<std::pair<int, int>> q;
        q.push(std::make_pair(x, y));
        grid[x][y] = '0';
        while (!q.empty())
        {
            auto front = q.front();
            q.pop();
            int x = front.first;
            int y = front.second;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + mX[i];
                int ny = y + mY[i];
                if (nx >= 0 && nx < m &&
                    ny >= 0 && ny < n)
                {
                    if (grid[nx][ny] - '0')
                    {
                        grid[nx][ny] = '0';
                        q.push(std::make_pair(nx, ny));
                    }
                }
            }
        }
    }

    void DFS(int x, int y, std::vector<std::vector<char>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int mX[4] = { 1,-1,0,0 };
        int mY[4] = { 0,0,1,-1 };
        if (x >= 0 && x < m && y >= 0 && y < n)
        {
            if (grid[x][y] - '0')
            {
                grid[x][y] = '0';
                for (int i = 0; i < 4; i++)
                {
                    int nx = x + mX[i];
                    int ny = y + mY[i];
                    {
                        DFS(nx, ny, grid);
                    }
                }
            }
        }
    }
    int numIslands(std::vector<std::vector<char>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int cnt = 0;
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] - '0')
                {
                    //BFS(i, j, grid);
                    DFS(i, j, grid);
                    cnt++;
                }
                    
            }
        }
        return cnt;
    }
};

//int main()
//{
//    Solution solution;
//    std::vector<std::vector<char>> grid =
//    {
//          {'1','1','0','0','0'},
//          {'1','1','0','0','0'},
//          {'0','0','1','0','0'},
//          {'0','0','0','1','1'}
//    };
//    std::cout << solution.numIslands(grid);
//}