#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
class Solution
{
public:
    int threeSumClosest(std::vector<int>& nums, int target)
    {
        std::sort(nums.begin(), nums.end());

        int result = 0;
        int minMinus = INT_MAX;

        for (int i = 0; i < nums.size(); i++)
        {
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                int minus = std::abs(target - sum);
                if (minus == 0) return sum;

                if (minus < minMinus)
                {
                    result = sum;
                    minMinus = minus;
                }

                if (sum > target)
                {
                    right--;
                }
                else
                {
                    left++;
                }

            }
        }

        return result;
    }
};