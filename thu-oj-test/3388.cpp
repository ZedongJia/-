#include <cmath>
#include <iostream>

long long x, y, k;

long long pow(long long x, long long y, long long mod)
{
    long long ans = 1;
    while (y)
    {
        if (y & 1)
        {
            ans = ans * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return ans % mod;
}

int main()
{
    while (std::cin >> x >> y >> k)
    {
        int res = pow(x, y, k - 1);
        printf("%lld\n", res == 0 ? k - 1 : res);
    }
}