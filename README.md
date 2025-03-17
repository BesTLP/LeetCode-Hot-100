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

# 2025/3/4 [ Pow(x, n) ](https://leetcode.cn/problems/powx-n/submissions/605982513/)

```c++
执行时间:0ms
```





这道题目是经典的快速幂算法问题，要求实现一个函数 `myPow(double x, int n)`，计算 `x` 的 `n` 次方。

特殊情况：

- 如果 `x` 为 1，那么无论 `n` 是多少，结果都是 1。
- 如果 `n` 为 0，那么任何数的 0 次方都是 1。
- 如果 `n` 为 1，那么结果就是 `x` 本身。

**负指数处理**：如果 `n` 是负数，我们可以将其转换为正数，然后计算 `x` 的 `-n` 次方，最后取倒数。

我们通过通过递归将问题分解为更小的子问题，利用 `x^n = x^(n/2) * x^(n/2)` 的性质，减少计算次数。

```c++
if(n % 2 == 0) x^n = x^(n/2) * x^(n/2); // like: n = 4

if(n % 2 != 0) x^n = x^(n/2) * x^(n/2) * x; // like: n = 5
```

但是测试用例里面涉及一个测试用例`(2， INT_MIN)`

>要注意`INT`的范围实际上是[-2^31 -1 , 2^31]，所以INT_MIN直接取负数的话是会超出范围的
>
>而`-(INT_MIN + 1) = INT_MAX`所以我们可以用下面的方式来解决这个问题
>
>```c++
>if(n == INT_MIN) return myPow(x, n + 1) / x;
>```
>
>

```c++
#include "iostream"
#include "vector"
class Solution 
{
public:
    double myPow(double x, int n) 
    {
        if (x == 1 || n == 0) return 1;

        if (n == 1) return x;

        if (n == INT_MIN) return myPow(x, n + 1) / x;
        x = n < 0 ? 1 / x : x;
        n = n < 0 ? -n : n;
        
        double temp = myPow(x, n / 2);
        if (n % 2 == 0)
        {
            return temp * temp;
        }
        else
        {
            return temp * temp * x;
        }
    }
};
```



# 2025/3/10 [电话号码的字母组合](https://leetcode.cn/problems/letter-combinations-of-a-phone-number/solutions/388738/dian-hua-hao-ma-de-zi-mu-zu-he-by-leetcode-solutio/)



给定一个仅包含数字 `2-9` 的字符串，返回所有它能表示的字母组合。答案可以按 **任意顺序** 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

**示例 1：**

```
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
```

**示例 2：**

```
输入：digits = ""
输出：[]
```

**示例 3：**

```
输入：digits = "2"
输出：["a","b","c"]
```



用`DFS`即可完成，注意在这道题之中，我们使用DFS是可以重复的，例如下面的情况是可以允许的：

```c++
输入：digits = "22"
输出：["aa","ab","ac",......]
```

所以我们的`DFS`代码就变成了

```c++
void DFS(std::vector<std::string>& result, std::string& TempResult, std::vector<int>& index, int cnt)
{
    if (cnt == index.size())
    {
        result.push_back(TempResult);
        return;
    }
    int i = index[cnt];
    for (int j = 0; j < NumberChar[i].size(); j++)
    {
        TempResult.push_back(NumberChar[i][j]);
        DFS(result, TempResult, index, cnt + 1);
        TempResult.pop_back();
    }
}
```

定义的二维动态数组如下，注意`0`和`1`并不代表任何字母

```c++
const std::vector<std::vector<char>> Solution::NumberChar =
{
    {},
    {},
    {'a','b','c'},
    {'d','e','f'},
    {'g','h','i'},
    {'j','k','l'},
    {'m','n','o'},
    {'p','q','r','s'},
    {'t','u', 'v'},
    {'w','x','y','z'}
};
```



```c++
#include "iostream"
#include "vector"
#include "string"

class Solution
{
public:
    static const std::vector<std::vector<char>> NumberChar;
    void DFS(std::vector<std::string>& result, std::string& TempResult, std::vector<int>& index, int cnt)
    {
        if (cnt == index.size())
        {
            result.push_back(TempResult);
            return;
        }
        int i = index[cnt];
        for (int j = 0; j < NumberChar[i].size(); j++)
        {
            TempResult.push_back(NumberChar[i][j]);
            DFS(result, TempResult, index, cnt + 1);
            TempResult.pop_back();
        }
    }
    std::vector<std::string> letterCombinations(std::string digits)
    {
        if (digits.empty()) return std::vector<std::string>();

        std::vector<int> index;
        for (auto c : digits)
        {
            index.push_back(c - '0');
        }
        std::vector<std::string> result;
        std::string TempResult;

        DFS(result, TempResult, index, 0);
        return result;
    }
};
```

