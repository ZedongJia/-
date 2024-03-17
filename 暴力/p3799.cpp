#include <iostream>
#define mod (long long)(1e9 + 7)
long long arr[100001]{};
long long num[1001]{};
long long C(long long n, long long k)
{
    return k == 1 ? n : n * (n - 1) / 2;
}
int main()
{
    long long n, upper = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
        num[arr[i]]++;
        upper = std::max(upper, arr[i]);
    }
    long long cnt = 0;
    for (int i = 1; i <= upper; i++)
    {
        if (num[i] >= 2)
        {
            long long times = C(num[i], 2) % mod;
            for (int j = 1; j <= int(i / 2); j++)
            {
                if (j != i - j)
                {
                    if (num[j] >= 1 && num[i - j] >= 1)
                    {

                        cnt += (C(num[j], 1) * C(num[i - j], 1) * times) % mod;
                    }
                }
                else
                {

                    if (num[j] >= 2)
                    {
                        cnt += (C(num[j], 2) * times) % mod;
                    }
                }
            }
        }
    }
    printf("%lld", cnt % mod);
}