#include <algorithm>
#include <iostream>
#define N 20000
typedef struct Edge
{
    int u;
    int v;
    int next = 0;
} Edge;
Edge edges[N<<1];
int edgeCount = 1;
int vals[N];
int edgeIndexs[N];
int n;
void addEdge(int u, int v)
{
    edges[edgeCount] = {u, v, edgeIndexs[u]};
    edgeIndexs[u] = edgeCount;
    edgeCount++;
    edges[edgeCount] = {v, u, edgeIndexs[v]};
    edgeIndexs[v] = edgeCount;
    edgeCount++;
}

int conn[N];

void dfs(int parent, int u)
{
    conn[u] += vals[u];
    for (int edgeIndex = edgeIndexs[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
    {
        int v = edges[edgeIndex].v;
        if (v != parent)
        {
            dfs(u, v);
            if (conn[v] > 0)
            {
                conn[u] += conn[v];
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &vals[i]);
        edgeIndexs[i] = 0;
        conn[n] = 0;
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }
    dfs(0, 1);
    printf("%d", *std::max_element(conn + 1, conn + n));
}