# LeetCode-Hot-100

# 2025/2/26 [设计浏览器历史记录](https://leetcode.cn/problems/design-browser-history/?envType=daily-question&envId=2025-02-26)

这道题类似于游戏引擎中的<font color='A2CD5A'>**Layer**</font>的思想，可以考虑选用游戏引擎中常见的迭代器来实现。分析几个函数的功能

`void visit(string url) visit`：从当前页跳转访问 `url` 对应的页面 。执行此操作会把浏览历史前进的记录全部删除

当前页我们用<font color='CD96CD'>**`m_NowUrlPointer`**</font>指示，也就是在调用`visit`函数之后，你默认需要将该<font color='87CEFA'>**迭代器之前**</font>（或者之后，看你自己的选择）的所有`url`页面<font color='FFD00'>**全部删除**</font>

`string back(int steps)` 在浏览历史中后退 `steps` 步，然后返回对应的`url`

`string forward(int steps)` 在浏览历史中前进 `steps` 步，然后返回对应的`url`

```c++
// back
while (steps > 0 && m_NowUrlPointer != m_UrlVector.end() - 1) // 注意最后一个元素是.end() - 1的位置
{
    steps--;
    m_NowUrlPointer++;
}
return m_NowUrlPointer->c_str();
// forward
while (steps > 0 && m_NowUrlPointer != m_UrlVector.begin()) // 第一个元素是.begin()的位置
{
    steps--;
    m_NowUrlPointer--;
}
```

<font color='FFD00'>**为什么`back`是++而`forward`是--呢？**</font>

我在`visit`中的实现是这样的，默认<font color='CD96CD'>**m_NowUrlPointer**</font>永远<font color='87CEFA'>**指示的是当前`url`的插入位置**</font>，也就是<font color='87CEFA'>**如果一直`visit`，那么迭代器永远指向第一个元素**</font>，而不是最后一个元素

> `m_NowUrlPointer`可以使用->直接访问元素，<font color='87CEFA'>**`->` 运算符是 解引用 运算符 `*` 和 成员访问 运算符 `.` 的结合。**</font>

```c++
m_NowUrlPointer = m_UrlVector.emplace(m_NowUrlPointer, url);
m_NowUrlPointer = m_UrlVector.erase(m_UrlVector.begin(), m_NowUrlPointer);
```

```c++
#include "string"
#include "vector"
#include "iostream"
class BrowserHistory
{
public:
	BrowserHistory(std::string homepage);
	void visit(std::string url);
	std::string back(int steps);
	std::string forward(int steps);


	std::vector<std::string> m_UrlVector;
	std::vector<std::string>::iterator m_NowUrlPointer;

};

BrowserHistory::BrowserHistory(std::string homepage)
{
	m_NowUrlPointer = m_UrlVector.begin();
	visit(homepage);
}

void BrowserHistory::visit(std::string url)
{
	m_NowUrlPointer = m_UrlVector.emplace(m_NowUrlPointer, url);
	m_NowUrlPointer = m_UrlVector.erase(m_UrlVector.begin(), m_NowUrlPointer);
}

std::string BrowserHistory::back(int steps)
{
	while (steps > 0 && m_NowUrlPointer != m_UrlVector.end() - 1)
	{
		steps--;
		m_NowUrlPointer++;
	}
	return m_NowUrlPointer->c_str();
}

std::string BrowserHistory::forward(int steps)
{
	while (steps > 0 && m_NowUrlPointer != m_UrlVector.begin())
	{
		steps--;
		m_NowUrlPointer--;
	}

	return m_NowUrlPointer->c_str();
}


```

# 2025/2/27 [单词搜索](https://leetcode.cn/problems/word-search/description/)

给定一个 `m x n` 二维字符网格 `board` 和一个字符串单词 `word` 。如果 `word` 存在于网格中，返回 `true` ；否则，返回 `false` 

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

就是比较简单的使用`DFS`就可以解决的问题，棋盘上可以向四个方向移动

