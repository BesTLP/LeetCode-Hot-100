#include "vector"
#include "iostream"
class Solution 
{
public:
    static int reverse(int x)
    {
        if (x == 0)
        {
            return 0;
        }

        // 去除前导零
        while (x % 10 == 0)
            x /= 10;

        int sum = 0;
        while (x != 0)
        {
            // [-2147483648, 2147483647] // 不能超过这个范围
            if (sum < INT_MIN / 10 || (sum == INT_MIN / 10 && x % 10 > 8))
            {
                return 0;
            }
            if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && x % 10 > 7))
            {
                return 0;
            }
            sum = sum * 10 + x % 10;
            x  = x / 10;
        }
        return sum;
    }
};