# 2025/3/10 [全排列](https://leetcode.cn/problems/permutations/submissions/)

给定一个不含重复数字的数组 `nums` ，返回其 *所有可能的全排列* 。你可以 **按任意顺序** 返回答案。

 **示例 1：**

```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

**示例 2：**

```
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```

**示例 3：**

```
输入：nums = [1]
输出：[[1]]
```

全排列的每一次`DFS`都需要从头开始查找当前没有被加入到`TempResult`的数字，递归的终止条件是当前已经把所有数字都添加到了`TempResult`中

 ```c++
 #include <vector>
 
 class Solution 
 {
 private:
     void DFS(std::vector<std::vector<int>>& Results, std::vector<int>& TempResult, std::vector<int>& nums, int cnt)
     {
         if (cnt == nums.size())
         {
             Results.push_back(TempResult);
             return;
         }
 
         for (int i = 0; i < nums.size(); i++)
         {
             if (!flag[i])
             {
                 flag[i] = true;
                 TempResult.push_back(nums[i]);
                 DFS(Results, TempResult, nums, cnt + 1);
                 TempResult.pop_back();
                 flag[i] = false;
             }
         }
     }
     
 public:
     std::vector<std::vector<int>> permute(std::vector<int>& nums) 
     {
         std::vector<std::vector<int>> Results;
         std::vector<int> TempResult;
         DFS(Results, TempResult, nums, 0);
 
         return Results;
     }
 
     bool flag[10] = { false };
 };
 ```

# 2025/3/11 [最小路径和](https://leetcode.cn/problems/minimum-path-sum/description/)

给定一个包含非负整数的 `m x n` 网格 `grid` ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

**说明：**<font color='FFD00'>**每次只能向下或者向右移动一步。**</font>

---

这道题的特点是每次<font color='87CEFA'>**只能向右或向下移动**</font>，因此不会出现回退的情况，也就不需要记录是否访问过当前网格。我们可以从多个角度来解决这个问题，包括 **DFS**、**BFS**、**动态规划（DP）** 和 **Dijkstra 算法**。

### DFS 解法

DFS（深度优先搜索）是一种递归的搜索方法，适用于路径搜索问题。我们需要明确以下几点：

1. **搜索结束条件**：当当前位置到达右下角时，搜索结束，并更新最小路径和。

2. **继续搜索条件**：由于只能向右或向下移动，且不需要回退，因此可以直接递归搜索下一个可能的网格。

   >注意，一般情况下需要记录当前搜索的网格是否已经被访问，只是当前题较为特殊

- 搜索结束，当目前已经到达右下角时搜索结束

  ```c++
  if (x == m - 1 && y == n - 1)
  {
      minSum = std::min(sum, minSum);
      return;
  }
  ```

- 继续搜索，由于本题并不涉及到回退的问题，因此可以直接继续搜索，直到搜索结束

  ```c++
  int moveX[2] = { 1,0 };
  int moveY[2] = { 0,1 };
  for (int i = 0; i < 2; i++)
  {
      // i = 0 →
      // i = 1 ↓
      int nextX = x + moveX[i];
      int nextY = y + moveY[i];
      if (nextX >= 0 && nextX < m &&
          nextY >= 0 && nextY < n )
      {
          DFS(grid, nextX, nextY, sum + grid[nextX][nextY]);
      }
  }
  ```

```c++
///********************************
//*************  DFS  *************
//*********************************/

class Solution 
{
public:
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        minSum = INT_MAX;
        DFS(grid, 0, 0, grid[0][0]);
        return minSum;
    }
