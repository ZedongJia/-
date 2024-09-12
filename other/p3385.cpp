#include <cstring>
#include <iostream>
#include <queue>

#define N 2001
#define E 3001
typedef struct Edge
{
    int u;
    int v;
    int w;
    int next;
} Edge;

Edge edges[E << 1];
int startEdge[N];
int totalEdge = 1;
void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        startEdge[i] = 0;
    }
    totalEdge = 1;
}

void addEdge(int u, int v, int w)
{
    edges[totalEdge] = {u, v, w, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}

bool spfa(int n)
{
    int visit[N];
    int dis[N];
    int count[N];
    for (int i = 1; i <= n; i++)
    {
        visit[i] = 0;
        dis[i] = INT32_MAX;
        count[i] = 0;
    }
    std::queue<int> tmp;
    visit[1] = 1;
    dis[1] = 0;
    tmp.push(1);
    while (!tmp.empty())
    {
        int u = tmp.front();
        tmp.pop();
        visit[u] = 0;
        for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            Edge &edge = edges[edgeIndex];
            if (dis[edge.u] == INT32_MAX)
                continue;
            if (dis[edge.v] > dis[edge.u] + edge.w)
            {
                dis[edge.v] = dis[edge.u] + edge.w;
                count[edge.v] = count[edge.u] + 1;
                if (count[edge.v] >= n)
                    return 1;
                if (!visit[edge.v])
                {
                    visit[edge.v] = 1;
                    tmp.push(edge.v);
                }
            }
        }
    }
    return 0;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        init(n);
        for (int i = 1; i <= m; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
            if (w >= 0)
                addEdge(v, u, w);
        }
        if (spfa(n))
            printf("YES\n");
        else
            printf("NO\n");
    }
}