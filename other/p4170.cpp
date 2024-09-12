#include <iostream>
#include <string>
int dp[50][50];
int main()
{
    std::string str;
    std::cin >> str;
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++)
            dp[i][j] = i == j ? 1 : 0;
    for (int l = 2; l <= str.length(); l++)
    {
        int sl = 0, sr = sl + l - 1;
        while (sr < str.length())
        {
            int cost = INT32_MAX;
            if (str[sl] == str[sr])
            {
                cost = std::min(dp[sl + 1][sr], dp[sl][sr - 1]);
            }
            else
            {
                for (int itv = sl; itv < sr; itv++)
                {
                    cost = std::min(cost, dp[sl][itv] + dp[itv + 1][sr]);
                }
            }
            dp[sl][sr] = cost;
            sl++, sr++;
        }
    }
    printf("%d", dp[0][str.length() - 1]);
}