private:
    void DFS(std::vector<std::vector<int>>& grid, int x, int y, int sum)
    {
        int m = grid.size();
        int n = grid[0].size();
        if (x == m - 1 && y == n - 1)
        {
            minSum = std::min(sum, minSum);
            return;
        }
        int moveX[2] = { 1,0 };
        int moveY[2] = { 0,1 };
        for (int i = 0; i < 2; i++)
        {
            int nextX = x + moveX[i];
            int nextY = y + moveY[i];
            if (nextX >= 0 && nextX < m &&
                nextY >= 0 && nextY < n )
            {
                DFS(grid, nextX, nextY, sum + grid[nextX][nextY]);
            }
        }
    }
    int minSum;
};
```

虽然 DFS 解法直观易懂，但在网格较大的情况下，时间复杂度会非常高，因为存在大量的重复计算，一般的算法题稍微添加一个时间限制就容易过不了。

### BFS 解法

BFS（广度优先搜索）是一种基于队列的搜索方法，适用于路径搜索问题。我们需要明确以下几点：

1. **搜索结束条件**：当当前位置到达右下角时，搜索结束，并更新最小路径和。

   ```c++
   if (x == grid.size() - 1 && y == grid[0].size() - 1)
   {
       minSum = std::min(minSum, sum);
   }
   ```

2. **继续搜索条件**：由于只能向右或向下移动，因此可以直接将下一个可能的网格加入队列。

   ```c++
   if (x + 1 < grid.size())
   {
       aQueue.emplace(Location(x + 1, y, sum + grid[x + 1][y]));
   }
   if (y + 1 < grid[0].size())
   {
       aQueue.emplace(Location(x, y + 1, sum + grid[x][y + 1]));
   }
   ```

```c++
///********************************
//*************  BFS  *************
//*********************************/
class Solution
{
public:
    struct Location
    {
        Location(int _x, int _y, int _sum)
            : x(_x), y(_y), sum(_sum) {}

        int x;
        int y;
        int sum;
    };
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        std::queue<Location> aQueue;
        aQueue.emplace(Location(0, 0, grid[0][0]));
        int minSum = INT_MAX;
        while (!aQueue.empty())
        {
            Location front = aQueue.front();
            int x = front.x;
            int y = front.y;
            int sum = front.sum;
            aQueue.pop();
            if (x == grid.size() - 1 && y == grid[0].size() - 1)
            {
                minSum = std::min(minSum, sum);
            }
            if (x + 1 < grid.size())
            {
                aQueue.emplace(Location(x + 1, y, sum + grid[x + 1][y]));
            }
            if (y + 1 < grid[0].size())
            {
                aQueue.emplace(Location(x, y + 1, sum + grid[x][y + 1]));
            }
        }
        return minSum;
    }
};

```

BFS的解决办法和DFS一样，容易出现超出时间限制的情况。

### 动态规划（DP）解法

动态规划通过存储中间结果来避免重复计算，时间复杂度为 O(m * n)，适合大规模网格。

因为这道题的特殊性，所以可以使用动态规划去做，但是如果上下左右都可以移动的话，则无法使用动态规划。

1. **初始化**：

   - `dp[0][0]` 初始化为 `grid[0][0]`，表示起点的路径和。

   - 初始化第一列和第一行的路径和，第一列只能由上方网格移动而来，第一行也只能由左侧的网格移动而来

     ```c++
     dp[0][0] = grid[0][0];
     for (int i = 1; i < m; i++)
     {
         dp[i][0] = dp[i - 1][0] + grid[i][0];
     }
     for (int i = 1; i < n; i++)
     {
         dp[0][i] = dp[0][i - 1] + grid[0][i];
     }
     ```

2. **状态转移**：

   - 对于每个网格 `(i, j)`，其最小路径和为上方和左方网格的最小值加上当前网格的值。

     ```c++
     for (int i = 1; i < m; i++)
     {
         for (int j = 1; j < n; j++)
         {
             dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
         }
     }
     ```

### Dijkstra 算法解法

Dijkstra 算法是一种贪心算法，适用于带权图的最短路径问题。我们可以将网格看作图，每个网格的值作为边的权重。

Dijkstra 算法是通过找当前最短路，以求实现全局最短的方法。

找最短路的方法我们需要通过优先队列构建最小堆来实现。

```c++
struct Location
{
    Location(int _x, int _y, int _sum)
        : x(_x), y(_y), sum(_sum) {}
    int x, y, sum;
};
struct CompareLocation
{
    bool operator()(const Location& L1, const Location& L2)
    {
        return L1.sum > L2.sum; // 最小堆,注意是＞符号
    }
};
std::priority_queue<Location, std::vector<Location>, CompareLocation> priQueue;
```

#### 代码解析

1. **初始化**：

   - 使用最小堆 `priQueue` 存储待搜索的位置，起点 `(0, 0, grid[0][0])` 入队。
   - `dist` 表初始化为 `INT_MAX`，表示每个位置的最小路径和。

2. **Dijkstra 过程**：

   - 从堆中取出堆顶元素，检查是否到达右下角。如果到达，则返回当前路径和。

   - 将当前节点的右节点和下节点加入堆（如果它们在网格范围内，并且新路径和更小）。

     ```c++
     for (int i = 0; i < 2; i++)
     {
         int nextX = top.x + moveX[i];
         int nextY = top.y + moveY[i];
         if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n)
         {
             int newSum = top.sum + grid[nextX][nextY];
             if (newSum < dist[nextX][nextY])
             {
                 dist[nextX][nextY] = newSum;
                 priQueue.push(Location(nextX, nextY, newSum));
             }
         }
     }
     ```

# 2025/3/11 [岛屿数量](https://leetcode.cn/problems/number-of-islands/description/)

给你一个由 `'1'`（陆地）和 `'0'`（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

---

这道题其实很简单，就是查找有多少个连通图，我们对当前标记为1的网格进行DFS或者BFS搜索，就可以将其周围的所有标记为1的网格全部访问完。

我们只需要记录下来我们一共执行了多少次访问即可。

>注意，当我们进入DFS或者BFS函数的时候，与当前进入的网格1附近的所有元素为1的网格都会被赋值为0，整个过程动态变化，因此当前连通的岛屿只会被访问一次，并不会多次访问。

```c++
void BFS(int x, int y, std::vector<std::vector<char>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    int mX[4] = { 1,-1,0,0 };
    int mY[4] = { 0,0,1,-1 };

    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(x, y));
    grid[x][y] = '0';
    while (!q.empty())
    {
        auto front = q.front();
        q.pop();
        int x = front.first;
        int y = front.second;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + mX[i];
            int ny = y + mY[i];
            if (nx >= 0 && nx < m &&
                ny >= 0 && ny < n)
            {
                if (grid[nx][ny] - '0')
                {
                    grid[nx][ny] = '0';
                    q.push(std::make_pair(nx, ny));
                }
            }
        }
    }
}

