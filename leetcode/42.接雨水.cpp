/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;
// @lc code=start
class Solution
{
  public:
    int trap(vector<int> &height)
    {
        int sum = 0;
        stack<int> sk;
        for (int i = 0; i < height.size(); i++)
        {
            if (sk.empty() || height[sk.top()] >= height[i])
            {
                sk.push(i);
            }
            else
            {
                while (sk.size() != 1 && height[sk.top()] <= height[i])
                {
                    int mid = height[sk.top()];
                    sk.pop();
                    sum += (i - sk.top() - 1) * (min(height[i], height[sk.top()]) - mid);
                }
                while (!sk.empty() && height[sk.top()] <= height[i])
                {
                    sk.pop();
                }
                sk.push(i);
            }
        }
        return sum;
    }
};
// @lc code=end
// [4,2,0,3,2,5],9