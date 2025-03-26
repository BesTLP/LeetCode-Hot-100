#include <vector>
class Solution
{
private:
    int partition(std::vector<int>& nums, int left, int right)
    {
        if (left == right) return left;
        int pivotIndex = left; // �������������Χ
        int pivot = nums[pivotIndex];

        std::swap(nums[pivotIndex], nums[left]); // �Ȱ� pivot �ŵ������, ����������ܻḲ�ǵ����λ���ϵ�ֵ
        pivotIndex = left;

        while (left < right)
        {
            while (left < right && nums[right] >= pivot) right--; // �ҵ��Ҳ�С�� pivot ��ֵ
            if (left < right)
            {
                nums[pivotIndex] = nums[right]; // ���
                pivotIndex = right;
            }

            while (left < right && nums[left] <= pivot) left++; // �ҵ������� pivot ��ֵ
            if (left < right)
            {
                nums[pivotIndex] = nums[left]; // �������
                pivotIndex = left;
            }
        }
        nums[pivotIndex] = pivot; // ��ԭ pivot ����ȷλ��
        return pivotIndex;
    }


    int quickSelect(std::vector<int>& nums, int left, int right, int k)
    {
        if (left == right)
        {
            return nums[left];
        }

        int pivotIndex = partition(nums, left, right);

        int rank = nums.size() - pivotIndex; // pivotIndex ������ǵ� `rank` �����
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
////����ѡ���㷨, ʱ�临�Ӷ�O(n)
//int main()
//{
//    Solution solution;
//    std::vector<int> nums = { 3,2,3,1,2,4,5,5,6 };
//    solution.findKthLargest(nums, 4);
//
//}