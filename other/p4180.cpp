#include <algorithm>
#include <iostream>
#include <limits.h>
#define N 100001
#define E 300001
#define T 17
typedef struct InputEdge
{
    int u;
    int v;
    int w;
} InputEdge;
typedef struct Edge
{
    int u;
    int v;
    int w;
    int next;
} Edge;
InputEdge inputEdges[E];
bool visited[E];
Edge edges[E << 1];
int startEdge[N];
int totalEdge = 1;
void addEdge(int u, int v, int w)
{
    edges[totalEdge] = {u, v, w, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}

bool cmp(const InputEdge &e1, const InputEdge &e2)
{
    return e1.w < e2.w;
}

int pa[N];
int find(int u)
{
    return u == pa[u] ? u : pa[u] = find(pa[u]);
}

int n, m;
long long kruskal()
{
    long long sum = 0;
    std::sort(inputEdges + 1, inputEdges + 1 + m, cmp);
    int count = 1;
    for (int i = 1; i <= m && count < n; i++)
    {
        InputEdge &inputEdge = inputEdges[i];
        if (find(inputEdge.u) != find(inputEdge.v))
        {
            pa[find(inputEdge.u)] = inputEdge.v;
            addEdge(inputEdge.u, inputEdge.v, inputEdge.w);
            addEdge(inputEdge.v, inputEdge.u, inputEdge.w);
            visited[i] = 1;
            sum += inputEdge.w;
            count++;
        }
    }
    return sum;
}

int depth[N];
int fa[N][T];
int firstMax[N][T];
int secondMax[N][T];
int lg[N];
void dfs(int f, int u, int w)
{
    fa[u][0] = f;
    firstMax[u][0] = w;
    secondMax[u][0] = -1;
    depth[u] = depth[f] + 1;
    for (int i = 1; i <= lg[depth[u]] - 1; i++)
    {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        int left = firstMax[u][i - 1], right = firstMax[fa[u][i - 1]][i - 1];
        firstMax[u][i] = std::max(left, right);
        if (left != right)
            secondMax[u][i] = std::max(secondMax[u][i], left > right ? right : left);
    }
    for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
    {
        int v = edges[edgeIndex].v;
        if (v != f)
        {
            dfs(u, v, edges[edgeIndex].w);
        }
    }
}

int LCA(int x, int y)
{
    if (depth[x] < depth[y])
    {
        std::swap(x, y);
    }
    for (int i = lg[depth[x]] - 1; i >= 0; i--)
    {
        if (depth[fa[x][i]] >= depth[y])
            x = fa[x][i];
    }
    if (x == y)
        return x;
    for (int i = lg[depth[x]] - 1; i >= 0; i--)
    {
        if (fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

int maxEW(int u, int lca, int requiredW)
{
    int w = -1;
    for (int i = lg[depth[u]] - 1; i >= 0; i--)
    {
        if (depth[fa[u][i]] >= depth[lca])
        {
            w = std::max(w, firstMax[u][i] == requiredW ? secondMax[u][i] : firstMax[u][i]);
            u = fa[u][i];
        }
    }
    return w;
}

int main()
{
    scanf("%d%d", &n, &m);
    lg[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        startEdge[i] = 0;
        depth[i] = 0;
        pa[i] = i;
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        inputEdges[i] = {u, v, w};
        visited[i] = 0;
    }
    long long minSum, ans = LONG_LONG_MAX;
    minSum = kruskal();
    dfs(0, 1, 0);
    for (int i = 1; i <= m; i++)
    {
        InputEdge &inputEdge = inputEdges[i];
        if (!visited[i])
        {
            int lca = LCA(inputEdge.u, inputEdge.v);
            int maxUW = maxEW(inputEdge.u, lca, inputEdge.w);
            int maxVW = maxEW(inputEdge.v, lca, inputEdge.w);
            if (maxUW == -1 && maxVW == -1)
                continue;
            ans = std::min(ans, minSum - std::max(maxUW, maxVW) + inputEdge.w);
        }
    }
    printf("%lld", ans);
}