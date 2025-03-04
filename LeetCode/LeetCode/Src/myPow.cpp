#include "iostream"
#include "vector"
class Solution 
{
public:
    double myPow(double x, int n) 
    {
        if (x == 1 || n == 0) return 1;

        if (n == 1) return x;

        long long int m = n;
        x = n < 0 ? 1 / x : x;
        m = m < 0 ? -m : m;
        
        double temp = myPow(x, m / 2);
        if (m % 2 == 0)
        {
            return temp * temp;
        }
        else
        {
            return temp * myPow(x, m / 2 + 1);
        }
    }
};

int main()
{
    Solution solution;
    std::cout << solution.myPow(2.0, -2147483648);
}