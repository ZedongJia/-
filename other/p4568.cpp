#include <iostream>
#include <queue>
#include <vector>
#define N 300001
#define E 3000001
typedef struct Edge
{
    int u;
    int v;
    int c;
    int next;
} Edge;

int totalEdge = 1;
int startEdge[N];
Edge edges[E << 1];

void addEdge(int u, int v, int c)
{
    edges[totalEdge] = {u, v, c, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}

int n, m, k;
int s, t;
int dis[N];
int visited[N];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= (k + 1) * n; i++)
    {
        startEdge[i] = 0;
        dis[i] = INT32_MAX;
        visited[i] = 0;
    }
    scanf("%d%d", &s, &t);
    s++, t++;
    for (int i = 1; i <= m; i++)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        u++, v++;
        addEdge(u, v, c);
        addEdge(v, u, c);
        for (int j = 1; j <= k; j++)
        {
            addEdge(u + (j - 1) * n, v + j * n, 0);
            addEdge(v + (j - 1) * n, u + j * n, 0);
            addEdge(u + j * n, v + j * n, c);
            addEdge(v + j * n, u + j * n, c);
        }
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> tmp;
    dis[s] = 0;
    tmp.push({0, s});
    while (!tmp.empty())
    {
        int u = tmp.top().second;
        tmp.pop();
        if (visited[u])
            continue;
        visited[u] = 1;
        for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            int v = edges[edgeIndex].v;
            if (dis[v] > dis[u] + edges[edgeIndex].c)
            {
                dis[v] = dis[u] + edges[edgeIndex].c;
                tmp.push({dis[v], v});
            }
        }
    }
    int ans = INT32_MAX;
    for (int i = 0; i <= k; i++)
        ans = std::min(ans, dis[t + n * i]);
    printf("%d", ans);
}