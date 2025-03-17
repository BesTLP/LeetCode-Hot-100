#include <vector>
#include <iostream>
class Solution 
{
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) 
    {
        if (nums.size() == 0) return { -1, -1 };

        int left = 0;
        int right = nums.size() - 1;
        int mid = left + (right - left) / 2;
        while (left <= right && nums[mid] != target)
        {
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
            mid = left + (right - left) / 2;
        }

        if (right < left || nums[mid] != target)
        {
            return { -1, -1 };
        }
        if (nums[mid] == target)
        {
            left = right = mid;
            while (left - 1 >= 0 && nums[left - 1] == target) left--;
            while (right + 1 < nums.size() && nums[right + 1] == target) right++;
        }

        return { left, right };
    }
};
//int main()
//{
//    Solution solution;
//    std::vector<int> nums = {2, 2};
//    int target = 3;
//    std::vector<int> result = solution.searchRange(nums, target);
//
//    std::cout << "目标值的范围是: [" << result[0] << ", " << result[1] << "]" << std::endl;
//    return 0;
//}