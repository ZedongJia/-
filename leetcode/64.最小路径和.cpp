/*
 * @lc app=leetcode.cn id=64 lang=cpp
 *
 * [64] 最小路径和
 */
#include <vector>
#include <iostream>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int minPathSum(vector<vector<int>> &grid)
    {
        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 30000));
        dp[0][0] = grid[0][0];
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (i + 1 < grid.size())
                    dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + grid[i + 1][j]);
                if (j + 1 < grid[0].size())
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + grid[i][j + 1]);
                printf("%d,%d,%d\n", i, j, dp[i][j]);
            }
        return dp[grid.size() - 1][grid[0].size() - 1];
    }
};
// @lc code=end
