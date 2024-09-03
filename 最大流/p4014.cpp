#include <cstring>
#include <iostream>
#include <queue>
int n, s, t;
typedef struct Edge
{
    int u;
    int v;
    int next;
    int cap;
    int cost;
} Edge;
Edge edges[10000];
Edge tmp[10000];

int head[102];
int visit[102];
int costs[102];
int prevEdge[102];
int totalEdge = 2;
void addEdge(int u, int v, int cap, int cost)
{
    edges[totalEdge] = {u, v, head[u], cap, cost};
    head[u] = totalEdge;
    totalEdge++;
}
bool spfa(bool small = true)
{
    memset(visit, 0, sizeof(visit));
    int invalid = 102;
    for (int i = 0; i < 102; i++)
    {
        costs[i] = invalid;
    }
    memset(prevEdge, 0, sizeof(prevEdge));
    std::queue<int> q;
    q.push(s);
    costs[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        visit[u] = 0;
        for (int i = head[u]; i; i = edges[i].next)
        {
            int v = edges[i].v;
            if (edges[i].cap && ((costs[v] == invalid) ||
                                 (small ? costs[v] > costs[u] + edges[i].cost : costs[v] < costs[u] + edges[i].cost)))
            {
                costs[v] = costs[u] + edges[i].cost;
                prevEdge[v] = i;
                if (!visit[v])
                {
                    q.push(v);
                    visit[v] = 1;
                }
            }
        }
    }
    return costs[t] != invalid;
}

int dfs(bool small = true)
{
    memcpy(edges, tmp, sizeof(tmp));
    int totalCost = 0;
    while (spfa(small))
    {
        int minCap = INT32_MAX;
        for (int i = prevEdge[t]; i; i = prevEdge[edges[i].u])
        {
            minCap = std::min(minCap, edges[i].cap);
        }
        for (int i = prevEdge[t]; i; i = prevEdge[edges[i].u])
        {
            edges[i].cap -= minCap;
            edges[i ^ 1].cap += minCap;
        }
        totalCost += costs[t];
    }
    return totalCost;
}

int main()
{
    scanf("%d", &n);
    s = 0;
    t = 2 * n + 1;
    for (int i = 1; i <= n; i++)
    {
        addEdge(s, i, 1, 0);
        addEdge(i, s, 0, 0);
        for (int j = 1; j <= n; j++)
        {
            int cost;
            scanf("%d", &cost);
            addEdge(i, n + j, 1, cost);
            addEdge(n + j, i, 0, -cost);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        addEdge(n + i, t, 1, 0);
        addEdge(t, n + i, 0, 0);
    }
    memcpy(tmp, edges, sizeof(edges));
    printf("%d\n", dfs());
    printf("%d", dfs(false));
}