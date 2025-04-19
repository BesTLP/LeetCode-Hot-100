#include <vector>
#include <unordered_map>
#include <map>
class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> mp;

        for (int i = 0; i < nums.size(); i++)
        {
            int value = target - nums[i];
            auto it = mp.find(value);
            if (it != mp.end() && mp[value] != i)
            {
                return { it->second, i };
            }

            mp[nums[i]] = i;
        }
    }
};