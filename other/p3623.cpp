#include <algorithm>
#include <iostream>
#include <vector>
#define N 20001
#define E 100001

typedef struct Edge
{
    int id;
    int u;
    int v;
    int w;
    int key = 0;
} Edge;
int n, m, k;
Edge edges[E];

bool cmp1(const Edge &e1, const Edge &e2)
{
    return e1.w > e2.w;
}
bool cmp2(const Edge &e1, const Edge &e2)
{
    if (e1.w == e2.w)
        return e1.key > e2.key;
    return e1.w < e2.w;
}
bool cmp3(const Edge &e1, const Edge &e2)
{
    if (e1.w == e2.w)
        return e1.id < e2.id;
    return e1.w < e2.w;
}

int pa[N];
int find(int u)
{
    return u == pa[u] ? pa[u] : pa[u] = find(pa[u]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        pa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].id = i;
    }
    std::sort(edges + 1, edges + 1 + m, cmp1);
    int count = 1;
    int reqK = 0;
    for (int i = 1; i <= m && count < n; i++)
    {
        Edge &edge = edges[i];
        if (find(edge.u) != find(edge.v))
        {
            pa[find(edge.u)] = edge.v;
            edge.key = 1;
            if (edge.w == 0)
            {
                reqK++;
            }
            count++;
        }
    }
    if (count != n || reqK > k)
    {
        printf("no solution");
    }
    else
    {
        std::vector<Edge> ans;
        count = 1;
        for (int i = 1; i <= n; i++)
            pa[i] = i;
        std::sort(edges + 1, edges + 1 + m, cmp2);
        int selected = 0;
        for (int i = 1; i <= m && count < n; i++)
        {
            Edge &edge = edges[i];
            if (find(edge.u) != find(edge.v))
            {
                if (edge.w == 0 && selected >= k)
                    continue;
                pa[find(edge.u)] = edge.v;
                ans.push_back(edge);
                count++;
                if (edge.w == 0)
                    selected++;
            }
        }
        if (selected < k)
        {
            printf("no solution");
        }
        else
        {
            std::sort(ans.begin(), ans.end(), cmp3);
            for (Edge &e : ans)
                printf("%d %d %d\n", e.u, e.v, e.w);
        };
    }
}