```c++
// 顺序为UP RIGHT LEFT DOWN
int MoveX[4] = { -1, 0, 0, 1 };
int MoveY[4] = { 0, 1, -1, 0 };
```

但是这道题我们可以提前做一些优化，比如如果`board`里面根本都没有`word`里面的字符或者字符数量更少，那么就不用进行后续的操作了。

注意一下，下面的判断条件需要分开写，因为如果`i`和`j`已经超出了`board`的范围，就会报数组越界错误。

```c++
if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
    return false;

if (visited[i][j] || board[i][j] != word[index])
    return false;

if (index == word.size() - 1) // 最后一个元素也能对的上
    return true;
```

```c++
#include "vector"
#include "iostream"
#include "string"

const int maxn = 1e3;
class Solution
{
public:

    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        // 重置 visited 数组
        memset(visited, false, sizeof(visited));

        int charCount[256] = { 0 };
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[i].size(); j++)
                charCount[board[i][j]]++;

        for (int i = 0; i < word.size(); i++)
        {
            char c = word[i];
            charCount[c]--;
            if (charCount[c] < 0)
                return false;
        }

        std::vector<std::vector<bool>> visited(board.size(), std::vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[i].size(); j++)
                if (board[i][j] - word[0] == 0)
                    if (Move(board, word, i, j, 0))
                        return true;

        return false;
    }

    bool Move(std::vector<std::vector<char>>& board, std::string& word, int i, int j, int index)
    {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return false;

        if (visited[i][j] || board[i][j] != word[index])
            return false;

        if (index == word.size() - 1) // 最后一个元素也能对的上
            return true;

        visited[i][j] = true;

        int MoveX[4] = { -1, 0, 0, 1 };
        int MoveY[4] = { 0, 1, -1, 0 };
        for (int ArrayIndex = 0; ArrayIndex < 4; ArrayIndex++)
            if (Move(board, word, i + MoveX[ArrayIndex], j + MoveY[ArrayIndex], index + 1))
                return true;

        visited[i][j] = false;
        return false;
    }

public:
    bool visited[maxn][maxn] = { false };
};
```



# 2025/3/1 [两数相加](https://leetcode.cn/problems/add-two-numbers/description/)

这个题目要求我们实现的是两个链表表示的数字相加的问题。

每个链表节点代表一个数字的一位，链表的<font color='87CEFA'>**头节点**</font>表示数字的<font color='87CEFA'>**最低位**</font>，链表的<font color='87CEFA'>**尾节点**</font>表示数字的<font color='87CEFA'>**最高位**</font>。

我们需要将两个链表表示的数字相加，并返回一个新的链表表示的结果。

其实类似于<font color='87CEFA'>**整数的相加减**</font>，我们只需要保证是<font color='87CEFA'>**从低位开始相加**</font>，处理好进位即可

```c++
    // 获取进位
    int Temp = (x + y + Temp) / 10;
    // 获取个位数
    int Value = (x + y + Temp) % 10;
```



注意循环的条件，可能会忘记如果还有进位的话依然需要构建一个节点来存储进位

```c++
    // 循环条件：l1或l2不为空，或者Temp不为0（即还有进位需要处理）
    while (l1 || l2 || Temp)
```

注意，只有当链表不为`nullptr`的时候，才能执行`Pointer->next`操作，否则会报错

```c++
    l1 = l1 != nullptr? l1->next : nullptr;
    l2 = l2 != nullptr? l2->next : nullptr;
```



```c++
    #include "iostream"
    #include "cstdio"

    struct ListNode 
    {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };
    class Solution 
    {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
        {
            ListNode* PreviousNode = nullptr;
            ListNode* FirstNode = nullptr;
            int Temp = 0; // 进位

            while (l1 || l2 || Temp)
            {
                int x = l1 != nullptr? l1->val : 0;
                int y = l2 != nullptr? l2->val : 0;

                if (FirstNode == nullptr)
                {
                    FirstNode = new ListNode();
                    FirstNode->val = (x + y + Temp) % 10;
                    PreviousNode = FirstNode;
                }
                else
                {
                    ListNode* CurrentNode = new ListNode();
                    CurrentNode->val = (x + y + Temp) % 10;
                    PreviousNode->next = CurrentNode;
                    PreviousNode = CurrentNode;
                }
                Temp = (x + y + Temp) / 10; // 获取到进位
                l1 = l1 != nullptr? l1->next : nullptr;
                l2 = l2 != nullptr? l2->next : nullptr;
            }
            return FirstNode;
        }
    };
```



