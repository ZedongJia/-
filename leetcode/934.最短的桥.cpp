/*
 * @lc app=leetcode.cn id=934 lang=cpp
 *
 * [934] 最短的桥
 */
#include <queue>
#include <vector>

using namespace std;

// @lc code=start
class Solution
{
  public:
    int shortestBridge(vector<vector<int>> &grid)
    {
        vector<vector<int>> v(grid.size(), vector(grid[0].size(), 0));
        vector<vector<int>> dir{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        int si = 0;
        int sj = 0;
        bool find = false;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == 1)
                {
                    si = i;
                    sj = j;
                    find = true;
                    break;
                }
            if (find)
            {
                break;
            }
        }
        int dis = 0;
        queue<vector<int>> q1;
        queue<vector<int>> q2;
        q1.push({si, sj});
        v[si][sj] = -1;
        while (!q1.empty())
        {
            vector<int> tmp = q1.front();
            int i = tmp[0];
            int j = tmp[1];
            q1.pop();
            for (int d = 0; d < dir.size(); d++)
            {
                int ni = i + dir[d][0];
                int nj = j + dir[d][1];
                if (ni < 0 || ni >= grid.size())
                    continue;
                if (nj < 0 || nj >= grid[0].size())
                    continue;
                if (v[ni][nj] == -1)
                    continue;
                v[ni][nj] = -1;
                if (grid[ni][nj] == 0)
                {
                    q2.push({ni, nj, 1});
                }
                else
                {
                    q1.push({ni, nj});
                }
            }
        }
        while (!q2.empty())
        {
            vector<int> tmp = q2.front();
            int i = tmp[0];
            int j = tmp[1];
            int depth = tmp[2];
            q2.pop();
            for (int d = 0; d < dir.size(); d++)
            {
                int ni = i + dir[d][0];
                int nj = j + dir[d][1];
                if (ni < 0 || ni >= grid.size())
                    continue;
                if (nj < 0 || nj >= grid[0].size())
                    continue;
                if (v[ni][nj] == -1)
                    continue;
                v[ni][nj] = -1;
                if (grid[ni][nj] == 0)
                {
                    q2.push({ni, nj, depth + 1});
                }
                else
                {
                    dis = depth;
                    return dis;
                }
            }
        }
        return dis;
    }
};
// @lc code=end

/**
[
      0,1,2,3,4,5,6
    0[0,0,0,1,1,0,0],
    1[0,0,0,1,0,0,0],
    2[0,0,0,1,0,0,0],
    3[0,0,0,0,0,0,0],
    4[0,0,0,0,0,0,0],
    5[0,1,0,0,0,0,0],
    6[0,1,1,0,0,0,0]
]
[[0,0,0,1,1,0,0],[0,0,0,1,0,0,0],[0,0,0,1,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,0,0],[0,1,0,0,0,0,0],[0,1,1,0,0,0,0]]

*/