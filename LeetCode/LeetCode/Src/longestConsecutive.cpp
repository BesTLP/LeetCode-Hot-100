#include <vector>
#include <set>
#include <unordered_set>
class Solution
{
public:
    int longestConsecutive(std::vector<int>& nums)
    {
        if (nums.size() == 0) return 0;
        std::unordered_set<int> numSet(nums.begin(), nums.end());

        int maxLength = INT_MIN;
        for (int num : numSet)
        {
            int currentNum = num;
            if (numSet.find(currentNum - 1) == numSet.end())
            {
                int Length = 1;
                // 说明当前是起点数
                while (numSet.find(currentNum + 1) != numSet.end())
                {
                    currentNum++;
                    Length++;
                }
                maxLength = std::max(Length, maxLength);
            }
        }
        return maxLength;

    }
};