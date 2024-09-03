#include <iostream>
int m[121][121];
int prefix[121][121]{};

int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            std::cin >> m[i][j];
            prefix[i][j] = prefix[i][j - 1] + m[i][j];
        }
    int ans = 0;
    for (int ci = 0; ci < n; ci++)
        for (int cj = ci + 1; cj <= n; cj++)
            for (int ri = 0; ri < n; ri++)
            {
                int _ans = 0;
                for (int rj = ri + 1; rj <= n; rj++)
                {
                    _ans += prefix[rj][cj] - prefix[rj][ci];
                    ans = std::max(_ans, ans);
                }
            }
    printf("%d", ans);
}