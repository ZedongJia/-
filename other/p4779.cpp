#include <iostream>
#include <queue>
#define N 100001
#define E 200001
typedef struct Edge
{
    int u;
    int v;
    int w;
    int next;
} Edge;

int totalEdge = 1;
int startEdge[N];
Edge edges[E];

void addEdge(int u, int v, int w)
{
    edges[totalEdge] = {u, v, w, startEdge[u]};
    startEdge[u] = totalEdge;
    totalEdge++;
}

int n, m, s;
int visited[N];
int dis[N];
typedef struct Node
{
    int id;
    int distance;
    bool operator<(const Node &n) const
    {
        return this->distance > n.distance;
    }
} Node;
Node nodes[N];

int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; i++)
    {
        startEdge[i] = 0;
        nodes[i] = {i, INT32_MAX};
        dis[i] = INT32_MAX;
        visited[i] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    dis[s] = 0;
    std::priority_queue<Node> tmp;
    tmp.push({s, 0});
    while (!tmp.empty())
    {
        int u = tmp.top().id;
        tmp.pop();
        if (visited[u])
            continue;
        visited[u] = 1;
        for (int edgeIndex = startEdge[u]; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            Edge &edge = edges[edgeIndex];
            if (dis[edge.u] == INT32_MAX)
                continue;
            dis[edge.v] = std::min(dis[edge.v], edge.w + dis[edge.u]);
            tmp.push({edge.v, dis[edge.v]});
        }
    }
    for (int i = 1; i < n; i++)
        printf("%d ", dis[i]);
    printf("%d", dis[n]);
}