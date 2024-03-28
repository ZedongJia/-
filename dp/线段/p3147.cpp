#include <iostream>
/**
    线段DP
    range(low, high)
    dp[i][j] = dp[i - 1][dp[i - 1][j]]
*/
int dp[100][270000]{};

int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int num;
        std::cin >> num;
        dp[num][i] = i + 1;
    }
    int ans = 0;
    for (int i = 2; i < 100; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (!dp[i][j])
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            if (dp[i][j])
            {
                ans = i;
            }
        }
    }
    printf("%d", ans);
}