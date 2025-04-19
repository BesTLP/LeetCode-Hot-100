#include <vector>

class Solution
{
public:
    int singleNumber(std::vector<int>& nums)
    {
        int single = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            single = single ^ nums[i];
        }

        return single;
    }
};