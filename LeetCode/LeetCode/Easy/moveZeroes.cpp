#include <vector>
class Solution
{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int LeftZeroIndex = 0;
        int ValueIndex = 0;
        while (true)
        {
            while (LeftZeroIndex < nums.size() && nums[LeftZeroIndex] != 0)
            {
                LeftZeroIndex++;
            }
            if (LeftZeroIndex >= nums.size() - 1) break;

            ValueIndex = LeftZeroIndex + 1;
            while (ValueIndex < nums.size() && nums[ValueIndex] == 0)
            {
                ValueIndex++;
            }
            if (ValueIndex >= nums.size()) break;

            std::swap(nums[LeftZeroIndex], nums[ValueIndex]);
            LeftZeroIndex++;
        }
    }
};