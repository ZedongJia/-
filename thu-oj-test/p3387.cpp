#include <iostream>
#include <queue>
#define N 10001
typedef struct Edge
{
    int u;
    int v;
    int next = 0;
} Edge;

Edge edges[N * 10];
int totalEdge = 1;
int startEdge[N];
int vals[N];
int newVals[N];
int maxVals[N];
int visited[N];
int parent[N];
int indegrees[N];
int n, m;

int find(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find(parent[v]);
}

void addEdge(int u, int v)
{
    edges[totalEdge] = {u, v, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}

void dfs(int u)
{
    for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
    {
        int v = edges[edgeIndex].v;
        if (!visited[v])
        {
            visited[v] = visited[u] + 1;
            dfs(v);
        }
        int fu = find(u), fv = find(v);
        if (visited[fv] > 0)
        {
            if (visited[fu] < visited[fv])
                parent[fv] = fu;
            else
                parent[fu] = fv;
        }
    }
    visited[u] = -1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &vals[i]);
        newVals[i] = 0;
        visited[i] = 0;
        startEdge[i] = 0;
        parent[i] = i;
        indegrees[i] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (visited[i] == 0)
        {
            visited[i] = 1;
            dfs(i);
        }
    for (int i = 1; i <= n; i++)
    {
        newVals[find(i)] += vals[i];
        startEdge[i] = 0;
    }
    totalEdge = 1;
    for (int i = 1; i <= m; i++)
    {
        int x = find(edges[i].u);
        int y = find(edges[i].v);
        if (x != y)
        {
            addEdge(x, y);
            indegrees[y]++;
        }
    }
    std::queue<int> vertexes;
    for (int i = 1; i <= n; i++)
    {
        if (i == find(i) && !indegrees[i])
        {
            vertexes.push(i);
            maxVals[i] = newVals[i];
        }
    }
    int ans = 0;
    while (!vertexes.empty())
    {
        int u = vertexes.front();
        vertexes.pop();
        for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            int v = edges[edgeIndex].v;
            maxVals[v] = std::max(maxVals[v], maxVals[u] + newVals[v]);
            indegrees[v]--;
            if (!indegrees[v])
                vertexes.push(v);
        }
        ans = std::max(ans, maxVals[u]);
    }
    printf("%d", ans);
}