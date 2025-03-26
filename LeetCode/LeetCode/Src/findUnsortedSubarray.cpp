#include <vector>

class Solution
{
public:
    int findUnsortedSubarray(std::vector<int>& nums)
    {
        if (nums.size() <= 1) return 0;

        int left = 0;
        int right = nums.size() - 1;

        while (left < nums.size() - 1 && nums[left] <= nums[left + 1])
        {
            left++;
        }
        if (left == nums.size() - 1) return 0;

        while (right > 0 && nums[right] >= nums[right - 1])
        {
            right--;
        }

        int minValue = *std::min_element(nums.begin() + left, nums.begin() + right + 1);
        int maxValue = *std::max_element(nums.begin() + left, nums.begin() + right + 1);
        while (left > 0 && nums[left - 1] > minValue)
        {
            left--;
        }
        while (right < nums.size() - 1 && nums[right + 1] < maxValue)
        {
            right++;
        }

        return right - left + 1;
    }
};
//
//int main()
//{
//    std::vector<int> nums = {2, 3, 1, 4, 5};
//    Solution solution;
//    solution.findUnsortedSubarray(nums);
//}