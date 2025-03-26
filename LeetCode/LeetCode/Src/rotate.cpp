#include <vector>
#include <algorithm>
class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix)
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        for (int i = 0; i < matrix.size(); i++)
        {
            std::reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};