void DFS(int x, int y, std::vector<std::vector<char>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    int mX[4] = { 1,-1,0,0 };
    int mY[4] = { 0,0,1,-1 };
    if (x >= 0 && x < m && y >= 0 && y < n)
    {
        if (grid[x][y] - '0')
        {
            grid[x][y] = '0';
            for (int i = 0; i < 4; i++)
            {
                int nx = x + mX[i];
                int ny = y + mY[i];
                {
                    DFS(nx, ny, grid);
                }
            }
        }
    }
}
int numIslands(std::vector<std::vector<char>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    int cnt = 0;
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] - '0')
            {
                //BFS(i, j, grid);
                DFS(i, j, grid);
                cnt++;
            }

        }
    }
    return cnt;
}
};
```

# 2025/3/11 [不同路径](https://leetcode.cn/problems/unique-paths/description/)

一个机器人位于一个 `m x n` 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

---

关键点也是，可以向下或者向右移动，因此我们可以通过动态规划来实现，和最小路径和的思路都是一样的，可以使用DFS或者BFS，但是大概率依然会超时。

```c++
class Solution
{
public:
	int uniquePaths(int m, int n)
	{
		std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
		dp[0][0] = 1;
		for (int i = 1; i < m; i++)
		{
			dp[i][0] = dp[i - 1][0];
		}
		for (int i = 1; i < n; i++)
		{
			dp[0][i] = dp[0][i - 1];
		}

		for (int i = 1; i < m; i++)
		{
			for (int j = 1; j < n; j++)
			{
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};

//class Solution
//{
//public:
//    void DFS(int m, int n, int x, int y)
//    {
//        if (x == m - 1 && y == n - 1)
//        {
//            cnt++;
//        }
//        for (int i = 0; i < 2; i++)
//        {
//            int nx = x + moveX[i];
//            int ny = y + moveY[i];
//            if (nx < m && ny < n)
//                DFS(m, n, nx, ny);
//        }
//
//    }
//    int uniquePaths(int m, int n)
//    {
//        DFS(m, n, 0, 0);
//        return cnt;
//    }
//    int cnt = 0;
//    int moveX[2] = { 1, 0 };
//    int moveY[2] = { 0, 1 };
//};
```

# 2025/3/15 [括号生成](https://leetcode.cn/problems/generate-parentheses/)



数字 `n` 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。

核心：

1. 左括号出现的次数不可以多余`n`

2. 右括号出现的次数不可以多余左括号
3. 只要满足以上两点就可以一直递归

```c++
if(left < n)
{
    DFS(s + "(", left + 1, right, n);
}
if(right < left)
{
    DFS(s + "(", left + 1, right, n);
}
```



递归结束条件，当左括号和右括号都达到`n`值，代表递归结束，为一次结果存储。

```c++
if(left == n && right == n)
{
    // 当前为一次结果
}
```



```c++
#include <vector>
#include <string>
#include <iostream>

class Solution
{
public:
    void DFS(std::string s, int left, int right, int n)
    {
        if (left ==  n && right == n)
        {
            result.push_back(s);
            return;
        }
        if (left < n)
        {
            DFS(s + "(", left + 1, right, n);
        }
        if (right < left)
        {
            DFS(s + ")", left, right + 1, n);
        }
    }
    std::vector<std::string> generateParenthesis(int n) 
    {
        std::string s;
        DFS(s, 0, 0, n);
        return result;
    }
public:
    std::vector<std::string> result;
};
```

# 2025/3/15 [三数之和](https://leetcode.cn/problems/3sum/)

给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请你返回所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。

防止三元组重复的方法：

1. 先将整数数组按顺序排序

2. 如果当前遍历的数字`nums[i] == nums[i - 1]`那么代表当前数字所涉及的情况已经被全部找到

3. 对于`nums[j]`以及`nums[k]`同理

   >`j`从 `i + 1`开始遍历，`k`从数组的末尾开始向前遍历，因此`j`需要判断与`j + 1`的值
   >
   >`k` 需要判断与`k - 1`的值

如果是按照从小到大进行排序，如果当前`sum < 0`，应该移动左指针，反之移动右指针

```c++
else if (sum < 0)
{
    left++;
}
else
{
    right--;
}
```

只有当前`sum = 0 `的时候，才需要同时移动指针，代表当前情况已经记录

该题我们使用固定`i`，利用双指针的方式求解

```c++
#include "string"
#include "vector"
#include "iostream"
#include <algorithm>
class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> Result;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0)
                {
                    Result.push_back({ nums[i], nums[left], nums[right] });
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                }
                else if (sum < 0)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }
        return Result;
    }
};
```

# 2025/3/15 [组合总和](https://leetcode.cn/problems/combination-sum/description/)

给你一个 **无重复元素** 的整数数组 `candidates` 和一个目标整数 `target` ，找出 `candidates` 中可以使数字和为目标数 `target` 的 所有 **不同组合** ，并以列表形式返回。你可以按 **任意顺序** 返回这些组合。

`candidates` 中的 **同一个** 数字可以 **无限制重复被选取** 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 `target` 的不同组合数少于 `150` 个。



这道题<font color='FFD00'>**并不是**</font>类似于背包算法，选择当前背包或者不选择当前背包，这道题中，每个数字的选择的机会都是等同的，所以我们需要去使用一个循环去遍历所有的数，选择是否加入当前结果中。

```c++
for(int i = 0; i < candidates.size(); i++)
{
    currentResult.push_back(candidates[i]);
    DFS();
    currentResult.pop_back();
}
```

```c++
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
class Solution
{
public:
    void DFS(std::vector<int>& candidates, std::vector<int> currentResult, int sum, int index, int target)
    {
        if (sum == target)
        {
            Result.push_back(currentResult);
            return;
        }
        else if (sum > target)
        {
            return;
        }

        for (int i = index; i < candidates.size(); i++)
        {
            currentResult.push_back(candidates[i]);
            DFS(candidates, currentResult, sum + candidates[i], i, target);
            currentResult.pop_back();
        }
    }
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
        std::vector<int> currentResult;
        DFS(candidates, currentResult, 0, 0, target);
        return Result;
    }
    std::vector<std::vector<int>> Result;

};
```

# 2025/3/16 [最接近的三数之和 ](https://leetcode.cn/problems/3sum-closest/description/)



这道题和三数之和的思路是相同的，也是采用三指针来解决。

我们依然要采用先排序的方式来避免出现重复的情况。

在三数之和中，如果`sum == target`，那么我们相当于找到了一组解。

在本题中，可能并不存在`sum == target`的情况，因此我们需要记录当前`sum`与`target`的距离，并更新距离最小的值作为我们最后的结果

```c++
if (minus < minMinus)
{
    result = sum;
    minMinus = minus;
}
```

指针的移动，如果我们是从小到大排序的话，比较当前`sum`和`target`的值即可



```c++
if(sum < target)
{
    // 如果按照从小到大排序的话，应该移动左指针
    left++
}
if(sum > target)
{
    right--;
}
```

```c++
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
class Solution 
{
public:
    int threeSumClosest(std::vector<int>& nums, int target) 
    {
        std::sort(nums.begin(), nums.end());
        int result = 0;
        int minMinus = INT_MAX;
        for (int i = 0; i < nums.size(); i++)
        {
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                int minus = std::abs(target - sum);
                if (minus == 0) return sum;

                if (minus < minMinus)
                {
                    result = sum;
                    minMinus = minus;
                }

                if (sum > target)
                {
                    right--;
                }
                else
                {
                    left++;
                }

            }
        }

