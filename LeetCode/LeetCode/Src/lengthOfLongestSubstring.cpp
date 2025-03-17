#include <set>
#include <string>
#include <vector>
#include <unordered_set>
class Solution 
{
public:
    int lengthOfLongestSubstring(std::string s) 
    {
        if (s.empty())
        {
            return 0;
        }
        std::unordered_set<char> charSet;
        int left = 0;
        int maxLength = INT_MIN;
        for (int right = 0; right < s.size(); right++)
        {
            while (charSet.find(s[right]) != charSet.end())
            {
                charSet.erase(s[left]);
                left++;
            }
            charSet.insert(s[right]);
            maxLength = std::max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};
//
//int main()
//{
//    Solution solution;
//    solution.lengthOfLongestSubstring("pwwkew");
//}