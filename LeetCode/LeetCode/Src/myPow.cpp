#include "iostream"
#include "vector"
class Solution 
{
public:
    double myPow(double x, int n) 
    {
        if (x == 1 || n == 0) return 1;

        if (n == 1) return x;

        if (n == INT_MIN) return myPow(x, n + 1) / x;
        x = n < 0 ? 1 / x : x;
        n = n < 0 ? -n : n;
        
        double temp = myPow(x, n / 2);
        if (n % 2 == 0)
        {
            return temp * temp;
        }
        else
        {
            return temp * temp * x;
        }
    }
};