        return result;
    }
};
```



# 2025/3/16 [下一个排列](https://leetcode.cn/problems/next-permutation/)

整数数组的一个 **排列** 就是将其所有成员以序列或线性顺序排列。

- 例如，`arr = [1,2,3]` ，以下这些都可以视作 `arr` 的排列：`[1,2,3]`、`[1,3,2]`、`[3,1,2]`、`[2,3,1]` 。

整数数组的 **下一个排列** 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 **下一个排列** 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

- 例如，`arr = [1,2,3]` 的下一个排列是 `[1,3,2]` 。
- 类似地，`arr = [2,3,1]` 的下一个排列是 `[3,1,2]` 。
- 而 `arr = [3,2,1]` 的下一个排列是 `[1,2,3]` ，因为 `[3,2,1]` 不存在一个字典序更大的排列。

给你一个整数数组 `nums` ，找出 `nums` 的下一个排列。

必须**[ 原地 ](https://baike.baidu.com/item/原地算法)**修改，只允许使用额外常数空间。

---

要找到当前排列的下一个排列，我们需要找到比当前排列大的最小排列。为了实现这一点，算法分为以下几个步骤：

**从右向左找到第一个下降点**：

- 从数组的末尾开始，找到第一个满足 `nums[i] < nums[i + 1]` 的位置 `i`。

  ```c++
  for (int i = nums.size() - 2; i >= 0; i--)
  {
      if (nums[i] < nums[i + 1])
      {
          minIndex = i;
          break;
      }
  }
  ```

- 这个位置 `i` 是需要交换的位置，因为 `nums[i]` 是当前排列中最后一个可以增大的元素。

- 如果找不到这样的 `i`，说明整个数组是降序排列的，直接将其反转成升序排列即可。

**从右向左找到第一个大于 `nums[i]` 的元素**：

- 在 `i` 的右侧，从右向左找到第一个大于 `nums[i]` 的元素 `nums[j]`。
- 这个元素 `nums[j]` 是比 `nums[i]` 大的最小元素，交换它们可以使排列变大。

**交换 `nums[i]` 和 `nums[j]`**：

- 交换这两个元素，使得排列变大。

**反转 `i` 右侧的部分**：

- 将 `i` 右侧的部分反转，使其变为升序排列。

- 这样可以保证得到的排列是最小的比当前排列大的排列。

  ```c++
  for (int j = nums.size() - 1; j > minIndex; j--)
  {
      if (nums[j] > nums[minIndex])
      {
          std::swap(nums[minIndex], nums[j]);
          std::reverse(nums.begin() + minIndex + 1, nums.end());
          break;
      }
  }
  ```

为什么这个算法有效？

**找到下降点 `i`**：

- 下降点 `i` 是当前排列中最后一个可以增大的位置。如果 `i` 不存在，说明当前排列已经是最大的排列。
- 通过找到 `i`，我们确定了需要修改的部分。

**找到 `nums[j]`**：

- 在 `i` 的右侧，`nums[j]` 是比 `nums[i]` 大的最小元素。交换 `nums[i]` 和 `nums[j]` 后，排列会变大。

**反转右侧部分**：

- 交换后，`i` 右侧的部分<font color='87CEFA'>**仍然是降序排列**</font>的。通过<font color='87CEFA'>**反转，我们将其变为升序排列**</font>，从而得到最小的比当前排列大的排列。





```c++
#include <vector>
#include <iostream>

