#include <iostream>
#include <limits.h>
#define N 1000000

long long arr[N];
long long dp[N];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &arr[i]);
    dp[0] = arr[0];
    long long maxVal = LONG_LONG_MIN;
    for (int i = 1; i < n; i++)
    {
        dp[i] = std::max(dp[i - 1] + arr[i], arr[i]);
        maxVal = std::max(maxVal, dp[i]);
    }
    printf("%lld", maxVal);
}