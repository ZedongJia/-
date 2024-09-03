#include <cstring>
#include <iostream>
#include <limits.h>
#include <queue>

#define N 201
#define E 10006
typedef struct Edge
{
    int v;
    long long cap;
    int next;
} Edge;
int totalEdge = 2;
Edge edges[E];
int head[N];
int curr[N];
int depth[N];

int n, m, s, t;

void addEdge(int u, int v, int cap)
{
    edges[totalEdge] = {v, cap, head[u]};
    head[u] = totalEdge;
    totalEdge++;
}

bool bfs()
{
    memset(depth, 0, sizeof(depth));
    std::queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edges[i].next)
        {
            int v = edges[i].v;
            if (!depth[v] && edges[i].cap)
            {
                depth[v] = depth[u] + 1;
                q.push(v);
                if (t == v)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

long long dfs(int u, long long totalCap)
{
    if (u == t)
        return totalCap;
    long long currCap = 0;
    for (int i = curr[u]; i && totalCap > 0; i = edges[i].next)
    {
        curr[u] = i;
        int v = edges[i].v;
        if ((depth[v] == depth[u] + 1) && edges[i].cap)
        {
            long long maxCap = dfs(v, std::min(totalCap, edges[i].cap));
            if (!maxCap)
            {
                depth[v] = 0;
            }
            else
            {
                totalCap -= maxCap;
                currCap += maxCap;
                edges[i].cap -= maxCap;
                edges[i ^ 1].cap += maxCap;
            }
        }
    }
    return currCap;
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &s, &t);
    memset(head, 0, sizeof(head));
    for (int i = 0; i < m; i++)
    {
        int u, v, cap;
        scanf("%d %d %d", &u, &v, &cap);
        addEdge(u, v, cap);
        addEdge(v, u, 0);
    }
    long long maxCap = 0;
    while (bfs())
    {
        memcpy(curr, head, sizeof(head));
        maxCap += dfs(s, LONG_LONG_MAX);
    }
    printf("%lld", maxCap);
}