class Solution 
{
public:
    void nextPermutation(std::vector<int>& nums) 
    {
        int minIndex = -1;
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            if (nums[i] < nums[i + 1])
            {
                minIndex = i;
                break;
            }
        }
        if (minIndex == -1)
        {
            std::reverse(nums.begin(), nums.end());
            for (int k = 0; k < nums.size(); k++)
            {
                std::cout << nums[k];
                if (k != nums.size() - 1) std::cout << ",";
                else std::cout << std::endl;
            }
            return;
        }

        for (int j = nums.size() - 1; j > minIndex; j--)
        {
            if (nums[j] > nums[minIndex])
            {
                std::swap(nums[minIndex], nums[j]);
                std::reverse(nums.begin() + minIndex + 1, nums.end());
                break;
            }
        }
        for (int k = 0; k < nums.size(); k++)
        {
            std::cout << nums[k];
            if (k != nums.size() - 1) std::cout << " ";
            else std::cout << std::endl;
        }
        return;
    }
};
```



# 2025/3/16 [最大子数组和](https://leetcode.cn/problems/maximum-subarray/)

## **Kadane算法**

Kadane算法用于在O(n)时间复杂度内求解最大子数组和。其核心思想是通过动态规划的思想，逐步计算以每个位置结尾的最大子数组和，并在这个过程中记录全局最大值。

主要采用动态规划的思想，对于每一个元素，有两种方案。

- 当前元素就是最大子数组，说明当前元素的值大于前面的子数组

- 当前元素延续前面的子数组，成为更大的子数组，也就是当前元素的值小于当前元素的值加上前面子数组的和

  ```c++
  if(currentSum + nums[i] > nums[i]) currentSum += nums[i];
  else 
  {
      currentSum = nums[i]; // 新的子数组开始的下标从 i 开始
  }
  ```

- 我们每求出一个新的子数组的和，就需要更新最大子数组的和

  ```c++
  maxSum = std::max(maxSum, currentSum);
  ```

```c++
#include <vector>
class Solution
{
public:
    int maxSubArray(std::vector<int>& nums)
    {
        int currentSum = nums[0];
        int maxSum = currentSum;
        for (int j = 1; j < nums.size(); j++)
        {
            if (currentSum + nums[j] > nums[j])
            {
                currentSum += nums[j];
            }
            else
            {
                currentSum = nums[j];
            }
            maxSum = std::max(maxSum, currentSum);
        }
        return maxSum;
    }
};
```



# 2025/3/17 [合并区间](https://leetcode.cn/problems/merge-intervals/description/)

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

---

首先需要保证我们的区间范围是从小到大的，左区间从小到大，左区间相同比较右侧区间，同样从小到大

```c++
std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& First, const std::vector<int>& Second)
{
        if (First[0] != Second[0])
        {
            return First[0] < Second[0];
        }
        else
        {
            return First[1] < Second[1];
        }
});
```

区间更新：

- 左侧区间不用更新，因为我们就是按照从小到大来进行排列的

- 右侧区间

  - 如果当前右侧区间小于下一个区间的左侧区间，说明两个区间并没有交集，将当前区间的结果存储
  - 如果当前右侧区间大于下一个区间的左侧区间，小于下一个区间的右侧区间，需要更新当前区间的右侧区间
  - 如果当前右侧区间大于下一个区间的右侧区间，那么说明下一个区间为当前区间的子集，不用更新
  - 最后一个区间无论是什么情况，我们都需要将其存储起来。

  ```c++
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
  mergeResult.push_back(TempResult);
  ```

完整代码：

```c++
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
                {
                    return First[0] < Second[0];
                }
                else
                {
                    return First[1] < Second[1];
                }
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
        mergeResult.push_back(TempResult);

        return mergeResult;
    }
};
```



# 2025/3/17 [无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/)

给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长子串** 的长度。

---

可以使用滑动窗口（Sliding Window）算法。滑动窗口是一种在数组中寻找子数组或子串的常用技巧，特别适合处理涉及连续子串的问题。

**初始化**：

- 使用一个哈希集合（`HashSet`）来存储当前窗口中的字符。
- 使用两个指针 `left` 和 `right` 来表示窗口的左右边界，初始时都指向字符串的开头。
- 用一个变量 `max_length` 来记录最长子串的长度。

**滑动窗口**：

- 移动右指针 `right`，将字符逐个加入哈希集合。

- 如果遇到重复字符（即字符已经在哈希集合中），则移动左指针 `left`，并从哈希集合中移除左指针指向的字符，直到重复字符被移除。

- 在每次移动右指针后，更新 `max_length` 为当前窗口长度和 `max_length` 中的较大值。

  ```c++
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
  ```

关于`Set`的使用

- **`set`**：
  - 元素是**有序的**，默认按升序排列。
  - 支持按顺序遍历元素。
- **`unordered_set`**：
  - 元素是**无序的**，存储顺序不可预测。
  - 遍历顺序与插入顺序无关。

```c++
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
            // 处理重复字母
            while (charSet.find(s[right]) != charSet.end())
            {
                charSet.erase(s[left]);
                left++;
            }
            // 加入当前字母
            charSet.insert(s[right]);
            
            // 更新最大字串长度
            maxLength = std::max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};
