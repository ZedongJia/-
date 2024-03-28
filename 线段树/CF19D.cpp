#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#define N 400005

typedef struct Op
{
    char op;
    int x;
    int y;
} Op;

// 离散化映射
std::vector<int> X, Y;
std::vector<Op> ops;
int tree[N * 2]{};
std::set<int> ys[N];

int qx;
void query(int n, int l, int r, int x, int y)
{
    if (qx != INT32_MAX)
        return;
    if (l == r && x < l)
    {
        if (tree[n] > y)
        {
            qx = l;
            return;
        }
    }
    int mid = (l + r) / 2;
    if (x < mid && tree[2 * n] > y)
    {
        query(2 * n, l, mid, x, y);
    }
    if (tree[2 * n + 1] > y)
        query(2 * n + 1, mid + 1, r, x, y);
}

void update(int n, int l, int r, int x, int y)
{
    if (l == r)
    {
        tree[n] = y;
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid)
    {
        update(2 * n, l, mid, x, y);
    }
    else
    {
        update(2 * n + 1, mid + 1, r, x, y);
    }
    tree[n] = std::max(tree[2 * n], tree[2 * n + 1]);
}

void build(int n, int l, int r)
{
    tree[n] = -1;
    if (l == r)
    {
        ys[l].insert(-1);
        return;
    }
    int mid = (l + r) / 2;
    build(2 * n, l, mid);
    build(2 * n + 1, mid + 1, r);
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char op[10];
        int x, y;
        scanf("%s%d%d", op, &x,&y);
        X.push_back(x);
        Y.push_back(y);
        ops.push_back({op[0], x, y});
    }
    // 构建映射 1 -> 123 ...
    std::sort(X.begin(), X.end());
    std::sort(Y.begin(), Y.end());
    X.erase(std::unique(X.begin(), X.end()), X.end());
    Y.erase(std::unique(Y.begin(), Y.end()), Y.end());
    build(1, 0, X.size());
    for (int i = 0; i < ops.size(); i++)
    {
        char op = ops[i].op;
        int x = ops[i].x;
        int y = ops[i].y;
        int hx = std::lower_bound(X.begin(), X.end(), x) - X.begin();
        int hy = std::lower_bound(Y.begin(), Y.end(), y) - Y.begin();
        if (op == 'a')
        {
            int tmp = *ys[hx].rbegin();
            if (tmp < hy)
                update(1, 0, X.size(), hx, hy);
            ys[hx].insert(hy);
        }
        else if (op == 'r')
        {
            int tmp1 = *ys[hx].rbegin();
            ys[hx].erase(hy);
            int tmp2 = *ys[hx].rbegin();
            if (tmp1 != tmp2)
                update(1, 0, X.size(), hx, tmp2);
        }
        else
        {
            qx = INT32_MAX;
            query(1, 0, X.size(), hx, hy);
            if (qx == INT32_MAX)
            {
                printf("-1\n");
                continue;
            }
            int qy = *ys[qx].lower_bound(hy + 1);
            printf("%d %d\n", X[qx], Y[qy]);
        }
    }
}