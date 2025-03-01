#include "iostream"
#include "cstdio"
#include "cmath"
#include <vector>
class Solution
{
public:
    int numSquares(int n)
    {
        // n <= 1e4
        std::vector<int> SquareNumber;
        for (int i = 1; i <= std::sqrt(n); i++)
        {
            SquareNumber.push_back(std::pow(i, 2));
        }

        std::vector<int> result;

        int index = SquareNumber.size() - 1;
        int cnt = 0;
        while (n != 0)
        {
            if (n - SquareNumber[index] >= 0)
            {
                n -= SquareNumber[index];
                cnt++;
            }
            else
            {
                index--;
            }
        }

        return cnt;
    }
};

int main()
{
    int n = 12;
    Solution solution;
    std::cout << solution.numSquares(n) << std::endl;
}