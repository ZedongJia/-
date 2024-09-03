/**
    主席树
*/
#include <algorithm>
#include <iostream>
#include <vector>

#define N 200001
typedef struct Node
{
    int lc;
    int rc;
    int val;
} Node;
int ncnt = 0;
Node tree[N * 50];

std::vector<int> root;
std::vector<int> nums;
std::vector<int> X;

int query(int l_n, int r_n, int l, int r, int k)
{
    if (l == r)
        return l;
    int mid = (l + r) / 2;
    int lsum = tree[tree[r_n].lc].val - tree[tree[l_n].lc].val;
    if (lsum >= k)
    {
        return query(tree[l_n].lc, tree[r_n].lc, l, mid, k);
    }
    else
    {
        return query(tree[l_n].rc, tree[r_n].rc, mid + 1, r, k - lsum);
    }
}

int update(int old_n, int l, int r, int num)
{
    ncnt++;
    int n = ncnt;
    tree[n] = tree[old_n];
    tree[n].val++;
    if (l == r)
    {
        return n;
    }
    int mid = (l + r) / 2;
    if (num <= mid)
        tree[n].lc = update(tree[old_n].lc, l, mid, num);
    else
        tree[n].rc = update(tree[old_n].rc, mid + 1, r, num);
    return n;
}

int build(int l, int r)
{
    ncnt++;
    int n = ncnt;
    tree[n].val = 0;
    if (l == r)
        return n;
    int mid = (l + r) / 2;
    tree[n].lc = build(l, mid);
    tree[n].rc = build(mid + 1, r);
    return n;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        int num;
        scanf("%d", &num);
        X.push_back(num);
        nums.push_back(num);
    }
    std::sort(X.begin(), X.end());
    X.erase(std::unique(X.begin(), X.end()), X.end());
    root.push_back(build(0, X.size()));
    for (int i = 0; i < n; i++)
    {
        int nidx = std::lower_bound(X.begin(), X.end(), nums[i]) - X.begin();
        root.push_back(update(*root.rbegin(), 0, X.size(), nidx));
    }
    for (int i = 0; i < m; i++)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int idx = query(root[l - 1], root[r], 0, X.size(), k);
        printf("%d\n", X[idx]);
    }
}