#include <vector>
#include <string>
#include <stack>
#include <map>
class Solution {
public:
    bool isValid(std::string s)
    {
        std::map<char, char> match;
        match[')'] = '(';
        match['}'] = '{';
        match[']'] = '[';
        std::stack<char> st;
        for (auto c : s)
        {
            if (c == '(' || c == '[' || c == '{')
                st.push(c);

            if (st.empty()) return false;

            if (c == ')' || c == '}' || c == ']')
            {
                if (st.top() == match[c])
                {
                    st.pop();
                }
                else
                {
                    return false;
                }
            }

        }
        return st.empty();
    }
};
//int main()
//{
//    Solution solution;
//    solution.isValid("([])");
//}