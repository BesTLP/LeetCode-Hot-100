#include <vector>
#include <unordered_map>
class Solution 
{
public:
    int subarraySum(std::vector<int>& nums, int k) 
    {
        std::unordered_map<int, int> prefixSumCount;

        prefixSumCount[0] = 1; // 前缀和为 0 的数出现了一次
        int count = 0;
        int currentSum = 0;

        for (auto num : nums)
        {
            currentSum += num;
            if (prefixSumCount.find(currentSum - k) != prefixSumCount.end())
            {
                count += prefixSumCount[currentSum - k];
            }
            prefixSumCount[currentSum]++;
        }

        return count;
    }
};