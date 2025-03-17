#include <vector>
class Solution
{
public:
    int maxSubArray(std::vector<int>& nums)
    {
        int i = 0;
        int currentSum = nums[i];
        int maxSum = INT_MIN;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (currentSum + nums[j] > nums[j])
            {
                currentSum += nums[j];
            }
            else
            {
                i = j;
                currentSum = nums[i];
            }
            maxSum = std::max(maxSum, currentSum);
        }
        return currentSum;
    }
};
