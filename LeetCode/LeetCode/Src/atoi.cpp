#include "string"
#include "iostream"
#include "cstdio"
class Solution 
{
public:
    static int myAtoi(std::string s)
    {
        int index = 0;
        // 空格全清
        while (s[index] == " ") // 注意这里不能使用" "，而是应该使用' '
            index++;

        int flag = 1;
        if (s[index] == '-' || s[index] == '+')
        {
            // 负数
            flag = s[index] == '-'? -1 : 1;
            index++;
        }

        // 去除前导零
        while (s[index] == '0' && index < s.size())
            index++;


        if (!(s[index] >= '0' && s[index] <= '9') || index == s.size()) return 0;

        int sum = 0;
        for (; index < s.size(); index++)
        {
            if (!(s[index] >= '0' && s[index] <= '9'))
            {
                break;
            }
            if (sum < INT_MIN / 10 || (sum == INT_MIN / 10 && s[index] - '0' > 8))
            {
                sum = INT_MIN;
                break;
            }
            if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && s[index] - '0' > 7))
            {
                sum = INT_MAX;
                break;
            }
            sum = sum * 10 + flag * (s[index] - '0');
        }
        return sum;
    }
};
int main()
{
    std::string s = "0-1";
    std::cout << Solution::myAtoi(s) << std::endl;
}