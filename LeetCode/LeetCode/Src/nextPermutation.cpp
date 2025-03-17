#include <vector>
#include <iostream>
class Solution 
{
public:
    void nextPermutation(std::vector<int>& nums) 
    {
        int minIndex = -1;
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            if (nums[i] < nums[i + 1])
            {
                minIndex = i;
                break;
            }
        }
        if (minIndex == -1)
        {
            std::reverse(nums.begin(), nums.end());
            for (int k = 0; k < nums.size(); k++)
            {
                std::cout << nums[k];
                if (k != nums.size() - 1) std::cout << ",";
                else std::cout << std::endl;
            }
            return;
        }

        for (int j = nums.size() - 1; j > minIndex; j--)
        {
            if (nums[j] > nums[minIndex])
            {
                std::swap(nums[minIndex], nums[j]);
                std::reverse(nums.begin() + minIndex + 1, nums.end());
                break;
            }
        }
        for (int k = 0; k < nums.size(); k++)
        {
            std::cout << nums[k];
            if (k != nums.size() - 1) std::cout << " ";
            else std::cout << std::endl;
        }
        return;
    }
};

//int main()
//{
//    Solution solution;
//    std::vector<int> nums = { 1,2,2 };
//    solution.nextPermutation(nums);
//}