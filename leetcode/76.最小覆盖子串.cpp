/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */
#include <string>
#include <map>
using namespace std;
// @lc code=start
class Solution {
public:
    bool allIn(string &t, map<char, int> have)
    {
        for (char &ch : t)
        {
            have[ch]--;
            if (have[ch] < 0)
                return false;
        }
        return true;
    }
    string minWindow(string s, string t) {
        int minLen = INT32_MAX;
        int minPl = 0;
        map<char, int> have;
        int pl = 0, pr = 0;
        while (pl < s.length() && pr < s.length())
        {
            if (allIn(t, have))
            {
                if (minLen > pr - pl + 1)
                {
                    minLen = pr - pl + 1;
                    minPl = pl;
                }
                // left bound
                have[s[pl]]--;
                pl++;
            } else
            {
                have[s[pr]]++;
                // right bound
                pr++;
            }
        }
        while (pl < s.length() && allIn(t, have))
        {
            if (minLen > pr - pl + 1)
            {
                minLen = pr - pl + 1;
                minPl = pl;
            }
            // left bound
            have[s[pl]]--;
            pl++;   
        }
        if (minLen == INT32_MAX)
            return "";
        else
            return s.substr(minPl, minLen);
    }
};
// @lc code=end