# 2025/3/1 [完全平方数](https://leetcode.cn/problems/perfect-squares/)



完全平方数：可以由一个整数的平方获取的整数，比如
$$
1 = 1 * 1\\
4 = 2 * 2\\
9 = 3 * 3
$$
这道题需要用动态规划的形式来做，有的人可能想要使用贪心来做，比如
$$
12 = 9 + 1 + 1 + 1
$$
但实际上正确答案是
$$
12 = 4 + 4 + 4
$$
使用贪心的完全平方数数量是`4`，但是正确答案是`3`

## 状态转移方程



先来看一个例子，`dp[n]`代表的是组成当前数`n` 需要的最少的完全平方数的个数
$$
if(dp[4] > dp[4 - 1 * 1])\\
dp[4] = dp[4 - 1 * 1];\\
if(dp[4] > dp[4 - 2 * 2])\\
dp[4] = dp[4 - 2 * 2];
$$
因为我们每一次相加都是加的完全平方数，也就是跨度一定是`j * j`（`j`代表正整数）

所以求取`dp[4]`的时候，只需要找到`dp[3]`和`dp[0]`谁最小即可。

扩展到所有的`dp[n]`，只需要找到所有的`dp[n - j * j]`谁最小即可(其中`j <= sqrt(n)`)



```c++
    int numSquares(int n)
    {
        // 动态规划的方式来求，得正确的答案
        // 12 = 4 + 4 + 4 (3)
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j * j <= i; j++)
            {
                dp[i] = std::min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }

    int numSquares(int n)
    {
        // 贪心的方式来求，得不到正确的答案
        // 12 = 9 + 1 + 1 + 1 (4)
        std::vector<int> SquareNumber;
        for (int i = 1; i <= std::sqrt(n); i++)
        {
            SquareNumber.push_back(std::pow(i, 2));
        }

        int index = SquareNumber.size() - 1;
        int cnt = 0;
        while (n != 0)
        {
            if (n - SquareNumber[index] >= 0)
            {
                n -= SquareNumber[index];
                cnt++;
            }
            else
            {
                index--;
            }
        }

        return cnt;
    }
```



# 2025/3/2 [整数反转](https://leetcode.cn/problems/reverse-integer/description/)



> 执行用时分布：0ms



给你一个 32 位的有符号整数 `x` ，返回将 `x` 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 `[−231, 231 − 1]` ，就返回 0。

**假设环境不允许存储 64 位整数（有符号或无符号）。**



>虽然很明显偷偷存储也是可以的，但我们还是老实一点，一共有三个核心步骤

1.一直加最后一位，并且将之前的结果都✖10即可（有点类似于进制转换）

```c++
sum = sum * 10 + x % 10;
```

2.需要<font color='87CEFA'>**去掉前导零**</font>

```c++
// 去除前导零
while (x % 10 == 0)
    x /= 10;
```

3.判断结果是否超出范围

```c++
// [-2147483648, 2147483647] // 不能超过这个范围
if (sum < INT_MIN / 10 || (sum == INT_MIN / 10 && x % 10 > 8))
{
    // 比如是否是-214748365	如果是-214748364那么还需要判断最后以为是否大于8
    return 0;
}
if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && x % 10 > 7))
{
    // 比如是否是214748365	如果是214748364那么还需要判断最后一位是否大于7
    return 0;
}
```