```



# 2025/3/17 [ 最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/description/)

给你一个字符串 `s`，找到 `s` 中最长的 回文 子串。

---

处理回文子串，我们需要使用中心扩展法，因为回文子串的长度可能是奇数也可能是偶数，因此，我们只需要遍历字符串中的每一个字符，让其向两边扩展即可找到以该字符为中心的最长回文子串。

- 奇数长度：以某个字符为中心，向左右扩展。
- 偶数长度：以两个字符为中心，向左右扩展。

返回子串

```c++
s.substr(startLocation, length);
```



```c++
int findPalindrome(const std::string& s, int left, int right)
{
    while (left >= 0 && right <= s.size() - 1 && s[left] == s[right])
    {
        left--;
        right++;
    }
    return right - left - 1; // 注意这里是 -1，正常的长度为 right - left + 1，但是我们这里的结束条件是找到回文子串后还需要移动一次指针，也就是right - left + 1 - 2;
}
```

完整代码：

```c++
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
```



# 2025/3/17 [在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/)

给你一个按照非递减顺序排列的整数数组 `nums`，和一个目标值 `target`。请你找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 `target`，返回 `[-1, -1]`。

你必须设计并实现时间复杂度为 `O(log n)` 的算法解决此问题。

---

只需要使用二分法找到`target`对应的值之后，向两边扩展即可，不过这种办法并不能完全实现`O(log n)`，比如全是`target`的情况

```c++
#include <vector>
#include <iostream>

