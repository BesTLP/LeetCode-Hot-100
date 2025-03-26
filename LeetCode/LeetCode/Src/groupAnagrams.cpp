#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (std::string str : strs)
        {
            std::string value = str;
            std::string key = str;
            std::sort(key.begin(), key.end());

            map[key].push_back(value);
        }

        std::vector<std::vector<std::string>> result;
        for (auto entry : map)
        {
            result.push_back(entry.second);
        }
        return result;
    }
};