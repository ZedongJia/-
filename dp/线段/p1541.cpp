#include <iostream>
int arr[400];
int dp[41][41][41][41]{};
int main()
{
    int n, m;
    int t[5]{};
    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    for (int i = 0; i < m; i++)
    {
        int tmp;
        std::cin >> tmp;
        t[tmp]++;
    }
    for (int i = 0; i <= t[1]; i++)
        for (int j = 0; j <= t[2]; j++)
            for (int k = 0; k <= t[3]; k++)
                for (int l = 0; l <= t[4]; l++)
                {
                    dp[i][j][k][l] =
                        std::max(std::max(i != 0 ? dp[i - 1][j][k][l] : 0, j != 0 ? dp[i][j - 1][k][l] : 0),
                                 std::max(k != 0 ? dp[i][j][k - 1][l] : 0, l != 0 ? dp[i][j][k][l - 1] : 0)) +
                        arr[i + j * 2 + k * 3 + l * 4];
                }
    printf("%d", dp[t[1]][t[2]][t[3]][t[4]]);
}