#include <vector>
class Solution
{
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            int trueIndex;
            if (nums[i] > n)
                trueIndex = nums[i] - n - 1;
            else
                trueIndex = nums[i] - 1;

            if (nums[trueIndex] <= n)
            {
                nums[trueIndex] += n;
            }
        }

        std::vector<int> result;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] <= n)
            {
                result.push_back(i + 1);
            }
        }
        return result;
    }

};

int main()
{
    Solution solution;
    std::vector<int> nums = { 4,3,2,7,7,2,3,1 };
    solution.findDisappearedNumbers(nums);

}