#include <iostream>
#define ll long long
ll tree[2000000]{};
ll delta[2000000]{};
ll arr[2000000]{};
ll ans[2000000];

void up(ll node)
{
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void f(ll node, ll lval, ll rval, ll k)
{
    tree[node] += (rval - lval + 1) * k;
    delta[node] += k;
}

void down(ll node, ll lval, ll rval)
{
    f(2 * node, lval, (lval + rval) / 2, delta[node]);
    f(2 * node + 1, (lval + rval) / 2 + 1, rval, delta[node]);
    delta[node] = 0;
}

void build(ll node, ll lval, ll rval)
{
    if (lval == rval)
    {
        tree[node] = arr[lval];
        return;
    }
    build(2 * node, lval, (lval + rval) / 2);
    build(2 * node + 1, (lval + rval) / 2 + 1, rval);
    up(node);
}

void update(ll node, ll lval, ll rval, ll qlval, ll qrval, ll k)
{
    if (qlval <= lval && qrval >= rval)
    {
        tree[node] += k * (rval - lval + 1);
        delta[node] += k;
        return;
    }
    down(node, lval, rval); // 上一次的更新到子节点
    ll mid = (rval + lval) / 2;
    if (qlval <= mid)
        update(2 * node, lval, mid, qlval, qrval, k); // 这一次的更新到子节点
    if (qrval > mid)
        update(2 * node + 1, mid + 1, rval, qlval, qrval, k); // 这一次的更新到子节点
    up(node);                                                 // 更新自己
}

ll querySum(ll node, ll lval, ll rval, ll qlval, ll qrval)
{
    down(node, lval, rval); // 上一次的更新到子节点
    if (qlval <= lval && qrval >= rval)
    {
        return tree[node];
    }
    ll mid = (rval + lval) / 2;
    ll lsum = 0;
    ll rsum = 0;
    if (qlval <= mid)
        lsum = querySum(2 * node, lval, mid, qlval, qrval);
    if (qrval > mid)
        rsum = querySum(2 * node + 1, mid + 1, rval, qlval, qrval);
    return lsum + rsum;
}

int main()
{
    ll n, m;
    std::cin >> n >> m;
    for (ll i = 0; i < n; i++)
        std::cin >> arr[i];
    build(1, 0, n - 1);
    ll ansIndex = 0;
    while (m--)
    {
        ll op;
        std::cin >> op;
        switch (op)
        {
        case 1: {
            ll x, y, k;
            std::cin >> x >> y >> k;
            update(1, 0, n - 1, x - 1, y - 1, k);
            break;
        }
        case 2: {
            ll x, y;
            std::cin >> x >> y;
            ans[ansIndex] = querySum(1, 0, n - 1, x - 1, y - 1);
            ansIndex++;
            break;
        }
        }
    }
    for (ll i = 0; i < ansIndex - 1; i++)
        printf("%lld\n", ans[i]);
    printf("%lld", ans[ansIndex - 1]);
}