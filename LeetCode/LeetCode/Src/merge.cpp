#include <vector>
#include <algorithm>
class Solution 
{
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals)
    {
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& First, const std::vector<int>& Second)
        {
                if (First[0] != Second[0])
                    return First[0] < Second[0];
                else
                    return First[1] < Second[1];
        });

        std::vector<std::vector<int>> mergeResult;
        std::vector<int> TempResult = intervals[0];
        for (int i = 1; i < intervals.size(); i++)
        {
            std::vector<int> currentInterval = intervals[i];
            int currentLeft = currentInterval[0];
            int currentRight = currentInterval[1];
            if (TempResult[1] < currentLeft)
            {
                mergeResult.push_back(TempResult);
                TempResult = currentInterval;
            }
            else if (TempResult[1] >= currentLeft && TempResult[1] <= currentRight)
            {
                TempResult[1] = currentRight;
            }
        }
        // 处理最后一个区间
        mergeResult.push_back(TempResult);

        return mergeResult;
    }
};
//
//int main()
//{
//    std::vector<std::vector<int>> intervals =
//    {
//        {{1,4},{2,3}}
//    };
//    Solution solution;
//    solution.merge(intervals);
//}