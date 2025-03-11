#include "vector"
#include "iostream"

class Solution 
{
public:
    static bool canJump(std::vector<int>& nums) 
    {
        if (nums.size() <= 1) return true;

        int JumpLocation = 0;
        for (int i = 0; i <= JumpLocation; i++)
        {
            if (JumpLocation >= nums.size() - 1) return true;
            JumpLocation = std::max(JumpLocation, nums[i] + i);
        }

        return false;
    }
};