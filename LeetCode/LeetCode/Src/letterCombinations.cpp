#include "iostream"
#include "vector"
#include "string"

class Solution
{
public:
    static const std::vector<std::vector<char>> NumberChar;
    void DFS(std::vector<std::string>& result, std::string& TempResult, std::vector<int>& index, int cnt)
    {
        if (cnt == index.size())
        {
            result.push_back(TempResult);
            return;
        }
        int i = index[cnt];
        for (int j = 0; j < NumberChar[i].size(); j++)
        {
            TempResult.push_back(NumberChar[i][j]);
            DFS(result, TempResult, index, cnt + 1);
            TempResult.pop_back();
        }
    }
    std::vector<std::string> letterCombinations(std::string digits)
    {
        if (digits.empty()) return std::vector<std::string>();

        std::vector<int> index;
        for (auto c : digits)
        {
            index.push_back(c - '0');
        }
        std::vector<std::string> result;
        std::string TempResult;

        DFS(result, TempResult, index, 0);
        return result;
    }
};
const std::vector<std::vector<char>> Solution::NumberChar =
{
    {},
    {},
    {'a','b','c'},
    {'d','e','f'},
    {'g','h','i'},
    {'j','k','l'},
    {'m','n','o'},
    {'p','q','r','s'},
    {'t','u', 'v'},
    {'w','x','y','z'}
};