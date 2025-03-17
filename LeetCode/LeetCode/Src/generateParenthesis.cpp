#include <vector>
#include <string>
#include <iostream>

class Solution 
{
public:
    void DFS(std::string s, int left, int right, int n)
    {
        if (left == n && right == n)
        {
            result.push_back(s);
            return;
        }
        if (left < n)
        {
            DFS(s + "(", left + 1, right, n);
        }
        if (right < left)
        {
            DFS(s + ")", left, right + 1, n);
        }
    }
    std::vector<std::string> generateParenthesis(int n) 
    {
        std::string s;
        DFS(s, 0, 0, n);
        return result;
    }
public:
    std::vector<std::string> result;
};
//
//int main()
//{
//    Solution solution;
//    solution.generateParenthesis(3);
//    for (std::string s : solution.result)
//    {
//        std::cout << s << std::endl;
//    }
//}