class Solution 
{
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) 
    {
        if (nums.size() == 0) return { -1, -1 };

        int left = 0;
        int right = nums.size() - 1;
        int mid = left + (right - left) / 2;
        while (left <= right && nums[mid] != target)
        {
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
            mid = left + (right - left) / 2;
        }

        if (right < left || nums[mid] != target)
        {
            return { -1, -1 };
        }
        
        if (nums[mid] == target)
        {
            left = right = mid;
            while (left - 1 >= 0 && nums[left - 1] == target) left--; // 这里需要先判断索引，再判断数组，不然就是overflow
            while (right + 1 < nums.size() && nums[right + 1] == target) right++;
        }

        return { left, right };
    }
};
```

# 2025/3/17 [子集](https://leetcode.cn/problems/subsets/description/)

给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。你可以按 **任意顺序** 返回解集。

---

可以采用回溯法，遍历整个数组，每个数字都有选或者不选两种选择。



```c++
void backtrack(std::vector<int> nums, int start, std::vector<int> path, std::vector<std::vector<int>>& Result)
{
    Result.push_back(path); // 每一个路径都需要存储

    for (int i = start; i < nums.size(); i++)
    {
        // 选择当前元素
        path.push_back(nums[i]);
        backtrack(nums, i + 1, path, Result);
        
        // 不选择当前元素
        path.pop_back();
    }
}
```

完整代码：

```c++
#include <vector>

class Solution 
{
public:
    void backtrack(std::vector<int> nums, int start, std::vector<int> path, std::vector<std::vector<int>>& Result)
    {
        Result.push_back(path);

        for (int i = start; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, Result);
            path.pop_back();
        }

    }
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> Result;
        backtrack(nums, 0, {}, Result);
        return Result;
    }
};
```

# 2025/3/17 [颜色分类](https://leetcode.cn/problems/sort-colors/description/)

给定一个包含红色、白色和蓝色、共 `n` 个元素的数组 `nums` ，**[原地](https://baike.baidu.com/item/原地算法)** 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

我们使用整数 `0`、 `1` 和 `2` 分别表示红色、白色和蓝色。

必须在不使用库内置的 sort 函数的情况下解决这个问题。

---

这个问题是经典的<font color='87CEFA'>**荷兰国旗问题（Dutch National Flag Problem）**</font>，我们可以使用三个指针来将数组分为三个部分：红色（0）、白色（1）和蓝色（2）。

1. **指针定义**：
   - `low` 指针指向红色区域的末尾，初始值为0。
   - `right` 指针指向蓝色区域的开头，初始值为数组的最后一个元素。
   - `mid` 指针用于遍历数组，初始值为0。
2. **遍历过程**：
   - 如果 `nums[mid] == 0`，表示当前元素是红色，将其与 `low` 指针指向的元素交换，并将 `low` 和 `mid` 指针都向右移动。
   - 如果 `nums[mid] == 1`，表示当前元素是白色，直接跳过，`mid` 指针向右移动。
   - 如果 `nums[mid] == 2`，表示当前元素是蓝色，将其与 `right` 指针指向的元素交换，并将 `right` 指针向左移动。
3. **终止条件**：
   - 当 `mid` 指针超过 `right` 指针时，遍历结束，数组已经按照红色、白色、蓝色的顺序排列。

```c++
#include <vector>
class Solution 
{
public:
    void sortColors(std::vector<int>& nums)
    {
        int left = 0;
        int mid = 0;
        int right = nums.size() - 1;
        while (mid <= right)
        {
            if (nums[mid] == 1) mid++;
            else if (nums[mid] == 0)
            {
                std::swap(nums[mid], nums[left]);
                left++;
                mid++;
            }
            else if (nums[mid] == 2)
            {
                std::swap(nums[mid], nums[right]);
                right--;
            }
        }
    }
};
```











































































































