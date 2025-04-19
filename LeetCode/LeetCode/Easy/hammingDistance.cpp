#include <vector>

class Solution
{
public:
    int hammingDistance(int x, int y)
    {
        // x = 4 : 0100
        // y = 1 : 0001
        // result = 2;
        int s = x ^ y;
        int ret = 0;
        while (s)
        {
            ret += s & 1;
            s = s >> 1;
        }
        return ret;
    }
};