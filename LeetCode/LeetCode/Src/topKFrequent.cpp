#include <vector>
#include <unordered_map>
#include <queue>
class Solution 
{
    struct Compare
    {
        bool operator()(const std::pair<int, int> a, const std::pair<int, int > b)
        {
            return a.second > b.second;
        }
    };
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) 
    {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            if (map.find(nums[i]) != map.end())
            {
                map[nums[i]]++;
            }
            else
            {
                map[nums[i]] = 1;
            }
        }

        std::pair<int, int> KeyWithFrequence;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq;
        for (auto entry : map)
        {
            pq.push(entry);
            if (pq.size() > k)
            {
                pq.pop();
            }
        }

        std::vector<int> ret;
        while (!pq.empty())
        {
            ret.push_back(pq.top().first);
            pq.pop();
        }
        return ret;

    }
};
//
//int main()
//{
//    std::vector<int> nums = { 1,1,1,2,2,3 };
//    Solution solution;
//    solution.topKFrequent(nums, 2);
//}