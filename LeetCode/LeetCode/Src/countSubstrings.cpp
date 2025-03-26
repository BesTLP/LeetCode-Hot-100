#include <string>
class Solution 
{
public:
    int countSubstrings(std::string s) 
    {
        int ret = 0;
        for (int i = 0; i < s.size(); i++)
        {
            // 以 s[i] 为中心
            for (int j = 0; j <= 1; j++)
            {
                int left = i;
                int right = i + j;
                while (left >= 0 && right < s.size() && s[left--] == s[right++])
                {
                    ret++;
                }
            }
        }

        return ret;
    }
};
//
//int main()
//{
//    std::string s = "aaa";
//    Solution solution;
//    solution.countSubstrings(s);
//}