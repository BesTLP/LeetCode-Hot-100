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

