#include <vector>
#include <numeric>
class Solution 
{
public:
    bool canPartition(std::vector<int>& nums) 
    {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        for (int i = 0; i < nums.size(); i++)
        {
            if (sum - nums[i] >= 0) sum - nums[i];

            if (sum == 0) return true;
        }
        return false;
    }
};