#include <iostream>
#include <map>

typedef struct Edge
{
    int u;
    int v;
    int w;
    int next;
} Edge;
int startEdge[52];
Edge edges[505];
int totalEdge = 1;
void addEdge(int u, int v, int w)
{
    edges[totalEdge] = {u, v, w, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}

int vals[52];
std::map<int, std::pair<int, int>> specialDayVal;
int n, m, T;
std::map<int, std::map<int, int>> dp;

int main()
{
    int k;
    scanf("%d%d%d%d", &n, &m, &T, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &vals[i]);
        startEdge[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    for (int i = 0; i < k; i++)
    {
        int d, u, val;
        scanf("%d%d%d", &d, &u, &val);
        specialDayVal[d] = {u, val};
    }
    dp[0][1] = vals[1];
    for (int i = 0; i < T; i++)
    {
        if (dp.find(i) == dp.end())
            continue;
        for (int u = 1; u <= n; u++)
        {
            if (dp[i].find(u) == dp[i].end())
                continue;
            for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
            {
                int d = i + edges[edgeIndex].w;
                if (d > T)
                    continue;
                int v = edges[edgeIndex].v;
                int addi = specialDayVal.find(d) != specialDayVal.end() && specialDayVal[d].first == v
                               ? specialDayVal[d].second
                               : 0;
                dp[d][v] = std::max(dp[d][v], dp[i][u] + vals[v] + addi);
            }
        }
    }
    if (dp.find(T) == dp.end() || dp[T].find(1) == dp[T].end())
        printf("-1");
    else
        printf("%d", dp[T][1]);
}