#include <vector>
#include <queue>
class Solution
{
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) 
    {
        std::vector<std::vector<int>> adj(numCourses);
        std::vector<int> in(numCourses, 0);
        for (auto pre : prerequisites)
        {
            // 要想修习second必须先学first
            int first = pre[1];
            int second = pre[0]; 
            adj[first].push_back(second);
            in[second]++;
        }
        
        std::queue<int> q;
        for (int i = 0; i < numCourses; i++)
        {
            if (in[i] == 0)
            {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty())
        {
            int front = q.front();
            q.pop();
            visited++;
            for (int i = 0; i < adj[front].size(); i++)
            {
                int node = adj[front][i];
                in[node]--;
                if (in[node] == 0)
                {
                    q.push(node);
                }
            }
        }
        return visited == numCourses;
    }

};