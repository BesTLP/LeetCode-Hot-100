#include <vector>

// 基础方法
class Solution
{
public:
	std::vector<int> countBits(int n)
	{
		std::vector<int> ret;
		for (int i = 0; i <= n; i++)
		{
			ret.push_back(countBit(i));
		}
		return ret;
	}
private:
	int countBit(int value)
	{
		int cnt = 0;
		while (value)
		{
			cnt += value & 1;
			value >>= 1;
		}
		return cnt;
	}
};


class Solution
{
public:
	std::vector<int> countBits(int n)
	{
		std::vector<int> ret(n + 1, 0);
		if (n == 0) return ret;

		for (int i = 1; i <= n; i++)
		{
			if (i % 2 == 0)
			{
				// 偶数
				ret[i] = ret[i >> 1];
			}
			else
			{
				ret[i] = ret[i >> 1] + 1;
			}
		}
		return ret;
	}
};

int main()
{
	Solution solution;
	solution.countBits(5);
}