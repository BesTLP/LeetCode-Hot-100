#include <vector>
#include <iostream>
class Solution 
{
public:
 /*   int maxProfit(std::vector<int>& prices) 
    {
        int maxProfit = 0;
        for (int i = 0; i < prices.size(); i++)
        {
            if (prices[i + 1] <= prices[i])
            {
                continue;
            }
            for (int j = prices.size() - 1; j > i; j--)
            {
                if (prices[j - 1] >= prices[j])
                {
                    continue;
                }
                if (prices[j] > prices[i])
                {
                    maxProfit = std::max(maxProfit, prices[j] - prices[i]);
                }
            }
        }
        return maxProfit;
    }*/

    //int maxProfit(std::vector<int>& prices)
    //{
    //    const int n = prices.size();
    //    std::vector<int> minPrices(n, INT_MAX);
    //    std::vector<int> maxPrices(n, INT_MIN);
    //    
    //    minPrices[0] = prices[0];
    //    maxPrices[n - 1] = prices[n - 1];
    //    for (int i = 1; i < n; i++)
    //    {
    //        minPrices[i] = std::min(minPrices[i - 1], prices[i]);
    //    }
    //    for (int i = n - 2; i >= 0; i--)
    //    {
    //        maxPrices[i] = std::max(maxPrices[i + 1], prices[i]);
    //    }

    //    int maxProfit = 0;
    //    for (int i = 0; i < n; i++)
    //    {
    //        maxProfit = std::max(maxProfit, maxPrices[i] - minPrices[i]);
    //    }

    //    return maxProfit;
    //}

    int maxProfit(std::vector<int>& prices)
    {
        int minPrice = prices[0];
        int maxProfit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] > minPrice)
            {
                maxProfit = std::max(maxProfit, prices[i] - minPrice);
            }
            else if (prices[i] < minPrice)
            {
                minPrice = prices[i];
            }
        }
        return maxProfit;
    }
};
