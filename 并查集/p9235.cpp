#include <algorithm>
#include <iostream>
#include <vector>
#define N 400005
#define K 20

int visited[N]{};
int parent[N]{};
int val[N]{};
int depth[N]{};
int f[N][K]{};

int find(int n)
{
    if (parent[n] != n)
        parent[n] = find(parent[n]);
    return parent[n];
}

typedef struct Edge
{
    int u;
    int v;
    int w;
} Edge;
bool cmp(Edge e1, Edge e2)
{
    return e1.w > e2.w;
}

int lca(int n1, int n2)
{
    if (depth[n1] < depth[n2])
        std::swap(n1, n2);
    int tmp = depth[n1] - depth[n2];
    for (int i = K - 1; i >= 0; i--)
        if (tmp >> i & 1)
        {
            n1 = f[n1][i];
        }
    for (int i = K - 1; i >= 0; i--)
    {
        if (f[n1][i] != f[n2][i])
        {
            n1 = f[n1][i];
            n2 = f[n2][i];
        }
    }
    return val[f[n1][0]];
}

Edge e[N];
std::vector<int> out[N];

void dfs(int n, int pn)
{
    visited[n] = 1;
    f[n][0] = pn;
    depth[n] = depth[pn] + 1;
    for (int i = 0; i < out[n].size(); i++)
    {
        if (pn == out[n][i])
            continue;
        dfs(out[n][i], n);
    }
}

int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        parent[i] = i;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    }
    std::sort(e, e + m, cmp);
    for (int i = 0; i < m; i++)
    {
        int pu = find(e[i].u);
        int pv = find(e[i].v);
        if (pu != pv)
        {
            // merge
            n++;
            int new_n = n;
            parent[new_n] = parent[pu] = parent[pv] = new_n;
            val[new_n] = e[i].w;
            out[new_n].push_back(pu);
            out[new_n].push_back(pv);
        }
    }
    for (int i = n; i >= 1; i--)
    {
        // calculate depth
        if (!visited[i])
            dfs(i, i);
    }

    for (int i = 1; i <= K - 1; i++)
        for (int j = 1; j <= n; j++)
            f[j][i] = f[f[j][i - 1]][i - 1];

    for (int i = 0; i < q; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (find(x) == find(y))
            printf("%d\n", lca(x, y));
        else
            printf("-1\n");
    }
}