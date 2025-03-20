#include <vector>

class Solution
{
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums)
    {
        std::vector<int> left(nums.size(), 1);
        std::vector<int> right(nums.size(), 1);
        std::vector<int> result(nums.size());
        left[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            left[i] = left[i - 1] * nums[i];
        }
        right[nums.size() - 1] = nums[nums.size() - 1];
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            right[i] = nums[i] * right[i + 1];
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (i - 1 >= 0 && i + 1 < nums.size())
            {
                result[i] = left[i - 1] * right[i + 1];
            }
            else if (i - 1 >= 0)
            {
                result[i] = left[i - 1];
            }
            else
            {
                result[i] = right[i + 1];
            }
        }

        return result;
    }
};