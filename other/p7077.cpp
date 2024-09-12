#include <iostream>
#include <queue>
#include <stack>

#define N 100001
#define E 1000001
#define MOD 998244353
typedef struct Edge
{
    int v;
    int next = 0;
} Edge;
typedef struct Node
{
    int type = 0;
    int tgtIndex = 0;
    long long addDelta = 0;
    long long accum = 0;
    long long mulDelta = 1;
    int startEdge = 0;
} Node;
Edge edges[E];
Node nodes[N];
int indegrees[N];
int totalEdges = 1;
int n;
int m;
void addEdge(int u, int v)
{
    edges[totalEdges] = {v, nodes[u].startEdge};
    nodes[u].startEdge = totalEdges;
    indegrees[v]++;
    totalEdges++;
}

int topoOrder[N];
int currIndex = 1;

void toposort()
{
    std::queue<int> curr;
    for (int i = 1; i <= m; i++)
        if (!indegrees[i])
            curr.push(i);
    while (!curr.empty())
    {
        int nodeIndex = curr.front();
        curr.pop();
        topoOrder[currIndex] = nodeIndex;
        currIndex++;
        Node &node = nodes[nodeIndex];
        for (int edgeIndex = node.startEdge; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            int v = edges[edgeIndex].v;
            indegrees[v]--;
            if (!indegrees[v])
            {
                curr.push(v);
            }
        }
    }
}

void mulDeltaUp()
{
    for (int i = m; i >= 1; i--)
    {
        int nodeIndex = topoOrder[i];
        Node &node = nodes[nodeIndex];
        for (int edgeIndex = node.startEdge; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            int v = edges[edgeIndex].v;
            node.mulDelta = (node.mulDelta * nodes[v].mulDelta) % MOD;
        }
    }
}

void accumDeltaDown()
{
    for (int i = 1; i <= m; i++)
    {
        int nodeIndex = topoOrder[i];
        Node &node = nodes[nodeIndex];
        long long accum = 1;
        for (int edgeIndex = node.startEdge; edgeIndex; edgeIndex = edges[edgeIndex].next)
        {
            int v = edges[edgeIndex].v;
            nodes[v].accum = (nodes[v].accum + (node.accum * accum) % MOD) % MOD;
            accum = (nodes[v].mulDelta * accum) % MOD;
        }
    }
}

long long data[N];
int querys[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &data[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        indegrees[i] = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &nodes[i].type);
        switch (nodes[i].type)
        {
        case 1: {
            scanf("%d%lld", &nodes[i].tgtIndex, &nodes[i].addDelta);
            break;
        }
        case 2: {
            scanf("%lld", &nodes[i].mulDelta);
            break;
        }
        case 3: {
            int edgeNumber;
            scanf("%d", &edgeNumber);
            while (edgeNumber--)
            {
                int v;
                scanf("%d", &v);
                addEdge(i, v);
            }
            break;
        }
        }
    }
    toposort();
    mulDeltaUp();
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
        scanf("%d", &querys[i]);
    long long currAccum = 1;
    for (int i = q - 1; i >= 0; i--)
    {
        nodes[querys[i]].accum = (nodes[querys[i]].accum + currAccum) % MOD;
        currAccum = (currAccum * nodes[querys[i]].mulDelta) % MOD;
    }
    accumDeltaDown();
    for (int i = 1; i <= n; i++)
        data[i] = (data[i] * currAccum) % MOD;
    for (int i = 1; i <= m; i++)
    {
        if (nodes[i].type == 1)
        {
            data[nodes[i].tgtIndex] = (data[nodes[i].tgtIndex] + (nodes[i].accum * nodes[i].addDelta) % MOD) % MOD;
        }
    }
    for (int i = 1; i < n; i++)
        printf("%lld ", data[i]);
    printf("%lld", data[n]);
}