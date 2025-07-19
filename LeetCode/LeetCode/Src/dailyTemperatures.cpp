#include <vector>
#include <stack>

class Solution
{
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures)
    {
        std::stack<std::pair<int, int>> tempStack;
        std::vector<int> ret(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); i++)
        {
            if (tempStack.empty())
            {
                tempStack.push(std::make_pair(i, temperatures[i]));
                continue;
            }

            while (!tempStack.empty() && temperatures[i] > tempStack.top().second)
            {
                std::pair<int, int> top = tempStack.top();
                tempStack.pop();
                int index = top.first;
                ret[index] = i - index;
            }
            tempStack.push(std::make_pair(i, temperatures[i]));
        }
        return ret;
    }
};
