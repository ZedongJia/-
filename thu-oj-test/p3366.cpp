#include <algorithm>
#include <iostream>
#define N 5001
#define E 200001
int n, m;
typedef struct Edge
{
    int u;
    int v;
    int w;
} Edge;
Edge edges[E];
bool cmp(const Edge &e1, const Edge &e2)
{
    return e1.w < e2.w;
}
int p[N];
int find(int u)
{
    if (u == p[u])
        return u;
    else
        return p[u] = find(p[u]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        p[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    std::sort(edges + 1, edges + 1 + m, cmp);
    int ans = 0;
    int i = 1, count = 1;
    while (i <= m && count < n)
    {
        Edge &edge = edges[i];
        int u = edge.u, v = edge.v, w = edge.w;
        if (find(u) != find(v))
        {
            p[find(u)] = v;
            ans += w;
            count++;
        }
        i++;
    }
    count != n ? printf("orz") : printf("%d", ans);
}