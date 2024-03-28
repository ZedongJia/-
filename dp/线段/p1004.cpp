#include <iostream>
int map[10][10]{};
int dp[10][10][10][10]{};
int main()
{
    int n;
    std::cin >> n;
    while (true)
    {
        int r, c, v;
        std::cin >> r >> c >> v;
        if (r == 0 && c == 0 && v == 0)
            break;
        map[r][c] = v;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                for (int l = 1; l <= n; l++)
                {
                    dp[i][j][k][l] = std::max(
                        std::max(
                            dp[i - 1][j][k - 1][l],
                            dp[i][j - 1][k][l - 1]
                        ),
                        std::max(
                            dp[i - 1][j][k][l - 1],
                            dp[i][j - 1][k - 1][l]
                        )
                    ) + map[i][j];
                    if (i != k && j != l)
                        dp[i][j][k][l] += map[k][l];
                }
    printf("%d", dp[n][n][n][n]);
}