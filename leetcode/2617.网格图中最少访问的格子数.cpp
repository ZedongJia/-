#include <iostream>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=2617 lang=cpp
 *
 * [2617] 网格图中最少访问的格子数
 */

// @lc code=start
class Solution
{
  public:
    int minimumVisitedCells(vector<vector<int>> &grid)
    {
        int row_n = grid.size();
        int col_n = grid[0].size();
        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size()));
        for (int i = row_n - 1; i >= 0; i--)
            for (int j = col_n - 1; j >= 0; j--)
                dp[i][j] = INT32_MAX - 1;
        dp[row_n - 1][col_n - 1] = 1;
        for (int i = row_n - 1; i >= 0; i--)
            for (int j = col_n - 1; j >= 0; j--)
            {
                // dp[i][j] = dp[i][k] + 1 | dp[k][j] + 1 two way
                for (int k = 1 + i; k < row_n && k <= grid[i][j] + i; k++)
                    dp[i][j] = min(dp[i][j], dp[k][j] + 1);
                for (int k = 1 + j; k < col_n && k <= grid[i][j] + j; k++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + 1);
            }
        // for (int i = 0; i < row_n; i++)
        // {
        //     for (int j = 0; j < col_n; j++)
        //         printf("%d(%d) ", dp[i][j], grid[i][j]);
        //     printf("\n");
        // }
        return dp[0][0] == INT32_MAX - 1 ? -1 : dp[0][0];
    }
};
// @lc code=end
