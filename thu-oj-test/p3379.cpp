#include <iostream>
#define N 500001
typedef struct Edge
{
    int u;
    int v;
    int next;
} Edge;
Edge edges[N << 1];
int startEdge[N];
int totalEdge = 1;
int n, m, root;
void addEdge(int u, int v)
{
    edges[totalEdge] = {u, v, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}
int lg[N];
int depth[N];
int fa[N][22];

void dfs(int f, int u)
{
    fa[u][0] = f;
    depth[u] = depth[f] + 1;
    for (int i = 1; i <= lg[depth[u]]; i++)
    {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
    {
        int v = edges[edgeIndex].v;
        if (v != f)
            dfs(u, v);
    }
}

int LCA(int x, int y)
{
    if (depth[x] < depth[y])
        std::swap(x, y);
    while (depth[x] > depth[y])
    {
        x = fa[x][lg[depth[x] - depth[y]] - 1];
    }
    if (x == y)
        return x;
    for (int k = lg[depth[x]] - 1; k >= 0; --k)
        if (fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}

int main()
{
    scanf("%d%d%d", &n, &m, &root);
    for (int i = 1; i <= n; i++)
    {
        depth[i] = 0;
        startEdge[i] = 0;
    }
    lg[0] = 0;
    for (int i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(root, root);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", LCA(x, y));
    }
}