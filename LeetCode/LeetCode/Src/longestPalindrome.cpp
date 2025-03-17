#include <string>

class Solution 
{
public:
    std::string longestPalindrome(std::string s) 
    {
        if (s.empty()) return "";
        int maxLength = INT_MIN;
        int start = -1;
        for (int i = 0; i < s.size(); i++)
        {
            int len1 = findPalindrome(s, i, i); // 奇数回文子串
            int len2 = findPalindrome(s, i, i + 1); // 偶数回文子串

            int len = std::max(len1, len2);
            if (len > maxLength)
            {
                maxLength = len;
                start = i - (len - 1) / 2;
            }
        }
        return s.substr(start, maxLength);
    }
private:
    int findPalindrome(const std::string& s, int left, int right)
    {
        while (left >= 0 && right <= s.size() - 1 && s[left] == s[right])
        {
            left--;
            right++;
        }
        return right - left - 1;
    }
};
//
//int main()
//{
//    Solution solution;
//    solution.longestPalindrome("babad");
//}