/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */
#include <string>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        int ans = 0;
        int pl = 0;
        while (pl < s.length())
        {
            int cnt[255]{};
            int pr = pl;
            while (pr < s.length() && cnt[s[pr]] == 0)
            {
                cnt[s[pr]] = 1;
                pr++;
            }
            ans = max(ans, pr - pl);
            pl++;
        }
        return ans;
    }
};
// @lc code=end
