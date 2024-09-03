#include <iostream>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution
{
  public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(amount + 1, 10001);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++)
            for (int j = 0; j <= amount; j++)
                if (j - coins[i] >= 0)
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
        return dp[amount] == 10001 ? -1 : dp[amount];
    }
};
// @lc code=end
int main()
{
    Solution s;
    vector<int> v({2, 2, 5});
    s.coinChange(v, 1);
}