```c++
#include "vector"
#include "iostream"
class Solution 
{
public:
    static int reverse(int x)
    {
        if (x == 0)
        {
            return 0;
        }
        // 去除前导零
        while (x % 10 == 0)
            x /= 10;

        int sum = 0;
        while (x != 0)
        {
            // [-2147483648, 2147483647] // 不能超过这个范围
            if (sum < INT_MIN / 10 || (sum == INT_MIN / 10 && x % 10 > 8))
            {
                return 0;
            }
            if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && x % 10 > 7))
            {
                return 0;
            }
            sum = sum * 10 + x % 10;
            x  = x / 10;
        }
        return sum;
    }
};
```





# 2025/3/2 [字符串转换整数 (atoi)](https://leetcode.cn/problems/string-to-integer-atoi/)

>执行用时分布: 0ms

无论是`去除前导零`

```c++
        // 去除前导零
        while (s[index] == '0' && index < s.size())
            index++; // 使用index下标，进一步节约erase耗时
```

还是每一步的`整数乘法`

```c++
            sum = sum * 10 + flag * (s[index] - '0');
```



还是最后判断`是否在整数范围之内`

```c++
        if (sum < INT_MIN / 10 || (sum == INT_MIN / 10 && s[index] - '0' > 8))
        {
            sum = INT_MIN;
            break;
        }
        if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && s[index] - '0' > 7))
        {
            sum = INT_MAX;
            break;
        }
```



另外一个关键点在于，不能写成

```c++
s[index] == " ";
```

C++中，字符串字面量 `" "` 是 `const char*`，但 `s[index]` 是 `char` 类型。

正确的写法是 `s[0] == ' '`，使用单引号表示字符。

```c++
s[index] == ' '
```



```c++
#include "string"
#include "iostream"
#include "cstdio"
class Solution 
{
public:
    int myAtoi(std::string s)
    {
        int index = 0;
        // 空格全清
        while (s[index] == ' ') // 注意这里不能使用" "，而是应该使用' '
            index++;

        int flag = 1;
        if (s[index] == '-' || s[index] == '+')
        {
            // 负数
            flag = s[index] == '-'? -1 : 1;
            index++;
        }

        // 去除前导零
        while (s[index] == '0' && index < s.size())
            index++;


        if (!(s[index] >= '0' && s[index] <= '9') || index == s.size()) return 0;

        int sum = 0;
        for (; index < s.size(); index++)
        {
            if (!(s[index] >= '0' && s[index] <= '9'))
            {
                break;
            }
            if (sum < INT_MIN / 10 || (sum == INT_MIN / 10 && s[index] - '0' > 8))
            {
                sum = INT_MIN;
                break;
            }
            if (sum > INT_MAX / 10 || (sum == INT_MAX / 10 && s[index] - '0' > 7))
            {
                sum = INT_MAX;
                break;
            }
            sum = sum * 10 + flag * (s[index] - '0');
        }
        return sum;
    }
};
```

# 2025/3/4 [删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/)

>执行用时：0ms

最容易想到的思路应该是，先遍历一遍链表，获取到链表的节点数之后，`n - i + 1`就是你要删除的节点

但是如何进行一次遍历就能找到需要删除的节点呢？

我们在这里引入快慢指针，快指针永远比慢指针多走`n`步，所以当快指针走到`nullptr`的时候，慢指针就会刚好走到要删除的第`n`个节点

```c++
ListNode* NextN = head;
ListNode* Current = head;

for (int i = 1; i <= n; i++)
    NextN = NextN->next;
```

当然你也可以考虑判断快指针的`next`是否是`nullptr`如果是`nullptr`的话，说明快指针的`next`就是要删除的节点，这样做可以不用记录`LastNode`上一个搜索到的节点

```c++
    ListNode* Last = Current;
    while (NextN)
    {
        NextN = NextN->next;
        Last = Current;
        Current = Current->next;
    }

    Last->next = Current->next;
    delete Current;

	// 我们这里做了一些改变，下面的方式可以不用记录上一个搜索到的节点
    while (NextN->next)
    {
        NextN = NextN->next;
        Current = Current->next;
    }

    ListNode* ToDelete = Current->next;
    Current->next = Current->next->next;
    delete ToDelete;
```

