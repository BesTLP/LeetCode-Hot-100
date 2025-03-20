#include <vector>

class Solution
{
public:
    int maxProduct(std::vector<int>& nums)
    {
        std::vector<int> dpMax(nums.size(), 1);
        std::vector<int> dpMin(nums.size(), 1);
        dpMax[0] = nums[0];
        dpMin[0] = nums[0];
        int maxValue = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            dpMax[i] = nums[i];
            dpMax[i] = std::max(dpMax[i - 1] * nums[i], dpMax[i]);
            dpMax[i] = std::max(dpMin[i - 1] * nums[i], dpMax[i]);

            dpMin[i] = nums[i];
            dpMin[i] = std::min(dpMin[i - 1] * nums[i], dpMin[i]);
            dpMin[i] = std::min(dpMax[i - 1] * nums[i], dpMin[i]);

            maxValue = std::max(maxValue, nums[i]);
            maxValue = std::max(maxValue, nums[i] * dpMax[i - 1]);
            maxValue = std::max(maxValue, nums[i] * dpMin[i - 1]);
        }
        return maxValue;
    }
};