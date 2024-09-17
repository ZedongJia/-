#include <cstring>
#include <iostream>

int n;
int dis[51];
int w[51];

int cost[51][51][2];

int main()
{
    int c = 0;
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &dis[i], &w[i]);
    for (int i = 2; i <= n; i++)
        w[i] += w[i - 1];
    for (int i = 0; i <= 50; i++)
        for (int j = 0; j <= 50; j++)
            cost[i][j][0] = cost[i][j][1] = INT32_MAX / 2;
    cost[c][c][0] = cost[c][c][1] = 0;
    for (int l = 2; l <= n; l++)
    {
        int s = c - l + 1;
        while (s < 1)
            s++;
        int e = s + l - 1;
        while (s <= c && e <= n)
        {
            cost[s][e][0] = std::min(cost[s + 1][e][0] + (dis[s + 1] - dis[s]) * (w[n] - w[e] + w[s]),
                                     cost[s + 1][e][1] + (dis[e] - dis[s]) * (w[n] - w[e] + w[s]));
            cost[s][e][1] = std::min(cost[s][e - 1][0] + (dis[e] - dis[s]) * (w[n] - w[e - 1] + w[s - 1]),
                                     cost[s][e - 1][1] + (dis[e] - dis[e - 1]) * (w[n] - w[e - 1] + w[s - 1]));
            s++;
            e = s + l - 1;
        }
    }
    printf("%d", std::min(cost[1][n][0], cost[1][n][1]));
}