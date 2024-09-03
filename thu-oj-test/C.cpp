#include <iostream>
using namespace std;
#define ll long long
const ll N = (1e5 + 7);
const ll MOD = (1e9 + 7);

ll fact[N], invfact[N];

ll pow(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

void init()
{
    fact[0] = invfact[0] = 1;
    for (ll i = 1; i < N; i++)
    {
        fact[i] = (fact[i - 1] * i) % MOD;
        invfact[i] = invfact[i - 1] * pow(i, MOD - 2) % MOD;
    }
}

ll C(ll m, ll n)
{
    return fact[m] * invfact[n] % MOD * invfact[m - n] % MOD;
}

int main()
{
    init();
    cout << C(6, 2);
}