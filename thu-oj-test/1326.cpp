#include <algorithm>
#include <cstring>
#include <iostream>

#define p2(x) (x) * (x)

int heightOf[501];
int dp[501][501];
int n, k;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &heightOf[i]);
    std::sort(heightOf + 1, heightOf + n + 1);
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++)
        dp[i][1] = p2(heightOf[i] - heightOf[1]);
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= i && j <= k; j++)
        {
            int ans = INT32_MAX;
            int it = j;
            while (it <= i)
            {
                ans = std::min(ans, dp[it - 1][j - 1] + p2(heightOf[i] - heightOf[it]));
                it++;
            }
            dp[i][j] = ans;
        }
    }
    printf("%d", dp[n][k]);
}