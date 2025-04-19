#include <vector>
#include <iostream>
class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        int row = 0;
        int col = cols - 1;

        while (row < rows && col >= 0)
        {
            if (matrix[row][col] == target)
            {
                return true;
            }
            else if (matrix[row][col] > target)
            {
                col--;
            }
            else
            {
                row++;
            }
        }

        return false;

    }
};
//
//int main()
//{
//    std::vector<std::vector<int>> matrix =
//    {
//        {1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}
//    };
//    Solution solution;
//    solution.searchMatrix(matrix, 5);
//
//}