#include <vector>
#include <queue>
/*
������������ nums ������ k���뷵�������е� k ������Ԫ�ء�
��ע�⣬����Ҫ�ҵ������������ĵ� k ������Ԫ�أ������ǵ� k ����ͬ��Ԫ�ء�
�������Ʋ�ʵ��ʱ�临�Ӷ�Ϊ O(n) ���㷨��������⡣
*/

// ����С�ѵ��㷨, ʱ�临�Ӷ�Ϊ O(nlogk)
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

////����ѡ���㷨, ʱ�临�Ӷ�O(n)
//int main()
//{
//    Solution solution;
//    std::vector<int> nums = { 3,2,1,5,6,4 };
//    solution.findKthLargest(nums, 2);
//
//}