```c++
#include "iostream"
// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution 
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        if ((!head->next && n >= 1) || !head )
        {
            // 如果只有一个节点, 或者根本没有节点
            head = nullptr;
            return head;    
        }

        ListNode* NextN = head; // 快指针
        ListNode* Current = head; // 慢指针
        for (int i = 1; i <= n; i++)
            NextN = NextN->next;

        if (NextN == nullptr)
        {
            Current = head;
            if(head != nullptr)
                head = head->next;

            delete Current;

            return head;
        }

        // 我们这里做了一些改变
        while (NextN->next)
        {
            NextN = NextN->next;
            Current = Current->next;
        }

        ListNode* ToDelete = Current->next;
        Current->next = Current->next->next;
        delete ToDelete;

        return head;
    }
};
```

# 2025/3/4 [跳跃游戏](https://leetcode.cn/problems/jump-game/description/)

我们只需要记录当我们遍历到数组的第`i`个元素的时候，我们实际上能够走到的位置是`nums[i] + i`

```c++
nums = [2, 3, 1, 1, 5]
```

我们遍历到第1个元素的时候，能走到的最远是nums[0] + 0 = 2，也就是下标为2的元素，是第三个元素

我们遍历到第2个元素的时候，能走到的最远是nums[1] + 1 = 4，也就是下标为4的元素，是第五个元素，已经到达了数组末尾，返回true

```c++
nums = [3, 2, 1, 0, 4]
```

我们遍历到第1个元素的时候，能走到的最远是nums[0] + 0 = 3，也就是下标为3的元素

我们遍历到第2个元素的时候，能走到的最远是nums[1] + 1 = 3，也就是下标为3的元素

我们遍历到第3个元素的时候，能走到的最远是nums[2] + 2= 3，也就是下标为3的元素

我们遍历到第4个元素的时候，能走到的最远是nums[3] + 3 = 3，也就是下标为3的元素

事实上没有办法到达数组的末尾，所以返回false

我们可以发现，最终能够返回true的形式是，至少存在一个`nums[i] + i > nums.size() - 1`

```c++
#include "vector"
#include "iostream"

class Solution 
{
public:
    bool canJump(std::vector<int>& nums) 
    {
        if (nums.size() <= 1) return true;

        int JumpLocation = 0;
        for (int i = 0; i <= JumpLocation; i++)
        {
            // 动态更新能到达的最远的位置
            if (JumpLocation >= nums.size() - 1) return true;
            JumpLocation = std::max(JumpLocation, nums[i] + i);
        }

        return false;
    }
};
```

# 2025/3/4 [盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/description/)

题目要求我们计算一个由整数数组 `height` 表示的容器所能容纳的最大水量。数组中的每个元素代表容器在该位置的高度，容器的宽度由数组的索引差决定。我们需要找到两个高度，使得它们与它们之间的距离相乘得到的面积最大。
$$
Area = (j - i) * min(Height[j], Height[i]);
$$
所以我们的目标是保证`j - i `以及`min(Height[j], Height[i])`最大

- 使用两个指针 `lower` 和 `upper`，分别指向数组的起始和末尾。
- 计算当前指针所指的两个高度之间的面积，并更新最大面积。
- 移动指针的策略是：移动高度较小的指针，因为移动高度较大的指针不会增加面积。

- 如果 `height[lower] < height[upper]`，则移动 `lower` 指针向右。
- 否则，移动 `upper` 指针向左。

```c++
#include "vector"
#include "iostream"
class Solution 
{
public:
    int maxArea(std::vector<int>& height) 
    {
        int lower = 0;
        int upper = height.size() - 1;
        int maxArea = 0;
        while (lower < upper)
        {
            maxArea = std::max((upper -lower) * std::min(height[lower], height[upper]), maxArea);
            if (height[lower] > height[upper])
            {
                upper--;
            }
            else
            {
                lower++;
            }
        }
        return maxArea;
    }
};
```

