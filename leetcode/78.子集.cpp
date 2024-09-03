/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> set;
        for (int i = 0; i < nums.size(); i++)
        {
            int len = set.size();
            for (int j = 0; j < len; j++)
            {
                vector<int> tmp = set[j];
                tmp.push_back(nums[i]);
                set.push_back(tmp);
            }
            set.push_back({nums[i]});
        }
        set.push_back({});
        return set;
    }
};
// @lc code=end
