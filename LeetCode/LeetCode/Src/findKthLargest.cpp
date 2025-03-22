#include <vector>
#include <queue>
/*
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
*/

// 用最小堆的算法, 时间复杂度为 O(nlogk)
class Solution 
{
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (int i = 0; i < nums.size(); i++)
        {
            if (pq.size() < k)
            {
                pq.push(nums[i]);
            }
            else if(nums[i] > pq.top())
            {
                pq.pop();
                pq.push(nums[i]);
            }
        }
        return pq.top();
    }
};

////快速选择算法, 时间复杂度O(n)
//int main()
//{
//    Solution solution;
//    std::vector<int> nums = { 3,2,1,5,6,4 };
//    solution.findKthLargest(nums, 2);
//
//}