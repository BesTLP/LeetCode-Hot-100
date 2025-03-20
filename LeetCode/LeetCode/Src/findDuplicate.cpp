#include <vector>

class Solution 
{
public:
    int findDuplicate(std::vector<int>& nums)
    {
        int fast = nums[nums[0]];
        int slow = nums[0];
        while (fast != slow)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;
        while (fast != slow)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return fast;
    }
};
