/*
 * @lc app=leetcode.cn id=30 lang=cpp
 *
 * [30] 串联所有单词的子串
 */
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution
{
  public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        vector<int> ans;
        int wordLen = words[0].length();
        int requiredLen = words.size() * wordLen;
        for (int i = 0; i < wordLen && i < s.length() - requiredLen + 1; i++)
        {
            map<string, int> hash;
            for (string &word : words)
            {
                hash[word]++;
            }
            for (int j = 0; j < words.size(); j++)
            {
                string substr = s.substr(i + j * wordLen, wordLen);
                hash[substr]--;
                if (hash[substr] == 0)
                {
                    hash.erase(substr);
                }
            }
            if (hash.empty())
            {
                ans.push_back(i);
            }
            for (int j = i + wordLen; j <= s.length() - requiredLen; j += wordLen)
            {
                string del = s.substr(j - wordLen, wordLen);
                string add = s.substr(j + requiredLen - wordLen, wordLen);
                hash[del]++;
                hash[add]--;
                if (hash[del] == 0)
                    hash.erase(del);
                if (hash[add] == 0)
                    hash.erase(add);
                if (hash.empty())
                {
                    ans.push_back(j);
                }
            }
        }
        vector<int> nans(ans.begin(), ans.end());
        return nans;
    }
};
// @lc code=end
/**
"barfoofoobarthefoobarman"
["bar","foo","the"]
*/