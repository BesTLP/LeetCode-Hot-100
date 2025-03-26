#include <vector>
class Solution
{
private:
    int partition(std::vector<int>& nums, int left, int right)
    {
        if (left == right) return left;
        int pivotIndex = left; // 修正随机索引范围
        int pivot = nums[pivotIndex];

        std::swap(nums[pivotIndex], nums[left]); // 先把 pivot 放到最左边, 否则后续可能会覆盖掉这个位置上的值
        pivotIndex = left;

        while (left < right)
        {
            while (left < right && nums[right] >= pivot) right--; // 找到右侧小于 pivot 的值
            if (left < right)
            {
                nums[pivotIndex] = nums[right]; // 填坑
                pivotIndex = right;
            }

            while (left < right && nums[left] <= pivot) left++; // 找到左侧大于 pivot 的值
            if (left < right)
            {
                nums[pivotIndex] = nums[left]; // 继续填坑
                pivotIndex = left;
            }
        }
        nums[pivotIndex] = pivot; // 还原 pivot 到正确位置
        return pivotIndex;
    }


    int quickSelect(std::vector<int>& nums, int left, int right, int k)
    {
        if (left == right)
        {
            return nums[left];
        }

        int pivotIndex = partition(nums, left, right);

        int rank = nums.size() - pivotIndex; // pivotIndex 代表的是第 `rank` 大的数
        if (rank == k)
            return nums[pivotIndex];
        else if (rank > k)
            return quickSelect(nums, pivotIndex + 1, right, k);
        else
            return quickSelect(nums, left, pivotIndex - 1, k);

    }
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        int ret = quickSelect(nums, 0, nums.size() - 1, k);
        return ret;
    }
};
////快速选择算法, 时间复杂度O(n)
//int main()
//{
//    Solution solution;
//    std::vector<int> nums = { 3,2,3,1,2,4,5,5,6 };
//    solution.findKthLargest(nums, 4);
//
//}