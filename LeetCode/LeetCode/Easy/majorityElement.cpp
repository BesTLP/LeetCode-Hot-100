#include <vector>
class Solution 
{
public:
    int majorityElement(std::vector<int>& nums)
    {
        int candicate = INT_MIN;
        int count = 0;
        for (auto v : nums)
        {
            if (count == 0)
            {
                candicate = v;
                count = 1;
            }
            else if (candicate != v)
            {
                count--;
            }
            else
            {
                count++;
            }
        }

        return candicate;
    }
};