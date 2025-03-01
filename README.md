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













































