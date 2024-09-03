/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution
{
  public:
    int maxProfit(int k, vector<int> &prices)
    {
        vector<int> buy(k + 1, -INT32_MAX);
        vector<int> sell(k + 1, 0);
        for (int i = 0; i < prices.size(); i++)
        {
            for (int j = 1; j <= k; j++)
            {
                buy[j] = max(buy[j], sell[j - 1] - prices[i]);
                sell[j] = max(sell[j], buy[j] + prices[i]);
            }
        }
        int maxVal = 0;
        for (int i = 1; i <= k; i++)
            maxVal = max(maxVal, sell[i]);
        return maxVal;
    }
};
// @lc code=end
