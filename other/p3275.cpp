#include <iostream>
#include <queue>
#define N 100001
typedef struct Edge
{
    int u;
    int v;
    bool eq;
    int next;
} Edge;

int totalEdge = 1;
int startEdge[N];
Edge edges[N << 1];
int n, k;

int size[N];
int count[N];
int visited[N];
int indegree[N];
void addEdge(int u, int v, bool eq)
{
    edges[totalEdge] = {u, v, eq, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}

int pa[N];

int find(int u)
{
    return u == pa[u] ? u : pa[u] = find(pa[u]);
}

void dfs(int u)
{
    for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
    {
        int v = edges[edgeIndex].v;
        if (visited[v] == 0)
        {
            visited[v] = visited[u] + 1;
            dfs(v);
        }
        int fu = find(u), fv = find(v);
        if (visited[fv] > 0)
        {
            if (visited[fv] > visited[fu])
            {
                pa[fv] = fu;
            }
            else
            {
                pa[fu] = fv;
            }
        }
    }
    visited[u] = -1;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        startEdge[i] = 0;
        size[i] = 0;
        visited[i] = 0;
        indegree[i] = 0;
        pa[i] = i;
    }
    for (int i = 1; i <= k; i++)
    {
        int u, v, t;
        scanf("%d%d%d", &t, &u, &v);
        switch (t)
        {
        case 1:
            addEdge(u, v, 1);
            addEdge(v, u, 1);
            break;
        case 2:
            addEdge(u, v, 0);
            break;
        case 3:
            addEdge(v, u, 1);
            break;
        case 4:
            addEdge(v, u, 0);
            break;
        case 5:
            addEdge(u, v, 1);
            break;
        }
    }
    for (int i = 1; i <= n; i++)
        if (visited[i] == 0)
            visited[i] = 1, dfs(i);
    for (int i = 1; i <= n; i++)
    {
        size[find(i)]++;
        startEdge[i] = 0;
    }
    int totalK = totalEdge;
    totalEdge = 1;
    for (int i = 1; i < totalK; i++)
    {
        Edge &edge = edges[i];
        int x = find(edge.u);
        int y = find(edge.v);
        bool eq = edge.eq;
        if (x == y)
        {
            if (!eq)
            {
                printf("-1");
                return 0;
            }
        }
        else
        {
            addEdge(x, y, eq);
            indegree[y]++;
        }
    }
    std::queue<int> tmp;
    for (int i = 1; i <= n; i++)
    {
        if (find(i) == i)
        {
            if (indegree[i] == 0)
            {
                tmp.push(i);
                count[i] = 1;
            }
        }
    }
    long long reqCount = 0;
    while (!tmp.empty())
    {
        int u = tmp.front();
        tmp.pop();
        reqCount += count[u] * size[u];
        for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            int v = edges[edgeIndex].v;
            bool eq = edges[edgeIndex].eq;
            count[v] = std::max(count[u] + (!eq ? 1 : 0), count[v]);
            indegree[v]--;
            if (indegree[v] == 0)
                tmp.push(v);
        }
    }
    printf("%lld", reqCount);
}