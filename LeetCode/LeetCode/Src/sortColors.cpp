#include <vector>
class Solution 
{
public:
    void sortColors(std::vector<int>& nums)
    {
        int left = 0;
        int mid = 0;
        int right = nums.size() - 1;
        while (mid <= right)
        {
            if (nums[mid] == 1) mid++;
            else if (nums[mid] == 0)
            {
                std::swap(nums[mid], nums[left]);
                left++;
                mid++;
            }
            else if (nums[mid] == 2)
            {
                std::swap(nums[mid], nums[right]);
                right--;
            }
        }
    }
};
int main()
{
    Solution solution;
    solution.sortColors({ 2,0,2,1,1,0 });
}